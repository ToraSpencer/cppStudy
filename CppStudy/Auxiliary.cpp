#include "Auxiliary.h"


////////////////////////////////////////////////////////////////////////////////////////////// ���߽ӿ�
namespace AUXILIARY
{
	// �ַ���ת��Ϊ���ַ�����
	std::wstring s2ws(const std::string& s)
	{
		std::locale old_loc = std::locale::global(std::locale(""));
		const char* src_str = s.c_str();
		const size_t buffer_size = s.size() + 1;
		wchar_t* dst_wstr = new wchar_t[buffer_size];
		wmemset(dst_wstr, 0, buffer_size);
		mbstowcs(dst_wstr, src_str, buffer_size);
		std::wstring result = dst_wstr;
		delete[]dst_wstr;
		std::locale::global(old_loc);
		return result;
	}


	// ���ַ���ת��Ϊ�ַ�����
	std::string ws2s(const std::wstring& ws)
	{
		std::locale old_loc = std::locale::global(std::locale(""));
		const wchar_t* src_wstr = ws.c_str();
		size_t buffer_size = ws.size() * 4 + 1;
		char* dst_str = new char[buffer_size];
		memset(dst_str, 0, buffer_size);
		wcstombs(dst_str, src_wstr, buffer_size);
		std::string result = dst_str;
		delete[]dst_str;
		std::locale::global(old_loc);
		return result;
	}


	// ��ָ��Ŀ¼�´����ļ��У�
	bool CreateFolder(const std::string& dirPath)
	{
		bool retFlag = false;

		// 1. ����·�����ַ����� 
		std::wstring wdirPath = s2ws(dirPath);

		// 2. �����ļ���
#ifdef _WIN32
		int retInt = CreateDirectory(wdirPath.c_str(), NULL);
		retFlag = (retInt > 0);
#endif 

		return retFlag;
	}


	// ���·���Ƿ����
	bool CheckValidPath(const std::string& path)
	{
		bool retFlag = false;

		// 1. ����·�����ַ����� 
		std::wstring wPath = s2ws(path);

		// 2. ʹ��GetFileAttributes()�ж�·�����ԣ�
#ifdef _WIN32 
		DWORD attributes = GetFileAttributes(wPath.c_str());
		if (attributes != INVALID_FILE_ATTRIBUTES)
			retFlag = true;
#endif 
		return retFlag;
	}


	// ������ȷ���ļ���·��
	std::string CorrectDirPath(const std::string& dirPath)
	{
		const size_t length = dirPath.length();
		if (length < 2)
			return dirPath;
		if ('/' == *dirPath.rbegin() || '\\' == *dirPath.rbegin())
			return dirPath;
		else
			return dirPath + "/";
	}


	// �����ļ�����·��������ļ����ַ���
	std::string ExtractFileName(const std::string& filePath)
	{
		std::string retStr;
		size_t posNum{ 0 };
		if (filePath.empty())
			return retStr;

		size_t posNum1 = filePath.find_last_of("\\");
		size_t posNum2 = filePath.find_last_of("/");
		int pn1 = std::string::npos == posNum1 ? -1 : static_cast<int>(posNum1);
		int pn2 = std::string::npos == posNum2 ? -1 : static_cast<int>(posNum2);
		if (pn1 < 0 && pn2 < 0)
			return filePath;
		posNum = pn1 < pn2 ? posNum2 : posNum1;
		if (posNum >= filePath.size() - 1)
			return retStr;
		retStr = &filePath[posNum + 1];

		return retStr;
	}


	// �����ļ�������·��������ļ������ƣ�������ĩβ��'/'��'\\'����
	std::string ExtractDirName(const std::string& dirPath)
	{
		std::string path = dirPath;
		if ('\\' == *path.rbegin() || '/' == *path.rbegin())
			path.erase(path.size() - 1);
		return ExtractFileName(path);
	}


