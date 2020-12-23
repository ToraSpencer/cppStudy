#include <cstdio>
#include <cstring>


#include <string>
#include <iostream>
#include <vector>						//vector类模板在头文件<vector>中
#include <algorithm>
#include <iterator>


#include <cstdio>

#include "example.h"

using namespace std;



// 知识点
/*
		string
			是封装成类的可变长字符串。
			是STL线性容器。

		wstring
			封装的是wchar_t类型数据，是宽字符。
			用于满足非ASCII字符的要求，例如Unicode编码，中文，日文，韩文。。。
			wstring在<string>头文件中定义，其对应的字面量前面带有L


		string, char*, const char*的比较


		C风格字符串的常用API函数
					strcpy(), strncpy()
					strcmp()
					strcat();
					
					
		字符串匹配
					在一个大的字符串T中搜索某个字符串P的所有出现位置。
					C++中有现成的轮子可以使用————string类的find(), find_first_of(), find_last_of()方法。


		不安全的函数
					strcpy(), strncpy()				两者都不安全，但是strncpy好一些，以后再考虑更安全的方法。
						
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
void set_fun_dataType_string(void);
void start_dataType_string(void);


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
void set_fun_dataType_string(void) 
{
	pfun[0] = test0;
	pfun[1] = test1;
	pfun[2] = test2;
	pfun[3] = test3;
	pfun[4] = test4;
	pfun[5] = test5;

}



void start_dataType_string(void) 
{
	// 界面层级符置为3，进入三级界面：
	interfaceLevel = 3;
	while (3 == interfaceLevel)
	{
		cout << "\n\n\n\n" << endl;
		cout << "**************************MENU: dataType_string**********************" << endl;
		cout << "Please choose a demon function to run:" << endl;
		cout << "-2: Run all existed demon function." << endl;
		cout << "-1: Back to the previous interface." << endl;
		cout << "0. test0: C++中的字符串（string对象），C中的字符串（char数组），以及C/C++中的字符串字面量。" << endl;
		cout << "1. test1: string类的接口" << endl;
		cout << "2: test2: string对象的输入输出" << endl;
		cout << "3: test3: C语言中的字符串的API" << endl;
		cout << "4: test4: 字符编码" << endl;
		cout << "5: test5: 常用算法实现" << endl;
		

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



//	test0: C++中的字符串（string对象），C中的字符串（char数组），以及C/C++中的字符串字面量。
static void test0(void) 
{
	char Cstr1[] = "this is a C type string";				// 使用字符串字面量初始化char数组——即C风格的字符串
	char Cstr2[] = "hahahahaha";
	char Cstr3[] = "hehehehehehe";
	const char* Cstr4 = NULL;
	string str1 = "this is a C++ string object";		// 使用字符串字面量初始化string对象——C++中的字符串
	string str2 = Cstr2;														// 使用C风格的字符串给C++的字符串对象初始化。



	// C风格字符串、string对象都可以使用字符串字面量初始化，都可以使用cout打印
	cout << "\t C风格、C++的字符串都可以使用字符串字面量初始化，都可以使用cout打印。" << endl;
	cout << "\tCstr1 == " << Cstr1 << endl;
	cout << "\tstr1 == " << str1 << endl;
	cout << endl;
	cout << "\t C++字符串对象可以使用C风格字符串来初始化：" << endl;
	cout << "\tstring str2 = Cstr2;	str2 == " << str2 << endl;
	cout << endl;


	// C风格的字符串初始化以后就不能作为一个整体被赋值，只能逐个字符地改写，或者使用strcpy()等函数
	



	//	C风格的字符串可以给string对象赋值
	str2 = Cstr3;															// 使用C风格的字符串给C++的字符串对象赋值。
	cout << "" << endl;
	cout << "\tC风格的字符串可以给C++的字符串对象赋值:" << endl;
	cout << "\tstr2 = Cstr3; str2 == " << str2 << endl;


	// string的c_str()方法返回其封装的c风格字符串
	Cstr4 = str2.c_str();									// 注意返回的c风格字符串是const的。
	cout << "Cstr4 == " << Cstr4 << endl;


	// string对象和字符串字面量的比较
	str1 = "hahaha";
	//		内容相同的string对象和字符串字面量==运算结果是true，可以用于检验。
	cout << "(int)(str1 == \"hahaha\") == "<<(int)(str1 == "hahaha") << endl;

}






// test1: string类的API
static void test1(void)
{
	cout << "\n\n\n\n" << endl;
    cout << "test1: string类的接口" << endl;

	string str1;					// 默认构造函数构造的空string
	string str2(9,'a');				// 若干个相同字符构造的string
	string str3("hello world");		// 字符串字面量构造的string


	// 访问单个元素的接口：operator[], at(), front(), back()
	cout << "\t访问单个元素的接口：operator[], at(), front(), back():" << endl;
	cout << "\tstr2[2] == " << str2[2] << endl;
	try
	{
		
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}
	cout << "\tstr3.front() == "<< str3.front() << endl;
	cout << "\tstr3.back() == "<< str3.back() << endl;
	cout << endl << endl;



	// 操作多个元素的接口：insert, replace, substr, append
	str1 = str2.substr(2,4);
	str2.replace(3, 2, "bcbcbc");
	str3.insert(6, "new ");			// 在第6个字符后面插入，“第六”是指从“第一“开始数
	cout << "\t操作多个元素的接口：insert, replace, sub_str, append, clear" << endl;
	cout << "\tstr1 == "<< str1 << endl;
	cout << "\tstr2 == "<< str2 << endl;
	cout << "\tstr3 == "<< str3 << endl;
	str1.clear();
	cout << "str1.clear(); str1 == " << str1 << endl;
	cout << endl << endl;



	// string对象之间的操作：operator+=
	str1 += str2;
	str1 += str3;
	cout << "\tstring对象之间的操作：operator+=" << endl;
	cout << "\tstr1 == " << str1 << endl;
	cout << endl << endl;

	
	// getline()



	// 迭代器接口：begin, cbegin(C++11), rbegin(C++11), crbegin(C++11)...
	cout << "\t使用反向迭代器，反向打印字符串："<< endl;
	for_each(str3.rbegin(), str3.rend(), printElem<char>);





}




// test2: string对象的输入输出
static void test2(void)
{
	cout << "\n\n\n\n" << endl;
  cout << "test2: string对象的输入输出" << endl;

	// std::getline————从输入流中读取数据填充string对象
	//		注：不能用cin来输入string对象，因为碰到空格会中断。
	string answer, number;
	cout << "Jun Lei: are you ok?" <<endl;
	setbuf(stdin, NULL);
	getline(cin, answer);
	cout << "Me: " << answer << endl;
	cout << "Jun Lei: whatever, have a nice day!" << endl;
	//		getline()可以设置字符串的停止标志：
	cout << "请输入号码，以井号键结束：" << endl;
	setbuf(stdin, NULL);
	getline(cin, number, '#');
	cout << "您输入的号码是：" << number << endl;
}



 
// test3: C语言中的字符串的API
static void test3(void)
{
		// 字符串输入输出——puts, fgets, fputs 
		// 拷贝——strcpy
		// 连接——strcat
		// 比较strcmp

		const char* str1 = "\tthis is a string literal";
		char str2[] = "\tthis is a copy of a string literal";
		char str3[100] = { '\0' };

		printf("\n\n\n\n");
		printf("test3: C语言中的字符串的API\0");


		// int puts(const char* str)——打印字符串：
		puts(str1);
		puts(str2);
		printf("\n\n");


		// char *fgets(char* str, int count, FILE* stream)——从给定流中读取有最大个数限定的字符，存储在给定字符数组中：
		printf("\tPlease input a string: ");
		setbuf(stdin, NULL);
		fgets(str3, 20, stdin);
		printf("\t%s", str3);
		printf("\n\n");


		// fputs——将以NULL结尾的字符串str的每个字符写入到输出流stream中。
		puts("\tPlease enter a string, and it will be printed immediately. If you want to quite this mode, input q:");
		while ((fgets(str3, 100, stdin)) && (*str3 != 'q'))
		{
			printf("\t");
			fputs(str3, stdout);
		}
		puts("\tTyping and printing mode exited.");




		char string1[50] = "hello ";
		char string2[] = "world ";
		char string3[20];

		// strcpy()———拷贝字符串，不安全，建议使用strncpy()
		/*
			 char *strcpy( char *dest, 					目标字符串
			 						 const char *src				源字符串
			 					)
		*/

		// strncpy()————拷贝字符串
		/*
			char *strncpy( char *dest,				目标字符串
									const char *src, 			源字符串，
									size_t n							最多复制的字符数，当src长度小于n时，dest剩余部分用空字节填充。
									) 

		
		*/
		strcpy(string3, string1);	





		//			int strcmp(str1, str2)，若相等返回0；若不相等，比较第一个不相等的字符的ASCII码，左<右的话返回负数
		cout << "strcmp(string1, string3) == " << strcmp(string1, string3) << endl;
		cout << "strcmp(\"abc\", \"abd\") == " << strcmp("abc", "abd") << endl;

		strcat(string1, string3);			// 删除string1末尾的'\0'，将string的内容复制到它后面
		strcat(string1, string2);			// 一开始就要保证string1开辟的空间足够大，可以容得下string2的内容
		cout << string1 << endl;


		// strcpy()和memcpy()的比较
		fill(string1, string1+49, '\0');		
		fill(string3, string3+19, '\0');
		strcpy(string1, "hahaha\0wawawawa");								// strcpy()遇到'\0'就停止						
		memcpy(string3, "hahaha\0wawawawa", 16);					// memcpy()一定会拷贝设定的字节数。
		
		printf("%s\n", string1);						
		printf("%s\n", string3);
		printf("%s\n", string3+7);


}
 


