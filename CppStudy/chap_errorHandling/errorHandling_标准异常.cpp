#include <iosfwd>
#include <ios>
#include <istream>
#include <ostream>
#include <iostream>
#include <string>
#include <typeinfo>
#include <stdexcept>

#include <cstdio>

#include "errorHandling_标准异常.h"
 
#define EPS 1e-10					//定义非常小的一个量EPSilon，当浮点数不大于这个值时，视为0
#define PI 3.14159


// std::exception::what()————返回异常解释字符串
/*.
	描述：
		返回一个c风格字符串，即char*，内容是对异常的解释。

	函数原型：
		virtual const char* what() const throw();  (C++11 前)
		virtual const char* what() const noexcept; (C++11 起)

*/



// 标准异常类：std:exception
/*
	定义于头文件<exception>
	基类： std::exception
	规范编程的情形下，所有自定义的异常类都应该继承自std::exception类，并重写what()函数

	派生类：
	logic_error
	invalid_argument		参数不合法
	domain_error
	length_error
	out_of_range			超出范围
	future_error(C++11)
	bad_optional_access(C++17)
	runtime_error
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
	bad_cast
	bad_any_cast(C++17)
	bad_weak_ptr(C++11)
	bad_function_call(C++11)
	bad_alloc
	bad_array_new_length(C++11)
	bad_errorHandling
	ios_base::failure(C++11 前)
	bad_variant_access(C++17)


*/





virtualModule* errorHandling_std_exception_module::getInstance()		// 线程不安全的单例模式
{
	if (nullptr != p_moduleIns)
	{
		delete p_moduleIns;
	}
	p_moduleIns = new errorHandling_std_exception_module;
	return p_moduleIns;
}

 

// test0: 对标准异常的测试
namespace TEST_STD_EXCEPTION1
{
	class classFoo
	{
		// 封装了一个字符串和一个数字的类，用于展示函数功能。
	public:
		std::string str;
		int age;

		classFoo() = default;

		classFoo(const std::string& str1, const int& age1) :str(str1)
		{
			if (age1 < 0)
				throw(std::out_of_range("异常——out of range: 输入年龄应该不小于0."));			// 当输入age1参数小于0时，抛出超出范围异常
			this->age = age1;
		}

		~classFoo() = default;

		void setAge(int age1)
		{
			if (age1 < 0)
			{
				throw(std::out_of_range("异常——out of range: classFoo::setAge(int)不允许传递小于0的整数参数。"));
			}
			this->age = age1;
		}
	};
}


void errorHandling_std_exception_module::test0(void)
{
	using namespace TEST_STD_EXCEPTION1;
	std::cout << "\n\n\n\n" << std::endl;
	std::cout << "test0: 对标准异常的测试" << std::endl;

	classFoo foo1;

	try
	{
		classFoo foo2("xiaohong", -1);		// 测试一个有异常风险的语句：
	}
	catch (std::exception e)
	{
		std::cout << "使用try-catch语句捕获了异常，异常解释字符串：e.what() == " << e.what() << std::endl;
	}

	try
	{
		foo1.setAge(-12);
	}
	catch (std::exception e)
	{
		std::cout << "使用try-catch语句捕获了异常，异常解释字符串：e.what() == " << e.what() << std::endl;
	}
}


void errorHandling_std_exception_module::test1(void)
{

}


void errorHandling_std_exception_module::test2(void) {}



void errorHandling_std_exception_module::test3(void) {}



void errorHandling_std_exception_module::test4(void) {}



void errorHandling_std_exception_module::test5(void) {}



void errorHandling_std_exception_module::test6(void) {}

