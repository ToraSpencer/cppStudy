#pragma once
#include <iostream>
#include <algorithm>
#include <cstring>					// 标准串操作
#include <iostream>					// 标准流操作
#include <limits>					// 极限
#include <cmath>					// 数据函数
#include <fstream>					// 文件输入输出
#include <cctype>					// 字符处理
#include <ctime>       				// 日期和时间函数
#include <cstdlib>					// 标准库
#include <cstdio>       			// 标准输入输出
#include <iomanip>					// 输入输出流格式设置	
#include <cstdarg> 					// 支持变长函数参数	
#include <cassert>					// 支持断言
 

// 表示状态的枚举量
enum Status {
	SUCCESS, FAIL, UNDER_FLOW, OVER_FLOW, RANGE_ERROR, DUPLICATE_ERROR,
	NOT_PRESENT, ENTRY_INSERTED, ENTRY_FOUND, VISITED, UNVISITED
};


// 宏定义
#define DEFAULT_SIZE 1000			// 缺省元素个数
#define DEFAULT_INFINITY 1000000	// 缺省无穷大
#define MAX_ERROR_MESSAGE_LEN 100


// 从输入流inStream中跳过空格及制表符获取一字符
char GetChar(std::istream &inStream = std::cin);


class Error
{
private:
	char message[MAX_ERROR_MESSAGE_LEN];		// 异常信息

public:
	Error(const char *mes = "一般性异常!");
	~Error(void) {};
	void Show() const;					// 显示异常信息
};


// 交换元素值
template <class ElemType >
void Swap(ElemType &e1, ElemType &e2)
{
	ElemType temp;		// 临时变量
						// 循环赋值实现交换e1, e2
	temp = e1;	e1 = e2;  e2 = temp;
}


// 打印数组
template<class ElemType>
void Display(ElemType elem[], int n)
{
	for (int i = 0; i < n; i++)
	{	// 显示数组elem
		cout << elem[i] << "  ";
	}
	cout << endl;
}


// 打印单个元素
template <class ElemType>
void Write(const ElemType &e)
{
	cout << e << "  ";
}


// 模块类的抽象基类
struct virtualModule
{
protected:
	virtual void test0() = 0;
	virtual void test1() = 0;
	virtual void test2() = 0;
	virtual void test3() = 0;
	virtual void test4() = 0;
	virtual void test5() = 0;
	virtual void test6() = 0;

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


// 反向遍历
template<typename T, typename F>
void revTraverseSTL(T& con, F f)
{
	std::for_each(con.rbegin(), con.rend(), f);
	std::cout << std::endl;
}


// lambda——打印std::cout支持的类型变量。
template <typename T>
auto disp = [](const T& arg)
{
	std::cout << arg << ", ";
};


// 自定义pointer-like字符串类
struct myString
{
private:
	const char*	pc;
public:
	myString() = delete;
	myString(const char* pc0) :pc(pc0) {}
	myString(const myString& str);	// 应该自己实现拷贝构造函数、重载赋值运算符，以实现深拷贝。否则系统分配浅拷贝的拷贝构造函数。
	

	
	
	const char* c_str() const
	{
		return this->pc;
	}
};



 





