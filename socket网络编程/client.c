/*************************************************************************
	> File Name: client.c
	> Author: yangle
	> Mail: yangle4695@gmail.com 
	> Created Time: 2016年08月05日 星期五 01时04分32秒
 ************************************************************************/

#include<stdio.h>

void collect_child(int sig)
{
	while(waitpid(-1,0,WNOHANG)>0){
		printf("colect child done...\n");
	}
}
void* hangler_data(void *arg)
{
	int sock = (int)arg;
	printf("create a new thread...new socket: %d\n",sock);
	char buf[1024];
	while(1){
		ssize_t _s = read(sock,buf,sizeof(buf)-1);
		if(_s>0){//read success
			buf[_s]='\0';
			printf("client# %s\n",buf);
			write(sock,buf,strlen(buf));
		}else{
			break;
		}
	}
	close(sock);
	pthread_exit((void*)0);
}

int main()
{
	int listen_sock = socket(AF_INET,SOCK_STREAM,0);
	if(listen_sock <0){
		perror("socket)";
	    exit(1);
	}
    struct sockaddr_in local;
	local.sin_family = AF_INET;
	local.sin
}

