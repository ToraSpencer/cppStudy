#include <iostream>
#include <cstdio>
#include <string>
#include <typeinfo>
using namespace std;

#define EPS 1e-10					 
#define PI 3.14159



// 知识点
/*
			函数指针的声明语法————和函数声明格式类似，只是函数名变成了*pf

			对于某函数foo()，可以用foo或&foo表示其指针。

			回调函数
					如果一个函数并不会被显式地直接调用，而是将其函数指针传给一个caller函数，由caller函数调用，这个函数就被成为回调函数。

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
void set_fun_dataType_function_pointer(void);
void start_dataType_function_pointer(void);

static void foo(void);
static void goo(void);
static int add_intNum(int x, int y);

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
void set_fun_dataType_function_pointer(void)
{
	pfun[0] = test0;
	pfun[1] = test1;
	pfun[2] = test2;
}


void start_dataType_function_pointer(void)
{
	interfaceLevel = 3;

	while (3 == interfaceLevel)
	{
		printf("\n\n\n\n\n");
		printf("**************************MENU: dataType_functionPointer**********************\n");
		printf("Please choose a demon function to run:\n");
		printf("-2: Run all existed demon function.\n");
		printf("-1: Back to the previous interface.\n");
		printf("0: test0: 函数指针的基本使用\n");
		printf("1: test1: 函数指针数组、二级函数指针\n");
		printf("2: test2: 回调函数\n");

		inputTag = scanf("%d", &inputNum);


		if (inputTag != 1)
		{
			printf("Invalid input. Please input again:\n");
			setbuf(stdin, NULL);
			continue;
		}


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

		default:
			printf("Invalid input. Please input again:\n");
			break;
		}


	}

}


namespace MY_CALCULATOR
{
	typedef float(*unaryOP)(const float& num);			// 有回调函数时使用typedef定义相关函数指针类型，这样可以将caller函数的参数列表写的更简洁。
	typedef float(*binaryOP)(const float& num1, const float& num2);

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


	// 重载1——进行一元运算：
	float calculate(unaryOP pfunc, const float& num)
	{
		float number = num;
		return (*pfunc)(number);
	}


	// 重载2——进行二元运算
	float calculate(binaryOP pfunc, const float& num1, const float& num2)
	{
		float number1 = num1;
		float number2 = num2;
		return (*pfunc)(number1, number2);
	}

}






static void foo(void)
{
	printf("\tthis is a string printed by the void function foo.\n");

}




static void goo(void)
{
	printf("\tthis is a string printed by the void function goo.\n");


}



static int add_intNum(int x, int y)
{
	return (x + y);

}




// test0: 函数指针的基本使用
static void test0(void)
{
	// 1. 函数指针的声明————和函数声明格式类似，只是函数名变成了*pf
	void(*pfv)(void) = NULL;
	int(*pfi)(int x, int y) = NULL;
	int temp = 0;

	cout << "\n\n\n\n" << endl;
	cout << "test0: 函数指针的基本使用" << endl;


	// 2.  
	pfv = foo;
	pfi = add_intNum;


	// 3. 
	cout << "\tnow test the void function:" << endl;
	(*pfv)();
	cout << endl;

	cout << "\tnow test the int function:" << endl;
	temp = (*pfi)(3, 4);
	cout << "\t(*pfi)(3,4) == " << temp << endl;
	cout << endl;

}




// test1: 函数指针数组、二级函数指针。
static void test1(void)
{
	// 1. 声明函数指针数组
	void(*pfv[10])(void) = { NULL };

	// 2. 二级指针
	void(**ppfv)(void) = NULL;

	printf("\n\n\n\n");
	printf("\ttest1: 函数指针数组、二级函数指针\n");


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


// test2: 回调函数
static void test2(void) 
{
	printf("\n\n\n\n");
	printf("test2: 回调函数");


	cout << MY_CALCULATOR::calculate((MY_CALCULATOR::add), 1.0f, 2.0f) << endl;
	cout << MY_CALCULATOR::calculate((MY_CALCULATOR::add), 3.0f, 1.0f) << endl;
	cout << MY_CALCULATOR::calculate((MY_CALCULATOR::sqrt), 3.0f) << endl;



}

