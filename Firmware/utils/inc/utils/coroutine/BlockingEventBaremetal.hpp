#include <atomic>

namespace CoroUtils
{
class BlockingEvent
{
public:
    void wait()
    {
        while (!m_isSet)
        {
        }
    }

    void set()
    {
        m_isSet.store(true);
    }

private:
    std::atomic_bool m_isSet = false;
};
} // namespace CoroUtils