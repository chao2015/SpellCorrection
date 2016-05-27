 ///
 /// @file    epoll_poller.cc
 /// @author  chenchao(anqing_chao@163.com)
 /// @date    2016-05-19 00:58:02
 ///
 
#include "epoll_poller.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <assert.h>

const int g_init_number=2048;

int CreateEpollFd() {
	int fd=::epoll_create1(0);
	if(-1==fd){
		perror("epoll_create1");
	}
	return fd;
}

void AddEpollfd(int epollfd,int acceptfd){
	struct epoll_event ev;
	ev.data.fd=acceptfd;
	ev.events=EPOLLIN;
	int ret=::epoll_ctl(epollfd,EPOLL_CTL_ADD,acceptfd,&ev);
	if(-1==ret){
		perror("epoll_ctl add");
		exit(EXIT_FAILURE);
	}
}

void DelEpollfd(int epollfd,int acceptfd){
	struct epoll_event ev;
	ev.data.fd=acceptfd;
	ev.events=EPOLLIN;
	int ret=::epoll_ctl(epollfd,EPOLL_CTL_DEL,acceptfd,&ev);
	if(-1==ret){
		perror("epoll_ctl del");
		exit(EXIT_FAILURE);
	}
}

int RecvPeek(int sockfd,char* buff,int count) {
	int nread;
	do{
		nread=::recv(sockfd,buff,count,MSG_PEEK);
	}while(-1==nread && errno==EINTR);
	return nread;
}

//判断连接是否已经断开
bool IsConnectionClose(int sockfd) {
	char buff[1024];
	int nread=RecvPeek(sockfd,buff,1024);
	if(-1==nread){
		perror("RecvPeek");
		exit(EXIT_FAILURE);
	}
	return (0==nread);
}

namespace ccspace {

EpollPoller::EpollPoller(int listenfd)
	: epollfd_(CreateEpollFd()),
	  listenfd_(listenfd),
	  is_looping_(false),
	  event_list_(g_init_number) {
	AddEpollfd(epollfd_,listenfd_);
}

EpollPoller::~EpollPoller() {
	::close(epollfd_);
}

void EpollPoller::Loop() {
	if(!is_looping_){
		is_looping_=true;
		while(is_looping_)
			WaitEpollfd();
	}
}

void EpollPoller::WaitEpollfd() {
	int nready;
	do{
		nready=epoll_wait(epollfd_,
						  &(*event_list_.begin()),
						  event_list_.size(),
						  5000);
	}while(nready==-1 && errno==EINTR);
	if(-1==nready){
		perror("epoll_wait");
		exit(EXIT_FAILURE);
	}else if(0==nready){
		printf("epoll_wait timeout!\n");
	}else{
		//扩大容量
		if(nready==static_cast<int>(event_list_.size())){
			event_list_.resize(nready*2);  //
		}
		for(int idx=0;idx!=nready;++idx){
			if(event_list_[idx].data.fd==listenfd_){
				//处理新连接
				if(event_list_[idx].events & EPOLLIN){
					HandleConnection();
				}
			}
			else{
				//处理旧连接
				if(event_list_[idx].events & EPOLLIN){
					HandleMessage(event_list_[idx].data.fd);
				}
			}
		}
	}
}

void EpollPoller::HandleConnection() {
	int peerfd=::accept(listenfd_,NULL,NULL);
	if(-1==peerfd){
		perror("accept");
		exit(EXIT_FAILURE);
	}
	//将新连接添加到epoll实例的监听列表中
	AddEpollfd(epollfd_,peerfd);
	TcpConnectionPtr pConnPtr(new TcpConnection(peerfd));
	pConnPtr->SetConnectionCallback(on_connection_);
	pConnPtr->SetMessageCallback(on_message_);
	pConnPtr->SetCloseCallback(on_close_);
	connection_map_[peerfd]=pConnPtr;
	//给客户端发一些信息 OnConnection();
	//pConnPtr->Send("welcome to server.");
	pConnPtr->HandleConnectionCallback();
}

void EpollPoller::HandleMessage(int fd) {
	bool is_closed=IsConnectionClose(fd);
	map<int,TcpConnectionPtr>::iterator it=connection_map_.find(fd);
	assert(it!=connection_map_.end());
	if(is_closed){
		//发现连接断开的操作
		it->second->HandleCloseCallback();
		DelEpollfd(epollfd_,fd);
		connection_map_.erase(it);
	}
	else{
		//如果是客户端发过来的数据
		it->second->HandleMessageCallback();
	}
}

void EpollPoller::Unloop() {
	if(is_looping_){
		is_looping_=false;
	}
}

void EpollPoller::SetConnectionCallback(EpollPollerCallback callback) {
	on_connection_=callback;
}

void EpollPoller::SetMessageCallback(EpollPollerCallback callback) {
	on_message_=callback;
}

void EpollPoller::SetCloseCallback(EpollPollerCallback callback) {
	on_close_=callback;
}

}  //namespace ccspace
