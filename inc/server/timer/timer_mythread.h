 ///
 /// @file    TimerMyThread.h
 /// @author  chenchao(anqing_chao@163.com)
 /// @date    2016-05-14 15:38:10
 ///

#ifndef __MY_THREAD_H__
#define __MY_THREAD_H__

#include "noncopyable.h"
#include <pthread.h>
#include <functional>

namespace ccspace {
//注意：1.std::function<void()>和头文件
class TimerMyThread : Noncopyable {
	typedef std::function<void()> TimerMyThreadCallback;

 public:
	TimerMyThread(TimerMyThreadCallback callback);
	~TimerMyThread();

	void Start();
	void Join();
	//void setTimerMyThreadCallback(TimerMyThreadCallback callback);
	static void* TimerMyThreadFunc(void* arg);

 private:
	pthread_t thread_id_;
	bool is_running_;
	TimerMyThreadCallback callback_;
};

}  //namespace ccspace

#endif
