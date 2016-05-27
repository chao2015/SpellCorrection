 ///
 /// @file    socket.h
 /// @author  chenchao(anqing_chao@163.com)
 /// @date    2016-05-16 22:14:10
 ///
 
#ifndef __MY_SOCKET_H__
#define __MY_SOCKET_H__

namespace ccspace {

class InetAddress;

class Socket {
 public:
	Socket();
	Socket(int fd);
	void Ready(const InetAddress& addr);
	int Accept();
	int Fd();
	void ShutdownWrite();
	static InetAddress GetLocalAddr(int fd);
	static InetAddress GetPeerAddr(int fd);
 private:
	void Bind(const InetAddress& addr);
	void Listen();
	void SetReuseAddr(bool on);
	void SetReusePort(bool on);
 private:
	int sockfd_;
};

}

#endif
