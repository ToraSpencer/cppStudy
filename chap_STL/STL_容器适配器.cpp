#include <iostream>
#include <string>
#include <typeinfo>
#include <vector>
#include <list>
#include <stack>					// std::stack容器适配器
#include <queue>					// std::queue, priority_queue容器适配器

#include <cstdio>

#include "STL_容器适配器.h"

#define EPS 1e-10					//定义非常小的一个量EPSilon，当浮点数不大于这个值时，视为0
#define PI 3.14159



// STL——容器适配器：std::stack, std::queue, priority_queue,
/*
	 适配器的作用：
				使用一套新的接口，覆盖掉原有程序的接口。
				本质上是类模板
 
 
*/



// std::stack——栈模板类
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
			std::stack<int> s;									// 使用默认的容器deque实现栈对象s。
			std::stack<int, vector<int> > stk;  		// 使用容器vector实现栈对象stk!!!注意空格

			operator=										// 赋值运算符重载

			void push(const T& el);   				// 在栈顶压（尾端）入新元素el
			void pop();    									// 删除栈顶（尾端）元素，但不返回其值
			（C++11）emplace							// 于栈顶原位构造元素
			const T& top();    							// 返回栈顶（尾端）元素的值，但不删除此元素

			bool empty()									// 检查底层的容器是否为空	
			size_type size()									// 返回容纳的元素数
			void swap(std::stack& s)						// 交换容器内容		


*/


// std::queue——队列模板类
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
			std::queue<T>
			std::queue<T,container<T>>

			operator=										// 赋值运算符重载

			void push(const T& el);					// 入队操作：从尾端加入元素。
			void pop();										// 出队操作：从首端删除元素。

			（C++11）emplace
		  
			T& front();										// 访问首部元素
			T& back();										// 访问尾部元素
			
			bool empty()									// 检查底层的容器是否为空
			size_type size()									// 返回容纳的元素数
			void swap(std::queue& q)						// 交换容器内容


*/



// priority_queue——优先级队列类模板——元素有序排列的队列
/*


*/




virtualModule* STL_adapter_module::getInstance()		// 线程不安全的单例模式
{
	if (nullptr != p_moduleIns)
	{
		delete p_moduleIns;
	}
	p_moduleIns = new STL_adapter_module;
	return p_moduleIns;
}








// test0:  std::stack类模板的成员
void STL_adapter_module::test0(void)
{
	std::stack<char> stack1;										// 默认情况下用deque构造std::stack
	std::stack<int, std::vector<int>> sti1;						// 指定使用vector来构造std::stack
	std::stack<float, std::list<float>> stf1;


	std::cout << "\n\n\n\n" << std::endl;
	std::cout << "test0:  std::stack类模板的成员" << std::endl;

	stack1.push('a');																			// 压栈操作
	stack1.push('b');
	stack1.push('c');
	stack1.push('d');
	stack1.push('e');
 

	std::cout << "\tstack1.empty() = " << stack1.empty() << std::endl;				// 查看是否为空
	std::cout << "\tstack1.size() = " << stack1.size() << std::endl;						// 查看当前元素数

	stack1.pop();																					// 出栈操作
	std::cout << "\tstack1.top() = " << stack1.top() << std::endl;						// 访问栈顶元素
	std::cout << std::endl;
	
}


// test1：std::queue类模板的成员 
void STL_adapter_module::test1(void)
{
	std::queue<int> qi1;
	std::queue<double, std::list<double>> qd1;

	std::cout << "\n\n\n\n" << std::endl;
	std::cout << "test1：std::queue类模板的成员 " << std::endl;

	qi1.push(0);						
	qi1.push(1);
	qi1.push(2);

	std::cout << "\tqi1.front() = " << qi1.front() << std::endl;
	std::cout << "\tqi1.back() = " << qi1.back() << std::endl;

	


}


void STL_adapter_module::test2(void) {}


void STL_adapter_module::test3(void) {}


void STL_adapter_module::test4(void) {}


void STL_adapter_module::test5(void) {}


void STL_adapter_module::test6(void) {}