#include <string>
#include <iostream>
#include <typeinfo>
#include <exception>
#include <stdexcept>

#include <cstdio>
#include "syntax_���������.h" 

#define EPS 1e-10					//����ǳ�С��һ����EPSilon�������������������ֵʱ����Ϊ0
#define PI 3.14159



// ֪ʶ��
/*
		



*/


virtualModule* syntax_overloaded_operator_module::getInstance()		// �̲߳���ȫ�ĵ���ģʽ
{
	if (nullptr != p_moduleIns)
	{
		delete p_moduleIns;
	}
	p_moduleIns = new syntax_overloaded_operator_module;
	return p_moduleIns;
}





namespace OVERLOADED_OPERATOR_EXAMPLE1 
{
	class Complex					// �Զ��帴����
	{
	public:
		float real;
		float imag;

		// ��Ԫ����������
		friend std::istream& operator >> (std::istream&, const Complex&);
		friend std::ostream& operator<<(std::ostream&, const Complex&);

		//		1. ���졢����������
		Complex();
		Complex(float x, float y);

		//		2. static��Ա����
		//		3. �Գ�Ա����get / set�ĺ���



		//		4. ��������������ĺ���
		Complex& operator+(const Complex& cc)	const;			// ���ؼӷ������
		Complex& operator=(const Complex& cc);		// ���ظ�ֵ�����
		operator float();													// ����C��������ת�������
	};

	std::istream& operator >> (std::istream&, Complex&);									// ����<<�������������һ������
	std::ostream& operator<<(std::ostream&, const Complex&);						// ����>>������������һ������

	Complex::Complex() : real(0), imag(0)
	{}


	Complex::Complex(float x, float y) : real(x), imag(y)
	{}

	Complex& Complex::operator+(const Complex& cc)	const
	{
		Complex temp;

		temp.real = real + cc.real;
		temp.imag = imag + cc.imag;

		return temp;
	}


	Complex& Complex::operator=(const Complex& cc)
	{
		Complex temp;

		temp.real = cc.real;
		temp.imag = cc.imag;

		return temp;
	}


	Complex::operator float()
	{
		float temp;

		// ���������鲿��Ϊ0���׳��쳣������ת��ʧ�ܡ�
		if (this->imag > EPS || this->imag < -EPS)			// �ж�һ���������Ƿ�Ϊ0����ȷ����
		{
			throw std::invalid_argument("imaginary part is not zero;");
		}

		temp = this->real;

		return temp;

	}

	std::istream& operator >> (std::istream& is, Complex& cc)
	{
		is >> cc.real >> cc.imag;
		return is;
	}

	std::ostream& operator<<(std::ostream& os, const Complex& cc)
	{
		os << cc.real;
		if (cc.imag >= 0)
		{
			os << " + ";
		}
		else
		{
			os << " - ";
		}
		os << "i" << cc.imag;

		return os;
	}

}



// test0���Զ��帴����Complex�г��������������
void syntax_overloaded_operator_module::test0(void)
{
	using namespace OVERLOADED_OPERATOR_EXAMPLE1;
	Complex c1 = Complex();
	Complex c2 = Complex(3,0);
	Complex c3 = Complex(2,5);

	std::cout << "\n\n\n\n" << std::endl;
	std::cout << "test0���Զ��帴����Complex�г��������������" << std::endl;


	std::cout << "\tc1 == " << c1 << std::endl;
	std::cout << "\tc2 == " << c2 << std::endl;
	std::cout << "\tc3 == " << c2 << std::endl;

	c1 = c3;
	std::cout << "\tc1 = c3; c1 == " << c1 << std::endl;
	

	// !!!!!?????????????
	std::cout << "\t��ֵ����������д����Ժ��ٸ���;" << std::endl;
	c1 = c2 + c3;
	std::cout << "\tc1 = c2 + c3; c1 == " << c1 << std::endl;
	
	std::cout << "\ttypeid(c1).name()" << typeid(c1).name() << std::endl;


}


void syntax_overloaded_operator_module::test1(void) {}


void syntax_overloaded_operator_module::test2(void) {}


void syntax_overloaded_operator_module::test3(void) {}


void syntax_overloaded_operator_module::test4(void) {}


void syntax_overloaded_operator_module::test5(void) {}


void syntax_overloaded_operator_module::test6(void) {}