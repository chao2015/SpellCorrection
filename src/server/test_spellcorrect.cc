 ///
 /// @file    test_tcpserver.cc
 /// @author  chenchao(anqing_chao@163.com)
 /// @date    2016-05-19 10:23:21
 ///

#include "spellcorrect_server.h"
#include <stdio.h>
#include <string.h>
#include <string>
#include <iostream>
using std::cout;
using std::endl;

int main(void) {
	ccspace::SpellcorrectServer server("./conf/my.conf");
	server.Start();
	return 0;
}
