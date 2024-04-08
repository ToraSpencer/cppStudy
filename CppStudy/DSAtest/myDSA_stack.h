#pragma once

#include <iostream>
#include <vector>
#include <list>
#include <stack>
#include <map>
#include <unordered_map>
#include <set>
#include <algorithm>
#include <exception>
#include <limits>


// MinStack类——最小栈——可在常数时间内返回栈中元素最小值；  
template <typename T>
class MinStack 
{
protected:
	std::stack<T> stack_ori;
	std::stack<T> stack_min;				// 同步存储stack_ori里每一个坑位对应的最小值；

public:
	MinStack() 
	{
		stack_min.push(std::numeric_limits<T>::max());
	}


	void push(const T x) 
	{
		stack_ori.push(x);
		stack_min.push(std::min(stack_min.top(), x));		// 某个元素x压入栈时，其位置不会改变，该位置对应的最小值也不会改变；
	}


	T pop()
	{
		if (this->stack_ori.empty()) 
			throw(std::underflow_error("!!!Error! the stack is empty."));

		T topElem = stack_ori.top();
		stack_ori.pop();
		stack_min.pop();

		return topElem;
	}


	T top()
	{
		return stack_ori.top();
	}


	T getMin() 
	{
		return stack_min.top();
	}
}; 




namespace STACK
{
	void test0(); 
	void test1();
	void test2();
	void test3();
	void test4();
	void test5();
	void test6();
	void test7();
	void test8();
	void test9();
	void test10();
	void test11();
	void test12();
	void test13();
	void test14();
	void test15();
	void test16();


}