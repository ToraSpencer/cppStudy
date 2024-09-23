#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <cmath>
#include <windows.h>

#include "reader.h"


// debug note
/*
	x64 Release环境下，如果开O2最大优化，调用测试函数不会打印任何内容，不知道是什么缘故；

*/


// 层次结构：章节 → 模块 → 测试函数

HMODULE g_Hdll = nullptr;				// 动态库句柄；
bool blInputValid = false;					// 菜单界面中判断输入是否有效的标识符。
int inputNum = 0;							// 菜单界面中用户输入的整数
int interfaceLevel = 1;						// 当前菜单界面的层级，主菜单是一级。


int main(int argc, char** argv)
{
	reader* pr = reader::getInstance();
	while (1 == interfaceLevel) 
	{
		pr->showChapList();
		blInputValid = (scanf("%d", &inputNum) > 0);

		// 若输入值不是整数，重新输入。
		if (!blInputValid)
		{
			std::cout << "Invalid input. Please input again:" << std::endl;
			setbuf(stdin, NULL);			// stdin输入流由默认缓冲区转为无缓冲区，这样就清空了缓冲区中的内容。
											// 不要用fflush来清空缓存区，该函数很多编译器支持得不好。
			continue;
		}

		if (-1 == inputNum) 
		{
			interfaceLevel = 0;
			break;
		}

		if(!pr->selectChap(static_cast<CHAP_ENUM>(inputNum))) 
		{
			std::cout << "请输入一个有效选项。" << std::endl;
			continue;
		}		

		if (!pr->isNullChap()) 
			interfaceLevel = 2;

		while (2 == interfaceLevel)
		{
			pr->showModuleList();
			blInputValid = (scanf("%d", &inputNum) > 0);

			// 若输入值不是整数，重新输入。
			if (!blInputValid)
			{
				std::cout << "Invalid input. Please input again:" << std::endl;
				setbuf(stdin, NULL);			// stdin输入流由默认缓冲区转为无缓冲区，这样就清空了缓冲区中的内容。
												// 不要用fflush来清空缓存区，该函数很多编译器支持得不好。
				continue;
			}

			if (-1 == inputNum) 
			{
				interfaceLevel = 1;
				break;
			}

			if(!pr->selectMol(inputNum)) 
			{
				std::cout << "请输入一个有效选项。" << std::endl;
				continue;
			}

			if (!pr->isNullModule()) 
				interfaceLevel = 3;

			while (3 == interfaceLevel) 
			{
				std::cout << "选择要执行的test序号，-1退出。" << std::endl;
				blInputValid = (scanf("%d", &inputNum) > 0);

				// 若输入值不是整数，重新输入。
				if (!blInputValid)
				{
					std::cout << "Invalid input. Please input again:" << std::endl;
					setbuf(stdin, NULL);			// stdin输入流由默认缓冲区转为无缓冲区，这样就清空了缓冲区中的内容。
													// 不要用fflush来清空缓存区，该函数很多编译器支持得不好。
					continue;
				}

				if (-1 == inputNum)
				{
					interfaceLevel = 2;
					break;
				}
				
				pr->runTest(inputNum);
				std::cout << std::endl << std::endl;
			}
		}	
	}

	getchar();
	return 0;
}



