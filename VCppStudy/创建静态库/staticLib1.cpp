// 创建静态库
/*
		创建生成静态库的项目——创建visual c++ win32控制台应用程序，在应用程序类型中选择“静态库”
		生成的静态库默认名称为项目名称，要想修改可以进入项目属性→ 常规→ 目标文件名。
*/

#include <iostream>
#include "staticLib1.h"


int add(const int a, const int b)
{
	std::cout << "调用了静态库staticLib1中的add函数。" << std::endl;

	return a + b;
}


int add(const int a, const int b, const int c)
{
	std::cout << "调用了静态库staticLib1中的add函数。" << std::endl;

	return a + b + c;
}


template <typename T>
T minus(const T a, const T b)
{
	return (a - b);
}


template <typename T>
T minus(const T a, const T b, const T c)
{
	return (a - b - c);
}


template <typename T1, typename T2, typename T3, typename T4>
T1 minus(const T1 a, const T2 b, const T3 c, const T4 d)
{
	T1 b0 = static_cast<T1>(b);
	T1 c0 = static_cast<T1>(c);
	T1 d0 = static_cast<T1>(d);
	return (a - b0 - c0 - d0);

}


template <typename T>
T divi(const T a, const T b)
{
	return a / b;
}


template <typename T>
T timer<T>::doTimes(const T a, const T b)
{
	this->counter++;
	return a * b;
}




// 模板函数需要特化之后才能在静态库中输出： 

/////////////////////////////////////////////////////////////////////////////////////////////////////////// 模板特化：
template int minus(const int, const int);
template float minus(const float, const float);
template double minus(const double, const double);

#ifdef ERROR_EXAMPLE1
template int minus(const int, const int, const int);
template float minus(const float, const float, const float);
template double minus(const double, const double, const double);
#endif

template int minus(const int, const int, const int, const int);
template float minus(const float, const int, const int, const int);

template int divi(const int, const int);
template float divi(const float, const float);
template double divi(const double, const double);

template int timer<int>::doTimes(const int, const int);
template float timer<float>::doTimes(const float, const float);
template double timer<double>::doTimes(const double, const double);


