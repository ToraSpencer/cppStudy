#include <iostream>
#include <string>
#include "staticLib1.h"
#include "dynamicLib1.h"


#include <windows.h>
#include <atlstr.h>		// ����CString�ࡣ����microsoft ATL(�ģ���avtive template library)




using namespace std;

typedef void (__cdecl *pfun)(void);
typedef int(__stdcall *f_funci)();



// ���þ�̬�⡢��̬��
namespace TEST_LIBS
{

	// ���þ�̬��
	/*
	���þ�̬�����ã�
	1. #include��̬��ͷ�ļ���
	2. ����Ĳ�����ѡһ
	2.1 ʹ��#pragma comment()�꺯������.lib�ļ���
	2.2 ��Ŀ����->������->�����������м���ϣ�����õ�.lib�ļ�;
	VC++����Ŀ¼��Ӿ�̬��ͷ�ļ�����·��(�����ֶ�����Ŀͷ�ļ�Ŀ¼���������ͷ�ļ�)��
	VC++��Ŀ¼���.lib�ļ�����Ŀ¼��


	*/

#pragma comment(lib,"staticLib1.lib")			// �����Ŀ����->������->����������֮�м�����.lib�ļ�������Ҫ��Ԥ�������� 

	void test1_1()
	{
		add(1, 2);

	}


	// test1_2 ���ö�̬��

	/*
		�����ַ�ʽ���ö�̬�⡪����̬���á���̬����
		��̬(��ʽ)����
		��ҪDLL�ļ���LIB�ļ���ͷ�ļ���
		ʹ��#pragma comment()�꺯��������Ϊ������ļ���.lib�ļ���
		��̬(��ʽ)����
		ֻ��ҪDLL�ļ���ͷ�ļ�������ҪLIB�ļ�
		ͨ������windowsAPI�����غ�ж��DLL
		LoadLibrary()
	*/
#pragma comment(lib,"dynamicLib1.lib")	// �������Ŀ����->������->����������֮�м���.lib�ļ�������Ҫ��Ԥ�������
	void test1_2()
	{
		MYDLL::disp();
		MYDLL::printCurrentPath();
		MYDLL::calculator calc;
		cout << "calc.Add(1,2) == " << calc.Add(1, 2) << endl;

	}



	// ʹ��WINDOWSϵͳ��HMODULE�����ö�̬�⡪��Ŀǰ�д��󣬶�̬��������ȡ��ֵ�����Ǻ���ָ���޷��Ӷ�̬������ȡ������ַ��
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
			cout << "���ض�̬��ʧ��" << endl;
		}
		else
		{
			pfuncV = (pVV)(GetProcAddress(Hdll, "dllDisp"));
			(*pfuncV)();
		}

		FreeLibrary(Hdll);

		if (Hdll == nullptr)
		{
			cout << "DLL�ͷųɹ�" << endl;
		}

		Hdll = LoadLibrary(L"../Release/dynamicLib1.dll");

		if (nullptr == Hdll)
		{
			cout << "���ض�̬��ʧ��" << endl;
		}
		else
		{
			pfuncV = (pVV)(GetProcAddress(Hdll, "dllDisp"));
			(*pfuncV)();
		}

	}


}



// ��д�����ļ�config.ini
namespace CONFIG
{
	// ��ȡ��ǰ����·��������config.ini�ļ���д������
	void test0()
	{
		CString   sPath;

		// ��ȡ��ǰ���̼��ص�ģ���·����
		std::cout << "��ǰsPath�ĳ����ǣ�" << sPath.GetLength() << std::endl;
		GetModuleFileName(NULL, sPath.GetBufferSetLength(MAX_PATH + 1), MAX_PATH);
		std::cout << "��ǰsPath�ĳ����ǣ�" << sPath.GetLength() << std::endl;

		// ����CString����ĳ��ȡ�
		sPath.ReleaseBuffer();
		std::cout << "��ǰsPath�ĳ����ǣ�" << sPath.GetLength() << std::endl;


		// ����wcout�����Ի�����ȱ����һ����ӡ���Ļ��д���
		std::wcout.imbue(std::locale(std::locale(), "", LC_CTYPE));
		wcout << (LPCTSTR)sPath << endl;		// ����̨�ϴ�ӡ���ַ�

												// ��ȡsPath�����ڶ���'\\'��֮ǰ������
		int   nPos;
		nPos = sPath.ReverseFind('\\');
		sPath = sPath.Left(nPos);
		nPos = sPath.ReverseFind('\\');
		sPath = sPath.Left(nPos);
		std::wcout << (LPCTSTR)sPath << std::endl;
		std::cout << "typeid(sPath).name() == " << typeid(sPath).name() << std::endl;
		std::cout << "typeid((LPCTSTR)sPath).name() == " << typeid((LPCTSTR)sPath).name() << std::endl;

		// ���������ļ�·��
		CString  configPath = sPath + "\\outerConfig.ini";
		wcout << (LPCTSTR)configPath << endl;

		// ���������ļ���д�����ݣ�

		/*
		BOOL WritePrivateProfileString(
		LPCTSTR lpAppName,			INI�ļ��е�һ����������ֵ����ĳһ������֮�£�һ��INI�ļ������ж��������
		LPCTSTR lpKeyName,			����
		LPCTSTR lpString,			��ֵ,Ҳ���Ǳ�����ֵ,��������ΪLPCTSTR�ͻ�CString�͵�.
		LPCTSTR lpFileName			INI�ļ�·�������·������·�������ԡ�
		);
		*/
		configPath = ".\\innerConfig.ini";
		WritePrivateProfileString(CString("physical attribute"), CString("height"), CString("170.0"), configPath);
		WritePrivateProfileString(CString("physical attribute"), CString("age"), CString("18"), configPath);
		WritePrivateProfileString(CString("character"), CString("hobby"), CString("video games"), configPath);
		WritePrivateProfileString(CString("character"), CString("idol"), CString("Ariana"), configPath);

		// ��MAX_PATH����΢��ϵͳ�·�����ֽ���(260)
		std::cout << "MAX_PATH == " << MAX_PATH << std::endl;



	}


