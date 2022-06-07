#include <iostream>
#include <string>
#include "staticLib1.h"
#include "dynamicLib1.h"


#include <windows.h>
#include <atlstr.h>		// 包含CString类。属于microsoft ATL(活动模板库avtive template library)




using namespace std;

typedef void (__cdecl *pfun)(void);
typedef int(__stdcall *f_funci)();



// 调用静态库、动态库
namespace TEST_LIBS
{
	// 调用静态库
	/*
	调用静态库配置：
	1. #include静态库头文件。
	2. 下面的操作二选一
	2.1 使用#pragma comment()宏函数加载.lib文件。
	2.2 项目属性->链接器->附加依赖项中加入希望调用的.lib文件;
	VC++包含目录添加静态库头文件所在路径(或者手动在项目头文件目录下添加所需头文件)；
	VC++库目录添加.lib文件所在目录。


	*/

#pragma comment(lib,"staticLib1.lib")			// 如果项目属性->链接器->附加依赖项之中加入了.lib文件，则不需要该预处理命令 

	void test1_1()
	{
		add(1, 2);

	}


	// test1_2 调用动态库

	/*
		有两种方式调用动态库——静态调用、动态调用
		静态(隐式)调用
		需要DLL文件，LIB文件，头文件。
		使用#pragma comment()宏函数加载作为导入库文件的.lib文件。
		动态(显式)调用
		只需要DLL文件和头文件，不需要LIB文件
		通过调用windowsAPI来加载和卸载DLL
		LoadLibrary()
	*/
#pragma comment(lib,"dynamicLib1.lib")	// 如果在项目属性->链接器->附加依赖项之中加入.lib文件，则不需要该预处理命令。
	void test1_2()
	{
		MYDLL::disp();
		MYDLL::printCurrentPath();
		MYDLL::calculator calc;
		cout << "calc.Add(1,2) == " << calc.Add(1, 2) << endl;

	}



	// 使用WINDOWS系统的HMODULE来调用动态库——目前有错误，动态库句柄可以取到值，但是函数指针无法从动态库句柄中取函数地址。
	void test1_3()
	{
		HMODULE Hdll = nullptr;
		using pDDD = double(*)(double, double);
		using pVV = void(*)(void);
		using pIV = int(*)(void);
		pDDD pfuncD = nullptr;
		pIV pfuncI = nullptr;
		pVV pfuncV = nullptr;

		Hdll = LoadLibrary(L"../Release/dynamicLib1.dll");

		if (nullptr == Hdll)
		{
			cout << "加载动态库失败" << endl;
		}
		else
		{
			pfuncV = (pVV)(GetProcAddress(Hdll, "dllDisp"));
			(*pfuncV)();
		}

		FreeLibrary(Hdll);

		if (Hdll == nullptr)
		{
			cout << "DLL释放成功" << endl;
		}

		Hdll = LoadLibrary(L"../Release/dynamicLib1.dll");

		if (nullptr == Hdll)
		{
			cout << "加载动态库失败" << endl;
		}
		else
		{
			pfuncV = (pVV)(GetProcAddress(Hdll, "dllDisp"));
			(*pfuncV)();
		}

	}


}


// 读写配置文件config.ini
namespace CONFIG
{
	// 读取当前程序路径，生成config.ini文件并写入内容
	void test0()
	{
		CString   sPath;

		// 获取当前进程加载的模块的路径。
		std::cout << "当前sPath的长度是：" << sPath.GetLength() << std::endl;
		GetModuleFileName(NULL, sPath.GetBufferSetLength(MAX_PATH + 1), MAX_PATH);
		std::cout << "当前sPath的长度是：" << sPath.GetLength() << std::endl;

		// 更新CString对象的长度。
		sPath.ReleaseBuffer();
		std::cout << "当前sPath的长度是：" << sPath.GetLength() << std::endl;

		// 设置wcout的语言环境，缺少这一步打印中文会有错误。
		std::wcout.imbue(std::locale(std::locale(), "", LC_CTYPE));
		wcout << (LPCTSTR)sPath << endl;		// 控制台上打印宽字符

												// 截取sPath倒数第二个'\\'及之前的内容
		int   nPos;
		nPos = sPath.ReverseFind('\\');
		sPath = sPath.Left(nPos);
		nPos = sPath.ReverseFind('\\');
		sPath = sPath.Left(nPos);
		std::wcout << (LPCTSTR)sPath << std::endl;
		std::cout << "typeid(sPath).name() == " << typeid(sPath).name() << std::endl;
		std::cout << "typeid((LPCTSTR)sPath).name() == " << typeid((LPCTSTR)sPath).name() << std::endl;

		// 生成配置文件路径
		CString  configPath = sPath + "\\outerConfig.ini";
		wcout << (LPCTSTR)configPath << endl;

		// 生成配置文件、写入内容；

		/*
		BOOL WritePrivateProfileString(
		LPCTSTR lpAppName,			INI文件中的一个节名。键值对在某一个节名之下，一个INI文件可以有多个节名；
		LPCTSTR lpKeyName,			键名
		LPCTSTR lpString,			键值,也就是变量的值,不过必须为LPCTSTR型或CString型的.
		LPCTSTR lpFileName			INI文件路径，相对路径绝对路径都可以。
		);
		*/
		configPath = ".\\innerConfig.ini";
		WritePrivateProfileString(CString("physical attribute"), CString("height"), CString("170.0"), configPath);
		WritePrivateProfileString(CString("physical attribute"), CString("age"), CString("18"), configPath);
		WritePrivateProfileString(CString("character"), CString("hobby"), CString("video games"), configPath);
		WritePrivateProfileString(CString("character"), CString("idol"), CString("Ariana"), configPath);

		// 宏MAX_PATH——微软系统最长路径的字节数(260)
		std::cout << "MAX_PATH == " << MAX_PATH << std::endl;

	}


