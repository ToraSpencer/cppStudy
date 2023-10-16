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

// �ڴ��CPU���ӽӿ���Ҫ��һЩͷ�ļ���
#ifdef WIN32 
#include <psapi.h>   
#include <direct.h>
#include <process.h>
#else
#include <sys/stat.h>
#include <sys/sysinfo.h>
#include <sys/time.h>
#include <unistd.h>
#endif
 

typedef void (__cdecl *pfun)(void);
typedef int(__stdcall *f_funci)();



////////////////////////////////////////////////////////////////////////////////////////////// DEBUG �ӿ�
namespace MY_DEBUG 
{
	static void debugDisp()			// �ݹ���ֹ
	{						//		�ݹ���ֹ��Ϊ�޲λ���һ�����������ζ����ԡ�
		std::cout << std::endl;
		return;
	}


	template <typename T, typename... Types>
	static void debugDisp(const T& firstArg, const Types&... args)
	{
		std::cout << firstArg << " ";
		debugDisp(args...);
	}


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
}
using namespace MY_DEBUG;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// WINDOWS API:
namespace MY_WIN_API
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


	// get current process pid
	inline int GetCurrentPid()
	{
		return _getpid();
	}

	// get specific process cpu occupation ratio by pid
#ifdef WIN32
// 
	static uint64_t convert_time_format(const FILETIME* ftime)
	{
		LARGE_INTEGER li;

		li.LowPart = ftime->dwLowDateTime;
		li.HighPart = ftime->dwHighDateTime;
		return li.QuadPart;
	}
#else
// FIXME: can also get cpu and mem status from popen cmd
// the info line num in /proc/{pid}/status file
#define VMRSS_LINE 22
#define PROCESS_ITEM 14

	static const char* get_items(const char* buffer, unsigned int item)
	{
		// read from buffer by offset
		const char* p = buffer;

		int len = strlen(buffer);
		int count = 0;

		for (int i = 0; i < len; i++)
		{
			if (' ' == *p)
			{
				count++;
				if (count == item - 1)
				{
					p++;
					break;
				}
			}
			p++;
		}

		return p;
	}

	static inline unsigned long get_cpu_total_occupy()
	{
		// get total cpu use time

		// different mode cpu occupy time
		unsigned long user_time;
		unsigned long nice_time;
		unsigned long system_time;
		unsigned long idle_time;

		FILE* fd;
		char buff[1024] = { 0 };

		fd = fopen("/proc/stat", "r");
		if (nullptr == fd)
			return 0;

		fgets(buff, sizeof(buff), fd);
		char name[64] = { 0 };
		sscanf(buff, "%s %ld %ld %ld %ld", name, &user_time, &nice_time, &system_time, &idle_time);
		fclose(fd);

		return (user_time + nice_time + system_time + idle_time);
	}

	static inline unsigned long get_cpu_proc_occupy(int pid)
	{
		// get specific pid cpu use time
		unsigned int tmp_pid;
		unsigned long utime;  // user time
		unsigned long stime;  // kernel time
		unsigned long cutime; // all user time
		unsigned long cstime; // all dead time

		char file_name[64] = { 0 };
		FILE* fd;
		char line_buff[1024] = { 0 };
		sprintf(file_name, "/proc/%d/stat", pid);

		fd = fopen(file_name, "r");
		if (nullptr == fd)
			return 0;

		fgets(line_buff, sizeof(line_buff), fd);

		sscanf(line_buff, "%u", &tmp_pid);
		const char* q = get_items(line_buff, PROCESS_ITEM);
		sscanf(q, "%ld %ld %ld %ld", &utime, &stime, &cutime, &cstime);
		fclose(fd);

		return (utime + stime + cutime + cstime);
	}
#endif

	inline float GetCpuUsageRatio(int pid)
	{
#ifdef WIN32
		static int64_t last_time = 0;
		static int64_t last_system_time = 0;

		FILETIME now;
		FILETIME creation_time;
		FILETIME exit_time;
		FILETIME kernel_time;
		FILETIME user_time;
		int64_t system_time;
		int64_t time;
		int64_t system_time_delta;
		int64_t time_delta;

		// get cpu num
		SYSTEM_INFO info;
		GetSystemInfo(&info);
		int cpu_num = info.dwNumberOfProcessors;

		float cpu_ratio = 0.0;

		// get process hanlde by pid
		HANDLE process = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pid);
		// use GetCurrentProcess() can get current process and no need to close handle

		// get now time
		GetSystemTimeAsFileTime(&now);

		if (!GetProcessTimes(process, &creation_time, &exit_time, &kernel_time, &user_time))
		{
			// We don't assert here because in some cases (such as in the Task Manager)  
			// we may call this function on a process that has just exited but we have  
			// not yet received the notification.  
			printf("GetCpuUsageRatio GetProcessTimes failed\n");
			return 0.0;
		}

		// should handle the multiple cpu num
		system_time = (convert_time_format(&kernel_time) + convert_time_format(&user_time)) / cpu_num;
		time = convert_time_format(&now);

		if ((last_system_time == 0) || (last_time == 0))
		{
			// First call, just set the last values.  
			last_system_time = system_time;
			last_time = time;
			return 0.0;
		}

		system_time_delta = system_time - last_system_time;
		time_delta = time - last_time;

		CloseHandle(process);

		if (time_delta == 0)
		{
			printf("GetCpuUsageRatio time_delta is 0, error\n");
			return 0.0;
		}

		// We add time_delta / 2 so the result is rounded.  
		cpu_ratio = (int)((system_time_delta * 100 + time_delta / 2) / time_delta); // the % unit
		last_system_time = system_time;
		last_time = time;

		cpu_ratio /= 100.0; // convert to float number

		return cpu_ratio;
