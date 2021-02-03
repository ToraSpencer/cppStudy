#include <cstdio>
#include <cstring>


#include <string>
#include <iostream>
#include <vector>						//vector类模板在头文件<vector>中
#include <algorithm>
#include <iterator>
#include <regex>

#include <cstdio>
 

#include "stdlib_正则表达式.h"




virtualModule* stdlib_regex_module::getInstance()		// 线程不安全的单例模式
{
	if (nullptr != p_moduleIns)
	{
		delete p_moduleIns;
	}
	p_moduleIns = new stdlib_regex_module;
	return p_moduleIns;
}




//	test0:  应用实例——匹配邮箱格式
void stdlib_regex_module::test0(void)
{
	std::cout << "\n\n\n\n" << std::endl;
	std::cout << "test " << std::endl;

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

	std::string email_address;
	std::string user_name, domain_name;

	std::regex pattern("([0-9A-Za-z\\-_\\.]+)@([0-9a-z]+\\.[a-z]{2,3}(\\.[a-z]{2})?)");



	// 输入文件结尾符（Windows用Ctrl+Z，UNIX用Ctrl+D）结束循环
	while (std::cin >> email_address)
	{
		if (regex_match(email_address, pattern))
		{
			std::cout << "您输入的电子邮件地址合法" << std::endl;

			// 截取第一组
			user_name = std::regex_replace(email_address, pattern, std::string("$1"));

			// 截取第二组
			domain_name = std::regex_replace(email_address, pattern, std::string("$2"));

			std::cout << "用户名：" << user_name << std::endl;
			std::cout << "域名：" << domain_name << std::endl;
			std::cout << std::endl;
		}
		else
		{
			std::cout << "您输入的电子邮件地址不合法" << std::endl << std::endl;
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