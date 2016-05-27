
 ///
 /// @file    myconf.cc
 /// @author  chenchao(anqing_chao@163.com)
 /// @date    2016-05-19 15:25:13
 ///
#include "myconf.h"
#include <cstring>
#include <fstream>
#include <sstream>
#include <iostream>
using std::cerr;
using std::endl;
using std::ifstream;
using std::istringstream;

ifstream& OpenFile(ifstream& in,const string& filepath) {
	in.close();
	in.clear();
	in.open(filepath.c_str());
	return in;
}

void BuildConfigMap(const string& filepath,map<string,string>& config_map) {
	ifstream in;
	if(!OpenFile(in,filepath)){
		cerr<<"No Config file!"<<endl;
		exit(EXIT_FAILURE);
	}
	for(string config_line;getline(in,config_line);){
		string config_part1, config_part2;
		istringstream iss(config_line);
		iss>>config_part1;
		iss>>config_part2;
		config_map.insert(map<string,string>::value_type
			(config_part1,config_part2));
	}
}

namespace ccspace{

MyConf::MyConf(const string& filepath)
	: filepath_(filepath) {
	GetConfigMap();
}

map<string,string>& MyConf::GetConfigMap() {
	BuildConfigMap(filepath_,config_map_);
	return config_map_;
}

string& MyConf::GetMyIp() {
	return config_map_["myip"];
}

unsigned short MyConf::GetMyPort() {
	return atoi(config_map_["myport"].c_str());
}

string& MyConf::GetMyEnDict() {
	return config_map_["myendict"];
}

string& MyConf::GetMyCnDict() {
	return config_map_["mycndict"];
}

string& MyConf::GetMyEnIndex() {
	return config_map_["myenindex"];
}

string& MyConf::GetMyCnIndex() {
	return config_map_["mycnindex"];
}

string& MyConf::GetMyCache() {
	return config_map_["mycache"];
}

}  //namespace ccspace
