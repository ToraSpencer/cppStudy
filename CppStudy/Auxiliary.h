#pragma once

#include <iostream>
#include <fstream>
#include <sstream>			// �ַ�����
#include <iomanip>

#include <iterator>
#include <utility>

#include <string>
#include <array>
#include <vector>
#include <list>
#include <deque>
#include <stack>
#include <queue>
#include <set>
#include <unordered_set>
#include <map>
#include <unordered_map>
#include <initializer_list>
#include <bitset>	

#include <algorithm>
#include <functional>
#include <numeric>
#include <limits>				// �ṩstd::numeric_limits<>ģ��

#include <cmath>
#include <random>
#include <ctime>
#include <typeinfo>
#include <type_traits>

#include <memory> 
#include <thread>					// c++�߳�֧�ֿ�
#include <mutex>
#include <atomic>			// ԭ������ 
#include <cassert>			// ����

// MFC
#ifdef _WIN32
#ifndef NOMINMAX
#define NOMINMAX
#endif 
#include <windows.h> 
#include <atlstr.h>				// ����CString�ࡣ����microsoft ATL(�ģ���avtive template library)
#include <io.h>
#endif  
   
#include <omp.h>			// openMP


// #define USE_BOOST
#ifdef  USE_BOOST
#include <boost/tuple/tuple.hpp>
#endif  
 

// �ڴ��CPU���ӽӿ���Ҫ��һЩͷ�ļ���
#ifdef _WIN32 
#include <psapi.h>   
#include <direct.h>
#include <process.h>
#else
#include <sys/stat.h>
#include <sys/sysinfo.h>
#include <sys/time.h>
#include <unistd.h>
#endif


#define BLUE_REGION
#ifdef BLUE_REGION
const std::string g_samplePath = "C:/myData/";
const std::string g_debugPath = "C:/myData/output/";
#else
const std::string g_samplePath = "E:/myData/";
const std::string g_debugPath = "E:/outputData/";
#endif 


////////////////////////////////////////////////////////////////////////////////////////////// ���߽ӿ�
namespace AUXILIARY
{
	// �ַ���ת��Ϊ���ַ�����
	std::wstring s2ws(const std::string& s);

	// ���ַ���ת��Ϊ�ַ�����
	std::string ws2s(const std::wstring& ws);

	// ��ָ��Ŀ¼�´����ļ��У�
	bool CreateFolder(const std::string& dirPath);

	// ���·���Ƿ����
	bool CheckValidPath(const std::string& path);

	// ������ȷ���ļ���·��
	std::string CorrectDirPath(const std::string& dirPath);

	// �����ļ�����·��������ļ����ַ���
	std::string ExtractFileName(const std::string& filePath);

	// �����ļ�������·��������ļ������ƣ�������ĩβ��'/'��'\\'����
	std::string ExtractDirName(const std::string& dirPath);

	// �����ļ������ļ�����·��������ļ���׺���ַ���������'.'��
	std::string ExtractNameExt(const std::string& filePath);

	// �����ļ�����·����ĩβ������"/"��"\\"��������������ļ�������·����ĩβû��"/"��"\\"
	std::string ExtractFileDir(const std::string& filePath);

	// ����ͷ����0�������ַ�����
	std::string formatNumWithLeadingZeros(const int number, const size_t width);

	// ���ݹ飩��ȡ����Ŀ¼�µ������ļ�
	void GetFileNames(std::vector<std::string>& files, std::string path, const bool blSenseDir);

	// ��ȡ����Ŀ¼�µ������ļ���
	void GetDirNames(std::vector<std::string>& files, std::string path);

