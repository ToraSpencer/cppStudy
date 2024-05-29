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
#include <windows.h>
#include <io.h>
 
 
/////////////////////////////////////////////////////////////////////////////////////////////// 辅助数据结构：
namespace AUXILIARY
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


	// 自定义pointer-like字符串类
	struct myString
	{
	private:
		const char* pc;
	public:
		myString() = delete;
		myString(const char* pc0) :pc(pc0) {}
		myString(const myString& str);	// 应该自己实现拷贝构造函数、重载赋值运算符，以实现深拷贝。否则系统分配浅拷贝的拷贝构造函数。

		const char* c_str() const
		{
			return this->pc;
		}
	};

	// 从输入流inStream中跳过空格及制表符获取一字符
	char GetChar(std::istream& inStream = std::cin); 
}
using namespace AUXILIARY;


/////////////////////////////////////////////////////////////////////////////////////////////// debug和disp接口：
namespace MY_DEBUG
{
	// 函数子baseTypePrinter——打印基本类型变量
	class baseTypePrinter
	{
	public:
		baseTypePrinter() = default;

		template<typename T>
		void operator()(const T& arg)
		{
			std::cout << arg << "\t";
		}

	};


	// 函数子pairPrinter————功能是打印pair对象
	class pairPrinter
	{
	private:
		unsigned int count = 0;

	public:
		pairPrinter() = default;

		template<typename T1, typename T2>
		void operator()(const std::pair<T1, T2>& p)
		{
			std::cout << "\t(" << p.first << ", " << p.second << ")";
			this->count++;
		}

		unsigned int getCount(void)
		{
			return this->count;
		}
	};


	// 传入函数子或函数指针遍历stl容器
	template<typename T, typename F>
	void traverseSTL(T& con, F f)
	{
		std::for_each(con.begin(), con.end(), f);
		std::cout << std::endl;
	}


	// 传入函数子或函数指针遍历std::map, std::unordered_map等
	template<typename mapType, typename F>
	void traverseSTLmap(mapType& m, F f)
	{
		std::for_each(m.begin(), m.end(), f);
		std::cout << std::endl;
	}


	// 反向遍历stl容器
	template<typename T, typename F>
	void revTraverseSTL(T& con, F f)
	{
		std::for_each(con.rbegin(), con.rend(), f);
		std::cout << std::endl;
	}


	// 函数子——打印std::cout支持的类型变量。
	template <typename	T>
	class disp
	{
	public:
		void operator()(const T& arg)
		{
			std::cout << arg << ", ";
		}
	};


	// 函数子——打印std::pair
	template <typename pairType>
	class dispPair
	{
	public:
		void operator()(const pairType& p)
		{
			std::cout << "(" << p.first << ", " << p.second << "), ";
		}
	};



	static void debugDisp()			// 递归终止
	{						//		递归终止设为无参或者一个参数的情形都可以。
		std::cout << std::endl;
		return;
	}

	template <typename T, typename... Types>
	static void debugDisp(const T& firstArg, const Types&... args)
	{
		std::cout << firstArg << " ";
		debugDisp(args...);
	}


	// 基于std::chrono的自定义计时器
	using namespace std::chrono;
	class tiktok
	{
	private:
		tiktok() = default;
		tiktok(const tiktok&) {}
		~tiktok() = default;

	public:
		time_point<steady_clock> startTik;
		time_point<steady_clock> endTik;
		unsigned recordCount;
		std::vector<time_point<steady_clock>> records;

		static tiktok& getInstance()
		{
			static tiktok tt_instance;
			return tt_instance;
		}

		// 开始计时
		void start()
		{
			this->startTik = steady_clock::now();
			this->recordCount = 0;
			this->records.clear();
		}

		// 结束计时，控制台上打印时间间隔，单位为秒
		void endCout(const char* str)
		{
			this->endTik = steady_clock::now();
			microseconds duration = duration_cast<microseconds>(this->endTik - this->startTik);
			std::cout << str << static_cast<double>(duration.count()) * \
				microseconds::period::num / microseconds::period::den << std::endl;
		}

		// 结束计时，返回std::chrono::microseconds类型的时间间隔；
		microseconds endGetCount()
		{
			this->endTik = steady_clock::now();
			microseconds duration = duration_cast<microseconds>(this->endTik - this->startTik);
			return duration;
		}

		// 结束计时，时间间隔写入到fileName的文本文件中，单位为秒；
		bool endWrite(const char* fileName, const char* str)
		{
			this->endTik = steady_clock::now();
			std::ofstream file(fileName, std::ios_base::out | std::ios_base::app);
			if (!file)
				return false;
			microseconds duration = duration_cast<microseconds>(this->endTik - this->startTik);
			file << str << static_cast<double>(duration.count()) * \
				microseconds::period::num / microseconds::period::den << std::endl;
			file.close();
			return true;
		}

		// 按下秒表，记录此刻的时刻，保存在this->records向量中；
		void takeArecord()
		{
			this->records.push_back(steady_clock::now());
			recordCount++;
		}
	};
}
using namespace MY_DEBUG;




	 





 





