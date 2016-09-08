/*************************************************************************
	> File Name: data_pool.cpp
	> Author: yangle
	> Mail: yangle4695@gmail.com 
	> Created Time: 2016年08月24日 星期三 08时48分41秒
 ************************************************************************/

#include "data_pool.h"

data_pool::data_pool(int size)
		:cap(size)
		 ,pool(size)
{
	space_step =0;
	data_step=0;
	sem_init(&space_sem,0,cap);
	sem_init(&data_sem,0,0);

}

void data_pool::get_data(std::string &out)
{
	sem_wait(&data_sem);
	//pthread_lock();
	out = pool[data_step++];
	data_step %= cap;
	sem_post(&space_sem);

}
void data_pool::put_data(const std::string &in)
{
	sem_wait(&space_sem);
	pool[space_step++] =in;
	space_step %= cap;
	sem_post(&data_sem);

}
data_pool::~data_pool()
{
	sem_destroy(&space_sem);
	sem_destroy(&data_sem);
}

