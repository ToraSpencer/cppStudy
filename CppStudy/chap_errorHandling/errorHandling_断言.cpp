#include <iostream>
#include <string>
#include <typeinfo>

#include <cstdio>

// �������˺�NDEBUG����assert()�ᱻ���á���Ҫ��#include <cassert>֮ǰȡ��NDEBUG�Ķ��壻
#undef NDEBUG
#include <cassert>
#include "errorHandling_����.h"

#define EPS 1e-10					//����ǳ�С��һ����EPSilon�������������������ֵʱ����Ϊ0
#define PI 3.14159



// ����
/*
	1. ������Ϣ��
	����ԭ�͡���void assert( int expression );
	���á����򵥵�˵����������������ش�������ֹ����ִ��
	������̡����ȼ�����ʽ expression�������ֵΪ�٣���Ϊ0������ô������stderr��ӡһ��������Ϣ��Ȼ��ͨ������ abort ����ֹ�������С�

	2. assert�����������Զ��׼��Ĵ���ģ������Ǵ����쳣�ġ�
		������쳣�ǲ�һ���ģ������ǲ�Ӧ�ó��ֵģ��쳣�ǲ��ɱ���ġ�
		c�����쳣����ͨ�������ж����������������и��Ե��쳣������ơ�
 
*/

 
virtualModule* errorHandling_assert_module::getInstance()		// �̲߳���ȫ�ĵ���ģʽ
{
	if (nullptr != p_moduleIns)
	{
		delete p_moduleIns;
	}
	p_moduleIns = new errorHandling_assert_module;
	return p_moduleIns;
}




void errorHandling_assert_module::test0() 
{
	int num;
	std::cout << "please input a positive integer" << std::endl;
	std::cin >> num;

	assert(num > 0 );					// �������˺�NDEBUG����assert()�ᱻ���ã�
	std::cout << "num == " << num << std::endl;			// ��������ֵ����0�Ļ������򲻻����е��������֮ǰ�ͱ�abort�ˡ�

}
 

void errorHandling_assert_module::test1() {}


void errorHandling_assert_module::test2() {}


void errorHandling_assert_module::test3() {}


void errorHandling_assert_module::test4() {}



void errorHandling_assert_module::test5() {}



void errorHandling_assert_module::test6() {}
