#include <cstdio>
#include <cstring>
#include <cstdio>


#include <string>
#include <iostream>
#include <vector>						//vector��ģ����ͷ�ļ�<vector>��
#include <algorithm>
#include <iterator>
#include <atlstr.h>
#include <windows.h>



#include "basicTypes_c����ַ�����string��wstring.h"

// ֪ʶ��
/*
		std::string
			�Ƿ�װ����Ŀɱ䳤�ַ�����
			��STL����������

		wstring
			��װ����wchar_t�������ݣ��ǿ��ַ���
			���������ASCII�ַ���Ҫ������Unicode���룬���ģ����ģ����ġ�����
			wstring��<std::string>ͷ�ļ��ж��壬���Ӧ��������ǰ�����L


		std::string, char*, const char*�ıȽ�


		C����ַ����ĳ���API����
					strcpy(), strncpy()
					strcmp()
					strcat();
					
					
		�ַ���ƥ��
					��һ������ַ���T������ĳ���ַ���P�����г���λ�á�
					C++�����ֳɵ����ӿ���ʹ�á�������std::string���find(), find_first_of(), find_last_of()������


		����ȫ�ĺ���
					strcpy(), strncpy()				���߶�����ȫ������strncpy��һЩ���Ժ��ٿ��Ǹ���ȫ�ķ�����
						
*/


virtualModule* basicTypes_strings_module::getInstance()		// �̲߳���ȫ�ĵ���ģʽ
{
	if (nullptr != p_moduleIns)
		delete p_moduleIns;
	p_moduleIns = new basicTypes_strings_module;
	return p_moduleIns;
}




//	test0: C++�е��ַ�����std::string���󣩣�C�е��ַ�����char���飩���Լ�C/C++�е��ַ�����������
void basicTypes_strings_module::test0(void)
{
	char Cstr1[] = "this is a C type std::string";				// ʹ���ַ�����������ʼ��char���顪����C�����ַ���
	char Cstr2[] = "hahahahaha";
	char Cstr3[] = "hehehehehehe";
	const char* Cstr4 = NULL;
	std::string str1 = "this is a C++ std::string object";		// ʹ���ַ�����������ʼ��std::string���󡪡�C++�е��ַ���
	std::string str2 = Cstr2;														// ʹ��C�����ַ�����C++���ַ��������ʼ����



	// C����ַ�����std::string���󶼿���ʹ���ַ�����������ʼ����������ʹ��std::cout��ӡ
	std::cout << "\t C���C++���ַ���������ʹ���ַ�����������ʼ����������ʹ��std::cout��ӡ��" << std::endl;
	std::cout << "\tCstr1 == " << Cstr1 << std::endl;
	std::cout << "\tstr1 == " << str1 << std::endl;
	std::cout << std::endl;
	std::cout << "\t C++�ַ����������ʹ��C����ַ�������ʼ����" << std::endl;
	std::cout << "\tstring str2 = Cstr2;	str2 == " << str2 << std::endl;
	std::cout << std::endl;


	// C�����ַ�����ʼ���Ժ�Ͳ�����Ϊһ�����屻��ֵ��ֻ������ַ��ظ�д������ʹ��strcpy()�Ⱥ���
	



	//	C�����ַ������Ը�std::string����ֵ
	str2 = Cstr3;															// ʹ��C�����ַ�����C++���ַ�������ֵ��
	std::cout << "" << std::endl;
	std::cout << "\tC�����ַ������Ը�C++���ַ�������ֵ:" << std::endl;
	std::cout << "\tstr2 = Cstr3; str2 == " << str2 << std::endl;


	// std::string��c_str()�����������װ��c����ַ���
	Cstr4 = str2.c_str();									// ע�ⷵ�ص�c����ַ�����const�ġ�
	std::cout << "Cstr4 == " << Cstr4 << std::endl;


	// std::string������ַ����������ıȽ�
	str1 = "hahaha";
	//		������ͬ��std::string������ַ���������==��������true���������ڼ��顣
	std::cout << "(int)(str1 == \"hahaha\") == "<<(int)(str1 == "hahaha") << std::endl;

}



