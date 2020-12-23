#include <iostream>
#include <cmath>
#include <stdexcept>

#include <exception>
#include <string>
#include <vector>

#include <cstdio>

#include "example.h"


#define EPS 1e-6

using namespace std;



// std::exception::what()————返回异常解释字符串
/*. BC------------------------------------------------------------------------
描述：
		返回一个c风格字符串，即char*，内容是对异常的解释。

函数原型：
		virtual const char* what() const throw();  (C++11 前)
		virtual const char* what() const noexcept; (C++11 起)
*. EC------------------------------------------------------------------------
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
					tx_exception(TM TS)
					format_error(C++20)
			bad_typeid
			bad_cast
					bad_any_cast(C++17)
			bad_weak_ptr(C++11)
			bad_function_call(C++11)
			bad_alloc
					bad_array_new_length(C++11)
			bad_exception
			ios_base::failure(C++11 前)
			bad_variant_access(C++17)

 
*/



/***************************************************************************
***************************************************************************/
// 全局变量、类型定义
 




/***************************************************************************
***************************************************************************/
// extern变量
extern void(*pfun[100])(void);
extern int inputTag, inputNum, interfaceLevel;


/***************************************************************************
***************************************************************************/
// 函数声明
void set_fun_exception_std_exception(void);
void start_exception_std_exception(void);

static void test0(void);
static void test1(void);
static void test2(void);
static void test3(void);
static void test4(void);



/***************************************************************************
***************************************************************************/
// extern函数
extern void traverse_pfun(void);



/***************************************************************************
***************************************************************************/
// 自定义类的实现



/***************************************************************************
***************************************************************************/
// 函数定义
void set_fun_exception_std_exception(void)
{
	pfun[0] = test0;
}


void start_exception_std_exception(void) 
{
	// 界面层级符置为3，进入三级界面：
	interfaceLevel = 3;
	while (3 == interfaceLevel)
	{
		cout << "\n\n\n\n" << endl;
		cout << "**************************MENU: exception_std_exception**********************" << endl;
		cout << "Please choose a demon function to run:" << endl;
		cout << "-2: Run all existed demon function." << endl;
		cout << "-1: Back to the previous interface." << endl;
		cout << "test0: 对标准异常的测试" << endl;


		inputTag = scanf("%d", &inputNum);

		// 若输入值不是整数，重新输入。
		if (inputTag != 1)
		{
			printf("Invalid input. Please input again:\n");
			setbuf(stdin, NULL);
			continue;
		}



		// 对三级界面输入值的响应。
		switch (inputNum)
		{
		case -2:
			traverse_pfun();
			break;

		case -1:
			interfaceLevel = 2;
			break;

		case 0:
			(*pfun[0])();
            break;


		default:
			printf("Invalid input. Please input again:\n");
			break;
		}


	}
}
 



// test0: 对标准异常的测试
static void test0(void) 
{
	cout << "\n\n\n\n" << endl;
    cout << "test0: 对标准异常的测试" << endl;

	classFoo foo1;

	try
	{
		// 测试一个有异常风险的语句：
		classFoo foo2("xiaohong", -1);
	}
	catch(exception e)
	{
		cout << "使用try-catch语句捕获了异常，异常解释字符串：e.what() == " << e.what() << endl;
	}

 
	try
	{
		foo1.setAge(-12);
	}
	catch(exception e)
	{
		cout << "使用try-catch语句捕获了异常，异常解释字符串：e.what() == " << e.what() << endl;;
	}
	

 
}
