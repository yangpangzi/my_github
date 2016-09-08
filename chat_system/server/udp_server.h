/*************************************************************************
	> File Name: udp_server.h
	> Author: yangle
	> Mail: yangle4695@gmail.com 
	> Created Time: 2016年08月23日 星期二 17时59分04秒
 ************************************************************************/

#pragma once

#include <iostream>
#include <string>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <map>
#include "data_pool.h"
#include "common.h"
#include "udp_data.h"

class udp_server{
	private:
		bool register_user(const struct sockaddr_in &client,std::string &_msg);
        int reliable_send_msg(const string &_in,\
					const struct sockaddr_in &client,\
					socklen_t len);
        int send_data(const std::string &_in,\
			const struct sockaddr_in &client,\
			const socklen_t &len)
	public:
		udp_server(const std::string &_ip="127.0.0.1",\
					const int &_port=9999);
		int init(int _port);
        int reliable_recv_msg();
		int recv_data(std::string &_out);
		int brocast_data();
		~udp_server();
	private:
		int sock;
        std::string ip;
		int port;
		std::map<std::string , struct sockaddr_in>online_user;
		data_pool pool;
};
