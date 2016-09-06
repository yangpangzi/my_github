/*************************************************************************
	> File Name: sql_api.cpp
	> Author: yangle
	> Mail: yangle4695@gmail.com 
	> Created Time: 2016年08月17日 星期三 09时09分06秒
 ************************************************************************/
#pragma once

#include<iostream>
#include <string>
#include "mysql.h"
using namespace std;

class sql_api{
	public:
		sql_api(const string &_host="127.0.0.1",const string &_user="yangle",const string &_passwd="4695106",const string &_db="tinyhttpd");
		int my_connect_mysql();
		int my_insert(std::string &cols,std::string &data);
		int my_select();
		~sql_api();
	private:
		MYSQL *conn;
		MYSQL_RES *res;
		std::string host;
		std::string user;
		std::string passwd;
		std::string db;
		int port;
};
