/*************************************************************************
	> File Name: cgi_math.c
	> Author: yangle
	> Mail: yangle4695@gmail.com 
	> Created Time: 2016年08月17日 星期三 08时41分18秒
 ************************************************************************/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

static void mymath(char *arg)
{
	//data1=100&data2=200
	char *data[3];
	data[2]=NULL;
	int i=1;

	char *end =arg + strlen(arg)-1;
	while(end >arg)
	{
		if(*end=='='){
			data[i--]=end+1;

		}
		if(*end=='&'){
			*end='\0';
		}
		end--;
	}
	printf("<html>\n");
	printf("<h1>");
	printf("%s + %s =%d",data[0],data[1],atoi(data[0]+atoi(data[1])));
	printf("</h1>\n");
	printf("</html>\n");
}

int main()
{
	char method[1024];
	char arg[1024];
	char content_len[1024];
	int len=-1;
	if(getenv("REQUEST_METHOD")){
		strcpy(method,getenv("REQUEST_METHOD"));
	}
	if(strcasecmp(method,"GET")==0){
		if(getenv("QUERY_STRING")){		
			strcpy(arg,getenv("QUERY_STRING"));
					}
	}else{
	if(getenv("CONTENT_LENGTH")){
	strcpy(content_len,getenv("CONTENT_LENGTH"));
	len =atoi(content_len);
	}
	int i=0;
	for(;i<len;i++){
	read(0,&arg[i],1);
	}
	arg[i]='\0';
	}
	mymath(arg);
	return 0;
}
