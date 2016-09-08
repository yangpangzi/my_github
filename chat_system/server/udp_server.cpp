/*************************************************************************
	> File Name: udp_server.cpp
	> Author: yangle
	> Mail: yangle4695@gmail.com 
	> Created Time: 2016年08月24日 星期三 08时07分36秒
 ************************************************************************/

#include<iostream>
#include "udp_server.h"

static void print_log(string _log)
{
	cerr<<_log<<endl;
}
udp_server::udp_server(const std::string &_ip,const int &_port)
		:ip(_ip)
		 ,port(_port)
{
	init(port);
}
bool udp_server::register_user(const struct sockaddr_in &client,string &_msg)
{
	string _ip_key=inet_ntoa(client.sin_addr);

	std::map<std::string,struct sockaddr_in>::iterator iter = online_user,find(_ip_key);
	udp_data _data;
	_data.str_to_val(_msg);
	string _cmd;
	_data.get_cmd(_cmd);
	if(_cmd=="MESSAGE")
	{
		if(iter != online_user.end()){
		return false;
	}else{
		online_user.insert(pair<string,struct sockaddr_in>(_ip_key,client));
	}
	}else if(_cmd=="CMD_QUIT")
	{
		onlinue_user.erase(_ip_key);
	}
	return true;
}

int udp_server::init(int _port)
{
	sock=socket(AF_INET,SOCK_DGRAM,0);
	if(sock<0)
	{
		print_log(strerror(errno));
		exit(1);
	}
	struct sockaddr_in local;
	local.sin_family=AF_INET;
	local.sin_port=htons(port);
	local.sin_addr.s_addr=htonl(INADDR_ANY);
	if(bind(sock,(struct sockaddr*)&local,sizeof(local))<0)
	{
		print_log(strerror(errno));
		exit(1);
	}
	return 0;
}
int udp_server::reliable_send_msg(const string &_in,\
			const struct sockaddr_in &client,\
			socklen_t len)
{
	return send_data(_in,client,len);
}
int udp_server::send_data(const std::string &_in,\
					const struct sockaddr_in &client,\
					const socklen_t &len)
{
	ssize_t _size = sendto(sock,_in.c_str(),_in.size(),0,(struct sockaddr*)&client,len);
	if(_size<0)
	{
		print_log(strerror(errno));
		return 1;
	}

	return 0;
}

int udp_server::reliable_recv_msg()
{
	string _out;
	int ret =recv_data(_out);
	if(ret>0)
	{
		pool.put_data(_out);
	}
	return ret;
}

int udp_server::recv_data(std::string &_out)
{
	char buf[SIZE];
	memset(buf,'\0',sizeof(buf));
	struct sockaddr_in client;
	socklen_t len=sizeof(client);

	ssize_t _size=recvfrom(sock,buf,sizeof(buf)-1,0,(struct sockaddr*)&client,&len);

	if(_size <0)
	{
		print_log(strerror(errno));
		out="";
		return 1;
	}else if(_size>=0){
		_out=buf;
		register_user(client,_out);

	}
	return _size;
}
int udp_server::brocast_data()
{
	string _msg;
	pool.get_data(_msg);
	map<string,struct sockaddr_in>::iterator _iter = online_user.begin();
	for(;_iter!=online_user.end();_iter++)
	{
		reliable_send_msg(_msg,_iter->second,sizeof(_iter->second));
	}
}
udp_server::~udp_server()
{
	close(sock);
	sock=-1;
}

