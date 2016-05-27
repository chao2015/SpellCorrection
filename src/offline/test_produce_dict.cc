 ///
 /// @file    test4_jieba.cc
 /// @author  chenchao(anqing_chao@163.com)
 /// @date    2016-05-24 15:44:36
 ///
 
#include "configuration.h"
#include "dict_producer.h"
#include "index_producer.h"
#include "split_tool.h"
#include <iostream>

int main() {
	ccspace::Configuration config("./conf/my.conf");
	ccspace::SplitToolCppJieba* p_jieba=new ccspace::SplitToolCppJieba(config);
	ccspace::DictProducer dict_en(config);
	dict_en.ShowFiles();
	dict_en.BuildEnDict();
	dict_en.StoreEnDict();
	ccspace::IndexProducer index_en(config,dict_en);
	index_en.BuildEnIndex();
	index_en.StoreEnIndex();
	ccspace::DictProducer dict_cn(config,p_jieba);
	dict_cn.ShowFiles();
	dict_cn.BuildCnDict();
	dict_cn.StoreCnDict();
	ccspace::IndexProducer index_cn(config,dict_cn);
	index_cn.BuildCnIndex();
	index_cn.StoreCnIndex();
}