	// �����ļ������ļ�����·��������ļ���׺���ַ���������'.'��
	std::string ExtractNameExt(const std::string& filePath)
	{
		std::string retStr;
		size_t posNum{ 0 };
		if (filePath.empty())
			return retStr;
		posNum = filePath.find_last_of(".");
		if (posNum >= filePath.size() - 1)
			return retStr;
		retStr = &filePath[posNum];
		return retStr;
	}


	// �����ļ�����·����ĩβ������"/"��"\\"��������������ļ�������·����ĩβû��"/"��"\\"
	std::string ExtractFileDir(const std::string& filePath)
	{
		std::string retStr;
		size_t posNum{ 0 };
		if (filePath.empty())
			return retStr;

		size_t posNum1 = filePath.find_last_of("\\");
		size_t posNum2 = filePath.find_last_of("/");
		int pn1 = std::string::npos == posNum1 ? -1 : static_cast<int>(posNum1);
		int pn2 = std::string::npos == posNum2 ? -1 : static_cast<int>(posNum2);
		if (pn1 < 0 && pn2 < 0)
			return retStr;
		posNum = pn1 < pn2 ? posNum2 : posNum1;
		if (posNum >= filePath.size() - 1)
			return retStr;
		retStr = filePath.substr(0, posNum);

		if ("." == retStr)
			return std::string{};

		return retStr;
	}


	// ����ͷ����0�������ַ�����
	std::string formatNumWithLeadingZeros(const int number, const size_t width)
	{
		std::stringstream ss;
		ss << std::setw(width) << std::setfill('0') << number;            // ��Ҫ<iomanip>
		return ss.str();
	}


	// ���ݹ飩��ȡ����Ŀ¼�µ������ļ�
	void GetFileNames(std::vector<std::string>& files, std::string path, const bool blSenseDir)
	{
#ifdef _WIN32
		intptr_t hFile = 0;                     // �ļ������ע�⣺�ҷ�����Щ���´���˴���long���ͣ�ʵ�������лᱨ������쳣 
		struct _finddata_t fileinfo;        // �ļ���Ϣ
		std::string tmpPath;
		if ('/' != *path.crbegin() && '\\' != *path.crbegin())
			path.assign(path).append("/");
		if ((hFile = _findfirst(tmpPath.assign(path).append("*").c_str(), &fileinfo)) != -1)
		{
			do
			{
				// �����Ŀ¼���ݹ���ң��������,���ļ�����·������vector��
				if (fileinfo.attrib & _A_SUBDIR)
				{
					if (blSenseDir && strcmp(fileinfo.name, ".") != 0 && strcmp(fileinfo.name, "..") != 0)
						GetFileNames(files, tmpPath.assign(path).append(fileinfo.name), blSenseDir);
				}
				else
					files.push_back(tmpPath.assign(path).append(fileinfo.name));
			} while (_findnext(hFile, &fileinfo) == 0);
			_findclose(hFile);
		}
#else
		// to be optimized....
		DIR* pDir;
		struct dirent* ptr;
		if (!(pDir = opendir(path.c_str())))
			return;
		while ((ptr = readdir(pDir)) != 0)
			if (strcmp(ptr->d_name, ".") != 0 && strcmp(ptr->d_name, "..") != 0)
				files.push_back(path + "/" + ptr->d_name);
		closedir(pDir);
#endif
	}