	// 读取INI文件的键值
	void test1()
	{
		CString configPath = ".\\innerConfig.ini";

		WCHAR* str = new WCHAR[MAX_PATH];
		int retNum1, retNum2;

		// 设置wcout的语言环境，缺少这一步打印中文会有错误。
		wcout.imbue(locale(locale(), "", LC_CTYPE));



		// 1. 读字符串

		/*
		GetPrivateProfileString(
					LPCTSTR lpAppName,			// 节名
					LPCTSTR lpKeyName,			// key名
					LPCTSTR lpDefault,			// 如果INI文件中没有前两个参数指定的节名或key名,则将此值赋给变量.
					LPTSTR lpReturnedString,	// 存储返回的字符串的缓存器
					DWORD nSize,				// 上面的缓存器的大小。
					LPCTSTR lpFileName			// INI文件路径，相对路径绝对路径都可以。
					);
		*/
		GetPrivateProfileString(CString("character"), CString("hobby"), CString(""), str, 256, configPath);
		std::wcout << (LPCTSTR)str << std::endl;	// LP-指针，C-const，TSTR-TCHAR字符构成的字符串。

		GetPrivateProfileString(CString("character"), CString("idol"), CString(""), str, 256, configPath);
		std::wcout << (LPCTSTR)str << std::endl;


		// 2. 读整形数

		/*
			UINT WINAPI GetPrivateProfileInt(
						_In_LPCTSTR lpAppName,					节名
						_In_LPCTSTR lpKeyName,					键名
						_In_INT nDefault,                 若没有取得键值，返回此值
						_In_LPCTSTR lpFileName				INI文件路径
						);
		*/

		std::cout << "age == " << \
			GetPrivateProfileInt(CString("physical attribute"), CString("age"), -1, configPath) << std::endl;


		// 3. 读浮点数
		GetPrivateProfileString(CString("physical attribute"), CString("height"), CString(""), str, 256, configPath);
		std::cout << typeid(str).name() << std::endl;
		std::wcout << str << std::endl;

		//		3.1 宽字符串转换为普通字符串
		const int iSize = WideCharToMultiByte(CP_ACP, 0, str, -1, NULL, 0, NULL, NULL); //iSize =wcslen(pwsUnicode)+1=6
		char* newStr = new char(iSize * sizeof(char));
		WideCharToMultiByte(CP_ACP, 0, str, -1, newStr, iSize, NULL, NULL);		
		std::cout << newStr << std::endl;
	

		//		3.2 字符串转换为float
		float height = std::atof(newStr);
		std::cout << "height == " << height << std::endl;

		//		3.3 宽字符串转换为float
		height = _wtof(str);
		std::cout << "height == " << height << std::endl;

		delete newStr;
	}


}


// windows多线程
namespace MULTITHREAD
{
	HANDLE hMutex = NULL;//互斥量

	DWORD WINAPI Fun(LPVOID lpParamter)
	{
		for (int i = 0; i < 10; i++)
		{
			//请求一个互斥量锁
			WaitForSingleObject(hMutex, INFINITE);
			cout << "A Thread Fun Display!" << endl;
			Sleep(100);
			//释放互斥量锁
			ReleaseMutex(hMutex);
		}
		return 0L;//表示返回的是long型的0

	}

	void test1()
	{
		HANDLE hThread = CreateThread(NULL, 0, Fun, NULL, 0, NULL);
		hMutex = CreateMutex(NULL, FALSE, L"screen");

		//关闭线程句柄
		if (hThread != nullptr) 
		{
			CloseHandle(hThread);
		}
	
		//主线程的执行路径
		for (int i = 0; i < 10; i++)
		{
			//请求获得一个互斥量锁
			if (hMutex != nullptr) 
			{
				WaitForSingleObject(hMutex, INFINITE);
			}
			
			cout << "Main Thread Display!" << endl;
			Sleep(100);

			//释放互斥量锁
			if (hMutex != nullptr)
			{
				ReleaseMutex(hMutex);
			}
		}
	}
}


// 暂时无法分类
namespace GENERAL_VCPP 
{

	// 查看环境信息
	void test0() 
	{
		std::cout << _MSC_VER << std::endl;		// 1900，对应MSVC++版本14.0

	}
}



int main()
{
	CONFIG::test0();

    return 0;
}

