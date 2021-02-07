#include <iostream>
#include <string>
#include <typeinfo>

#include <cstdio>

#include "DSA_图.h"

#define EPS 1e-10					//定义非常小的一个量EPSilon，当浮点数不大于这个值时，视为0
#define PI 3.14159


virtualModule* DSA_graph_module::getInstance()		// 线程不安全的单例模式
{
	if (nullptr != p_moduleIns)
	{
		delete p_moduleIns;
	}
	p_moduleIns = new DSA_graph_module;
	return p_moduleIns;
}



 
void DSA_graph_module::test0(void) {}
 

void DSA_graph_module::test1(void) {}


void DSA_graph_module::test2(void) {}


void DSA_graph_module::test3(void) {}


void DSA_graph_module::test4(void) {}



void DSA_graph_module::test5(void) {}



void DSA_graph_module::test6(void) {}
