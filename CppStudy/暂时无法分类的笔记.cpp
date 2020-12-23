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
        {
            pc++;
        }
    }
 

}


// test: ！！！不要发生有符号数和无符号数比较情形，否则会将有符号数隐式转换为无符号数操作
static void test2()
{
	vector<int> vec;

	unsigned int num = 0;

	for (int i = 10; i >= num; i--)			// i会隐式转换为无符号整形，减到0后执行--操作会变成4294967295，循环依然会继续。
	{
		vec.push_back(i);

		if (vec.size() > 15)
		{
			break;
		}
	}

	for (const auto& elem : vec)
	{
		cout << elem << ",  ";
	}

}




