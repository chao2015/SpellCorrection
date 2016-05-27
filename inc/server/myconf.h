#ifndef _CONF_H
#define _CONF_H

#include <string>
#include <sstream>
#include <map>
using std::string;
using std::map;

namespace ccspace {

class MyConf {
 public:
	MyConf(const string& filepath);
	map<string,string>& GetConfigMap();
	string& GetMyIp();
	unsigned short GetMyPort();
	string& GetMyEnDict();
	string& GetMyCnDict();
	string& GetMyEnIndex();
	string& GetMyCnIndex();
	string& GetMyCache();
 private:
	string filepath_;
	map<string,string> config_map_;
};

}  //namespace ccspace

#endif
