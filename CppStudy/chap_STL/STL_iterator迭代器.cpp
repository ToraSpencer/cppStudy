#include <iostream>
#include <string>
#include <typeinfo>
#include <algorithm>
#include <iterator>


#include <cstdio>
#include "STL_iterator������.h"


#define EPS 1e-10					//����ǳ�С��һ����EPSilon�������������������ֵʱ����Ϊ0
#define PI 3.14159


// ֪ʶ��
/*
	1. (C++11)<iterator>���ṩ��begin(), end()���������Ի�ȡ������ײ�ָ���β��ָ�롣
	
	2. ����������
				�����������Ӽ����㷵��int��������֮��ļ����
				
	3. �жϵ������Ƿ�Ϊ�ա�����β��������Ƚϡ�


*/


virtualModule* STL_iterator_module::getInstance()		// �̲߳���ȫ�ĵ���ģʽ
{
	if (nullptr != p_moduleIns)
	{
		delete p_moduleIns;
	}
	p_moduleIns = new STL_iterator_module;
	return p_moduleIns;
}






// test0:  
void STL_iterator_module::test0(void)
{
	


}


void STL_iterator_module::test1(void)
{



}


void STL_iterator_module::test2(void)
{



}


void STL_iterator_module::test3(void)
{



}


void STL_iterator_module::test4(void)
{



}


void STL_iterator_module::test5(void)
{



}


void STL_iterator_module::test6(void)
{



}



