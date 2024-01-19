#include <string>
#include<iostream>

#include <cstdio>

#include "function_����ģ��.h"

/*
	����ģ��


*/


virtualModule* function_function_template_module::getInstance()		// �̲߳���ȫ�ĵ���ģʽ
{
	if (nullptr != p_moduleIns)
	{
		delete p_moduleIns;
	}
	p_moduleIns = new function_function_template_module;
	return p_moduleIns;
}


// ����ģ��ʵ��1
namespace FUNCTION_TEMPLATE_EXAMPLE1
{
	// foo��������ģ��ʾ�����������Ͳ���T���ͷ����Ͳ���N
	template <typename T, size_t N>
	void foo(T(&arr)[N])				// ʹ�÷�Χforѭ����������ӡ�����������е�����Ԫ�ء�
	{
		for (T elem : arr) 
			std::cout << "\t" << elem; 
		std::cout << std::endl;
	}
}


// test0: ����ģ��Ļ���ʹ��
void function_function_template_module::test0(void)
{
	using namespace FUNCTION_TEMPLATE_EXAMPLE1;
	int arri[10] = {0,1,2,3,4,5,6,7,8,9};
	float arrf[5] = {1.11, 2.22, 3.33, 4.44, 5.55};

	std::cout << "\n\n\n\n" << std::endl;
	std::cout << "test0: ����ģ��Ļ���ʹ��" << std::endl;

	std::cout << "ʵ��������ģ��foo<T, N>Ȼ����ã�" << std::endl;
	foo<int, 10>(arri);
	foo<float, 5>(arrf);

	debugDisp("test0 finished.");
}


void function_function_template_module::test1(void)
{}



void function_function_template_module::test2(void)
{}



void function_function_template_module::test3(void)
{}



void function_function_template_module::test4(void)
{}



void function_function_template_module::test5(void)
{}



void function_function_template_module::test6(void)
{}