/*************************************************************************
	> File Name: client.c
	> Author: yangle
	> Mail: yangle4695@gmail.com 
	> Created Time: 2016年08月05日 星期五 01时04分32秒
 ************************************************************************/
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<signal.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<pthread.h>
#include <sys/types.h>
#include <sys/socket.h>

void collect_child(int sig)
{
	while(waitpid(-1,0,WNOHANG)>0){
		printf("collect child done...\n");
	}
}
void* handler_data(void *arg)
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
		perror("socket");
	    exit(1);
	}
    struct sockaddr_in local;
	local.sin_family = AF_INET;
	local.sin_port = htons(8080);
	local.sin_addr.s_addr = htonl(INADDR_ANY);//0
	if(bind(listen_sock,(struct sockaddr*)&local,sizeof(local))< 0){
	perror("bind");
	exit(2);
	}
	if(listen(listen_sock,5) < 0){
       perror("listen");
	   exit(3);

	}
	struct sockaddr_in peer;
	socklen_t len =sizeof(peer);

	signal(SIGCHLD,collect_child);
	while(1){
		int new_fd = accept(listen_sock,\
					(struct sockaddr*)&peer,&len);
		if(new_fd > 0){
			pthread_t id;
			pthread_create(&id,NULL,handler_data,(void*)new_fd);
			pthread_detach(id);

		}
	}
	return 0;
}

