#pragma once
#include <iostream>
#include <set>
#include <string>
#include <typeinfo>
#include <algorithm>
#include <utility>
#include <initializer_list>

#include <cstdio>
#include <cstdarg>			// �ṩ��һЩ֧�ֿɱ���������ĺ�

#include "function_��������.h"

#define EPS 1e-10					//����ǳ�С��һ����EPSilon�������������������ֵʱ����Ϊ0
#define PI 3.14159



// ֪ʶ��
/*


*/


virtualModule* function_inline_function_module::getInstance()		// �̲߳���ȫ�ĵ���ģʽ
{
	if (nullptr != p_moduleIns)
	{
		delete p_moduleIns;
	}
	p_moduleIns = new function_inline_function_module;
	return p_moduleIns;
}


void function_inline_function_module::test0(void) {}


void function_inline_function_module::test1(void) {}


void function_inline_function_module::test2(void) {}


void function_inline_function_module::test3(void) {}


void function_inline_function_module::test4(void) {}


void function_inline_function_module::test5(void) {}


void function_inline_function_module::test6(void) {}



