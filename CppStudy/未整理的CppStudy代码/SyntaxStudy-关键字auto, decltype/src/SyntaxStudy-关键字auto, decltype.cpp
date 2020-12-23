#include <iostream>
#include <string>
#include <cmath>
#include <typeinfo>
using namespace std;


/* auto——（C++11）类型说明符
 * 			让编译器根据初始值来推断变量的类型。
 */
void test1()
{
	cout << "" << endl;
	int a = 1;
	int b = 2;
	auto c = a+b;				// 变量c初始化为a+b的结果。


	cout << "c = a+b = " << c << endl;
	cout << "typeid(c).name() = " << typeid(c).name() << endl;
}

void test2()
{
	int i1 = 5;
	const int ci1 = 10;
	auto p1 = &i1;		// auto会忽略顶层const————即auto声明的指针都不是const
	auto p2 = &ci1;		// 此处是底层const，auto给p2分配的类型是const int*即初始指向int常量的只读指针。
}

int main()
{
	//test1();
	test2();

	return 0;
}


