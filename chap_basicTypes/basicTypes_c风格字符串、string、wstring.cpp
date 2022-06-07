#include <cstdio>
#include <cstring>
#include <cstdio>


#include <string>
#include <iostream>
#include <vector>						//vector类模板在头文件<vector>中
#include <algorithm>
#include <iterator>
#include <atlstr.h>
#include <windows.h>



#include "basicTypes_c风格字符串、string、wstring.h"

// 知识点
/*
		std::string
			是封装成类的可变长字符串。
			是STL线性容器。

		wstring
			封装的是wchar_t类型数据，是宽字符。
			用于满足非ASCII字符的要求，例如Unicode编码，中文，日文，韩文。。。
			wstring在<std::string>头文件中定义，其对应的字面量前面带有L


		std::string, char*, const char*的比较


		C风格字符串的常用API函数
					strcpy(), strncpy()
					strcmp()
					strcat();
					
					
		字符串匹配
					在一个大的字符串T中搜索某个字符串P的所有出现位置。
					C++中有现成的轮子可以使用————std::string类的find(), find_first_of(), find_last_of()方法。


		不安全的函数
					strcpy(), strncpy()				两者都不安全，但是strncpy好一些，以后再考虑更安全的方法。
						
*/


virtualModule* basicTypes_strings_module::getInstance()		// 线程不安全的单例模式
{
	if (nullptr != p_moduleIns)
		delete p_moduleIns;
	p_moduleIns = new basicTypes_strings_module;
	return p_moduleIns;
}




//	test0: C++中的字符串（std::string对象），C中的字符串（char数组），以及C/C++中的字符串字面量。
void basicTypes_strings_module::test0(void)
{
	char Cstr1[] = "this is a C type std::string";				// 使用字符串字面量初始化char数组——即C风格的字符串
	char Cstr2[] = "hahahahaha";
	char Cstr3[] = "hehehehehehe";
	const char* Cstr4 = NULL;
	std::string str1 = "this is a C++ std::string object";		// 使用字符串字面量初始化std::string对象——C++中的字符串
	std::string str2 = Cstr2;														// 使用C风格的字符串给C++的字符串对象初始化。



	// C风格字符串、std::string对象都可以使用字符串字面量初始化，都可以使用std::cout打印
	std::cout << "\t C风格、C++的字符串都可以使用字符串字面量初始化，都可以使用std::cout打印。" << std::endl;
	std::cout << "\tCstr1 == " << Cstr1 << std::endl;
	std::cout << "\tstr1 == " << str1 << std::endl;
	std::cout << std::endl;
	std::cout << "\t C++字符串对象可以使用C风格字符串来初始化：" << std::endl;
	std::cout << "\tstring str2 = Cstr2;	str2 == " << str2 << std::endl;
	std::cout << std::endl;


	// C风格的字符串初始化以后就不能作为一个整体被赋值，只能逐个字符地改写，或者使用strcpy()等函数
	



	//	C风格的字符串可以给std::string对象赋值
	str2 = Cstr3;															// 使用C风格的字符串给C++的字符串对象赋值。
	std::cout << "" << std::endl;
	std::cout << "\tC风格的字符串可以给C++的字符串对象赋值:" << std::endl;
	std::cout << "\tstr2 = Cstr3; str2 == " << str2 << std::endl;


	// std::string的c_str()方法返回其封装的c风格字符串
	Cstr4 = str2.c_str();									// 注意返回的c风格字符串是const的。
	std::cout << "Cstr4 == " << Cstr4 << std::endl;


	// std::string对象和字符串字面量的比较
	str1 = "hahaha";
	//		内容相同的std::string对象和字符串字面量==运算结果是true，可以用于检验。
	std::cout << "(int)(str1 == \"hahaha\") == "<<(int)(str1 == "hahaha") << std::endl;

}