	// ��ȡINI�ļ��ļ�ֵ
	void test1()
	{
		CString configPath = ".\\innerConfig.ini";

		WCHAR* str = new WCHAR[MAX_PATH];
		int retNum1, retNum2;

		// ����wcout�����Ի�����ȱ����һ����ӡ���Ļ��д���
		wcout.imbue(locale(locale(), "", LC_CTYPE));



		// 1. ���ַ���

		/*
		GetPrivateProfileString(
					LPCTSTR lpAppName,			// ����
					LPCTSTR lpKeyName,			// key��
					LPCTSTR lpDefault,			// ���INI�ļ���û��ǰ��������ָ���Ľ�����key��,�򽫴�ֵ��������.
					LPTSTR lpReturnedString,	// �洢���ص��ַ����Ļ�����
					DWORD nSize,				// ����Ļ������Ĵ�С��
					LPCTSTR lpFileName			// INI�ļ�·�������·������·�������ԡ�
					);
		*/
		GetPrivateProfileString(CString("character"), CString("hobby"), CString(""), str, 256, configPath);
		std::wcout << (LPCTSTR)str << std::endl;	// LP-ָ�룬C-const��TSTR-TCHAR�ַ����ɵ��ַ�����

		GetPrivateProfileString(CString("character"), CString("idol"), CString(""), str, 256, configPath);
		std::wcout << (LPCTSTR)str << std::endl;


		// 2. ��������

		/*
			UINT WINAPI GetPrivateProfileInt(
						_In_LPCTSTR lpAppName,					����
						_In_LPCTSTR lpKeyName,					����
						_In_INT nDefault,                 ��û��ȡ�ü�ֵ�����ش�ֵ
						_In_LPCTSTR lpFileName				INI�ļ�·��
						);
		*/

		std::cout << "age == " << \
			GetPrivateProfileInt(CString("physical attribute"), CString("age"), -1, configPath) << std::endl;


		// 3. ��������
		GetPrivateProfileString(CString("physical attribute"), CString("height"), CString(""), str, 256, configPath);
		std::cout << typeid(str).name() << std::endl;
		std::wcout << str << std::endl;

		//		3.1 ���ַ���ת��Ϊ��ͨ�ַ���
		const int iSize = WideCharToMultiByte(CP_ACP, 0, str, -1, NULL, 0, NULL, NULL); //iSize =wcslen(pwsUnicode)+1=6
		char* newStr = new char(iSize * sizeof(char));
		WideCharToMultiByte(CP_ACP, 0, str, -1, newStr, iSize, NULL, NULL);		
		std::cout << newStr << std::endl;
	

		//		3.2 �ַ���ת��Ϊfloat
		float height = std::atof(newStr);
		std::cout << "height == " << height << std::endl;

		//		3.3 ���ַ���ת��Ϊfloat
		height = _wtof(str);
		std::cout << "height == " << height << std::endl;

		delete newStr;
	}


}




// windows���߳�
namespace MULTITHREAD
{
	HANDLE hMutex = NULL;//������

	DWORD WINAPI Fun(LPVOID lpParamter)
	{
		for (int i = 0; i < 10; i++)
		{
			//����һ����������
			WaitForSingleObject(hMutex, INFINITE);
			cout << "A Thread Fun Display!" << endl;
			Sleep(100);
			//�ͷŻ�������
			ReleaseMutex(hMutex);
		}
		return 0L;//��ʾ���ص���long�͵�0

	}

	void test1()
	{
		HANDLE hThread = CreateThread(NULL, 0, Fun, NULL, 0, NULL);
		hMutex = CreateMutex(NULL, FALSE, L"screen");

		//�ر��߳̾��
		if (hThread != nullptr) 
		{
			CloseHandle(hThread);
		}
	
		//���̵߳�ִ��·��
		for (int i = 0; i < 10; i++)
		{
			//������һ����������
			if (hMutex != nullptr) 
			{
				WaitForSingleObject(hMutex, INFINITE);
			}
			
			cout << "Main Thread Display!" << endl;
			Sleep(100);

			//�ͷŻ�������
			if (hMutex != nullptr)
			{
				ReleaseMutex(hMutex);
			}
		}
	}
}


// ��ʱ�޷�����
namespace GENERAL_VCPP 
{

	// �鿴������Ϣ
	void test0() 
	{
		std::cout << _MSC_VER << std::endl;		// 1900����ӦMSVC++�汾14.0

	}
}



int main()
{
	MULTITHREAD::test1();

    return 0;
}

