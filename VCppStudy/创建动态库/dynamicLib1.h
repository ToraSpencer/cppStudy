#ifndef _DYNAMICLIB1_H
#define _DYNAMICLIB1_H

// ���� SDKDDKVer.h ��������õ���߰汾�� Windows ƽ̨��
//		���ҪΪ��ǰ�� Windows ƽ̨����Ӧ�ó�������� WinSDKVer.h������
//		�� _WIN32_WINNT ������ΪҪ֧�ֵ�ƽ̨��Ȼ���ٰ��� SDKDDKVer.h��
#include <SDKDDKVer.h>	

//#define WIN32_LEAN_AND_MEAN             // �� Windows ͷ���ų�����ʹ�õ�����
#include <windows.h>					// Windows ͷ�ļ�: 
#endif
#include <iostream>
#include <locale>

// ���ڱ�ͷ�ļ������ɶ�̬�⡢ʹ�ö�̬�����Ŀ�ж�Ҫʹ�ã�������Ҫ���������������Ҫ�����̬�⣬���ǵ��붯̬�⡣



/*
	�ڴ�ͳ�ķǹ���̬���У�һ���ִ���򵥵ظ��ӵ����õĳ����С������������ͬʱ����ͬһ���ӳ��򣬾ͻ���������Ƕδ��롣
	���������ʹ��ͬһ��������ʱ��DLL���Լ����ڴ��̺������ڴ��м��ش�����ظ������������ڴ�������á�

*/



// ������̬��
/*
	�ؼ���__declspec
			Microsoft c++��ר�õĹؼ���
			�����һЩ���Կ��ԶԱ�׼C++�������䣬��align��allocate��deprecated�� dllexport��dllimport��
			����
				_declspec(dllimport) ����ԭ��
						��ʾ��������Ǵӱ��DLL�е��룬��������Ҫʹ�á�
				_declspec(dllexport) ����ԭ��
						��ʾ������������������������ɵ�DLL�С�
*/




// ���ɶ�̬�����Ŀ��Ӧ�ö���Ԥ�����DLL_EXPORTS���Ӷ�ִ�������̬��ķ�֧��
//		 ����1����Ŀ����->C/C++ -> Ԥ������ -> Ԥ�����������м����DLL_EXPORTS
//		 ����2��stdafx.h��#define DLL_EXPORTS
#ifdef DLL_EXPORTS
#define DLL_API __declspec(dllexport) 
#else
#define DLL_API __declspec(dllimport)
#endif

extern "C"	// һ��Ҫ���ϣ�
{
	/*
		��ΪC++��name mangling���ָı���ƣ�����Դ�ļ��к���fun�ڱ������ɵ�Ŀ���ļ������ֲ���fun������fun@@YAHXZ���ϲ���֮��ģ�
		���Բ�ʹ��extern "C"�Ļ�GetProcAddress���Ҳ���������ַ��
	*/
	DLL_API int funci();

	DLL_API void dllDisp(void);

}


namespace MYDLL
{
	// 1. DLL�ж��庯��
	extern "C" 
	{
		DLL_API void disp(void);
		DLL_API void printCurrentPath(void);
	}
	


	// 2. DLL���Զ�����
	class DLL_API calculator				// __declspec(dllexport) Ҫ����class���棬������ǰ
	{
	public:

		double Add(double a, double b);

		double Subtract(double a, double b);

		double Multiply(double a, double b);

		double Divide(double a, double b);

	};

}

 