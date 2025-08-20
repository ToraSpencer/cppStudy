#include <string>
#include<iostream>
#include <cstddef>
#include <memory>
#include <iterator>

#include <cstdio>


#include "basicTypes_数组.h"



// 知识点
/*
			1. 数组的维度必须是一个常量表达式
			
			2. 字符数组的特殊性：
							可以用字符串字面量来初始化char[]，注意末尾元素是'\0'，但是这样做貌似是不安全的？？？
			3. size_t类型：
							数组下标一般定义为size_t类型
							是一个机器相关的无符号整形
							在<cstddef>中定义
							被设计得足够大以便能表示内存中任意对象的大小。
			4. 缓冲区溢出错误
							即数组下标越界。
							一般编译器都检查不出来，只能自己小心。

			5. 引用的数组——不存在
				 数组的引用：
								int (&arri)[10];		// arri是一个10元素int数组的引用。

			6. 指针的数组：
								 int *(piarr)[10];					// piarr是含有10个int*指针元素的数组。
				数组的指针：
									int (*parri)[10];						// parri是数组的指针，指向一个10元素的int数组。
									float (*parrf)[] = {1.11, 2.22, 3.33};			// parrf是float数组的指针。


			7. 数组作为函数的参数
							向函数传递一个数组，无论是值传递还是引用传递，会退化为数组首元素的指针。
							void printf(const int[]);	// []内不需要写容量，写了也白写
																				// 因为数组是以指针的形式传递进函数的，不含有容量信息。
																				// 本质上传递的是const int*
			8. 数组的初始化——见test4
							全局数组的元素值会自动初始化为0，局部数组不会初始化。
							可以使用memset()函数将数组元素值初始化为0，并且此后的任意时刻都可以将数组所有元素值置0；
						
*/



virtualModule* basicTypes_array_module::getInstance()		// 线程不安全的单例模式
{
	if (nullptr != p_moduleIns)
	{
		delete p_moduleIns;
	}
	p_moduleIns = new basicTypes_array_module;
	return p_moduleIns;
}





// test0: 数组的声明、初始化、基本用法
void basicTypes_array_module::test0()
{
	std::cout << "\n\n\n\n" << std::endl;
	std::cout << "test0: 数组的声明、初始化" << std::endl;

	// 声明数组时，数组维度必须是一个常量表达式：
	int arri1[5];
	const size_t size1 = 4;
	float arrf1[size1]; 
	constexpr size_t size2 = 3;
	float arrf2[size2];									// 上面如果不指明size1是常量，size2是常量表达式的话，编译不通过。  

	// 声明时如果赋初始值，则可以不写维度：
	int arri2[] = {1,2,3};


	// 列表初始化可以只初始化部分数组。
	int arri3[5] = { 9 };					// 首元素设为9，其他元素默认初始化，值为0；
	for (int i: arri3)  
		std::cout << "\t" << i; 
	std::cout << std::endl;


	// 使用sizeof可以获取数组的容量、元素数
	std::cout << "\tarri1的容量为：sizeof(arri1) == " << sizeof(arri1) << std::endl;
	std::cout << "\tarrf1的元素数目为：sizeof(arrf1)/sizeof(float) == " << sizeof(arrf1) / sizeof(float) << std::endl;
	std::cout << "\tarrf1的元素数目为：sizeof(arrf2)/sizeof(float) == " << sizeof(arrf2) / sizeof(float) << std::endl;
}




// test1:  指针的数组、数组的指针。
void basicTypes_array_module::test1()
{
	int* (arr1)[10];			// arr1是指针的数组, arr1是数组名
	int (*arr2)[10];			// arr2是数组的指针，这个数组没有数组名

	std::cout << "\n\n\n\n" << std::endl;
	std::cout << "test1: 指针的数组、数组的指针。" << std::endl;

	std::cout << "sizeof(int) == " << sizeof(int) << std::endl;
	std::cout << "sizeof(int*) == " << sizeof(int*) << std::endl;
	std::cout << "sizeof(void*) == " << sizeof(void*) << std::endl;


	std::cout << "sizeof(arr1) == " << sizeof(arr1) << std::endl;      // sizeof(数组名)返回的是整个数组的容量
	std::cout << "sizeof(arr2) == " << sizeof(arr2) << std::endl;      // arr2不是数组名，只是一个指针，C++里所有指针容量都是一样的，由机器决定。


	// 使用指针数组创建二维数组，每行元素数可不相等。
	int intArr0[3] = {1,2,3};
	int intArr1[4] = {11,12,13,14};
	int intArr2[5] = {21, 22, 23, 24, 25};

	int* ptrArr[3] = {&intArr0[0], &intArr1[0], & intArr2[0]};
	
	std::cout << ptrArr[0][0] << std::endl;
	std::cout << ptrArr[1][1] << std::endl;
	std::cout << ptrArr[2][2] << std::endl;
}



// test2: （C++11）标准库函数begin(), end()作用于数组
void basicTypes_array_module::test2()
{
	std::cout << "\n\n\n\n" << std::endl;
	std::cout << "test2: （C++11）标准库函数begin(), end()作用于数组" << std::endl;


	// begin(), end()函数定义于头文件<iterator>
	// 作用于数组分别返回数组的首元素指针、尾后指针。
	int arri1[] = {1,2,3,4,5};
	int* pi = arri1;

	std::cout << "\t遍历数组arri1:" << std::endl;
	while (pi != std::end(arri1))
	{
		std::cout << "\t" << *(pi++);
	}
	std::cout << std::endl;


}



// test3: 数组作为函数参数
namespace ARRAY_ARG 
{

	// 数组作为参数传递给函数，编译期间会自动退化为指针。
	static void foo(const int arr[])
	{
		std::cout << "sizeof(arg) == " << sizeof(arr) << std::endl;			// 注意sizeof()是操作符(operator)，不是函数。

	}
}

void basicTypes_array_module::test3()
{
	using namespace ARRAY_ARG;
	std::cout << "\n\n\n\n" << std::endl;
	std::cout << "test3: 数组作为函数参数"<< std::endl;

	int arr[] = {1,2,3,4,5};

	std::cout << sizeof(arr) << std::endl;			// 结果为20。注意sizeof()是操作符(operator)，不是函数，数组传递给sizeof不会退化为指针。sizeof(arg)也可以写作sizeof arg;
	foo(arr);													// 打印结果为4（32位程序）

	
}



// test4: 数组的初始化
void basicTypes_array_module::test4()
{
	std::cout << "\n\n\n\n" << std::endl;
	std::cout << " test4: 数组的初始化"<< std::endl;

	auto fDisp = [](int* pi, int len)
	{
		for (int i = 0; i<len; i++)
		{
			std::cout << *pi << "  ";
			pi++;
		}
		std::cout << std::endl;
	};


	auto foo = [&fDisp]()
	{
		int arri[10];		// arri在lambda表达式内，是一个局部数组对象。
		fDisp(arri, 10);	// 此时遍历打印arri的所有元素，可以看出没有初始化。
		memset(arri, 0, sizeof(arri));
		fDisp(arri, 10);	// 此时打印全部为0；
	};


	foo();
}


void basicTypes_array_module::test5() {}


void basicTypes_array_module::test6() {}