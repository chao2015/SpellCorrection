 ///
 /// @file    noncopyable.h
 /// @author  chenchao(anqing_chao@163.com)
 /// @date    2016-05-13 15:03:20
 ///

#ifndef __MY_NONCOPYABLE_H__
#define __MY_NONCOPYABLE_H__

namespace ccspace {

class Noncopyable {
 protected:
	Noncopyable(){}
 private:
	Noncopyable(const Noncopyable& rhs);
	Noncopyable& operator=(const Noncopyable& rhs);
};

}  //namespace ccspace

#endif
