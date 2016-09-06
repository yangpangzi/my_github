#include "sql_api.h"
#include <string.h>
//arg="name=zhangsan&school=sust&hobby=coding"
void myselect()
{
	sql_api *sql=new sql_api;
	sql ->my_connect_mysql();
	sql ->my_select();
	delete sql;
}

int main()
{
	myselect();
	return 0;
}