	// ��ȡ����Ŀ¼�µ������ļ���
	void GetDirNames(std::vector<std::string>& files, std::string path)
	{
#ifdef _WIN32
		intptr_t hFile = 0;                     // �ļ������ע�⣺�ҷ�����Щ���´���˴���long���ͣ�ʵ�������лᱨ������쳣
		struct _finddata_t fileinfo;        // �ļ���Ϣ
		std::string tmpPath;
		if ('/' != *path.crbegin() && '\\' != *path.crbegin())
			path.assign(path).append("/");
		if ((hFile = _findfirst(tmpPath.assign(path).append("*").c_str(), &fileinfo)) != -1)
		{
			do
			{
				if (fileinfo.attrib & _A_SUBDIR)
					if (strcmp(fileinfo.name, ".") != 0 && strcmp(fileinfo.name, "..") != 0)
						files.push_back(tmpPath.assign(path).append(fileinfo.name).append("/"));
			} while (_findnext(hFile, &fileinfo) == 0);
			_findclose(hFile);
		}
#else
		// to be optimized....
		DIR* pDir;
		struct dirent* ptr;
		if (!(pDir = opendir(path.c_str())))
			return;
		while ((ptr = readdir(pDir)) != 0)
			if (strcmp(ptr->d_name, ".") != 0 && strcmp(ptr->d_name, "..") != 0)
				files.push_back(path + "/" + ptr->d_name);
		closedir(pDir);
#endif
	}

}
using namespace AUXILIARY;

 
////////////////////////////////////////////////////////////////////////////////////////////// DEBUG �ӿ�
namespace MY_DEBUG
{
	void debugDisp()			// �ݹ���ֹ
	{						//		�ݹ���ֹ��Ϊ�޲λ���һ�����������ζ����ԡ�
		std::cout << std::endl;
		return;
	}
	
	void debugDispWStr(const std::wstring& wstr)
	{
		std::wcout.imbue(std::locale(std::locale(), "", LC_CTYPE));		// ����wcout�����Ի�����ȱ����һ����ӡ���Ļ��д���
		std::wcout << wstr << std::endl;
	}

	// ��Ա������汾��Ϣ�ĺ�
	void print_compiler_info()
	{
		std::cout << "Compiler Version: ";
#if defined(_MSC_VER)
		std::cout << "MSVC, version " << _MSC_VER << "\n";
#elif defined(__GNUC__)
		std::cout << "GCC, version " << __GNUC__ << "." << __GNUC_MINOR__ << "\n";
#elif defined(__clang__)
		std::cout << "Clang, version " << __clang_major__ << "." << __clang_minor__ << "\n";
#else
		std::cout << "Unknown compiler\n";
#endif
	}


	// ��ӡ����ϵͳ��Ϣ
	void print_os_info()
	{
#if defined(_WIN32)
		std::cout << "Operating System: Windows\n";
#elif defined(__linux__)
		std::cout << "Operating System: Linux\n";
#elif defined(__APPLE__)
		std::cout << "Operating System: macOS\n";
#else
		std::cout << "Operating System: Unknown\n";
#endif
	}

	// ��ӡbuild mode������release��debug:
	void print_build_mode()
	{
#if defined(_DEBUG)
		std::cout << "Build Mode: Debug\n";
#else
		std::cout << "Build Mode: Release\n";
#endif
	}

	// ��ӡ�������ܹ���Ϣ
	void print_architecture_info()
	{
		std::cout << "Processor Architecture: ";
#if defined(__x86_64__) || defined(_M_X64)
		std::cout << "x64 (AMD or Intel)\n";
#elif defined(__i386) || defined(_M_IX86)
		std::cout << "x86\n";
#elif defined(__arm__) || defined(_M_ARM)
		std::cout << "ARM\n";
#elif defined(__aarch64__)
		std::cout << "ARM64\n";
#else
		std::cout << "Unknown architecture\n";
#endif
	}


	// ��ӡ��������������
	void print_cpu_cores()
	{
		unsigned int cores = std::thread::hardware_concurrency();
		std::cout << "Number of Processor Cores: " << cores << "\n";
	}


