#include <cstdio>
#include <cstring>


#include <string>
#include <iostream>
#include <vector>						//vector类模板在头文件<vector>中
#include <algorithm>
#include <iterator>
#include <regex>

#include <cstdio>
#include "example.h"
using namespace std;




/*
**	 
**
**
**
*/





/***************************************************************************
***************************************************************************/
// 全局变量、类型定义



/***************************************************************************
***************************************************************************/
// extern变量
extern void(*pfun[100])(void);
extern int inputTag, inputNum, interfaceLevel;


/***************************************************************************
***************************************************************************/
// 函数声明
void set_fun_stdlib_regex(void);
void start_stdlib_regex(void);


static void test0(void);
static void test1(void);
static void test2(void);
static void test3(void);
static void test4(void);
static void test5(void);


/***************************************************************************
***************************************************************************/
// extern函数
extern void traverse_pfun(void);



/***************************************************************************
***************************************************************************/
// 自定义类的实现



/***************************************************************************
***************************************************************************/
// 函数定义
void set_fun_stdlib_regex(void)
{
	pfun[0] = test0;
	pfun[1] = test1;
	pfun[2] = test2;
	pfun[3] = test3;
	pfun[4] = test4;
	pfun[5] = test5;

}



void start_stdlib_regex(void)
{
	// 界面层级符置为3，进入三级界面：
	interfaceLevel = 3;
	while (3 == interfaceLevel)
	{
		cout << "\n\n\n\n" << endl;
		cout << "**************************MENU: stdlib_正则表达式**********************" << endl;
		cout << "Please choose a demon function to run:" << endl;
		cout << "-2: Run all existed demon function." << endl;
		cout << "-1: Back to the previous interface." << endl;
		cout << "0. test0:  " << endl;
		cout << "1. test1: " << endl;
		cout << "2: test2:  " << endl;
		cout << "3: test3:  " << endl;
		cout << "4: test4:  " << endl;
		cout << "5: test5:  " << endl;


		inputTag = scanf("%d", &inputNum);

		// 若输入值不是整数，重新输入。
		if (inputTag != 1)
		{
			printf("Invalid input. Please input again:\n");
			setbuf(stdin, NULL);
			continue;
		}

		// 对三级界面输入值的响应。
		switch (inputNum)
		{
		case -2:
			traverse_pfun();
			break;

		case -1:
			interfaceLevel = 2;
			break;

		case 0:
			(*pfun[0])();
			break;

		case 1:
			(*pfun[1])();
			break;

		case 2:
			(*pfun[2])();
			break;

		case 3:
			(*pfun[3])();
			break;

		case 4:
			(*pfun[4])();
			break;

		case 5:
			(*pfun[5])();
			break;



		default:
			printf("Invalid input. Please input again:\n");
			break;
		}


	}


}



//	test0:  应用实例——匹配邮箱格式
static void test0(void)
{
	cout << "\n\n\n\n" << endl;
	cout << "test " << endl;

	// 正则表达式，匹配规则：
	/*
		第1组（即用户名），
			匹配规则：0至9、A至Z、a至z、下划线、点、连字符之中的任意字符，重复一遍或以上
			中间，一个“@”符号
		第二组（即域名）
			匹配规则：0至9或a至z之中的任意字符重复一遍或以上，
							接着一个点，接着a至z之中的任意字符重复2至3遍（如com或cn等），
							第二组内部的一组，一个点，接着a至z之中的任意字符重复2遍（如cn或fr等）
							内部一整组重复零次或一次
	*/

	string email_address;
	string user_name, domain_name;

	regex pattern("([0-9A-Za-z\\-_\\.]+)@([0-9a-z]+\\.[a-z]{2,3}(\\.[a-z]{2})?)");



	// 输入文件结尾符（Windows用Ctrl+Z，UNIX用Ctrl+D）结束循环
	while (cin >> email_address)
	{
		if (regex_match(email_address, pattern))
		{
			cout << "您输入的电子邮件地址合法" << endl;

			// 截取第一组
			user_name = regex_replace(email_address, pattern, string("$1"));

			// 截取第二组
			domain_name = regex_replace(email_address, pattern, string("$2"));

			cout << "用户名：" << user_name << endl;
			cout << "域名：" << domain_name << endl;
			cout << endl;
		}
		else
		{
			cout << "您输入的电子邮件地址不合法" << endl << endl;
		}
	}
 

}



// test1:  
static void test1(void)
{
	cout << "\n\n\n\n" << endl;
	cout << "test1:  " << endl;


}



// test2: 
static void test2(void)
{
	cout << "\n\n\n\n" << endl;
	cout << "test2:  " << endl;


}



// test3: 
static void test3(void)
{
	cout << "\n\n\n\n" << endl;
	cout << "test3:  " << endl;


}



// test4:  
static void test4(void)
{
}



// test5:  
static void test5(void)
{
}