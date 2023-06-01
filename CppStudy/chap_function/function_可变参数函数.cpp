#include <iostream>
#include <set>
#include <string>
#include <typeinfo>
#include <algorithm>
#include <utility>
#include <initializer_list>

#include <cstdio>
#include <cstdarg>			// �ṩ��һЩ֧�ֿɱ���������ĺ�

#include "function_�ɱ��������.h"

#define EPS 1e-10					//����ǳ�С��һ����EPSilon�������������������ֵʱ����Ϊ0
#define PI 3.14159



// ֪ʶ��
/*
1. ʵ�ֺ���������Ŀ�ɱ�ķ�����
C�����п���ʹ��<stdarg.h>���ṩ�Ŀɱ�����б�va_list;
C++11�п���ʹ��initialize_list;
C++��ʹ�ñ��ģ�塪����function_����ģ�壬OOP_��ģ������ģ�顣

2. C�����еĿɱ�����б�
��������printArgs(��������test0;



*/


virtualModule* function_variadic_function_module::getInstance()		// �̲߳���ȫ�ĵ���ģʽ
{
	if (nullptr != p_moduleIns)
	{
		delete p_moduleIns;
	}
	p_moduleIns = new function_variadic_function_module;
	return p_moduleIns;
}




extern "C" {

	// �ɱ����������ѭ����ӡ���д���Ĳ�����
	static void printArgs(int num, ...)
	{
		int i, presentArg = 0;

		// 1. ����va_list�������汣���к꺯��va_start �� va_copy �� va_arg��va_end�������Ϣ
		va_list args;

		// 2. ���ú꺯��va_start()����ʹ�ñ�printfArgs�������Է��ʿɱ������
		va_start(args, num);


		// 3. ѭ����ӡ���������
		for (i = 0; i<num; i++)
		{

			// 3.1 ���ú꺯��va_arg()��ȡ�������
			// 		va_arg()���������ڲ�ָ�뵱ǰָ��Ĳ�����Ȼ��ָ�������ƶ�sizeof(int)�ľ��룬ָ����һ��������
			presentArg = va_arg(args, int);


			printf("��ǰ�����Ĳ�����presentArg == %d\n", presentArg);
		}


		// 4. ���ú꺯��va_end()����������־��
		va_end(args);

	}

}

// test0: C������ʹ��va_listʵ�ֲ����ɱ�ĺ�����
void function_variadic_function_module::test0(void)
{
	std::cout << "\n\n\n\n" << std::endl;
	std::cout << " test0: C������ʹ��va_listʵ�ֲ����ɱ�ĺ�����" << std::endl;


	printArgs(6, 1, 2, 3, 4, 5, 6);		//������ע�⺯���������Ѿ��޶��˴���Ŀɱ������Ӧ����int���͡�

}


// test1: ʹ�ó�ʼ���б�initializer_listʵ�ֿɱ��������(C++11)
namespace VARIADIC_FUNC_IL
{
	static void foo(const std::initializer_list<int>& ilist);

	// �������Ϊinitializer_list�ĺ���
	static void foo(const std::initializer_list<int>& ilist)
	{
		for (int num : ilist)
		{
			std::cout << num << std::endl;
		}
	}
}


void function_variadic_function_module::test1(void)
{
	using namespace VARIADIC_FUNC_IL;
	std::cout << "\n\n\n\n" << std::endl;
	std::cout << "'test1: ʹ�ó�ʼ���б�initializer_listʵ�ֿɱ��������(C++11)" << std::endl;

	foo({ 1,2,3,4,5 });


}


// test2: �����ñ��ģ��ʵ�ֵĿɱ�κ���ģ��(C++11)

// ���ģ��ʵ�ֵ�����������������������ֵ��
namespace VA_TEMPLATE_FUNC1
{
	template <typename T1, typename T2>
	double maxInTowNums(const T1& num1, const T2& num2)			// �����ĺ���ģ��
	{
		if (num1 >= num2)
		{
			double temp = num1;
			return temp;
		}
		else
		{
			double temp = num2;
			return temp;
		}
	}


	template <typename T>
	double Max(const T& num)		// �ݹ���ֹ
	{
		double temp = num;
		return temp;
	}


	template <typename T1, typename... Types>
	double Max(const T1& num, const Types&... args) // �ݹ����
	{
		return maxInTowNums(num, Max(args...));		// ע��������������ͬ�ĵط�ʹ����...����typename���棬���ͺ��棬��������
													// �ֱ��ʾģ����ڶ�����ͣ��β��б���ڶ�����͵Ķ���βΣ��������д��ڶ������������
	}


}


// ���ģ��ʵ�ִ�ӡ�����������print����
namespace VA_TEMPLATE_FUNC2
{

	void print()			// �ݹ���ֹ
	{						//		�ݹ���ֹ��Ϊ�޲λ���һ�����������ζ����ԡ�
		std::cout << std::endl;
		return;
	}

	template <typename T, typename... Types>
	void print(const T& firstArg, const Types&... args)
	{
		std::cout << firstArg << ",  ";
		print(args...);
	}
}


void function_variadic_function_module::test2(void)
{
	std::cout << "\n\n\n\n" << std::endl;
	std::cout << "test2: �����ñ��ģ��ʵ�ֵĿɱ�κ���ģ��(C++11)" << std::endl;

	std::cout << VA_TEMPLATE_FUNC1::Max(2, 5.11, 3.44, 100.9, 999, 12, -1) << std::endl;

	VA_TEMPLATE_FUNC2::print(23, 99.2, "i was printed by a varadic template function");


}


void function_variadic_function_module::test3(void)
{


}


void function_variadic_function_module::test4(void)
{


}


void function_variadic_function_module::test5(void)
{


}


void function_variadic_function_module::test6(void)
{}



