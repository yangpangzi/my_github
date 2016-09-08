/*************************************************************************
	> File Name: client.cpp
	> Author: yangle
	> Mail: yangle4695@gmail.com 
	> Created Time: 2016年08月23日 星期二 08时48分20秒
 ************************************************************************/
#pragma once
#include<iostream>
using namespace std;
#include <string.h>
#include <errno.h>
#include <map>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include "common.h"
#include "udp_data.h"

class udp_client{
	public:
		udp_client(const string &_ip="127.0.0.1",\
					const int &_port=9999);
		void init();
		int recv_data(string& out);
		int send_data(const string &in);
		~udp_client();
	private:
		int sock;
		string remote_ip;
		int remote_port;
};


