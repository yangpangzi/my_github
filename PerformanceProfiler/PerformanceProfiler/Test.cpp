#include "PerformanceProfiler.h"

//PerformanceProfiler pp;
//
//void TestPP1()
//{
//	PPSection* ps1 = pp.CreateSection(__FILE__, __FUNCTION__, __LINE__, "����");
//	ps1->Begin();
//	// ����
//	Sleep(1000);
//	ps1->End();
//
//	PPSection* ps2 = pp.CreateSection(__FILE__, __FUNCTION__, __LINE__, "�м��߼�");
//	ps2->Begin();
//
//	// �м��߼�-Ȩ�޴���
//	Sleep(500);
//
//	ps2->End();
//
//	PPSection* ps3 = pp.CreateSection(__FILE__, __FUNCTION__, __LINE__, "���ݿ�");
//	ps3->Begin();
//
//	// ���ݿ����
//	Sleep(1500);
//
//	ps3->End();
//}
//

void TestSingleThead()
{
	PERFORMANCE_PROFILER_EE_ST_BEGIN(network,"����s");
	// ����
	Sleep(200);
	PERFORMANCE_PROFILER_EE_ST_END(network);

	PERFORMANCE_PROFILER_EE_ST_BEGIN(mid, "�м��߼�s");
	// �м��߼�
	Sleep(300);

	PERFORMANCE_PROFILER_EE_ST_END(mid);

	PERFORMANCE_PROFILER_EE_ST_BEGIN(sql, "���ݿ�s");
	// ���ݿ�
	Sleep(400);

	PERFORMANCE_PROFILER_EE_ST_END(sql);
}

// �ݹ�
LongType Fib(LongType n)
{
	PERFORMANCE_PROFILER_EE_ST_BEGIN(in, "����");

	LongType ret = n;
	if (n < 2)
	{
		ret = n;
	}
	else
	{
		ret = Fib(n - 1) + Fib(n - 2);
	}

	PERFORMANCE_PROFILER_EE_ST_END(in);

	return ret;
}

void TestFib()
{
	PERFORMANCE_PROFILER_EE_ST_BEGIN(out, "����");

	Fib(28);

	PERFORMANCE_PROFILER_EE_ST_END(out);
}

void Fun(size_t n)
{
	while (n--)
	{
		PERFORMANCE_PROFILER_EE_MT_BEGIN(network, "����m");
		Sleep(100);
		PERFORMANCE_PROFILER_EE_MT_END(network);

		PERFORMANCE_PROFILER_EE_MT_BEGIN(mid, "�м��߼�m");
		Sleep(200);
		PERFORMANCE_PROFILER_EE_MT_END(mid);

		PERFORMANCE_PROFILER_EE_MT_BEGIN(sql, "���ݿ�m");
		Sleep(300);
		PERFORMANCE_PROFILER_EE_MT_END(sql);
	}
}

// ���ݲ�׼ȷ
// �̰߳�ȫ
void TestMultiThread()
{
	thread t1(Fun, 5);
	thread t2(Fun, 4);
	thread t3(Fun, 3);

	t1.join();
	t2.join();
	t3.join();
}

int main()
{
	//TestPP1();
	//TestPP1();
	//TestPP1();

	//TestPP2();

	
	SET_CONFIG_OPTIONS(PERFORMANCE_PROFILER
		| SAVE_TO_FILE
		| SAVE_TO_CONSOLE
		| SORT_BY_COSTTIME);
	TestFib();
	TestMultiThread();
	TestSingleThead();
	//PerformanceProfiler::GetInstance()->OutPut();

	return 0;
}