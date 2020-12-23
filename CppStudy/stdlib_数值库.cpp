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


using namespace std;

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



/***************************************************************************
***************************************************************************/
// 全局变量、类型定义



/***************************************************************************
***************************************************************************/
// extern变量
extern void(*pfun[100])(void);
extern int inputTag, inputNum, interfaceLevel;



/***************************************************************************
***************************************************************************/
// 函数声明
void set_fun_stdlib_numeric_lib(void);
void start_stdlib_numeric_lib(void);

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
void set_fun_stdlib_numeric_lib(void) 
{
	pfun[0] = test0;
	pfun[1] = test1;
	pfun[2] = test2;
	pfun[3] = test3;
}


void start_stdlib_numeric_lib(void)

{
	// 界面层级符置为3，进入三级界面：
	interfaceLevel = 3;
	while (3 == interfaceLevel)
	{
		cout << "\n\n\n\n" << endl;
		cout << "**************************MENU: stdlib_IO_lib**********************" << endl;
		cout << "Please choose a demon function to run:" << endl;
		cout << "-2: Run all existed demon function." << endl;
		cout << "-1: Back to the previous interface." << endl;
		cout << "0. test0: <cmath>中的无穷大宏定义，及相关函数" << endl;
		cout << "1. test1: <cmath>中的常用普通数值函数 " << endl;
		cout << "2. test2: <complex>中的实例化复数对象，及其成员函数、相关函数、运算符重载" << endl;
		cout << "3. test3: C++中生成随机数——<random>随机数生成器的使用" << endl;


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

		case 1:
			(*pfun[1])();

		case 2:
			(*pfun[2])();

		case 3:
			(*pfun[3])();


		default:
			printf("Invalid input. Please input again:\n");
			break;
		}


	}
}




// test0: <cmath>中的无穷大宏定义，及相关函数
static void test0(void) 
{
	cout << "\n\n\n\n" << endl;
	cout << "test0: <cmath>中的无穷大宏定义，及相关函数" << endl;

	// 宏：无穷大INFINITY，本质上是一个float
	cout << "INFINITY == " << INFINITY << endl;
	cout << "INFINITY+123 == " << INFINITY+123 << endl;
	cout << "typeid(INFINITY).name() == " << typeid(INFINITY).name() << endl;



	// INFINITY可以参与比较运算
	cout << (INFINITY > 999) << endl; 


	// 使用函数bool isinf()来判断一个数是否为无穷大:
	cout << "isinf(INFINITY) == " << isinf(INFINITY) << endl;

}



// test1: <cmath>中的常用普通数值函数
static void test1(void)
{
	cout << "\n\n\n\n" << endl;
	cout << "test1: <cmath>中的常用普通数值函数" << endl;

	cout << "\t绝对值：	abs(-2) == " << abs(-2) << endl;
	cout << "\t四舍五入取整：	round(5.7) == " << round(5.7) << endl;
	cout << "\t幂运算：	pow(2,5) == " << pow(2,5) << endl;
}


// test2: <complex>中的实例化复数对象，及其成员函数、相关函数、运算符重载。
static void test2(void)
{
	complex<double>	z1(0,1);
	complex<double> z2 = polar(1.0, PI/3);

	cout << "\n\n\n\n" << endl;
	cout << "test2:	<complex>中的实例化复数对象，及其成员函数、相关函数、运算符重载。" << endl;


	// 构造函数
	cout << "\tcomplex类的构造函数：" << endl;
	cout << "\t\tcomplex<double> z1(1,2); z1 = " << z1 <<endl;
	cout << "\t\tcomplex<double> z2; z2 = polar(1.0,PI/3); z2 = " << z2 << endl;
	cout << endl;


	// 重载运算符：
	cout << "\tcomplex类重载的运算符" << endl;
	cout<< z1 * z2 << endl;

	z2 = z1;
	z2 = complex<double>(10,20);
	cout << z2 << endl;
	cout << endl;

	// complex类的成员函数：
	cout << "z1.real() == " << z1.real() << endl;
	cout << "z2.imag() == " << z1.imag() << endl;
	cout << endl;

	// 与complex类相关的类外定义的函数、重载的函数。
	cout << "abs(z1) == " << abs(z1) << endl;
	cout << "arg(z1) == " << arg(z1) << endl;
	cout << "conj(z1) == " << conj(z1) << endl;
	cout << endl;
}





// test3: C++中生成随机数——<random>随机数生成器的使用
static void test3(void) 
{
	default_random_engine e;								// 随机数生成器的引擎对象
	uniform_int_distribution<unsigned int>	UID_ui(1, 10);
	uniform_int_distribution<int>	UID_i(-100, 100);
	uniform_real_distribution<float> URD_f(-10, 10);

	cout << "\n\n\n\n" << endl;
	cout << "test3: C++中生成随机数——<random>随机数生成器的使用" << endl;

	// 均匀分布的int, unsigned int, float
	cout << UID_i(e) << endl;
	cout << UID_ui(e) << endl;
	cout << URD_f(e) << endl << endl;


	//			每次重新调用随机数产生器会产生新的随机数：
	cout << URD_f(e) << endl;



}


// test4: C语言中生成随机数
static void test4(void)
{
	cout << "\n\n\n\n" << endl;
	cout << "test4: C语言中生成随机数" << endl;
	

	srand(time(NULL));				// 以当前时间为种子初始化随机数生成器
	int a = 50;
	int b = 100;

	//	均匀分布的随机整数
	//			[a, b)区间的随机整数：
	cout << rand() % (b - a) + a << endl;
	//			[a, b]区间的随机整数：
	cout << rand() % (b - a + 1) + a << endl;


}



