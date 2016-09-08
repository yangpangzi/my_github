/*************************************************************************
	> File Name: client.cpp
	> Author: yangle
	> Mail: yangle4695@gmail.com 
	> Created Time: 2016年08月23日 星期二 09时20分51秒
 ************************************************************************/

#include "udp_client.h"
#include <stdio.h>

udp_client::udp_client(const std::string &_ip,\
			const int &_port)
		:remote_ip(_ip)
		 ,remote_port(_port)
{
init();
}
void udp_client::init()
{
    sock = socket(AF_INET,SOCK_DGRAM,0);
    if(sock <0){
	   printf("%s %s %d","create socket error!",__FUNCTION__,__LINE__);
	   exit(1);
	}
}
  
int udp_client::recv_data(std::string& out)
{
	char buf[SIZE];
	struct sockaddr_in peer;
	socklen_t len=sizeof(peer);
	ssize_t s= recvfrom(sock,buf,sizeof(buf),0,\
				(struct sockaddr*)&peer,&len);
	if(s>0){
		buf[s]='\0';
		out =buf;
	}else{
		printf("%s %s %d","recvfrom error!",__FUNCTION__,__LINE__);

	}
	return s;
}
int udp_client::send_data(const std::string &in)
{
	struct sockaddr_in remote;
	remote.sin_family=AF_INET;
	remote.sin_port=htons(remote_port);
	remote.sin_addr.s_addr=inet_addr(remote_ip.c_str());
	socklen_t len =sizeof(remote);
	ssize_t s=sendto(sock,in.c_str(),in.size(),0,\
				(struct sockaddr*)&remote,len);
	if(s<0){
		printf("%s %s %d","sendto error!",__FUNCTION__,__LINE__);

	}
    return s;
}
udp_client::~udp_client()
{
     if(sock >0){
	    close(sock);
	    sock=-1;
     }
}
