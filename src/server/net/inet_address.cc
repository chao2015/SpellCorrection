 ///
 /// @file    inet_address.cc
 /// @author  chenchao(anqing_chao@163.com)
 /// @date    2016-05-16 21:59:25
 ///
 
#include "inet_address.h"
#include <arpa/inet.h>
#include <string.h>
#include <sys/socket.h>
#include <iostream>
using std::cout;
using std::endl;

namespace ccspace {

InetAddress::InetAddress(unsigned short port) {
	memset(&addr_,0,sizeof(addr_));
	addr_.sin_family=AF_INET;
	addr_.sin_port=htons(port);
	addr_.sin_addr.s_addr=INADDR_ANY;  //设置为主机地址
}

InetAddress::InetAddress(const string& ip,unsigned short port) {
	memset(&addr_,0,sizeof(addr_));
	addr_.sin_family=AF_INET;
	addr_.sin_port=htons(port);
	addr_.sin_addr.s_addr=inet_addr(ip.c_str());
}

InetAddress::InetAddress(const struct sockaddr_in& addr)
	:addr_(addr) {
}

const struct sockaddr_in* InetAddress::GetInetAddressPtr() const {
	return &addr_;
}

string InetAddress::Ip() const {
	return inet_ntoa(addr_.sin_addr);
}

unsigned short InetAddress::Port() const {
	return ntohs(addr_.sin_port);
}

}  //namespace ccspace
