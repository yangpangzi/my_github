/*************************************************************************
	> File Name: myjson.cpp
	> Author: yangle
	> Mail: yangle4695@gmail.com 
	> Created Time: 2016年08月25日 星期四 21时13分44秒
 ************************************************************************/

#include "myjson.h"
myjson::myjson()
{}
void myjson::serialize(Json::Value &val,std::string &out)
{
#ifdef FAST
	Json::FastWrite _w;
#else
	Json::StyledWriter _w;
#endif
	out =_w.write(val);
}

void myjson::unserialized(std::string &in,Json::Value &val)
{
	Json::Reader _r;
	_r.parse(in,val,false);
}
myjson::~myjson()
{}
