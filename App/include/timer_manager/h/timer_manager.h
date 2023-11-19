#include <chrono>
#include <condition_variable>
#include <functional>
#include <iostream>
#include <map>
#include <mutex>
#include <thread>
#include "timer_handler.h"

class TimerManager{
public:
    using TimerId = uint32_t;
    using Callable = std::function<void()>;
    using Duration = std::chrono::seconds;

    bool Arm(TimerId timer_id, Duration duration);
    bool Disarm(TimerId timer_id);
    bool SetUpTimer(TimerId timer_id, Callable call_back);
    void Stop();
private:
    std::map<TimerId,std::shared_ptr<TimerHandler>> timer_container_;
    std::map<TimerId,std::thread>thread_container;
    void TimeHandling(TimerId timer_id, bool is_stopped);
    std::mutex time_mutex;
    std::condition_variable cv;
};