// test1: �ַ������õ�API
void basicTypes_strings_module::test1(void)
{
	std::cout << "\n\n\n\n" << std::endl;
    std::cout << "test1: std::string��Ľӿ�" << std::endl;

	std::string str1;					// Ĭ�Ϲ��캯������Ŀ�std::string
	std::string str2(9,'a');				// ���ɸ���ͬ�ַ������std::string
	std::string str3("hello world");		// �ַ��������������std::string


	// 1. ���ʵ���Ԫ�صĽӿڣ�operator[], at(), front(), back()
	std::cout << "\t���ʵ���Ԫ�صĽӿڣ�operator[], at(), front(), back():" << std::endl;
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


	// 2. �������Ԫ�صĽӿڣ�insert, replace, substr, append
	str1 = str2.substr(2,4);		// ����Ϊ��ֹ�ַ����������Ǳ����䡣
	str2.replace(3, 2, "bcbcbc");
	str3.insert(6, "new ");			// �ڵ�6���ַ�������룬����������ָ�ӡ���һ����ʼ��
	std::cout << "\t�������Ԫ�صĽӿڣ�insert, replace, sub_str, append, clear" << std::endl;
	std::cout << "\tstr1 == "<< str1 << std::endl;
	std::cout << "\tstr2 == "<< str2 << std::endl;
	std::cout << "\tstr3 == "<< str3 << std::endl;
	str1.clear();
	std::cout << "str1.clear(); str1 == " << str1 << std::endl;
	std::cout << std::endl << std::endl;

	// 3. std::string����֮��Ĳ�����operator+=
	str1 += str2;
	str1 += str3;
	std::cout << "\tstring����֮��Ĳ�����operator+=" << std::endl;
	std::cout << "\tstr1 == " << str1 << std::endl;
	std::cout << std::endl << std::endl;

	// 4. �������ӿڣ�begin, cbegin(C++11), rbegin(C++11), crbegin(C++11)...
	std::cout << "\tʹ�÷���������������ӡ�ַ�����"<< std::endl;
	for_each(str3.rbegin(), str3.rend(), disp<char>);
	std::cout << std::endl << std::endl;

	// 5. 1 �ַ���ת��Ϊ��������std::stoi(), std::stol(), std::stoll(), std::stof() �������� C����ַ������ַ��������ַ���תΪ��ֵ(c++11)��
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
	int num5 = std::stoi(str5);		// ǰ��Ŀո�Ӱ����ֵת��
	int num6 = std::stoi(str6);		// �����м��пո�Ļ�����ضϿո��������֡�
	
	std::cout << num0 << std::endl;
	std::cout << num1 << std::endl;
	std::cout << num2 << std::endl;
	std::cout << num3 << std::endl;
	// std::cout << std::stoi(str3) << std::endl;		�ַ������з���ֵ�ַ�������жϡ�
	std::cout << num4 << std::endl;
	std::cout << num5 << std::endl;
	std::cout << num6 << std::endl;
	std::cout << std::endl << std::endl;

	// 5.2 ��������ת��Ϊ�ַ�����a. ʹ��stringstreamʵ�֣� b. std::to_string()��std::to_wstring()������ֵת��Ϊ�ַ�����C++11��
	str1 = std::to_string(321);
	str2 = std::to_string(987654321);
	wstr1 = std::to_wstring(12345);
	std::cout << str1 << std::endl;
	std::cout << str2 << std::endl;
	std::wcout << wstr1 << std::endl;
	std::cout << std::endl << std::endl;

	// 6. �Ӵ�������
	str1 = "asdfhjkl12345";

	//		substr()
	str2 = str1.substr(3, 4);
	std::cout << str2 << std::endl;
	str2 = "9999";
	str1.erase(3, 4);
	str1.insert(3, str2);
	std::cout << str1 << std::endl;

}




