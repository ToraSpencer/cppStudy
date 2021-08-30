#include <iostream>
#include <string>
#include <typeinfo>


#include <cstdio>

#include "syntax_Ԥ����ָ��.h"

#define EPS 1e-10					//����ǳ�С��һ����EPSilon�������������������ֵʱ����Ϊ0
#define PI 3.14159

 
// ֪ʶ��
/*
#define���������꣨macro������
	��ʽ
			#define ��  �滻��
			��һ�����滻�峬��һ�У���һ�е���ĩβ��Ҫ��\
	ע��
			���滻�ı�������ȫ���ı��滻�����Ǻ��滻Ϊ�ַ���
			����һ���Ǻ�(token)���ַ������������ַ����ַ���
			������������#define PI 3.14159
			˫�����е�PI���ᱻ�滻����Ϊ���ַ����ַ���
			�����ط���PI�ᱻ�滻���ı�3.14159
	���ࡪ������1. ������(object-like macro)��	2. �ຯ����(function-like macro)

�꺯�����ຯ���꣩
��test2;


����ض���
		�ȳ������еĺ궨�壺#undef  PI
		���ض���ú꣺ #define PI 3.14159

#include���������ļ�����


Ԥ�������
		C��׼��Ԥ����õ�һЩ����
		�����Ա��ض���
		��__FILE__, __LINE__��


Ԥ���������ָ��
#line
����__FILE__��__LINE__������
���ӣ�
#line 1000				 // ��ǰ�к�����Ϊ1000
#line 10 "temp.c"     // ��ǰ�к�����Ϊ10����ǰԴ�ļ�������Ϊtemp.c

��������
#ifdef, #else, #endif
#ifndef, #else, #endif
#if, #elif, #else, #endif

�Ǻ�ճ�ϼ�����##�����
�����ں���滻����
�������Ǻ�ճ�ϳ�һ���Ǻţ�Ȼ����Ϊ�ú���滻��


#pragma������������ָʾ
��Դ��������ӱ���ָ��
�趨��������״̬��������ָʾ���������һЩ�ض��Ķ�����
#pragma once
ͨ������ͷ�ļ��У�ʹ�ø�ͷ�ļ�ֻ������һ�Ρ�
�Ǳ�׼��������׼�ķ���Ӧ����ʹ��#ifndef
���Ǳ��㷺���ã�ע����Щ�ϵı��������ܲ�֧�֡�
#pragma comment
���ӿ��ļ���
#pragma pack
�����ڴ����
 

#error������������ָ��
��Ԥ������������ʾ�ô���ָ���е��ı�
���ӣ�#error not C11
 

����Ԥ�����
ANSI C��׼���м�����׼Ԥ����꣺
__FILE__����ǰԴ�����ļ������ַ���������
__LINE__����ǰԴ�����кŵ����ͳ���
__DATE__��Ԥ��������ڣ��ַ���������
__TIME__����������ʱ�䣬�ַ���������
__STDC__����Ҫ������ϸ���ѭANSI C��׼ʱ�ñ�ʶ����ֵΪ1��
__cplusplus������дC++����ʱ�ñ�ʶ�������塣

���������ĺ궨��
#define _DEBUG              // ���Ժ꣬���ʹ��VS������Ŀʱ�����������ѡ��Debug�Ļ��������Զ�����˺ꡣ
#define _NDEBUG             // release��
#define _WINDLL             // ��ʾҪ��һ���õ�MFC��DLL
#define _DLL                // ����������Ϊ��̬���ӿ�ʱ����ֵΪ1��

*/




virtualModule* syntax_preprocessing_instruction_module::getInstance()		// �̲߳���ȫ�ĵ���ģʽ
{
	if (nullptr != p_moduleIns)
	{
		delete p_moduleIns;
	}
	p_moduleIns = new syntax_preprocessing_instruction_module;
	return p_moduleIns;
}



