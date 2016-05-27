 ///
 /// @file    condition.cc
 /// @author  chenchao(anqing_chao@163.com)
 /// @date    2016-05-19 20:47:30
 ///
 
#include "condition.h"
#include "mutex_lock.h"

namespace ccspace {

Condition::Condition(MutexLock& mutex)
	: mutex_(mutex) {
	pthread_cond_init(&cond_,NULL);
}

Condition::~Condition() {
	pthread_cond_destroy(&cond_);
}

void Condition::Wait() {
	pthread_cond_wait(&cond_,mutex_.GetMutexPtr());
}

void Condition::Notify() {
	pthread_cond_signal(&cond_);
}

void Condition::Notifyall() {
	pthread_cond_broadcast(&cond_);
}

}  //namespace ccspace
