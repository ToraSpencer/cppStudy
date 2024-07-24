#pragma once

#include <iostream>
#include <fstream>
#include <sstream>			// �ַ�����

#include <iterator>
#include <utility>

#include <string>
#include <array>
#include <vector>
#include <list>
#include <deque>
#include <stack>
#include <queue>
#include <set>
#include <unordered_set>
#include <map>
#include <unordered_map>
#include <initializer_list>
#include <bitset>	

#include <algorithm>
#include <functional>
#include <numeric>
#include <limits>				// �ṩstd::numeric_limits<>ģ��

#include <cmath>
#include <random>
#include <ctime>
#include <typeinfo>
#include <type_traits>

#include <windows.h> 
#include <atlstr.h>				// ����CString�ࡣ����microsoft ATL(�ģ���avtive template library)
#include <io.h>


#include <memory>

#include <thread>					// c++�߳�֧�ֿ�
#include <mutex>
#include <atomic>			// ԭ������

#include <cassert>			// ����


// #define USE_BOOST

// boost
#ifdef  USE_BOOST
#include <boost/tuple/tuple.hpp>
#endif  




// �ڴ��CPU���ӽӿ���Ҫ��һЩͷ�ļ���
#ifdef WIN32 
#include <psapi.h>   
#include <direct.h>
#include <process.h>
#else
#include <sys/stat.h>
#include <sys/sysinfo.h>
#include <sys/time.h>
#include <unistd.h>
#endif


// cinolib�еĶ��̲߳���forѭ����
template<typename Func>
void PARALLEL_FOR(unsigned int  beg, unsigned int  end, \
	const Func& func, const unsigned int serial_if_less_than = 12)
{
	/*
		PARALLEL_FOR(
			unsigned int   beg,                                     ��ʼԪ������
			unsigned int  end,                                      βԪ������
			const unsigned int  serial_if_less_than,      �����Ҫ�����Ԫ�ز�С�ڸ�ֵ����ʹ�ò��л���
			const Func & func										����Ԫ�صĺ����ӣ�
			)
	*/
	unsigned int elemCount = end - beg + 1;

	if (elemCount < serial_if_less_than)
		for (unsigned int i = beg; i < end; ++i)
			func(i);
	else
	{
		// ȷ������߳�����
		const static unsigned n_threads_hint = std::thread::hardware_concurrency();
		const static unsigned n_threads = (n_threads_hint == 0u) ? 8u : n_threads_hint;

		// forѭ���ķ�Χ�ֽ�ɼ��Σ�
		unsigned int slice = (unsigned int)std::round(elemCount / static_cast<double>(n_threads));
		slice = std::max(slice, 1u);

		// �̺߳�����
		auto subTraverse = [&func](unsigned int head, unsigned int tail)
		{
			for (unsigned int k = head; k < tail; ++k)
				func(k);
		};

		// �����̳߳أ�ִ�в���forѭ����
		std::vector<std::thread> pool;              // �̳߳أ�
		pool.reserve(n_threads);
		unsigned int head = beg;
		unsigned int tail = std::min(beg + slice, end);
		for (unsigned int i = 0; i + 1 < n_threads && head < end; ++i)
		{
			pool.emplace_back(subTraverse, head, tail);
			head = tail;
			tail = std::min(tail + slice, end);
		}
		if (head < end)
			pool.emplace_back(subTraverse, head, end);

		// �߳�ͬ����
		for (std::thread& t : pool)
		{
			if (t.joinable())
				t.join();
		}
	}
}


// ��β���forѭ��������������Ĳ���ʹ��std::tuple���룻
template<typename Func, typename paramTuple>
void PARALLEL_FOR(unsigned int  beg, unsigned int  end, const Func& func,\
	const paramTuple& pt, const unsigned int serial_if_less_than = 12)
{
	/*
		PARALLEL_FOR(
			unsigned int   beg,                                     ��ʼԪ������
			unsigned int  end,                                      βԪ������
			const unsigned int  serial_if_less_than,      �����Ҫ�����Ԫ�ز�С�ڸ�ֵ����ʹ�ò��л���
			const paramTuple& pt								�������������������
			const Func & func										����Ԫ�صĺ����ӣ�
			)
	*/
	unsigned int elemCount = end - beg + 1;

	if (elemCount < serial_if_less_than)
		for (unsigned int i = beg; i < end; ++i)
			func(i, pt);
	else
	{
		// ȷ������߳�����
		const static unsigned n_threads_hint = std::thread::hardware_concurrency();
		const static unsigned n_threads = (n_threads_hint == 0u) ? 8u : n_threads_hint;

		// forѭ���ķ�Χ�ֽ�ɼ��Σ�
		unsigned int slice = (unsigned int)std::round(elemCount / static_cast<double>(n_threads));
		slice = std::max(slice, 1u);

		// �̺߳�����
		auto subTraverse = [&func, &pt](unsigned int head, unsigned int tail)
		{
			for (unsigned int k = head; k < tail; ++k)
				func(k, pt);
		};

		// �����̳߳أ�ִ�в���forѭ����
		std::vector<std::thread> pool;              // �̳߳أ�
		pool.reserve(n_threads);
		unsigned int head = beg;
		unsigned int tail = std::min(beg + slice, end);
		for (unsigned int i = 0; i + 1 < n_threads && head < end; ++i)
		{
			pool.emplace_back(subTraverse, head, tail);
			head = tail;
			tail = std::min(tail + slice, end);
		}
		if (head < end)
			pool.emplace_back(subTraverse, head, end);

		// �߳�ͬ����
		for (std::thread& t : pool)
		{
			if (t.joinable())
				t.join();
		}
	}
}


// �Զ���pointer-like�ַ�����
struct myString
{
private:
	const char* pc;
public:
	myString() = delete;
	myString(const char* pc0) :pc(pc0) {}
	const char* c_str() const
	{
		return this->pc;
	}
};


// �Զ���Ƚ�������ǰ��С�ں���ʱ����true
auto myComparer = [](const myString& str1, const myString& str2) ->bool
{
	if (strlen(str1.c_str()) < strlen(str2.c_str())) 
		return true; 
	else 
		return false; 
};


auto dispMyString = [](const myString& str)
{
	std::cout << str.c_str() << std::endl;
};


// ���뺯���ӻ���ָ�����stl����
template<typename T, typename F>
void traverseSTL(T& con, F f)
{
	std::for_each(con.begin(), con.end(), f);
	std::cout << std::endl;
}


// ���뺯���ӻ���ָ�����std::map, std::unordered_map��
template<typename mapType, typename F>
void traverseSTLmap(mapType& m, F f)
{
	std::for_each(m.begin(), m.end(), f);
	std::cout << std::endl;
}


// �������
template<typename T, typename F>
void revTraverseSTL(T& con, F f)
{
	std::for_each(con.rbegin(), con.rend(), f);
	std::cout << std::endl;
}


// �����ӡ�����ӡstd::cout֧�ֵ����ͱ�����
template <typename	T>
class disp 
{
public:
	void operator()(const T& arg) 
	{
		std::cout << arg << ", ";
	}
};


// �����ӡ�����ӡstd::pair
template <typename pairType>
class dispPair
{
public:
	void operator()(const pairType& p)
	{
		std::cout << "(" << p.first << ", " << p.second << "), ";
	}
};


template <typename T>
void templateTest(const T& arg);
