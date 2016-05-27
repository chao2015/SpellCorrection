 ///
 /// @file    index_producer.cc
 /// @author  chenchao(anqing_chao@163.com)
 /// @date    2016-05-20 22:27:08
 ///

#include "configuration.h"
#include "index_producer.h"
#include "dict_producer.h"
#include <iostream>
#include <fstream>
using std::cout;
using std::endl;
using std::cerr;
using std::ofstream;

namespace ccspace {

string& GetFirstWord(string& word) {
	char ch=word[0];
	if(ch & (1<<7)){  //存储utf-8编码的中文字符
		if((ch & 0xF0)==0xC0 || (ch & 0xF0)==0xD0)
			word=word.substr(0,2);
		else if((ch & 0xF0) == 0xE0)
			word=word.substr(0, 3);
		else if((ch & 0xF0) == 0xF0)
			word=word.substr(0, 4);
		else if((ch & 0xFF) == 0xF8)
			word=word.substr(0, 5);
		else if((ch & 0xFF) == 0xFE)
			word=word.substr(0, 6);
	}else{
		word=word.substr(0, 1);
	}
	return word;
}

IndexProducer::IndexProducer(Configuration& config,DictProducer& dict)
	: config_(config),
	  dict_(dict) {
}

void IndexProducer::BuildEnIndex() {
	//将dict_map_的内容放进dict_vector_中
	for(auto & elem : dict_.GetDictMap()){
		dict_vector_.push_back(elem);
	}
	//遍历dict_vector_的内容，插入到index_map_中
	int vector_index=0;
	for(auto & elem : dict_vector_){
		for(int word_index=0;word_index<elem.first.size();++word_index){
			string key=GetFirstWord(elem.first);
			if(index_map_.find(key)!=index_map_.end()){
				index_map_[key].push_back(vector_index);  //向vector<int>插入vector<pair<>>的下标数据	
			}else{
				vector<int> vector_init;
				index_map_.insert(pair<string,vector<int>>(elem.first,vector_init));
			}
		}
		++vector_index;
	}
}

#if 0
	//init map
	for(int ascii=97;ascii<=122;++ascii){
		vector<int> vector_init;
		index_map_.insert(pair<string,vector<int> >((char*)ascii,vector_init));
	}
#endif
#if 0
	//map<char,vector<int> >
	for(auto & elem : dict_vector_){
		for(int word_index=0;word_index<elem.first.size();++word_index){
			if(index_map_.find((char)(elem.first)[word_index])!=index_map_.end()){
				index_map_[(char)(elem.first)[word_index]].push_back(vector_index);  //向vector<int>插入vector<pair<>>的下标数据
			}else{
				vector<int> vector_init;
				index_map_.insert(pair<char,vector<int>>((char)(elem.first)[word_index],vector_init));
			}
		}
		++vector_index;
	}
#endif
#if 0//test
	for(auto & elem : index_map_){
		cout<<elem.first<<" "<<elem.second.size()<<endl;
	}
#endif




#if 1
void IndexProducer::BuildCnIndex() {
	//将dict_map_的内容放进dict_vector_中
	for(auto & elem : dict_.GetDictMap()){
		dict_vector_.push_back(elem);
	}
	//遍历dict_vector_的内容，插入到index_map_中
	int vector_index=0;
	for(auto & elem : dict_vector_){
		for(int word_index=0;word_index<elem.first.size();++word_index){
			string key=GetFirstWord(elem.first);
			if(index_map_.find(key)!=index_map_.end()){
				index_map_[key].push_back(vector_index);  //向vector<int>插入vector<pair<>>的下标数据	
			}else{
				vector<int> vector_init;
				index_map_.insert(pair<string,vector<int>>(elem.first,vector_init));
			}
		}
		++vector_index;
	}
}
#endif

void IndexProducer::StoreEnIndex() {
	ofstream outfile(config_.GetMyEnIndex().c_str());
	if(!outfile.good()){
		cerr<<"write en index failed!"<<endl;
		exit(EXIT_FAILURE);
	}
	for(auto & elem : index_map_){
		outfile<<elem.first<<" ";
		for(auto & vec_elem : elem.second){
			outfile<<vec_elem<<" ";
		}
		outfile<<endl;
	}
}

void IndexProducer::StoreCnIndex() {
	ofstream outfile(config_.GetMyCnIndex().c_str());
	if(!outfile.good()){
		cerr<<"write cn index failed!"<<endl;
		exit(EXIT_FAILURE);
	}
	for(auto & elem : index_map_){
		outfile<<elem.first<<" ";
		for(auto & vec_elem : elem.second){
			outfile<<vec_elem<<" ";
		}
		outfile<<endl;
	}
}


}  //namespace ccspace
