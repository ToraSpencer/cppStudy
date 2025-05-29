#include <iostream>
#include <string>
#include <typeinfo>

#include <cstdio>

#include "chap_syntax.h"
 

#define EPS 1e-10					//定义非常小的一个量EPSilon，当浮点数不大于这个值时，视为0
#define PI 3.14159

//	知识点
/*	
 
		C风格的强制类型转换
					(T)arg;

			
		四种显式强制类型转换：
					static_cast 		
								可以执行内置数据类型之间的转换。
								可以执行有继承关系的指针、引用的转换，但是类对象之间的转换建议还是用dynamic_cast更安全。
								

					dynamic_cast 		
								可以执行有继承关系的类对象的指针、引用的转换。
								转换前会类型安全检查，如果不安全的话则转换失败，返回NULL指针。
								向下造型的时候一定要使用，如基类指针/引用转换为派生类指针/引用，此时很容易发生安全问题。
								

					const_cast 
								可以去除、增添变量的const属性，一般不会使用。

					reinterpret_cast 
								类似于C风格的强制类型转换，不安全。


	
		类型安全转换：
					子类转换成父类是安全的，父类转换成子类是不安全的。
					可以理解为子类的信息是多于父类的，子类转换成父类时，大不了丢掉一些信息，但是父类转换成子类的话，会有信息空洞，是不安全的。 

*/

 
	virtualModule* syntax_type_cast_module::getInstance()		// 线程不安全的单例模式
	{
		if (nullptr != p_moduleIns) 
			delete p_moduleIns; 

		p_moduleIns = new syntax_type_cast_module;
		return p_moduleIns;
	}



	// test0: const_cast
	void syntax_type_cast_module::test0()
	{
		int  numi1 = 5;
		const int* pci1 = NULL;
		int* pi1 = NULL;

		std::cout << "test0: const_cast" << std::endl;

		pci1 = &numi1;											 			// const指针pci1指向numi1，是底层const。不可以通过pci1来修改numi1的值。
		pi1 = const_cast<int*>(pci1);						 	 // 使用pci1给pi1赋值，但是使用const_cast移除了const属性。


		*pi1 = 6;
		std::cout << "\tpci1 = &numi1; pi1 = const_cast<int*>(pci1);	 *pi1 = 6; " << std::endl;
		std::cout << "\tnumi1 == " << numi1 << std::endl;

	}


	// test1: 使用dynamic_cast()实现向下造型(downcast)
	namespace DYNAMIC_CAST_EXAMPLE
	{
		class Pet
		{
		public: virtual ~Pet() {}
		};


		class Tortoise : public Pet {};


		class Rabbit : public Pet {};


	}


	void syntax_type_cast_module::test1()
	{
		using namespace DYNAMIC_CAST_EXAMPLE;
		Pet* pet = new Rabbit;							// 指向兔子对象的pet指针。

		Tortoise* tortoise = dynamic_cast<Tortoise*>(pet);	// Pet指针试图向下造型为Tortoise指针，理应是失败的
		Rabbit* rabbit = dynamic_cast<Rabbit*>(pet);		// Pet指针指针向下造型为Rabbit指针，理应是成功的，因为Pet指针原先指向的就是Rabbit对象。


		if (tortoise == NULL)					// 转换失败dynamic_cast将会返回NULL指针。
		{
			printf("Pet指针向下造型为Tortoise指针失败\n");
		}
		else
		{
			printf("Pet指针向下造型为Tortoise指针成功\n");
		}

		if (rabbit == NULL)
		{
			printf("Pet指针向下造型为Rabbit指针失败\n");
		}
		else
		{
			printf("Pet指针向下造型为Rabbit指针成功\n");
		}
	}


	void syntax_type_cast_module::test2()
	{
	}


	void syntax_type_cast_module::test3()
	{
	}


	void syntax_type_cast_module::test4()
	{
	}


	void syntax_type_cast_module::test5()
	{
	}


	void syntax_type_cast_module::test6()
	{
	}


	void syntax_type_cast_module::test7()
	{
	}
