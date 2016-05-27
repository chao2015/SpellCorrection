 ///
 /// @file    socket.cc
 /// @author  chenchao(anqing_chao@163.com)
 /// @date    2016-05-16 22:20:46
 ///
 
#include "socket.h"
#include "inet_address.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <iostream>
using std::cout;
using std::endl;


int CreateSocketfd() {
	int fd=::socket(AF_INET,SOCK_STREAM,0);
	if(-1==fd){
		perror("socket");
	}
	return fd;
}

namespace ccspace {

Socket::Socket()
	:sockfd_(CreateSocketfd()) {
}

Socket::Socket(int fd)
	:sockfd_(fd) {
}

void Socket::Ready(const InetAddress& addr) {
	SetReuseAddr(true);
	SetReusePort(true);
	Bind(addr);
	Listen();
}

void Socket::SetReuseAddr(bool on) {
	int optval=on ? 1 : 0;
    //int setsockopt(int sockfd, int level, int optname,const void *optval, socklen_t optlen);
    //sockfd：标识一个套接口的描述字。
    //level：选项定义的层次；支持SOL_SOCKET、IPPROTO_TCP、IPPROTO_IP和IPPROTO_IPV6。
    //optname：需设置的选项。这里是地址复用和端口复用
    //optval：指针，指向存放选项待设置的新值的缓冲区。(存储1或者0，即true或false)
    //optlen：optval缓冲区长度。
	if(-1==::setsockopt(sockfd_,
						SOL_SOCKET,
						SO_REUSEADDR,
						&optval,
						static_cast<socklen_t>(sizeof(optval)))){
		perror("setsockopt reuse addr error");
	}
}

void Socket::SetReusePort(bool on) {
#ifdef SO_REUSEPORT
	int optval=on ? 1 : 0;
	if(-1==::setsockopt(sockfd_,
						SOL_SOCKET,
						SO_REUSEPORT,
						&optval,
						static_cast<socklen_t>(sizeof(optval)))){
		perror("setsockopt refuse addr error");
		close(sockfd_);
		exit(EXIT_FAILURE);
	}
#else
	if(on){
		perror("SO_REUSEPORT is not surpported!");
	}
#endif
}

void Socket::Bind(const InetAddress& addr) {
	if(-1==::bind(sockfd_,
				  (struct sockaddr*)addr.GetInetAddressPtr(),
				  sizeof(struct sockaddr))) {
		perror("bind error");
		close(sockfd_);
		exit(EXIT_FAILURE);
	}
}

void Socket::Listen() {
	if(-1==::listen(sockfd_,10)){
		perror("listen error");
		close(sockfd_);
		exit(EXIT_FAILURE);
	}
}

int Socket::Accept() {
	int peerfd=::accept(sockfd_,NULL,NULL);
	if(-1==peerfd){
		perror("accept");
		close(sockfd_);
	}
	return peerfd;
}

void Socket::ShutdownWrite() {
	if(-1==::shutdown(sockfd_,SHUT_WR)) {
		perror("shutdown write");
	}
}

InetAddress Socket::GetLocalAddr(int fd) {
	struct sockaddr_in local_addr;
	socklen_t len=sizeof(struct sockaddr_in);
    //参数1：标识一个已捆绑套接口的描述字。
    //参数2：接收套接口的地址（名字）。
    //参数3：名字缓冲区长度。
	if(-1==::getsockname(fd,(struct sockaddr*)&local_addr,&len)) {
		perror("getsockname");
	}
	return InetAddress(local_addr);
}

InetAddress Socket::GetPeerAddr(int fd) {
	struct sockaddr_in peer_addr;
	socklen_t len=sizeof(struct sockaddr_in);
	if(-1==::getpeername(fd,(struct sockaddr*)&peer_addr,&len)) {
		perror("getpeername");
	}
	return InetAddress(peer_addr);
}

int Socket::Fd() {
	return sockfd_;
}

}  //namespace ccspace
