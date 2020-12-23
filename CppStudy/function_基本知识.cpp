#include <iostream>
#include <string>
#include <typeinfo>

#include <cstdio>
 
using namespace std;

#define EPS 1e-10					//定义非常小的一个量EPSilon，当浮点数不大于这个值时，视为0
#define PI 3.14159



// C++函数——基本知识


 

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
void set_fun_function_basic(void);
void start_function_basic(void);

static unsigned long factorial(unsigned int);
static void to_binary(unsigned long);

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
void set_fun_function_basic(void)
{
	pfun[0] = test0;
	pfun[1] = test1;
	pfun[2] = test2;
	pfun[3] = test3;
	pfun[4] = test4;
	pfun[5] = test5;
}



void start_function_basic(void)
{
	// 界面层级符置为3，进入三级界面：
	interfaceLevel = 3;
	while (3 == interfaceLevel)
	{
		cout << "\n\n\n\n" << endl;
		cout << "**************************MENU: function_basic**********************" << endl;
		cout << "Please choose a demon function to run:" << endl;
		cout << "-2: Run all existed demon function." << endl;
		cout << "-1: Back to the previous interface." << endl;
		cout << "0. test0: 简单的递归调用 " << endl;
 


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



// factorial————计算阶乘num!
/*. BC------------------------------------------------------------------------
**	factorial————计算阶乘num!
**
**	描述：
**			尾递归实现。
**
**	函数原型：
**			static unsigned long factorial(	unsigned int num				需要计算阶乘的正整数
**															)
**			返回值： unsigned long														阶乘计算结果
**
*. EC------------------------------------------------------------------------
*/
static unsigned long factorial(unsigned int num)
{
	//		递归递推：factorial(n) == n*factorial(n-1)
	//		递归终止条件：factorial(1) == 1;	factorial(0) == 1;

	unsigned long result;

	if ((1 == num) || (0 == num))
	{
		result = 1;
	}
	else
	{
		//		 尾递归：
		//				递归最简单的情形。
		//				可以很容易地改写成循环的形式。
		result = num * factorial(num - 1);
	}

	return result;

}



// to_binary————将输入的十进制正整数转换为二进制数打印出来
/*. BC------------------------------------------------------------------------
**	to_binary————将输入的十进制正整数转换为二进制数打印出来
**
**	描述：
**
**	函数原型：
**			static void to_binary(	unsigned long num							待转换为二进制显示的十进制正整数
**											)
**
*. EC------------------------------------------------------------------------
*/
static void to_binary(unsigned long num)
{
	//		递归递推： to_binary(num) → to_binary(num/2)
	//		递归终止条件： num == 0; num == 1;
	int remind;

	remind = num % 2;
	if (num >= 2)
	{
		to_binary(num / 2);
	}

	putchar(remind ? '1' : '0');

}


// test0: 简单的递归调用：
static void test0(void)
{
	unsigned long num = 1;
	int inputValid = 0;
	unsigned long result = 0;

	printf("test0: 简单的递归调用：\n");
	printf("\ttest0.0：尾递归实现的阶乘计算：\n");
	printf("\t\tplease input a non-negative integer:\n");

	while ((0 == inputValid) && (num >= 0))				// 合法输入的检验
	{
		setbuf(stdin, NULL);
		inputValid = scanf("%d", &num);

		if ((1 == inputValid) && (num >= 0))
		{
			break;
		}
		else
		{
			setbuf(stdin, NULL);
			printf("\t\tinvalid input. Please input again.\n");
		}
	}

	result = factorial(num);
	printf("\t\tthe factorial of %d is: factorial(%d) == %d;\n", num, num, result);


	printf("\ttest0.1：递归实现的十进制到二进制转换：\n");
	printf("\t\tplease input a non-negative integer:\n");
	setbuf(stdin, NULL);
	inputValid = 0;
	while ((0 == inputValid) && (num >= 0))
	{
		setbuf(stdin, NULL);
		inputValid = scanf("%d", &num);

		if ((1 == inputValid) && (num >= 0))
		{
			break;
		}
		else
		{
			setbuf(stdin, NULL);
			printf("\t\tinvalid input. Please input again.\n");
		}
	}

	printf("\t\tthe binary form of %d is :\n", num);
	printf("\t\t");
	to_binary(num);
	setbuf(stdin, NULL);


}

// test1： 
static void test1(void) {}


static void test2(void)
{}


static void test3(void)
{}



static void test4(void)
{}



static void test5(void)
{}