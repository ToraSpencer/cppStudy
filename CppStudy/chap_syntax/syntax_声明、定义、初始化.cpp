#include <iosfwd>
#include <ios>
#include <istream>
#include <ostream>
#include <iostream>
#include <string>
#include <typeinfo>

#include <cstdio>
#include "chap_syntax.h"
 
#define EPS 1e-10					//定义非常小的一个量EPSilon，当浮点数不大于这个值时，视为0
#define PI 3.14159



// syntax_声明、定义、初始化
/*
				 
*/




	virtualModule* syntax_declare_define_initialize_module::getInstance()		// 线程不安全的单例模式
	{
		if (nullptr != p_moduleIns) 
			delete p_moduleIns; 
		p_moduleIns = new syntax_declare_define_initialize_module;
		return p_moduleIns;
	}




	// test0: 自动初始化问题
	namespace AUTOMATIC_INITIALIZATION
	{
		class AAA
		{
		private:
			int numi;
			float numf;

		public:
			AAA()
			{
			}

			void disp()
			{
				std::cout << "AAA类型的对象中：numi == " << this->numi << "， numf == " << this->numf << std::endl;
			}
		};


		AAA a_global;
		int numi_global;
		float numf_global;

	}


	void syntax_declare_define_initialize_module::test0()
	{
		using namespace AUTOMATIC_INITIALIZATION;
		extern int intName;					// 声明——声明一个名字
		//int intDefined;							// 定义——创建一个数据实体，和一个名字绑定起来。

		// 函数体外是全局变量，函数体内是局部变量，main函数也算。
		//	全局基本类型变量会自动初始化为0值，局部基本类型的变量不会自动初始化。
		//	定义类对象的时候，不管是局部的还是全局的，都会自动调用无参构造函数。
		//	未初始化的局部变量不可使用。
		AAA a_local; 
		a_global.disp();
		std::cout << "numi_global ==" << numi_global << std::endl;
		std::cout << "" << numf_global << std::endl;

		// 类的构造函数中，可以不显示初始化成员数据。
		//		然后用该构造函数构造的全局对象会自动将成员数据初始化为0值。
		//		局部对象成员数据不会自动初始化，为随机值，但是不会影响该对象的使用。
		a_local.disp();

		debugDisp("test0() finished.");
	}


	void syntax_declare_define_initialize_module::test1()
	{

	}

	void syntax_declare_define_initialize_module::test2()
	{

	}


	void syntax_declare_define_initialize_module::test3()
	{

	}


	void syntax_declare_define_initialize_module::test4()
	{

	}


	void syntax_declare_define_initialize_module::test5()
	{

	}

	void syntax_declare_define_initialize_module::test6()
	{

	}

	void syntax_declare_define_initialize_module::test7()
	{

	}
