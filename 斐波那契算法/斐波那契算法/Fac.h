#pragma once
////递归算法
//int fib(int n)
//{
//	int last = 0;
//	int sum = 1;
//	if (n <= 2)
//	{
//		return 1;
//	}
//	else
//	{
//		return fib(n - 1) + fib(n - 2);
//	}
//}
////递归效率分析
//long fib1(int n, int* arr)
//{
//	arr[n]++;
//	if (n <= 2)
//	{
//		return 1;
//	}
//	else
//	{
//		return fib1(n - 1, arr) + fib1(n - 2, arr);
//	}
//}

//迭代算法
int fib(int n)
{
	int last = 0;
	int sum = 1;
	for (int i = 0; i <= n;i++)
	{
		int temp = sum;
		sum = sum + last;
		last = temp;
	}
	return sum;
	
}