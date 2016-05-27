 ///
 /// @file    tcp_connection.h
 /// @author  chenchao(anqing_chao@163.com)
 /// @date    2016-05-18 23:58:01
 ///

#ifndef _MY_TCPCONNECTION_H__
#define _MY_TCPCONNECTION_H__

#include "noncopyable.h"
#include "socket.h"
#include "socket_io.h"
#include "inet_address.h"
#include <functional>
#include <memory>
#include <string>

namespace ccspace {

class TcpConnection;
typedef std::shared_ptr<TcpConnection> TcpConnectionPtr;

class TcpConnection 
	: Noncopyable, 
	  public std::enable_shared_from_this<TcpConnection> {
 public:
	typedef std::function<void(TcpConnectionPtr)> TcpConnectionCallback;
	TcpConnection(int fd);
	~TcpConnection();

	std::string Receive();
	void Send(const std::string& msg);
	void Shutdown();
	std::string ToString() const;
	void HandleConnectionCallback();
	void HandleMessageCallback();
	void HandleCloseCallback();
	void SetConnectionCallback(TcpConnectionCallback callback);
	void SetMessageCallback(TcpConnectionCallback callback);
	void SetCloseCallback(TcpConnectionCallback callback);
	int Fd();
 private:
	Socket socket_;
	SocketIO socket_io_;
	const InetAddress local_addr_;
	const InetAddress peer_addr_;
	bool is_shutdown_write_;
	TcpConnectionCallback on_connection_callback_;
	TcpConnectionCallback on_message_callback_;
	TcpConnectionCallback on_close_callback_;
};

}  //namespace ccspace

#endif
