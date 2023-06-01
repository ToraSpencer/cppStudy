#include <iostream>
#include <set>
#include <string>
#include <typeinfo>
#include <algorithm>
#include <utility>
#include <initializer_list>

#include <cstdio>
#include <cstdarg>			// �ṩ��һЩ֧�ֿɱ���������ĺ�
 
#include "function_����ָ��.h"

#define EPS 1e-10					//����ǳ�С��һ����EPSilon�������������������ֵʱ����Ϊ0
#define PI 3.14159



// ֪ʶ��
/*
	����ָ��������﷨���������ͺ���������ʽ���ƣ�ֻ�Ǻ����������*pf

	����ĳ����foo()��������foo��&foo��ʾ��ָ�롣

	�ص�����
		���һ�����������ᱻ��ʽ��ֱ�ӵ��ã����ǽ��亯��ָ�봫��һ��caller��������caller�������ã���������ͱ���Ϊ�ص�������



*/


virtualModule* function_function_pointer_module::getInstance()		// �̲߳���ȫ�ĵ���ģʽ
{
	if (nullptr != p_moduleIns)
	{
		delete p_moduleIns;
	}
	p_moduleIns = new function_function_pointer_module;
	return p_moduleIns;
}


// test0: ����ָ�롢����ָ�����顣
namespace FUNC_POINTER_EXAMPLE1
{
	void foo(void)
	{
		std::cout << "function foo is called." << std::endl;
	}

	void goo(void)
	{
		std::cout << "function goo is called." << std::endl;
	}

}

void function_function_pointer_module::test0(void)
{
	using namespace FUNC_POINTER_EXAMPLE1;

	// 1. ��������ָ������
	void(*pfv[10])(void) = { NULL };

	// 2. ����ָ��
	void(**ppfv)(void) = NULL;

	printf("\n\n\n\n");
	printf("\ttest1: ����ָ�����顢��������ָ��\n");


	// 3. 
	ppfv = &pfv[0];
	*ppfv = foo;
	ppfv++;
	*ppfv = goo;


	// 4.  
	ppfv = &pfv[0];
	(**ppfv)();
	ppfv++;
	(**ppfv)();
}


// test1: �ص�����
namespace CALLBACK_FUNC
{

	namespace MY_CALCULATOR
	{
		// �лص�����ʱʹ�ñ���ָ����غ���ָ�����ͣ��������Խ�caller�����Ĳ����б�д�ĸ���ࡣ
		using unaryOP = float(*)(const float& num);				// һԪ���㺯��ָ������		
		using binaryOP = float(*)(const float& num1, const float& num2);	// ��Ԫ���㺯��ָ�����͡�

		float add(const float& num1, const float& num2)
		{
			return num1 + num2;
		}

		float minus(const float& num1, const float& num2)
		{
			return num1 - num2;
		}

		float sqrt(const float& num)
		{
			return std::sqrt(num);
		}


		// ����1��������һԪ���㣺
		float calculate(unaryOP pfunc, const float& num)
		{
			float number = num;
			return (*pfunc)(number);
		}


		// ����2�������ж�Ԫ����
		float calculate(binaryOP pfunc, const float& num1, const float& num2)
		{
			float number1 = num1;
			float number2 = num2;
			return (*pfunc)(number1, number2);
		}

	}

}

void function_function_pointer_module::test1(void)
{
	using namespace CALLBACK_FUNC;

	printf("\n\n\n\n");
	printf("test1: �ص�����");

	std::cout << MY_CALCULATOR::calculate((MY_CALCULATOR::add), 1.0f, 2.0f) << std::endl;
	std::cout << MY_CALCULATOR::calculate((MY_CALCULATOR::add), 3.0f, 1.0f) << std::endl;
	std::cout << MY_CALCULATOR::calculate((MY_CALCULATOR::sqrt), 3.0f) << std::endl;

}



void function_function_pointer_module::test2(void) {}


void function_function_pointer_module::test3(void) {}


void function_function_pointer_module::test4(void) {}


void function_function_pointer_module::test5(void) {}


void function_function_pointer_module::test6(void){}



