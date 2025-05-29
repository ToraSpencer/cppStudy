#include <iostream>
#include <string>
#include <typeinfo>

#include <cstdio>

#include "DSA_顺序表.h"

#define EPS 1e-10					//定义非常小的一个量EPSilon，当浮点数不大于这个值时，视为0
#define PI 3.14159


virtualModule* DSA_sequence_list_module::getInstance()		// 线程不安全的单例模式
{
	if (nullptr != p_moduleIns)
	{
		delete p_moduleIns;
	}
	p_moduleIns = new DSA_sequence_list_module;
	return p_moduleIns;
}



 
void DSA_sequence_list_module::test0() {}
 

void DSA_sequence_list_module::test1() {}


void DSA_sequence_list_module::test2() {}


void DSA_sequence_list_module::test3() {}


void DSA_sequence_list_module::test4() {}



void DSA_sequence_list_module::test5() {}



void DSA_sequence_list_module::test6() {}
