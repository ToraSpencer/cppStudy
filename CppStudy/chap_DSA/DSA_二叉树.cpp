#include <iostream>
#include <string>
#include <typeinfo>

#include <cstdio>

#include "DSA_������.h"

#define EPS 1e-10					//����ǳ�С��һ����EPSilon�������������������ֵʱ����Ϊ0
#define PI 3.14159


virtualModule* DSA_binary_tree_module::getInstance()		// �̲߳���ȫ�ĵ���ģʽ
{
	if (nullptr != p_moduleIns)
	{
		delete p_moduleIns;
	}
	p_moduleIns = new DSA_binary_tree_module;
	return p_moduleIns;
}



 
void DSA_binary_tree_module::test0(void) {}
 

void DSA_binary_tree_module::test1(void) {}


void DSA_binary_tree_module::test2(void) {}


void DSA_binary_tree_module::test3(void) {}


void DSA_binary_tree_module::test4(void) {}



void DSA_binary_tree_module::test5(void) {}



void DSA_binary_tree_module::test6(void) {}
