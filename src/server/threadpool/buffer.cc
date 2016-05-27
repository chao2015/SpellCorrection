 ///
 /// @file    buffer.cc
 /// @author  chenchao(anqing_chao@163.com)
 /// @date    2016-05-19 21:53:34
 ///
 
#include "buffer.h"

namespace ccspace {

Buffer::Buffer(int size)
	: mutex_(),
	  not_empty_(mutex_),
	  not_full_(mutex_),
	  que_size_(size),
	  empty_flag_(true) {
}

bool Buffer::Empty() {
	return que_.empty();
}

bool Buffer::Full() {
	return que_.size()==que_size_;
}

void Buffer::WakeupEmpty() {
	empty_flag_=false;
	not_empty_.Notifyall();
}

void Buffer::Push(Task task) {
	mutex_.Lock();
	while(Full()){
		not_full_.Wait();
	}
	que_.push(task);
	not_empty_.Notify();
	mutex_.Unlock();
}

Buffer::Task Buffer::Pop() {
	mutex_.Lock();
	while(empty_flag_ && Empty()){
		not_empty_.Wait();
	}
	if(empty_flag_){
		Task task=que_.front();
		que_.pop();
		not_full_.Notify();
		mutex_.Unlock();
		return task;
	}else{
		mutex_.Unlock();
		return NULL;
	}
}

}  //namespace ccspace
