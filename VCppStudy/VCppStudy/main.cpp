#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <random>
#include <functional>
#include <algorithm>
#include <numeric>
#include <thread>

#include "staticLib1.h"
#include "dynamicLib1.h"

#include <windows.h>
#include <atlstr.h>		// ����CString�ࡣ����microsoft ATL(�ģ���avtive template library)
#include <io.h>
 

typedef void (__cdecl *pfun)(void);
typedef int(__stdcall *f_funci)();


// �Զ����ʱ����ʹ��WINDOWS��ʱAPI
class tiktok
{
private:
	tiktok() = default;
	tiktok(const tiktok&) {}
	~tiktok() = default;

public:
	DWORD startTik;
	DWORD endTik;
	unsigned recordCount;
	std::vector<DWORD> records;

	static tiktok& getInstance()
	{
		static tiktok tt_instance;
		return tt_instance;
	}

	void start()
	{
		this->startTik = GetTickCount();
		this->recordCount = 0;
		this->records.clear();
	}

	void endCout(const char* str)
	{
		this->endTik = GetTickCount();
		std::cout << str << endTik - startTik << std::endl;
	}

	bool endWrite(const char* fileName, const char* str)
	{
		this->endTik = GetTickCount();
		std::ofstream file(fileName, std::ios_base::out | std::ios_base::app);
		if (!file)
			return false;

		file << str << endTik - startTik << std::endl;
		file.close();
		return true;
	}

	void takeArecord()
	{
		this->records.push_back(GetTickCount());
		recordCount++;
	}
};



// TEST�������þ�̬�⡢��̬��
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
		std::cout << "calc.Add(1,2) == " << calc.Add(1, 2) << std::endl;

		std::cout << addNum(3, 4) << std::endl;
		std::cout << addNum(3, 4, 5) << std::endl;

		dispArg(3.1415);
		dispArg(333);
		dispArg("hahaha");

		std::cout << "finished." << std::endl;
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
			std::cout << "���ض�̬��ʧ��" << std::endl;
		else
		{
			pfuncV = (pVV)(GetProcAddress(Hdll, "dllDisp"));
			(*pfuncV)();
		}

		FreeLibrary(Hdll);

		if (Hdll == nullptr)
			std::cout << "DLL�ͷųɹ�" << std::endl;

		Hdll = LoadLibrary(L"../Release/dynamicLib1.dll");

		if (nullptr == Hdll)
			std::cout << "���ض�̬��ʧ��" << std::endl;
		else
		{
			pfuncV = (pVV)(GetProcAddress(Hdll, "dllDisp"));
			(*pfuncV)();
		}

	}

}



// ���Գ��õ�windows api
namespace TEST_WINAPI
{
	// ��ȡĳ��Ŀ¼�������ļ�����Ŀ¼����
	void getFileNames(std::string path, std::vector<std::string>& files, bool blRecur = true)
	{
		std::string str;
		struct _finddata_t fileinfo;			// �ļ���Ϣ
		intptr_t hFile = _findfirst(str.assign(path).append("/*").c_str(), &fileinfo);							// �ļ����	
		bool blFileValid = (hFile != -1);

		if (blFileValid)			
		{
			do
			{
				bool isSubDir = (fileinfo.attrib & _A_SUBDIR);
				//�����Ŀ¼,�ݹ���ң��������,���ļ�����·������vector��
				if (isSubDir & blRecur)
				{
					if (strcmp(fileinfo.name, ".") != 0 && strcmp(fileinfo.name, "..") != 0)
						getFileNames(str.assign(path).append("/").append(fileinfo.name), files);
				}
				else
					if (strcmp(fileinfo.name, ".") != 0 && strcmp(fileinfo.name, "..") != 0)
						files.push_back(str.assign(path).append("/").append(fileinfo.name));
			} while (_findnext(hFile, &fileinfo) == 0);
			_findclose(hFile);
		}
	}


	// ��ȡ��ǰ����·�������������ļ�config.ini��д������
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
		std::wcout << (LPCTSTR)sPath << std::endl;		// ����̨�ϴ�ӡ���ַ�

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
		std::wcout << (LPCTSTR)configPath << std::endl;

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
		std::wcout.imbue(std::locale(std::locale(), "", LC_CTYPE));

		// 1. ���ַ���
		/*
		GetPrivateProfileString(
					LPCTSTR lpAppName,				// ����
					LPCTSTR lpKeyName,				// key��
					LPCTSTR lpDefault,					// ���INI�ļ���û��ǰ��������ָ���Ľ�����key��,�򽫴�ֵ��������.
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
		const int iSize = WideCharToMultiByte(CP_ACP, 0, str, -1, NULL, 0, NULL, NULL);		//iSize =wcslen(pwsUnicode)+1=6
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
 

	// ����getFileNames()
	void test2() 
	{
		std::vector<std::string> fileNames, fileNamesRecur;
		std::string path("E:/��Ǽ�֧��");  

		//getFileNames(path, fileNames, false);
		//std::cout << "�ǵݹ�����ļ�����" << std::endl;
		//for (const auto& ph : fileNames)
		//	std::cout << ph << std::endl;
		//std::cout << std::endl << std::endl;

		getFileNames(path, fileNamesRecur, true);
		std::cout << "�ݹ�����ļ�����" << std::endl;
		for (const auto& ph : fileNamesRecur)
			std::cout << ph << std::endl;

		std::cout << "finished." << std::endl;
	}


	// CString, ����ͨ�ַ����ַ�����ת����
	void test3() 
	{
		/*
		CStringT
			ʵ��������һ�������ɱ䳤���ַ�����ģ���ࡣ
			CStringTģ����������ʵ����CString��CStringA��CStringW�����Ƿֱ��ṩ��TCHAR��char��wchar_t�ַ����͵��ַ����Ĳ�����
				char���Ͷ������Ansi�ַ�
				wchar_t���Ͷ������Unicode�ַ���
			
			��TCHARȡ����MFC���̵����ԶԻ����е�Configuration Properties->General->Character Set���ԣ�
					���������ΪUse Multi-Byte Character Set����TCHAR���Ͷ������Ansi�ַ���
					�����ΪUse Unicode Character Set����TCHAR���Ͷ������Unicode�ַ���
 
		
		*/
		CString   sPath;
		CString cstr{"���"};

