 ///
 /// @file    inet_address.h
 /// @author  chenchao(anqing_chao@163.com)
 /// @date    2016-05-16 21:34:37
 ///

#ifndef __MY_INETADDR_H_
#define __MY_INETADDR_H_
#include <netinet/in.h>  //struct sockaddr_in
#include <string>
using std::string;

namespace ccspace {

class InetAddress {  //copyable
 public:
	InetAddress(unsigned short port);
	InetAddress(const string& ip,unsigned short port);
	InetAddress(const struct sockaddr_in& addr);
	string Ip() const;
	unsigned short Port() const;
	const struct sockaddr_in* GetInetAddressPtr() const;
 private:
	struct sockaddr_in addr_;
};

}  //namespace ccspace

#endif
