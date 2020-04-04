// from https://github.com/larspensjo/SimpleSignal/blob/master/SimpleSignal.h
// Modyfied by ValentiWorkLearning

#pragma once

#include <memory>
#include <functional>
#include <list>
//#include <vector>
#include <algorithm>
#include <string>
#include <etl/vector.h>

#include  "logger_service.hpp"

namespace Simple {

template<typename Type, const size_t StorageSize = 3>
using TStorageType = etl::vector<Type, StorageSize>;

namespace Lib {

/// ProtoSignal is the template implementation for callback list.
template<typename,typename> class ProtoSignal;   // undefined

/// CollectorInvocation invokes signal handlers differently depending on return type.
template<typename,typename> struct CollectorInvocation;

/// CollectorLast returns the result of the last signal handler from a signal emission.
template<typename Result>
struct CollectorLast {
  using CollectorResult = Result;
  explicit        CollectorLast ()              : last_() {}
  inline bool     operator()    (Result r)      { last_ = r; return true; }
  CollectorResult result        ()              { return last_; }
private:
  Result last_;
};

/// CollectorDefault implements the default signal handler collection behaviour.
template<typename Result>
struct CollectorDefault : CollectorLast<Result>
{};

/// CollectorDefault specialisation for signals with void return type.
template<>
struct CollectorDefault<void> {
  using CollectorResult = void;
  void                  result     ()           {}
  inline bool           operator() (void)       { return true; }
};

/// CollectorInvocation specialisation for regular signals.
template<class Collector, class R, class... Args>
struct CollectorInvocation<Collector, R (Args...)> {
  inline bool
  invoke (Collector &collector, const std::function<R (Args...)> &cbf, Args... args) const
  {
    return collector (cbf (args...));
  }
};

/// CollectorInvocation specialisation for signals with void return type.
template<class Collector, class... Args>
struct CollectorInvocation<Collector, void (Args...)> {
  inline bool
  invoke (Collector &collector, const std::function<void (Args...)> &cbf, Args... args) const
  {
    cbf (args...); return collector();
  }
};

struct ExecuteLaterPool
{
    static ExecuteLaterPool& Instance()
    {
        static ExecuteLaterPool executePool;
        return executePool;
    }

    template< typename Function, typename ... Args >
    auto pushToLater( Function&& function, Args&& ... _argList )
    {
        executionQueue.push_back(
            [this,localFunction = function, _argList...]
            {
                localFunction(_argList...);
            }
        );
    }

    void processQueue()
    {
      for( auto& signalItem : executionQueue )
      {
            signalItem();
      }
      executionQueue.clear();
    }
private:

    TStorageType<std::function<void()>> executionQueue;
};

/// ProtoSignal template specialised for the callback signature and collector.
template<class Collector, class R, class... Args>
class ProtoSignal<R (Args...), Collector> : private CollectorInvocation<Collector, R (Args...)> {
protected:
  using CbFunction = std::function<R (Args...)>;
  using Result = typename CbFunction::result_type;
  using CollectorResult = typename Collector::CollectorResult;

private:
  /*copy-ctor*/ ProtoSignal (const ProtoSignal&) = delete;
  ProtoSignal&  operator=   (const ProtoSignal&) = delete;

  using CallbackSlot = std::unique_ptr<CbFunction>;
  using CallbackList = TStorageType<CallbackSlot>;

  CallbackList callback_list_;

  size_t add_cb(const CbFunction& cb, size_t _callbackId = std::numeric_limits<size_t>::max() )
  {
      auto callback = std::make_unique<CbFunction>(cb);
      size_t callbackId = reinterpret_cast<size_t>(callback.get());
      callback_list_.emplace_back( std::move(callback) );
      return callbackId;
  }

  bool remove_cb(size_t id)
  {
    auto it =std::remove_if(begin(callback_list_), end(callback_list_),
                            [id](const CallbackSlot& slot) { return size_t(slot.get()) == id; });
    bool const removed = it != end(callback_list_);
    callback_list_.erase(it, end(callback_list_));
    return removed;
  }

public:
  /// ProtoSignal constructor, connects default callback if non-nullptr.
  ProtoSignal (const CbFunction &method)
  {
    if (method)
      add_cb(method);
  }
  /// ProtoSignal destructor releases all resources associated with this signal.
  ~ProtoSignal ()
  {
  }

