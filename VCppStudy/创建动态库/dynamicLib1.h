#ifndef _DYNAMICLIB1_H
#define _DYNAMICLIB1_H

// 包括 SDKDDKVer.h 将定义可用的最高版本的 Windows 平台。
//		如果要为以前的 Windows 平台生成应用程序，请包括 WinSDKVer.h，并将
//		将 _WIN32_WINNT 宏设置为要支持的平台，然后再包括 SDKDDKVer.h。
#include <SDKDDKVer.h>	
#include <windows.h>					// Windows 头文件: 
#endif

#include <iostream>
#include <locale>
 

/*
	在传统的非共享动态库中，一部分代码简单地附加到调用的程序中。如果两个程序同时调用同一个子程序，就会出现两份那段代码。
	当多个程序使用同一个函数库时，DLL可以减少在磁盘和物理内存中加载代码的重复量，且有助于代码的重用。

*/


// 创建动态库
/*
	关键字__declspec
			Microsoft c++中专用的关键字
			配合着一些属性可以对标准C++进行扩充，如align、allocate、deprecated、 dllexport、dllimport等
			例：
				_declspec(dllimport) 函数原型
						表示这个函数是从别的DLL中导入，本程序需要使用。
				_declspec(dllexport) 函数原型
						表示这个函数将导出到本程序生成的DLL中。
*/


// 宏DLL_EXPORTS
/*
	本头文件在生成动态库、使用动态库的项目中都要使用
	生成动态库的项目中应该定义预编译宏DLL_EXPORTS，从而执行输出动态库的分支。
		 方法1：项目属性->C/C++ -> 预处理器 -> 预处理器定义中加入宏DLL_EXPORTS
		 方法2：stdafx.h中#define DLL_EXPORTS
	使用动态库的项目中执行导入动态库的分支，使用__declspec(dllimport)
*/
#ifdef DLL_EXPORTS
#define DLL_API __declspec(dllexport) 
#else
#define DLL_API __declspec(dllimport)
#endif
 

// 导出函数：
DLL_API int funci();
DLL_API void dllDisp(void);

// 导出重载函数：
DLL_API int addNum(const int, const int);
DLL_API int addNum(const int, const int, const int);

// 导出函数模板——不能直接导出，只能导出特例化之后的模板函数：
template <typename T> void dispArg(const T arg);
template DLL_API void dispArg<int>(const int);
template DLL_API void dispArg<double>(const double);
template DLL_API void dispArg<char const *>(const char const *);
 

namespace MYDLL
{
	// 1. DLL中定义函数
	extern "C" 
	{
		DLL_API void disp(void);
		DLL_API void printCurrentPath(void);
	}
	

	// 2. DLL中自定义类
	class DLL_API calculator				// __declspec(dllexport) 要放在class后面，不是最前
	{
	public:

		double Add(double a, double b);

		double Subtract(double a, double b);

		double Multiply(double a, double b);

		double Divide(double a, double b);

	};

}

 