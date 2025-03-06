#pragma once

#include <iostream>
#include <fstream>
#include <sstream>			// 字符串流
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
#include <limits>				// 提供std::numeric_limits<>模板

#include <cmath>
#include <random>
#include <ctime>
#include <typeinfo>
#include <type_traits>

#include <memory> 
#include <thread>					// c++线程支持库
#include <mutex>
#include <atomic>			// 原子类型 
#include <cassert>			// 断言

// MFC
#ifdef _WIN32
#ifndef NOMINMAX
#define NOMINMAX
#endif 
#include <windows.h> 
#include <atlstr.h>				// 包含CString类。属于microsoft ATL(活动模板库avtive template library)
#include <io.h>
#endif  
   
#include <omp.h>			// openMP


// #define USE_BOOST
#ifdef  USE_BOOST
#include <boost/tuple/tuple.hpp>
#endif  
 

// 内存和CPU监视接口需要的一些头文件；
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


////////////////////////////////////////////////////////////////////////////////////////////// 工具接口
namespace AUXILIARY
{
	// 字符串转换为宽字符串；
	std::wstring s2ws(const std::string& s);

	// 宽字符串转换为字符串；
	std::string ws2s(const std::wstring& ws);

	// 在指定目录下创建文件夹：
	bool CreateFolder(const std::string& dirPath);

	// 检测路径是否存在
	bool CheckValidPath(const std::string& path);

	// 返回正确的文件夹路径
	std::string CorrectDirPath(const std::string& dirPath);

	// 输入文件完整路径，输出文件名字符串
	std::string ExtractFileName(const std::string& filePath);

	// 输入文件夹完整路径，输出文件夹名称（不包括末尾的'/'或'\\'）：
	std::string ExtractDirName(const std::string& dirPath);

	// 输入文件名或文件完整路径，输出文件后缀名字符串（包括'.'）
	std::string ExtractNameExt(const std::string& filePath);

	// 输入文件完整路径（末尾不能是"/"或"\\"），输出其所在文件夹完整路径，末尾没有"/"或"\\"
	std::string ExtractFileDir(const std::string& filePath);

	// 生成头部补0的数字字符串：
	std::string formatNumWithLeadingZeros(const int number, const size_t width);

	// （递归）读取输入目录下的所有文件
	void GetFileNames(std::vector<std::string>& files, std::string path, const bool blSenseDir);

	// 读取输入目录下的所有文件夹
	void GetDirNames(std::vector<std::string>& files, std::string path);

	// cinolib中的多线程并行for循环；
	template<typename Func>
	void PARALLEL_FOR(unsigned int  beg, unsigned int  end, \
		const Func& func, const unsigned int serial_if_less_than = 12)
	{
		/*
			PARALLEL_FOR(
				unsigned int   beg,                                     起始元素索引
				unsigned int  end,                                      尾元素索引
				const unsigned int  serial_if_less_than,      如果需要处理的元素不小于该值，则使用并行化；
				const Func & func										操作元素的函数子；
				)
		*/
		unsigned int elemCount = end - beg + 1;

		if (elemCount < serial_if_less_than)
			for (unsigned int i = beg; i < end; ++i)
				func(i);
		else
		{
			// 确定起的线程数；
			const static unsigned n_threads_hint = std::thread::hardware_concurrency();
			const static unsigned n_threads = (n_threads_hint == 0u) ? 8u : n_threads_hint;

			// for循环的范围分解成几段；
			unsigned int slice = (unsigned int)std::round(elemCount / static_cast<double>(n_threads));
			slice = std::max(slice, 1u);

			// 线程函数：
			auto subTraverse = [&func](unsigned int head, unsigned int tail)
				{
					for (unsigned int k = head; k < tail; ++k)
						func(k);
				};

			// 生成线程池，执行并发for循环；
			std::vector<std::thread> pool;              // 线程池；
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

			// 线程同步；
			for (std::thread& t : pool)
			{
				if (t.joinable())
					t.join();
			}
		}
	}


