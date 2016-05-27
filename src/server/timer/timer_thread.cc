 ///
 /// @file    timer_thread.cc
 /// @author  chenchao(anqing_chao@163.com)
 /// @date    2016-05-15 13:31:47
 ///
 
#include "timer_thread.h"
#include <iostream>
using std::cout;
using std::endl;

namespace ccspace {

TimerThread::TimerThread(int initial_time,
						 int interval_time,
						 TimerThreadCallback callback)
	: timer_(initial_time,interval_time,callback),
	  thread_(std::bind(&Timer::Start,&timer_)) {
}

void TimerThread::Start() {
	thread_.Start();
}

void TimerThread::Stop() {
	timer_.Stop();
	thread_.Join();
}

}  //namespace ccspace