#else
		unsigned long totalcputime1, totalcputime2;
		unsigned long procputime1, procputime2;

		totalcputime1 = get_cpu_total_occupy();
		procputime1 = get_cpu_proc_occupy(pid);

		// FIXME: the 200ms is a magic number, works well
		usleep(200000); // sleep 200ms to fetch two time point cpu usage snapshots sample for later calculation

		totalcputime2 = get_cpu_total_occupy();
		procputime2 = get_cpu_proc_occupy(pid);

		float pcpu = 0.0;
		if (0 != totalcputime2 - totalcputime1)
			pcpu = (procputime2 - procputime1) / float(totalcputime2 - totalcputime1); // float number

		int cpu_num = get_nprocs();
		pcpu *= cpu_num; // should multiply cpu num in multiple cpu machine

		return pcpu;
#endif
	}


	// get specific process physical memeory occupation size by pid (MB)
	inline float GetMemoryUsage(int pid)
	{
#ifdef WIN32
		uint64_t mem = 0, vmem = 0;
		PROCESS_MEMORY_COUNTERS pmc;

		// get process hanlde by pid
		HANDLE process = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pid);
		if (GetProcessMemoryInfo(process, &pmc, sizeof(pmc)))
		{
			mem = pmc.WorkingSetSize;
			vmem = pmc.PagefileUsage;
		}
		CloseHandle(process);

		// use GetCurrentProcess() can get current process and no need to close handle

		// convert mem from B to MB
		return mem / 1024.0 / 1024.0;

#else
		char file_name[64] = { 0 };
		FILE* fd;
		char line_buff[512] = { 0 };
		sprintf(file_name, "/proc/%d/status", pid);

		fd = fopen(file_name, "r");
		if (nullptr == fd)
			return 0;

		char name[64];
		int vmrss = 0;
		for (int i = 0; i < VMRSS_LINE - 1; i++)
			fgets(line_buff, sizeof(line_buff), fd);

		fgets(line_buff, sizeof(line_buff), fd);
		sscanf(line_buff, "%s %d", name, &vmrss);
		fclose(fd);

		// cnvert VmRSS from KB to MB
		return vmrss / 1024.0;
#endif
	}


}
using namespace MY_WIN_API;



////////////////////////////////////////////////////////////////////////////////////////////// ���Ժ�����

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
		int ret1 = add(1, 2);
		float ret2 = minus(1.2, 3.3);
#ifdef ERROR_EXAMPLE1
		float ret22 = minus(4, 1.5, 2.2);
#endif
		int ret3 = minus(10, 1, 2, 3);
		int ret4 = add(1,2,3);
		debugDisp("ret1 == ", ret1);
		debugDisp("ret2 == ", ret2); 
		debugDisp("ret3 == ", ret3);
		debugDisp("ret4 == ", ret4);

		timer<int> ti;
		timer<double> td;
		double ret5 = ti.doTimes(3, 5);
		double ret6 = td.doTimes(3, 5);
		double ret7 = td.doTimes(1.2, 4.8);
		int ret8 = divi(9, 4);

		debugDisp("ret5 == ", ret5);
		debugDisp("ret6 == ", ret6);
		debugDisp("ret7 == ", ret7);
		debugDisp("ret8 == ", ret8);
		debugDisp("ti.getCounter() == ", ti.getCounter());
		debugDisp("td.getCounter() == ", td.getCounter());


		debugDisp("finished.");
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
#pragma comment(lib,"dynamicLib1.lib")		// �������Ŀ����->������->����������֮�м���.lib�ļ�������Ҫ��Ԥ�������
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

		//// CT2A()����CStringת��Ϊansi�����std::string;
		//std::string str1 = CT2A(sPath);
		//std::string str2 = CT2A(cstr);
		
 
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

		// �ر��߳̾��
		if (hThread != nullptr) 
			CloseHandle(hThread);
	
		// ���̵߳�ִ��·��
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
	
	// TEST_WINAPI::test3();

	// MULTITHREAD::test2();

	int hours = 0;
	double weekly_pay = 0;
	double rate = 0;

	printf("������Ա����Сʱ���ʣ���");
	scanf("%lf", &rate);
	printf("������Ա���Ĺ���ʱ����Сʱ��: ");
	scanf("%d", &hours);
	weekly_pay = rate * 40 + 2 * rate * (hours - 40);
	printf("����Ӧ֧��нˮ�ǣ���%.lf", weekly_pay);

    return 0;
}

