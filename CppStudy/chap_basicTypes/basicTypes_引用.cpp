#include <iostream>
#include <cstdio>
#include <string>
#include <typeinfo>

#include "basicTypes_����.h"

#define EPS 1e-10					 
#define PI 3.14159



// ֪ʶ��
/*
		����
				��һ������ı�����
				���ñ����ʼ�����������������ٳ�ʼ����
				���úͳ�ʼֵ�ǰ�(bind)��һ��ģ���������в�����������

		���ô���(passed by reference)
				ָ�������β����������͡� 
				��ʱ�β���ʵ�εı������βκ�ʵ�ε�ֵ����һ�𣬲����п����ķ�����
				���Ӧ��ֵ����(passed by value)�У�ʵ�ε�ֵ�������βΡ�
				�����β�����Ϊ��const����ʱ��ֻ�ܰ���ֵ����"hello",123������������������ֵ���Ͳ�����Ϊ��ʵ��



		
				
			 

*/


virtualModule* basicTypes_reference_module::getInstance()		// �̲߳���ȫ�ĵ���ģʽ
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
	int& num2 = num1;								// ����num2��num1��ֵ����һ��
	std::cout << "num2 == " << num2 << std::endl;

	num2 = 100;											// ʹ������num2���ı����num1��ֵ��
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


