#SpellCorrection Project in C++ Based on Linux Platform

----

[TOC]

----

##一、概述

+ 项目设计uml图(暂略)

###1.简介

+ 实现过程中利用了socket网络编程中的TCP/IP协议进行客户端和服务器通信。
+ 本项目使用的是线程池来进行多客户端同时进行业务处理。
+ 本项目引入缓存(cache)机制，结合定时器(timer)，实现了依据操作和依据时限两种方式来更新缓存。
+ 本项目引入CppJieba，来实现中文部分的分词功能。
+ 本项目通过最小编辑距离算法来实现文本纠错的业务逻辑。
+ 本项目引入log4cpp，来实现记录日志的功能。(暂缺)
+ 项目中利用了Makefile，方便编译。

###2.实现的功能

>离线部分(offline)构建字典，启动服务器(server)，客户端(client)连接：

```shell
welcome to server.
//精确查找
hello  //用户标准输入
receive msg:hello  //服务器返回信息
//模糊查找(纠错)
worlld
receive msg:world
//无相似记录
aabbccddeeffgg
receive msg:no answer!
//中文部分，与上述3种情况类同
诸葛亮
receive msg:诸葛亮
诸葛
receive msg:诸葛亮
肯定没有
receive msg:no answer!
```

##二、运行方法

###1.说明

+ 本项目是在linux mint17.2版本的机器上面编写与测试，gcc版本为4.8.4，内核版本为3.16.0。
+ 运行前，需要在conf/my.conf文件中修改myip和myport部分数据为真实的ip和port信息。

###2.编译运行

```shell
git clone git@github.com:chao2015/SpellCorrection.git
```

>以下每步操作均由项目目录SpellCorrection开始：

+ 第一步：编译

```shell
make
cd ./src
make
cd ./src/client
make
```

+ 第二步：离线部分运行(每次启动服务端时无需重复运行)

```shell
./bin/offline.exe
```

+ 第三步：服务端启动方法

```shell
./bin/server.exe
```

+ 第四步：客户端启动方法，注意为区别与服务端的另一终端

```shell
./bin/client.exe
```