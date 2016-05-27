 ///
 /// @file    condition.h
 /// @author  chenchao(anqing_chao@163.com)
 /// @date    2016-05-19 20:44:05
 ///

#ifndef __MY_CONDITION_H__
#define __MY_CONDITION_H__
#include "noncopyable.h"
#include <pthread.h>

namespace ccspace {

class MutexLock;

class Condition : Noncopyable {
 public:
	Condition(MutexLock& mutex);
	~Condition();
	void Wait();
	void Notify();
	void Notifyall();
 private:
	pthread_cond_t cond_;
	MutexLock& mutex_;
};

}  //namespace ccspace

#endif
