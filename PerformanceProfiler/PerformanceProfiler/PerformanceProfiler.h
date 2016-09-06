#pragma once

#include <iostream>
#include <string>
#include <map>
#include <algorithm>

// C++11
#include <unordered_map>
#include <thread>
#include <mutex>

#include<time.h>
#include <assert.h>

#ifdef _WIN32
	#include <windows.h>
#else
	#include <pthread.h>
#endif // _WIN32

using namespace std;

typedef long long LongType;

/////////////////////////////////////////////////////////////////

// 单例的基类 -- 饿汉模式
template<class T>
class Singleton
{
public:
	static T* GetInstance()
	{
		assert(_sInstance);
		return _sInstance;
	}

protected:
	static T* _sInstance;
};

template<class T>
T* Singleton<T>::_sInstance = new T;

class SaveAdapter
{
public:
	virtual void Save(const char* format, ...) = 0;
};

class ConsoleSaveAdapter : public SaveAdapter
{
public:
	virtual void Save(const char* format, ...)
	{
		va_list args;
		va_start(args, format);
		vfprintf(stdout, format, args);
		va_end(args);
	}
};

class FileSaveAdapter : public SaveAdapter
{
public:
	FileSaveAdapter(const char* filename)
	{
		_fout = fopen(filename, "w");
		assert(_fout);
	}
	~FileSaveAdapter()
	{
		if (_fout)
		{
			fclose(_fout);
		}
	}
	virtual void Save(const char* format, ...)
	{
		va_list args;
		va_start(args, format);
		vfprintf(_fout, format, args);
		va_end(args);
	}

protected:
	// 防拷贝
	FileSaveAdapter(FileSaveAdapter&);
	FileSaveAdapter&operator=(FileSaveAdapter&);

protected:
	FILE* _fout;
};

// 
//class SqlSaveadpter : public SaveAdapter
//{};

////////////////////////////////////////////////////////////////
// 配置管理
enum ConfigOptions
{
	NONE = 0,
	PERFORMANCE_PROFILER = 1,
	SAVE_TO_CONSOLE = 2,
	SAVE_TO_FILE = 4,
	SORT_BY_COSTTIME = 8,
	SORT_BY_CALLCOUNT = 16,
};

class ConfigManager : public Singleton<ConfigManager>
{
public:
	void SetOptions(int options)
	{
		_options = options;
	}

	void AddOption(int option)
	{
		_options |= option;
	}

	void DelOption(int option)
	{
		_options &= (~option);
	}

	int GetOptions()
	{
		return _options;
	}

protected:
	friend class Singleton<ConfigManager>;

	ConfigManager()
		:_options(NONE)
	{}

	ConfigManager(const ConfigManager&);
	ConfigManager& operator=(const ConfigManager&);

protected:
	int _options;
};


/////////////////////////////////////////////////////////////////
// PerformanceProfiler
struct  PPNode
{
	string _filename;
	string _function;
	size_t _line;
	string _desc;		//附加描述信息

	PPNode(const char* filename, const char* function,
		size_t line, const char* desc)
		:_filename(filename)
		, _function(function)
		, _line(line)
		, _desc(desc)
	{}

	bool operator==(const PPNode& node) const
	{
		if (_line == node._line
			&& _function == node._function
			&& _filename == node._filename)
		{
			return true;
		}

		return false;
	}
};

struct PPSection
{
	PPSection()
		:_totalCostTime(0)
		,_totalCallCount(0)
		,_totalRefCount(0)
	{}

	void Begin(int id);
	void End(int id);

	// <id, 统计信息>
	map<int, LongType> _beginTimeMap;
	map<int, LongType> _costTimeMap;
	map<int, LongType> _callCountMap;
	map<int, LongType> _refCountMap;

	LongType _totalBeginTime;		// 开始时间
	LongType _totalCostTime;		// 花费时间
	LongType _totalCallCount;		// 调用次数
	LongType _totalRefCount;		// 引用计数，解决递归问题

	mutex _mtx;
};

// PPNode的计算哈希值的仿函数
struct PPNodeHash
{
	static size_t BKDRHash(const char * str)
	{
		unsigned int seed = 131; // 31 131 1313 13131 131313
		unsigned int hash = 0;
		while (*str)
		{
			hash = hash * seed + (*str++);
		}
		return (hash & 0x7FFFFFFF);
	}
	size_t operator()(const PPNode& node) const
	{
		static string hash;
		hash = node._desc;
		hash += node._function;

		return BKDRHash(hash.c_str());
	}
};

class PerformanceProfiler : public Singleton<PerformanceProfiler>
{
	// O(1)
	typedef unordered_map<PPNode, PPSection*, PPNodeHash> PP_MAP;
public:
	PPSection* CreateSection(const char* filename, const char* function,
		size_t line, const char* desc);
	void OutPut();

protected:
	void  _OutPut(SaveAdapter& sa);
	friend class Singleton<PerformanceProfiler>;

	PerformanceProfiler(){}
	PerformanceProfiler(const PerformanceProfiler&);
	PerformanceProfiler& operator=(const PerformanceProfiler&);

protected:
	PP_MAP _ppMap;  // 统计资源信息的容器
	mutex _mtx;
};

struct Report
{
	~Report()
	{
		PerformanceProfiler::GetInstance()->OutPut();
	}
};
static Report report;

static int GetTheadId()
{
#ifdef _WIN32
	return GetCurrentThreadId();
#else
	return thread_self();
#endif // _WIN32
}


// 剖析单线程场景
#define PERFORMANCE_PROFILER_EE_ST_BEGIN(sign, desc) \
	PPSection* ps##sign = NULL;						 \
	if (ConfigManager::GetInstance()->GetOptions() & PERFORMANCE_PROFILER)\
	{												 \
		ps##sign = PerformanceProfiler::GetInstance()->CreateSection(__FILE__, __FUNCTION__, __LINE__, desc); \
		ps##sign->Begin(-1);						 \
	}

#define PERFORMANCE_PROFILER_EE_ST_END(sign)	\
	if (ps##sign)								\
		ps##sign->End(-1);

// 剖析多线程场景
#define PERFORMANCE_PROFILER_EE_MT_BEGIN(sign, desc) \
	PPSection* ps##sign = NULL;						 \
	if (ConfigManager::GetInstance()->GetOptions() & PERFORMANCE_PROFILER)\
	{												 \
		ps##sign = PerformanceProfiler::GetInstance()->CreateSection(__FILE__, __FUNCTION__, __LINE__, desc); \
		ps##sign->Begin(GetTheadId());						 \
	}

#define PERFORMANCE_PROFILER_EE_MT_END(sign)	\
	if (ps##sign)								\
		ps##sign->End(GetTheadId());


#define SET_CONFIG_OPTIONS(option)				\
	ConfigManager::GetInstance()->SetOptions(option);