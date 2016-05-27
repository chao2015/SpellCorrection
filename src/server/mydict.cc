 ///
 /// @file    mydict.cc
 /// @author  chenchao(anqing_chao@163.com)
 /// @date    2016-05-22 14:45:43
 ///
 
#include "mydict.h"
#include <iostream>
#include <fstream>
#include <sstream>

namespace ccspace {

MyDict* MyDict::pInstance=NULL;

MyDict* MyDict::createInstance() {
	if(NULL==pInstance){
		pInstance=new MyDict;
	}
	return pInstance;
}

vector<pair<string,int> >& MyDict::GetDict() {
	return dict_;
}

map<string,set<int> >& MyDict::GetIndex() {
	return index_;
}

void MyDict::ShowDict() {
	auto iter=dict_.begin();
	for(;iter!=dict_.end();++iter){
		std::cout<<iter->first<<"-->"
				 <<iter->second<<std::endl;
	}
}

void MyDict::ShowIndex() {
	auto iter=index_.begin();
	for(;iter!=index_.end();++iter){
		std::cout<<iter->first<<"-->";
		auto sit=iter->second.begin();
		for(;sit!=iter->second.end();++sit){
			std::cout<<*sit<<" ";
		}
		std::cout<<std::endl;
	}
}

void MyDict::ReadFrom(const char* dictpath) {
	std::ifstream in(dictpath);
	if(!in){
		std::cout<<__DATE__<<" "<<__TIME__
				 <<__FILE__<<" "<<__LINE__
				 <<":dict read error"<<std::endl;
		exit(-1);
	}
	std::string line;
	while(getline(in,line)){
		std::stringstream ss(line);
		std::string key;
		int value;
		ss>>key>>value;
		dict_.push_back(make_pair(key,value));
	}
	in.close();
}

//private:
MyDict::MyDict(){
}

void MyDict::Init(const char* en_dictpath,const char* cn_dictpath) {
	ReadFrom(en_dictpath);
	ReadFrom(cn_dictpath);
	for(size_t idx=0;idx!=dict_.size();++idx){
		RecordToIndex(idx);
	}
}

void MyDict::RecordToIndex(int idx) {
	string key;
	string word=dict_[idx].first;
	for(std::size_t word_idx=0;word_idx!=word.size();++word_idx){
		char ch=word[word_idx];
		if(ch & (1<<7)){  //存储utf-8编码的中文字符
			if((ch & 0xF0)==0xC0 || (ch & 0xF0)==0xD0){
				key=word.substr(word_idx,2);
				++word_idx;
			}
			else if((ch & 0xF0) == 0xE0){
				key = word.substr(word_idx, 3);
				word_idx += 2;
			}
			else if((ch & 0xF0) == 0xF0){
				key = word.substr(word_idx, 4);
				word_idx += 3;
			}
			else if((ch & 0xFF) == 0xF8){
				key = word.substr(word_idx, 5);
				word_idx += 4;
			}
			else if((ch & 0xFF) == 0xFE){
				key = word.substr(word_idx, 6);
				word_idx += 5;
			}
		}else{
			key = word.substr(word_idx, 1);
		}
		index_[key].insert(idx);
	}
}

} //namespace ccspace
