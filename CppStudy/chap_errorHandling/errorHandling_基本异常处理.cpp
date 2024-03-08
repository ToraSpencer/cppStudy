#include <iostream>
#include <string>
#include <typeinfo>

#include <cstdio>

#include "errorHandling_基本异常处理.h"

#define EPS 1e-10					//定义非常小的一个量EPSilon，当浮点数不大于这个值时，视为0
#define PI 3.14159



/*
	语法——异常的抛出、处理
		@ 异常的抛出throw——函数运转的时候发生异常时，应该生成一个对应的异常对象，使用throw抛出
		@ 异常的处理
			# 通过try catch语句来处理异常。
			# try(异常)
			 
*/

 
virtualModule* errorHandling_basic_exception_module::getInstance()		// 线程不安全的单例模式
{
	if (nullptr != p_moduleIns)
	{
		delete p_moduleIns;
	}
	p_moduleIns = new errorHandling_basic_exception_module;
	return p_moduleIns;
}



 
void errorHandling_basic_exception_module::test0(void) {}
 

void errorHandling_basic_exception_module::test1(void) {}


void errorHandling_basic_exception_module::test2(void) {}


void errorHandling_basic_exception_module::test3(void) {}


void errorHandling_basic_exception_module::test4(void) {}



void errorHandling_basic_exception_module::test5(void) {}



void errorHandling_basic_exception_module::test6(void) {}
