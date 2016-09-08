/*************************************************************************
	> File Name: udp_server.h
	> Author: yangle
	> Mail: yangle4695@gmail.com 
	> Created Time: 2016年08月23日 星期二 17时59分04秒
 ************************************************************************/

#pragma once

#include <iostream>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <map>
#include <errno.h>
#include <unistd.h>
#include <stdlib.h>
#include "data_pool.h"
#include "common.h"
#include "udp_data.h"
using namespace std;

class udp_server{
	public:
		udp_server(const int &_port=9999);
		int init(int _port);
        int reliable_recv_msg(std::string& _out);
		int recv_data(std::string &_out);
		int brocast_data();
		~udp_server();
	private:
		bool register_user(const struct sockaddr_in &client,std::string &_msg);
        int reliable_send_msg(const string &_in,\
					const struct sockaddr_in &client,\
					socklen_t len);
        int send_data(const std::string &_in,\
			const struct sockaddr_in &client,\
			const socklen_t &len);
	private:
		int sock;
		int port;
		std::map<std::string , struct sockaddr_in>online_user;
		data_pool pool;
};
