#include "timer_manager.h"
#include <algorithm>
#include <functional>
#include <memory>
#include <utility>

void TimerManager::Stop() {
    for(auto& item : timer_container_){
        item.second->Stop();
    }
    timer_container_.clear();
    for(auto& var : thread_container){
        if(var.second.joinable()){
            var.second.join();
        }
    }
    thread_container.clear();
    std::cout <<"[Manager] stop all timer!\n";
}


bool TimerManager::Arm(TimerId timer_id, Duration duration){
    std::cout <<"[Manager] Arm for timerId:" << static_cast<int>(timer_id) << "\n";
    bool result{false};
    auto iterator = timer_container_.find(timer_id);
    if(iterator != timer_container_.end()){ 
        thread_container[timer_id] = std::thread{&TimerHandler::Arm, iterator->second, duration};
    }
    return result;
}

bool TimerManager::Disarm(TimerId timer_id){
    bool result{false};
    auto iterator = timer_container_.find(timer_id);
    auto thread_it = thread_container.find(timer_id);

    if(iterator != timer_container_.end() && thread_it != thread_container.end()){
        iterator->second->Disarm();
        if(thread_it->second.joinable()){
            thread_it->second.join();
        }
        result = true;
    }
    return result;
}

bool TimerManager::SetUpTimer(TimerId timer_id, Callable call_back){
    std::cout << "[Manager] SetUp timer for timerId:" << timer_id << "\n";
    bool result{false};
    auto iterator = timer_container_.find(timer_id);
    if(iterator != timer_container_.end()){
        std::cout << "[Manager] Timer already active timerId:" << timer_id << "\n";
    }
    else{
        result = true;
        TimerHandler::OnMessage on_message = std::bind(&TimerManager::TimeHandling,this,std::placeholders::_1,std::placeholders::_2);
        timer_container_[timer_id] = std::make_shared<TimerHandler>(timer_id,on_message,call_back);
    }
    return result;
}   


void TimerManager::TimeHandling(TimerId timer_id, bool is_stopped){
    auto iterator = timer_container_.find(timer_id);
    if(iterator != timer_container_.end() && !is_stopped){
        iterator->second->GetCallBack()();
     }
}
