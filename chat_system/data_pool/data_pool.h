/*************************************************************************
	> File Name: data_pool.h
	> Author: yangle
	> Mail: yangle4695@gmail.com 
	> Created Time: 2016年08月24日 星期三 08时43分32秒
 ************************************************************************/
#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <semaphore.h>

class data_pool{
	public:
		data_pool(int size=128);
		void get_dat(std::string &out);
		void put_data(const std::string &in);
		~data_pool();
	private:
		std::vector<std::string>pool;
		int cap;
		int spcae_step;
		int data_step;
		sem_t space_sem;
		sem_t data_sem;			
};


