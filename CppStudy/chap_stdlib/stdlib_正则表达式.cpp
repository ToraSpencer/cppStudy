#include <cstdio>
#include <cstring>


#include <string>
#include <iostream>
#include <vector>						//vector��ģ����ͷ�ļ�<vector>��
#include <algorithm>
#include <iterator>
#include <regex>

#include <cstdio>
 

#include "stdlib_������ʽ.h"




virtualModule* stdlib_regex_module::getInstance()		// �̲߳���ȫ�ĵ���ģʽ
{
	if (nullptr != p_moduleIns)
	{
		delete p_moduleIns;
	}
	p_moduleIns = new stdlib_regex_module;
	return p_moduleIns;
}




//	test0:  Ӧ��ʵ������ƥ�������ʽ
void stdlib_regex_module::test0(void)
{
	std::cout << "\n\n\n\n" << std::endl;
	std::cout << "test " << std::endl;

	// ������ʽ��ƥ�����
	/*
		��1�飨���û�������
			ƥ�����0��9��A��Z��a��z���»��ߡ��㡢���ַ�֮�е������ַ����ظ�һ�������
			�м䣬һ����@������
		�ڶ��飨��������
			ƥ�����0��9��a��z֮�е������ַ��ظ�һ������ϣ�
							����һ���㣬����a��z֮�е������ַ��ظ�2��3�飨��com��cn�ȣ���
							�ڶ����ڲ���һ�飬һ���㣬����a��z֮�е������ַ��ظ�2�飨��cn��fr�ȣ�
							�ڲ�һ�����ظ���λ�һ��
	*/

	std::string email_address;
	std::string user_name, domain_name;

	std::regex pattern("([0-9A-Za-z\\-_\\.]+)@([0-9a-z]+\\.[a-z]{2,3}(\\.[a-z]{2})?)");



	// �����ļ���β����Windows��Ctrl+Z��UNIX��Ctrl+D������ѭ��
	while (std::cin >> email_address)
	{
		if (regex_match(email_address, pattern))
		{
			std::cout << "������ĵ����ʼ���ַ�Ϸ�" << std::endl;

			// ��ȡ��һ��
			user_name = std::regex_replace(email_address, pattern, std::string("$1"));

			// ��ȡ�ڶ���
			domain_name = std::regex_replace(email_address, pattern, std::string("$2"));

			std::cout << "�û�����" << user_name << std::endl;
			std::cout << "������" << domain_name << std::endl;
			std::cout << std::endl;
		}
		else
		{
			std::cout << "������ĵ����ʼ���ַ���Ϸ�" << std::endl << std::endl;
		}
	}
 

}



// test1:  
void stdlib_regex_module::test1(void)
{
	std::cout << "\n\n\n\n" << std::endl;
	std::cout << "test1:  " << std::endl;


}



// test2: 
void stdlib_regex_module::test2(void)
{
	std::cout << "\n\n\n\n" << std::endl;
	std::cout << "test2:  " << std::endl;


}



// test3: 
void stdlib_regex_module::test3(void)
{
	std::cout << "\n\n\n\n" << std::endl;
	std::cout << "test3:  " << std::endl;


}



// test4:  
void stdlib_regex_module::test4(void)
{
}



// test5:  
void stdlib_regex_module::test5(void)
{
}



void stdlib_regex_module::test6(void) 
{

}