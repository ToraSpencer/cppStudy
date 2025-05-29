#include <iostream>
#include <string>
#include <typeinfo>

#include <cstdio>

// 若定义了宏NDEBUG，则assert()会被禁用。需要在#include <cassert>之前取消NDEBUG的定义；
#undef NDEBUG
#include <cassert>
#include "errorHandling_断言.h"

#define EPS 1e-10					//定义非常小的一个量EPSilon，当浮点数不大于这个值时，视为0
#define PI 3.14159



// 断言
/*
	1. 基本信息：
	函数原型——void assert( int expression );
	作用——简单地说是如果它的条件返回错误，则终止程序执行
	具体过程——先计算表达式 expression，如果其值为假（即为0），那么它先向stderr打印一条出错信息，然后通过调用 abort 来终止程序运行。

	2. assert是用来避免显而易见的错误的，而不是处理异常的。
		错误和异常是不一样的，错误是不应该出现的，异常是不可避免的。
		c语言异常可以通过条件判断来处理，其它语言有各自的异常处理机制。
 
*/

 
virtualModule* errorHandling_assert_module::getInstance()		// 线程不安全的单例模式
{
	if (nullptr != p_moduleIns)
	{
		delete p_moduleIns;
	}
	p_moduleIns = new errorHandling_assert_module;
	return p_moduleIns;
}




void errorHandling_assert_module::test0() 
{
	int num;
	std::cout << "please input a positive integer" << std::endl;
	std::cin >> num;

	assert(num > 0 );					// 若定义了宏NDEBUG，则assert()会被禁用；
	std::cout << "num == " << num << std::endl;			// 如果输入的值等于0的话，程序不会运行到这里，在这之前就被abort了。

}
 

void errorHandling_assert_module::test1() {}


void errorHandling_assert_module::test2() {}


void errorHandling_assert_module::test3() {}


void errorHandling_assert_module::test4() {}



void errorHandling_assert_module::test5() {}



void errorHandling_assert_module::test6() {}
