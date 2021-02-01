#include <iostream>
#include <cstdio>
#include <string>
#include <typeinfo>

#include "basicTypes_引用.h"

#define EPS 1e-10					 
#define PI 3.14159



// 知识点
/*
		引用
				是一个对象的别名。
				引用必须初始化，不能先声明，再初始化。
				引用和初始值是绑定(bind)在一起的，这个过程中不发生拷贝。

		引用传递(passed by reference)
				指函数的形参是引用类型。 
				此时形参是实参的别名，形参和实参的值绑定在一起，不会有拷贝的发生。
				相对应的值传递(passed by value)中，实参的值拷贝给形参。
				函数形参类型为非const引用时，只能绑定左值，像"hello",123这样的字面量不是左值，就不能作为其实参



		
				
			 

*/


virtualModule* basicTypes_reference_module::getInstance()		// 线程不安全的单例模式
{
	if (nullptr != p_moduleIns)
	{
		delete p_moduleIns;
	}
	p_moduleIns = new basicTypes_reference_module;
	return p_moduleIns;
}



// test0:  
void basicTypes_reference_module::test0(void)
{
	int num1 = 99;
	int& num2 = num1;								// 引用num2和num1的值绑定在一起。
	std::cout << "num2 == " << num2 << std::endl;

	num2 = 100;											// 使用引用num2来改变变量num1的值。
	std::cout << "num1 == " << num1 << std::endl;

}


// test1: 
void basicTypes_reference_module::test1(void)
{

}


void basicTypes_reference_module::test2(void)
{

}


void basicTypes_reference_module::test3(void)
{

}


void basicTypes_reference_module::test4(void)
{

}


void basicTypes_reference_module::test5(void)
{

}


void basicTypes_reference_module::test6(void)
{

}