	// ��ȡ����ӡCPU��Ϣ
#if defined(__GNUC__) || defined(__clang__)
#include <cpuid.h>
	void print_cpu_info()
	{
		unsigned int eax, ebx, ecx, edx;
		char cpu_brand[49] = { 0 };

		__get_cpuid(0x80000002, &eax, &ebx, &ecx, &edx);
		std::memcpy(cpu_brand, &eax, sizeof(eax));
		std::memcpy(cpu_brand + 4, &ebx, sizeof(ebx));
		std::memcpy(cpu_brand + 8, &ecx, sizeof(ecx));
		std::memcpy(cpu_brand + 12, &edx, sizeof(edx));

		__get_cpuid(0x80000003, &eax, &ebx, &ecx, &edx);
		std::memcpy(cpu_brand + 16, &eax, sizeof(eax));
		std::memcpy(cpu_brand + 20, &ebx, sizeof(ebx));
		std::memcpy(cpu_brand + 24, &ecx, sizeof(ecx));
		std::memcpy(cpu_brand + 28, &edx, sizeof(edx));

		__get_cpuid(0x80000004, &eax, &ebx, &ecx, &edx);
		std::memcpy(cpu_brand + 32, &eax, sizeof(eax));
		std::memcpy(cpu_brand + 36, &ebx, sizeof(ebx));
		std::memcpy(cpu_brand + 40, &ecx, sizeof(ecx));
		std::memcpy(cpu_brand + 44, &edx, sizeof(edx));

		std::cout << "CPU: " << cpu_brand << "\n";
	}
#elif defined(_MSC_VER)
#include <intrin.h>
	void print_cpu_info()
	{
		int cpuInfo[4] = { -1 };
		char cpuBrand[0x40];
		__cpuid(cpuInfo, 0x80000002);
		memcpy(cpuBrand, cpuInfo, sizeof(cpuInfo));
		__cpuid(cpuInfo, 0x80000003);
		memcpy(cpuBrand + 16, cpuInfo, sizeof(cpuInfo));
		__cpuid(cpuInfo, 0x80000004);
		memcpy(cpuBrand + 32, cpuInfo, sizeof(cpuInfo));

		std::cout << "CPU: " << cpuBrand << "\n";
	}

#else

	void print_cpu_info()
	{
		std::cout << "CPU: Unknown\n";
	}
#endif

	void print_env_info()
	{
		print_compiler_info();
		print_os_info();
		print_architecture_info();
		print_build_mode();
		print_cpu_cores();
		print_cpu_info();
	}

}
using namespace MY_DEBUG;



////////////////////////////////////////////////////////////////////////////////////////////// ����windows APIд��һЩ���߽ӿ�
namespace MY_WIN_API
{
	// ��ȡĳ��Ŀ¼�������ļ�����Ŀ¼����
	void getFileNames(std::string path, std::vector<std::string>& files, bool blRecur)
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
				if (isSubDir && blRecur)
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


	// ��õ�ǰ���̵Ľ���ID
	int GetCurrentPid()
	{
		return _getpid();
	}


	// get specific process cpu occupation ratio by pid
	std::uint64_t convert_time_format(const FILETIME* ftime)
	{
		LARGE_INTEGER li;

		li.LowPart = ftime->dwLowDateTime;
		li.HighPart = ftime->dwHighDateTime;
		return li.QuadPart;
	} 


	float GetCpuUsageRatio(int pid)
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
	double GetMemoryUsage(int pid)
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


	// �����ļ���
	bool CopyFileViaWinAPI(const std::string& outputPath, const std::string& inputPath)
	{
		const std::string destDir = ExtractFileDir(outputPath);
		const LPCSTR sourceFile = inputPath.c_str();
		const LPCSTR destFolder = destDir.c_str();
		const LPCSTR destFilePath = outputPath.c_str();

		// 1. ���Ŀ���ļ����Ƿ����
		DWORD folderAttr = GetFileAttributesA(destFolder);
		if (folderAttr == INVALID_FILE_ATTRIBUTES || !(folderAttr & FILE_ATTRIBUTE_DIRECTORY))
			return false;

		// 2. �����ļ�
		if (!CopyFileA(sourceFile, destFilePath, FALSE))
		{
			std::cerr << "�ļ�����ʧ�ܣ�������룺" << GetLastError() << "\n";
			return false;
		}

		return true;
	}
}
using namespace MY_WIN_API;


std::function<bool(const myString&, const myString&)> myComparer =\
[](const myString& str1, const myString& str2) ->bool
	{
		if (strlen(str1.c_str()) < strlen(str2.c_str()))
			return true;
		else
			return false;
	};


void dispMyString(const myString& str)
{
	std::cout << str.c_str() << std::endl;
};