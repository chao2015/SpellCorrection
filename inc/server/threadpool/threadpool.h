 ///
 /// @file    threadpool.h
 /// @author  chenchao(anqing_chao@163.com)
 /// @date    2016-05-19 23:11:46
 ///
 
#ifndef __MY_THREADPOOL_H__
#define __MY_THREADPOOL_H__

#include "cache.h"
#include "buffer.h"
#include "myconf.h"
#include <functional>
#include <vector>
using std::vector;

namespace ccspace {

class Thread;

class Threadpool {
 public:
	typedef std::function<void(Cache&)> Task;
	Threadpool(int threads_number,int buff_size,MyConf& conf);
	~Threadpool();
	void Start();
	void Stop();
	void AddTask(Task task);
	Task GetTask();
	void ThreadFunc(Cache& cache);

	void ReadCache();
	void UpdateCache();
 private:
	int threads_number_;
	int buff_size_;
	vector<Thread*> vec_threads_;
	Buffer buff_;
	bool is_exited_;
	Cache cache_;
	MyConf& conf_;
};

}  //namespace ccspace

#endif