	// cinolib�еĶ��̲߳���forѭ����
	template<typename Func>
	void PARALLEL_FOR(unsigned int  beg, unsigned int  end, \
		const Func& func, const unsigned int serial_if_less_than = 12)
	{
		/*
			PARALLEL_FOR(
				unsigned int   beg,                                     ��ʼԪ������
				unsigned int  end,                                      βԪ������
				const unsigned int  serial_if_less_than,      �����Ҫ�����Ԫ�ز�С�ڸ�ֵ����ʹ�ò��л���
				const Func & func										����Ԫ�صĺ����ӣ�
				)
		*/
		unsigned int elemCount = end - beg + 1;

		if (elemCount < serial_if_less_than)
			for (unsigned int i = beg; i < end; ++i)
				func(i);
		else
		{
			// ȷ������߳�����
			const static unsigned n_threads_hint = std::thread::hardware_concurrency();
			const static unsigned n_threads = (n_threads_hint == 0u) ? 8u : n_threads_hint;

			// forѭ���ķ�Χ�ֽ�ɼ��Σ�
			unsigned int slice = (unsigned int)std::round(elemCount / static_cast<double>(n_threads));
			slice = std::max(slice, 1u);

			// �̺߳�����
			auto subTraverse = [&func](unsigned int head, unsigned int tail)
				{
					for (unsigned int k = head; k < tail; ++k)
						func(k);
				};

			// �����̳߳أ�ִ�в���forѭ����
			std::vector<std::thread> pool;              // �̳߳أ�
			pool.reserve(n_threads);
			unsigned int head = beg;
			unsigned int tail = std::min(beg + slice, end);
			for (unsigned int i = 0; i + 1 < n_threads && head < end; ++i)
			{
				pool.emplace_back(subTraverse, head, tail);
				head = tail;
				tail = std::min(tail + slice, end);
			}
			if (head < end)
				pool.emplace_back(subTraverse, head, end);

			// �߳�ͬ����
			for (std::thread& t : pool)
			{
				if (t.joinable())
					t.join();
			}
		}
	}


	// ��β���forѭ��������������Ĳ���ʹ��std::tuple���룻
	template<typename Func, typename paramTuple>
	void PARALLEL_FOR(unsigned int  beg, unsigned int  end, const Func& func, \
		const paramTuple& pt, const unsigned int serial_if_less_than = 12)
	{
		/*
			PARALLEL_FOR(
				unsigned int   beg,                                     ��ʼԪ������
				unsigned int  end,                                      βԪ������
				const unsigned int  serial_if_less_than,      �����Ҫ�����Ԫ�ز�С�ڸ�ֵ����ʹ�ò��л���
				const paramTuple& pt								�������������������
				const Func & func										����Ԫ�صĺ����ӣ�
				)
		*/
		unsigned int elemCount = end - beg + 1;

		if (elemCount < serial_if_less_than)
			for (unsigned int i = beg; i < end; ++i)
				func(i, pt);
		else
		{
			// ȷ������߳�����
			const static unsigned n_threads_hint = std::thread::hardware_concurrency();
			const static unsigned n_threads = (n_threads_hint == 0u) ? 8u : n_threads_hint;

			// forѭ���ķ�Χ�ֽ�ɼ��Σ�
			unsigned int slice = (unsigned int)std::round(elemCount / static_cast<double>(n_threads));
			slice = std::max(slice, 1u);

			// �̺߳�����
			auto subTraverse = [&func, &pt](unsigned int head, unsigned int tail)
				{
					for (unsigned int k = head; k < tail; ++k)
						func(k, pt);
				};

			// �����̳߳أ�ִ�в���forѭ����
			std::vector<std::thread> pool;              // �̳߳أ�
			pool.reserve(n_threads);
			unsigned int head = beg;
			unsigned int tail = std::min(beg + slice, end);
			for (unsigned int i = 0; i + 1 < n_threads && head < end; ++i)
			{
				pool.emplace_back(subTraverse, head, tail);
				head = tail;
				tail = std::min(tail + slice, end);
			}
			if (head < end)
				pool.emplace_back(subTraverse, head, end);

			// �߳�ͬ����
			for (std::thread& t : pool)
			{
				if (t.joinable())
					t.join();
			}
		}
	} 

