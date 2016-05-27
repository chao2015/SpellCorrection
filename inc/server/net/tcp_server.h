 ///
 /// @file    tcp_server.h
 /// @author  chenchao(anqing_chao@163.com)
 /// @date    2016-05-19 10:06:47
 ///

#ifndef __MY_TCPSERVER_H__
#define __MY_TCPSERVER_H__

#include "noncopyable.h"
#include "socket.h"
#include "epoll_poller.h"

namespace ccspace {

class TcpServer : Noncopyable {
 public:
	typedef EpollPoller::EpollPollerCallback TcpServerCallback;
	TcpServer(unsigned short port);
	TcpServer(const string& ip,unsigned short port);
	void Start();
	void Stop();
	void SetConnectionCallback(TcpServerCallback callback);
	void SetMessageCallback(TcpServerCallback callback);
	void SetCloseCallback(TcpServerCallback callback);
 private:
	Socket socket_;
	EpollPoller epoll_;
	TcpServerCallback on_connection_;
	TcpServerCallback on_message_;
	TcpServerCallback on_close_;
};

}  //namespace ccspace

#endif
