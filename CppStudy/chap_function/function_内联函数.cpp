#pragma once
#include <iostream>
#include <set>
#include <string>
#include <typeinfo>
#include <algorithm>
#include <utility>
#include <initializer_list>

#include <cstdio>
#include <cstdarg>			// 提供了一些支持可变参数函数的宏

#include "function_内联函数.h"

#define EPS 1e-10					//定义非常小的一个量EPSilon，当浮点数不大于这个值时，视为0
#define PI 3.14159



// 知识点
/*


*/


virtualModule* function_inline_function_module::getInstance()		// 线程不安全的单例模式
{
	if (nullptr != p_moduleIns)
	{
		delete p_moduleIns;
	}
	p_moduleIns = new function_inline_function_module;
	return p_moduleIns;
}


void function_inline_function_module::test0() {}


void function_inline_function_module::test1() {}


void function_inline_function_module::test2() {}


void function_inline_function_module::test3() {}


void function_inline_function_module::test4() {}


void function_inline_function_module::test5() {}


void function_inline_function_module::test6() {}



