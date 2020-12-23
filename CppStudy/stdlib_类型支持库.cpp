#include <iostream>
#include <set>
#include <string>
#include <typeinfo>
#include <algorithm>
#include <utility>
#include <type_traits>



#include <cstdio>
#include <cassert>			//提供宏函数assert()


#include "example.h" 
using namespace std;

#define EPS 1e-10					//定义非常小的一个量EPSilon，当浮点数不大于这个值时，视为0
#define PI 3.14159


// 知识点
/*
	主要相关头文件
			<typeinfo>
			<type_traits>
			<cstddef>
			<limits>
			<typeindex>

	is_xxx系列类模板（C++11）
			用于判断数据对象是否是xxx类型。
			如is_pointer, is_null_pointer, is_const, is_signed.... 
			定义于<type_traits>
			封装了一个static的bool成员变量value，用is_xxx<type>::value的值来判断type类型是否是xxx类型

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
void set_fun_stdlib_type_support_lib(void);
void start_stdlib_type_support_lib(void);





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

void set_fun_stdlib_type_support_lib(void)
{
	pfun[0] = test0;
	pfun[1] = test1;
	pfun[2] = test2;
	pfun[3] = test3;
	pfun[4] = test4;
	pfun[5] = test5;
}



void start_stdlib_type_support_lib(void)
{
	// 界面层级符置为3，进入三级界面：
	interfaceLevel = 3;
	while (3 == interfaceLevel)
	{
		cout << "\n\n\n\n" << endl;
		cout << "**************************MENU: TYPE_SUPPORT_LIB**********************" << endl;
		cout << "Please choose a demon function to run:" << endl;
		cout << "-2: Run all existed demon function." << endl;
		cout << "-1: Back to the previous interface." << endl;
		cout << "0. test0: " << endl;
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






// test0: is_xxx系列类模板判断类型、属性
static void test0(void)
{
	cout << "\n\n\n\n" << endl;
	cout << "test0:  is_xxx系列类模板判断类型、属性" << endl;

	std::cout << std::is_pointer<int>::value << endl;
	std::cout << std::is_pointer<int *>::value << endl;
	std::cout << std::is_pointer<int &>::value << endl;
	std::cout << std::is_pointer<int **>::value << endl;
	std::cout << std::is_pointer<int[10]>::value << endl;
	std::cout << std::is_pointer<std::nullptr_t>::value << endl;



}





// test1: typeid()函数
static void test1(void)
{
	cout << "test1: typeid()函数 :" << endl << endl;

	// typeid()返回type_info类对象，其中name()方法返回数据类型名： 
	
	cout << "typeid(5).name() = ：" << typeid(5).name() << endl;
	cout << "typeid(3.12).name() = " << typeid(3.12).name() << endl;
	cout << "typeid('c').name() = " << typeid('a').name() << endl;
	cout << "typeid(\"helloWorld\").name() = " << typeid("helloWorld").name() << "	//字符串的本质是字符数组。" << endl;

	int i = 1;
	int* p_i = &i;
	cout << "int i = 1; int* p_i = &i; typeid(p_i).name() = " << typeid(p_i).name() << endl;

	int a[] = { 1,2,3 };
	cout << "int a[] = {1,2,3}; typeid(a).name() = " << typeid(a).name() << endl;

	int b[2][3] = { {1,2,3},{4,5,6} };
	cout << "int b[2][3] = {{1,2,3},{4,5,6}}; typeid(b).name() = " << typeid(b).name() << endl;

	class testClass {};
	testClass t;
	cout << "class testClass{}; testClass t; typeid(t).name() = " << typeid(t).name() << endl;

	cout << endl;

 

}



// test2: isxxx()系列函数
static void test2(void)
{
	int* pi = NULL;
	typedef double* dptr;

	// 尖括号中的参数是类型、不是变量。
	// 圆括号中参数列表只能为空，用于返回value;

	auto value1 = is_null_pointer<dptr>();
	cout << value1 << endl;

	cout << is_null_pointer<int*>::value << endl;


	cout << "finished " << endl;

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



