#include <iostream>
#include <set>
#include <string>
#include <typeinfo>
#include <algorithm>
#include <utility>
#include <initializer_list>

#include <cstdio>
#include <cstdarg>			// 提供了一些支持可变参数函数的宏

#include "function_可变参数函数.h"

#define EPS 1e-10					//定义非常小的一个量EPSilon，当浮点数不大于这个值时，视为0
#define PI 3.14159



// 知识点
/*
1. 实现函数参数数目可变的方法：
	C语言中可以使用<stdarg.h>中提供的可变参数列表va_list;
	C++11中可以使用initialize_list;
	C++中使用变参模板——见function_函数模板，OOP_类模板两个模块。

	2. C语言中的可变参数列表
	详见下面的printArgs(）函数，test0;

*/


virtualModule* function_variadic_function_module::getInstance()		// 线程不安全的单例模式
{
	if (nullptr != p_moduleIns)
	{
		delete p_moduleIns;
	}
	p_moduleIns = new function_variadic_function_module;
	return p_moduleIns;
}




extern "C" {

	// 可变参数函数，循环打印所有传入的参数。
	static void printArgs(int num, ...)
	{
		int i, presentArg = 0;

		// 1. 创建va_list对象，里面保存有宏函数va_start 、 va_copy 、 va_arg及va_end所需的信息
		va_list args;

		// 2. 调用宏函数va_start()——使得本printfArgs函数可以访问可变参数。
		va_start(args, num);


		// 3. 循环打印输入参数。
		for (i = 0; i<num; i++)
		{

			// 3.1 调用宏函数va_arg()获取输入参数
			// 		va_arg()——返回内部指针当前指向的参数，然后指针往后移动sizeof(int)的距离，指向下一个参数。
			presentArg = va_arg(args, int);


			printf("当前读到的参数：presentArg == %d\n", presentArg);
		}


		// 4. 调用宏函数va_end()——结束标志。
		va_end(args);

	}

}

// test0: C语言中使用va_list实现参数可变的函数。
void function_variadic_function_module::test0()
{
	std::cout << "\n\n\n\n" << std::endl;
	std::cout << " test0: C语言中使用va_list实现参数可变的函数。" << std::endl;


	printArgs(6, 1, 2, 3, 4, 5, 6);		//！！！注意函数定义中已经限定了传入的可变参数都应该是int类型。

}


// test1: 使用初始化列表initializer_list实现可变参数函数(C++11)
namespace VARIADIC_FUNC_IL
{
	static void foo(const std::initializer_list<int>& ilist);

	// 输入参数为initializer_list的函数
	static void foo(const std::initializer_list<int>& ilist)
	{
		for (int num : ilist)
		{
			std::cout << num << std::endl;
		}
	}
}


void function_variadic_function_module::test1()
{
	using namespace VARIADIC_FUNC_IL;
	std::cout << "\n\n\n\n" << std::endl;
	std::cout << "'test1: 使用初始化列表initializer_list实现可变参数函数(C++11)" << std::endl;

	foo({ 1,2,3,4,5 });


}


// test2: 测试用变参模板实现的可变参函数模板(C++11)

// 变参模板实现的求任意个任意类型数的最大值。
namespace VA_TEMPLATE_FUNC1
{
	template <typename T1, typename T2>
	double maxInTowNums(const T1& num1, const T2& num2)			// 辅助的函数模板
	{
		if (num1 >= num2)
		{
			double temp = num1;
			return temp;
		}
		else
		{
			double temp = num2;
			return temp;
		}
	}


	template <typename T>
	double Max(const T& num)		// 递归终止
	{
		double temp = num;
		return temp;
	}


	template <typename T1, typename... Types>
	double Max(const T1& num, const Types&... args) // 递归递推
	{
		return maxInTowNums(num, Max(args...));		// 注意至少有三个不同的地方使用了...——typename后面，类型后面，变量后面
													// 分别表示模板存在多个类型，形参列表存在多个类型的多个形参，函数体中存在多个变量参数。
	}


}


// 变参模板实现打印任意个变量的print函数
namespace VA_TEMPLATE_FUNC2
{

	void print()			// 递归终止
	{						//		递归终止设为无参或者一个参数的情形都可以。
		std::cout << std::endl;
		return;
	}

	template <typename T, typename... Types>
	void print(const T& firstArg, const Types&... args)
	{
		std::cout << firstArg << ",  ";
		print(args...);
	}
}


void function_variadic_function_module::test2()
{
	std::cout << "\n\n\n\n" << std::endl;
	std::cout << "test2: 测试用变参模板实现的可变参函数模板(C++11)" << std::endl;

	std::cout << VA_TEMPLATE_FUNC1::Max(2, 5.11, 3.44, 100.9, 999, 12, -1) << std::endl;

	VA_TEMPLATE_FUNC2::print(23, 99.2, "i was printed by a varadic template function");


}


void function_variadic_function_module::test3()
{


}


void function_variadic_function_module::test4()
{


}


void function_variadic_function_module::test5()
{


}


void function_variadic_function_module::test6()
{}



