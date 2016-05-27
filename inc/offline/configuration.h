 ///
 /// @file    configuration.h
 /// @author  chenchao(anqing_chao@163.com)
 /// @date    2016-05-19 15:17:29
 ///
 
#ifndef __MY_CONFIGURATION_H__
#define __MY_CONFIGURATION_H__

#include <iostream>
#include <map>
using std::string;
using std::map;

namespace ccspace {

class Configuration {
 public:
	Configuration(const string& filepath);
	map<string,string>& GetConfigMap();
	string& GetMyIp();
	unsigned short GetMyPort();
	string& GetMyEnDict();
	string& GetMyCnDict();
	string& GetMyEnIndex();
	string& GetMyCnIndex();
	string& GetMyEnSources();
	string& GetMyCnSources();
 private:
	string filepath_;
	map<string,string> config_map_;
};

}  //namespace ccspace 

#endif
