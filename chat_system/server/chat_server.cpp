/*************************************************************************
	> File Name: main.cpp
	> Author: yangle
	> Mail: yangle4695@gmail.com 
	> Created Time: 2016年08月24日 星期三 08时31分22秒
 ************************************************************************/

#include<iostream>
#include "udp_server.h"

static void *mybrocast(void *arg)
{
	udp_server *ser =(udp_server*)arg;
	while(1){
		ser->brocast_data();
	}
}

static void *myrecv(void *arg)
{
	udp_server *ser = (udp_server *)arg;
	std::string out;
	udp_data data;
	while(1){
		ser->reliable_recv_msg(out);
		data.str_to_val(out);
		string nick_name;
		data.get_nick_name(nick_name);
		string school;
		data.get_school(school);
		string msg;
		data.get_msg(msg);
		string cmd;
		data.get_cmd(cmd);
		std::cout<<nick_name<<std::endl;
		std::cout<<school<<std::endl;
		std::cout<<msg<<std::endl;
		std::cout<<cmd<<std::endl;
	}
}

static void usage(const char *proc)
{
	std::cout<<"Usag:"<<proc<<" [ip] [port]"<<std::endl;

}

int main(int argc,char *argv[])
{
	if(argc !=3){
		usage(argv[0]);
		exit(3);
	}
	int port=atoi(argv[2]);
    udp_server ser;
//	ser.init(port);
	pthread_t id1,id2;
	pthread_create(&id1,NULL,myrecv,(void*)&ser);
	pthread_create(&id2,NULL,mybrocast,(void*)&ser);
	pthread_join(id1,NULL);
	pthread_join(id2,NULL);

	return 0;

}
