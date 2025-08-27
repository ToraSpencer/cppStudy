#include <iostream>
#include <string>
#include <typeinfo>

#include <memory>
#include <vector>
#include <cstddef>
#include <cstdio>
#include <new>


#include "basicTypes_枚举、共用体、结构体.h"
 

#define EPS 1e-10					//定义非常小的一个量EPSilon，当浮点数不大于这个值时，视为0
#define PI 3.14159



// 知识点
/*
			1. union共用体——共用体的所有成员占用同一段内存，修改一个成员会影响其余所有成员。
			
			2. 枚举特点：
							元素值必须是整型值。
							
			3. 结构体中的内存对齐问题，详见UP_内存管理章节。




*/


virtualModule* basicTypes_enum_union_struct_module::getInstance()		// 线程不安全的单例模式
{
	if (nullptr != p_moduleIns)
	{
		delete p_moduleIns;
	}
	p_moduleIns = new basicTypes_enum_union_struct_module;
	return p_moduleIns;
}



namespace TEST_STRUCT
{
	struct person
	{
		std::string name;
		bool sex;
		unsigned age;
		std::string job;
	};


	struct controlWord				// 使用了位字段的结构体，其中每个成员都是一个字段。
	{
		unsigned int word1 : 4;   	// 4bit为word1的值
		unsigned int : 4;        		// 4bit为空白的占位
		bool word2 : 1;
		bool word3 : 1;
	};


	typedef struct
	{
		char a;
		short b;
		int c;
		long d;							// 32位系统中long的大小是4字节，64位系统中是8字节。
		char e;
		long long f;				// long long的大小是8字节。
	}stru;


	auto dispPerson = [](const TEST_STRUCT::person& p)
	{
		auto dispL = [](auto&& arg)			// arg是一个万能引用。
		{
			std::cout << arg << std::endl;
		};

		//std::cout << p.name << std::endl;
		//std::cout << p.sex << std::endl;
		//std::cout << p.age << std::endl;
		//std::cout << p.job << std::endl;
		dispL(p.name);
		dispL(p.sex);
		return;
	};


}
 

namespace TEST_UNION 
{
	typedef union data
	{
		int numi;
		float numf;
		char ch;
	} unionData;


	template <typename T>
	class Foo
	{
	public:
		union
		{
			T arr[3];
			struct
			{
				T X;
				T Y;
				T Z;
			};
		};

	public:
		Foo(const T x0, const T y0, const T z0) : X(x0), Y(y0), Z(z0) {}
		T& at(const size_t index)
		{
			return this->arr[index];
		}
	};

}



// test0: 结构体的基本使用方法
void basicTypes_enum_union_struct_module::test0()
{
	using namespace TEST_STRUCT;

	std::cout << "\n\n\n\n" << std::endl;
	std::cout << "test0: 结构体的基本使用方法" << std::endl;

	// 结构体实例初始化：
	//		注：C中声明结构体实例时前面要加struct
	//				一般C中使用typedef   person{.....}person; 这样的格式声明结构体，然后声明实例的时候就不用写struct了
	person p1 = {"xiaoming", true, 18, "doctor"};
	person p2 = {};						// 此时所有成员值为0


	dispPerson(p1);
	std::cout << std::endl;
	dispPerson(p2);
	std::cout << std::endl;


}


// test1：枚举类型的基本使用
void basicTypes_enum_union_struct_module::test1()
{
	// 定义枚举类型的主要目的是：增加程序的可读性。
	// 枚举类型最常见也最有意义的用处之一就是用来描述状态量
	std::cout << "\n\n\n\n" << std::endl;
	std::cout << "test0: 结构体的基本使用方法" << std::endl;



	// 定义枚举类型
	enum weekDay{SUN, MON, TUE, WED, THU, FRI, SAT};		// 默认情形下，枚举常量取值为0, 1, 2,...	
	enum color{RED, BLUE, GREEN = 1, YELLOW};						// 取值可重复，此时取值分别为0,1,1,2		



	// 枚举类型的信息
	std::cout << "typeid(SUN).name() " << typeid(SUN).name() << std::endl;	// 枚举常量SUN的类型是weekDay，weekDay即是类型名。
	std::cout << "sizeof(weekDay) == " << sizeof(weekDay) << std::endl;		// 这样返回值是weekDay类型的大小
	std::cout << "sizeof(SUN)" << sizeof(SUN) << std::endl;								// 枚举类型的大小不确定，编译器会根据其值大小来分配，可能是1,2,4字节，一定是整型。
	

	// 简单的应用举例：
	int num;
	int inputValid = 0;
	std::string str;
	enum person{alice = 1, bob, cindy, david, eric, frank, grey};
	std::cout << "请输入要查看的选手编号" << std::endl;
	while(0 == inputValid)
	{
		setbuf(stdin, NULL);
		inputValid = scanf("%d", &num);

		if(0 == inputValid || num < 1 || num > 6)
		{
			std::cout << "输入不合法，请重新输入。" << std::endl;
			setbuf(stdin, NULL);
		}
	}
	switch(num)
	{
		case 1:
			str = "alice";
			break;

		case 2:
			str = "bob";
			break;

		case 3:
			str = "cindy";
			break;

		case 4:
			str = "eric";
			break;

		case 5:
			str = "frank";
			break;

		case 6:
			str = "grey";
			break;

		default:
			break;
	}
	std::cout << num << "号选手是" << str << std::endl;
}


// test2: 共用体的基本使用
void basicTypes_enum_union_struct_module::test2()
{
	using namespace TEST_UNION;
	std::cout << "\n\n\n\n" << std::endl;
	std::cout << " test2:  共用体的基本使用" << std::endl;

	unionData a;
	a.numi = 99;
	debugDisp("sizeof(unionData) == ", sizeof(unionData)); 
	printf("%d, %f, %c\n", a.numi, a.numf, a.ch);

	// union中一个成员的更改，会影响到其他成员
	a.numi = 1;
	printf("%d, %f, %c\n", a.numi, a.numf, a.ch);

	a.numf = 3.14f;
	printf("%d, %f, %c\n", a.numi, a.numf, a.ch);

	a.ch = 'a';
	printf("%d, %f, %c\n", a.numi, a.numf, a.ch);
	
 
}


// test3: 结构体中的内存对齐
void basicTypes_enum_union_struct_module::test3()
{
	using namespace TEST_STRUCT;

	std::cout << "\n\n\n\n" << std::endl;
	std::cout << " test3: 结构体中的内存对齐" << std::endl;

	stru s1 = {1,2,3,4,5,6};
	unsigned char* pc= NULL;
	pc = reinterpret_cast<unsigned char*>(&s1);

	// s1的内存应该是这样的：
	/*
		char a; short b; int c; long d; char e; long long f;

		axbbcccc
		dddddddd
		exxxxxxx
		ffffffff
		所以一共占32字节，结构体实例内部的数据分布可以使用一个unsigned char*指针来查看验证。
	*/

	
	std::cout << "sizeof(s1) == " << sizeof(s1) << std::endl;
	std::cout << "结构体实例s1内部数据分布：" << std::endl;
	for(int i = 1; i <= 32; i++)
	{
		printf("%d. 0x%x\n" , i, *pc);
		pc++;
		if(i >= 32) 
			break; 
			
	}



}



void basicTypes_enum_union_struct_module::test4()
{}



void basicTypes_enum_union_struct_module::test5()
{}


void basicTypes_enum_union_struct_module::test6() 
{

}