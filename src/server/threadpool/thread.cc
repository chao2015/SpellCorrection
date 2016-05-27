 ///
 /// @file    thread.cc
 /// @author  chenchao(anqing_chao@163.com)
 /// @date    2016-05-19 23:01:30
 ///
 
#include "thread.h"

namespace ccspace {

Thread::Thread(ThreadCallback callback,Cache & cache) 
	: pthread_id_(0),
	  is_running_(false),
	  callback_(callback),
	  cache_(cache){
}

Thread::~Thread() {
	if(is_running_){
		is_running_=false;
		pthread_detach(pthread_id_);
	}
}

void Thread::Start() {
	pthread_create(&pthread_id_,NULL,&Thread::ThreadFunc,this);
	is_running_=true;
}

void Thread::Join() {
	if(is_running_){
		pthread_join(pthread_id_,NULL);
		is_running_=false;
	}
}

Cache& Thread::GetCache() {
	return cache_;
}

void* Thread::ThreadFunc(void* arg) {
	Thread* p_thread=static_cast<Thread*>(arg);
	if(p_thread){
		p_thread->callback_(p_thread->cache_);
	}
}

}  //namespace ccspace
