#include <iostream>
#include <string>
#include <typeinfo>
#include <vector>
#include <list>
#include <stack>					// std::stack����������
#include <queue>					// std::queue, priority_queue����������

#include <cstdio>

#include "STL_����������.h"

#define EPS 1e-10					//����ǳ�С��һ����EPSilon�������������������ֵʱ����Ϊ0
#define PI 3.14159



// STL����������������std::stack, std::queue, std::priority_queue,
/*
	 �����������ã�
				ʹ��һ���µĽӿڣ����ǵ�ԭ�г���Ľӿڡ�
				����������ģ��
 
 
*/



// std::stack����ջ 
/*
	Ĭ��������deque

	��������������vector, list

	��Ա���ݣ�
			container_type			Container										�ײ���������
			value_type				Container::value_type
			size_type					Container::size_type
			reference					Container::reference
			const_reference		Container::const_reference

	��Ա������
			std::stack<int> s;									// ʹ��Ĭ�ϵ�����dequeʵ��ջ����s��
			std::stack<int, vector<int> > stk;  		// ʹ������vectorʵ��ջ����stk!!!ע��ո�

			operator=										// ��ֵ���������

			void push(const T& el);   				// ��ջ��ѹ��β�ˣ�����Ԫ��el
			void pop();    									// ɾ��ջ����β�ˣ�Ԫ�أ�����������ֵ
			��C++11��emplace							// ��ջ��ԭλ����Ԫ��
			const T& top();    							// ����ջ����β�ˣ�Ԫ�ص�ֵ������ɾ����Ԫ��

			bool empty()									// ���ײ�������Ƿ�Ϊ��	
			size_type size()									// �������ɵ�Ԫ����
			void swap(std::stack& s)						// ������������		


*/


// std::queue�������� 
/*
	Ĭ��������deque
	��������������list
	��Ա���ݣ�
			container_type			Container										�ײ���������
			value_type				Container::value_type
			size_type					Container::size_type
			reference					Container::reference
			const_reference		Container::const_reference


	��Ա������
			std::queue<T>
			std::queue<T,container<T>>

			operator=										// ��ֵ���������

			void push(const T& el);					// ��Ӳ�������β�˼���Ԫ�ء�
			void pop();										// ���Ӳ��������׶�ɾ��Ԫ�ء�

			��C++11��emplace
		  
			T& front();										// �����ײ�Ԫ��
			T& back();										// ����β��Ԫ��
			
			bool empty()									// ���ײ�������Ƿ�Ϊ��
			size_type size()									// �������ɵ�Ԫ����
			void swap(std::queue& q)						// ������������


*/



// priority_queue�������ȼ����С���Ԫ���������еĶ���
/*


*/

 

virtualModule* STL_adapter_module::getInstance()		// �̲߳���ȫ�ĵ���ģʽ
{
	if (nullptr != p_moduleIns)
	{
		delete p_moduleIns;
	}
	p_moduleIns = new STL_adapter_module;
	return p_moduleIns;
}

 

// test0:  std::stack�ĳ��ó�Ա
void STL_adapter_module::test0()
{

	std::cout << "\n\n\n\n" << std::endl;
	std::cout << "test0:  std::stack�ĳ��ó�Ա" << std::endl;
	std::stack<char> stack1;										// Ĭ���������deque����std::stack
	std::stack<int, std::vector<int>> sti1;						// ָ��ʹ��vector������std::stack
	std::stack<float, std::list<float>> stf1;

	// 1. push()����ѹջ����
	stack1.push('a');															 
	stack1.push('b');
	stack1.push('c');
	stack1.push('d');
	stack1.push('e');
 
	// 2. ������
	std::cout << "stack1.empty() = " << stack1.empty() << std::endl;				// �鿴�Ƿ�Ϊ��
	std::cout << "stack1.size() = " << stack1.size() << std::endl;						// �鿴��ǰԪ����

	// 3. д����
	stack1.pop();																								// ��ջ����

	//		3.1 top()������������ջ��Ԫ�ص����ã�����ʱջΪ������׳��쳣��
	debugDisp("stack1.top() = ", stack1.top());							 
	

	debugDisp("test0() finished.");
}


// test1��std::queue��ģ��ĳ�Ա 
void STL_adapter_module::test1()
{
	std::queue<int> qi1;
	std::queue<double, std::list<double>> qd1;

	std::cout << "\n\n\n\n" << std::endl;
	std::cout << "test1��std::queue��ģ��ĳ�Ա " << std::endl;

	qi1.push(0);						
	qi1.push(1);
	qi1.push(2);

	std::cout << "\tqi1.front() = " << qi1.front() << std::endl;
	std::cout << "\tqi1.back() = " << qi1.back() << std::endl;

	


}


void STL_adapter_module::test2() {}


void STL_adapter_module::test3() {}


void STL_adapter_module::test4() {}


void STL_adapter_module::test5() {}


void STL_adapter_module::test6() {}