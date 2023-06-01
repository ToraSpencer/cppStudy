#include <cmath>								// ������ѧ����
#include <complex>							// ������
#include <valarray>							// ������ֵ�����������ģ��
#include <random>							// ��C++11�������������
#include <numeric>
#include <ratio>
#include <cfenv>


#include <iostream>
#include <string>
#include <typeinfo>


#include <cstdlib>
#include <ctime>
#include <cstdio>


#include "stdlib_��ֵ��.h"

 

#define EPS 1e-10					// ����ǳ�С��һ����EPSilon�������������������ֵʱ����Ϊ0
#define PI 3.14159



//  ֪ʶ��
/*
	<cmath>			������ѧ����
	<complex>		��������
	<valarray>		��ʾ�Ͳ���ֵ���������
	<random>		(C++11 ��)	��������������ֲ�
	<numeric>		������ֵ����ֵ����
	<ratio>			(C++11 ��)	����ʱ����������
	<cfenv>			(C++11 ��)	���㻷�����ʺ���
	<bit>			(C++20 ��)	λ���ݺ���
	<numbers>		(C++20 ��)	��ѧ����


	��ѧ���е����Ǻ���ֻ�ϻ��Ȳ��ϽǶȡ�


	

*/

virtualModule* stdlib_numerical_module::getInstance()		// �̲߳���ȫ�ĵ���ģʽ
{
	if (nullptr != p_moduleIns)
	{
		delete p_moduleIns;
	}
	p_moduleIns = new stdlib_numerical_module;
	return p_moduleIns;
}




// test0: <cmath>�е������궨�壬����غ���
void stdlib_numerical_module::test0(void)
{
	std::cout << "\n\n\n\n" << std::endl;
	std::cout << "test0: <cmath>�е������궨�壬����غ���" << std::endl;

	// �꣺�����INFINITY����������һ��float
	std::cout << "INFINITY == " << INFINITY << std::endl;
	std::cout << "INFINITY+123 == " << INFINITY+123 << std::endl;
	std::cout << "typeid(INFINITY).name() == " << typeid(INFINITY).name() << std::endl;



	// INFINITY���Բ���Ƚ�����
	std::cout << (INFINITY > 999) << std::endl; 


	// ʹ�ú���bool isinf()���ж�һ�����Ƿ�Ϊ�����:
	std::cout << "isinf(INFINITY) == " << isinf(INFINITY) << std::endl;

}



// test1: <cmath>�еĳ�����ͨ��ֵ����
void stdlib_numerical_module::test1(void)
{
	std::cout << "\n\n\n\n" << std::endl;
	std::cout << "test1: <cmath>�еĳ�����ͨ��ֵ����" << std::endl;

	std::cout << "\t����ֵ��	abs(-2) == " << abs(-2) << std::endl;
	std::cout << "\t��������ȡ����	round(5.7) == " << round(5.7) << std::endl;
	std::cout << "\t�����㣺	pow(2,5) == " << pow(2,5) << std::endl;
}


// test2: <complex>�е�ʵ�����������󣬼����Ա��������غ�������������ء�
void stdlib_numerical_module::test2(void)
{
	std::complex<double>	z1(0,1);
	std::complex<double> z2 = std::polar(1.0, PI/3);

	std::cout << "\n\n\n\n" << std::endl;
	std::cout << "test2:	<complex>�е�ʵ�����������󣬼����Ա��������غ�������������ء�" << std::endl;


	// ���캯��
	std::cout << "\tcomplex��Ĺ��캯����" << std::endl;
	std::cout << "\t\tcomplex<double> z1(1,2); z1 = " << z1 <<std::endl;
	std::cout << "\t\tcomplex<double> z2; z2 = polar(1.0,PI/3); z2 = " << z2 << std::endl;
	std::cout << std::endl;


	// �����������
	std::cout << "\tcomplex�����ص������" << std::endl;
	std::cout<< z1 * z2 << std::endl;

	z2 = z1;
	z2 = std::complex<double>(10,20);
	std::cout << z2 << std::endl;
	std::cout << std::endl;

	// complex��ĳ�Ա������
	std::cout << "z1.real() == " << z1.real() << std::endl;
	std::cout << "z2.imag() == " << z1.imag() << std::endl;
	std::cout << std::endl;

	// ��complex����ص����ⶨ��ĺ��������صĺ�����
	std::cout << "abs(z1) == " << abs(z1) << std::endl;
	std::cout << "arg(z1) == " << arg(z1) << std::endl;
	std::cout << "conj(z1) == " << conj(z1) << std::endl;
	std::cout << std::endl;
}


// test3: C++���������������<random>�������������ʹ��
void stdlib_numerical_module::test3(void)
{
	std::default_random_engine e;								// ��������������������
	std::uniform_int_distribution<unsigned int>	UID_ui(1, 10);
	std::uniform_int_distribution<int>	UID_i(-100, 100);
	std::uniform_real_distribution<float> URD_f(-10, 10);

	std::cout << "\n\n\n\n" << std::endl;
	std::cout << "test3: C++���������������<random>�������������ʹ��" << std::endl;

	// ���ȷֲ���int, unsigned int, float
	std::cout << UID_i(e) << std::endl;
	std::cout << UID_ui(e) << std::endl;
	std::cout << URD_f(e) << std::endl << std::endl;


	//			ÿ�����µ��������������������µ��������
	std::cout << URD_f(e) << std::endl;



}


// test4: C���������������
void stdlib_numerical_module::test4(void)
{
	std::cout << "\n\n\n\n" << std::endl;
	std::cout << "test4: C���������������" << std::endl;
	

	srand(time(NULL));				// �Ե�ǰʱ��Ϊ���ӳ�ʼ�������������
	int a = 50;
	int b = 100;

	//	���ȷֲ����������
	//			[a, b)��������������
	std::cout << rand() % (b - a) + a << std::endl;
	//			[a, b]��������������
	std::cout << rand() % (b - a + 1) + a << std::endl;


}


void stdlib_numerical_module::test5(void) {}


void stdlib_numerical_module::test6(void) {}



