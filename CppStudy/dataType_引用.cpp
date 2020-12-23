#include <iostream>
#include <cstdio>
#include <string>
#include <typeinfo>
using namespace std;

#define EPS 1e-10					 
#define PI 3.14159



// 知识点
/*
		引用
				是一个对象的别名。
				引用必须初始化，不能先声明，再初始化。
				引用和初始值是绑定(bind)在一起的，这个过程中不发生拷贝。

		引用传递(passed by reference)
				指函数的形参是引用类型。 
				此时形参是实参的别名，形参和实参的值绑定在一起，不会有拷贝的发生。
				相对应的值传递(passed by value)中，实参的值拷贝给形参。
				函数形参类型为非const引用时，只能绑定左值，像"hello",123这样的字面量不是左值，就不能作为其实参



		
				
			 

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
void set_fun_dataType_reference(void);
void start_dataType_reference(void);


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
void set_fun_dataType_reference(void)
{
	pfun[0] = test0;
	pfun[1] = test1;

}


void start_dataType_reference(void)
{
	interfaceLevel = 3;

	while (3 == interfaceLevel)
	{
		printf("\n\n\n\n\n");
		printf("**************************MENU: dataType_functionPointer**********************\n");
		printf("Please choose a demon function to run:\n");
		printf("-2: Run all existed demon function.\n");
		printf("-1: Back to the previous interface.\n");
		printf("0: test0:  ");
		printf("1: test1: ");


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

		default:
			printf("Invalid input. Please input again:\n");
			break;
		}


	}

}







// test0:  
static void test0(void)
{
	int num1 = 99;
	int& num2 = num1;								// 引用num2和num1的值绑定在一起。
	cout << "num2 == " << num2 << endl;

	num2 = 100;											// 使用引用num2来改变变量num1的值。
	cout << "num1 == " << num1 << endl;



}




// test1: 
static void test1(void)
{

}


