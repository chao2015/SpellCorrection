 ///
 /// @file    timer_thread.h
 /// @author  chenchao(anqing_chao@163.com)
 /// @date    2016-05-15 13:27:27
 ///

#ifndef __MY_TIMER_THREAD_H__
#define __MY_TIMER_THREAD_H__

#include "timer.h"
#include "timer_mythread.h"

namespace ccspace {

class TimerThread {
	typedef Timer::TimerCallback TimerThreadCallback;
 public:
	TimerThread(int initial_time,
			    int interval_time,
				TimerThreadCallback callback);
	void Start();
	void Stop();
 private:
	Timer timer_;
	TimerMyThread thread_;
};

}  //namespace ccspace

#endif