// test4: 字符编码
static void test4(void)
{
	printf("\n\n\n\n");
	printf("test4: 字符编码\n");

	// 输入中文、英文、数字查询其编码（半角字符为ASCII码，全角字符为GB2312码
	//		1. 创建待查询的字符串，声明读字符编码的指针。
	char str[] = "是敌法地方kju421";
	unsigned char* puc = (unsigned char*)str;


	//		2. 打印待查询的字符串。
	printf("\t原字符串：str == %s\n", str);


	//		3. 使用unsigned char*指针以十六进制整形数形式逐个读取字符串中的数据：
	printf("\t使用unsigned char*指针以十六进制整形数形式逐个读取字符串中的数据：\n");
	do
	{
		printf("\t0x%x,", *puc);
		puc++;

	} while (*puc != '\0');
	printf("\n");



	//	输入ASCII码或GB2312码，来生成全角字符或半角字符。 
	//		1. 声明空的字符串变量，读写字符数据的unsigned char指针
	char str2[100] = { '\0' };
 

	//		 2. 写入ASCII码数据
	puc = (unsigned char*)str2;
	*puc = 33;						// !
	*(puc + 1) = 34;				// "
	*(puc + 2) = 48;				// 0
	*(puc + 3) = 49;				// 1
	*(puc + 4) = 65;				// A
	*(puc + 5) = 66;				// B
	*(puc + 6) = 97;				// a
	*(puc + 7) = 98;				// b
	*(puc + 8) = '\0';
	printf("\t用unsigned char指针逐个字节写入ASCII数据到字符串中，每个字节最高位为0：\n");
	printf("\tstr == %s\n", str2);


	//		3. 写入GB2312码数据
	*puc = 0xb0;						 
	*(puc + 1) = 0xa1;			 
	*(puc + 2) = 0xb0;				 
	*(puc + 3) = 0xa2;				 
	*(puc + 4) = 0xb0;			 
	*(puc + 5) = 0xa3;				 
	*(puc + 6) = 0xb0;				 
	*(puc + 7) = 0xa4;			 
	*(puc + 8) = '\0';
	printf("\t用unsigned char指针逐个字节写入GB2312数据到字符串中，每个字节最高位为1：\n");
	printf("\tstr == %s\n", str2);

}



