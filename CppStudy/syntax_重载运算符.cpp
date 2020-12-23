#include <string>
#include <iostream>
#include <typeinfo>
#include <exception>
#include <stdexcept>

#include <cstdio>


using namespace std;

#define EPS 1e-10					//定义非常小的一个量EPSilon，当浮点数不大于这个值时，视为0
#define PI 3.14159





// 知识点
/*
		



*/




/***************************************************************************
***************************************************************************/
// 全局变量、类型定义
class Complex					// 自定义复数类
{
public:
	float real;
	float imag;

// 友元函数声明：
	friend istream& operator>>(istream&, const Complex&);
	friend ostream& operator<<(ostream&, const Complex&);

//		1. 构造、析构函数。
	Complex();
	Complex(float x, float y);

//		2. static成员函数
//		3. 对成员数据get / set的函数
 


//		4. 类内重载运算符的函数
	Complex& operator+(const Complex& cc)	const;			// 重载加法运算符
	Complex& operator=(const Complex& cc);		// 重载赋值运算符
	operator float();													// 重载C风格的类型转换运算符

//		5. 其他函数




};





/***************************************************************************
***************************************************************************/
// extern变量
extern void(*pfun[100])(void);
extern int inputTag, inputNum, interfaceLevel;



/***************************************************************************
***************************************************************************/
// 函数声明
istream& operator>>(istream&, Complex&);									// 重载<<运算符——输入一个复数
ostream& operator<<(ostream&, const Complex&);						// 重载>>运算符——输出一个复数

void set_fun_syntax_overloaded_operator(void);
void start_syntax_overloaded_operator(void);

static void test0(void);
static void test1(void);
static void test2(void);
static void test3(void);
static void test4(void);


/***************************************************************************
***************************************************************************/
// extern函数
extern void traverse_pfun(void);


/***************************************************************************
***************************************************************************/
// 自定义类的实现



/***************************************************************************
***************************************************************************/
// 函数定义
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

	// 若复数的虚部不为0，抛出异常，类型转换失败。
	if (this->imag > EPS || this->imag < -EPS)			// 判断一个浮点数是否为0的正确方法
	{
		throw invalid_argument("imaginary part is not zero;");
	}

	temp = this->real;

	return temp;

}


istream& operator>>(istream& is, Complex& cc)	
{
	is >> cc.real >> cc.imag;
	return is;
}


ostream& operator<<(ostream& os, const Complex& cc) 
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



void set_fun_syntax_overloaded_operator(void) 
{
	pfun[0] = test0;

}



void start_syntax_overloaded_operator(void) 
{
	// 界面层级符置为3，进入三级界面：
	interfaceLevel = 3;
	while (3 == interfaceLevel)
	{
		cout << "\n\n\n\n" << endl;
		cout << "**************************MENU: syntax_overloaded_operator**********************" << endl;
		cout << "Please choose a demon function to run:" << endl;
		cout << "-2: Run all existed demon function." << endl;
		cout << "-1: Back to the previous interface." << endl;
		cout << "0: test0：自定义复数类Complex中常见的重载运算符" << endl;


		inputTag = scanf("%d", &inputNum);

		// 若输入值不是整数，重新输入。
		if (inputTag != 1)
		{
			printf("Invalid input. Please input again:\n");
			setbuf(stdin, NULL);
			continue;
		}

		// 对三级界面输入值的响应。
		switch (inputNum)
		{
		case -2:
			traverse_pfun();
			break;

		case -1:
			interfaceLevel = 2;
			break;

		case 0:
			(*pfun[0])();
			break;

		default:
			printf("Invalid input. Please input again:\n");
			break;
		}


	}
}



// test0：自定义复数类Complex中常见的重载运算符
static void test0(void)
{
	Complex c1 = Complex();
	Complex c2 = Complex(3,0);
	Complex c3 = Complex(2,5);

	cout << "\n\n\n\n" << endl;
	cout << "test0：自定义复数类Complex中常见的重载运算符" << endl;


	cout << "\tc1 == " << c1 << endl;
	cout << "\tc2 == " << c2 << endl;
	cout << "\tc3 == " << c2 << endl;

	c1 = c3;
	cout << "\tc1 = c3; c1 == " << c1 << endl;
	

	// !!!!!?????????????
	cout << "\t赋值运算符重载有错误，以后再更改;" << endl;
	c1 = c2 + c3;
	cout << "\tc1 = c2 + c3; c1 == " << c1 << endl;
	
	cout << "\ttypeid(c1).name()" << typeid(c1).name() << endl;


}
