#include <iostream>
#include <set>
#include <string>
#include <typeinfo>
#include <algorithm>
#include <utility>



#include <cstdio>
#include <cassert>			//提供宏函数assert()


#include "example.h" 
using namespace std;

#define EPS 1e-10					//定义非常小的一个量EPSilon，当浮点数不大于这个值时，视为0
#define PI 3.14159


// 知识点
/*
		1. 基本信息：
					函数原型——void assert( int expression );
					作用——简单地说是如果它的条件返回错误，则终止程序执行
					具体过程——先计算表达式 expression，如果其值为假（即为0），那么它先向stderr打印一条出错信息，然后通过调用 abort 来终止程序运行。

		2. assert是用来避免显而易见的错误的，而不是处理异常的。
					错误和异常是不一样的，错误是不应该出现的，异常是不可避免的。
					c语言异常可以通过条件判断来处理，其它语言有各自的异常处理机制。


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
void set_fun_UP_assert(void);
void start_UP_assert(void);





static void test0(void);
static void test1(void);
static void test2(void);
static void test3(void);
static void test4(void);
static void test5(void);



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

void set_fun_UP_assert(void)
{
	pfun[0] = test0;
	pfun[1] = test1;
	pfun[2] = test2;
	pfun[3] = test3;
	pfun[4] = test4;
	pfun[5] = test5;
}



void start_UP_assert(void)
{
	// 界面层级符置为3，进入三级界面：
	interfaceLevel = 3;
	while (3 == interfaceLevel)
	{
		cout << "\n\n\n\n" << endl;
		cout << "**************************MENU: UP_ASSERT**********************" << endl;
		cout << "Please choose a demon function to run:" << endl;
		cout << "-2: Run all existed demon function." << endl;
		cout << "-1: Back to the previous interface." << endl;
		cout << "0. test0: 断言的基本使用" << endl;
		cout << "1. test1:  " << endl;


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
		
		
		case 1:
			(*pfun[1])();
			break;
		
		
		case 2:
			(*pfun[2])();
			break;
		
		
		case 3:
			(*pfun[3])(); 	
			break;
		
		
		case 4:
			(*pfun[4])();
			break;
		
			
		case 5:
			(*pfun[5])();
			break;


		default:
			printf("Invalid input. Please input again:\n");
			break;
		}


	}
}






// test0: 断言的基本使用
static void test0(void)
{

	cout << "\n\n\n\n" << endl;
	cout << "test0: 断言的基本使用" << endl;

	int flag;
	cout << "please input a integer" << endl;
	cin >> flag;
	
	assert(flag);
	cout << "flag >0" << endl;			// 如果输入的值等于0的话，程序不会运行到这里，在这之前就被abort了。

}






static void test1(void)
{
 

}


static void test2(void)
{
 

}

static void test3(void)
{
 

}

static void test4(void)
{
 

}

static void test5(void)
{
 

}



