#pragma once

//// error_example1: ��̬���п���������غ���������ģ������б���ͬ��ģ�庯���޷������
//#define ERROR_EXAMPLE1

int add(const int a, const int b);
int add(const int a, const int b, const int c);


template <typename T>
T minus(const T a, const T b);

#ifdef ERROR_EXAMPLE1			// ������minus()ģ�������ͬ���޷��ھ�̬���ж������أ�
template <typename T>
T minus(const T a, const T b, const T c);
#endif


// ������minus()ģ���������ͬ��
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



 