// ������̬��
/*
		�������ɾ�̬�����Ŀ��������visual c++ win32����̨Ӧ�ó�����Ӧ�ó���������ѡ�񡰾�̬�⡱
		���ɵľ�̬��Ĭ������Ϊ��Ŀ���ƣ�Ҫ���޸Ŀ��Խ�����Ŀ���ԡ� ����� Ŀ���ļ�����
*/

#include <iostream>
#include "staticLib1.h"


int add(const int a, const int b)
{
	std::cout << "�����˾�̬��staticLib1�е�add������" << std::endl;

	return a + b;
}


int add(const int a, const int b, const int c)
{
	std::cout << "�����˾�̬��staticLib1�е�add������" << std::endl;

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




// ģ�庯����Ҫ�ػ�֮������ھ�̬��������� 

/////////////////////////////////////////////////////////////////////////////////////////////////////////// ģ���ػ���
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


