#include <iostream>
#include <vector>


#include <cstdio>
#include <cstdlib>


// 知识点
/*
	声明
			声明一个名字。

	定义
			定义一个变量，本质上是创建了与该名字关联的实体。


	初始化
			初始化 == 创建变量 + 赋予初始值
			赋值 == 擦除变量的当前值 + 用新值代替
			
			在函数体内部的内置类型变量将不会被初始化。

			const的变量/对象必须被初始化。

			引用创建的时候必须被初始化。


			左值（l-value）
						可以出现在赋值语句的左边或者右边。
						比如变量；
						被用做左值时，用的是对象的身份（在内存中的位置）。

						
			右值（r-value）
						只能出现在赋值语句的右边，比如常量。
						当一个对象被用作右值的时候，用的是对象的值（内容）；


			短路
						对于逻辑与运算符、逻辑或运算符，都是先求左侧运算对象的值再求右侧运算对象的值。
						若左侧运算可以确定表达式的结果了，则不会再去计算右侧运算，此时右侧运算被短路。


	常见的异常、错误
			缓冲区溢出（栈溢出/数组越界）
			内存泄漏(memory leak)

*/



// size_t
/*
	size_t是标准C库中定义的，它是一个基本的与机器相关的无符号整数的C/C + +类型， 
	它是sizeof操作符返回的结果类型，该类型的大小可选择。
	其大小足以保证存储内存中对象的大小（简单理解为 unsigned int就可以了，64位系统中为 long unsigned int）。
	通常用sizeof(XX)操作，这个操作所得到的结果就是size_t类型。

	类似的还有wchar_t, ptrdiff_t。
		wchar_t就是wide char type，“一种用来记录一个宽字符的数据类型”。
		ptrdiff_t就是pointer difference type，“一种用来记录两个指针之间的距离的数据类型”。
 

*/



// 静态库、动态库
/*
静态库
在应用中，一些公共代码需要反复使用，就把这些代码编译为静态库文件。
在链接步骤中，连接器将从静态库文件取得所需的代码，复制到生成的可执行文件中。
linux系统中静态库文件后缀为.a
windows系统中静态库文件后缀为.lib
有的.lib文件为windows中动态库的导入库文件。
对于作为导入库文件的.lib文件而言，其实际的执行代码位于动态库中。
导入库只包含了地址符号表等，确保程序找到对应函数的一些基本地址信息。
而对于作为静态库的.lib来说，其本身就包含了实际执行代码、符号表等等


WINDOWS中的动态库
windows系统中动态库文件后缀为.dll
显式加载
宿主程序代码中通过函数LoadLibrary(), FreeLibrary()指定DLL的加载和卸载
宿主程序启动后，其进程在遇到LoadLibrary()函数时才将DLL加载到进程的内存空间。
显式加载时，只有需要使用dll文件，不需要LIB文件。
隐式加载
隐式加载时没有显式地调用LoadLibrary()和FreeLibrary()，因此称为隐式加载。
宿主程序在启动时搜索到dll文件后，将动态链接库加载到宿主程序进程的内存空间。
隐式加载本质上也是通过LoadLibrary()函数实现加载工作。
需要使用lib文件和dll文件。

LINUX中的动态库
linux系统中动态库文件后缀为.so



DLL文件
DLL和EXE文件一样，其中包含的也是程序的二进制执行代码和程序所需的资源
DLL中的代码是以API函数形式出现的
通俗地说，DLL中包含的程序代码都被做成了一个个小模块，应用程序通过按下所需DLL中特定的按钮，来调用DLL中这个按钮所代表的功能





静态库和动态库的区别
静态库在程序的链接阶段被复制到了程序中，和程序运行的时候没有关系；
动态库是程序在运行时由系统动态加载到内存中供程序调用。
使用动态库的优点是系统只需载入一次，不同的程序可以得到内存中相同的动态库的副本，因此节省了很多内存。


调用静态库的方式：
包含静态库的头文件，如#include "lib1/lib1.h"
试用预处理指令导入静态库——如#pragma comment(lib,"lib1.lib")
如果使用了VS，则上一步可以改为在项目属性->链接器->附加依赖项之中加入.lib文件。





*/





// 工作项目中学到的那些奇技淫巧
/*
	宏函数定义某功能的统一接口
			宏函数实现自定义类的实例化：
					#define VD_DECLAREOBJECT(className)	struct className : public IVObject



*/


 
// test0: 大小端问题
static void test0() 
{
    // 内存中数据存储，低位在前高位在后。
    unsigned int num = 0x1234;           		// 4字节
    int i = 1;
    char* pc = (char*)(&num);

    for (i; i <= 4; i++)
    {
        printf("%x\t", *pc);

        if (i <= 3)
            pc++;
    }
 

}


// test: ！！！不要发生有符号数和无符号数比较情形，否则会将有符号数隐式转换为无符号数操作
static void test2()
{
	std::vector<int> vec;
	unsigned int num = 0;

	for (int i = 10; i >= num; i--)			// i会隐式转换为无符号整形，减到0后执行--操作会变成4294967295，循环依然会继续。
	{
		vec.push_back(i);

		if (vec.size() > 15)
			break;
	}

	for (const auto& elem : vec)
		std::cout << elem << ",  ";
}




namespace RECURSION
{
	// factorial————尾递归计算阶乘num!
	static unsigned long factorial(unsigned int num)
	{
		//		递归递推：factorial(n) == n*factorial(n-1)
 
		//		递归终止条件：factorial(1) == 1;	factorial(0) == 1;

		unsigned long result;

		if ((1 == num) || (0 == num))
			result = 1;
		else
			result = num * factorial(num - 1);		// 尾递归：递归最简单的情形， 可以很容易地改写成循环的形式。

		return result;
	}

	// to_binary————将输入的十进制正整数转换为二进制数打印出来
	static void to_binary(unsigned long num)
	{
		//		递归递推： to_binary(num) → to_binary(num/2)
 
		//		递归终止条件： num == 0; num == 1;
		int remind;

		remind = num % 2;
		if (num >= 2)
			to_binary(num / 2);

		putchar(remind ? '1' : '0');
	}

}

// test0: 简单的递归调用：
static void test0(void)
{
	using namespace RECURSION;
	unsigned long num = 99;


	cout << factorial(num) << endl;

	cout << to_binary(num) << endl;
}

 