// test5: 常用算法C++实现
static void test5(void)
{
	cout << "\n\n\n\n" << endl;
	cout << "test5: 常用算法C++实现" << endl;

	// 字符串匹配——在一个大的字符串T中搜索某个字符串P的所有出现位置。
	/*
	*/

	// C++中的轮子实现字符串匹配：
	string str1 = "asdfajiuiuwww.baidu.comasdfuoiup";

	//			string类的find()方法——查找字符串中的字符或子串
	//					size_type——string和vector定义的类型，是表示容器容量的无符号整型数，
	string::size_type num = str1.find("baidu", 0);							// 第二个参数是搜索开始的位置。
	if (num == string::npos)															// 搜索不到的时候返回npos，一般等于-1
	{
		cout << "没有找到模板字符串" << endl;
	}
	else
	{ 
		cout << "找到模板字符串，位置是" << num << endl;
	}


	//			string类的find_first_of()和find_last_of()方法——查找字符或子串第一次、最后一次出现的位置
	string::size_type num1 = str1.find_first_of("asd");
	string::size_type num2 = str1.find_last_of("asd");
	if (num1 != num2)			
	{
		cout << "子串asd出现了不止一次" << endl;				// 可以用这种方法来判断子串在目标字符串中出现的次数
	}


}



// test: 宽字符wstring类
static void test6(void)
{
	// wstring在<string>头文件中定义，其对应的字面量前面带有L
	wstring str = L"abcde";
	cout << str.size() << endl;


	cout << str[0] << endl;
	cout << str[1] << endl;
	cout << str[2] << endl;

	cout << static_cast<unsigned char>(str[1]) << endl;

}