	// ���뺯���ӻ���ָ�����stl����
	template<typename T, typename F>
	void traverseSTL(T& con, F f)
	{
		std::for_each(con.begin(), con.end(), f);
		std::cout << std::endl;
	}

	// ���뺯���ӻ���ָ�����std::map, std::unordered_map��
	template<typename mapType, typename F>
	void traverseSTLmap(mapType& m, F f)
	{
		std::for_each(m.begin(), m.end(), f);
		std::cout << std::endl;
	}

	// �������
	template<typename T, typename F>
	void revTraverseSTL(T& con, F f)
	{
		std::for_each(con.rbegin(), con.rend(), f);
		std::cout << std::endl;
	}

	template <typename T>
	void templateTest(const T& arg);
}
using namespace AUXILIARY;


////////////////////////////////////////////////////////////////////////////////////////////// DEBUG �ӿ�
namespace MY_DEBUG
{
	// �����ӡ�����ӡstd::cout֧�ֵ����ͱ�����
	template <typename	T>
	class disp
	{
	public:
		void operator()(const T& arg)
		{
			std::cout << arg << ", ";
		}
	};


	// �����ӡ�����ӡstd::pair
	template <typename pairType>
	class dispPair
	{
	public:
		void operator()(const pairType& p)
		{
			std::cout << "(" << p.first << ", " << p.second << "), ";
		}

		void operator()(const std::string& str, const pairType& p)
		{
			std::cout << str << "(" << p.first << ", " << p.second << "), ";
		}
	};


	template <typename	T1, typename T2>
	std::ostream& operator<<(std::ostream& ss, const std::pair<T1, T2>& p) 
	{
		ss << "(" << p.first << ", " << p.second << ")";
		return ss;
	}

	 
	void debugDisp();

	template <typename T, typename... Types>
	void debugDisp(const T& firstArg, const Types&... args)
	{
		std::cout << firstArg << " ";	// �ݹ���ƣ�
		debugDisp(args...);
	}

	void debugDispWStr(const std::wstring& wstr);

	// ��Ա������汾��Ϣ�ĺ�
	void print_compiler_info();

	// ��ӡ����ϵͳ��Ϣ
	void print_os_info();

	// ��ӡbuild mode������release��debug:
	void print_build_mode();

	// ��ӡ�������ܹ���Ϣ
	void print_architecture_info();

	// ��ӡ��������������
	void print_cpu_cores();

	// ��ȡ����ӡCPU��Ϣ
	void print_cpu_info();

	void print_env_info();

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



////////////////////////////////////////////////////////////////////////////////////////////// ����windows APIд��һЩ���߽ӿ�
namespace MY_WIN_API
{
	// ��ȡĳ��Ŀ¼�������ļ�����Ŀ¼����
	void getFileNames(std::string path, std::vector<std::string>& files, bool blRecur = true);


	// ��õ�ǰ���̵Ľ���ID
	int GetCurrentPid();


	// get specific process cpu occupation ratio by pid 
	std::uint64_t convert_time_format(const FILETIME* ftime);
 
	 
	float GetCpuUsageRatio(int pid);


	// get specific process physical memeory occupation size by pid (MB)
	double GetMemoryUsage(int pid);


	// �����ļ���
	bool CopyFileViaWinAPI(const std::string& outputPath, const std::string& inputPath);
}
using namespace MY_WIN_API;

 

// �Զ���pointer-like�ַ�����
struct myString
{
private:
	const char* pc;
public:
	myString() = delete;
	myString(const char* pc0) :pc(pc0) {}

	const char* c_str() const
	{
		return this->pc;
	}
	 
};

// �Զ���Ƚ�������ǰ��С�ں���ʱ����true 
extern std::function<bool(const myString&, const myString&)> myComparer;

void dispMyString(const myString& str);