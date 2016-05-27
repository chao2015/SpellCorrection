 ///
 /// @file    mutex_lock.h
 /// @author  chenchao(anqing_chao@163.com)
 /// @date    2016-05-19 20:30:44
 ///

#ifndef __MY_MUTEXLOCK_H__
#define __MY_MUTEXLOCK_H__
#include "noncopyable.h"
#include <pthread.h>

namespace ccspace {

class MutexLock : Noncopyable {
 public:
	MutexLock();
	~MutexLock();
	void Lock();
	void Unlock();
	pthread_mutex_t* GetMutexPtr();
 private:
	pthread_mutex_t mutex_;
	bool is_locked_;
};

}  //namespace ccspace

#endif
