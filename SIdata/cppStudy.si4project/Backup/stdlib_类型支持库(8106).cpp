#include <iostream>
#include <set>
#include <string>
#include <typeinfo>
#include <algorithm>
#include <utility>
#include <type_traits>

#include "stdlib_����֧�ֿ�.h"


#include <cstdio>
#include <cassert>			//�ṩ�꺯��assert()


 

#define EPS 1e-10					//����ǳ�С��һ����EPSilon�������������������ֵʱ����Ϊ0
#define PI 3.14159


// ֪ʶ��
/*
	��Ҫ���ͷ�ļ�
			<typeinfo>
			<type_traits>
			<cstddef>
			<limits>
			<typeindex>

	is_xxxϵ����ģ�壨C++11��
			�����ж����ݶ����Ƿ���xxx���͡�
			��is_pointer, is_null_pointer, is_const, is_signed.... 
			������<type_traits>
			��װ��һ��static��bool��Ա����value����is_xxx<type>::value��ֵ���ж�type�����Ƿ���xxx����

*/


virtualModule* stdlib_type_support_module::getInstance()		// �̲߳���ȫ�ĵ���ģʽ
{
	if (nullptr != p_moduleIns)
	{
		delete p_moduleIns;
	}
	p_moduleIns = new stdlib_type_support_module;
	return p_moduleIns;
}


 


// test0: is_xxxϵ����ģ���ж����͡�����
void stdlib_type_support_module::test0(void)
{
	std::cout << "\n\n\n\n" << std::endl;
	std::cout << "test0:  is_xxxϵ����ģ���ж����͡�����" << std::endl;

	std::cout << std::is_pointer<int>::value << std::endl;
	std::cout << std::is_pointer<int *>::value << std::endl;
	std::cout << std::is_pointer<int &>::value << std::endl;
	std::cout << std::is_pointer<int **>::value << std::endl;
	std::cout << std::is_pointer<int[10]>::value << std::endl;
	std::cout << std::is_pointer<std::nullptr_t>::value << std::endl;



}


// test1: typeid()����
void stdlib_type_support_module::test1(void)
{
	std::cout << "test1: typeid()���� :" << std::endl << std::endl;

	// typeid()����type_info���������name()�������������������� 
	
	std::cout << "typeid(5).name() = ��" << typeid(5).name() << std::endl;
	std::cout << "typeid(3.12).name() = " << typeid(3.12).name() << std::endl;
	std::cout << "typeid('c').name() = " << typeid('a').name() << std::endl;
	std::cout << "typeid(\"helloWorld\").name() = " << typeid("helloWorld").name() << "	//�ַ����ı������ַ����顣" << std::endl;

	int i = 1;
	int* p_i = &i;
	std::cout << "int i = 1; int* p_i = &i; typeid(p_i).name() = " << typeid(p_i).name() << std::endl;

	int a[] = { 1,2,3 };
	std::cout << "int a[] = {1,2,3}; typeid(a).name() = " << typeid(a).name() << std::endl;

	int b[2][3] = { {1,2,3},{4,5,6} };
	std::cout << "int b[2][3] = {{1,2,3},{4,5,6}}; typeid(b).name() = " << typeid(b).name() << std::endl;

	class testClass {};
	testClass t;
	std::cout << "class testClass{}; testClass t; typeid(t).name() = " << typeid(t).name() << std::endl;

	std::cout << std::endl;

 

}



// test2: isxxx()ϵ�к���
void stdlib_type_support_module::test2(void)
{
	int* pi = NULL;
	typedef double* dptr;

	// �������еĲ��������͡����Ǳ�����
	// Բ�����в����б�ֻ��Ϊ�գ����ڷ���value;

	auto value1 = std::is_null_pointer<dptr>();
	std::cout << value1 << std::endl;

	std::cout << std::is_null_pointer<int*>::value << std::endl;


	std::cout << "finished " << std::endl;

}


void stdlib_type_support_module::test3(void)
{
 

}


void stdlib_type_support_module::test4(void)
{
 

}


void stdlib_type_support_module::test5(void)
{
 

}


void stdlib_type_support_module::test6(void)
{


}





