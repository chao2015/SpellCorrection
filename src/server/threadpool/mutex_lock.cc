 ///
 /// @file    mutex_lock.cc
 /// @author  chenchao(anqing_chao@163.com)
 /// @date    2016-05-19 20:37:22
 ///
 
#include "mutex_lock.h"

namespace ccspace {

MutexLock::MutexLock()
	: is_locked_(false) {
	pthread_mutex_init(&mutex_,NULL);
}

MutexLock::~MutexLock() {
	pthread_mutex_destroy(&mutex_);
}

void MutexLock::Lock() {
	pthread_mutex_lock(&mutex_);
	is_locked_=true;
}

void MutexLock::Unlock() {
	pthread_mutex_unlock(&mutex_);
	is_locked_=false;
}

pthread_mutex_t* MutexLock::GetMutexPtr() {
	return &mutex_;
}

}  //namespace ccspace
