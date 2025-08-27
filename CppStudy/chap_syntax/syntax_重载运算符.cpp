#include <string>
#include <iostream>
#include <typeinfo>
#include <exception>
#include <stdexcept>

#include <cstdio>
#include "chap_syntax.h"

#define EPS 1e-10					//定义非常小的一个量EPSilon，当浮点数不大于这个值时，视为0
#define PI 3.14159



// 知识点
/*
		



*/



	virtualModule* syntax_overloaded_operator_module::getInstance()		// 线程不安全的单例模式
	{
		if (nullptr != p_moduleIns)
			delete p_moduleIns;
		p_moduleIns = new syntax_overloaded_operator_module;
		return p_moduleIns;
	}





	namespace OVERLOADED_OPERATOR_EXAMPLE1
	{
		class Complex					// 自定义复数类
		{
		public:
			float real;
			float imag;

			// 友元函数声明：
			friend std::istream& operator >> (std::istream&, const Complex&);
			friend std::ostream& operator<<(std::ostream&, const Complex&);

			//		1. 构造、析构函数。
			Complex();
			Complex(float x, float y);

			//		2. static成员函数
			//		3. 对成员数据get / set的函数
			 

			//		4. 类内重载运算符的函数
			Complex operator+(const Complex& cc)	const;			// 重载加法运算符
			Complex& operator=(const Complex& cc);		// 重载赋值运算符
			operator float();													// 重载C风格的类型转换运算符
		};

		std::istream& operator >> (std::istream&, Complex&);									// 重载<<运算符——输入一个复数
		std::ostream& operator<<(std::ostream&, const Complex&);						// 重载>>运算符——输出一个复数

		Complex::Complex() : real(0), imag(0)
		{
		}


		Complex::Complex(float x, float y) : real(x), imag(y)
		{
		}

		Complex Complex::operator+(const Complex& cc)	const
		{
			Complex temp;

			temp.real = real + cc.real;
			temp.imag = imag + cc.imag;

			return temp;
		}


		Complex& Complex::operator=(const Complex& cc)
		{ 
			this->real = cc.real;
			this->imag = cc.imag;

			return *this;
		}


		Complex::operator float()
		{
			float temp;

			// 若复数的虚部不为0，抛出异常，类型转换失败。
			if (this->imag > EPS || this->imag < -EPS)			// 判断一个浮点数是否为0的正确方法
				throw std::invalid_argument("imaginary part is not zero;");

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
				os << " + ";
			else
				os << " - ";
			os << "i" << cc.imag;

			return os;
		}

	}



	// test0：自定义复数类Complex中常见的重载运算符
	void syntax_overloaded_operator_module::test0()  
	{
		using namespace OVERLOADED_OPERATOR_EXAMPLE1;
		Complex c1 = Complex();
		Complex c2 = Complex(3, 0);
		Complex c3 = Complex(2, 5);

		std::cout << "\n\n\n\n" << std::endl;
		std::cout << "test0：自定义复数类Complex中常见的重载运算符" << std::endl;


		std::cout << "\tc1 == " << c1 << std::endl;
		std::cout << "\tc2 == " << c2 << std::endl;
		std::cout << "\tc3 == " << c2 << std::endl;

		c1 = c3;
		std::cout << "\tc1 = c3; c1 == " << c1 << std::endl;


		// !!!!!?????????????
		std::cout << "\t赋值运算符重载有错误，以后再更改;" << std::endl;
		c1 = c2 + c3;
		std::cout << "\tc1 = c2 + c3; c1 == " << c1 << std::endl;

		std::cout << "\ttypeid(c1).name()" << typeid(c1).name() << std::endl;


	}


	void syntax_overloaded_operator_module::test1() {}


	void syntax_overloaded_operator_module::test2() {}


	void syntax_overloaded_operator_module::test3() {}


	void syntax_overloaded_operator_module::test4() {}


	void syntax_overloaded_operator_module::test5() {}


	void syntax_overloaded_operator_module::test6() {} 

	void syntax_overloaded_operator_module::test7() {}