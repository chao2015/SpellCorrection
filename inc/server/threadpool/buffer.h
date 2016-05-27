 ///
 /// @file    buffer.h
 /// @author  chenchao(anqing_chao@163.com)
 /// @date    2016-05-19 21:40:51
 ///

#ifndef __MY_BUFFER_H__
#define __MY_BUFFER_H__

#include "mutex_lock.h"
#include "condition.h"
#include <queue>
#include <functional>
using std::queue;

namespace ccspace {

class Cache;

class Buffer {
 public:
	typedef std::function<void(Cache&)> Task;
	Buffer(int size);
	void Push(Task task);
	Task Pop();
	void WakeupEmpty();
	bool Empty();
	bool Full();
 private:
	MutexLock mutex_;
	Condition not_empty_;
	Condition not_full_;
	queue<Task> que_;
	int que_size_;
	bool empty_flag_;
};

}  //namespace ccspace

#endif
