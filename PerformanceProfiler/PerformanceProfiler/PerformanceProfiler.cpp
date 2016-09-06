#define _CRT_SECURE_NO_WARNINGS 1
#include "PerformanceProfiler.h"

void PPSection::Begin(int id)
{
	// id != -1时表示多线程场景
	if (id != -1)
	{
		lock_guard<mutex> lock(_mtx);

		// 分别统计线程和总的花费时间和调用次数
		if (_refCountMap[id]++ == 0)
			_beginTimeMap[id] = clock();
	}
	else
	{
		if (_totalRefCount++ == 0)
			_totalBeginTime = clock();
	}
}

void PPSection::End(int id)
{
	if (id != -1)
	{
		lock_guard<mutex> lock(_mtx);

		if (--_refCountMap[id] == 0)
			_costTimeMap[id] += clock() - _beginTimeMap[id];

		++_callCountMap[id];
	}
	else
	{
		if (--_totalRefCount == 0)
			_totalCostTime += clock() - _totalBeginTime;
		++_totalCallCount;
	}
}

PPSection* PerformanceProfiler::CreateSection(const char* filename, const char* function,
	size_t line, const char* desc)
{
	PPNode node(filename, function, line, desc);
	PPSection* section = NULL;

	// RAII
	lock_guard<mutex> lock(_mtx);

	PP_MAP::iterator it = _ppMap.find(node);
	if (it != _ppMap.end())
	{
		section = it->second;
	}
	else
	{
		section = new PPSection;
		_ppMap.insert(pair<PPNode, PPSection*>(node, section));
	}

	return section;
}

void PerformanceProfiler::OutPut()
{
	int options = ConfigManager::GetInstance()->GetOptions();
	if (options & SAVE_TO_CONSOLE)
	{
		ConsoleSaveAdapter csa;
		_OutPut(csa);
	}

	if (options & SAVE_TO_FILE)
	{
		FileSaveAdapter fsa("PerformanceProfilerReport.txt");
		_OutPut(fsa);
	}
}

void  PerformanceProfiler::_OutPut(SaveAdapter& sa)
{
	vector<PP_MAP::iterator> vInfos;
	PP_MAP::iterator ppIt = _ppMap.begin();
	while (ppIt != _ppMap.end())
	{
		PPSection* section = ppIt->second;
		map<int, LongType>::iterator timeIt;
		timeIt = section->_costTimeMap.begin();
		while (timeIt != section->_costTimeMap.end())
		{
			section->_totalCostTime += timeIt->second;
			section->_totalCallCount += section->_callCountMap[timeIt->first];

			++timeIt;
		}
		vInfos.push_back(ppIt);
		++ppIt;
	}
	struct SortByCostTime
	{
		bool operator()(PP_MAP::iterator l
		, PP_MAP::iterator r) const
		{
			return l->second->_totalCostTime
				> r->second->_totalCostTime;
		}
	};
	// 按花费时间排序
	sort(vInfos.begin(), vInfos.end(), SortByCostTime());

	int num = 1;
	//PP_MAP::iterator ppIt = _ppMap.begin();

	for (size_t i = 0; i < vInfos.size(); ++i)
	{
		ppIt = vInfos[i];
		const PPNode& node = ppIt->first;
		PPSection* section = ppIt->second;

		// node信息
		sa.Save("No.%d, Desc:%s\n", num++, node._desc.c_str());
		sa.Save("Filename:%s, Line:%d, Function:%s\n"
			, node._filename.c_str()
			, node._line
			, node._function.c_str());

		// section信息
		map<int, LongType>::iterator timeIt;
		timeIt = section->_costTimeMap.begin();
		while (timeIt != section->_costTimeMap.end())
		{
			int id = timeIt->first;
			sa.Save("ThreadId:%d, CostTime:%.2f s, CallCount:%lld\n"
				, id
				, (double)timeIt->second / 1000
				, section->_callCountMap[id]);

			section->_totalCostTime += timeIt->second;
			section->_totalCallCount += section->_callCountMap[id];

			++timeIt;
		}

		sa.Save("TotalCostTime:%.2f s, TotalCallCount:%lld, AverCostTime:%lld ms\n\n"
			, (double)section->_totalCostTime / 1000
			, section->_totalCallCount
			, section->_totalCostTime / section->_totalCallCount);

		++ppIt;
	}
}