	// 变参并行for循环——索引以外的参数使用std::tuple传入；
	template<typename Func, typename paramTuple>
	void PARALLEL_FOR(unsigned int  beg, unsigned int  end, const Func& func, \
		const paramTuple& pt, const unsigned int serial_if_less_than = 12)
	{
		/*
			PARALLEL_FOR(
				unsigned int   beg,                                     起始元素索引
				unsigned int  end,                                      尾元素索引
				const unsigned int  serial_if_less_than,      如果需要处理的元素不小于该值，则使用并行化；
				const paramTuple& pt								索引以外的其他参数；
				const Func & func										操作元素的函数子；
				)
		*/
		unsigned int elemCount = end - beg + 1;

		if (elemCount < serial_if_less_than)
			for (unsigned int i = beg; i < end; ++i)
				func(i, pt);
		else
		{
			// 确定起的线程数；
			const static unsigned n_threads_hint = std::thread::hardware_concurrency();
			const static unsigned n_threads = (n_threads_hint == 0u) ? 8u : n_threads_hint;

			// for循环的范围分解成几段；
			unsigned int slice = (unsigned int)std::round(elemCount / static_cast<double>(n_threads));
			slice = std::max(slice, 1u);

			// 线程函数：
			auto subTraverse = [&func, &pt](unsigned int head, unsigned int tail)
				{
					for (unsigned int k = head; k < tail; ++k)
						func(k, pt);
				};

			// 生成线程池，执行并发for循环；
			std::vector<std::thread> pool;              // 线程池；
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

			// 线程同步；
			for (std::thread& t : pool)
			{
				if (t.joinable())
					t.join();
			}
		}
	} 

	// 传入函数子或函数指针遍历stl容器
	template<typename T, typename F>
	void traverseSTL(T& con, F f)
	{
		std::for_each(con.begin(), con.end(), f);
		std::cout << std::endl;
	}

	// 传入函数子或函数指针遍历std::map, std::unordered_map等
	template<typename mapType, typename F>
	void traverseSTLmap(mapType& m, F f)
	{
		std::for_each(m.begin(), m.end(), f);
		std::cout << std::endl;
	}

	// 反向遍历
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


////////////////////////////////////////////////////////////////////////////////////////////// DEBUG 接口
namespace MY_DEBUG
{
	// 函数子——打印std::cout支持的类型变量。
	template <typename	T>
	class disp
	{
	public:
		void operator()(const T& arg)
		{
			std::cout << arg << ", ";
		}
	};


	// 函数子——打印std::pair
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
		std::cout << firstArg << " ";	// 递归递推；
		debugDisp(args...);
	}

	void debugDispWStr(const std::wstring& wstr);

	// 针对编译器版本信息的宏
	void print_compiler_info();

	// 打印操作系统信息
	void print_os_info();

	// 打印build mode——是release或debug:
	void print_build_mode();

	// 打印处理器架构信息
	void print_architecture_info();

	// 打印处理器核心数量
	void print_cpu_cores();

	// 获取并打印CPU信息
	void print_cpu_info();

	void print_env_info();

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



////////////////////////////////////////////////////////////////////////////////////////////// 基于windows API写的一些工具接口
namespace MY_WIN_API
{
	// 读取某个目录下所有文件名、目录名；
	void getFileNames(std::string path, std::vector<std::string>& files, bool blRecur = true);


	// 获得当前进程的进程ID
	int GetCurrentPid();


	// get specific process cpu occupation ratio by pid 
	std::uint64_t convert_time_format(const FILETIME* ftime);
 
	 
	float GetCpuUsageRatio(int pid);


	// get specific process physical memeory occupation size by pid (MB)
	double GetMemoryUsage(int pid);


	// 复制文件：
	bool CopyFileViaWinAPI(const std::string& outputPath, const std::string& inputPath);
}
using namespace MY_WIN_API;

 

// 自定义pointer-like字符串类
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

// 自定义比较器——前者小于后者时返回true 
extern std::function<bool(const myString&, const myString&)> myComparer;

void dispMyString(const myString& str);