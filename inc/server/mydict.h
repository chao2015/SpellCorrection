 ///
 /// @file    mydict.h
 /// @author  chenchao(anqing_chao@163.com)
 /// @date    2016-05-22 14:39:14
 ///

#ifndef __MY_MYDICT_H__
#define __MY_MYDICT_H__

#include <string>
#include <vector>
#include <set>
#include <utility>
#include <map>
using std::vector;
using std::map;
using std::set;
using std::pair;
using std::string;

namespace ccspace {

class MyDict {
 public:
	static MyDict* createInstance();
	void Init(const char* en_dictpath,const char* cn_dictpath);
	void ShowDict();
	void ShowIndex();
	vector<pair<string,int> >& GetDict();
	map<string,set<int> >& GetIndex();
 private:
	MyDict();
	void ReadFrom(const char* dictpath);
	void RecordToIndex(int idx);
 private:
	static MyDict* pInstance;
	vector<pair<string,int> > dict_;
	map<string,set<int> > index_;
};

}  //namespace ccspace

#endif
