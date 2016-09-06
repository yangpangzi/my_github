
#include "sql_api.h"
#include <stdio.h>
#include <string.h>
//arg="name =zhangsan&school=sust&hobby=coding"
void myinsert(char *arg)
{
	sql_api *sql=new sql_api;
	 string cols="(student_name,student_age,student_school,register_time)";

	 char *buf[5];
	 buf[4]=NULL;
	 int index =3;
	 char *end =arg+strlen(arg)-1;
	 while(end >arg){
		 if(*end =='='){
			 buf[index--]=end+1;
		 }
		 if(*end =='&'){
			 *end='\0';
		 }
		 end--;
	 }
	 string data ="(\"";
	 data +=buf[0];
	 data +="\",";
	 data +=buf[1];
	 data +=",\"";
	 data +=buf[2];
	 data +="\",";
	 data +=buf[3];
	 data +=")";
	
printf("%s\n", cols.c_str());
printf("%s\n", data.c_str());
	 sql->my_connect_mysql();
	 sql ->my_insert(cols,data);
	 delete sql;

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
	myinsert(arg);
	return 0;
}
