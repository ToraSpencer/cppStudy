#include <iostream>
#include <string>
#include <typeinfo>

#include <cstdio>

#include "syntax_几个特殊运算符.h" 


#define EPS 1e-10					//定义非常小的一个量EPSilon，当浮点数不大于这个值时，视为0
#define PI 3.14159


// sizeof()运算符：返回一个对象或类型所占的内存字节数。	
/*
    sizeof(对象);           如sizeof(num)
    sizeof(类型名);         如sizeof(int)
			 
*/




// 三目运算符：b ? x : y;   
/*
    计算条件b，若b值为true，则计算表达式x，并返回结果；
        若b值为false，则计算表达式y，并返回计算结果。
			 
*/

virtualModule* syntax_operator_module::getInstance()		// 线程不安全的单例模式
{
	if (nullptr != p_moduleIns)
	{
		delete p_moduleIns;
	}
	p_moduleIns = new syntax_operator_module;
	return p_moduleIns;
}

 
// test0: sizeof()运算符
void syntax_operator_module::test0(void)
{
    std::cout << "\n\n\n\n" << std::endl;
	std::cout << "test0: sizeof()运算符" << std::endl;

    int arri[5];
    std::cout << "\t数组arri占内存：sizeof(arri) == " << sizeof(arri) << std::endl;
    std::cout << "\t数组arri含元素数：sizeof(arri)/sizeof(int) == " << sizeof(arri)/sizeof(int) << std::endl;

    // 所有指针占内存都是一样的，由操作系统位数决定，64位系统下指针占8字节，即机器字长。
    int* pi;
    double* pd;
    void* pv;
    std::cout << "\t" << sizeof(pi) << std::endl;
    std::cout << "\t" << sizeof(pd) << std::endl;
    std::cout << "\t" << sizeof(pv) << std::endl;

}



// test1: 三目运算符
void syntax_operator_module::test1(void)
{
    std::cout << "\n\n\n\n" << std::endl;
	std::cout << "test1: 三目运算符" << std::endl;


    // 应用例子————判断输入整数是奇数还是偶数。
    int inputValid = 0;
    int num;
    std::string str;

    std::cout << "请输入一个整数：" << std::endl;
    while(0 == inputValid)
    {
        setbuf(stdin, NULL);
        inputValid = scanf("%d", &num);
        
        if(0 == inputValid)
        {
            std::cout << "输入不合法，请重新输入。" << std::endl;
            setbuf(stdin, NULL);
        }
    }
    str = (num%2 == 0) ? "偶数": "奇数";
    std::cout << "输入的整数是" << str << std::endl;
     
}



void syntax_operator_module::test2(void)
{


}


void syntax_operator_module::test3(void)
{


}


void syntax_operator_module::test4(void)
{


}


void syntax_operator_module::test5(void)
{


}


void syntax_operator_module::test6(void)
{


}