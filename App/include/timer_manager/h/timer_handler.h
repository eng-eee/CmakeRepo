#include <atomic>
#include <chrono>
#include <condition_variable>
#include <ctime>
#include <functional>
#include <iostream>
#include <mutex>

class TimerHandler{
public:
  using TimerId = uint32_t;
  using OnMessage = std::function<void(TimerId,bool)>;
  using Callable = std::function<void()>;
  using Duration = std::chrono::seconds;
  
  TimerHandler(TimerId timer_id, OnMessage timeout_call_back, Callable call_back) : timer_id_(timer_id),timeout_call_back_{timeout_call_back}, call_back_{call_back}{}
  void Arm(Duration duration)
	{
		std::unique_lock<std::mutex>lock{mtx};
		is_stopped = false;
		auto time_ = std::chrono::system_clock::now()+duration;
		cv.wait_until(lock,time_,[&]{
			return is_stopped.load();
		});
		timeout_call_back_(timer_id_,is_stopped);
	}

  void Disarm(){
		is_stopped = true;
		cv.notify_one();
	}
  
	void Stop() {
		is_stopped = true;
		cv.notify_one();
	}
	Callable GetCallBack(){
		return call_back_;
	}

private:
  TimerId timer_id_;
  OnMessage timeout_call_back_;
	Callable call_back_;
	std::atomic<bool> is_stopped{true};
	std::mutex mtx;
	std::condition_variable cv;
};