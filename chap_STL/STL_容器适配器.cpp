#include <iostream>
#include <string>
#include <typeinfo>
#include <vector>
#include <list>
#include <stack>					// stack容器适配器
#include <queue>					// queue, priority_queue容器适配器

#include <cstdio>


using namespace std;

#define EPS 1e-10					//定义非常小的一个量EPSilon，当浮点数不大于这个值时，视为0
#define PI 3.14159



// STL——容器适配器：stack, queue, priority_queue,
/*
	 适配器的作用：
				使用一套新的接口，覆盖掉原有程序的接口。
				本质上是类模板




**
*/



// stack——栈模板类
/*
	默认容器：deque

	其他可用容器：vector, list

	成员数据：
			container_type			Container										底层容器对象
			value_type				Container::value_type
			size_type					Container::size_type
			reference					Container::reference
			const_reference		Container::const_reference

	成员函数：
			stack<int> s;									// 使用默认的容器deque实现栈对象s。
			stack<int, vector<int> > stk;  		// 使用容器vector实现栈对象stk!!!注意空格

			operator=										// 赋值运算符重载

			void push(const T& el);   				// 在栈顶压（尾端）入新元素el
			void pop();    									// 删除栈顶（尾端）元素，但不返回其值
			（C++11）emplace							// 于栈顶原位构造元素
			const T& top();    							// 返回栈顶（尾端）元素的值，但不删除此元素

			bool empty()									// 检查底层的容器是否为空	
			size_type size()									// 返回容纳的元素数
			void swap(stack& s)						// 交换容器内容		


*/


// queue——队列模板类
/*
	默认容器：deque
	其他可用容器：list
	成员数据：
			container_type			Container										底层容器对象
			value_type				Container::value_type
			size_type					Container::size_type
			reference					Container::reference
			const_reference		Container::const_reference


	成员函数：
			queue<T>
			queue<T,container<T>>

			operator=										// 赋值运算符重载

			void push(const T& el);					// 入队操作：从尾端加入元素。
			void pop();										// 出队操作：从首端删除元素。

			（C++11）emplace
		  
			T& front();										// 访问首部元素
			T& back();										// 访问尾部元素
			
			bool empty()									// 检查底层的容器是否为空
			size_type size()									// 返回容纳的元素数
			void swap(queue& q)						// 交换容器内容


*/



// priority_queue——优先级队列类模板——元素有序排列的队列
/*


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
void set_fun_STL_adapter(void);
void start_STL_adapter(void);

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
void set_fun_STL_adapter(void)
{
	pfun[0] = test0;
	pfun[1] = test1;
}



void start_STL_adapter(void)
{
	// 界面层级符置为3，进入三级界面：
	interfaceLevel = 3;
	while (3 == interfaceLevel)
	{
		cout << "\n\n\n\n" << endl;
		cout << "**************************MENU: STL_adapter**********************" << endl;
		cout << "Please choose a demon function to run:" << endl;
		cout << "-2: Run all existed demon function." << endl;
		cout << "-1: Back to the previous interface." << endl;
		cout << "0. test0:  stack类模板的成员" << endl;
		cout << "1. test1：queue类模板的成员  " << endl;


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



// test0:  stack类模板的成员
static void test0(void) 
{
	stack<char> stc1;										// 默认情况下用deque构造stack
	stack<int, vector<int>> sti1;						// 指定使用vector来构造stack
	stack<float, list<float>> stf1;


	cout << "\n\n\n\n" << endl;
	cout << "test0:  stack类模板的成员" << endl;

	stc1.push('a');																			// 压栈操作
	stc1.push('b');
	stc1.push('c');
	stc1.push('d');
	stc1.push('e');
 

	cout << "\tstc1.empty() = " << stc1.empty() << endl;				// 查看是否为空
	cout << "\tstc1.size() = " << stc1.size() << endl;						// 查看当前元素数

	stc1.pop();																					// 出栈操作
	cout << "\tstc1.top() = " << stc1.top() << endl;						// 访问栈顶元素
	cout << endl;
	
}


// test1：queue类模板的成员 
static void test1(void)
{
	queue<int> qi1;
	queue<double, list<double>> qd1;

	cout << "\n\n\n\n" << endl;
	cout << "test1：queue类模板的成员 " << endl;

	qi1.push(0);						
	qi1.push(1);
	qi1.push(2);

	cout << "\tqi1.front() = " << qi1.front() << endl;
	cout << "\tqi1.back() = " << qi1.back() << endl;

	


}