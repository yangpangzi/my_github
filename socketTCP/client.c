/*************************************************************************
	> File Name: server.c
	> Author: yangle
	> Mail: yangle4695@gmail.com 
	> Created Time: 2016年08月05日 星期五 05时59分18秒
 ************************************************************************/

#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/types.h>          /* See NOTES */
#include <sys/socket.h>
#include <stdlib.h>
#include<string.h>
#include <pthread.h>
#include<arpa/inet.h>
#include <netinet/in.h>
#include <signal.h>
#include <unistd.h>

void usage(const char *proc)
{
	printf("%s [ip][port]\n",proc);
}

int main(int argc,char *argv[])
{
	if(argc !=3){
		usage(argv[0]);
			return 3;
	}
	int conn = socket(AF_INET,SOCK_STREAM,0);
		if(conn < 0){
			perror("socket");
			return 1;
		}
	struct sockaddr_in remote;
	remote.sin_family = AF_INET;
	remote.sin_port = htons(atoi(argv[2]));
	remote.sin_addr.s_addr = inet_addr(argv[1]);

	if( connect(conn, (struct sockaddr*)&remote,sizeof(remote))< 0){
		perror("connect");
		return 2;
	}
	char buf[1024];

	while(1){
		ssize_t _s = read(0,buf,sizeof(buf)-1);
		if(_s >0){
			buf[_s]='\0';
			write(conn,buf,strlen(buf));
			read(conn,buf,sizeof(buf)-1);
			printf("server echo: %s\n",buf);

		}
	}
return 0;

}
