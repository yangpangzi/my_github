/*************************************************************************
	> File Name: cwindow.h
	> Author: yangle
	> Mail: yangle4695@gmail.com 
	> Created Time: 2016年08月25日 星期四 22时19分49秒
 ************************************************************************/

#include<iostream>
using namespace std;
#include "ncurses.h"
#include "common.h"
#include <string.h>
#include <pthread.h>
class cwindow{
	public:
		cwindow();

		void create_header();
		void create_output();
		void create_flist();
		void create_input();
		void win_refresh(WINDOW* _win);
		void put_str_to_win(WINDOW *_win,\
					int _y,int _x,std::string &str);
void get_str_from_win(WINDOW* _win,string& out);
		void clear_win_line(WINDOW* _win,int begin,int num);
	WINDOW* get_header()
	{
		return header;
	}
	WINDOW* get_output()
	{
		return output;
	}
	WINDOW* get_flist()
	{
		return flist;
	}
	WINDOW* get_input()
	{
		return input;
	}
        ~cwindow();
	private:
		WINDOW *header;
		WINDOW *output;
		WINDOW *flist;
		WINDOW *input;
		pthread_mutex_t lock;
};

