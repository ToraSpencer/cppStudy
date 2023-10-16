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
#include <atlstr.h>		// 包含CString类。属于microsoft ATL(活动模板库avtive template library)
#include <io.h>

// 内存和CPU监视接口需要的一些头文件；
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



////////////////////////////////////////////////////////////////////////////////////////////// DEBUG 接口
namespace MY_DEBUG 
{
	static void debugDisp()			// 递归终止
	{						//		递归终止设为无参或者一个参数的情形都可以。
		std::cout << std::endl;
		return;
	}


	template <typename T, typename... Types>
	static void debugDisp(const T& firstArg, const Types&... args)
	{
		std::cout << firstArg << " ";
		debugDisp(args...);
	}


	// 自定义计时器，使用WINDOWS计时API
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

	// 读取某个目录下所有文件名、目录名；
	void getFileNames(std::string path, std::vector<std::string>& files, bool blRecur = true)
	{
		std::string str;
		struct _finddata_t fileinfo;			// 文件信息
		intptr_t hFile = _findfirst(str.assign(path).append("/*").c_str(), &fileinfo);							// 文件句柄	
		bool blFileValid = (hFile != -1);

		if (blFileValid)
		{
			do
			{
				bool isSubDir = (fileinfo.attrib & _A_SUBDIR);
				//如果是目录,递归查找；如果不是,把文件绝对路径存入vector中
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



////////////////////////////////////////////////////////////////////////////////////////////// 测试函数：

// TEST——调用静态库、动态库
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
#pragma comment(lib,"dynamicLib1.lib")		// 如果在项目属性->链接器->附加依赖项之中加入.lib文件，则不需要该预处理命令。
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
			std::cout << "加载动态库失败" << std::endl;
		else
		{
			pfuncV = (pVV)(GetProcAddress(Hdll, "dllDisp"));
			(*pfuncV)();
		}

		FreeLibrary(Hdll);

		if (Hdll == nullptr)
			std::cout << "DLL释放成功" << std::endl;

		Hdll = LoadLibrary(L"../Release/dynamicLib1.dll");

		if (nullptr == Hdll)
			std::cout << "加载动态库失败" << std::endl;
		else
		{
			pfuncV = (pVV)(GetProcAddress(Hdll, "dllDisp"));
			(*pfuncV)();
		}

	}

} 


// 测试常用的windows api
namespace TEST_WINAPI
{
	// 读取某个目录下所有文件名、目录名；
	void getFileNames(std::string path, std::vector<std::string>& files, bool blRecur = true)
	{
		std::string str;
		struct _finddata_t fileinfo;			// 文件信息
		intptr_t hFile = _findfirst(str.assign(path).append("/*").c_str(), &fileinfo);							// 文件句柄	
		bool blFileValid = (hFile != -1);

		if (blFileValid)			
		{
			do
			{
				bool isSubDir = (fileinfo.attrib & _A_SUBDIR);
				//如果是目录,递归查找；如果不是,把文件绝对路径存入vector中
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


	// 读取当前程序路径，生成配置文件config.ini并写入内容
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
		std::wcout << (LPCTSTR)sPath << std::endl;		// 控制台上打印宽字符

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
		std::wcout << (LPCTSTR)configPath << std::endl;

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
		std::wcout.imbue(std::locale(std::locale(), "", LC_CTYPE));

		// 1. 读字符串
		/*
		GetPrivateProfileString(
					LPCTSTR lpAppName,				// 节名
					LPCTSTR lpKeyName,				// key名
					LPCTSTR lpDefault,					// 如果INI文件中没有前两个参数指定的节名或key名,则将此值赋给变量.
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
		const int iSize = WideCharToMultiByte(CP_ACP, 0, str, -1, NULL, 0, NULL, NULL);		//iSize =wcslen(pwsUnicode)+1=6
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
 

	// 测试getFileNames()
	void test2() 
	{
		std::vector<std::string> fileNames, fileNamesRecur;
		std::string path("E:/抽壳加支撑");  

		//getFileNames(path, fileNames, false);
		//std::cout << "非递归遍历文件名：" << std::endl;
		//for (const auto& ph : fileNames)
		//	std::cout << ph << std::endl;
		//std::cout << std::endl << std::endl;

		getFileNames(path, fileNamesRecur, true);
		std::cout << "递归遍历文件名：" << std::endl;
		for (const auto& ph : fileNamesRecur)
			std::cout << ph << std::endl;

		std::cout << "finished." << std::endl;
	}


	// CString, 和普通字符、字符串的转换：
	void test3() 
	{
		/*
		CStringT
			实际上它是一个操作可变长度字符串的模板类。
			CStringT模板类有三个实例：CString、CStringA和CStringW，它们分别提供对TCHAR、char和wchar_t字符类型的字符串的操作。
				char类型定义的是Ansi字符
				wchar_t类型定义的是Unicode字符，
			
			而TCHAR取决于MFC工程的属性对话框中的Configuration Properties->General->Character Set属性，
					如果此属性为Use Multi-Byte Character Set，则TCHAR类型定义的是Ansi字符，
					而如果为Use Unicode Character Set，则TCHAR类型定义的是Unicode字符。
 
		
		*/
		CString   sPath;
		CString cstr{"你好"};

		////			注：WIN10下TXT文件默认的字符编码是UTF-8，需要转换成ANSI或UNICODE编码；
		//std::wcout.imbue(std::locale(std::locale(), "", LC_CTYPE));			// 设置wcout的语言环境，缺少这一步打印中文会有错误。
		//std::wstring wDatFileName = STR_UTF8ToUnicode(tempStr);
		//std::string datFileName = STR_UnicodeToANSI(wDatFileName);
		//std::string datFilePath = g_debugPath + datFileName;
		//std::cout << datFilePath << std::endl;

		// 获取当前进程加载的模块的路径。
		std::cout << "当前sPath的长度是：" << sPath.GetLength() << std::endl;
		GetModuleFileName(NULL, sPath.GetBufferSetLength(MAX_PATH + 1), MAX_PATH);
		std::cout << "当前sPath的长度是：" << sPath.GetLength() << std::endl;

		//// CT2A()——CString转换为ansi编码的std::string;
		//std::string str1 = CT2A(sPath);
		//std::string str2 = CT2A(cstr);
		
 
		std::cout << "finished." << std::endl;
	}
}


// windows多线程
namespace MULTITHREAD
{
	HANDLE hMutex = NULL;		//互斥量

	DWORD WINAPI Fun(LPVOID lpParamter)
	{
		for (int i = 0; i < 10; i++)
		{
			//请求一个互斥量锁
			WaitForSingleObject(hMutex, INFINITE);
			std::cout << "A Thread Fun Display!" << std::endl;
			Sleep(100);

			//释放互斥量锁
			ReleaseMutex(hMutex);
		}
		return 0L;			//表示返回的是long型的0

	}


	void test1()
	{
		HANDLE hThread = CreateThread(NULL, 0, Fun, NULL, 0, NULL);
		hMutex = CreateMutex(NULL, FALSE, L"screen");

		// 关闭线程句柄
		if (hThread != nullptr) 
			CloseHandle(hThread);
	
		// 主线程的执行路径
		for (int i = 0; i < 10; i++)
		{
			//请求获得一个互斥量锁
			if (hMutex != nullptr) 
				WaitForSingleObject(hMutex, INFINITE);
			
			std::cout << "Main Thread Display!" << std::endl;
			Sleep(100);

			//释放互斥量锁
			if (hMutex != nullptr)
				ReleaseMutex(hMutex);
		}
	}


	void test2() 
	{
		// 生成一个大容量的向量，存放随机数：
		std::vector<float> numVec(10000, 0);
		std::vector<float> randVec(10000);
		numVec[0] = 0.1;
		unsigned elemCount = numVec.size();
		std::default_random_engine e;								// 随机数生成器的引擎对象
		std::uniform_real_distribution<float> URD_f(0, 1);
		tiktok& tt = tiktok::getInstance();

# if 1
		// 单线程耗时为9s+
		std::cout << "开始：" << std::endl;
		tt.start();
		for (unsigned i = 0; i < elemCount; ++i)		// 生成一组随机数，求和，赋值给numVec中的元素；
		{
			for (auto& num : randVec)
				num = URD_f(e);
			numVec[i] = std::sqrt(std::accumulate(randVec.begin(), randVec.end(), 0));
		}
		tt.endCout("单线程耗时：");
#endif 

		// 多线程并行：
		const static unsigned n_threads = std::thread::hardware_concurrency();
		std::cout << "线程数：" << n_threads << std::endl;
		if (0u == n_threads)
			return;

		unsigned slice = std::round(elemCount / n_threads);
		slice = std::max(slice, 1u);
		std::vector<std::thread> threadPool;
		threadPool.reserve(n_threads);

		// 线程函数：
		auto func = [&](unsigned start, unsigned end)
		{
			std::vector<float> tmpRands(10000);
			for (unsigned i = start; i < end; ++i)		// 生成一组随机数，求和，赋值给numVec中的元素；
			{
				for (auto& num : tmpRands)
					num = URD_f(e);
				numVec[i] = std::sqrt(std::accumulate(tmpRands.begin(), tmpRands.end(), 0));
			}
		};

		// 生成thread对象：
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
		tt.endCout("多线程耗时：");

		std::cout << "finished." << std::endl;
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
	// TEST_LIBS::test1_2();
	
	// TEST_WINAPI::test3();

	// MULTITHREAD::test2();

	int hours = 0;
	double weekly_pay = 0;
	double rate = 0;

	printf("请输入员工的小时工资：￥");
	scanf("%lf", &rate);
	printf("请输入员工的工作时数（小时）: ");
	scanf("%d", &hours);
	weekly_pay = rate * 40 + 2 * rate * (hours - 40);
	printf("本周应支付薪水是：￥%.lf", weekly_pay);

    return 0;
}

