 ///
 /// @file    socket_io.cc
 /// @author  chenchao(anqing_chao@163.com)
 /// @date    2016-05-18 21:13:59
 ///

#include "socket_io.h"
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <sys/socket.h>

namespace ccspace {

SocketIO::SocketIO(int fd)
	: fd_(fd) {
}
//从buff位置开始读取buff_size个字节(不一定是buff全部大小)
int SocketIO::ReadN(char* buff,int buff_size) {
	int left_size=buff_size;  //剩余的字节数
	char* pbuf=buff;  //缓冲区的偏移量
	while(left_size>0){
		int read_ret=::read(fd_,pbuf,left_size);
		if(-1==read_ret){
			if(errno==EINTR)
				continue;
			perror("read error");
			exit(EXIT_FAILURE);
		}else if(0==read_ret){
			break;
		}
		pbuf+=read_ret;
		left_size-=read_ret;
	}
	return (buff_size-left_size);
}

int SocketIO::WriteN(const char* buff,int buff_size) {
	int left_size=buff_size;
	const char * pbuf=buff;
	int write_ret=0;
	while(left_size>0){
		write_ret=write(fd_,pbuf,left_size);
		if(-1==write_ret){
			if(errno==EINTR)
				continue;
			perror("write");
			exit(EXIT_FAILURE);
		}
		pbuf+=write_ret;
		left_size-=write_ret;
	}
	return (buff_size-left_size);
}

int SocketIO::RecvPeek(char* buff,int buff_size) {
	int ret_read;
	do{
		//并不移走内核缓冲区的数据
		ret_read=::recv(fd_,buff,buff_size,MSG_PEEK);
	}while(-1==ret_read && errno==EINTR);
	return ret_read;
}

int SocketIO::ReadLine(char* buff,int max) {
	int left_size=max-1;  //如果是max个字节里面没有'\n'，
						  //就取max-1个字节的数据，加'\n'
	char* pbuf=buff;
	int read_total=0;
	while(left_size>0){
		//先去内核缓冲区预读数据
		int read_ret=RecvPeek(pbuf,left_size);
		if(read_ret<=0)
			return read_ret;
		//检查read_ret个字节的数据里面有没有'\n'
		for(int idx=0;idx!=read_ret;++idx){
			if(pbuf[idx]=='\n'){
				//找到'\n',直接从内核缓冲区中移走数据，并返回
				int line_size=idx+1;
				if(ReadN(pbuf,line_size)!=line_size)
					return EXIT_FAILURE;
				left_size-=line_size;
				read_total+=line_size;
				pbuf+=line_size;
				*pbuf='\0';
				return read_total;  //返回一行有多少字节
			}
		}
		//没有找到，就移走内核缓冲区里面的read_ret个字节的数据
		if(ReadN(pbuf,read_ret)!=read_ret)
			return EXIT_FAILURE;
		left_size-=read_ret;
		pbuf+=read_ret;
		read_total+=read_ret;
	}
	//在最大字节数的范围内最终也没有找到'\n',就直接截取max-1个字节作为一行
	*pbuf='\0';
	return max-1;
}

}  //namespace ccspace
