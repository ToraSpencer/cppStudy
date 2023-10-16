#pragma once

//// error_example1: 静态库中可以输出重载函数，但是模板参数列表相同的模板函数无法输出；
//#define ERROR_EXAMPLE1

int add(const int a, const int b);
int add(const int a, const int b, const int c);


template <typename T>
T minus(const T a, const T b);

#ifdef ERROR_EXAMPLE1			// 与上面minus()模板参数相同，无法在静态库中定义重载；
template <typename T>
T minus(const T a, const T b, const T c);
#endif


// 与上面minus()模板参数不相同；
template <typename T1, typename T2, typename T3, typename T4>
T1 minus(const T1 a, const T2 b, const T3 c, const T4 d);


template <typename T>
T divi(const T a, const T b);


template <typename T>
class timer 
{
public:
	int counter{0};

public:
	timer() {};
	 
	T doTimes(const T a, const T b);

	int getCounter() 
	{
		return this->counter;
	}
};



 