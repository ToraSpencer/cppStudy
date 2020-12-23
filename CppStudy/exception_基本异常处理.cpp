#include <iostream>
#include <cmath>
#include <stdexcept>

#include <cstdio>

#define EPS 1e-6

using namespace std;


/*
**	语法——异常的抛出、处理
**		@ 异常的抛出throw——函数运转的时候发生异常时，应该生成一个对应的异常对象，使用throw抛出
**		@ 异常的处理
**				# 通过try catch语句来处理异常。
**				#
**				# try(异常)
**
**
**
*/



/***************************************************************************
***************************************************************************/
// 全局变量、类型定义

//		自定义的异常类，仿照标准异常类来实现。
class myException
{
public:
	myException();

};






/***************************************************************************
***************************************************************************/
// extern变量
extern void(*pfun[100])(void);
extern int inputTag, inputNum, interfaceLevel;


/***************************************************************************
***************************************************************************/
// 函数声明
void set_fun_exception_basic(void);
void start_exception_basic(void);

// 自定义浮点数除法，带有异常处理
double Divide(float a, float b);		// 异常类型声明：只能抛出int类型的异常							
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
void set_fun_exception_basic(void)
{
	pfun[0] = test0;
}


void start_exception_basic(void) 
{
	// 界面层级符置为3，进入三级界面：
	interfaceLevel = 3;
	while (3 == interfaceLevel)
	{
		cout << "\n\n\n\n" << endl;
		cout << "**************************MENU: exception_basic**********************" << endl;
		cout << "Please choose a demon function to run:" << endl;
		cout << "-2: Run all existed demon function." << endl;
		cout << "-1: Back to the previous interface." << endl;
		cout << "test0: 基本异常处理。" << endl;


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


//	Divide————自定义浮点数除法，带有异常处理
/*. BC------------------------------------------------------------------------
 
*. EC------------------------------------------------------------------------
*/
double Divide(float a, float b)  
{
	float temp = double(a/b);

	if ((b <= EPS) && (b >= -EPS))				// 若分母为0，抛出异常
	{
		throw 0;								// 抛出int类型的异常
	}

	return temp;
}




// test0: 简单的异常机制的展示：
static void test0(void) 
{
	cout << "\n\n\n\n" << endl;
    cout << "test0: 基本异常处理" << endl;
 
}