		////			ע��WIN10��TXT�ļ�Ĭ�ϵ��ַ�������UTF-8����Ҫת����ANSI��UNICODE���룻
		//std::wcout.imbue(std::locale(std::locale(), "", LC_CTYPE));			// ����wcout�����Ի�����ȱ����һ����ӡ���Ļ��д���
		//std::wstring wDatFileName = STR_UTF8ToUnicode(tempStr);
		//std::string datFileName = STR_UnicodeToANSI(wDatFileName);
		//std::string datFilePath = g_debugPath + datFileName;
		//std::cout << datFilePath << std::endl;

		// ��ȡ��ǰ���̼��ص�ģ���·����
		std::cout << "��ǰsPath�ĳ����ǣ�" << sPath.GetLength() << std::endl;
		GetModuleFileName(NULL, sPath.GetBufferSetLength(MAX_PATH + 1), MAX_PATH);
		std::cout << "��ǰsPath�ĳ����ǣ�" << sPath.GetLength() << std::endl;

		// CT2A()����CStringת��Ϊansi�����std::string;
		std::string str1 = CT2A(sPath);
		std::string str2 = CT2A(cstr);
		



		std::cout << "finished." << std::endl;
	}
}



// windows���߳�
namespace MULTITHREAD
{
	HANDLE hMutex = NULL;		//������

	DWORD WINAPI Fun(LPVOID lpParamter)
	{
		for (int i = 0; i < 10; i++)
		{
			//����һ����������
			WaitForSingleObject(hMutex, INFINITE);
			std::cout << "A Thread Fun Display!" << std::endl;
			Sleep(100);

			//�ͷŻ�������
			ReleaseMutex(hMutex);
		}
		return 0L;			//��ʾ���ص���long�͵�0

	}

	void test1()
	{
		HANDLE hThread = CreateThread(NULL, 0, Fun, NULL, 0, NULL);
		hMutex = CreateMutex(NULL, FALSE, L"screen");

		//�ر��߳̾��
		if (hThread != nullptr) 
			CloseHandle(hThread);
	
		//���̵߳�ִ��·��
		for (int i = 0; i < 10; i++)
		{
			//������һ����������
			if (hMutex != nullptr) 
				WaitForSingleObject(hMutex, INFINITE);
			
			std::cout << "Main Thread Display!" << std::endl;
			Sleep(100);

			//�ͷŻ�������
			if (hMutex != nullptr)
				ReleaseMutex(hMutex);
		}
	}


	void test2() 
	{
		// ����һ��������������������������
		std::vector<float> numVec(10000, 0);
		std::vector<float> randVec(10000);
		numVec[0] = 0.1;
		unsigned elemCount = numVec.size();
		std::default_random_engine e;								// ��������������������
		std::uniform_real_distribution<float> URD_f(0, 1);
		tiktok& tt = tiktok::getInstance();

# if 1
		// ���̺߳�ʱΪ9s+
		std::cout << "��ʼ��" << std::endl;
		tt.start();
		for (unsigned i = 0; i < elemCount; ++i)		// ����һ�����������ͣ���ֵ��numVec�е�Ԫ�أ�
		{
			for (auto& num : randVec)
				num = URD_f(e);
			numVec[i] = std::sqrt(std::accumulate(randVec.begin(), randVec.end(), 0));
		}
		tt.endCout("���̺߳�ʱ��");
#endif 

		// ���̲߳��У�
		const static unsigned n_threads = std::thread::hardware_concurrency();
		std::cout << "�߳�����" << n_threads << std::endl;
		if (0u == n_threads)
			return;

		unsigned slice = std::round(elemCount / n_threads);
		slice = std::max(slice, 1u);
		std::vector<std::thread> threadPool;
		threadPool.reserve(n_threads);

		// �̺߳�����
		auto func = [&](unsigned start, unsigned end)
		{
			std::vector<float> tmpRands(10000);
			for (unsigned i = start; i < end; ++i)		// ����һ�����������ͣ���ֵ��numVec�е�Ԫ�أ�
			{
				for (auto& num : tmpRands)
					num = URD_f(e);
				numVec[i] = std::sqrt(std::accumulate(tmpRands.begin(), tmpRands.end(), 0));
			}
		};

		// ����thread����
		unsigned start = 0;
		unsigned end = 0;
		for (unsigned i = 0; end + slice - 1 <= elemCount; ++i)
		{
			start = i * slice;
			end = start + slice;
			threadPool.emplace_back(func, start ,end);
		}
		if (end < elemCount)
			threadPool.emplace_back(func, end, elemCount);

		tt.start();
		for (auto& t : threadPool)
		{
			if (t.joinable())
				t.join();
		}
		tt.endCout("���̺߳�ʱ��");

		std::cout << "finished." << std::endl;
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
	// TEST_LIBS::test1_2();
	
	TEST_WINAPI::test3();

	// MULTITHREAD::test2();

    return 0;
}