  /// Operator to add a new function or lambda as signal handler, returns a handler connection ID.
  size_t connect (const CbFunction &cb, size_t connectionId = std::numeric_limits<size_t>::max())      { return add_cb(cb,connectionId); }
  /// Operator to remove a signal handler through it connection ID, returns if a handler was removed.
  bool   disconnect (size_t connection)         { return remove_cb(connection); }

  /// Emit a signal, i.e. invoke all its callbacks and collect return types with the Collector.
  CollectorResult
  emit (Args... args) const
  {
    Collector collector;
    for (auto &slot : callback_list_) {
        if (slot) {
            const bool continue_emission = this->invoke (collector, *slot, args...);
            if (!continue_emission)
              break;
        }
    }
    return collector.result();
  }

  void emitLater(Args ... args )
  {
      ExecuteLaterPool::Instance().pushToLater(
          [this,args... ]
          {
              emit(args...);
          }
      );
  }

  // Number of connected slots.
  std::size_t
  size () const
  {
    return callback_list_.size();
  }
};

} // Lib
// namespace Simple

/**
 * Signal is a template type providing an interface for arbitrary callback lists.
 * A signal type needs to be declared with the function signature of its callbacks,
 * and optionally a return result collector class type.
 * Signal callbacks can be added with operator+= to a signal and removed with operator-=, using
 * a callback connection ID return by operator+= as argument.
 * The callbacks of a signal are invoked with the emit() method and arguments according to the signature.
 * The result returned by emit() depends on the signal collector class. By default, the result of
 * the last callback is returned from emit(). Collectors can be implemented to accumulate callback
 * results or to halt a running emissions in correspondance to callback results.
 * The signal implementation is safe against recursion, so callbacks may be removed and
 * added during a signal emission and recursive emit() calls are also safe.
 * The overhead of an unused signal is intentionally kept very low, around the size of a single pointer.
 * Note that the Signal template types is non-copyable.
 */
template <typename SignalSignature, class Collector = Lib::CollectorDefault<typename std::function<SignalSignature>::result_type> >
struct Signal /*final*/ :
    Lib::ProtoSignal<SignalSignature, Collector>
{
  using ProtoSignal = Lib::ProtoSignal<SignalSignature, Collector>;
  using CbFunction = typename ProtoSignal::CbFunction;
  /// Signal constructor, supports a default callback as argument.
  Signal (const CbFunction &method = CbFunction()) : ProtoSignal (method) {}
};

/// This function creates a std::function by binding @a object to the member function pointer @a method.
template<class Instance, class Class, class R, class... Args> std::function<R (Args...)>
slot (Instance &object, R (Class::*method) (Args...))
{
  return [&object, method] (Args... args) { return (object .* method) (args...); };
}

/// This function creates a std::function by binding @a object to the member function pointer @a method.
template<class Class, class R, class... Args> std::function<R (Args...)>
slot (Class *object, R (Class::*method) (Args...))
{
  return [object, method] (Args... args) { return (object ->* method) (args...); };
}

/// Keep signal emissions going while all handlers return !0 (true).
template<typename Result>
struct CollectorUntil0 {
  using CollectorResult = Result;
  explicit                      CollectorUntil0 ()      : result_() {}
  const CollectorResult&        result          ()      { return result_; }
  inline bool
  operator() (Result r)
  {
    result_ = r;
    return result_ ? true : false;
  }
private:
  CollectorResult result_;
};

/// Keep signal emissions going while all handlers return 0 (false).
template<typename Result>
struct CollectorWhile0 {
  using CollectorResult = Result;
  explicit                      CollectorWhile0 ()      : result_() {}
  const CollectorResult&        result          ()      { return result_; }
  inline bool
  operator() (Result r)
  {
    result_ = r;
    return result_ ? false : true;
  }
private:
  CollectorResult result_;
};

/// CollectorVector returns the result of the all signal handlers from a signal emission in a std::vector.
template<typename Result>
struct CollectorVector {
  using CollectorResult = TStorageType<Result>;
  const CollectorResult&        result ()       { return result_; }
  inline bool
  operator() (Result r)
  {
    result_.push_back (r);
    return true;
  }
private:
  CollectorResult result_;
};

} // Simple