// test1: 字符串常用的API
void basicTypes_strings_module::test1(void)
{
	std::cout << "\n\n\n\n" << std::endl;
    std::cout << "test1: std::string类的接口" << std::endl;

	std::string str1;					// 默认构造函数构造的空std::string
	std::string str2(9,'a');				// 若干个相同字符构造的std::string
	std::string str3("hello world");		// 字符串字面量构造的std::string


	// 1. 访问单个元素的接口：operator[], at(), front(), back()
	std::cout << "\t访问单个元素的接口：operator[], at(), front(), back():" << std::endl;
	std::cout << "\tstr2[2] == " << str2[2] << std::endl;
	try
	{
		
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}
	std::cout << "\tstr3.front() == "<< str3.front() << std::endl;
	std::cout << "\tstr3.back() == "<< str3.back() << std::endl;
	std::cout << std::endl << std::endl;


	// 2. 操作多个元素的接口：insert, replace, substr, append
	str1 = str2.substr(2,4);		// 参数为起止字符的索引，是闭区间。
	str2.replace(3, 2, "bcbcbc");
	str3.insert(6, "new ");			// 在第6个字符后面插入，“第六”是指从“第一“开始数
	std::cout << "\t操作多个元素的接口：insert, replace, sub_str, append, clear" << std::endl;
	std::cout << "\tstr1 == "<< str1 << std::endl;
	std::cout << "\tstr2 == "<< str2 << std::endl;
	std::cout << "\tstr3 == "<< str3 << std::endl;
	str1.clear();
	std::cout << "str1.clear(); str1 == " << str1 << std::endl;
	std::cout << std::endl << std::endl;

	// 3. std::string对象之间的操作：operator+=
	str1 += str2;
	str1 += str3;
	std::cout << "\tstring对象之间的操作：operator+=" << std::endl;
	std::cout << "\tstr1 == " << str1 << std::endl;
	std::cout << std::endl << std::endl;

	// 4. 迭代器接口：begin, cbegin(C++11), rbegin(C++11), crbegin(C++11)...
	std::cout << "\t使用反向迭代器，反向打印字符串："<< std::endl;
	for_each(str3.rbegin(), str3.rend(), disp<char>);
	std::cout << std::endl << std::endl;

	// 5. 1 字符串转换为其他类型std::stoi(), std::stol(), std::stoll(), std::stof() ———— C风格字符串、字符串、宽字符串转为数值(c++11)：
	char* cstr = "123";
	str1 = "123";
	str2 = "1234567890";
	str3 = "12fd132";
	std::string str4 = "12.23";
	std::string str5 = " 888";
	std::string str6 = "123 456 678";
	std::wstring wstr1 = L"54321";
	int num0 = std::stoi(cstr);
	int num1 = std::stoi(str1);
	long num2 = std::stol(str2);
	int num3 = std::stoi(wstr1);
	float num4 = std::stof(str4);
	int num5 = std::stoi(str5);		// 前后的空格不影响数值转换
	int num6 = std::stoi(str6);		// 数字中间有空格的话，会截断空格后面的数字。
	
	std::cout << num0 << std::endl;
	std::cout << num1 << std::endl;
	std::cout << num2 << std::endl;
	std::cout << num3 << std::endl;
	// std::cout << std::stoi(str3) << std::endl;		字符串中有非数值字符程序会中断。
	std::cout << num4 << std::endl;
	std::cout << num5 << std::endl;
	std::cout << num6 << std::endl;
	std::cout << std::endl << std::endl;

	// 5.2 其他类型转换为字符串：a. 使用stringstream实现； b. std::to_string()和std::to_wstring()——数值转换为字符串（C++11）
	str1 = std::to_string(321);
	str2 = std::to_string(987654321);
	wstr1 = std::to_wstring(12345);
	std::cout << str1 << std::endl;
	std::cout << str2 << std::endl;
	std::wcout << wstr1 << std::endl;
	std::cout << std::endl << std::endl;

	// 6. 子串操作：
	str1 = "asdfhjkl12345";

	//		substr()
	str2 = str1.substr(3, 4);
	std::cout << str2 << std::endl;
	str2 = "9999";
	str1.erase(3, 4);
	str1.insert(3, str2);
	std::cout << str1 << std::endl;

}




