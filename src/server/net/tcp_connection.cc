 ///
 /// @file    tcp_connection.cc
 /// @author  chenchao(anqing_chao@163.com)
 /// @date    2016-05-19 00:13:49
 ///
 
#include "tcp_connection.h"
#include <iostream>
#include <sstream>
#include <string.h>

namespace ccspace {

TcpConnection::TcpConnection(int fd)
	: socket_(fd),
	  socket_io_(fd),
	  local_addr_(Socket::GetLocalAddr(fd)),
	  peer_addr_(Socket::GetPeerAddr(fd)),
	  is_shutdown_write_(false) {
}

TcpConnection::~TcpConnection() {
	if(!is_shutdown_write_){
		Shutdown();
	}
}

void TcpConnection::Shutdown() {
	if(!is_shutdown_write_){
		is_shutdown_write_=true;
		socket_.ShutdownWrite(); 
	}
}

std::string TcpConnection::Receive() {
	char buff[1024];
	memset(buff,0,sizeof(buff));
	socket_io_.ReadLine(buff,1024);
	return std::string(buff);
}

void TcpConnection::Send(const std::string& msg) {
	socket_io_.WriteN(msg.c_str(),msg.size());
}

std::string TcpConnection::ToString() const {
	std::ostringstream oss;
	oss<<local_addr_.Ip()<<":"<<local_addr_.Port()
		<<"--->"
		<<peer_addr_.Ip()<<":"<<peer_addr_.Port()<<" ";
	return oss.str();
}

void TcpConnection::SetConnectionCallback(TcpConnectionCallback callback) {
	on_connection_callback_=callback;
}

void TcpConnection::SetMessageCallback(TcpConnectionCallback callback) {
	on_message_callback_=callback;
}

void TcpConnection::SetCloseCallback(TcpConnectionCallback callback) {
	on_close_callback_=callback;
}

void TcpConnection::HandleConnectionCallback() {
	if(on_connection_callback_)
		on_connection_callback_(shared_from_this());
}

void TcpConnection::HandleMessageCallback() {
	if(on_message_callback_)
		on_message_callback_(shared_from_this());
}

void TcpConnection::HandleCloseCallback() {
	if(on_close_callback_)
		on_close_callback_(shared_from_this());
}

int TcpConnection::Fd() {
	return socket_.Fd();
}

}  //namespace ccspace
