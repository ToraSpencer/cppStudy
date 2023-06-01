#include <iostream>
#include <string>
#include <typeinfo>
#include <cstdio>
#include <limits>			// 包含std::numeric_limits<>模板：查询各种算术类型的属性 

#include "basicTypes_内置类型.h"


#define EPS 1e-10					//定义非常小的一个量EPSilon，当浮点数不大于这个值时，视为0
#define PI 3.14159



// 知识点
/*
	内置类型全局变量会自动初始化，局部变量不会。


	char/unsigned char:
		1字节

	short/unsigned short:
		2字节
	
	int/unsigned int:
		16位操作系统：2字节
		32位操作系统：4字节
		64位操作系统：4字节
	
	long/unsigned long:
		16位操作系统：4字节
		32位操作系统：4字节
		64位操作系统：8字节

	想要使用确定位数的整型数可以使用<cstdint>中的如std::int_32t, std::uint_64t等类型；



*/


virtualModule* basicTypes_builtin_types_module::getInstance()		// 线程不安全的单例模式
{
	if (nullptr != p_moduleIns)
		delete p_moduleIns;
	p_moduleIns = new basicTypes_builtin_types_module;
	return p_moduleIns;
}

 
// test0:  std::numeric_limits<>模板：查询各种算术类型的属性 
void basicTypes_builtin_types_module::test0(void) 
{
	// ！！！注意：使用std::numeric_limits<T>::max()和std::numeric_limits<T>::min()需要在预处理器中定义NOMINMAX;
	std::cout << "test0: std::numeric_limits<>模板：查询各种算术类型的属性 " << std::endl;
	auto ret1 = std::numeric_limits<int>::max();						
	auto ret2 = std::numeric_limits<float>::max();
	auto ret3 = std::numeric_limits<double>::max();

	// std::numeric_limits<T>::max()返回类型为constexpr T;
	std::cout << "ret1 == " << ret1 << std::endl;
	std::cout << "typeid(ret1).name() == " << typeid(ret1).name() << std::endl;

	ret1 = 1;
}


void basicTypes_builtin_types_module::test1(void) {}


void basicTypes_builtin_types_module::test2(void) {}


void basicTypes_builtin_types_module::test3(void) {}


void basicTypes_builtin_types_module::test4(void) {}


void basicTypes_builtin_types_module::test5(void) {}


void basicTypes_builtin_types_module::test6(void) {}


