#include <iostream>
#include <string>
#include <typeinfo>

#include <cstdio>

#include "errorHandling_�����쳣����.h"

#define EPS 1e-10					//����ǳ�С��һ����EPSilon�������������������ֵʱ����Ϊ0
#define PI 3.14159



/*
	�﷨�����쳣���׳�������
		@ �쳣���׳�throw����������ת��ʱ�����쳣ʱ��Ӧ������һ����Ӧ���쳣����ʹ��throw�׳�
		@ �쳣�Ĵ���
			# ͨ��try catch����������쳣��
			# try(�쳣)
			 
*/

 
virtualModule* errorHandling_basic_exception_module::getInstance()		// �̲߳���ȫ�ĵ���ģʽ
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
