#include <cmath>								// 常用数学函数
#include <complex>							// 复数类
#include <valarray>							// 面向数值计算的数组类模板
#include <random>							// （C++11）随机数生成器
#include <numeric>
#include <ratio>
#include <cfenv>


#include <iostream>
#include <string>
#include <typeinfo>


#include <cstdlib>
#include <ctime>
#include <cstdio>


#include "stdlib_数值库.h"

 

#define EPS 1e-10					// 定义非常小的一个量EPSilon，当浮点数不大于这个值时，视为0
#define PI 3.14159



//  知识点
/*
	<cmath>			常用数学函数
	<complex>		复数类型
	<valarray>		表示和操作值的数组的类
	<random>		(C++11 起)	随机数生成器及分布
	<numeric>		容器中值的数值运算
	<ratio>			(C++11 起)	编译时有理数算术
	<cfenv>			(C++11 起)	浮点环境访问函数
	<bit>			(C++20 起)	位操纵函数
	<numbers>		(C++20 起)	数学常数


	数学库中的三角函数只认弧度不认角度。


	

*/


virtualModule* stdlib_numerical_module::getInstance()		// 线程不安全的单例模式
{
	if (nullptr != p_moduleIns)
	{
		delete p_moduleIns;
	}
	p_moduleIns = new stdlib_numerical_module;
	return p_moduleIns;
}


// test0: <cmath>中的无穷大宏定义，及相关函数
void stdlib_numerical_module::test0(void)
{
	std::cout << "\n\n\n\n" << std::endl;
	std::cout << "test0: <cmath>中的无穷大宏定义，及相关函数" << std::endl;

	// 宏：无穷大INFINITY，本质上是一个float
	std::cout << "INFINITY == " << INFINITY << std::endl;
	std::cout << "INFINITY+123 == " << INFINITY+123 << std::endl;
	std::cout << "typeid(INFINITY).name() == " << typeid(INFINITY).name() << std::endl;



	// INFINITY可以参与比较运算
	std::cout << (INFINITY > 999) << std::endl; 


	// 使用函数bool isinf()来判断一个数是否为无穷大:
	std::cout << "isinf(INFINITY) == " << isinf(INFINITY) << std::endl;

}


// test1: <cmath>中的常用普通数值函数
void stdlib_numerical_module::test1(void)
{
	std::cout << "\n\n\n\n" << std::endl;
	std::cout << "test1: <cmath>中的常用普通数值函数" << std::endl;

	std::cout << "\t绝对值：	abs(-2) == " << abs(-2) << std::endl;
	std::cout << "\t四舍五入取整：	round(5.7) == " << round(5.7) << std::endl;
	std::cout << "\t幂运算：	pow(2,5) == " << pow(2,5) << std::endl;
}


// test2: <complex>中的实例化复数对象，及其成员函数、相关函数、运算符重载。
void stdlib_numerical_module::test2(void)
{
	std::complex<double>	z1(0,1);
	std::complex<double> z2 = std::polar(1.0, PI/3);

	std::cout << "\n\n\n\n" << std::endl;
	std::cout << "test2:	<complex>中的实例化复数对象，及其成员函数、相关函数、运算符重载。" << std::endl;


	// 构造函数
	std::cout << "\tcomplex类的构造函数：" << std::endl;
	std::cout << "\t\tcomplex<double> z1(1,2); z1 = " << z1 <<std::endl;
	std::cout << "\t\tcomplex<double> z2; z2 = polar(1.0,PI/3); z2 = " << z2 << std::endl;
	std::cout << std::endl;


	// 重载运算符：
	std::cout << "\tcomplex类重载的运算符" << std::endl;
	std::cout<< z1 * z2 << std::endl;

	z2 = z1;
	z2 = std::complex<double>(10,20);
	std::cout << z2 << std::endl;
	std::cout << std::endl;

	// complex类的成员函数：
	std::cout << "z1.real() == " << z1.real() << std::endl;
	std::cout << "z2.imag() == " << z1.imag() << std::endl;
	std::cout << std::endl;

	// 与complex类相关的类外定义的函数、重载的函数。
	std::cout << "abs(z1) == " << abs(z1) << std::endl;
	std::cout << "arg(z1) == " << arg(z1) << std::endl;
	std::cout << "conj(z1) == " << conj(z1) << std::endl;
	std::cout << std::endl;
}


// test3: C++中生成随机数——<random>随机数生成器的使用
void stdlib_numerical_module::test3(void)
{
	std::default_random_engine e;								// 随机数生成器的引擎对象
	std::uniform_int_distribution<unsigned int>	UID_ui(1, 10);
	std::uniform_int_distribution<int>	UID_i(-100, 100);
	std::uniform_real_distribution<float> URD_f(-10, 10);

	std::cout << "\n\n\n\n" << std::endl;
	std::cout << "test3: C++中生成随机数——<random>随机数生成器的使用" << std::endl;

	// 均匀分布的int, unsigned int, float
	std::cout << UID_i(e) << std::endl;
	std::cout << UID_ui(e) << std::endl;
	std::cout << URD_f(e) << std::endl << std::endl;


	//			每次重新调用随机数产生器会产生新的随机数：
	std::cout << URD_f(e) << std::endl;
	 
}


// test4: C语言中生成随机数
void stdlib_numerical_module::test4(void)
{
	std::cout << "\n\n\n\n" << std::endl;
	std::cout << "test4: C语言中生成随机数" << std::endl;
	

	srand(time(NULL));				// 以当前时间为种子初始化随机数生成器
	int a = 50;
	int b = 100;

	//	均匀分布的随机整数
	//			[a, b)区间的随机整数：
	std::cout << rand() % (b - a) + a << std::endl;
	//			[a, b]区间的随机整数：
	std::cout << rand() % (b - a + 1) + a << std::endl;


}


// test5: C++中生成整数序列
void stdlib_numerical_module::test5(void)
{ 
	debugDisp("\n\n\n");
	debugDisp("test5: C++中生成整数序列"); 
	 
	// std::iota(begin, end, 首元素值)——生成间隔为1的等差数列：
	std::vector<int> numVec1;
	numVec1.resize(10);
	std::iota(numVec1.begin(), numVec1.end(), 9);
	debugDisp("numVec1 == ");
	traverseSTL(numVec1, disp<int>());
	 

	debugDisp("test5() finished.");
}


void stdlib_numerical_module::test6(void) {}



