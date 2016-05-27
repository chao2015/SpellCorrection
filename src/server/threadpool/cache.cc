 ///
 /// @file    cache.cc
 /// @author  chenchao(anqing_chao@163.com)
 /// @date    2016-05-21 09:43:11
 ///
 
#include "cache.h"
#include <iostream>
#include <fstream>
using std::cout;
using std::endl;
using std::ifstream;
using std::ofstream;

namespace ccspace {

ifstream& OpenFile(ifstream& in,const string& file) {
	in.close();
	in.clear();
	in.open(file.c_str());
	return in;
}
Cache::Cache(int num)
    : hash_map_(num) {
	//WriteToFile();
}

Cache::Cache(const Cache& rhs)
    : hash_map_(rhs.hash_map_) {
	//WriteToFile();
}

void Cache::AddElement(const string& key,const string& value) {
	if(hash_map_.count(key))
		hash_map_[key] = value;
	else
		hash_map_.insert(std::pair<string,string>(key,value));
}

string Cache::Query(const string & word) {
	auto iter = hash_map_.find(word);
	if(iter != hash_map_.end()){
		return iter->second;
	}else{
		return string();
	}
}

void Cache::ReadFromFile(const string& filename) {
	ifstream ifs;
	if(!OpenFile(ifs,filename)){
		cout << "open cache file error!" << endl;
		return;
	}
	string key, value;
	while(ifs >> key >> value){
		hash_map_.insert(std::make_pair(key, value));
		cout << key << " " << value << endl;
	}
}

void Cache::WriteToFile(const string& filename) {
	ofstream ofs(filename.c_str());
	if(!ofs.good()){
		cout << "ofstream:write cache file error" << endl;
		return ;
	}
	auto iter = hash_map_.begin();
	for(; iter != hash_map_.end(); ++iter){
		ofs << iter->first << "\t" << iter->second << endl;
	}
}

void Cache::Update(const Cache& rhs) {
	auto iter = rhs.hash_map_.begin();
	for(; iter != rhs.hash_map_.end(); ++iter){
		hash_map_.insert(*iter);
	}
}

}  //namespace ccspace
