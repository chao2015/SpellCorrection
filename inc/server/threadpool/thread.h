 ///
 /// @file    thread.h
 /// @author  chenchao(anqing_chao@163.com)
 /// @date    2016-05-19 22:54:00
 ///

#ifndef __MY_THREAD_H__
#define __MY_THREAD_H__

#include "noncopyable.h"
#include "cache.h"
#include <pthread.h>
#include <functional>

namespace ccspace {

class Thread : Noncopyable {
 public:
	typedef std::function<void(Cache&)> ThreadCallback;
	Thread(ThreadCallback callback,Cache& cache);
	~Thread();
	void Start();
	void Join();
	Cache& GetCache();
	void SetThreadCallBack(ThreadCallback callback);
	static void* ThreadFunc(void* arg);
 private:
	pthread_t pthread_id_;
	bool is_running_;
	ThreadCallback callback_;
	Cache cache_;
};

}  //namespace ccspace

#endif
