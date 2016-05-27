 ///
 /// @file    epoll.h
 /// @author  chenchao(anqing_chao@163.com)
 /// @date    2016-05-19 00:49:14
 ///

#ifndef __MY_EPOLLPOLLER_H__
#define __MY_EPOLLPOLLER_H__

#include "noncopyable.h"
#include "tcp_connection.h"
#include <sys/epoll.h>
#include <vector>
#include <map>
#include <functional>
using std::vector;
using std::map;

namespace ccspace {

class EpollPoller : Noncopyable {
 public:
	typedef std::function<void(TcpConnectionPtr)> EpollPollerCallback;
	EpollPoller(int listenfd);
	~EpollPoller();
	void Loop();
	void Unloop();
	void SetConnectionCallback(EpollPollerCallback callback);
	void SetMessageCallback(EpollPollerCallback callback);
	void SetCloseCallback(EpollPollerCallback callback);
 private:
	void WaitEpollfd();
	void HandleConnection();
	void HandleMessage(int fd);
 private:
	int epollfd_;
	int listenfd_;
	bool is_looping_;
	vector<struct epoll_event> event_list_;
	map<int,TcpConnectionPtr> connection_map_;
	EpollPollerCallback on_connection_;
	EpollPollerCallback on_message_;
	EpollPollerCallback on_close_;
};


}  //namespace ccspace

#endif
