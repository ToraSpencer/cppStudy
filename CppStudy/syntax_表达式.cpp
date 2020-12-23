#include <iosfwd>
#include <ios>
#include <istream>
#include <ostream>
#include <iostream>
#include <string>
#include <typeinfo>

#include <cstdio>


using namespace std;

#define EPS 1e-10					//定义非常小的一个量EPSilon，当浮点数不大于这个值时，视为0
#define PI 3.14159



// C++语法——表达式、constexpr
/*
		 
*/


/***************************************************************************
***************************************************************************/
// extern变量
extern void(*pfun[100])(void);
extern int inputTag, inputNum, interfaceLevel;



/***************************************************************************
***************************************************************************/
// 函数声明
void set_fun_syntax_expression(void);
void start_syntax_expression(void);

static void test0(void);
static void test1(void);
static void test2(void);
static void test3(void);
static void test4(void);


/***************************************************************************
***************************************************************************/
// extern函数
void traverse_pfun(void);


/***************************************************************************
***************************************************************************/
// 自定义类的实现



/***************************************************************************
***************************************************************************/
// 函数定义
void set_fun_syntax_expression(void) {}



void start_syntax_expression(void) {}



// 常量表达式constexpr的简单应用
constexpr unsigned fooConst()			// 返回值为constexpr的函数
{
	return 9;
}
 
static void test0(void) 
{
	int arr[fooConst()];				// fooConst()函数返回一个常量表达式，可以用来声明数组。

	cout << sizeof(arr) << endl;

}
