#include <iostream>
#include <string>
#include <typeinfo>
#include <cstdio>
#include <limits>			// ����std::numeric_limits<>ģ�壺��ѯ�����������͵����� 

#include "basicTypes_��������.h"


#define EPS 1e-10					//����ǳ�С��һ����EPSilon�������������������ֵʱ����Ϊ0
#define PI 3.14159



// ֪ʶ��
/*
	��������ȫ�ֱ������Զ���ʼ�����ֲ��������ᡣ


	char/unsigned char:
		1�ֽ�

	short/unsigned short:
		2�ֽ�
	
	int/unsigned int:
		16λ����ϵͳ��2�ֽ�
		32λ����ϵͳ��4�ֽ�
		64λ����ϵͳ��4�ֽ�
	
	long/unsigned long:
		16λ����ϵͳ��4�ֽ�
		32λ����ϵͳ��4�ֽ�
		64λ����ϵͳ��8�ֽ�

	��Ҫʹ��ȷ��λ��������������ʹ��<cstdint>�е���std::int_32t, std::uint_64t�����ͣ�



*/


virtualModule* basicTypes_builtin_types_module::getInstance()		// �̲߳���ȫ�ĵ���ģʽ
{
	if (nullptr != p_moduleIns)
		delete p_moduleIns;
	p_moduleIns = new basicTypes_builtin_types_module;
	return p_moduleIns;
}

 
// test0:  std::numeric_limits<>ģ�壺��ѯ�����������͵����� 
void basicTypes_builtin_types_module::test0(void) 
{
	// ������ע�⣺ʹ��std::numeric_limits<T>::max()��std::numeric_limits<T>::min()��Ҫ��Ԥ�������ж���NOMINMAX;
	debugDisp("test0: std::numeric_limits<>ģ�壺��ѯ�����������͵����� ");
	constexpr int ret1 = std::numeric_limits<int>::max();						
	constexpr float ret2 = std::numeric_limits<float>::max();
	constexpr double ret3 = std::numeric_limits<double>::max();
	constexpr char ret4 = std::numeric_limits<char>::max();
	constexpr int ret5 = std::numeric_limits<int>::min();
	constexpr float ret6 = std::numeric_limits<float>::min();
	constexpr double ret7 = std::numeric_limits<double>::min();
	constexpr char ret8 = std::numeric_limits<char>::min();
	debugDisp("std::numeric_limits<int>::max() == ", ret1);
	debugDisp("std::numeric_limits<float>::max() == ", ret2);
	debugDisp("std::numeric_limits<double>::max() == ", ret3);
	debugDisp("std::numeric_limits<char>::max() == ", ret4);
	debugDisp("std::numeric_limits<int>::min() == ", ret5);
	debugDisp("std::numeric_limits<float>::min() == ", ret6);
	debugDisp("std::numeric_limits<double>::min() == ", ret7);
	debugDisp("std::numeric_limits<char>::min() == ", ret8);

	// std::numeric_limits<T>::max()��������Ϊconstexpr T; 
	std::cout << "typeid(ret1).name() == " << typeid(ret1).name() << std::endl;

	debugDisp("test0 finished.");
}


void basicTypes_builtin_types_module::test1(void) {}


void basicTypes_builtin_types_module::test2(void) {}


void basicTypes_builtin_types_module::test3(void) {}


void basicTypes_builtin_types_module::test4(void) {}


void basicTypes_builtin_types_module::test5(void) {}


void basicTypes_builtin_types_module::test6(void) {}


