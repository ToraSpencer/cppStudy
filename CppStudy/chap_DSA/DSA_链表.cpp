#include <iostream>
#include <string>
#include <typeinfo>

#include <cstdio>

#include "DSA_链表.h"

#define EPS 1e-10					//定义非常小的一个量EPSilon，当浮点数不大于这个值时，视为0
#define PI 3.14159


virtualModule* DSA_linked_list_module::getInstance()		// 线程不安全的单例模式
{
	if (nullptr != p_moduleIns)
	{
		delete p_moduleIns;
	}
	p_moduleIns = new DSA_linked_list_module;
	return p_moduleIns;
}



 
void DSA_linked_list_module::test0() 
{
	float fnums[6] = {1,2,3,4,5,6};
	LinkedList<float> list1(fnums, 6);
	LinkedList<int> list2 = LinkedList<int>();
	std::cout << list2.InsertElem(-1);
	std::cout << list2.InsertElem(-2);
	std::cout << list2.InsertElem(-3);
	std::cout << list2.InsertElem(-4);
	std::cout << list2.InsertElem(-5);
	std::cout << std::endl;
	list1.Display();
	list2.Display();
	
}
 

void DSA_linked_list_module::test1() {}


void DSA_linked_list_module::test2() {}


void DSA_linked_list_module::test3() {}


void DSA_linked_list_module::test4() {}



void DSA_linked_list_module::test5() {}



void DSA_linked_list_module::test6() {}
