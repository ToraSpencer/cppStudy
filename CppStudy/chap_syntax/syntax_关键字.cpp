#include <iostream>
#include <string>
#include <typeinfo>


#include <cstdio>

#include "syntax_关键字.h"

#define EPS 1e-10					//定义非常小的一个量EPSilon，当浮点数不大于这个值时，视为0
#define PI 3.14159



// 知识点
/*
			const
					const指针——顶层、底层const
								一个有顶层const的形参和没有它的函数无法区分。 Record lookup(Phone* const)和 Record lookup(Phone*)无法区分。
								相反，是否有某个底层const形参可以区分。 Record lookup(Account*)和 Record lookup(const Account*)可以区分。

					const和宏的对比——const变量比宏更安全，因为const变量编译的时候会进行错误检查。

					函数中使用const形参
								值传递的形参不需要const修饰
								引用、指针形参使用const修饰，可以保护传入数据不会被函数修改。

					函数前加const修饰
								普通函数和类方法前都可以加const修饰，表示函数返回值是const，不可修改。
								
					函数后加const修饰
								只有非static的类方法可以加const修饰，且const加在函数之后。
								表示该类方法的this指针是const指针，不能更改类成员的值。
		
			static
					源文件内static——源文件内的static函数只能在本源文件内被访问和调用。
					函数内static——函数内static变量相当于一个全局变量。
					类内static——类内的static成员变量属于整个类所有，不属于某一个对象；需要在类外初始化；在静态存储区中。
										 static类方法只能访问static成员变量和static类方法，因为它不能使用this指针。



			auto
					C和C++中都有auto，但是作用有很大的不同。
					
			extern 
			explicit

		C++中相对于C新增加的关键字：
				using 			 
						1. 命名空间,及其内的名字的使用
									(a) using namespace 命名空间名;
									(b) using 命名空间名::名字;
						2. 使用类型别名：
									(a) 标识符 attr(可选) = 类型标识 ;
									(b)	template < 模板形参列表 >
 											using 标识符 attr(可选) = 类型标识 ;

 											
				auto
				
				decltype
						decltype(f()) sum = x;			// 推断sum的类型是函数f的返回类型。
*/



virtualModule* syntax_keyword_module::getInstance()		// 线程不安全的单例模式
{
	if (nullptr != p_moduleIns)
	{
		delete p_moduleIns;
	}
	p_moduleIns = new syntax_keyword_module;
	return p_moduleIns;
}


 



// test0: 关键字const
void syntax_keyword_module::test0(void)
{
	int numi1 = 11;
	int numi2 = 22;
	int* pi1 = NULL;
	int* const cpi1 = &numi1;							// 是一个顶层const，即该指针本身是一个常量，cpi1不可以指向其他位置。
	const int* pci1 = &numi1;							// 是一个底层const，即该指针指向的数据是一个常量。
																				//				不可以通过pci1来修改其指向的numi1的值
																				//				但是该指针可以指向其他位置。
	const int* const cpci1 = &numi1;			//	第一个是底层const，第二个是顶层const，指针本身是常量，规定其指向的数据也应该是常量。		

	std::cout << "\n\n\n\n" << std::endl;
	std::cout << "test0: 关键字const" << std::endl;


	std::cout << "\t顶层/底层const" << std::endl;
	// 顶层const：指针本身是一个常量 
	std::cout << "\t\tint* const cpi1 = &numi1;	*cpci1 == " << *cpi1 << "——顶层const"<< std::endl;


	pi1 = const_cast<int*>(cpi1);							// 可以使用const_cast去除cpi1的const属性， pi1指向的位置可以修改：
	pi1 = &numi2;
	std::cout <<"\t\tpi1 = const_cast<int*>(cpi1); pi1 = &numi2; *pi1 == " << *pi1 << std::endl;


	// 底层const：指针指向的数据是一个常量
	std::cout << "\t\tconst int* pci1 = &numi1; *pci1 == " << *pci1<< "——底层const"<< std::endl;
	pci1 = &numi2;												// 底层const指针可以指向其他位置：
	std::cout << "\t\tpci1 = &numi2; *pci1 ==  " << *pci1 << std::endl;


	// 顶层、底层const可以同时出现——指针本身是常量，指向的数据也是常量。
	std::cout << "\t\tconst int* const cpci1 = &numi1; *cpci1 == " << *cpci1<< "——顶层、底层const可以同时存在" << std::endl;
	std::cout << std::endl;

}



// test1: 关键字static
namespace KEYWORD_STATIC 
{
	static int foo1(void)
	{
		int num = 1;
		num++;
		return num;
	}




	static int foo2(void)
	{
		static int num = 1;		// 函数体内的static变量实际上就是全局变量。声明一次后之后的声明都无效。
		num++;
		return num;
	}
}

void syntax_keyword_module::test1(void)
{
	using namespace KEYWORD_STATIC;
	std::cout << "\n\n\n\n" << std::endl;
	std::cout << "test0: 关键字static" << std::endl;


	// 函数内static——函数内的static变量相当于一个全局变量。
  for (int i = 0; i < 5; i++)
  {
      std::cout << "foo1 == " << foo1() << std::endl;
  }

  for (int i = 0; i < 5; i++)
  {
      std::cout << "foo2 == " << foo2() << std::endl;
  }

}



// test: const常量
void syntax_keyword_module::test2(void)
{
	

}


void syntax_keyword_module::test3(void)
{


}


void syntax_keyword_module::test4(void)
{


}



void syntax_keyword_module::test5(void)
{


}



void syntax_keyword_module::test6(void)
{


}
