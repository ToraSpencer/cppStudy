#include <iostream>
#include <string>
#include <typeinfo>
#include <cstdio>


#include "basicTypes_��������.h"


#define EPS 1e-10					//����ǳ�С��һ����EPSilon�������������������ֵʱ����Ϊ0
#define PI 3.14159



// ֪ʶ��
/*
			��������ȫ�ֱ������Զ���ʼ�����ֲ��������ᡣ




*/




virtualModule* basicTypes_builtin_types_module::getInstance()		// �̲߳���ȫ�ĵ���ģʽ
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


