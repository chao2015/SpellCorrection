 ///
 /// @file    mytask.cc
 /// @author  chenchao(anqing_chao@163.com)
 /// @date    2016-05-21 10:22:22
 ///
 
#include "mytask.h"
#include "cache.h"
#include "mydict.h"

namespace ccspace {

int tripleMin(const int & a, const int & b, const int & c)
{
	return a < b ? (a < c ? a : c) : (b < c ? b : c);
}

size_t nBytesCode(const char ch)
{
	size_t nBytes = 0;
	if(ch &(1 << 7))
	{//对中文进行处理-utf8编码
		if((ch & 0xF0) == 0xC0 || (ch & 0xF0) == 0xD0)   //  1111 0000
		{												 // &11xx xxxx
			nBytes += 2;								 //  1100 0000	
		}												 //  1101 0000
		else if((ch & 0xF0) == 0xE0)
		{
			nBytes += 3;
		}
		else if((ch & 0xFF) == 0xF0 ||
				(ch & 0xFF) == 0xF1 ||
				(ch & 0xFF) == 0xF2 ||
				(ch & 0xFF) == 0xF3 ||
				(ch & 0xFF) == 0xF4 ||
				(ch & 0xFF) == 0xF5 ||
				(ch & 0xFF) == 0xF6 ||
				(ch & 0xFF) == 0xF7 )
		{
			nBytes += 4;
		}
		else if((ch & 0xFF) == 0xF8 ||
				(ch & 0xFF) == 0xF9 ||
				(ch & 0xFF) == 0xFA ||
				(ch & 0xFF) == 0xFB) 
		{
			nBytes += 5;
		}
		else if((ch & 0xFF) == 0xFC)
		{
			nBytes += 6;
		}
	}
	else
	{//1字节编码或英文
		nBytes += 1;	
	}
	return nBytes;
}

std::size_t length(const std::string &str)
{
	std::size_t ilen = 0;
	for(std::size_t idx = 0; idx != str.size(); ++idx)
	{
		int nBytes = nBytesCode(str[idx]);
		idx += (nBytes - 1);
		++ilen;
	}
	return ilen;
}

int editDistance(const std::string & lhs, const std::string &rhs)
{//计算最小编辑距离-包括处理中英文
	size_t lhs_len = length(lhs);
	size_t rhs_len = length(rhs);
	int editDist[lhs_len + 1][rhs_len + 1];
	for(size_t idx = 0; idx <= lhs_len; ++idx)
	{
		editDist[idx][0] = idx;
	}

	for(size_t idx = 0; idx <= rhs_len; ++idx)
	{
		editDist[0][idx] = idx;
	}
	
	std::string sublhs, subrhs;
	for(std::size_t dist_i = 1, lhs_idx = 0; dist_i <= lhs_len; ++dist_i, ++lhs_idx)
	{
		size_t nBytes = nBytesCode(lhs[lhs_idx]);
		sublhs = lhs.substr(lhs_idx, nBytes);
		lhs_idx += (nBytes - 1);

		for(std::size_t dist_j = 1, rhs_idx = 0; dist_j <= rhs_len; ++dist_j, ++rhs_idx)
		{
			nBytes = nBytesCode(rhs[rhs_idx]);
			subrhs = rhs.substr(rhs_idx, nBytes);
			rhs_idx += (nBytes - 1);
			if(sublhs == subrhs)
			{
				editDist[dist_i][dist_j] = editDist[dist_i - 1][dist_j - 1];
			}
			else
			{
				editDist[dist_i][dist_j] = tripleMin(
					editDist[dist_i][dist_j - 1] + 1,
					editDist[dist_i - 1][dist_j] + 1,
					editDist[dist_i - 1][dist_j - 1] + 1);
			}
		}
	}
	return editDist[lhs_len][rhs_len];
}

int GetNextWordIndex(const string& word,int idx) {
	char ch=word[idx];
	if(ch & (1<<7)){  //存储utf-8编码的中文字符
		if((ch & 0xF0)==0xC0 || (ch & 0xF0)==0xD0)
			idx+=2;
		else if((ch & 0xF0) == 0xE0)
			idx+=3;
		else if((ch & 0xF0) == 0xF0)
			idx+=4;
		else if((ch & 0xFF) == 0xF8)
			idx+=5;
		else if((ch & 0xFF) == 0xFE)
			idx+=6;
	}else{
		idx+=1;
	}
	return idx;
}

MyTask::MyTask(const string& query_word,int peerfd)
	: query_word_(query_word),
	  peerfd_(peerfd) {	
}

void MyTask::Execute(Cache& cache) {
#if 0
	cout << "Task::execute()--->query " << query_word_ << endl;
	MyDict * pDict = MyDict::createInstance();
	auto myDict = pDict->get_dict();
	cout << myDict[0].first << "-->" << myDict[0].second << endl;
#endif 
	string result = cache.Query(query_word_);
	if(result != string()){
		::write(peerfd_, result.c_str(), result.size());
		cout << "response client" << endl;
		return;
	}

	QueryIndexTable();//查询索引表

	Response(cache);//给客户端返回结果
}

void MyTask::QueryIndexTable() {
	auto index_table = MyDict::createInstance()->GetIndex();
	string ch;
	int bytes;
	for(int idx = 0; idx < query_word_.size();(idx+=bytes-idx)){
		//ch = query_word_.substr(idx, 1);
		bytes=GetNextWordIndex(query_word_,idx);
		ch=query_word_.substr(idx,bytes-idx);
		if(index_table.count(ch)){
			cout << "indexTable has character " << ch << endl;
			Statistic(index_table[ch]);
		}
	}
}

void MyTask::Statistic(set<int>& iset) {
	auto dict = MyDict::createInstance()->GetDict();
	auto iter = iset.begin();
	for(; iter != iset.end(); ++iter){
		string rhsWord = dict[*iter].first;
		int idist = Distance(rhsWord);//进行最小编辑距离的计算
		if(idist < 3){
			MyResult res;
			res.word_ = rhsWord;
			res.frequency_ = dict[*iter].second;
			res.distance_ = idist;
			result_que_.push(res);
		}
	}
}

int MyTask::Distance(const string & rhsWord)
{
	return editDistance(query_word_, rhsWord);
}

void MyTask::Response(Cache& cache) {
	if(result_que_.empty()){
		string result = "no answer!";
		int nwrite = ::write(peerfd_, result.c_str(), result.size());
		if(-1 == nwrite){
			cout << "reponse error" << endl;
		}
	}else{
		//while(!result_que_.empty()){
			MyResult result = result_que_.top();
			int nwrite = ::write(peerfd_, result.word_.c_str(), result.word_.size());	
		//	::write(peerfd_, "\n", 1);
			if(-1 == nwrite){
				cout << "reponse error" << endl;
			}
			cache.AddElement(query_word_, result.word_);//更新缓存
			cout << "respone(): add Cache" << endl;
		//	result_que_.pop();
		//}
	}
	cout << "reponse client" << endl;
}

}  //namespace ccspace
