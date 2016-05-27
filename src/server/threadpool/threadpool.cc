 ///
 /// @file    threadpool.cc
 /// @author  chenchao(anqing_chao@163.com)
 /// @date    2016-05-19 23:18:36
 ///
 
#include "threadpool.h"
#include "thread.h"
#include <unistd.h>
#include <iostream>
using std::cout;
using std::endl;

namespace ccspace {
	
Threadpool::Threadpool(int threads_number,int buff_size,MyConf& conf)
	: threads_number_(threads_number),
	  buff_size_(buff_size),
	  buff_(buff_size_),
	  is_exited_(false),
	  conf_(conf) {
	vec_threads_.reserve(threads_number_);	  
}

Threadpool::~Threadpool() {
	if(!is_exited_){
		Stop();
	}
}

void Threadpool::Stop() {
	if(!is_exited_){
		while(!buff_.Empty()){
			sleep(1);
		}
		is_exited_=true;
		buff_.WakeupEmpty();
		for(auto & p_thread : vec_threads_){
			p_thread->Join();
			delete p_thread;
		}
	}
}

void Threadpool::Start() {
	ReadCache();

	for(int idx=0;idx!=threads_number_;++idx){
		Thread* p_thread=new Thread(
				std::bind(&Threadpool::ThreadFunc,this,std::placeholders::_1),
				cache_);
		vec_threads_.push_back(p_thread);
	}
	for(auto & p_thread : vec_threads_){
		p_thread->Start();
	}
}

void Threadpool::ThreadFunc(Cache& cache) {
	while(!is_exited_){
		Task task=GetTask();
		if(task){
			task(cache);
		}
	}
}

void Threadpool::AddTask(Task task) {
	buff_.Push(task);
}
//要加Threadpool:: 否则Task报错无此类型
Threadpool::Task Threadpool::GetTask() {
	return buff_.Pop();
}

void Threadpool::ReadCache() {
	cache_.ReadFromFile(conf_.GetMyCache());
}

void Threadpool::UpdateCache() {
	cout<<"timer executing,update Caches"<<endl;
	for(int idx=0;idx!=threads_number_;++idx){
		cache_.Update(vec_threads_[idx]->GetCache());
	}
	for(int idx=0;idx!=threads_number_;++idx){
		vec_threads_[idx]->GetCache().Update(cache_);
	}
	cache_.WriteToFile(conf_.GetMyCache());
	cout<<"write to cache file"<<endl;
}

}  //namespace ccspace
