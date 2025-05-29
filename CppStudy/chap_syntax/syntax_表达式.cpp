#include <iosfwd>
#include <ios>
#include <istream>
#include <ostream>
#include <iostream>
#include <string>
#include <typeinfo>

#include <cstdio>

#include "chap_syntax.h"
 
#define EPS 1e-10					//定义非常小的一个量EPSilon，当浮点数不大于这个值时，视为0
#define PI 3.14159

// C++语法——表达式、constexpr
/*
		 
*/

 
	virtualModule* syntax_expression_module::getInstance()		// 线程不安全的单例模式
	{
		if (nullptr != p_moduleIns)
		{
			delete p_moduleIns;
		}
		p_moduleIns = new syntax_expression_module;
		return p_moduleIns;
	}

	 
	// test0:常量表达式constexpr的简单应用
	namespace CONSTEXPR_APPLICATION1
	{
		constexpr unsigned fooConst()			// 返回值为constexpr的函数
		{
			return 9;
		}

	}


	void syntax_expression_module::test0()  
	{
		using namespace CONSTEXPR_APPLICATION1;
		int arr[fooConst()];				// fooConst()函数返回一个常量表达式，可以用来声明数组。

		std::cout << sizeof(arr) << std::endl;

	}


	void syntax_expression_module::test1()
	{
	}


	void syntax_expression_module::test2()
	{

	}



	void syntax_expression_module::test3()
	{

	}



	void syntax_expression_module::test4()
	{

	}



	void syntax_expression_module::test5()
	{

	}



	void syntax_expression_module::test6()
	{

	}



	void syntax_expression_module::test7()
	{

	}
