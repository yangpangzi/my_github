/*************************************************************************
	> File Name: myjson.h
	> Author: yangle
	> Mail: yangle4695@gmail.com 
	> Created Time: 2016年08月25日 星期四 21时09分46秒
 ************************************************************************/

#include<iostream>
#include <string>
#include "json/json.h"

class myjson{
	public:
		myjson();
		~myjson();
		static void serialize(Json::Value &val,std::string &out);
		static void unserialized(std::string &in,Json::Value &val);
};

