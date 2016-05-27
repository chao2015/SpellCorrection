 ///
 /// @file    timer.cc
 /// @author  chenchao(anqing_chao@163.com)
 /// @date    2016-05-15 11:44:34
 ///
 
#include "timer.h"
#include <errno.h>
#include <poll.h>
#include <stdio.h>
#include <sys/timerfd.h>
#include <unistd.h>
#include <iostream>
using std::cout;
using std::endl;

int CreateTimerFd() {
	int fd=::timerfd_create(CLOCK_REALTIME,0);
	if(-1==fd) {
		perror("timerfd_create error");
	}
	return fd;
}

void SetTimerfd(int timerfd,int initial_time,int interval_time) {
	struct itimerspec new_time;
	new_time.it_value.tv_sec=initial_time;
	new_time.it_value.tv_nsec=0;
	new_time.it_interval.tv_sec=interval_time;
	new_time.it_interval.tv_nsec=0;
	int ret=::timerfd_settime(timerfd,0,&new_time,NULL);
	if(-1==ret) {
		perror("timerfd_settime error");
	}
}

void StopTimerfd(int timerfd) {
	SetTimerfd(timerfd,0,0);
}

int ReadTimerfd(int timerfd) {
	uint64_t howmany;
	int ret=read(timerfd,&howmany,sizeof(uint64_t));
	if(ret!=sizeof(uint64_t)){
		perror("read error");
	}
	return ret;
}

namespace ccspace {

Timer::Timer(int initial_time,int interval_time,TimerCallback callback)
	: timerfd_(CreateTimerFd()),
	  initial_time_(initial_time),
	  interval_time_(interval_time),
	  is_started_(false),
	  callback_(callback) {
}

Timer::~Timer() {
	if(is_started_){
		Stop();
	}
}

void Timer::Start() {
	SetTimerfd(timerfd_,initial_time_,interval_time_);
	is_started_=true;

	struct pollfd pollfd;
	pollfd.fd=timerfd_;
	pollfd.events=POLLIN;  //there is data to read

	while(is_started_){
		int ret=::poll(&pollfd,1,5000); 
		if(-1==ret){
			if(errno==EINTR)
				continue;
			exit(EXIT_FAILURE);
		}else if(0==ret){
			cout<<"poll timeout"<<endl;
		}else{
			if(pollfd.revents & POLLIN){
				ReadTimerfd(timerfd_);
				if(callback_){
					callback_();  //处理任务
				}
			}
		}
	}
}

void Timer::Stop() {
	if(is_started_){
		::StopTimerfd(timerfd_);
		is_started_=false;
	}
}
}  //namespace ccspace