// test2: std::string对象的输入输出
void basicTypes_strings_module::test2(void)
{
	std::cout << "\n\n\n\n" << std::endl;
	std::cout << "test2: std::string对象的输入输出" << std::endl;

	// std::getline————从输入流中读取数据填充std::string对象
	//		注：不能用cin来输入std::string对象，因为碰到空格会中断。
	std::string answer, number;
	std::cout << "Jun Lei: are you ok?" <<std::endl;
	setbuf(stdin, NULL);
	std::getline(std::cin, answer);
	std::cout << "Me: " << answer << std::endl;
	std::cout << "Jun Lei: whatever, have a nice day!" << std::endl;
	//		getline()可以设置字符串的停止标志：
	std::cout << "请输入号码，以井号键结束：" << std::endl;
	setbuf(stdin, NULL);
	std::getline(std::cin, number, '#');
	std::cout << "您输入的号码是：" << number << std::endl;
}



 
// test3: C语言中的字符串的API
void basicTypes_strings_module::test3(void)
{
		// 字符串输入输出——puts, fgets, fputs 
		// 拷贝——strcpy
		// 连接——strcat
		// 比较strcmp

		const char* str1 = "\tthis is a std::string literal";
		char str2[] = "\tthis is a copy of a std::string literal";
		char str3[100] = { '\0' };

		printf("\n\n\n\n");
		printf("test3: C语言中的字符串的API\0");


		// int puts(const char* str)——打印字符串：
		puts(str1);
		puts(str2);
		printf("\n\n");


		// char *fgets(char* str, int count, FILE* stream)——从给定流中读取有最大个数限定的字符，存储在给定字符数组中：
		printf("\tPlease input a std::string: ");
		setbuf(stdin, NULL);
		fgets(str3, 20, stdin);
		printf("\t%s", str3);
		printf("\n\n");


		// fputs——将以NULL结尾的字符串str的每个字符写入到输出流stream中。
		puts("\tPlease enter a std::string, and it will be printed immediately. If you want to quite this mode, input q:");
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
		std::cout << "strcmp(string1, string3) == " << strcmp(string1, string3) << std::endl;
		std::cout << "strcmp(\"abc\", \"abd\") == " << strcmp("abc", "abd") << std::endl;

		strcat(string1, string3);			// 删除string1末尾的'\0'，将std::string的内容复制到它后面
		strcat(string1, string2);			// 一开始就要保证string1开辟的空间足够大，可以容得下string2的内容
		std::cout << string1 << std::endl;


		// strcpy()和memcpy()的比较
		std::fill(string1, string1+49, '\0');		
		std::fill(string3, string3+19, '\0');
		strcpy(string1, "hahaha\0wawawawa");								// strcpy()遇到'\0'就停止						
		memcpy(string3, "hahaha\0wawawawa", 16);					// memcpy()一定会拷贝设定的字节数。
		
		printf("%s\n", string1);						
		printf("%s\n", string3);
		printf("%s\n", string3+7);


		// 英文字母大小写转换：std::toUpper(), std::toLower();
		std::string lowerStr = "asdf";
		std::string upperStr;
		for (const auto& ch: lowerStr)
		{
			int temp = std::toupper(static_cast<unsigned char>(ch));
			upperStr.push_back(static_cast<char>(temp));
		}
		std::cout << upperStr << std::endl;


}
 


// test4: 字符编码
void basicTypes_strings_module::test4(void)
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
void basicTypes_strings_module::test5(void)
{
	std::cout << "\n\n\n\n" << std::endl;
	std::cout << "test5: 常用算法C++实现" << std::endl;

	// 字符串匹配——在一个大的字符串T中搜索某个字符串P的所有出现位置。
	/*
	*/

	// C++中的轮子实现字符串匹配：
	std::string str1 = "asdfajiuiuwww.github.comasdfuoiup";

	//			std::string类的find()方法——查找字符串中的字符或子串
	//					size_type——std::string和vector定义的类型，是表示容器容量的无符号整型数，
	std::string::size_type num = str1.find("github", 0);							// 第二个参数是搜索开始的位置。
	if (num == std::string::npos)															// 搜索不到的时候返回npos，一般等于-1
		std::cout << "没有找到模板字符串" << std::endl;
	else
		std::cout << "找到模板字符串，位置是" << num << std::endl;


	//			std::string类的find_first_of()和find_last_of()方法——查找字符或子串第一次、最后一次出现的位置
	std::string::size_type num1 = str1.find_first_of("asd");
	std::string::size_type num2 = str1.find_last_of("asd");
	if (num1 != num2)			
		std::cout << "子串asd出现了不止一次" << std::endl;				// 可以用这种方法来判断子串在目标字符串中出现的次数
}



