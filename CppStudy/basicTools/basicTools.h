#pragma once
#include <iostream>
#include <algorithm>
#include <cstring>					// 标准串操作
#include <iostream>				// 标准流操作
#include <limits>					// 极限
#include <cmath>					// 数据函数
#include <fstream>				// 文件输入输出
#include <cctype>					// 字符处理
#include <ctime>       				// 日期和时间函数
#include <cstdlib>					// 标准库
#include <cstdio>       			// 标准输入输出
#include <iomanip>				// 输入输出流格式设置	
#include <cstdarg> 				// 支持变长函数参数	
#include <cassert>					// 支持断言
#include <chrono>

#include <vector>
#include <map>
#include <unordered_map>

#ifndef NOMINMAX
#define NOMINMAX
#endif
#include <windows.h>
#include <io.h>

#include "AuxiliaryHeader.h"
 
 
/////////////////////////////////////////////////////////////////////////////////////////////// 辅助数据结构：
namespace AUXILIARY_DSA
{
	// 宏定义、常量
	#define DEFAULT_SIZE 1000			// 缺省元素个数
	#define DEFAULT_INFINITY 1000000	// 缺省无穷大
	#define MAX_ERROR_MESSAGE_LEN 100
	#define MAX_PATH          260
	constexpr float VF_EPS = 0.0001f;
	constexpr float VF_EPS_2 = 0.000001f;
	constexpr float VF_MAX = 10000.0f;
	constexpr float VF_MIN = -10000.0f;

	// 表示状态的枚举量
	enum Status {
		SUCCESS, FAIL, UNDER_FLOW, OVER_FLOW, RANGE_ERROR, DUPLICATE_ERROR,
		NOT_PRESENT, ENTRY_INSERTED, ENTRY_FOUND, VISITED, UNVISITED
	};


	// 模块类的基类
	struct virtualModule
	{
	protected:
		virtual void test0() {}
		virtual void test1() {}
		virtual void test2() {}
		virtual void test3() {}
		virtual void test4() {}
		virtual void test5() {}
		virtual void test6() {}
		virtual void test7() {}

	public:
		static virtualModule* p_moduleIns;
		virtual ~virtualModule() = default;
		void run(unsigned testID);
	};


	// 章节类的抽象基类
	struct virtualChap
	{
	public:
		virtualModule* pm;		// 当前查看的模块的指针，需要让caller可以访问，
								//	to be optimized: 其实更规范的作法是设计成友元，然后依然设置为protected成员
		static virtualChap* p_chapIns;
		virtual ~virtualChap();

		virtual void showModuleList() = 0;
		virtual bool selectModule(const int molEnum) = 0;
		virtual void runTest(const unsigned testID);
		bool isNullModule() const;
	};


	// Error类——自定义异常类
	class Error
	{
	private:
		char message[MAX_ERROR_MESSAGE_LEN];		// 异常信息

	public:
		Error(const char* mes = "一般性异常!");
		~Error(void) {};
		void Show() const;					// 显示异常信息
	};
	 

	// 从输入流inStream中跳过空格及制表符获取一字符
	char GetChar(std::istream& inStream = std::cin); 
}
using namespace AUXILIARY_DSA; 




	 





 





