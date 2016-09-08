/*************************************************************************
	> File Name: chat_wincliet.cpp
	> Author: yangle
	> Mail: yangle4695@gmail.com 
	> Created Time: 2016年09月03日 星期六 01时03分54秒
 ************************************************************************/
#include "udp_client.h"
#include <stdio.h>
#include <pthread.h>
#include <vector>
#include <signal.h>
#include <algorithm>
#include <stdlib.h>
#include <strstream>
#include "cwindow.h"

cwindow win;

vector<string> list;

void* client_header(void*arg)
{
	string msg="WELCOME TO MY CHAT SYSTEM";
	win.create_header();
	win.win_refresh(win.get_header());
	int x=0,y;
	while(1)
	  {
		  int max_y,max_x;
		  getmaxyx(win.get_header(),max_y,max_x);
		  y=max_y/2-1;
		  win.clear_win_line(win.get_header(),y,1);
		  win.put_str_to_win(win.get_header(),y,++x%max_x,msg);
		  sleep(1);
		  win.win_refresh(win.get_header());
	  }
}
void*client_output(void*arg)
{
	udp_data _client_data;
	udp_client *_client =(udp_client*)arg;
	string _msg;
	string _nick_name;
	string _school;
	string _info;
	string _cmd;

	int total=1;

	win.create_output();
	win.win_refresh(win.get_output());
	while(1)
	{

		win.win_refresh(win.get_output());
		if(_client->recv_data(_msg)==0)
		{
			_client_data.str_to_val(_msg);
			_client_data.get_nick_name(_nick_name);
			_client_data.get_school(_school);
			_client_data.get_cmd(_cmd);
			if(_cmd=="MESSAGE")
			{
				string show_msg=_nick_name+"/"+_school;
				list.push_back(show_msg);
				show_msg+=":";
				show_msg+=_info;
				total %=(LINES*3/5-1);
				if(total ==0)
				{
					win.clear_win_line(win.get_output(),1,LINES*3/5);
					total = 1;
				}
				win.put_str_to_win(win.get_output(),total++,1,show_msg);
				win.win_refresh(win.get_output());
			}
			win.win_refresh(win.get_output());

		}
	}
}
void * client_list(void*arg)
{
	//list
	win.create_flist();
	while(1)
	{
		int max_y,max_x;
		getmaxyx(win.get_flist(),max_y,max_x);

		int i=0;
		sort(list.begin(),list.end());
		vector<string>::iterator iter=unique(list.begin(),list.end());
		list.erase(iter,list.end());
		int total = list.size();

		int page=max_y-3;
		int page_num=total/page;
		int page_mod =total%page;
		if(page_mod>0)
		{
			page_num+1;
		}
		strstream ss;
		string str_page_num;
		ss<<page_num;
		string _out_page;
		win.win_refresh(win.get_flist());
		for(i=0;i< page_num;i++)
		{
			string str_i;
			strstream ssi;
			ssi<<i+1;
			ssi>>str_i;
			_out_page=str_i+"/"+str_page_num;
			win.clear_win_line(win.get_flist(),max_y-2,1);
			win.put_str_to_win(win.get_flist(),max_y-2,max_x/2,_out_page);
			int y=0;
			for(int j=0;j<page;++j)
			{
				y++;
				y=y%(max_y-3);
				int index =i*page+j;
				if(index<total)
				{
					string _fri=list[index];
					if(y==0)
					{
						win.win_refresh(win.get_flist());
						sleep(3);
						win.clear_win_line(win.get_flist(),1,max_y-4);
						continue;
					}
					win.put_str_to_win(win.get_flist(),y,2,_fri);
				}else
				{
					break;
				}
			}
		}
		win.win_refresh(win.get_flist());
		usleep(10000);
	}
}

void* client_input(void* arg)
{
	win.create_input();
	win.win_refresh(win.get_input());
	string _nick_name;
	string _school;
	string _cmd = "MESSAGE";
	string send_string;

	udp_client* _client = (udp_client*)arg;
	udp_data _client_data;
	string message ="please ENTER :";
	string put_name="Please input nick_name";
	string put_school="Please input school";
	string _client_msg;

	win.put_str_to_win(win.get_input(),1,2,put_name);
	win.win_refresh(win.get_input());
	win.get_str_from_win(win.get_input(),_nick_name);
	win.win_refresh(win.get_input());

	win.put_str_to_win(win.get_input(),2,2,put_school);
	win.win_refresh(win.get_input());
	win.get_str_from_win(win.get_input(),_school);
	win.win_refresh(win.get_input());

	win.clear_win_line(win.get_input(),1,2);
	win.win_refresh(win.get_input());

	while(1)
	{

		win.put_str_to_win(win.get_input(),1,2,message);
		win.win_refresh(win.get_input());
		win.get_str_from_win(win.get_input(),_client_msg);

		_client_data.set_nick_name(_nick_name);
		_client_data.set_school(_school);
		_client_data.set_msg(_client_msg);
		_client_data.set_cmd(_cmd);

		_client_data.val_to_str(send_string);
		_client->send_data(send_string);

		win.clear_win_line(win.get_input(),1,1);
		usleep(10000);
	}
}

void handler(int sig)
{

	udp_client _client;
	udp_data _client_data;
	string _nick_name="YL";
	string _school="SKD";
	string _client_msg="None";
	string _cmd ="CMD-OUT";
	string send_string;

	switch(sig)
	{
		case SIGINT:
			{

				_client_data.set_nick_name(_nick_name);
				_client_data.set_school(_school);
				_client_data.set_msg(_client_msg);
				_client_data.set_cmd(_cmd);

				_client_data.val_to_str(send_string);
				_client.send_data(send_string);

				exit(1);
			}
			break;
		case SIGTERM:
			endwin();
			break;
		default:
			break;
	}
}



int main()
{

	udp_client client;
	udp_data _client_data;
	client.init();

	signal(SIGINT,handler);
	signal(SIGTERM,handler);

	win.create_header();
	win.create_output();
	win.create_flist();
	win.create_input();

	pthread_t header,output,flist,input;
	pthread_create(&header,NULL,client_header,NULL);
	pthread_create(&output,NULL,client_output,(void*)&client);
	pthread_create(&flist,NULL,client_list,NULL);
	pthread_create(&input,NULL,client_input,(void*)&client);

	pthread_join(header,NULL);
	pthread_join(output,NULL);
	pthread_join(flist,NULL);
	pthread_join(input,NULL);

	return 0;
}
