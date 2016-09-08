/*************************************************************************
	> File Name: cwindow.cpp
	> Author: yangle
	> Mail: yangle4695@gmail.com 
	> Created Time: 2016年08月25日 星期四 22时25分40秒
 ************************************************************************/

#include "cwindow.h"

cwindow::cwindow()
{
	pthread_mutex_init(&lock,NULL);
	initscr();
	header=NULL;
	output=NULL;
	flist=NULL;
	input=NULL;
}
void cwindow:: create_header()
{
	int _h=LINES/5;
	int _w=COLS;
	int _y=0;
	int _x=0;
	header=newwin(_h,_w,_y,_x);
}
void cwindow:: create_output()
{
	int _h=(LINES*3)/5;
	int _w=(COLS*4)/5;
	int _y=LINES/5;
	int _x=0;
	output=newwin(_h,_w,_y,_x);
}
void cwindow:: create_flist()
{
	int _h=(LINES*3)/5;
	int _w=COLS/4;
	int _y=LINES/5;
	int _x=(COLS*3)/4;
	flist=newwin(_h,_w,_y,_x);
}
void cwindow:: create_input()
{
	int _h=LINES/5;
	int _w=COLS;
	int _y=(LINES*4)/5;
	int _x=0;
	input=newwin(_h,_w,_y,_x);

}
void cwindow:: win_refresh(WINDOW* _win)
{
	box(_win,0,0);
	pthread_mutex_lock(&lock);

	wrefresh(_win);
	pthread_mutex_unlock(&lock);

}
void cwindow:: put_str_to_win(WINDOW *win,\
			int _y,int _x,std::string &str)
{
	mvwaddstr(win,_y,_x,str.c_str());
}
cwindow:: ~cwindow()
{
	endwin();

}
void cwindow::get_str_from_win(WINDOW* _win,string& out)
{
	char buf[SIZE];
	memset(buf,'\0',sizeof(buf));
	wgetnstr(_win,buf,sizeof(buf));
	out=buf;
}

void clear_win_line(WINDOW* _win,int begin,int num)
{
	while(num-->0)
	{
		wmove(_win,begin++,0);
		wclrtoeol(_win);
	}
}

int main()
{
	cwindow x;
		return 0;
}
