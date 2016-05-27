 ///
 /// @file    thread.cc
 /// @author  chenchao(anqing_chao@163.com)
 /// @date    2016-05-14 15:55:59
 ///

#include "timer_mythread.h"

namespace ccspace {

TimerMyThread::TimerMyThread(TimerMyThreadCallback callback)
	: thread_id_(0),
	  is_running_(false), 
	  callback_(callback) {
}

TimerMyThread::~TimerMyThread() {
	if(is_running_){
		pthread_detach(thread_id_);
	}
	is_running_=false;
}

void TimerMyThread::Start() {
	pthread_create(&thread_id_,NULL,TimerMyThreadFunc,this);
	is_running_=true;
}

void TimerMyThread::Join() {
	pthread_join(thread_id_,NULL);
	is_running_=false;
}
#if 0
void TimerMyThread::setTimerMyThreadCallback(TimerMyThreadCallback callback) {
	callback_=callback;
}
#endif
void* TimerMyThread::TimerMyThreadFunc(void* arg) {
	TimerMyThread* pTimerMyThread=static_cast<TimerMyThread*>(arg);
	if(pTimerMyThread){
		pTimerMyThread->callback_();  //执行回调函数，在class Product和class Consume中实现回调函数
	}
}

}  //namespace ccspace
