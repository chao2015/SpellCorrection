 ///
 /// @file    test_threadpool.cc
 /// @author  chenchao(anqing_chao@163.com)
 /// @date    2016-05-19 23:56:14
 ///

#ifndef __MY_MYTASK_H__
#define __MY_MYTASK_H__

#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <iostream>
#include <queue>
#include <string>
#include <vector>
#include <set>
using std::cout;
using std::endl;
using std::string;
using std::priority_queue;
using std::vector;
using std::set;

namespace ccspace {

struct MyResult {
	string word_;
	int frequency_;
	int distance_;
};

struct MyCompare {
	bool operator()(const MyResult& lhs,const MyResult& rhs) {
		if(lhs.distance_>rhs.distance_){
			return true;
		}else if(lhs.distance_==rhs.distance_ &&
				 lhs.frequency_<rhs.frequency_){
			return true;
		}else if(lhs.distance_==rhs.distance_ &&
				 lhs.frequency_==rhs.frequency_ &&
				 lhs.word_>rhs.word_){
			return true;
		}else{
			return false;
		}
	}
};

class Cache;

class MyTask {
 public:
	MyTask(const string& query_word,int peerfd);
	void Execute(Cache& cache);  //执行查询
	void QueryIndexTable();  //查询索引
	void Statistic(set<int>& iset);  //进行计算
	int Distance(const string& rhs);  //计算最小编辑距离
	void Response(Cache& cache);  //响应客户端的请求
 private:
	string query_word_;  //等待查询的单词
	int peerfd_;  //与客户端进行连接的fd
	priority_queue<MyResult,vector<MyResult>,MyCompare> result_que_;  //保存候选结果的优先级队列
};

}  //namespace ccspace

#endif
