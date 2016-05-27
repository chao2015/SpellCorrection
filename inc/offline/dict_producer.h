 ///
 /// @file    dict_producer.h
 /// @author  chenchao(anqing_chao@163.com)
 /// @date    2016-05-18 00:28:55
 ///

#include <string>
#include <vector>
#include <map>
using std::string;
using std::vector;
using std::map;

namespace ccspace {

class Configuration;
class SplitTool;

class DictProducer {
 public:
	DictProducer(Configuration& config);  //构造函数
	DictProducer(Configuration& config,SplitTool* split_tool);  //构造函数，专为中文处理
	void BuildEnDict();  //创建英文字典
	void BuildCnDict();  //创建中文字典
	void StoreEnDict();  //将英文字典写入文件
	void StoreCnDict();  
	void ShowFiles() const;  //查看文件路径，作为测试用
	void GetFiles();  //获取文件的绝对路径
	void PushDict(const string& word);  //存储某个单词,即是添加字典元素的封装,没有使用
	map<string,int>& GetDictMap();  //获取字典的map
 private:
	string dir_;  //语料库文件存放路径
	vector<string> files_;  //语料库文件的绝对路径集合
	map<string,int> dict_;  //字典内容
	SplitTool* split_tool_;  //分词工具,使用指针的目的是可以以空指针存在，在只用英文字典时可以不初始化
	Configuration& config_;
};

}  //namespace ccspace