// test6: 宽字符wchar_t，宽字符串wstring
void basicTypes_strings_module::test6(void)
{
	// wstring在<std::string>头文件中定义，其对应的字面量前面带有L
	std::wstring str = L"abcde";
	std::cout << str.size() << std::endl;
	std::cout << str[0] << std::endl;
	std::cout << str[1] << std::endl;
	std::cout << str[2] << std::endl;
	std::cout << static_cast<unsigned char>(str[1]) << std::endl << std::endl;

	// 1. 宽字符和普通字符的转换：
	char ch1 = '1';
	char ch2 = '9';
	wchar_t wch1 = L'1';
	wchar_t wch2 = L'9';
	wchar_t wch3 = static_cast<wchar_t>(ch1);
	std::cout << static_cast<int>(ch1) << std::endl;	// 49
	std::cout << static_cast<int>(ch2) << std::endl;	// 57
	std::cout << static_cast<int>(wch1) << std::endl;	// 49
	std::cout << static_cast<int>(wch2) << std::endl;	// 57
	std::cout << static_cast<char>(wch2) << std::endl;				// 9	宽字符和字符类型使用static_cast转换，内容不变。
	std::wcout << static_cast<wchar_t>(ch2) << std::endl;			// 9
 	std::cout << ch1 << std::endl;					// 1
	std::cout << ch2 << std::endl;					// 9 
	std::wcout << wch1 << std::endl;				// 1
	std::wcout << wch2 << std::endl;				// 9
	std::wcout << wch3 << std::endl << std::endl;	// 1

	std::cout << (char)(1 + 48) << std::endl;		// 1
	std::cout << (char)(9 + 48) << std::endl;		// 9
	std::wcout << (wchar_t)(1 + 48) << std::endl;	// 1
	std::wcout << (wchar_t)(9 + 48) << std::endl;	// 9


	// 2. VC++中的宽字符TCHAR，及其相关接口

		/*
		C++支持两种字符串，即常规的ANSI编码（使用""包裹）和Unicode编码（使用L""包裹）
		TCHAR使用条件编译，对两套字符集及其操作进行了统一。
		#ifdef   UNICODE
			typedef   wchar_t   TCHAR;
		#else
			typedef   unsigned   char   TCHAR;
		#endif
	*/
	std::cout << typeid(wchar_t).name() << std::endl;
	std::cout << typeid(TCHAR).name() << std::endl;
	std::cout << typeid(WCHAR).name() << std::endl;

	const TCHAR* wstr1 = L"阿斯顿发送到发送到发斯蒂芬";
 
	// std::locale()——设置语言环境
	std::wcout.imbue(std::locale(std::locale(), "", LC_CTYPE));	// 设置wcout的语言环境，缺少这一步打印中文会有错误。
	std::wcout << wstr1 << std::endl;

	TCHAR modulePath[MAX_PATH + 1] = { 0 };
	GetModuleFileName(NULL, modulePath, MAX_PATH);
	std::wcout << L"当前运行模块为： "  << modulePath << std::endl;

	// wcsrchr()——宽字符串搜索
	TCHAR* pc = wcsrchr(modulePath, TEXT('\\'));				// pc指向字符串modulePath中最后一次出现'\\'的位置；
	std::wcout << L"当前运行模块名为：" << pc << std::endl;

	TCHAR tail[100] = { 0 };
	//	wcscpy_s()——宽字符串拷贝
	wcscpy_s(tail, sizeof(tail) / sizeof(TCHAR), pc);
	std::wcout << L"当前运行模块名为：" << tail << std::endl;
	std::wcout << tail << std::endl;

	// 截断字符串
	*pc = L'\0';
	std::wcout << L"当前运行模块所在目录为："  << modulePath << std::endl;
	std::cout << wcscmp(tail, TEXT("\\mytest0.exe")) << std::endl;

}
