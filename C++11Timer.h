#include <chrono>

// simulation of Windows GetTickCount()
unsigned long long
GetTickCount()
{
    using namespace std::chrono;
    return duration_cast<milliseconds>(steady_clock::now().time_since_epoch()).count();
}

// Clock built upon Windows GetTickCount()
struct TickCountClock
{
    typedef unsigned long long                       rep;
    typedef std::milli                               period;
    typedef std::chrono::duration<rep, period>       duration;
    typedef std::chrono::time_point<TickCountClock>  time_point;
    static const bool is_steady =                    true;

    static time_point now() noexcept
    {
        return time_point(duration(GetTickCount()));
    }
};

// Test TickCountClock

#include <thread>
#include <iostream>

int
main()
{
    auto t0 = TickCountClock::now();
    std::this_thread::sleep_until(t0 + std::chrono::seconds(1));
    auto t1 = TickCountClock::now();
    std::cout << (t1-t0).count() << "ms\n";
}
