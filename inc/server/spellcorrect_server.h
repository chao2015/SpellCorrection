 ///
 /// @file    spellcorrect_server.h
 /// @author  chenchao(anqing_chao@163.com)
 /// @date    2016-05-20 09:56:28
 ///

#ifndef __MY_SPELLCORRECTSERVER_H__
#define __MY_SPELLCORRECTSERVER_H__

#include "myconf.h"
#include "tcp_server.h"
#include "threadpool.h"
#include "timer_thread.h"

namespace ccspace {

class SpellcorrectServer {
 public:
	SpellcorrectServer(const string& config_filename);
	void Start();
	void OnConnection(TcpConnectionPtr conn_ptr);
	void OnMessage(TcpConnectionPtr conn_ptr);
	void OnClose(TcpConnectionPtr conn_ptr);
 private:
	MyConf config_;
	TcpServer tcp_server_;
	Threadpool threadpool_;
	TimerThread timer_;
};

}  //namespace ccspace

#endif
