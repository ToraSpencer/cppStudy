#include <iostream>
#include <set>
#include <string>
#include <typeinfo>
#include <algorithm>
#include <utility>



#include <cstdio>



#include "example.h" 
using namespace std;

#define EPS 1e-10					// 定义非常小的一个量EPSilon，当浮点数不大于这个值时，视为0
#define PI 3.14159


// 知识点
/*
	静态库
		在应用中，一些公共代码需要反复使用，就把这些代码编译为静态库文件。
		在链接步骤中，连接器将从静态库文件取得所需的代码，复制到生成的可执行文件中。
		linux系统中静态库文件后缀为.a
		windows系统中静态库文件后缀为.lib
		有的.lib文件为windows中动态库的导入库文件。
				对于作为导入库文件的.lib文件而言，其实际的执行代码位于动态库中。
				导入库只包含了地址符号表等，确保程序找到对应函数的一些基本地址信息。
				而对于作为静态库的.lib来说，其本身就包含了实际执行代码、符号表等等

		
	WINDOWS中的动态库
		windows系统中动态库文件后缀为.dll
		显式加载
				宿主程序代码中通过函数LoadLibrary(), FreeLibrary()指定DLL的加载和卸载 
				宿主程序启动后，其进程在遇到LoadLibrary()函数时才将DLL加载到进程的内存空间。	
				显式加载时，只有需要使用dll文件，不需要LIB文件。
		隐式加载
				隐式加载时没有显式地调用LoadLibrary()和FreeLibrary()，因此称为隐式加载。
				宿主程序在启动时搜索到dll文件后，将动态链接库加载到宿主程序进程的内存空间。 
				隐式加载本质上也是通过LoadLibrary()函数实现加载工作。
				需要使用lib文件和dll文件。

	LINUX中的动态库
		linux系统中动态库文件后缀为.so



	DLL文件
		DLL和EXE文件一样，其中包含的也是程序的二进制执行代码和程序所需的资源
		DLL中的代码是以API函数形式出现的
		通俗地说，DLL中包含的程序代码都被做成了一个个小模块，应用程序通过按下所需DLL中特定的按钮，来调用DLL中这个按钮所代表的功能

		
		


	静态库和动态库的区别
		静态库在程序的链接阶段被复制到了程序中，和程序运行的时候没有关系；
		动态库是程序在运行时由系统动态加载到内存中供程序调用。
		使用动态库的优点是系统只需载入一次，不同的程序可以得到内存中相同的动态库的副本，因此节省了很多内存。


	调用静态库的方式：
			包含静态库的头文件，如#include "lib1/lib1.h"
			试用预处理指令导入静态库——如#pragma comment(lib,"lib1.lib")
			如果使用了VS，则上一步可以改为在项目属性->链接器->附加依赖项之中加入.lib文件。





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
void set_fun_dynamic_static_library(void);
void start_dynamic_static_library(void);





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

void set_fun_dynamic_static_library(void)
{
	pfun[0] = test0;
	pfun[1] = test1;
	pfun[2] = test2;
	pfun[3] = test3;
	pfun[4] = test4;
	pfun[5] = test5;
}



void start_UP_dynamic_static_library(void)
{
	// 界面层级符置为3，进入三级界面：
	interfaceLevel = 3;
	while (3 == interfaceLevel)
	{
		cout << "\n\n\n\n" << endl;
		cout << "**************************MENU: UP_DYNAMIC_STATIC_LIBRARY**********************" << endl;
		cout << "Please choose a demon function to run:" << endl;
		cout << "-2: Run all existed demon function." << endl;
		cout << "-1: Back to the previous interface." << endl;
		cout << "0. test0:  " << endl;
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






// test0: 
static void test0(void)
{

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



