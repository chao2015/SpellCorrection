 ///
 /// @file    time.h
 /// @author  chenchao(anqing_chao@163.com)
 /// @date    2016-05-15 11:31:38
 ///
 
#ifndef __MY_TIMER_H__
#define __MY_TIMER_H__

#include "noncopyable.h"
#include <functional>

namespace ccspace {

class Timer : Noncopyable {
 public:
	typedef std::function<void()> TimerCallback;  //在TimerThread中用到，必须放在public区
	Timer(int initial_time,
		  int interval_time,
		  TimerCallback callback);
	~Timer();

	void Start();
	void Stop();
 private:
	int timerfd_;
	int initial_time_;
	int interval_time_;
	bool is_started_;
	TimerCallback callback_;
};

}  //namespace ccspace

#endif
