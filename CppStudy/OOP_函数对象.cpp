#include <iostream>
#include <string>
#include <typeinfo>


#include <cstdio>

#include "example.h"

using namespace std;

#define EPS 1e-10					//定义非常小的一个量EPSilon，当浮点数不大于这个值时，视为0
#define PI 3.14159



// C++面向对象编程——函数对象（函数子），头文件functional
/*
	函数对象（函数子）类：
			若一个类中将运算符()重载为成员函数，则这个类是一个函数对象类，其实例就是一个函数对象。
			使用起来的形式和函数调用一样，而且也确实进行了函数调用。
			函数对象可以保存函数的调用状态，可以实现函数回调。
			
	<functional>头文件
			标准库中的函数对象类模板
			
	lambda表达式（c++11）
			本质是一个匿名函数对象，也是一个可调用的表达式。

			捕获列表
				[=,&a,&b]		以引用传递的方式捕捉变量a和b，以值传递方式捕捉其它所有变量;
				[&,a,this]		以值传递的方式捕捉变量a和this，引用传递方式捕捉其它所有变量。
			
			
			捕捉列表不允许变量重复传递。下面一些例子就是典型的重复，会导致编译时期的错误。
				X [=,a]	————这里已经以值传递方式捕捉了所有变量，但是重复捕捉a了，会报错的;
				X [&,&this]————这里&已经以引用传递方式捕捉了所有变量，再捕捉this也是一种重复。
					

*/

  
// extern变量
extern void(*pfun[100])();
extern int inputTag, inputNum, interfaceLevel;
 
// 函数声明
void set_fun_OOP_function_object();
void start_OOP_function_object();

static void test0();
static void test1();
static void test2();
static void test3();
static void test4();

 
// extern函数
void traverse_pfun();
 

// 自定义类的实现
 
 
// 函数定义
void set_fun_OOP_function_object() 
{
	 pfun[0] = test0;
	 pfun[1] = test1;
}



void start_OOP_function_object()
{
	// 界面层级符置为3，进入三级界面：
	interfaceLevel = 3;
	while (3 == interfaceLevel)
	{
		cout << "\n\n\n\n" << endl;
		cout << "**************************MENU: OOP_function_object**********************" << endl;
		cout << "Please choose a demon function to run:" << endl;
		cout << "-2: Run all existed demon function." << endl;
		cout << "-1: Back to the previous interface." << endl;
		cout << "0. test0: 函数对象的基本功能、特点。" << endl;
		cout << "1. test1：<functional>中的常用函数对象类模板" << endl;
		cout << "2. test2: 简单的lambda表达式" << endl;


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
			


		default:
			printf("Invalid input. Please input again:\n");
			break;
		}


	}
}



// test0: 函数对象的基本功能、特点。
static void test0() 
{
	cout << "\n\n\n\n" << endl;
	cout << "test0: 函数对象的基本功能、特点" << endl;

	vector<classFoo> vf;
    classFoo f1;
    classFoo f2("xiaoming", 12);
    classFoo f3("xiaohong", 23);
    classFoo f4("laowang", 87);
    FooPrinter ffoo;
 
    vf.push_back(f1);
    vf.push_back(f2);
    vf.push_back(f2);
    vf.push_back(f3);
    vf.push_back(f4);

    cout << "传递函数遍历：" << endl;
    for_each(vf.begin(), vf.end(), printFoo);

    cout << "传递函数子遍历：" << endl;
    auto ffoo1 = for_each(vf.begin(), vf.end(), ffoo);
    cout << endl;
	// 显示函数子被调用次数：
	// ffoo只是在for_each函数中被拷贝，并没有被调用，真正被调用的是被传出的对象ffoo1
	cout << "\tffoo.getCount() == " << ffoo.getCount() << endl;
    cout << "\tffoo1.getCount() == " << ffoo1.getCount() << endl;
    

 
 
}



// test1：<functional>中的常用函数类模板：
static void test1()
{
	cout << "\n\n\n\n" << endl;
	cout << "test1：<functional>中的常用函数对象类模板" << endl;

	plus<int> plus_int;
	int result = 0;
	result = plus_int(5,6);
	cout << "\t plus_int(5,6) == " << plus_int(5,6) << endl;

}



// test2: 简单的lambda表达式
static void test2()
{
	cout << "\n\n\n\n" << endl;
	cout << "test2: 简单的lambda表达式" << endl;


	// 没有参数，没有返回值的lambda表达式
	auto functor1 = []() {cout << "hello" << endl; };	 
	functor1(); 


	// 有参数，有返回值的lambda表达式
	auto functor2 = [](const string& a, const string& b) -> bool    // 尾返回指示返回值的类型。
	{
		return a.size() < b.size(); 
	};
	string str1 = "hahaha";
	string str2 = "haha";
	if(functor2(str1, str2))
	{
		cout << "str1比str2短" << endl;
	}
	else
	{
		cout << "str1比str2长" << endl;
	}


	// 给算法库中的算法传递lambda表达式函数对象。
	vector<string> vi = {"hahah","hello","lalala"};
	//			这样就不需要在全局范围内再额外定义函数对象类。
	for_each(vi.begin(), vi.end(), [](const string& str) {cout << str << endl; });




}




static void test3()
{



}
