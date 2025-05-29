#include <iostream>
#include <string>
#include <typeinfo>
#include <algorithm>
#include <iterator>


#include <cstdio>
#include "STL_iterator迭代器.h"


#define EPS 1e-10					//定义非常小的一个量EPSilon，当浮点数不大于这个值时，视为0
#define PI 3.14159


// 知识点
/*
	1. (C++11)<iterator>中提供了begin(), end()函数，可以获取数组的首部指针和尾后指针。
	
	2. 迭代器运算
				两个迭代器加减运算返回int，即他们之间的间隔。
				
	3. 判断迭代器是否为空——与尾后迭代器比较。


*/


virtualModule* STL_iterator_module::getInstance()		// 线程不安全的单例模式
{
	if (nullptr != p_moduleIns)
	{
		delete p_moduleIns;
	}
	p_moduleIns = new STL_iterator_module;
	return p_moduleIns;
}






// test0:  
void STL_iterator_module::test0()
{
	


}


void STL_iterator_module::test1()
{



}


void STL_iterator_module::test2()
{



}


void STL_iterator_module::test3()
{



}


void STL_iterator_module::test4()
{



}


void STL_iterator_module::test5()
{



}


void STL_iterator_module::test6()
{



}



