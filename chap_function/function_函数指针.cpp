#include <iostream>
#include <set>
#include <string>
#include <typeinfo>
#include <algorithm>
#include <utility>
#include <initializer_list>

#include <cstdio>
#include <cstdarg>			// 提供了一些支持可变参数函数的宏
 
#include "function_函数指针.h"

#define EPS 1e-10					//定义非常小的一个量EPSilon，当浮点数不大于这个值时，视为0
#define PI 3.14159



// 知识点
/*
	函数指针的声明语法————和函数声明格式类似，只是函数名变成了*pf

	对于某函数foo()，可以用foo或&foo表示其指针。

	回调函数
		如果一个函数并不会被显式地直接调用，而是将其函数指针传给一个caller函数，由caller函数调用，这个函数就被成为回调函数。



*/


virtualModule* function_function_pointer_module::getInstance()		// 线程不安全的单例模式
{
	if (nullptr != p_moduleIns)
	{
		delete p_moduleIns;
	}
	p_moduleIns = new function_function_pointer_module;
	return p_moduleIns;
}


// test0: 函数指针、函数指针数组。
namespace FUNC_POINTER_EXAMPLE1
{
	void foo(void)
	{
		std::cout << "function foo is called." << std::endl;
	}

	void goo(void)
	{
		std::cout << "function goo is called." << std::endl;
	}

}

void function_function_pointer_module::test0(void)
{
	using namespace FUNC_POINTER_EXAMPLE1;

	// 1. 声明函数指针数组
	void(*pfv[10])(void) = { NULL };

	// 2. 二级指针
	void(**ppfv)(void) = NULL;

	printf("\n\n\n\n");
	printf("\ttest1: 函数指针数组、二级函数指针\n");


	// 3. 
	ppfv = &pfv[0];
	*ppfv = foo;
	ppfv++;
	*ppfv = goo;


	// 4.  
	ppfv = &pfv[0];
	(**ppfv)();
	ppfv++;
	(**ppfv)();
}


// test1: 回调函数
namespace CALLBACK_FUNC
{

	namespace MY_CALCULATOR
	{
		// 有回调函数时使用别名指代相关函数指针类型，这样可以将caller函数的参数列表写的更简洁。
		using unaryOP = float(*)(const float& num);				// 一元运算函数指针类型		
		using binaryOP = float(*)(const float& num1, const float& num2);	// 二元运算函数指针类型。

		float add(const float& num1, const float& num2)
		{
			return num1 + num2;
		}

		float minus(const float& num1, const float& num2)
		{
			return num1 - num2;
		}

		float sqrt(const float& num)
		{
			return std::sqrt(num);
		}


		// 重载1——进行一元运算：
		float calculate(unaryOP pfunc, const float& num)
		{
			float number = num;
			return (*pfunc)(number);
		}


		// 重载2——进行二元运算
		float calculate(binaryOP pfunc, const float& num1, const float& num2)
		{
			float number1 = num1;
			float number2 = num2;
			return (*pfunc)(number1, number2);
		}

	}

}

void function_function_pointer_module::test1(void)
{
	using namespace CALLBACK_FUNC;

	printf("\n\n\n\n");
	printf("test1: 回调函数");

	std::cout << MY_CALCULATOR::calculate((MY_CALCULATOR::add), 1.0f, 2.0f) << std::endl;
	std::cout << MY_CALCULATOR::calculate((MY_CALCULATOR::add), 3.0f, 1.0f) << std::endl;
	std::cout << MY_CALCULATOR::calculate((MY_CALCULATOR::sqrt), 3.0f) << std::endl;

}



void function_function_pointer_module::test2(void) {}


void function_function_pointer_module::test3(void) {}


void function_function_pointer_module::test4(void) {}


void function_function_pointer_module::test5(void) {}


void function_function_pointer_module::test6(void){}



