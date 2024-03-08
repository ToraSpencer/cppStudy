#include <iosfwd>
#include <ios>
#include <istream>
#include <ostream>
#include <iostream>
#include <string>
#include <typeinfo>
#include <stdexcept>

#include <cstdio>

#include "errorHandling_��׼�쳣.h"
 
#define EPS 1e-10					//����ǳ�С��һ����EPSilon�������������������ֵʱ����Ϊ0
#define PI 3.14159


// std::exception::what()�������������쳣�����ַ���
/*.
	������
		����һ��c����ַ�������char*�������Ƕ��쳣�Ľ��͡�

	����ԭ�ͣ�
		virtual const char* what() const throw();  (C++11 ǰ)
		virtual const char* what() const noexcept; (C++11 ��)

*/



// std:exception�ࡪ����׼�쳣��
/*
	������ͷ�ļ�<exception>
	���ࣺ std::exception
	�淶��̵������£������Զ�����쳣�඼Ӧ�ü̳���std::exception�࣬����дwhat()����

	�����ࣺ
		logic_error�����߼��쳣
				invalid_argument		�������Ϸ�
				domain_error
				length_error
				out_of_range			������Χ
				future_error(C++11)

		runtime_error��������ʱ�쳣
				range_error
				overflow_error
				underflow_error
				regex_error(C++11)
				system_error(C++11)
						ios_base::failure(C++11)
						filesystem::filesystem_error(C++17)
				nonexistent_local_time(C++20)
				ambiguous_local_time(C++20)
				tx_errorHandling(TM TS)
				format_error(C++20)

		bad_typeid

		bad_cast��������װ���쳣
				bad_any_cast(C++17)

		bad_weak_ptr(C++11)

		bad_function_call(C++11)

		bad_alloc������̬�ڴ�����쳣
				bad_array_new_length(C++11)

		bad_errorHandling

		ios_base::failure(C++11 ǰ)

		bad_variant_access(C++17)

		bad_optional_access(C++17)

*/
 

// noexcept�ؼ���
/*
	����ָʾ�����Ƿ�����׳��쳣��
	�����ڸ�֪������ĳ�����������׳��쳣���Ա��ڱ������Գ�������Ż����������ɸ���Ч�Ļ����룻
*/


virtualModule* errorHandling_std_exception_module::getInstance()		// �̲߳���ȫ�ĵ���ģʽ
{
	if (nullptr != p_moduleIns) 
		delete p_moduleIns;

	p_moduleIns = new errorHandling_std_exception_module;
	return p_moduleIns;
}


// test0: �Ա�׼�쳣�Ĳ���
namespace TEST_STD_EXCEPTION
{

	class classFoo
	{
		// ��װ��һ���ַ�����һ�����ֵ��࣬����չʾ�������ܡ�
	public:
		std::string str;
		int age;

		classFoo() = default;

		classFoo(const std::string& str1, const int& age1) :str(str1)
		{
			if (age1 < 0)
				throw(std::out_of_range("�쳣����out of range: ��������Ӧ�ò�С��0."));			// ������age1����С��0ʱ���׳�������Χ�쳣
			this->age = age1;
		}

		~classFoo() = default;

		void setAge(int age1)
		{
			if (age1 < 0)
			{
				throw(std::out_of_range("�쳣����out of range: classFoo::setAge(int)��������С��0������������"));
			}
			this->age = age1;
		}
	};


	void foo(const int num)	
	{
		if (num < 0)
			throw(std::out_of_range("invalid input."));

		debugDisp("foo(): input number ==", num);
	}
	 
}


void errorHandling_std_exception_module::test0(void)
{
	using namespace TEST_STD_EXCEPTION;
	std::cout << "\n\n\n\n" << std::endl;
	std::cout << "test0: �Ա�׼�쳣�Ĳ���" << std::endl;

	classFoo foo1;
	try
	{
		foo(-1);
	}
	catch (const std::exception& e)
	{
		debugDisp("ʹ��try-catch��䲶�����쳣���쳣�����ַ�����e.what() == ", e.what());
	}

	try
	{
		classFoo foo2("xiaohong", -1);		// ����һ�����쳣���յ���䣺
	}
	catch (const std::exception& e)
	{
		debugDisp("ʹ��try-catch��䲶�����쳣���쳣�����ַ�����e.what() == ", e.what());
	}

	try
	{
		foo1.setAge(-12);
	}
	catch (const std::exception& e)
	{
		debugDisp("ʹ��try-catch��䲶�����쳣���쳣�����ַ�����e.what() == ", e.what());
	}
}

  
void errorHandling_std_exception_module::test1(void) {}


void errorHandling_std_exception_module::test2(void) {}



void errorHandling_std_exception_module::test3(void) {}



void errorHandling_std_exception_module::test4(void) {}



void errorHandling_std_exception_module::test5(void) {}



void errorHandling_std_exception_module::test6(void) {}

