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
		std::cout<<data.get_nick_name<<std::endl;
		std::cout<<data.get_school<<std::endl;
		std::cout<<data.get_msg<<std::endl;
		std::data.get_cmd<<std::endl;
	}
}

static void usage(const char *proc)
{
	std::cout<<"Usag:"<<proc<<" [ip] [port]"<<std::endl;

}

int main()
{
	if(argc !=3){
		usag(argv[0]);
		exit(3);
	}
    udp_server ser(argv[1],atoi(argv[2]));
	pthread_t id1,id2;
	pthread_create(&id1,NULL,myrecv,(void*)&ser);
	pthread_create(&id2,NULL,mybrocast,(void*)&ser);
	pthread_join(id1,NULL);
	pthread_join(id2,NULL);

	return 0;

}
