 ///
 /// @file    socket_io.h
 /// @author  chenchao(anqing_chao@163.com)
 /// @date    2016-05-16 20:07:07
 ///

#ifndef __MY_SOCKETIO_H__
#define __MY_SOCKETIO_H__

#include "noncopyable.h"
#include <unistd.h>

namespace ccspace {

class SocketIO : Noncopyable {
 public:
	SocketIO(int fd);
	int WriteN(const char* buff,int buff_size);
	int ReadN(char* buff,int buff_size);
	int ReadLine(char* buff,int buff_size);
 private:
	int RecvPeek(char* buff,int);
 private:
	int fd_;
};

}  //namespace ccspace

#endif
