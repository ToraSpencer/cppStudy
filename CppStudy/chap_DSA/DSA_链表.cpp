#include <iostream>
#include <string>
#include <typeinfo>

#include <cstdio>

#include "DSA_����.h"

#define EPS 1e-10					//����ǳ�С��һ����EPSilon�������������������ֵʱ����Ϊ0
#define PI 3.14159


virtualModule* DSA_linked_list_module::getInstance()		// �̲߳���ȫ�ĵ���ģʽ
{
	if (nullptr != p_moduleIns)
	{
		delete p_moduleIns;
	}
	p_moduleIns = new DSA_linked_list_module;
	return p_moduleIns;
}



 
void DSA_linked_list_module::test0(void) 
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
 

void DSA_linked_list_module::test1(void) {}


void DSA_linked_list_module::test2(void) {}


void DSA_linked_list_module::test3(void) {}


void DSA_linked_list_module::test4(void) {}



void DSA_linked_list_module::test5(void) {}



void DSA_linked_list_module::test6(void) {}
