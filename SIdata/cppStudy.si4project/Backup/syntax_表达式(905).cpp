#include <iosfwd>
#include <ios>
#include <istream>
#include <ostream>
#include <iostream>
#include <string>
#include <typeinfo>

#include <cstdio>

#include "syntax_���ʽ.h"
 
#define EPS 1e-10					//����ǳ�С��һ����EPSilon�������������������ֵʱ����Ϊ0
#define PI 3.14159



// C++�﷨�������ʽ��constexpr
/*
		 
*/



virtualModule* syntax_expression_module::getInstance()		// �̲߳���ȫ�ĵ���ģʽ
{
	if (nullptr != p_moduleIns)
	{
		delete p_moduleIns;
	}
	p_moduleIns = new syntax_expression_module;
	return p_moduleIns;
}



 


// test0:�������ʽconstexpr�ļ�Ӧ��
namespace CONSTEXPR_APPLICATION1 
{
	constexpr unsigned fooConst()			// ����ֵΪconstexpr�ĺ���
	{
		return 9;
	}

}

void syntax_expression_module::test0(void)
{
	using namespace CONSTEXPR_APPLICATION1;
	int arr[fooConst()];				// fooConst()��������һ���������ʽ�����������������顣

	std::cout << sizeof(arr) << std::endl;

}



void syntax_expression_module::test2(void) 
{

}



void syntax_expression_module::test3(void)
{

}



void syntax_expression_module::test4(void)
{

}



void syntax_expression_module::test5(void)
{

}



void syntax_expression_module::test6(void)
{

}



void syntax_expression_module::test1(void)
{

}