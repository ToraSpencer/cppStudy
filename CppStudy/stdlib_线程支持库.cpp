#include <thread>
#include <mutex>
#include <future>
#include <condition_variable>


#include <iostream>
#include <string>
#include <typeinfo>

#include <cstdio>
using namespace std;

#define EPS 1e-10								//定义非常小的一个量EPSilon，当浮点数不大于这个值时，视为0
#define PI 3.14159



// C++标准库——线程支持库
/*
**			(C++11 起)<thread> 												std::thread 类及支持函数
**			(C++20 起)<stop_token> 										std::jthread 的停止记号
**			(C++11 起)<mutex> 												互斥原语
**			(C++14 起)<shared_mutex> 									共享的互斥原语
**			 (C++11 起)<future>	 											异步计算的原语
**			(C++11 起)<condition_variable> 						 	线程等待条件
**			 (C++20 起)<semaphore> 										信号量
**			 (C++20 起)<latch>	 												闩
**			 (C++20 起)<barrier>	 											屏障
**
**
*/


// 进程
/*
	进程组成：
			1.程序
			2.数据
			3.进程控制块(PCB)

*/


// 线程
/*
	线程是进程中的一个实体，是被系统独立分配和调度的基本单位。
	也有说，线程是CPU可执行调度的最小单位。
	也就是说，进程本身并不能获取CPU时间，只有它的线程才可以。

	线程、进程的比较
			线程参与操作系统的调度，参与CPU的竞争，得到分配的时间片，获得处理机（CPU）运行。
			而进程负责获取操作系统分配的资源，如内存。


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
void set_fun_stdlib_thread_support_lib(void);
void start_stdlib_thread_support_lib(void);

static void test0(void);
static void test1(void);
static void test2(void);
static void test3(void);
static void test4(void);
static void test5(void);


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
void set_fun_stdlib_thread_support_lib(void)
{
	pfun[0] = test0;
	pfun[1] = test1;
	pfun[2] = test2;
	pfun[3] = test3;
	pfun[4] = test4;
	pfun[5] = test5;

}



void start_stdlib_thread_support_lib(void)
{
	// 界面层级符置为3，进入三级界面：
	interfaceLevel = 3;
	while (3 == interfaceLevel)
	{
		cout << "\n\n\n\n" << endl;
		cout << "**************************MENU: stdlib_thread_support_lib**********************" << endl;
		cout << "Please choose a demon function to run:" << endl;
		cout << "-2: Run all existed demon function." << endl;
		cout << "-1: Back to the previous interface." << endl;
		cout << "0. test0:  " << endl;
		cout << "1. test1：  " << endl;


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


		case 1:
			(*pfun[1])();


		default:
			printf("Invalid input. Please input again:\n");
			break;
		}


	}
}




static void test0(void) 
{

}


// test1： <ctime>——C风格的时间、日期工具。
static void test1(void) 
{}


// test2:
static void test2(void)
{
	using namespace chrono;

	//循环1：
	auto start = system_clock::now();

	long int num = 10000000;
	for (int i = 0; i != num; i++)
	{
		int* b = new int[10]();
		delete[] b;
	}

	auto end = system_clock::now();
	auto duration = duration_cast<microseconds>(end - start);
	cout << "程序1花费了"
		<< double(duration.count()) * microseconds::period::num / microseconds::period::den << "秒" << endl;


	//循环2
	start = system_clock::now();

	int num2 = num >> 1;
	for (int i = 0; i != num2; i++) {
		int* b = new int[10]();
		delete[] b;
	}
	for (int i = num2; i != num; i++) {
		int* b = new int[10]();
		delete[] b;
	}

	end = system_clock::now();
	duration = duration_cast<microseconds>(end - start);
	cout << "程序2花费了"
		<< double(duration.count()) * microseconds::period::num / microseconds::period::den << "秒" << endl;

	//循环3
	start = system_clock::now();

	//testfuc2(num);

	end = system_clock::now();
	duration = duration_cast<microseconds>(end - start);
	cout << "程序3花费了"
		<< double(duration.count()) * microseconds::period::num / microseconds::period::den << "秒" << endl;


}



static void test3(void)
{}



static void test4(void)
{}



static void test5(void)
{}