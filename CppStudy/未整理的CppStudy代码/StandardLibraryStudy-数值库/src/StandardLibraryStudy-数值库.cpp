#include <cmath>							//常用数学函数
#include <complex>							//复数类
#include <valarray>							//面向数值计算的数组类模板
#include <random>							//随机数生成器
#include <numeric>
#include <ratio>
#include <cfenv>

#include <iostream>
#include <string>
#include <typeinfo>
using namespace std;

#define pi 3.14159

//<cmath>
void test1()
{
	cout << "<cmath>: " << endl << endl;

	cout << "无穷大：" << endl;
	cout << INFINITY << endl;
	cout << "用函数bool isinf()来判断一个数是否为无穷大：" << isinf(INFINITY) << endl;
	cout << "INFINITY的类型为float: typeid(INFINITY).name() = " << typeid(INFINITY).name() << endl;
	cout << endl;

	cout << "常用数值函数" << endl;
	cout << "abs(-2) = " << abs(-2) << endl;
	cout << "round(5.7) = " << round(5.7) << endl;
	cout << endl;

	cout << "幂运算用函数pow(),不支持^运算符表示幂运算。 pow(2,5) = " << pow(2,5) << endl;




	cout << endl;
}

//<complex>
void test2()
{
	cout << "<complex>" << endl << endl;

	//构造方法
	cout << "复数对象的构造方法：" << endl;
	complex<double> z1(0,1);
	cout << "complex<double> z1(1,2); z1 = " << z1 << endl;
	complex<double> z2;
	z2 = polar(1.0,pi/3);								//模和辐角必须同是int或float，所以这里1写成1.0
	cout << "complex<double> z2; z2 = polar(1.0,pi/3); z2 = " << z2 << endl;
	cout << endl;



	//重载运算符
	cout << "为复数重载了一系列的运算符：" << endl;
	cout << "复数乘法：z1*z2 = " << z1*z2 << endl;		//复数只能和复数运算，不可以和实数运算，可以将实数改写成复数。
	cout << endl;


	//重载函数
	cout << "重载了exp():" << endl;
	cout << "matlab里的exp(1j*pi/6) = exp(complex<double>(0,pi/6)) =" << exp(complex<double>(0,pi/6)) << endl;
	cout << endl;

	//成员函数、其他函数
	cout << "复数类成员函数和相关函数：" << endl;
	cout << "返回复数的实部：z1.real() = " << z1.real() << endl;
	cout << "返回复数的虚部: z1.imag() = " << z1.imag() << endl;
	cout << "返回复数的模: abs(z1) = " << abs(z1) << endl;
	cout << "返回复数的辐角：arg(z1) = " << arg(z1) << endl;
	cout << "返回复数的共轭：conj(z1) = " << conj(z1) << endl;
	cout << endl;

	//复数对象的赋值：
	cout << "只能构造出一个新复数对象，然后将该对象赋值给另一个对象，来实现赋值：" << endl;
	z2 = complex<double>(2,3);
	cout << "z2 = complex<double>(2,3); z2 = " << z2 << endl;
	cout << endl;

}

//<random>
void test3()
{
	cout << "<random>" << endl << endl;

	default_random_engine e;
	uniform_int_distribution<unsigned> u(1,10);
	uniform_int_distribution<int> i(-100,100);
	uniform_real_distribution<float> f(-10,10);



	unsigned randomUnsigned = u(e);
	int	randomInt = i(e);
	float randomFloat = f(e);
	float randomFloat_new = f(e);

	cout << "1~10之间均匀随机的整数: randomInt = " << randomUnsigned << endl;
	cout << "-100~100之间均匀随机分布的整数：" << randomInt << endl;
	cout << "-10~10之间连续均匀分布的随机浮点数" << randomFloat << endl;
	cout << "每次调用随机数产生器会产生新的随机数：randomFloat_new = f(e) = " << randomFloat_new << endl;
	cout << endl;

	cout << "每次调用随机数产生器会产生新的随机数：" << endl;
	float temp;
	for(int i = 1;i<=10;i++)
	{
		temp = f(e);
		cout << temp << "  " << endl;
	}
}

int main()
{
	//test1();
	test2();
	//test3();

	return 0;
}

