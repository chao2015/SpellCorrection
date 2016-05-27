 ///
 /// @file    index_producer.h
 /// @author  chenchao(anqing_chao@163.com)
 /// @date    2016-05-20 22:14:35
 /// 备注：服务器实际运行时会读取中英文字典，创建索引，故这个索引类的作用仅仅在于
 /// 创建记录索引的本地文件。

#ifndef __MY_INDEXPRODUCER_H__
#define __MY_INDEXPRODUCER_H__

#include <vector>
#include <map>
using std::vector;
using std::map;
using std::pair;
using std::string;

namespace ccspace {

class Configuration;
class DictProducer;

class IndexProducer {
 public:
	IndexProducer(Configuration&,DictProducer&);
	void BuildEnIndex();
	void BuildCnIndex();
	void StoreEnIndex();
	void StoreCnIndex();
 private:
	Configuration& config_;
	DictProducer& dict_;
	vector<pair<string,int> > dict_vector_;
	map<string,vector<int> > index_map_;
};

}  //namespace ccspace

#endif
