#include <iostream>
#include <set>
#include <string>
#include <typeinfo>
#include <algorithm>
#include <utility>
#include <type_traits>

#include "stdlib_类型支持库.h"


#include <cstdio>
#include <cassert>			//提供宏函数assert()


 

#define EPS 1e-10					//定义非常小的一个量EPSilon，当浮点数不大于这个值时，视为0
#define PI 3.14159


// 知识点
/*
	主要相关头文件
			<typeinfo>
			<type_traits>
			<cstddef>
			<limits>
			<typeindex>

	is_xxx系列类模板（C++11）
			用于判断数据对象是否是xxx类型。
			如is_pointer, is_null_pointer, is_const, is_signed.... 
			定义于<type_traits>
			封装了一个static的bool成员变量value，用is_xxx<type>::value的值来判断type类型是否是xxx类型

*/


virtualModule* stdlib_type_support_module::getInstance()		// 线程不安全的单例模式
{
	if (nullptr != p_moduleIns)
	{
		delete p_moduleIns;
	}
	p_moduleIns = new stdlib_type_support_module;
	return p_moduleIns;
}


 


// test0: is_xxx系列类模板判断类型、属性
void stdlib_type_support_module::test0(void)
{
	std::cout << "\n\n\n\n" << std::endl;
	std::cout << "test0:  is_xxx系列类模板判断类型、属性" << std::endl;

	std::cout << std::is_pointer<int>::value << std::endl;
	std::cout << std::is_pointer<int *>::value << std::endl;
	std::cout << std::is_pointer<int &>::value << std::endl;
	std::cout << std::is_pointer<int **>::value << std::endl;
	std::cout << std::is_pointer<int[10]>::value << std::endl;
	std::cout << std::is_pointer<std::nullptr_t>::value << std::endl;



}


// test1: typeid()函数
void stdlib_type_support_module::test1(void)
{
	std::cout << "test1: typeid()函数 :" << std::endl << std::endl;

	// typeid()返回type_info类对象，其中name()方法返回数据类型名： 
	
	std::cout << "typeid(5).name() = ：" << typeid(5).name() << std::endl;
	std::cout << "typeid(3.12).name() = " << typeid(3.12).name() << std::endl;
	std::cout << "typeid('c').name() = " << typeid('a').name() << std::endl;
	std::cout << "typeid(\"helloWorld\").name() = " << typeid("helloWorld").name() << "	//字符串的本质是字符数组。" << std::endl;

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



// test2: isxxx()系列函数
void stdlib_type_support_module::test2(void)
{
	int* pi = NULL;
	typedef double* dptr;

	// 尖括号中的参数是类型、不是变量。
	// 圆括号中参数列表只能为空，用于返回value;

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





