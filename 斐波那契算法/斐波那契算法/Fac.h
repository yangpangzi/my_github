#pragma once
////�ݹ��㷨
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
////�ݹ�Ч�ʷ���
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

//�����㷨
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