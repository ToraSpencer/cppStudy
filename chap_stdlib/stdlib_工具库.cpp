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
	// windows系统提供的计时接口——GetTickCount();
	DWORD start = GetTickCount();			// typedef unsigned long DWORD

	// C语言标准库中的计时接口——clock()——程序开始到此刻处理器时钟所记录的时间，单位为毫秒
	clock_t start_c = clock();
	Sleep(2000);
	clock_t end_c = clock();

	DWORD end = GetTickCount();
	DWORD interval = end - start;
	std::cout << interval << std::endl;				// windows
	std::cout << end_c - start_c << std::endl;		// c语言


	// C语言标准库——time()——获取1970.1.1 00:00:00到此刻经历的秒数。					 
	time_t now = time(0);

	std::cout << "1970 到目前经过秒数:" << now << std::endl;


	//  C语言标准库——格式化时间日期数据localtime()
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


void stdlib_tools_module::test1() {}


void stdlib_tools_module::test2() {}


void stdlib_tools_module::test3() {}


void stdlib_tools_module::test4() {}


void stdlib_tools_module::test5() {}


void stdlib_tools_module::test6() {}

