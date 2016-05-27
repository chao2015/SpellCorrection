 //
 /// @file    cache.h
 /// @author  chenchao(anqing_chao@163.com)
 /// @date    2016-05-20 21:07:59
 ///

#ifndef __MY_CACHE_H__
#define __MY_CACHE_H__

#include <string>
#include <unordered_map>
using std::string;
using std::unordered_map;

namespace ccspace {

class Cache {
 public:
	Cache(int num=100);
	Cache(const Cache& cache);
	void AddElement(const string& key,const string& value);  //往缓存中添加数据
	string Query(const string& word);
	void ReadFromFile(const string& filename);  //从文件中读取缓存信息
	void WriteToFile(const string& filename);  //将缓存信息写入到文件中
	void Update(const Cache& cache);  //更新缓存信息
 private:
	unordered_map<string,string> hash_map_;  //互斥变量
};

}  //namespace ccspace

#endif
