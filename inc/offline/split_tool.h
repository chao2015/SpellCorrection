 ///
 /// @file    split_tool.h
 /// @author  chenchao(anqing_chao@163.com)
 /// @date    2016-05-19 16:20:02
 ///

#ifndef __MY_SPLITTOOL_H__
#define __MY_SPLITTOOL_H__

#include "configuration.h"
#include <vector>
using std::vector;

namespace ccspace {

class SplitTool {
 public:
	SplitTool(){}
	virtual ~SplitTool(){}
	virtual vector<string> Cut(const string& sentence)=0;
};

class SplitToolCppJieba : public SplitTool {
 public:
	SplitToolCppJieba(Configuration& conf);
	~SplitToolCppJieba();
	vector<string> Cut(const string& sentence);
 private:
	Configuration& config_;
};

}  //namespace ccspace

#endif