// test0: ����Ԥ������ţ����������� 
void syntax_preprocessing_instruction_module::test0(void)
{
	std::cout << "\n\n\n\n" << std::endl;
	std::cout << "test0: ����Ԥ������ţ������������" << std::endl;

	std::cout << "\t��ǰԴ�ļ������ƣ�__FILE__ == " << __FILE__ << "�� ���ַ�����������" << std::endl;
	std::cout << "\t��ǰԴ�ļ��еĴ����кţ�__LINE__ == " << __LINE__ << "����ʮ����������" << std::endl;
	std::cout << "\t��ǰԴ�ļ��Ĵ������ڣ�__DATE__ == " << __DATE__ << "�� ���ַ�����������" << std::endl;
	std::cout << "\t��ǰԴ�ļ��ı���ʱ�䣺__TIME__ == " << __TIME__ << "�� ���ַ�����������" << std::endl;
	std::cout << std::endl;

#ifdef __cplusplus
	std::cout << "\tC/C++��ϱ���п���ʹ��#ifdef __cplusplus ... #endif �� extern \"C\"{}������C��C++�Ĵ��롣" << std::endl;
	std::cout << "\tC++03��__cplusplus = 199711L" << std::endl;
	std::cout << "\tC++11��__cplusplus = 201103L" << std::endl;
	std::cout << "\t���Ը���__cplusplus���ֵ���жϵ�ǰC++�������İ汾��" << std::endl;
	std::cout << "\t��ǰ��Ŀ�У�__cplusplus == " << __cplusplus << std::endl;
	std::cout << std::endl;
#endif


	// #error #warning ������󡢱��뾯��
#ifndef __cplusplus
#error this project should be processed with c++ compiler
#endif



#line 1000								// ��ǰ�к�����Ϊ1000 
	std::cout << "\t��ǰ�к�����Ϊ1000 ��#line 1000; __LINE__ == " << __LINE__ << std::endl;
#line 10 "temp.c"						 // ��ǰ�к�����Ϊ10����ǰԴ�ļ�������Ϊtemp.c
	std::cout << "\t��ǰ�к�����Ϊ10����ǰԴ�ļ�������Ϊtemp.c:" << std::endl;
	std::cout << "\t__LINE__ == " << __LINE__ << std::endl;
	std::cout << "\t__FILE__ == " << __FILE__ << std::endl;

	// __COUNTER__��ÿ����һ��+1
	std::cout << "__COUNTER__  == " << __COUNTER__ << std::endl;
	std::cout << "__COUNTER__  == " << __COUNTER__ << std::endl;

#if 0
	//		#if 0 �е����ݲ�����룬�������ﲻ���1
	std::cout << "__COUNTER__  == " << __COUNTER__ << std::endl;
#endif

	if (0) 
	{
		std::cout << "__COUNTER__  == " << __COUNTER__ << std::endl;
	}
	else
	{
		// ����ķ�֧��Ȼ�������У����ǻ���룬����������1.
		std::cout << "__COUNTER__  == " << __COUNTER__ << std::endl;
		std::cout << "__COUNTER__  == " << __COUNTER__ << std::endl;
	}

}



// test1: �꺯��
/*
���еĲ������������������滻�弴Ϊ�����塣
�꺯��û��inline������ȫ����Ϊֻ�ǵ�����չ������������ȫ���
ע��ÿ����������ü����ţ�����������������ŵĻ�TIMES(1+2,3+4)��չ��Ϊ1+2*3+4��
*/
#define TIMES(x,y) (x)*(y)	


// 	#���Խ��꺯���еĲ����ַ�����������ʱ���꺯���еĲ���xΪ__FILE__�����䲻�ᱻ��չ��������ֱ��ת��Ϊ�ַ�����
#define _STRING(x) #x
void syntax_preprocessing_instruction_module::test1(void)
{
	std::cout << "\n\n\n\n" << std::endl;
	std::cout << "test2: �꺯��" << std::endl;

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
