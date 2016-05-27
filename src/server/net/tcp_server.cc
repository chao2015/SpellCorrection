 ///
 /// @file    tcp_server.cc
 /// @author  chenchao(anqing_chao@163.com)
 /// @date    2016-05-19 10:11:27
 ///
 
#include "tcp_server.h"

namespace ccspace {

TcpServer::TcpServer(unsigned short port)
	: socket_(),
	  epoll_(socket_.Fd()) {
	InetAddress addr(port);
	socket_.Ready(addr);
}

TcpServer::TcpServer(const string& ip,unsigned short port)
	: socket_(),
	  epoll_(socket_.Fd()) {
	InetAddress addr(ip,port);
	socket_.Ready(addr);
}

void TcpServer::Start() {
	epoll_.SetConnectionCallback(on_connection_);
	epoll_.SetMessageCallback(on_message_);
	epoll_.SetCloseCallback(on_close_);
	epoll_.Loop();
}

void TcpServer::Stop() {
	epoll_.Unloop();
}

void TcpServer::SetConnectionCallback(TcpServerCallback callback) {
	on_connection_=callback;
}

void TcpServer::SetMessageCallback(TcpServerCallback callback) {
	on_message_=callback;
}

void TcpServer::SetCloseCallback(TcpServerCallback callback) {
	on_close_=callback;
}

}  //namespace ccspace
