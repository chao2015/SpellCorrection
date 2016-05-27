 ///
 /// @file    split_tool.cc
 /// @author  chenchao(anqing_chao@163.com)
 /// @date    2016-05-24 11:18:05
 ///
 
#include "split_tool.h"
#include "cppjieba/Jieba.hpp"
#include <iostream>

namespace ccspace {

SplitToolCppJieba::SplitToolCppJieba(Configuration& conf)
	: config_(conf) {
		
	}

SplitToolCppJieba::~SplitToolCppJieba() {
}

vector<string> SplitToolCppJieba::Cut(const string& sentence) {
	cppjieba::Jieba jieba((config_.GetConfigMap())["dict_path"],
						  (config_.GetConfigMap())["hmm_path"],
						  (config_.GetConfigMap())["user_dict_path"]);
	//vector<string> words;
	vector<string> jiebawords;
	
	//std::cout<<sentence<<std::endl;
	jieba.Cut(sentence,jiebawords,true);
	
	//std::cout<<limonp::Join(words.begin(),words.end()," ")<<std::endl;  //打印分词后的效果，以空格分词
	return jiebawords;  //这里如果没有return，编译不会报错，但会出现段错误。
}



}  //namespace ccspace
