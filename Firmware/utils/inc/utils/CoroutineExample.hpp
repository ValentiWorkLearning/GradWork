#include <cstdlib>
#include "logger/logger_service.hpp"

//
// Created by rogerv on 9/29/19.
//
// Based on example code (but with significant cleanup) found in:
// Rainer Grimm, Concurrency with Modern C++ (Leanpub, 2017 - 2019), 207-209.
//
// https://github.com/roger-dv/cpp20-coro-generator/blob/master/main.cpp

#ifndef GENERATOR_H
#define GENERATOR_H

// infiniteDataStream.cpp
#include <coroutine>
#include <memory>

namespace coro_exp {

  template<typename T>
  class generator {
  public:
    struct promise_type;
    using handle_type = std::coroutine_handle<promise_type>;
  private:
    handle_type coro;
  public:
    explicit generator(handle_type h) : coro(h) {}
    generator(const generator &) = delete;
    generator(generator &&oth) noexcept : coro(oth.coro) {
      oth.coro = nullptr;
    }
    generator &operator=(const generator &) = delete;
    generator &operator=(generator &&other) noexcept {
      coro = other.coro;
      other.coro = nullptr;
      return *this;
    }
    ~generator() {
      if (coro) {
        coro.destroy();
      }
    }

    bool next() {
      coro.resume();
      return not coro.done();
    }

    T getValue() {
      return coro.promise().current_value;
    }

    struct promise_type {
    private:
      T current_value{};
      friend class generator;
    public:
      promise_type() = default;
      ~promise_type() = default;
      promise_type(const promise_type&) = delete;
      promise_type(promise_type&&) = delete;
      promise_type &operator=(const promise_type&) = delete;
      promise_type &operator=(promise_type&&) = delete;

      auto initial_suspend() {
        return std::suspend_always{};
      }

      auto final_suspend() {
        return std::suspend_always{};
      }

      auto get_return_object() {
        return generator{handle_type::from_promise(*this)};
      }

      auto return_void() {
        return std::suspend_never{};
      }

      auto yield_value(T some_value) {
        current_value = some_value;
        return std::suspend_always{};
      }

      void unhandled_exception() {
        std::exit(1);
      }
    };
  };

} // coroutn_exp

#endif //GENERATOR_H


coro_exp::generator<int> iota(int n = 0) {
  while(true)
    co_yield n++;
}


using coro_exp::generator;

static const double demo_ceiling = 10E44;

generator<double> fibonacci(const double ceiling) {
  double j = 0;
  double i = 1;
  co_yield j;
  if (ceiling > j) {
    do {
      co_yield i;
      double tmp = i;
      i += j;
      j = tmp;
    } while (i <= ceiling);
  }
}

void testMe(){
    LOG_DEBUG( "Example program using C++20 coroutine to implement a Fibonacci Sequence generator" );
    auto iter = fibonacci(demo_ceiling);
    auto value = iter.getValue();
    LOG_DEBUG(static_cast<int>(value));

    iter.next();
    value = iter.getValue();
    LOG_DEBUG(static_cast<int>(value));

    iter.next();
    value = iter.getValue();
    LOG_DEBUG(static_cast<int>(value));

    iter.next();
    value = iter.getValue();
    LOG_DEBUG(static_cast<int>(value));
}