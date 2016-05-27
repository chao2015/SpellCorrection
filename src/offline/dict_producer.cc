 ///
 /// @file    dict_producer.cc
 /// @author  chenchao(anqing_chao@163.com)
 /// @date    2016-05-18 00:48:38
 ///
 
#include "dict_producer.h"
#include "configuration.h"
#include "split_tool.h"
#include <dirent.h>
#include <stdio.h>
#include <strings.h>
#include <cstring>
#include <iostream>
#include <fstream>
#include <sstream>  //istringstream
using std::cerr;
using std::cin;
using std::cout;
using std::endl;
using std::ifstream;
using std::istringstream;
using std::ofstream;

namespace ccspace {

ifstream& OpenFile(ifstream& in,const string& file) {
	in.close();
	in.clear();
	in.open(file.c_str());
	return in;
}

void LineHandle(string& line) {
	for(int line_num=0;line_num!=line.size();++line_num){
		if(!isalpha(line[line_num]))
			line[line_num]=' ';
		else if(isupper(line[line_num]))
			line[line_num]^=0x20;
	}
}

DictProducer::DictProducer(Configuration& config)
	: config_(config),
	  dir_(config.GetMyEnSources()) {
	GetFiles();
}

DictProducer::DictProducer(Configuration& config,SplitTool* split_tool)
	: config_(config),
	  split_tool_(split_tool),
	  dir_(config.GetMyCnSources()) {
	GetFiles();
}

void DictProducer::BuildCnDict() {
	for(auto & elem : files_){
		ifstream infile;
		if(!OpenFile(infile,elem)){
			cerr<<"No input file!"<<endl;
			exit(EXIT_FAILURE);
		}
		string line;
		while(getline(infile,line)){
			vector<string> cut_line_vec;
			cut_line_vec=split_tool_->Cut(line);
			for(auto & vec_elem : cut_line_vec){
				if(dict_.find(vec_elem)!=dict_.end()){
					++dict_[vec_elem];
				}else{
					dict_.insert(map<string,int>::value_type(vec_elem,1));
				}
			}
		}
		infile.close();
	}
}

void DictProducer::BuildEnDict() {
	for(auto & elem : files_){
	ifstream infile;
	if(!OpenFile(infile,elem)){
		cerr<<"No input file!"<<endl;
		exit(EXIT_FAILURE);
	}
	string line;
	string word;	
	while(infile>>line){	
		LineHandle(line);
		istringstream iss(line);
		while(iss>>word){
			if(dict_.find(word)!=dict_.end()){
				++dict_[word];
			}else{
				dict_.insert(map<string,int>::value_type(word,1));
			}
		}
	}
	infile.close();
	}
}

void DictProducer::StoreEnDict() {
	ofstream outfile(config_.GetMyEnDict().c_str());
	if(!outfile.good()){
		cerr<<"write dictionary failed!"<<endl;
		exit(EXIT_FAILURE);
	}
	for(auto & elem : dict_){
		outfile<<elem.first<<" "<<elem.second<<endl;
	}
}

void DictProducer::StoreCnDict() {
	ofstream outfile(config_.GetMyCnDict().c_str());
	if(!outfile.good()){
		cerr<<"write dictionary failed!"<<endl;
		exit(EXIT_FAILURE);
	}
	for(auto & elem : dict_){
		outfile<<elem.first<<" "<<elem.second<<endl;
	}
}


void DictProducer::GetFiles() {
	DIR* dp=opendir(dir_.c_str());
	if(NULL==dp){
		fprintf(stderr,"cannot open dir:%s\n",dir_.c_str());
		return;
	}
	struct dirent* dpInfo;
	char buf[512];
	while((dpInfo=readdir(dp))!=NULL){
		if(!(strcmp(".",dpInfo->d_name)==0 || 
			strcmp("..",dpInfo->d_name)==0)){
			bzero(buf,sizeof(buf));
			sprintf(buf,"%s/%s",dir_.c_str(),dpInfo->d_name);
			files_.push_back(buf);
		}
	}
}

void DictProducer::ShowFiles() const {
	for(auto & elem : files_){
		cout<<elem<<endl;
	}
}

map<string,int>& DictProducer::GetDictMap() {
	return dict_;
}

}  //namespace ccspace
