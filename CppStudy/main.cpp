#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <cmath>
#include <windows.h>

#include "reader.h"


// debug note
/*
	x64 Release�����£������O2����Ż������ò��Ժ��������ӡ�κ����ݣ���֪����ʲôԵ�ʣ�

*/


// ��νṹ���½� �� ģ�� �� ���Ժ���

HMODULE g_Hdll = nullptr;				// ��̬������
bool blInputValid = false;					// �˵��������ж������Ƿ���Ч�ı�ʶ����
int inputNum = 0;							// �˵��������û����������
int interfaceLevel = 1;						// ��ǰ�˵�����Ĳ㼶�����˵���һ����


int main(int argc, char** argv)
{
	reader* pr = reader::getInstance();
	while (1 == interfaceLevel) 
	{
		pr->showChapList();
		blInputValid = (scanf("%d", &inputNum) > 0);

		// ������ֵ�����������������롣
		if (!blInputValid)
		{
			std::cout << "Invalid input. Please input again:" << std::endl;
			setbuf(stdin, NULL);			// stdin��������Ĭ�ϻ�����תΪ�޻�����������������˻������е����ݡ�
											// ��Ҫ��fflush����ջ��������ú����ܶ������֧�ֵò��á�
			continue;
		}

		if (-1 == inputNum) 
		{
			interfaceLevel = 0;
			break;
		}

		if(!pr->selectChap(static_cast<CHAP_ENUM>(inputNum))) 
		{
			std::cout << "������һ����Чѡ�" << std::endl;
			continue;
		}		

		if (!pr->isNullChap()) 
			interfaceLevel = 2;

		while (2 == interfaceLevel)
		{
			pr->showModuleList();
			blInputValid = (scanf("%d", &inputNum) > 0);

			// ������ֵ�����������������롣
			if (!blInputValid)
			{
				std::cout << "Invalid input. Please input again:" << std::endl;
				setbuf(stdin, NULL);			// stdin��������Ĭ�ϻ�����תΪ�޻�����������������˻������е����ݡ�
												// ��Ҫ��fflush����ջ��������ú����ܶ������֧�ֵò��á�
				continue;
			}

			if (-1 == inputNum) 
			{
				interfaceLevel = 1;
				break;
			}

			if(!pr->selectMol(inputNum)) 
			{
				std::cout << "������һ����Чѡ�" << std::endl;
				continue;
			}

			if (!pr->isNullModule()) 
				interfaceLevel = 3;

			while (3 == interfaceLevel) 
			{
				std::cout << "ѡ��Ҫִ�е�test��ţ�-1�˳���" << std::endl;
				blInputValid = (scanf("%d", &inputNum) > 0);

				// ������ֵ�����������������롣
				if (!blInputValid)
				{
					std::cout << "Invalid input. Please input again:" << std::endl;
					setbuf(stdin, NULL);			// stdin��������Ĭ�ϻ�����תΪ�޻�����������������˻������е����ݡ�
													// ��Ҫ��fflush����ջ��������ú����ܶ������֧�ֵò��á�
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