// test2: std::string������������
void basicTypes_strings_module::test2(void)
{
	std::cout << "\n\n\n\n" << std::endl;
	std::cout << "test2: std::string������������" << std::endl;

	// std::getline�����������������ж�ȡ�������std::string����
	//		ע��������cin������std::string������Ϊ�����ո���жϡ�
	std::string answer, number;
	std::cout << "Jun Lei: are you ok?" <<std::endl;
	setbuf(stdin, NULL);
	std::getline(std::cin, answer);
	std::cout << "Me: " << answer << std::endl;
	std::cout << "Jun Lei: whatever, have a nice day!" << std::endl;
	//		getline()���������ַ�����ֹͣ��־��
	std::cout << "��������룬�Ծ��ż�������" << std::endl;
	setbuf(stdin, NULL);
	std::getline(std::cin, number, '#');
	std::cout << "������ĺ����ǣ�" << number << std::endl;
}



 
// test3: C�����е��ַ�����API
void basicTypes_strings_module::test3(void)
{
		// �ַ��������������puts, fgets, fputs 
		// ��������strcpy
		// ���ӡ���strcat
		// �Ƚ�strcmp

		const char* str1 = "\tthis is a std::string literal";
		char str2[] = "\tthis is a copy of a std::string literal";
		char str3[100] = { '\0' };

		printf("\n\n\n\n");
		printf("test3: C�����е��ַ�����API\0");


		// int puts(const char* str)������ӡ�ַ�����
		puts(str1);
		puts(str2);
		printf("\n\n");


		// char *fgets(char* str, int count, FILE* stream)�����Ӹ������ж�ȡ���������޶����ַ����洢�ڸ����ַ������У�
		printf("\tPlease input a std::string: ");
		setbuf(stdin, NULL);
		fgets(str3, 20, stdin);
		printf("\t%s", str3);
		printf("\n\n");


		// fputs��������NULL��β���ַ���str��ÿ���ַ�д�뵽�����stream�С�
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

		// strcpy()�����������ַ���������ȫ������ʹ��strncpy()
		/*
			 char *strcpy( char *dest, 					Ŀ���ַ���
			 						 const char *src				Դ�ַ���
			 					)
		*/

		// strncpy()�������������ַ���
		/*
			char *strncpy( char *dest,				Ŀ���ַ���
									const char *src, 			Դ�ַ�����
									size_t n							��ิ�Ƶ��ַ�������src����С��nʱ��destʣ�ಿ���ÿ��ֽ���䡣
									) 

		
		*/
		strcpy(string3, string1);	


		//			int strcmp(str1, str2)������ȷ���0��������ȣ��Ƚϵ�һ������ȵ��ַ���ASCII�룬��<�ҵĻ����ظ���
		std::cout << "strcmp(string1, string3) == " << strcmp(string1, string3) << std::endl;
		std::cout << "strcmp(\"abc\", \"abd\") == " << strcmp("abc", "abd") << std::endl;

		strcat(string1, string3);			// ɾ��string1ĩβ��'\0'����std::string�����ݸ��Ƶ�������
		strcat(string1, string2);			// һ��ʼ��Ҫ��֤string1���ٵĿռ��㹻�󣬿����ݵ���string2������
		std::cout << string1 << std::endl;


		// strcpy()��memcpy()�ıȽ�
		std::fill(string1, string1+49, '\0');		
		std::fill(string3, string3+19, '\0');
		strcpy(string1, "hahaha\0wawawawa");								// strcpy()����'\0'��ֹͣ						
		memcpy(string3, "hahaha\0wawawawa", 16);					// memcpy()һ���´���趨���ֽ�����
		
		printf("%s\n", string1);						
		printf("%s\n", string3);
		printf("%s\n", string3+7);


		// Ӣ����ĸ��Сдת����std::toUpper(), std::toLower();
		std::string lowerStr = "asdf";
		std::string upperStr;
		for (const auto& ch: lowerStr)
		{
			int temp = std::toupper(static_cast<unsigned char>(ch));
			upperStr.push_back(static_cast<char>(temp));
		}
		std::cout << upperStr << std::endl;


}
 


// test4: �ַ�����
void basicTypes_strings_module::test4(void)
{
	printf("\n\n\n\n");
	printf("test4: �ַ�����\n");

	// �������ġ�Ӣ�ġ����ֲ�ѯ����루����ַ�ΪASCII�룬ȫ���ַ�ΪGB2312��
	//		1. ��������ѯ���ַ������������ַ������ָ�롣
	char str[] = "�ǵз��ط�kju421";
	unsigned char* puc = (unsigned char*)str;


	//		2. ��ӡ����ѯ���ַ�����
	printf("\tԭ�ַ�����str == %s\n", str);


	//		3. ʹ��unsigned char*ָ����ʮ��������������ʽ�����ȡ�ַ����е����ݣ�
	printf("\tʹ��unsigned char*ָ����ʮ��������������ʽ�����ȡ�ַ����е����ݣ�\n");
	do
	{
		printf("\t0x%x,", *puc);
		puc++;

	} while (*puc != '\0');
	printf("\n");



	//	����ASCII���GB2312�룬������ȫ���ַ������ַ��� 
	//		1. �����յ��ַ�����������д�ַ����ݵ�unsigned charָ��
	char str2[100] = { '\0' };
 

	//		 2. д��ASCII������
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
	printf("\t��unsigned charָ������ֽ�д��ASCII���ݵ��ַ����У�ÿ���ֽ����λΪ0��\n");
	printf("\tstr == %s\n", str2);


	//		3. д��GB2312������
	*puc = 0xb0;						 
	*(puc + 1) = 0xa1;			 
	*(puc + 2) = 0xb0;				 
	*(puc + 3) = 0xa2;				 
	*(puc + 4) = 0xb0;			 
	*(puc + 5) = 0xa3;				 
	*(puc + 6) = 0xb0;				 
	*(puc + 7) = 0xa4;			 
	*(puc + 8) = '\0';
	printf("\t��unsigned charָ������ֽ�д��GB2312���ݵ��ַ����У�ÿ���ֽ����λΪ1��\n");
	printf("\tstr == %s\n", str2);

}



