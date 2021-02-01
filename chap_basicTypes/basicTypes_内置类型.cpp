#include <iostream>
#include <string>
#include <typeinfo>
#include <cstdio>


#include "basicTypes_内置类型.h"


#define EPS 1e-10					//定义非常小的一个量EPSilon，当浮点数不大于这个值时，视为0
#define PI 3.14159



// 知识点
/*
			内置类型全局变量会自动初始化，局部变量不会。




*/




virtualModule* basicTypes_builtin_types_module::getInstance()		// 线程不安全的单例模式
{
	if (nullptr != p_moduleIns)
	{
		delete p_moduleIns;
	}
	p_moduleIns = new basicTypes_builtin_types_module;
	return p_moduleIns;
}



 
// test0:  
void basicTypes_builtin_types_module::test0(void) {}

void basicTypes_builtin_types_module::test1(void) {}


void basicTypes_builtin_types_module::test2(void) {}


void basicTypes_builtin_types_module::test3(void) {}


void basicTypes_builtin_types_module::test4(void) {}


void basicTypes_builtin_types_module::test5(void) {}


void basicTypes_builtin_types_module::test6(void) {}


