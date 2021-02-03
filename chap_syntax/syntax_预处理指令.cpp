#include <iostream>
#include <string>
#include <typeinfo>


#include <cstdio>

#include "syntax_预处理指令.h"

#define EPS 1e-10					//定义非常小的一个量EPSilon，当浮点数不大于这个值时，视为0
#define PI 3.14159

 
// 知识点
/*
#define————宏（macro）定义
格式
#define 宏  替换体
若一个宏替换体超过一行，上一行的行末尾需要加\
注意
宏替换的本质是完全的文本替换，将记号替换为字符串
宏是一个记号(token)型字符串，而不是字符型字符串
比如若定义了#define PI 3.14159
双引号中的PI不会被替换，因为是字符型字符串
其他地方的PI会被替换成文本3.14159
分类————1. 类对象宏(object-like macro)，	2. 类函数宏(function-like macro)

宏函数（类函数宏）
见test2;


宏的重定义
先撤销已有的宏定义：#undef  PI
再重定义该宏： #define PI 3.14159

#include————文件包含


预定义符号
C标准中预定义好的一些符号
不可以被重定义
如__FILE__, __LINE__等


预定符号相关指令
#line
重置__FILE__和__LINE__的内容
例子：
#line 1000				 // 当前行号重置为1000
#line 10 "temp.c"     // 当前行号重置为10，当前源文件名重置为temp.c

条件编译
#ifdef, #else, #endif
#ifndef, #else, #endif
#if, #elif, #else, #endif

记号粘合剂——##运算符
作用于宏的替换体中
把两个记号粘合成一个记号，然后作为该宏的替换体


#pragma————编译指示
在源代码中添加编译指令
设定编译器的状态，或者是指示编译器完成一些特定的动作。
#pragma once
通常用在头文件中，使得该头文件只被包含一次。
非标准方法，标准的方法应该是使用#ifndef
但是被广泛采用，注意有些老的编译器可能不支持。
#pragma comment
连接库文件。
#pragma pack
设置内存对齐





#error————错误指令
让预处理器报错，显示该错误指令中的文本
例子：#error not C11



常见预定义宏
ANSI C标准中有几个标准预定义宏：
__FILE__：当前源代码文件名，字符串字面量
__LINE__：当前源代码行号的整型常量
__DATE__：预处理的日期，字符串字面量
__TIME__：编译代码的时间，字符串字面量
__STDC__：当要求程序严格遵循ANSI C标准时该标识被赋值为1；
__cplusplus：当编写C++程序时该标识符被定义。

其他常见的宏定义
#define _DEBUG              // 调试宏，如果使用VS创建项目时解决方案配置选择Debug的话，将会自动定义此宏。
#define _NDEBUG             // release宏
#define _WINDLL             // 表示要做一个用到MFC的DLL
#define _DLL                // 当工程类型为动态链接库时，该值为1。

*/




virtualModule* syntax_preprocessing_instruction_module::getInstance()		// 线程不安全的单例模式
{
	if (nullptr != p_moduleIns)
	{
		delete p_moduleIns;
	}
	p_moduleIns = new syntax_preprocessing_instruction_module;
	return p_moduleIns;
}



// test0: 常用预处理符号，及其相关命令。 
void syntax_preprocessing_instruction_module::test0(void)
{
	std::cout << "\n\n\n\n" << std::endl;
	std::cout << "test0: 常用预处理符号，及其相关命令" << std::endl;

	std::cout << "\t当前源文件的名称：__FILE__ == " << __FILE__ << "； 是字符串字面量。" << std::endl;
	std::cout << "\t当前源文件中的代码行号：__LINE__ == " << __LINE__ << "；是十进制整数。" << std::endl;
	std::cout << "\t当前源文件的处理日期：__DATE__ == " << __DATE__ << "； 是字符串字面量。" << std::endl;
	std::cout << "\t当前源文件的编译时间：__TIME__ == " << __TIME__ << "； 是字符串字面量。" << std::endl;
	std::cout << std::endl;

#ifdef __cplusplus
	std::cout << "\tC/C++混合编程中可以使用#ifdef __cplusplus ... #endif 和 extern \"C\"{}来区分C和C++的代码。" << std::endl;
	std::cout << "\tC++03：__cplusplus = 199711L" << std::endl;
	std::cout << "\tC++11：__cplusplus = 201103L" << std::endl;
	std::cout << "\t可以根据__cplusplus宏的值来判断当前C++编译器的版本。" << std::endl;
	std::cout << "\t当前项目中：__cplusplus == " << __cplusplus << std::endl;
	std::cout << std::endl;
#endif


	// #error #warning 编译错误、编译警告
#ifndef __cplusplus
#error this project should be processed with c++ compiler
#endif




#line 1000								// 当前行号重置为1000 
	std::cout << "\t当前行号重置为1000 ：#line 1000; __LINE__ == " << __LINE__ << std::endl;
#line 10 "temp.c"						 // 当前行号重置为10，当前源文件名重置为temp.c
	std::cout << "\t当前行号重置为10，当前源文件名重置为temp.c:" << std::endl;
	std::cout << "\t__LINE__ == " << __LINE__ << std::endl;
	std::cout << "\t__FILE__ == " << __FILE__ << std::endl;
}



// test1: 宏函数
/*
宏中的参数用括号括起来，替换体即为函数体。
宏函数没有inline函数安全，因为只是单纯地展开，不会做安全检查
注意每个参数都最好加括号，如下面如果不加括号的话TIMES(1+2,3+4)会展开为1+2*3+4；
*/
#define TIMES(x,y) (x)*(y)	


// 	#可以将宏函数中的参数字符串化——此时若宏函数中的参数x为__FILE__，则其不会被宏展开，而是直接转化为字符串。
#define _STRING(x) #x
void syntax_preprocessing_instruction_module::test1(void)
{
	std::cout << "\n\n\n\n" << std::endl;
	std::cout << "test2: 宏函数" << std::endl;

	std::cout << TIMES(1 + 2, 3 + 4) << std::endl;
	std::cout << _STRING(__FILE__) << std::endl;

}


void syntax_preprocessing_instruction_module::test2(void) {}


void syntax_preprocessing_instruction_module::test3(void) {}


void syntax_preprocessing_instruction_module::test4(void) {}



void syntax_preprocessing_instruction_module::test5(void)
{


}



void syntax_preprocessing_instruction_module::test6(void)
{


}
