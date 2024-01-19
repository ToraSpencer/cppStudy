#include <ctime>
#include <cstdio>
#include <typeinfo>
#include <chrono>

#include <iostream>
#include <string>
#include <typeinfo>

#include <cstdio>

#include "stdlib_工具库.h"


#ifdef WIN32
#include <windows.h>
#endif

 
#define EPS 1e-10								//定义非常小的一个量EPSilon，当浮点数不大于这个值时，视为0
#define PI 3.14159


// C++标准库——工具库
/*
	工具库大致可以分为两类：语言支持库、通用库

	内容：
		智能指针与分配器
		日期和时间
		函数对象，hash (C++11)
		字符串转换 (C++17)
		工具函数
		pair， tuple (C++11)
		optional (C++17)， any (C++17)
		variant (C++17)，format (C++20)
 
*/


virtualModule* stdlib_tools_module::getInstance()		// 线程不安全的单例模式
{
	if (nullptr != p_moduleIns)
	{
		delete p_moduleIns;
	}
	p_moduleIns = new stdlib_tools_module;
	return p_moduleIns;
}


// struct tm——<time.h>定义的一个结构体，方便于时间表示
void stdlib_tools_module::test0()
{
	// C++ 标准库没有提供所谓的日期类型，继承了C语言用于日期和时间操作的结构和函数
	
	// 1. windows系统提供的计时接口——GetTickCount();
	DWORD start = GetTickCount();			// typedef unsigned long DWORD

	// 2. C语言标准库中的计时接口——clock()——程序开始到此刻处理器时钟所记录的时间，单位为毫秒
	clock_t start_c = clock();
	Sleep(2000);
	clock_t end_c = clock();

	DWORD end = GetTickCount();
	DWORD interval = end - start;
	std::cout << interval << std::endl;				// windows
	std::cout << end_c - start_c << std::endl;		// c语言

	// 3. C语言标准库——time()——获取1970.1.1 00:00:00到此刻经历的秒数。					 
	time_t now = time(0);
	std::cout << "1970 到目前经过秒数:" << now << std::endl;

	// 4. C语言标准库——格式化时间日期数据localtime()
	/*
		std::tm* localtime( const std::time_t *time );
		不是线程安全的，建议用WINDOWS提供的localtime_s(),或linux提供的localtime_r()
	*/

	//  C标准库中定义的日期时间结构体： struct tm;
	tm *ltm = nullptr;

	ltm = localtime(&now);			// 将毫秒数数据转换为tm对象。
	std::cout << "年: " << 1900 + ltm->tm_year << std::endl;
	std::cout << "月: " << 1 + ltm->tm_mon << std::endl;
	std::cout << "日: " << ltm->tm_mday << std::endl;
	std::cout << "时间: " << ltm->tm_hour << ":";
	std::cout << ltm->tm_min << ":";
	std::cout << ltm->tm_sec << std::endl;

	struct tm now_tm;
	localtime_s(&now_tm, &now);
	std::cout << "年: " << 1900 + now_tm.tm_year << std::endl;
	std::cout << "月: " << 1 + now_tm.tm_mon << std::endl;
	std::cout << "日: " << now_tm.tm_mday << std::endl;
	std::cout << "时间: " << now_tm.tm_hour << ":";
	std::cout << now_tm.tm_min << ":";
	std::cout << now_tm.tm_sec << std::endl;
}


// c++11标准计时库<chrono>
void stdlib_tools_module::test1() 
{
	/*
		<chrono>中提供了三种时钟：
				steady_clock 
						是单调的时钟，相当于教练手中的秒表；
						只会增长，适合用于记录程序耗时；
				system_clock 
						是系统的时钟；
						因为系统的时钟可以修改；甚至可以网络对时； 所以用系统时间计算时间差可能不准。
				high_resolution_clock 
						是当前系统能够提供的最高精度的时钟；
						它也是不可以修改的。
						相当于 steady_clock 的高精度版本。	
	*/
	using namespace std::chrono; 
	time_point<steady_clock> start, end;			// std::chrono::time_point——表示一个时刻
	microseconds dur;								// using microseconds = std::chrono::duration<long long, micro>——表示一段时间；

	//循环1：
	start = steady_clock::now();
	long int num = 10000000;
	for (int i = 0; i != num; i++)
	{
		int* b = new int[10]();
		delete[] b;
	}

	// 1. now()方法——获取当前时刻
	end = steady_clock::now();

	// 2. duration_cast<>()——
	std::chrono::duration<double, std::micro> dur0 = end - start;			// 直接相减，得到浮点型的时长
	dur = duration_cast<microseconds>(dur0);										// cast成整型的市场；
	debugDisp("dur0 == ", dur0.count(), ", 单位ms");
	debugDisp("dur == ", dur.count(), ", 单位ms");

	//循环2
	start = steady_clock::now();
	int num2 = num >> 1;
	for (int i = 0; i != num2; i++)
	{
		int* b = new int[10]();
		delete[] b;
	}
	for (int i = num2; i != num; i++)
	{
		int* b = new int[10]();
		delete[] b;
	}
	end = steady_clock::now();
	dur = duration_cast<microseconds>(end - start);
	debugDisp("程序2花费了", static_cast<double>(dur.count()) * \
		microseconds::period::num / microseconds::period::den, "秒");

	//循环3
	start = steady_clock::now();
	end = steady_clock::now();
	dur = duration_cast<microseconds>(end - start);
	debugDisp("程序3花费了", static_cast<double>(dur.count()) * \
		microseconds::period::num / microseconds::period::den, "秒");

	debugDisp("test3() finished.");
}


void stdlib_tools_module::test2() {}


void stdlib_tools_module::test3() {}


void stdlib_tools_module::test4() {}


void stdlib_tools_module::test5() {}


void stdlib_tools_module::test6() {}

