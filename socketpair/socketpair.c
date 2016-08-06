/*************************************************************************
	> File Name: socketpair.c
	> Author: yangle
	> Mail: yangle4695@gmail.com 
	> Created Time: 2016年08月06日 星期六 01时39分52秒
 ************************************************************************/

#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<sys/socket.h>


int main()
{
	int fd[2];
	int ret=socketpair(PF_LOCAL,SOCK_STREAM,0,fd);
	if(ret!=0){
		perror("socketpair()");
		return ret;
	}
	pid_t id = fork();
    if(id<0){
	   perror("fork()");
	   return id;
    }else if(id ==0){//child
        close(fd[0]);
		char buf[1024];
		while(1){
			memset(buf,0,sizeof(buf));
			strcpy(buf,"hello world");
			write(fd[1],buf,sizeof(buf));
			read(fd[1],buf,sizeof(buf));
			sleep(1);
			printf("%s\n",buf);
		   }
		}else if(id > 0){
			close(fd[1]);
			char buf[1024];
			while(1){
				memset(buf,0,sizeof(buf));
				read(fd[0],buf,sizeof(buf));
				printf("%s\n",buf);
				strcpy(buf,"hello world too");
				write(fd[0],buf,sizeof(buf));
			}
		}
		return 0;

}

