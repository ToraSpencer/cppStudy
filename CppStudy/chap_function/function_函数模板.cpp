#include <string>
#include<iostream>

#include <cstdio>

#include "function_函数模板.h"

/*
	函数模板


*/


virtualModule* function_function_template_module::getInstance()		// 线程不安全的单例模式
{
	if (nullptr != p_moduleIns)
	{
		delete p_moduleIns;
	}
	p_moduleIns = new function_function_template_module;
	return p_moduleIns;
}


// 函数模板实例1
namespace FUNCTION_TEMPLATE_EXAMPLE1
{
	// foo——函数模板示例，带有类型参数T，和非类型参数N
	template <typename T, size_t N>
	void foo(T(&arr)[N])				// 使用范围for循环，遍历打印出传入数组中的所有元素。
	{
		for (T elem : arr) 
			std::cout << "\t" << elem; 
		std::cout << std::endl;
	}
}


// test0: 函数模板的基本使用
void function_function_template_module::test0()
{
	using namespace FUNCTION_TEMPLATE_EXAMPLE1;
	int arri[10] = {0,1,2,3,4,5,6,7,8,9};
	float arrf[5] = {1.11, 2.22, 3.33, 4.44, 5.55};

	std::cout << "\n\n\n\n" << std::endl;
	std::cout << "test0: 函数模板的基本使用" << std::endl;

	std::cout << "实例化函数模板foo<T, N>然后调用：" << std::endl;
	foo<int, 10>(arri);
	foo<float, 5>(arrf);

	debugDisp("test0 finished.");
}


void function_function_template_module::test1()
{}



void function_function_template_module::test2()
{}



void function_function_template_module::test3()
{}



void function_function_template_module::test4()
{}



void function_function_template_module::test5()
{}



void function_function_template_module::test6()
{}