// test5: �����㷨C++ʵ��
void basicTypes_strings_module::test5(void)
{
	std::cout << "\n\n\n\n" << std::endl;
	std::cout << "test5: �����㷨C++ʵ��" << std::endl;

	// �ַ���ƥ�䡪����һ������ַ���T������ĳ���ַ���P�����г���λ�á�
	/*
	*/

	// C++�е�����ʵ���ַ���ƥ�䣺
	std::string str1 = "asdfajiuiuwww.github.comasdfuoiup";

	//			std::string���find()�������������ַ����е��ַ����Ӵ�
	//					size_type����std::string��vector��������ͣ��Ǳ�ʾ�����������޷�����������
	std::string::size_type num = str1.find("github", 0);							// �ڶ���������������ʼ��λ�á�
	if (num == std::string::npos)															// ����������ʱ�򷵻�npos��һ�����-1
		std::cout << "û���ҵ�ģ���ַ���" << std::endl;
	else
		std::cout << "�ҵ�ģ���ַ�����λ����" << num << std::endl;


	//			std::string���find_first_of()��find_last_of()�������������ַ����Ӵ���һ�Ρ����һ�γ��ֵ�λ��
	std::string::size_type num1 = str1.find_first_of("asd");
	std::string::size_type num2 = str1.find_last_of("asd");
	if (num1 != num2)			
		std::cout << "�Ӵ�asd�����˲�ֹһ��" << std::endl;				// ���������ַ������ж��Ӵ���Ŀ���ַ����г��ֵĴ���
}



// test6: ���ַ�wchar_t�����ַ���wstring
void basicTypes_strings_module::test6(void)
{
	// wstring��<std::string>ͷ�ļ��ж��壬���Ӧ��������ǰ�����L
	std::wstring str = L"abcde";
	std::cout << str.size() << std::endl;
	std::cout << str[0] << std::endl;
	std::cout << str[1] << std::endl;
	std::cout << str[2] << std::endl;
	std::cout << static_cast<unsigned char>(str[1]) << std::endl << std::endl;

	// 1. ���ַ�����ͨ�ַ���ת����
	char ch1 = '1';
	char ch2 = '9';
	wchar_t wch1 = L'1';
	wchar_t wch2 = L'9';
	wchar_t wch3 = static_cast<wchar_t>(ch1);
	std::cout << static_cast<int>(ch1) << std::endl;	// 49
	std::cout << static_cast<int>(ch2) << std::endl;	// 57
	std::cout << static_cast<int>(wch1) << std::endl;	// 49
	std::cout << static_cast<int>(wch2) << std::endl;	// 57
	std::cout << static_cast<char>(wch2) << std::endl;				// 9	���ַ����ַ�����ʹ��static_castת�������ݲ��䡣
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


	// 2. VC++�еĿ��ַ�TCHAR��������ؽӿ�

		/*
		C++֧�������ַ������������ANSI���루ʹ��""��������Unicode���루ʹ��L""������
		TCHARʹ���������룬�������ַ����������������ͳһ��
		#ifdef   UNICODE
			typedef   wchar_t   TCHAR;
		#else
			typedef   unsigned   char   TCHAR;
		#endif
	*/
	std::cout << typeid(wchar_t).name() << std::endl;
	std::cout << typeid(TCHAR).name() << std::endl;
	std::cout << typeid(WCHAR).name() << std::endl;

	const TCHAR* wstr1 = L"��˹�ٷ��͵����͵���˹�ٷ�";
 
	// std::locale()�����������Ի���
	std::wcout.imbue(std::locale(std::locale(), "", LC_CTYPE));	// ����wcout�����Ի�����ȱ����һ����ӡ���Ļ��д���
	std::wcout << wstr1 << std::endl;

	TCHAR modulePath[MAX_PATH + 1] = { 0 };
	GetModuleFileName(NULL, modulePath, MAX_PATH);
	std::wcout << L"��ǰ����ģ��Ϊ�� "  << modulePath << std::endl;

	// wcsrchr()�������ַ�������
	TCHAR* pc = wcsrchr(modulePath, TEXT('\\'));				// pcָ���ַ���modulePath�����һ�γ���'\\'��λ�ã�
	std::wcout << L"��ǰ����ģ����Ϊ��" << pc << std::endl;

	TCHAR tail[100] = { 0 };
	//	wcscpy_s()�������ַ�������
	wcscpy_s(tail, sizeof(tail) / sizeof(TCHAR), pc);
	std::wcout << L"��ǰ����ģ����Ϊ��" << tail << std::endl;
	std::wcout << tail << std::endl;

	// �ض��ַ���
	*pc = L'\0';
	std::wcout << L"��ǰ����ģ������Ŀ¼Ϊ��"  << modulePath << std::endl;
	std::cout << wcscmp(tail, TEXT("\\mytest0.exe")) << std::endl;

}
