// Detailed research from cppcoro library
#include <condition_variable>
#include <mutex>
#include <atomic>

namespace CoroUtils
{
class BlockingEvent
{
public:
    void wait()
    {
        std::unique_lock<std::mutex> lock(mutex);
        condEvent.wait(lock, [this] { return m_isSet.load(std::memory_order_acquire); });
    }

    void set()
    {
        m_isSet.store(true, std::memory_order_release);
        condEvent.notify_all();
    }

private:
    std::atomic_bool m_isSet = false;
    std::mutex mutex;
    std::condition_variable condEvent;
};
}