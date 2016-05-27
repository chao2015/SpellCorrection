 ///
 /// @file    configuration.cc
 /// @author  chenchao(anqing_chao@163.com)
 /// @date    2016-05-19 15:25:13
 ///
 
#include "configuration.h"
#include <cstring>
#include <fstream>
#include <sstream>
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

Configuration::Configuration(const string& filepath)
	: filepath_(filepath) {
	GetConfigMap();
}

map<string,string>& Configuration::GetConfigMap() {
	BuildConfigMap(filepath_,config_map_);
	return config_map_;
}

string& Configuration::GetMyIp() {
	return config_map_["myip"];
}

unsigned short Configuration::GetMyPort() {
	return atoi(config_map_["myport"].c_str());
}

string& Configuration::GetMyEnDict() {
	return config_map_["myendict"];
}

string& Configuration::GetMyCnDict() {
	return config_map_["mycndict"];
}

string& Configuration::GetMyEnIndex() {
	return config_map_["myenindex"];
}

string& Configuration::GetMyCnIndex() {
	return config_map_["mycnindex"];
}

string& Configuration::GetMyEnSources() {
	return config_map_["myensources"];
}

string& Configuration::GetMyCnSources() {
	return config_map_["mycnsources"];
}


}  //namespace ccspace
