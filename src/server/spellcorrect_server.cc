 ///
 /// @file    spellcorrect_server.cc
 /// @author  chenchao(anqing_chao@163.com)
 /// @date    2016-05-20 10:15:09
 ///
 
#include "spellcorrect_server.h"
#include "mytask.h"
#include "mydict.h"
#include <iostream>
using std::cout;
using std::endl;

namespace ccspace {

SpellcorrectServer::SpellcorrectServer(const string& config_filename) 
	: config_(config_filename),
	  tcp_server_(config_.GetMyIp(),config_.GetMyPort()),
	  threadpool_(4,1000,config_), 
	  timer_(4,10,std::bind(&Threadpool::UpdateCache,&threadpool_)){
	MyDict* p_dict=MyDict::createInstance();
	p_dict->Init(config_.GetMyEnDict().c_str(),config_.GetMyCnDict().c_str());
	//p_dict->ShowIndex();
}

void SpellcorrectServer::Start() {
	threadpool_.Start();
	timer_.Start();
	using std::placeholders::_1;
	//参数是TcpServerCallback,也是std::function<void(TcpConnectionPtr)>类型的函数,只能有一个参数,成员函数默认都有this参数
	//_1:保留下次调用时的第一个参数。例如f(1,2,3)中只会保留第1个参数传递给bind过的函数。
	tcp_server_.SetConnectionCallback(std::bind(&SpellcorrectServer::OnConnection,this,_1));  //消除默认this指针对参数列表的影响
	tcp_server_.SetMessageCallback(std::bind(&SpellcorrectServer::OnMessage,this,_1));
	tcp_server_.SetCloseCallback(std::bind(&SpellcorrectServer::OnClose,this,_1));
	tcp_server_.Start();
}

void SpellcorrectServer::OnConnection(TcpConnectionPtr conn_ptr) {
	cout<<conn_ptr->ToString()<<"has connected!"<<endl;
	conn_ptr->Send("welcome to server.");
}

void SpellcorrectServer::OnMessage(TcpConnectionPtr conn_ptr) {
	std::string msg=conn_ptr->Receive();
	cout<<msg<<endl;
	//conn_ptr->Send(msg);
	int pos=msg.find('\n');
	string data=msg.substr(0,pos);
	cout<<data<<endl;
	cout<<"data's size="<<data.size()<<endl;
	MyTask task(data,conn_ptr->Fd());
	threadpool_.AddTask(std::bind(&MyTask::Execute,task,std::placeholders::_1));

}

void SpellcorrectServer::OnClose(TcpConnectionPtr conn_ptr) {
	cout<<conn_ptr->ToString()<<"has closed."<<endl;
}

}  //namespace ccspace
