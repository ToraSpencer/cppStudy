﻿#include "toolsHeader.h"
 

//  WINDOWS提供的时间相关的接口
/*

	WINDOWS提供的时间相关的接口——需要头文件<windows.h>
			GetTickCount()
			Sleep()

*/
 


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
		std::cout << firstArg << " ";	// 递归递推；
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



////////////////////////////////////////////////////////////////////////////////////////////// windows API
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


	// 获得当前进程的进程ID
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



////////////////////////////////////////////////////////////////////////////////////////////// 暂时不知如何分类：
namespace TEST_UNKNOWN
{
	// const_cast
	namespace CONSTCAST
	{
		void transformConstInt(const int& num)
		{
			std::cout << "num == " << num << std::endl;
			int& newNum = const_cast<int&>(num);
			newNum++;

			// 改变新的非const引用后，原const引用也随之修改；
			std::cout << "num == " << num << std::endl;
		}

		void test1()
		{
			int num1 = 99;
			transformConstInt(num1);
		std:std::cout << num1 << std::endl;

			// const_cast<>()只能去除指针和引用的const属性，不可以将其他const变量修改成非const的；

			//const int num2 = 99;
			//transformConstInt(num2);
			//std:std::cout << num2 << std::endl;
		}

	}


	// tuple
	namespace TEST_TUPLE
	{
		// std::make_tuple();
		void test0()
		{
			std::tuple<int, float, bool> t1(1, 2.0, false);
			std::tuple<double, unsigned, bool> t2 = std::make_tuple(2.0, 3, true);
		}


		// std::get<>
		void test1()
		{
			std::tuple<int, double, double, std::string> tetrad = std::make_tuple(3, 1.1, 2.2, "hahaha");

			auto ret1 = std::get<2>(tetrad);
			auto ret2 = std::get<int>(tetrad);
			auto ret3 = std::get<std::string>(tetrad);
			// auto ret4 = std::get<double>(tetrad);				有二义性，编译不通过；

			debugDisp("ret1 == ", ret1);
			debugDisp("ret2 == ", ret2);
			debugDisp("ret3 == ", ret3);

			debugDisp("finished.");
		}

	}

	 
	namespace DESIGN_PATTERN
	{
		// 桥接模式（bridge） 
		/*
			一种结构型设计模式；
			抽象和行为实现放在两个不同的类层次中，两个层次可以独立改变。
			遵循类的最小设计原则，不同的类承担不同的职责。
		*/


		// 组合模式
		/*
			组合：整体和部分有相同的生命周期，整体消亡则部分也不存在；如人体-人体的各种器官；
			聚合：整体和部分可以有不同的生命周期，整体消亡部分也可以独立存在，如羊群-个体的羊
		*/

#if 0 

		//			组合模式实例——公司组织架构管理系统：
		class orgComponent			// 组织类；
		{
		public:
			orgComponent() = default;

			orgComponent(const char* str) : name(std::string(str))
			{}

			std::string getName() const
			{
				return this->name;
			}

			virtual	void add(const orgComponent& org);

			virtual orgComponent* getChild(const char* orgName);

			virtual unsigned getStuffCount();

		private:
			std::string name;
		};


		class orgComposite : orgComponent		// 组合类；
		{
		public:
			orgComposite(const char* str) :name(std::string(str))
			{}

			virtual void add(const  orgComponent& org)
			{
				this->orgs.push_back(org);
			}

			virtual orgComponent* getChild(const char* orgName)
			{
				orgComponent* orgPtr = nullptr;
				for (auto& elem : this->orgs)
				{
					orgPtr = elem.getChild(orgName);
					if (nullptr != orgPtr)
						return orgPtr;
				}
				return nullptr;
			}

			virtual unsigned getStuffCount()
			{
				unsigned count = 0;
				for (auto& elem : orgs)						// 递归累加职工人数；
					count += elem.getStuffCount();

				return count;
			}

		private:
			std::list<orgComponent> orgs;
			std::string name;
		};


		// 具体的组织部门，相当于叶子节点。
		class ITCenter : orgComponent
		{
		public:
			ITCenter(const char* str) : name(std::string(str)) {}

			virtual unsigned getStuffCount()
			{
				return stuffCount;
			}

			virtual void add(const orgComponent& org)
			{
				std::cout << "已经是最基础部门，无法增加下属部门。" << std::endl;
			}

			virtual orgComponent* getChild(const char* str)
			{
				if (0 == strcmp(this->name.c_str(), str))
					return this;
				else
					return nullptr;
			}

			void setStuffCount(const unsigned num)
			{
				this->stuffCount = num;
			}

		private:
			unsigned stuffCount = 0;
		};


		class algorithmCenter : orgComponent
		{
		public:
			algorithmCenter(const char* str) : name(str) {}

			virtual unsigned getStuffCount()
			{
				return stuffCount;
			}

			virtual void add(const orgComponent& org)
			{
				std::cout << "已经是最基础部门，无法增加下属部门。" << std::endl;
			}

			virtual orgComponent* getChild(const char* str)
			{
				if (0 == strcmp(this->name.c_str(), str))
					return this;
				else
					return nullptr;
			}

			void setStuffCount(const unsigned num)
			{
				this->stuffCount = num;
			}

		private:
			unsigned stuffCount = 0;
		};

		// 用户使用的管理系统类；
		class clientSystem
		{
		public:
			static clientSystem& getInstance()
			{
				static clientSystem sys;
				return sys;
			}

		private:
			orgComposite head("AAA Corporation");

			clientSystem()
			{
				constructSystem();
			}

			clientSystem(clientSystem&) = delete;
			~clientSystem() = default;

			void constructSystem()
			{
				orgComposite branch1("AAA SH branch office");
				orgComposite depTec1("main Technology department");
				orgComposite depTec2("SH Technology department");

				ITCenter ITCenter_SH("SH IT center");
				ITCenter_SH.setStuffCount(20);

				ITCenter ITCenter_main("main IT center");
				ITCenter_main.setStuffCount(99);

				algorithmCenter algCenter_main("main algorithm center");
				algCenter_main.setStuffCount(200);

				depTec2.add(ITCenter_SH);
				branch1.add(depTec2);

				depTec1.add(algCenter_main);
				depTec1.add(ITCenter_main);
				this->head.add(depTec1);
				this->head.add(branch1);
			}

			void listCorpInfo()
			{
				std::cout << "whole stuff count == " << this->head.getStuffCount() << std::endl;
			}
		};
#endif
	}


	namespace CHAR_STRING
	{
		// c/c++中的字符串转换接口
		void test1()
		{
			std::wcout.imbue(std::locale(std::locale(), "", LC_CTYPE));			// 设置wcout的语言环境，缺少这一步打印中文会有错误。

			// std::stoi(), std::stof() 将字符串转换为int和float
			std::string str1 = "123";
			std::string str2 = "v321";
			std::string str3 = " 43";
			std::string str4 = "5 6";
			char cstr1[] = "32";

			std::cout << std::stoi(str1) << std::endl;
			// std::cout << std::stoi(str2) << std::endl;		字符串中有非数值字符程序会中断。
			std::cout << std::stoi(str3) << std::endl;			// 前后的空格不影响数值转换
			std::cout << std::stoi(str4) << std::endl;			// 数字中间有空格的话，会截断空格后面的数字。
			std::cout << std::stoi(cstr1) << std::endl;			// std::string和char* 两种格式的字符串都可以转换

			// wcstombs()——宽字符串转换为窄字符串，C语言接口
			/*
				std::size_t wcstombs(					返回值，成功则返回字符数，不包括终止符'\0'；失败则返回static_cast<std::size_t>(-1)
						char* dst,
						const wchar_t* src,
						std::size_t len
						);

				wcstombs == wide characters std::string to multibyte std::string;
			*/

			//	 mbstowcs()——窄字符串转换为宽字符串，C语言接口
		   /*
			   std::size_t mbstowcs(						返回值，成功则返回转换成功的字符数，不包括终止符'\0'；失败则返回static_cast<std::size_t>(-1)
					   wchar_t* dst,
					   const char* src,
					   std::size_t len
					   );

			   mbstowcs == multibyte std::string to wide characters std::string;
		   */

			std::wstring wstr1;
			str1 = "abcd1234";
			wstr1.resize(str1.size());
			mbstowcs(&wstr1[0], str1.c_str(), str1.size());
			std::wcout << wstr1 << std::endl;
			std::cout << "wstr1.size() == " << wstr1.size() << std::endl;
		}

		// 字符串匹配：
		void test3()
		{
			// 1. std::string, std::wstring的find()方法——寻找字符串中匹配的字符或子串；
			std::string str1 = "asdfajiuiuwww.github.comasdfuoiup";

			//			size_type――std::string和vector定义的类型，是表示容器容量的无符号整型数，
			std::string::size_type num = str1.find("github", 0);							// 第二个参数是搜索开始的位置。
			if (num == std::string::npos)															// 搜索不到的时候返回npos，一般等于-1
				std::cout << "没有找到模板字符串" << std::endl;
			else
				std::cout << "找到模板字符串，位置是" << num << std::endl;

			std::string str11, str12;
			str11.insert(str11.end(), str1.begin() + num, str1.end());
			str12.insert(str12.end(), str1.begin(), str1.begin() + num);
			std::cout << "str1匹配子串开始之后的内容为：" << str11 << std::endl;
			std::cout << "str12 == " << str12 << std::endl;
		}
	}

 
	namespace C_PROGRAMMING
	{
		// FILE IO:
		void test0()
		{
			const char* fileName = "G:\\gitRepositories\\SimplifiedQSlimLibrary-master\\data\\fish.ply";
			FILE* filePtr = fopen(fileName, "r");
			if (0 == filePtr)
				std::cout << "文件打开失败, by C" << std::endl;

			std::ifstream fileIn(fileName);
			if (!fileIn)
				std::cout << "文件打开失败, by C++" << std::endl;

			char readStr[512];
			for (unsigned i = 0; i < 10; ++i)
			{
				fileIn.getline(readStr, 512);
				std::cout << readStr << std::endl;
			}

			std::cout << "finished." << std::endl;
		}


	}


	// 断言
	namespace ASSERT
	{
		// 
		void test0()
		{
			int a = 1;
			assert(a != 0 && "a == 0 is not allowed!");

			assert(false && "should not be here.");

			std::cout << "finished." << std::endl;
		}

	}
 
	 
	namespace TEST_NAN_INFINITY
	{
		// nan INFINITY
		void test1()
		{
			float num1 = INFINITY;			// C风格的无穷大
			float num2 = -INFINITY;
			float num3 = NAN;					// C风格的not a number;
			float num4 = -num3;

			float num11 = std::numeric_limits<float>::infinity();			// C++风格的无穷大；
			float num22 = -std::numeric_limits<float>::infinity();
			float num33 = std::numeric_limits<float>::quiet_NaN();			// C++风格的not a number;

			// 大小比较：常数和C风格的NAN比较，始终返回false; 但是C++风格的NAN貌似本质上还是个无穷大值； 
			debugDisp("(3 > num1) == ", 3 > num1);
			debugDisp("(3 > num11) == ", 3 > num11);
			debugDisp("(3 > num2) == ", 3 > num2);
			debugDisp("(3 > num22) == ", 3 > num22);
			debugDisp("(3 > num3) == ", 3 > num3);
			debugDisp("(3 < num3) == ", 3 < num3);
			debugDisp("(3 > num4) == ", 3 > num4);
			debugDisp("(3 < num4) == ", 3 < num4);
			debugDisp("(3 > num33) == ", 3 > num33);
			debugDisp("(3 < num33) == ", 3 < num33);

			// identity: 
			debugDisp("std::inf(num1) == ", std::isinf(num1));
			debugDisp("std::inf(num2) == ", std::isinf(num2));
			debugDisp("std::isnan(num3) == ", std::isnan(num3));
			debugDisp("std::isnan(num4) == ", std::isnan(num4));

			debugDisp("std::numeric_limits<decltype(3)>::has_infinity(num11) == ", \
				std::numeric_limits<decltype(num11)>::infinity() > num11);
			debugDisp("std::numeric_limits<decltype(3)>::has_infinity(num11) == ", \
				std::numeric_limits<decltype(num22)>::infinity() > num22);
			debugDisp("std::numeric_limits<decltype(3)>::has_infinity(num11) == ", \
				std::numeric_limits<decltype(num33)>::quiet_NaN() == num33);

			debugDisp("finished.");

		}

	}


	// 类型萃取：
	namespace TEST_TRAITS
	{
		void test1()
		{
			std::vector<int> numVec1{ 11, 22, 0, 89, -3, 12, 999 };
			auto iter = numVec1.begin();

			// std::is_same<>()——编译期检测两个类型是否相同
			int numI1 = 1;
			double numD1 = 0.9;
			auto ret11 = std::is_same<decltype(numI1), decltype(numD1)>();
			auto ret12 = std::is_same<double, decltype(numD1)>();
			debugDisp("std::is_same<decltype(numI1), decltype(numD1)>() == ", ret11);
			debugDisp("std::is_same<double, decltype(numD1)>() == ", ret12);
			debugDisp("return type11 == ", typeid(ret11).name());
			debugDisp("return type12 == ", typeid(ret12).name());
			debugDisp("\n\n");

			// 编译器检测一个对象是否是指针：
			int* numPtr1 = nullptr;
			auto ret21 = std::is_pointer<decltype(numI1)>::value;
			auto ret22 = std::is_pointer<decltype(numPtr1)>::value;
			debugDisp("std::is_pointer<decltype(numI1)>::value == ", ret21);
			debugDisp("std::is_pointer<decltype(numPtr1)>::value == ", ret22);
			debugDisp("return type21 == ", typeid(ret21).name());
			debugDisp("return type22 == ", typeid(ret22).name());


			debugDisp("finished.");
		}

	}


	// 异常
	namespace TEST_EXCEPTION
	{
		void foo(const int num)
		{
			if (num < 0)
				throw(std::out_of_range("invalid input."));

			debugDisp("input number ==", num);
		}

		void goo(const int num) noexcept
		{
			if (num < 0)
				throw(std::out_of_range("invalid input."));

			debugDisp("input number ==", num);
		}

		void test1()
		{
			try
			{
				goo(-1);
			}
			catch (const std::exception& e)
			{
				debugDisp(e.what());
			}

			debugDisp("finished.");
		}

	}


	// 位运算：
	namespace TEST_BIT
	{
		// std::bitset
		void test0()
		{
			constexpr unsigned NBIT = 32;
			constexpr std::bitset<NBIT> bit0 = 0x0;
			constexpr std::bitset<NBIT> bit1 = 0x2;
			constexpr std::bitset<NBIT> bit2 = 0x4;
			constexpr std::bitset<NBIT> bit3 = 0x8;
			constexpr std::bitset<NBIT> bit4 = 0x10;

			std::bitset<NBIT> tmpBit;
			std::cout << "tmpBit == " << tmpBit << std::endl;

			tmpBit.flip(2);
			std::cout << "tmpBit == " << tmpBit << std::endl;
			std::cout << "(tmpBit & bit2)  == " << (tmpBit & bit2) << std::endl;
			std::cout << "bit4.to_ulong() == " << bit4.to_ulong() << std::endl;
			std::cout << "operator == : (bit4 == 0x10) ? " << (bit4 == 0x10) << std::endl;
			std::cout << "operator == : (tmpBit == 0x10) ? " << (tmpBit == 0x10) << std::endl;

			std::cout << "finished." << std::endl;
		}


		// 左移、右移运算符；
		void test1()
		{
			// 左移(<<)运算，a << b表示把a的二进制位向左移动b位，低位用0补上。等价于做运算a *= std::pow(2, b);
			debugDisp("(1 << 3) == ", 1 << 3);					// B1左移3位得到B100 == 8 
			debugDisp("(2 << 3) == ", 2 << 3); 


			std::cout << "test1 finished." << std::endl;
		}


	}

	 
	// 变参模板
	namespace VAR_TEMP
	{
		// 自定义变参模板类Tuple
		template <typename... Types> class Tuple;

		//		递归终止
		template <>
		class Tuple<>
		{
		public:
			static unsigned int size()
			{
				return 0;
			}


		};


		//		递归递推
		template<typename T, typename... Types>
		class Tuple<T, Types...> : private Tuple<Types...>
		{
		protected:
			T m_head;
		public:
			Tuple() {}

			// 递归的构造函数
			Tuple(T h, Types... tail) :m_head(h), Tuple<Types...>(tail...) {}

			T head()
			{
				return m_head;
			}

			Tuple<Types...>& tail()
			{
				return *this;
			}


			// 递归求出Tuple中的元素个数。
			static unsigned int size()
			{
				return (1 + Tuple<Types...>::size());
			}

		};


		void testTuple()
		{
			Tuple<int, float, std::string, char>   t(1, 2.2, "haha", 'a');
			std::cout << t.head() << std::endl;
			std::cout << "类型个数为：" << t.size() << std::endl;

			auto t2 = t.tail();
			std::cout << t2.head() << std::endl;
			std::cout << "类型个数为：" << t2.size() << std::endl;


		}



		// 仿照项目中TVBuilderArgTuple类模板写的一个可变参数类模板。

		//		除了使用vector代替序列化数据对象，和resume()方法读取的是vector对象以外，其他都一样。
		template <typename... Types> class vecSet;

		template <>
		class vecSet<>
		{
		public:
			vecSet() {}
			~vecSet() {}

			template<typename TA>
			void resume(const std::vector<TA>& v)
			{}


			template <typename F>
			void travel(F f)
			{
				f();
			}

			void disp() {}

		};

		template <typename T, typename... Types>
		class vecSet<T, Types...> : protected vecSet<Types...>
		{
		private:
			std::vector<T> m_vec;
			vecSet<Types...> m_sub;


		public:
			vecSet() {}


			vecSet(const std::initializer_list<T>& list)
			{
				auto iter = list.begin();
				for (const T& elem : list)
				{
					m_vec.push_back(elem);
				}
			}


			~vecSet() {}


			template<typename TA>
			void resume(const std::vector<TA>& v)
			{
				TA elem;
				void* ptr1 = NULL;
				T* ptr2 = NULL;

				if (typeid(T).name() == typeid(TA).name())		// 若参数和成员数据m_vec是同一类型，则拷贝元素。		
				{
					for (auto iter = v.begin(); iter != v.end(); iter++)
					{
						elem = *iter;
						ptr1 = reinterpret_cast<void*>(&elem);
						ptr2 = reinterpret_cast<T*>(ptr1);
						this->m_vec.push_back(*ptr2);
					}
				}

				this->m_sub.resume(v);			// 子集合递归调用。
			}


			template <typename F>
			void travel(F f)				// f为函数子	
			{
				// 若vecSet对象只含一种类型，则可以传入普通的lambda表达式；
				// 若不止含一种类型，则传入的函数子应该定义为可变参数类。
				m_sub.travel([this, f](const Types& ... args)
					{
						f(m_vec, args ...);
					});

			}


			void disp()
			{
				for (auto elem : this->m_vec)
				{
					std::cout << elem << "  ";
				}
				std::cout << std::endl;

				this->m_sub.disp();				// 子集合递归调用。
			}


		};


		void testVecSet()
		{
			vecSet<int, double, std::string > vvv;
			std::vector<int> vi = { 1,2,3,4,5 };
			std::vector<double> vf = { 1.1, 2.2, 3.3, 4.4 };
			std::vector<std::string> vs = { "haha","hello","world" };

			vvv.resume(vi);
			vvv.resume(vf);
			vvv.resume(vs);

			vvv.disp();


			vecSet<int> vseti = vecSet<int>({ 11,22,33,44,55 });
			vseti.disp();


			vecSet<std::string> v;
			v.resume(vs);
			v.travel([](const std::vector<std::string>& vec_input)			// 此时v的成员数据m_vec类型是std::vector<std::string>，lambda表达式的形参类型要与之匹配。
				{
					std::cout << "遍历向量中的元素：" << std::endl;
					for (const std::string& elem : vec_input)
					{
						std::cout << elem << std::endl;
					}

				});


			// 自定义一个函数子类，使用可变参数类模板，生成函数子传入travel()函数看看是否能正常工作。

		}


		// a. 模板特化举例：
		// a.1 函数模板特化
		template <typename T>
		bool isEqual(T arg1, T arg2)
		{
			return arg1 == arg2;
		}


		template <>				// 函数模板isEqual的全特化
		bool isEqual(char* arg1, char* arg2)
		{
			return strcmp(arg1, arg2);
		}



		// test: 测试模板特化
		void test1()
		{
			std::cout << isEqual("ahahah", "wawaa") << std::endl;
			std::cout << isEqual("ahahah", "ahhah") << std::endl;

		}


	}

	 
	// 宏
	namespace TEST_MACRO
	{
		// 使用可变参数宏实现封装printf()的宏函数
#define DISP(fm, ...) printf(fm,__VA_ARGS__) 

		void test0()
		{
			DISP("hello, %d\n", 10);
			DISP("hello, %d, %d, %d, %d\n", 10, 22, 33, 44);

			// __COUNTER__自身计数器，编译器每碰到它一次，它就自增1。
			std::cout << __COUNTER__ << std::endl;
			std::cout << __COUNTER__ << std::endl;
		}

		// 操作系统相关的宏：
		void test1()
		{
#ifdef  _WIN32
			debugDisp("是WINDOWS系统程序。_WIN32 == ", _WIN32);			// WINDOWS环境下，不管是32位还是64位都定义了_WIN32

#ifdef  _WIN64
			debugDisp("是WINDOWS系统64位的程序。_WIN64 == ", _WIN64);			// 只在WINDOWS环境下的64位程序中定义；
#else 
			debugDisp("是WINDOWS系统32位的程序。");
#endif 
#endif 

#ifdef __APPLE__
#include <TargetConditionals.h>

#if defined(TARGET_OS_OSX)
			debugDisp("是MACOS系统程序。");
#elif TARGET_OS_IPHONE
			debugDisp("是iPhone程序。");
#else
			debugDisp("是other apple OS程序。");
#endif

#endif

			debugDisp("finished.");
		}

	}

	 

	// 函数返回引用
/*
	最大的好处——在内存中不产生返回值的副本
	返回的引用所绑定的变量一定是全局变量，不能是函数中定义的局部变量
*/


// sizeof()运算符
	namespace SIZEOF
	{
		// 一个value-like类
		struct myArr1
		{
			int arri[10];

			myArr1()
			{
				memset(&arri[0], 1, 10 * sizeof(int));
			}
		};


		// 一个pointer-like类
		struct myArr2
		{
			int* pData;

			myArr2()
			{
				this->pData = new int[10];
				memset(this->pData, 1, 10 * sizeof(int));
			}
		};


		// 封装了std::vector的类
		struct myArr3
		{
			std::vector<int> veci;
			myArr3()
			{
				this->veci.resize(10);
				memset(&(this->veci[0]), 1, 10 * sizeof(int));
			}
		};


		void test0()
		{
			int arri[10];
			int* pi = nullptr;
			std::vector<int> veci(10);
			myArr1 arri1;
			myArr2 arri2;
			myArr3 arri3;
			pi = &arri[0];

			std::cout << sizeof(arri) << std::endl;
			std::cout << sizeof(pi) << std::endl;
			std::cout << sizeof(veci) << std::endl;
			std::cout << sizeof(arri1) << std::endl;
			std::cout << sizeof(arri2) << std::endl;
			std::cout << sizeof(arri3) << std::endl;

			// 貌似vector也是一个pointer-like class，对象本身容量不大，只是一个指向堆内存数据的指针。
			std::cout << sizeof(std::vector<int>(1)) << std::endl;
			std::cout << sizeof(std::vector<int>(10000)) << std::endl;			// 不管std::vector容量多大，对象大小都是12个字节。
		}
	}

	 
	// 测试WINDOWS API:
	namespace TEST_WINDOWS_API
	{
		// 测试监视CPU和内存状态：
		void test0()
		{
			std::vector<int> intVec;
			int current_pid = 0;
			float cpu_usage_ratio = 0;
			float memory_usage = 0;
			current_pid = GetCurrentPid();												// or you can set a outside program pid
			std::cout << "current pid: " << current_pid << std::endl;

			cpu_usage_ratio = GetCpuUsageRatio(current_pid);
			memory_usage = GetMemoryUsage(current_pid);
			std::cout << "cpu usage ratio: " << cpu_usage_ratio * 100 << "%" << std::endl;
			std::cout << "memory usage: " << memory_usage << "MB" << std::endl;
			std::cout << std::endl << std::endl;

			intVec.resize(1000000, 42);
			cpu_usage_ratio = GetCpuUsageRatio(current_pid);
			memory_usage = GetMemoryUsage(current_pid);
			std::cout << "cpu usage ratio: " << cpu_usage_ratio * 100 << "%" << std::endl;
			std::cout << "memory usage: " << memory_usage << "MB" << std::endl;
			std::cout << std::endl << std::endl;

			for (int i = 0; i < 10; ++i)
			{
				std::vector<int> intVec2;
				intVec2.resize(1000000, 42);
				cpu_usage_ratio = GetCpuUsageRatio(current_pid);
				memory_usage = GetMemoryUsage(current_pid);
				std::cout << "cpu usage ratio: " << cpu_usage_ratio * 100 << "%" << std::endl;
				std::cout << "memory usage: " << memory_usage << "MB" << std::endl;
				std::cout << std::endl << std::endl;

				intVec2.clear();
				cpu_usage_ratio = GetCpuUsageRatio(current_pid);
				memory_usage = GetMemoryUsage(current_pid);
				std::cout << "cpu usage ratio: " << cpu_usage_ratio * 100 << "%" << std::endl;
				std::cout << "memory usage: " << memory_usage << "MB" << std::endl;
				std::cout << std::endl << std::endl;
			}

			std::vector<int> intVec3;
			for (int i = 0; i < 10; ++i)
			{
				intVec3.insert(intVec3.end(), intVec.begin(), intVec.end());
				cpu_usage_ratio = GetCpuUsageRatio(current_pid);
				memory_usage = GetMemoryUsage(current_pid);
				std::cout << "cpu usage ratio: " << cpu_usage_ratio * 100 << "%" << std::endl;
				std::cout << "memory usage: " << memory_usage << "MB" << std::endl;
				std::cout << std::endl << std::endl;
			}

			debugDisp("finished.");
		}


		void test00()
		{
			// launch some task to occupy cpu and memory
			for (int i = 0; i < 5; i++)
				std::thread([]
					{
						std::this_thread::sleep_for(std::chrono::milliseconds(10));
					}).detach();

					int current_pid = GetCurrentPid();												// or you can set a outside program pid
					float cpu_usage_ratio = GetCpuUsageRatio(current_pid);
					float memory_usage = GetMemoryUsage(current_pid);

					while (true)
					{
						std::cout << "current pid: " << current_pid << std::endl;
						std::cout << "cpu usage ratio: " << cpu_usage_ratio * 100 << "%" << std::endl;
						std::cout << "memory usage: " << memory_usage << "MB" << std::endl;

						std::this_thread::sleep_for(std::chrono::milliseconds(1000));
					}
		}


		// 
		void test1()
		{
			CString   cPath;
			std::string path;

			// GetModuleFileName()——获取当前进程加载的模块的路径。
			GetModuleFileName(NULL, cPath.GetBufferSetLength(MAX_PATH + 1), MAX_PATH);
			path = CT2CA{ cPath };
			debugDisp("当前运行模块的路径：", path);

			// CreateDirectory()——创建文件夹； 
			if (!CreateDirectory(L"E:/newDir1/", NULL))
				debugDisp("创建文件夹失败！");
			if (!CreateDirectory(L"E:/newDir2/", NULL))
				debugDisp("创建文件夹失败！");

			// RemoveDirectory()—— 删除文件夹；
			if (!RemoveDirectory(L"E:/newDir2"))
				debugDisp("删除文件夹失败！");

			debugDisp("finished.");
		}
	}


	// 测试本项目中的工具接口
	namespace TEST_WHEELS
	{
		void test0()
		{
			std::vector<int> vi{ 1,2,3,4,5,6 };

			auto valueUp = [](int& num)
			{
				num += 1;
			};

			traverseSTL(vi, valueUp);
			traverseSTL(vi, disp<int>{});
			revTraverseSTL(vi, disp<int>{});
		}
	}


	// 文件读写
	namespace FILEIO
	{
		typedef	struct TDline
		{
			std::string name;
			unsigned long tel;
			std::string address;
			void disp()
			{
				std::cout << "姓名：" << this->name << ", 电话号码：" << this->tel << "， 住址：" << this->address << std::endl;
			}
		}TDline;


		// 读写文件——write();
		void test0()
		{
			// 创建文件流对象。
			// 程序对文件的读是输入，写是输出
			// 也可以创建只写不读的文件流ofstream，和只读不写的文件流ifstream
			std::fstream ExpData;
			std::fstream ExpDataTxt;
			std::fstream TelDirectory("telephone_directory.dat", std::ios_base::out | std::ios_base::binary);
			std::fstream TelDirectoryTxt("telephone_directory.txt", std::ios_base::out);

			//		默认打开模式是文本模式，如果希望二进制模式要指定。
			ExpData.open("experiment_data.dat", std::ios_base::out | std::ios_base::binary);

			std::string str1 = "实验项目：氧气实验。\n 结果：反应后物质质量（单位:g）:";
			float fnum1 = 3.11;

			// 1.1 写二进制文件，基本类型变量——可以用write()方法写入，也可以用输出流运算符。
			ExpData << str1 << fnum1 << std::endl;
			ExpData.close();					// ！！操作完之后要关闭文件流

												// 1.2 写二进制文件，自定义类型变量——write()方法写入，或使用重载的输出流运算符。
												// write()方法
												/*
												basic_ostream& write( const char_type* s,		待写入的数据的头部指针，强转为char*
												std::streamsize count			待写入数据字节数。
												)

												？？？可以写自定义结构体实例，不可以写类对象；？？？为什么？
												*/
			TDline line1 = { "小明", 13688888888, "xx路xx号" };
			TelDirectory.write(reinterpret_cast<char*>(&line1), sizeof(line1));
			TelDirectory.close();

			// 1.3 写文本文件
			ExpDataTxt.open("experiment_data.txt", std::ios::out);
			ExpDataTxt << str1 << fnum1;
			ExpDataTxt.close();
			TDline line2 = { "小红", 13555555555, "xx路xx号" };
			TelDirectoryTxt.write(reinterpret_cast<char*>(&line2), sizeof(line2));
			TelDirectoryTxt.close();

			// 2.1 读文件——输入流运算符、getline()方法、read()方法; 推荐用read()方法
			// read()方法————二进制文件中读取数据。
			/*
			basic_istream& read( char_type* s,					接收读取数据的变量的头部指针，强转为char*
			std::streamsize count			读取输入的字节数。
			);
			*/
			TDline readLine;
			TelDirectory.open("telephone_directory.dat", std::ios_base::in | std::ios_base::binary);
			TelDirectory.read(reinterpret_cast<char*>(&readLine), sizeof(readLine));
			readLine.disp();
			TelDirectory.close();
		}


		// 读写文件seekg(), tellg(), read(), write(), is_open()
		void test1()
		{
			// 在文件中读写数组
			int iarr[10] = { 1,2,3,4,5,6,7,8,9,10 };

			std::fstream datafile;
			datafile.open("data.dat", std::ios::out | std::ios::binary);
			datafile.write(reinterpret_cast<char*>(&iarr), sizeof(iarr));
			datafile.close();

			int readInt[50];
			// std::fstream::seekg()
			// std::fstream::tellg()
			// 成员数据——beg, end;
			datafile.open("data.dat", std::ios::in | std::ios::binary);
			datafile.seekg(0, datafile.end);							// 追溯到流的尾部
			unsigned int size = datafile.tellg();						// 获取文件流的长度。
			datafile.seekg(0, datafile.beg);							// 回到流的头部	
			std::cout << "size == " << size << std::endl;

			int* pi = readInt;
			datafile.read(reinterpret_cast<char*>(&readInt[0]), size);

			for (const auto& elem : readInt)
				std::cout << elem << std::endl;

			// 文件中读写多个结构体实例
			TDline vline[3];
			vline[0] = { "小明", 123456, "上海" };
			vline[1] = { "小宏", 654321, "北京" };
			vline[2] = { "小蓝", 888888, "南宁" };
			std::cout << sizeof(vline) << std::endl;

			std::fstream telDirectory("telephone_directory.dat", std::ios_base::out | std::ios_base::binary);
			telDirectory.write(reinterpret_cast<char*>(&vline[0]), sizeof(vline));
			telDirectory.close();

			TDline vlineRead[10];
			telDirectory.open("telephone_directory.dat", std::ios_base::in | std::ios_base::binary);
			telDirectory.seekg(0, telDirectory.end);					//追溯到文件流的尾部
			unsigned int TDsize = telDirectory.tellg();				// 获取文件流的长度。
			telDirectory.seekg(0, telDirectory.beg);					//回到文件流的头部	
			std::cout << "TDsize == " << TDsize << std::endl;
			if (telDirectory.is_open())
			{
				std::cout << "读取telephone_directory.dat中..." << std::endl;
				telDirectory.read(reinterpret_cast<char*>(&vlineRead[0]), TDsize);
				std::cout << "读取完毕。" << std::endl;
			}
			vlineRead[0].disp();
			vlineRead[1].disp();
			vlineRead[2].disp();
		}


		// 读文本文件getline(); CString和c++字符串的转换；
		void test2()
		{
			std::wcout.imbue(std::locale(std::locale(), "", LC_CTYPE));	// 设置wcout的语言环境，缺少这一步打印中文会有错误。

			CString   sPath;
			GetModuleFileName(NULL, sPath.GetBufferSetLength(MAX_PATH + 1), MAX_PATH);
			std::wcout << (LPCTSTR)sPath << std::endl;

			// AllocSysString();
			wchar_t wPath[512] = { L'\0' };
			wchar_t* wPtr = &wPath[0];
			wPtr = sPath.AllocSysString();			// 不会拷贝结尾的L'\0'，所以上面手动写入；
			std::wcout << wPath << std::endl;

			std::ifstream file1("E:/workstation/smarteeproj/Exe/TstAlgorithm/cppTest/cppTest/testTxt.txt");
			if (!file1.is_open())
			{
				std::cout << "testTxt.txt打开失败。" << std::endl;
				return;
			}

			// 循环调用getline读取文本文件中的内容；
			std::cout << "循环调用getline读取文本文件中的内容：" << std::endl;
			char strRead[512] = { 0 };
			while (file1.getline(strRead, 512))		// 只要可以读到文件内容（包括空行），getline()返回值就一直是True；如果读取失败，那么会抛出相对应的异常。
				std::cout << strRead << std::endl;

			std::cout << "finished." << std::endl;
		}
	}

 
}
using namespace TEST_UNKNOWN;


////////////////////////////////////////////////////////////////////////////////////////////// C++新特性：
namespace TEST_NEW_FEATURES
{
	// 折叠表达式（C++17）（fold expression）
	namespace FOLDEXP
	{
		// 使用折叠表达式可以更加方便地实现可变参数模板
		template <typename ... Ts>
		auto mySum(Ts ... ts)
		{
			return (ts + ...);
		}

		void test0()
		{
			std::cout << mySum(1, 2, 3, 4, 5, 6) << std::endl;
			std::cout << mySum(std::string{ "hello" }, std::string{ " " }, std::string{ "world" }) << std::endl;
		}

	}


	// 常量表达式constexpr ( c++11)
	namespace CONSTEXPR
	{
		// constexpr修饰变量：限定该变量是编译期常量；而const变量可能是编译期常量也可能是运行期常量。
		void test0()
		{




		}

		// constexpr修饰函数：如果其传入的参数可以在编译时期计算出来，那么这个函数就会产生编译时期的值
		void test1()
		{

		}

	}


	//  c++11移动语义、右值引用、万能引用
	namespace MOVING
	{
		// 目的函数
		template<typename T>
		void showAttr(T& num)
		{
			std::cout << "是一个左值" << std::endl;
		}


		template<typename T>
		void showAttr(T&& num)
		{
			std::cout << "是一个右值" << std::endl;
		}


		// 输入参数为万能引用的转发函数——需要保证传入的引用转发之后性质不变。
		template <typename T>
		void passShowAttr(T&& num)
		{
			showAttr(std::forward<T>(num));
		}


		// 接收万能引用的函数要实现完美转发，需要用到std::forward()
		void test2()
		{
			int a = 1;

			passShowAttr(1);
			passShowAttr(a);
			passShowAttr(std::move(a));
			passShowAttr(a);	// std::move()内部做了强制转换，返回一个左值引用，但是并不改变变量a原先的类型。
		}


		// 自己实现的带有移动构造的类。
		class myString
		{
		private:
			char* c_str;

		public:
			myString() = delete;			// 禁用无参构造

			myString(const char* str)
			{
				unsigned len = strlen(str);
				this->c_str = new char[len + 1];
				memcpy(c_str, str, len + 1);
			}

			myString(const myString& str0)			// 拷贝构造
			{
				std::cout << "拷贝构造函数被调用。" << std::endl;
				char* pc = str0.getStr();
				unsigned num = strlen(pc) + 1;
				this->c_str = new char[num];
				memcpy(this->c_str, pc, num);

			}


			myString(myString&& str) noexcept		// 移动构造。
			{
				std::cout << "移动构造函数被调用" << std::endl;
				this->c_str = str.getStr();
				str.setStr(nullptr);
			}


			char* getStr() const
			{
				return this->c_str;
			}


			void setStr(char* pc)
			{
				this->c_str = pc;
			}


			void disp()
			{
				std::cout << this->c_str << std::endl;
			}

		};



		void test3()
		{
			myString str1("hahawawawa");
			myString str2(str1);
			myString str3(std::move(myString("hello world")));

			str1.disp();
			str2.disp();
			str3.disp();

			myString str4(std::move(str1));
			str4.disp();
			str1.disp();



		}


		// <utility>中判断左值右值引用的接口。
		template <typename T>
		void testRefAttr(T&& arg)
		{
			if (std::is_lvalue_reference<decltype(arg)>::value)
				std::cout << "是左值引用" << std::endl;
			else if (std::is_rvalue_reference<decltype(arg)>::value)
				std::cout << "是右值引用或右值" << std::endl;
			else
				std::cout << "？？？" << std::endl;

		}

		void test4()
		{
			int a = 3;
			testRefAttr(a);
			testRefAttr(5);
			testRefAttr(std::move(a));
		}



		// auto&&一定是万能引用：
		auto funcContainer = [](auto&& func, auto&& arg)	// 可以调用任意单参数函数的Lambda
		{
			return (std::forward<decltype(func)>(func))(std::forward<decltype(arg)>(arg));
		};

		void disp(const std::string& str)
		{
			std::cout << str << std::endl;
		}

		double Sqrt(double num)
		{
			return std::sqrt(num);
		}

		void test5()
		{
			funcContainer(disp, "hahahah");
			std::cout << funcContainer(Sqrt, 100) << std::endl;
		}

	}


	// 其他C++11及之后的新特性
	namespace MORDERN_CPP
	{
		// 使用using而不是typedef来创建类型别名
		template <typename T>
		using myPair = std::pair<T, T>;			// using可以创建模板的别名，typedef不可以
		void test1()
		{
			myPair<int> pi = std::make_pair(5, 6);

		}


		using VOIDP = void*;
		using pVV = VOIDP(*)(void);			// 这里如果不将void*打包成VOIDP将会编译报错。
		void* getNum()
		{
			int* pi = new int(999);
			return reinterpret_cast<void*>(pi);
		}

		void test2()
		{
			pVV pfuncV = nullptr;
			pfuncV = getNum;
			int* pi = nullptr;
			pi = reinterpret_cast<int*>((*pfuncV)());
			std::cout << *pi << std::endl;
		}

	}


	// 智能指针：
	namespace SMART_POINTER
	{
		// 智能指针
	/*
		make_shared()

		shared_ptr的常用接口
			use_count()
			unique()
			reset()

		unique_ptr的常用接口

	*/

		void test0()
		{
			// shared_ptr

			// make_shared<T>()——创建一个堆对象，返回其智能指针
			std::shared_ptr<int> pi1 = std::make_shared<int>(99);
			std::shared_ptr<int> pi2(pi1);

			// 类方法use_count()——显示指向对象被多少个智能指针共享
			std::cout << pi1.use_count() << std::endl;

			// get()——返回shared_ptr封装的指针；
			int* intPtr1 = pi1.get();
			std::cout << "*intPtr1 == " << *intPtr1 << std::endl;

			// 类方法unique()——是否独占指向对象

			// 类方法reset()——释放，或释放后指向别的对象。
			pi1.reset();
			std::cout << "pi1.use_count() == " << pi1.use_count() << std::endl;
			std::cout << "pi2.use_count() == " << pi2.use_count() << std::endl;

			int* intPtr2 = new int(88);
			pi2.reset(intPtr2);				// reset普通指针；
			std::cout << "*pi2 == " << *pi2 << std::endl;


			// 智能指针空了以后再reset()也不会有问题，普通堆对象的指针在delete之后再次delete会报错；
			pi1.reset();
			pi1.reset();
			pi1.reset();
			int* tempPtr = new int(100);
			delete tempPtr;
			// delete tempPtr;


			// 可以直接用if和!来判断只能指针是否为空；
			if (pi1)
				std::cout << "pi1不为空" << std::endl;
			else
				std::cout << "pi1为空" << std::endl;

			if (!pi2)
				std::cout << "pi2为空" << std::endl;
			else
				std::cout << "pi2不为空" << std::endl;



			// 智能指针接管传统指针，不要用智能指针指向栈对象，虽然指向的时候不报错，但是reset()的时候会产生异常。
			float* opf1 = new float(3.1415);
			std::shared_ptr<float> pf1(opf1);


			// unique_ptr

					// allocator<T>类模板
			std::allocator<char> ch_allo;
			ch_allo.allocate(9);			// 开辟堆内存，大小为9个char

		}
	}


}



////////////////////////////////////////////////////////////////////////////////////////////// STL
namespace TEST_STL 
{
	// C++线程支持库，并发编程相关的WINDOWS API
	namespace STD_THREAD
	{
		// test0()——c++线程支持库中的常用接口；
		void test0()
		{
			std::cout << "支持的并发线程数 : " << std::thread::hardware_concurrency() << std::endl;
			const static unsigned n_threads = std::thread::hardware_concurrency();
			if (0u == n_threads)
				return;

			std::cout << "finished." << std::endl;
		}


		// testWin1()——windows中的互斥锁g_hMutex；
#ifdef _WIN32

	// CreateThread()——WINDOWS中创建线程的API;
	/*
	*/


	// CreateEvent()——创建或打开一个事件对象；
	/*
		HANDLE CreateEvent(
				LPSECURITY_ATTRIBUTES	lpEventAttributes,			 对象安全属性——若为NULL，事件将获得一个默认的安全符。
				BOOL	bManualReset,							对象复位方式——若为TRUE，则必须用ResetEvent()手动将该事件的状态复原到无信号状态。
																									若为FALSE，则当一个线程等待到事件信号后， 系统会自动将该事件状态复原为无信号状态。
				BOOL	bInitialState,							对象初始状态——TRUE为有信号状态，FALSE为无信号状态；
				LPCTSTR	lpName								对象名称，NULL表示无名称；
		);

		若调用成功，函数返回事件对象的句柄。
				对于命名的对象，若在函数调用前已经被创建，将返回存在的事件对象的句柄，且在GetLastError函数中返回ERROR_ALREADY_EXISTS。
		若调用失败，返回值为NULL，如果需要获得详细的错误信息，需要调用GetLastError。
	*/


	// WaitForSingleObject()——等待单个事件对象；


	// WaitForMultipleObjects()——等待多个事件对象；
	/*
		DWORD WaitForMultipleObjects(
				DWORD dwCount,									等待的内核对象个数
				CONST HANDLE* phObjects,					一个数组，存放被等待的内核对象的句柄
				BOOL bWaitAll,										是否等到所有内核对象为已通知状态后才返回
				DWORD dwMilliseconds							等待时间
				);

		 bWaitAll如果为TRUE，则只有当等待的所有内核对象为已通知状态时函数才返回，如果为FALSE，则只要一个内核对象为已通知状态，则该函数返回。
		 若该函数失败，返回WAIT_FAILED；如果超时，返回WAIT_TIMEOUT；
		 若bWaitAll参数为TRUE——函数成功则返回WAIT_OBJECT_0
		 若bWaitAll为FALSE——函数成功则返回值指明是哪个内核对象收到通知。
	*/


	// CRITICAL_SECTION类——临界区锁类；

		HANDLE g_hMutex = NULL;			// 互斥量

		// 线程函数
		DWORD WINAPI Fun1(LPVOID lpParamter)
		{
			for (int i = 0; i < 5; i++)
			{
				//请求一个互斥量锁
				WaitForSingleObject(g_hMutex, INFINITE);
				std::cout << "子线程得到互斥锁。 i == " << i << std::endl;
				Sleep(100);

				//释放互斥量锁
				std::cout << "子线程释放互斥锁 " << std::endl;
				ReleaseMutex(g_hMutex);
			}

			return 0L;//表示返回的是long型的0
		}

		void testWin1()
		{
			// 1. 创建一个子线程、互斥锁。
			HANDLE hThread = CreateThread(NULL, 0, Fun1, NULL, 0, NULL);
			g_hMutex = CreateMutex(NULL, FALSE, L"screen");

			// 2. 关闭线程句柄
			if (hThread != nullptr)
				CloseHandle(hThread);

			// 3. 主线程的执行路径
			for (int i = 0; i < 5; i++)
			{
				// 请求获得一个互斥量锁
				if (g_hMutex != nullptr)
					WaitForSingleObject(g_hMutex, INFINITE);

				std::cout << "！主线程得到互斥锁。 i == " << i << std::endl;
				Sleep(100);

				// 释放互斥量锁
				if (g_hMutex != nullptr)
				{
					std::cout << "！主线程释放互斥锁 " << std::endl;
					ReleaseMutex(g_hMutex);
				}
			}
		}
#endif


		// test1()——std::thread线程类
		float genRandFloat(const unsigned sleepTime)
		{
			std::default_random_engine e;
			std::uniform_real_distribution<float> URD_f(-10, 10);

			std::stringstream ss;
			ss << "genRandFloat() is going to sleep " << sleepTime << " milliseconds\n";
			std::cout << ss.str();			// 整合进一个字符串然后输出，否则连续写入std::cout的过程可能会被中断

			Sleep(sleepTime);

			std::cout << "genRandFloat() finished.\n";

			return URD_f(e);
		}

		int genRandInt(const unsigned sleepTime)
		{
			std::default_random_engine e;
			std::uniform_int_distribution<int> URD_i(-10, 10);

			std::stringstream ss;
			ss << "genRandInt() is going to sleep " << sleepTime << " milliseconds\n";
			std::cout << ss.str();			// 整合进一个字符串然后输出，否则连续写入std::cout的过程可能会被中断

			Sleep(sleepTime);

			std::cout << "genRandInt() finished.\n";

			return URD_i(e);
		}

		bool genMultiRandInt(std::vector<int>& vec, const unsigned sleepTime = 1000)
		{
			std::default_random_engine e;
			std::uniform_int_distribution<int> URD_i(-10, 10);

			std::stringstream ss;
			ss << "genMultiRandInt() is going to sleep " << sleepTime << " milliseconds\n";
			std::cout << ss.str();			// 整合进一个字符串然后输出，否则连续写入std::cout的过程可能会被中断

			Sleep(sleepTime);
			vec.push_back(URD_i(e));
			vec.push_back(URD_i(e));
			vec.push_back(URD_i(e));

			std::cout << "genMultiRandInt() finished.\n";

			return true;
		}


		void test1()
		{
			// 1. 构造线程对象的参数可以是函数对象，也可以是lambda
			float numF1;
			int numI1;
			std::vector<int> numVec1;

			//		1.1 用lambda构造线程对象；其中使用lambda来读取线程函数的返回值；
			std::thread t1{ [&]()
				{
					numF1 = genRandFloat(1000);
			} };
			std::thread t2{ [&]()
				{
					numI1 = genRandInt(3000);
			} };

			//		1.1 不需要接受返回值的话，使用函数对象及其参数构造线程对象；
			std::thread t3{ genMultiRandInt, std::ref(numVec1), 2000 };					// 参数的引用类型会被忽略，希望传入引用的话需要使用std::ref();

			// 2. join()方法——等待本线程完成；具体来说是阻塞当前std::thread对象所在线程，直至该线程对象结束；
			t1.join();
			t2.join();
			t3.join();

			debugDisp("numF1 == ", numF1);
			debugDisp("numI1 == ", numI1);
			debugDisp("numVec1 == ");
			traverseSTL(numVec1, disp<int>());
			debugDisp("\n\n");

			debugDisp("finished.");
		}


		// test11()——C++标准库中的互斥锁：
		int g_num = 0;
		std::mutex g_mutex0;

		// 互斥锁实现的线程安全的写操作；
		void safe_increment_mutex()
		{
			std::lock_guard<std::mutex> lock(g_mutex0);			// mutex的封装类对象；该对象被析构时，封装的互斥锁自动释放；
			std::cout << "thread " << std::this_thread::get_id() << " start: " << std::endl;
			g_num++;
			std::cout << "thread " << std::this_thread::get_id() << " finished, g_num == " << g_num << std::endl;
		}

		// 非线程安全的写操作；
		void unsafe_increment()
		{
			std::cout << "thread " << std::this_thread::get_id() << " start: " << std::endl;
			g_num++;
			std::cout << "thread " << std::this_thread::get_id() << " finished, g_num == " << g_num << std::endl;
		}

		void test11()
		{
			std::vector<std::thread> threadPool;

			// 带锁
			threadPool.reserve(10);
			for (unsigned i = 0; i < 10; ++i)
				threadPool.emplace_back(safe_increment_mutex);
			for (auto& t : threadPool)
				t.join();

			std::cout << std::endl << std::endl;

			// 不带锁；
			threadPool.clear();
			g_num = 0;
			for (unsigned i = 0; i < 10; ++i)
				threadPool.emplace_back(unsafe_increment);
			for (auto& t : threadPool)
				t.join();

			debugDisp("finished.");
		}


		// test2()——测试多线程并发for循环;
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

			std::cout << "多线程测试开始：" << std::endl;	// 生成一组随机数，求和，赋值给numVec中的元素；
			tt.start();
			PARALLEL_FOR(0, elemCount, [&](const unsigned index)
				{
					for (auto& num : randVec)
						num = URD_f(e);
					numVec[index] = std::sqrt(std::accumulate(randVec.begin(), randVec.end(), 0));
				});
			tt.endCout("多线程耗时：");

# if 1
			// 单线程耗时为9s+
			std::cout << "单线程测试开始：" << std::endl;
			tt.start();
			for (unsigned i = 0; i < elemCount; ++i)
			{
				for (auto& num : randVec)
					num = URD_f(e);
				numVec[i] = std::sqrt(std::accumulate(randVec.begin(), randVec.end(), 0));
			}
			tt.endCout("单线程耗时：");
#endif 

			// 测试变参并行for 循环：
			float accumBase = 1.5;
			std::vector<float>* vecPtr = &randVec;
			std::tuple<float, std::vector<float>*> ptt = std::make_tuple(accumBase, vecPtr);
			PARALLEL_FOR(0, elemCount, [&](const unsigned index, const std::tuple<float, std::vector<float>*>& paramTuple)
				{
					std::vector<float>& randVec0 = *std::get<1>(paramTuple);
					float accumBase0 = std::get<0>(paramTuple);
					for (auto& num : randVec)
						num = URD_f(e);
					numVec[index] = std::sqrt(std::accumulate(randVec0.begin(), randVec0.end(), accumBase0));
				}, ptt);
			std::cout << "finished." << std::endl;
		}


		// test3()——测试原子操作：
		std::atomic<bool> g_readySignal(false);
		std::atomic<bool> g_winSignal(false);

		void count1m(int id)
		{
			std::stringstream ss1, ss2, ss3;
			ss1 << "thread # " << id << " joined.\n";			// 整合进一个字符串然后输出，否则连续写入std::cout的过程可能会被中断	
			printf(ss1.str().c_str());

			// 1. 等待开始信号：
			while (!g_readySignal)
			{
			}
			ss2 << "thread # " << id << " start racing.\n";
			printf(ss2.str().c_str());

			// 2. count for 1 million的循环：
			for (int i = 0; i < 1000000; ++i)
			{
			}

			// 3. 比赛结果：
			if (!g_winSignal.exchange(true))
			{
				// 第一个将原子变量g_winSignal由false赋值为true的线程才会走到这里；
				ss3 << "thread # " << id << " won!\n";
				printf(ss3.str().c_str());
			}
			else
			{
				ss3 << "thread # " << id << " finished.\n";
				printf(ss3.str().c_str());
			}
		};

		void test3()
		{
			std::vector<std::thread> threads;
			std::cout << "spawning 10 threads that count to 1 million...\n";

			for (int i = 1; i <= 10; ++i)
				threads.push_back(std::thread(count1m, i));

			g_readySignal = true;
			for (auto& th : threads)
				th.join();

			debugDisp("finished.");
		}


		// test4()——测试生产消费模式（互斥锁+条件变量）： 
		const int g_productSize = 5;			// 生产者数量	
		const int g_customerSize = 5;			// 消费者数量	
		const int g_maxSize = 10;				// 最大产品数量
		const int g_tarSize = 20;					// 销量目标
		std::mutex g_mutex;										// 互斥量
		std::condition_variable g_condition;				// 条件变量	
		std::queue<int> g_queue;								// 队列，模拟缓冲区
		int g_prodID = 1;												// 商品ID;
		bool blAllprodFinished = false;						// 生产线程是否已全部结束
		int g_prodFinishCount = 0;								// 已结束的生产线程数

		// 生产线程函数
		void Producer(const int tag)
		{
			std::stringstream ss;
			ss << "producer thread # p" << tag << " started.\n";
			printf(ss.str().c_str());					// 整合进一个字符串然后输出，否则连续写入std::cout的过程可能会被其他线程抢占；

			while (true)
			{
				std::unique_lock<std::mutex> lock(g_mutex);

				// w1. 若队列中的产品数达到设定的最大值，则当前生产线程进入阻塞等待状态；
				while (g_queue.size() >= g_maxSize)
					g_condition.wait(lock);		// 阻塞当前的线程，直到消费进程那边进行到条件变量g_condition放出通知notify_all()为止；									

				// w2. 获取产品ID
				int prodIDcur = g_prodID;
				if (prodIDcur > g_tarSize)
					prodIDcur = -1;
				if (prodIDcur < 0)
				{
					// w2i. 若获取产品ID失败，则退出当前生产线程；
					debugDisp("producer thread # p", tag, " finished.");
					g_prodFinishCount++;
					if (g_prodFinishCount >= g_productSize)
					{
						blAllprodFinished = true;
						debugDisp("all producer threads finished.");
					}
					return;
				}

				// w3. 开始生产：
				Sleep(100);
				g_queue.push(prodIDcur);
				g_prodID++;
				debugDisp("producer thread # p", tag, "生产了产品：#", prodIDcur);

				// w4. 生产了一个产品，通知消费线程可以开始消费；
				g_condition.notify_all();
			}
		}


		// 消费线程函数
		void Customer(const int tag)
		{
			std::stringstream ss;
			ss << "customer thread # c" << tag << " started.\n";
			printf(ss.str().c_str());

			while (true)
			{
				std::unique_lock <std::mutex> lock(g_mutex);

				// w1. 若队列中产品已耗尽，且生产线程并没有全部结束；则当前线程进入阻塞等待状态；
				while (g_queue.empty() && !blAllprodFinished)
					g_condition.wait(lock);			// 	阻塞当前的线程，直到生产进程那边进行到条件变量g_condition放出通知notify_all()为止；

				// w2. 取队列中的产品：
				int prodIDcur = -1;
				if (!g_queue.empty())
				{
					prodIDcur = g_queue.front();
					g_queue.pop();
				}
				if (prodIDcur < 0)
				{
					// w2i. 若取产品失败，则退出当前消费线程；
					debugDisp("customer thread # c", tag, " finished.");
					return;
				}

				// w3. 消费过程	
				debugDisp("customer thread # c", tag, "消费了产品：#", prodIDcur);
				Sleep(50);

				// w4. 消费了一个产品，通知生产线程可以开始生产
				g_condition.notify_all();
			}
		}


		void test4()
		{
			std::vector<std::thread> threadPool;				// 线程池；

			// 创建生产者和消费者线程：
			for (unsigned i = 0; i < g_productSize; ++i)
				threadPool.push_back(std::thread(Producer, i));

			for (unsigned i = g_productSize; i < g_productSize + g_customerSize; ++i)
				threadPool.push_back(std::thread(Customer, i - g_productSize));

			// 线程同步；
			for (unsigned i = 0; i < g_productSize + g_customerSize; ++i)
				threadPool[i].join();

			debugDisp("finished.");
		}
	}



	namespace STL_LIST
	{
		void test1()
		{
			// std::list是双向链表，任意位置插入、删除都很方便。
			std::list<int> l1{ 1,2,3,4,5,6,7 };
			std::vector<int> v1{ -1, -2, -3, -4 };
			auto iter1 = l1.begin();
			auto iter2 = l1.begin();
			auto iter3 = l1.begin();

			iter2++;
			for (int i = 0; i < 3; ++i)
			{
				iter3++;
			}
			std::cout << "*iter1 == " << *iter1 << std::endl;
			std::cout << "*iter2 == " << *iter2 << std::endl;
			std::cout << "*iter3 == " << *iter3 << std::endl;
			l1.insert(iter1, 999);														// 插在当前迭代器指向位置的前面；

			traverseSTL(l1, disp<int>{});
			std::cout << "*iter1 == " << *iter1 << std::endl;
			std::cout << "*iter2 == " << *iter2 << std::endl;		// 任意插入删除操作都不会使迭代器失效。
			std::cout << "*iter3 == " << *iter3 << std::endl;

			l1.insert(iter3, v1.begin(), v1.end());
			traverseSTL(l1, disp<int>{});
			std::cout << "*iter1 == " << *iter1 << std::endl;
			std::cout << "*iter2 == " << *iter2 << std::endl;		// 任意插入删除操作都不会使迭代器失效。
			std::cout << "*iter3 == " << *iter3 << std::endl;


			// 支持首尾端压入、删除元素——push_front, pop_front(), push_back(), pop_back();



		}
	}


	namespace STL_SET_MAP
	{
		// 1. std::set的insert方法
		void test1()
		{
			// std::set的insert方法返回一个pair，第一项是插入元素的迭代器，第二项是指示是否插入成功的BOOL值
			std::set<int> numSet1;
			auto retPair = numSet1.insert(1);
			auto iter = retPair.first;
			std::cout << "*iter == " << *iter << std::endl;
			std::cout << "retPair.second == " << retPair.second << std::endl;

			// 插入失败的话，返回阻止插入的元素的迭代器；
			retPair = numSet1.insert(1);
			std::cout << "*retPair.first ==  " << *retPair.first << std::endl;
			std::cout << "retPair.second == " << retPair.second << std::endl;

			std::map<int, double > numMap;
			numMap.insert({ 1, 1.0 });
			numMap.insert({ 2, 2.0 });
			numMap.insert({ 3, 3.0 });
			numMap.insert({ 4, 4.0 });
			auto ret = numMap.insert({ 5, 5.0 });
			if (ret.second)
				std::cout << "first insert succeeded: " << ret.first->first << ", " << ret.first->second << std::endl;
			ret = numMap.insert({ 1, 1.1 });
			if (ret.second)
				std::cout << "second insert succeeded: " << ret.first->first << ", " << ret.first->second << std::endl;
		}


		// set和map中的自定义比较器：
		struct edgeComparator			// 严格弱序(strict weak ordering)比较器
		{
		public:
			bool operator()(const std::pair<int, int>& edge1, const std::pair<int, int>& edge2) const
			{
				if (edge2.first < edge1.first)
					return true;
				else if (edge2.first > edge1.first)
					return false;
				else
				{
					if (edge2.second < edge1.second)
						return true;
					else
						return false;
				}
			}
		};


		// 2. 自定义比较器
		void test2()
		{
			// 创建非基本类型的set和map，需要传入自定义比较器;
			std::set<std::pair<int, int>, edgeComparator> edgeSet1;

			auto retPair1 = edgeSet1.insert({ 1,  2 });
			retPair1 = edgeSet1.insert({ 2, 3 });
			retPair1 = edgeSet1.insert({ -1, 0 });
			retPair1 = edgeSet1.insert({ -2, -1 });
			retPair1 = edgeSet1.insert({ 1, 3 });
			retPair1 = edgeSet1.insert({ 1, 2 });
			std::cout << "retPair1.second == " << retPair1.second << std::endl;
			for (const auto& pair : edgeSet1)
				std::cout << pair.first << ", " << pair.second << std::endl;
			std::cout << std::endl;

			// 作为比较器的lambda: 
			auto edgeComLambda = [](const std::pair<int, int>& edge1, const std::pair<int, int>& edge2) ->bool
			{
				if (edge2.first < edge1.first)
					return true;
				else if (edge2.first > edge1.first)
					return false;
				else
				{
					if (edge2.second < edge1.second)
						return true;
					else
						return false;
				}
			};
			std::set<std::pair<int, int>, decltype(edgeComLambda)> edgeSet2;			// 模板参数是类型名；
			auto retPair2 = edgeSet2.insert({ 1,  2 });
			retPair2 = edgeSet2.insert({ 2, 3 });
			retPair2 = edgeSet2.insert({ -1, 0 });
			retPair2 = edgeSet2.insert({ -2, -1 });
			retPair2 = edgeSet2.insert({ 1, 3 });
			retPair2 = edgeSet2.insert({ 1, 2 });
			std::cout << "retPair1.second == " << retPair2.second << std::endl;
			for (const auto& pair : edgeSet2)
				std::cout << pair.first << ", " << pair.second << std::endl;
			std::cout << std::endl;


			std::cout << "finished." << std::endl;
		}


		// 3. multiset , multimap
		void test3()
		{
			std::multiset<int> set1;
			std::multimap<char, int> map1;
			std::unordered_multimap<char, double> map2;
			{
				set1.insert(2);
				set1.insert(99);
				set1.insert(3);
				set1.insert(1);
				set1.insert(1);							// 可以插入重复元素；
				map1.insert({ 'a', 1 });
				map1.insert({ 'a', -1 });
				map1.insert({ 'a', -1 });				// 可以插入重复元素；
				map1.insert({ 'a', 10 });
				map1.insert({ 'a', 11 });
			}

			// 1. count()方法——返回multiset中某一个元素重复的次数，multimap中某一个键对应的值的个数；
			debugDisp("set1.count(1) == ", set1.count(1));
			debugDisp("map1.count('a') == ", map1.count('a'));
			auto iter = map1.find('a');
			for (unsigned i = 0; i < map1.count('a'); ++i)			// 遍历某个键对应的所有值：
				disp<int>{}((iter++)->second);							// 同一个键的值对象按插入顺序排列
			debugDisp("\n");

			// 2. 迭代器
			std::multiset<int>::iterator iterS1 = set1.begin();
			std::multimap<char, int>::iterator iterM1 = map1.begin();
			int minElem = *iterS1;
			std::pair<const char, int> pair1 = *iterM1;
			debugDisp("minElem == ", minElem);
			debugDisp("pair1.first == ", pair1.first, "; pair1.second == ", pair1.second);

			// 3. erase()方法——
			iter = map1.find('a');
			iter = map1.erase(iter);									// 返回后一位键值对的迭代器；
			for (unsigned i = 0; i < map1.count('a'); ++i)		 
				disp<int>{}((iter++)->second);		 
			debugDisp("\n");

			debugDisp("test3() finished.");
		}


		// 4. 基于哈希表的无序容器：unordered_set, unordered_map, unordered_multiset, unordered_multimap;
		void test4()		// 插入和搜索的时间复杂度为O(1)
		{
			std::unordered_multimap<int, double> numMap;
			numMap.insert({ 1, 1.1 });
			numMap.insert({ 2, 1.1 });
			numMap.insert({ 1, 1.4 });
			numMap.insert({ 1, 1.3 });
			numMap.insert({ 1, -1.1 });
			numMap.insert({ 2, 2.3 });
			numMap.insert({ 1, 1.1 });			// 可以存入相同的键值对；

			// std::unordered_multimap查找key:
			std::cout << "numMap1.count(1) == " << numMap.count(1) << std::endl;
			auto iter = numMap.find(1);

			// 桶管理方法：
			std::cout << "numMap.bucket_count() == " << numMap.bucket_count() << std::endl;			// 桶的数目；

			// bucket()方法，返回桶的下标。不过貌似没什么意义，因为不能通过下标来访问桶对应的元素；
			unsigned bukIdx0 = numMap.bucket(2);
			std::cout << "numMap.bucket(2) == " << numMap.bucket(2) << std::endl;
			std::cout << "numMap.bucket_size(bukIdx0) == " << numMap.bucket_size(bukIdx0) << std::endl;

			// 对每个桶的遍历：
			for (auto iter = numMap.begin(); iter != numMap.end(); ++iter)
				std::cout << iter->first << ", " << iter->second << std::endl << std::endl;;

			// 删除操作：
			std::cout << "erase:	" << std::endl;
			for (auto iter = numMap.begin(); iter != numMap.end(); ++iter)
			{
				if (1 == iter->first && 1.4 == iter->second)
					iter = numMap.erase(iter);
			}
			for (auto iter = numMap.begin(); iter != numMap.end(); ++iter)
				std::cout << iter->first << ", " << iter->second << std::endl << std::endl;

			std::cout << "erase:	" << std::endl;
			for (auto iter = numMap.begin(); iter != numMap.end(); ++iter)
			{
				if (1 == iter->first && 1.1 == iter->second)
				{
					iter = numMap.erase(iter);
					break;				// 一次只能删除一个值；
				}
			}
			for (auto iter = numMap.begin(); iter != numMap.end(); ++iter)
				std::cout << iter->first << ", " << iter->second << std::endl << std::endl;;

			std::cout << "finished." << std::endl;
		}


		// 5. 自定义哈希函数；貌似使用自定义哈希函数生成unordered_set和unordered_map时间效率很低，远不如基于基本类型的
		class edgeHash	// 自定义哈希函数
		{
		public:
			std::size_t operator()(const std::pair<int, int>& edge) const
			{
				return (std::hash<int>()(edge.first) + std::hash<int>()(edge.second));
			}
		};

		class edgeEqual	// 自定义等价比较器：
		{
		public:
			bool operator()(const std::pair<int, int>& edge1, const std::pair<int, int>& edge2) const
			{
				return (edge1.first == edge2.first && edge1.second == edge2.second);
			}
		};


		void test5()
		{
			// 
			std::unordered_set < std::pair<int, int>, edgeHash, edgeEqual> edgeSet1;

			auto retPair1 = edgeSet1.insert({ 1,  2 });
			retPair1 = edgeSet1.insert({ 2, 3 });
			retPair1 = edgeSet1.insert({ -1, 0 });
			retPair1 = edgeSet1.insert({ -2, -1 });
			retPair1 = edgeSet1.insert({ 1, 3 });
			retPair1 = edgeSet1.insert({ 1, 2 });
			std::cout << "retPair1.second == " << retPair1.second << std::endl;
			for (const auto& pair : edgeSet1)
				std::cout << pair.first << ", " << pair.second << std::endl;
			std::cout << std::endl;

			// std::pair<int, int>表示的边的自定义哈希函数；
			auto edgeHashLamb = [](const std::pair<int, int>& edge)->std::size_t
			{
				return (std::hash<int>()(edge.first) + std::hash<int>()(edge.second));
			};

			// std::pair<int, int>表示的边的等价比较器；
			auto edgeComLamb = [](const std::pair<int, int>& edge1, const std::pair<int, int>& edge2)->bool
			{
				return (edge1.first == edge2.first && edge1.second == edge2.second);
			};

			std::unordered_set < std::pair<int, int>, decltype(edgeHashLamb), decltype(edgeComLamb)> edgeSet2;			// 模板参数是类型名；
			auto retPair2 = edgeSet2.insert({ 1,  2 });
			retPair2 = edgeSet2.insert({ 2, 3 });
			retPair2 = edgeSet2.insert({ -1, 0 });
			retPair2 = edgeSet2.insert({ -2, -1 });
			retPair2 = edgeSet2.insert({ 1, 3 });
			retPair2 = edgeSet2.insert({ 1, 2 });
			std::cout << "retPair1.second == " << retPair2.second << std::endl;
			for (const auto& pair : edgeSet2)
				std::cout << pair.first << ", " << pair.second << std::endl;
			std::cout << std::endl;


			std::cout << "finished." << std::endl;
		}


		// 6. 哈希表的插入操作貌似不是线程安全的：
		void test6()
		{
			std::default_random_engine e;
			std::uniform_int_distribution<unsigned int>	UID_ui(1, 100);
			std::unordered_set<unsigned> set0;
			//PARALLEL_FOR(0, 1000, [&](const unsigned i) 
			//	{
			//		set0.insert(UID_ui(e));
			//	});

			for (unsigned i = 0; i < 1000; ++i)		// 貌似对unordered_set的插入操作不是线程安全的；
				set0.insert(UID_ui(e));

			traverseSTL(set0, disp<unsigned>{});

			std::cout << "finished." << std::endl;
		}


		// 7. key_type, mapped_type, value_type
		void test7()
		{
			using AsciiMap = std::map<char, int>;
			AsciiMap::key_type c1;
			AsciiMap::mapped_type num1;
			AsciiMap::value_type pair1;						// std::pair<const char, int>类型，注意前一项是const
			debugDisp("AsciiMap::key_type的类型为：", typeid(c1).name());
			debugDisp("AsciiMap::mapped_type的类型为：", typeid(num1).name());
			debugDisp("AsciiMap::value_type的类型为：", typeid(pair1).name());

			debugDisp("test7() finished.");
		}
	}


	namespace STL_STACK_QUEUE
	{
		// 优先队列priority_queue（C++11）
		void test1()
		{
			// 自定义的std::string的优先级比较器——字符越多优先级越高；
			auto strPriCmp = [](const std::string& str1, const std::string& str2)->bool
			{
				if (str1.size() < str2.size())
					return true;
				else
					return false;
			};

			std::priority_queue<std::string, std::vector<std::string>, decltype(strPriCmp)> pQueue1;
			pQueue1.push(std::string("asdfasdf"));
			pQueue1.push(std::string("a1212sdfasdf"));
			pQueue1.push(std::string("asdf"));
			pQueue1.push(std::string("110df"));
			pQueue1.push(std::string("a"));
			pQueue1.push(std::string("asdsdfasdfasdfasdfafasdf"));

			while (!pQueue1.empty())
			{
				std::cout << pQueue1.top() << std::endl;
				pQueue1.pop();
			}

			std::cout << "finished." << std::endl;
		}

	}


	// STL算法库
	namespace STL_ALGORITHM
	{
		// std::find()
		void test0()
		{
			std::vector<int> veci{ 1,2,3,4,5,6 };

			if (veci.end() != std::find(veci.begin(), veci.end(), 1))
			{
				std::cout << "找到1" << std::endl;
			}

			if (veci.end() != std::find(veci.begin(), veci.end(), 0))
			{
				std::cout << "找到0" << std::endl;
			}



		}


		// STL算法库中的std::sort()
		void test00()
		{
			std::vector<float> numVec{ 1,-2,3,-4, 5,10,7,6, 9,-1 };
			std::map<float, unsigned> sortInfo;
			for (unsigned i = 0; i < numVec.size(); ++i)
			{
				sortInfo.insert(std::make_pair(numVec[i], i));
			}

			// std::sort(numVec.begin(), numVec.end());

			std::vector<float> sortedNum;
			std::vector<unsigned> sortedIdx;
			for (const auto& pair : sortInfo)
			{
				sortedNum.push_back(pair.first);
				sortedIdx.push_back(pair.second);
			}

			traverseSTL(sortedNum, disp<float>{});
			traverseSTL(sortedIdx, disp<unsigned>{});
		}


		// 比较器comparer
		void test1()
		{
			std::string str1, str2;
			str1 = "hahah";
			str2 = "hahahahha";
		}


		// std::copy()函数
		void test2()
		{
			// 复制栈上的数组
			int arri1[5] = { 1,2,3,4,5 };
			int arri2[5];
			std::copy(std::begin(arri1), std::end(arri1), arri2);
			debugDisp("arri2 == ");
			for (const auto elem : arri2)
				std::cout << elem << ", ";
			std::cout << std::endl;

			// 貌似不能复制std::vector，会编译报错；

			//std::vector<int> vec1{1, 2, 3, 4, 5}, vec2;
			//std::copy(vec1.begin(), vec1.end(), vec2);
			//debugDisp("vec2 == ");
			//traverseSTL(vec2, disp<int>());

			debugDisp("finished.");
		}


		// back_inserter()尾插入迭代器， fill_n()
		void test3()
		{
			std::vector<int> vi{ 1, 2, 3, 4, 5, 6 };
			std::fill_n(back_inserter(vi), 5, 999);		//  

			traverseSTL(vi, disp<int>{});
			std::cout << std::endl;
		}


		// 谓词(predicate)——可调用的表达式，如函数子、函数指针。	排序算法
		void test4()
		{
			std::vector<myString> strVec{ myString("sdsaasdfasdf"), myString("hahaha"), myString("j"), myString("kjasjdliuppoiulkj;l") };

			// std::sort()——传入自定义比较器，有小到大排序
			std::sort(strVec.begin(), strVec.end(), myComparer);
			traverseSTL(strVec, dispMyString);

		}


		// xxx_if算法——参数中包含谓词，进行条件判断，只对符合条件的元素进行操作
		void test5()
		{
			std::vector<int> vi{ 1,2,3,-1,99,-3,22,88,-9 };
			auto isNeg = [](const int& num)->bool
			{
				if (num < 0)
				{
					return true;
				}
				return false;
			};

			auto iter = find_if(vi.cbegin(), vi.cend(), isNeg);
			std::cout << *iter << std::endl;
			traverseSTL(vi, disp<int>{});


			// find_if()配合容器自身的erase()方法，删除满足指定条件的元素。
			iter = find_if(vi.cbegin(), vi.cend(), isNeg);
			while (iter != vi.end())
			{
				vi.erase(iter);
				iter = find_if(vi.cbegin(), vi.cend(), isNeg);
			}
			traverseSTL(vi, disp<int>{});

			// 应用场景——一堆字符串按照字符数是否大于5，分到两个容器中：
			std::vector<std::string> vecStr{ "asdfasdfadf","haha","helloworld","wawaawa","a","la" };
			std::vector<std::string> vecStr1, vecStr2;
			auto isLongStr = [](const std::string& str)->bool
			{
				if (str.length() > 5)
					return true;
				else
					return false;
			};
			auto it = find_if(vecStr.begin(), vecStr.end(), isLongStr);
			while (it != vecStr.cend())
			{
				vecStr2.push_back(*it);
				vecStr.erase(it);
				it = find_if(vecStr.begin(), vecStr.end(), isLongStr);
			}
			vecStr1 = std::move(vecStr);
			traverseSTL(vecStr1, disp<std::string>{});
			traverseSTL(vecStr2, disp<std::string>{});

		}


		// test: <algorithm>:merge(), <iterator>:back_insert()
		void test6()
		{
			std::vector<int> v1{ 1,2,3 }, v2{ 4, 5, 6 }, dst{ 9,9,9 };

			debugDisp("dst == ");
			merge(v1.begin(), v1.end(), v2.begin(), v2.end(), std::back_inserter(dst));
			traverseSTL(dst, disp<int>());

			v2.insert(v2.end(), v1.begin(), v1.end());
			debugDisp("v2 == ");
			traverseSTL(v2, disp<int>());

			debugDisp("finished.");
		}


		//  std::distance()————<iterator>， 反向迭代器。
		void test7()
		{
			std::vector<int> vi{ 1,2,3,4,5,6,7,8,9 };
			auto iter1 = vi.cbegin() + 2;
			auto iter2 = vi.crbegin();


			// distance()的两个参数应该是相同类型的迭代器。
			std::cout << "*iter1 == " << *iter1 << std::endl;
			std::cout << distance(vi.cbegin(), iter1) << std::endl;		// distance()返回值——可以理解为前面一个迭代器往后移多少位和后面那个迭代器重合。
			std::cout << distance(iter1, vi.cend()) << std::endl;
			std::cout << distance(vi.crbegin(), iter2) << std::endl;


			// 反向迭代器：
			iter2++;
			std::cout << "*(vi.crend() -1 ) == " << *(vi.crend() - 1) << std::endl;
			std::cout << "*iter2 == " << *iter2 << std::endl;
			std::cout << distance(vi.crbegin(), iter2) << std::endl;
			std::cout << distance(iter2, vi.crend()) << std::endl;


		}


		// std::swap()——交换容器中两个元素的位置；
		void test8()
		{
			// 交换容器中的元素；
			std::vector<int> vec{ 1,2,3,4,5,6,7,8,9 };
			auto iter1 = vec.begin();
			auto iter2 = vec.begin() + 1;
			std::swap(*iter1, *iter2);
			traverseSTL(vec, disp<int>{});

		}


		// std::count()——统计容器中某元素重复的次数；
		void test9()
		{
			std::vector<int> vec{ 1,2,3,4,5,6,7,8,9,1,2,3,4,4,3,1,2 };
			int result = std::count(vec.begin(), vec.end(), 2);
			std::cout << "2在迭代器范围内出现的次数：" << result << std::endl;
		}


		// std::unique()——移除毗邻的重复元素：
		void test10()
		{
			tiktok& tt = tiktok::getInstance();
			std::vector<int> numVec1{ 1,1,2,3,3,4,4,5,6,7 };
			std::vector<int> numVec2;

			// 1. numVec1中的元素被重排，numVec1.begin()~ret之间的元素为unique元素；ret之后的元素是随机的
			auto retIter = std::unique(numVec1.begin(), numVec1.end());
			numVec2.insert(numVec2.end(), numVec1.begin(), retIter);
			int uniqueCount = std::distance(numVec1.begin(), retIter);
			debugDisp("uniqueCount == ", uniqueCount);
			debugDisp("numVec2 == ");
			traverseSTL(numVec2, disp<int>());

			// 2. 可以先排序再调用unique()，再删除retIter之后的元素，从而删除所有重复元素：
			numVec1 = std::vector<int>{ 1,1,2,3,3,4,4,5,6,7 };
			std::sort(numVec1.begin(), numVec1.end());
			retIter = std::unique(numVec1.begin(), numVec1.end());
			numVec1.erase(retIter, numVec1.end());
			debugDisp("numVec1 == ");
			traverseSTL(numVec1, disp<int>());

			// 3. 比较sort+unique方法和使用std::unordered_set方法的速度——前者更快；
			std::default_random_engine e;												// 随机数生成器的引擎对象
			std::uniform_int_distribution<int> URD_I(0, 100);
			std::unordered_set<int> tmpSet;
			const int numCount = 1e6;
			numVec1.resize(numCount);
			for (auto& num : numVec1)
				num = URD_I(e);
			numVec2 = numVec1;

			tt.start();
			std::sort(numVec1.begin(), numVec1.end());
			retIter = std::unique(numVec1.begin(), numVec1.end());
			numVec1.erase(retIter, numVec1.end());
			tt.endCout("sort() + unique()方法耗时：");

			tt.start();
			for (const auto& num : numVec2)
				tmpSet.insert(num);
			numVec2.clear();
			numVec2.insert(numVec2.end(), tmpSet.begin(), tmpSet.end());
			tt.endCout("使用unordered_set的方法耗时：");


			std::cout << "finished." << std::endl;
		}
	}
	 

	// std::function
	namespace STD_FUNCTION
	{
		bool foo(const int num)
		{
			if (num > 0)
				return true;
			else
				return false;
		}

		bool goo(const int num)
		{
			if (num > 0)
			{
				std::cout << "positive" << std::endl;
				return true;
			}
			else
			{
				std::cout << "non-positive." << std::endl;
				return false;
			}
		}

		void test0()
		{
			std::function<bool(const int)> func = foo;
			std::cout << "func(1 ) == " << func(1) << std::endl;

			func = goo;
			std::cout << "func(1 ) == " << func(1) << std::endl;


			auto lambda2 = [&](const int num)->int
			{
				return 3 * num;
			};
			std::function<int(const int)> func2 = lambda2;
			std::cout << "func2(1 ) == " << func2(1) << std::endl;

			std::cout << "finished." << std::endl;
		}
	}


	// 数值库
	namespace STD_NUMERIC
	{
		// std::numeric_limits<>模板类
		void test0()
		{
			// lowest()——； min()——； max()——
			std::cout
				<< "type\t│ lowest()\t│ min()\t\t│ max()\n"
				<< "bool\t│ "
				<< std::numeric_limits<bool>::lowest() << "\t\t│ "
				<< std::numeric_limits<bool>::min() << "\t\t│ "
				<< std::numeric_limits<bool>::max() << '\n'
				<< "uchar\t│ "
				<< +std::numeric_limits<unsigned char>::lowest() << "\t\t│ "
				<< +std::numeric_limits<unsigned char>::min() << "\t\t│ "
				<< +std::numeric_limits<unsigned char>::max() << '\n'
				<< "int\t│ "
				<< std::numeric_limits<int>::lowest() << "\t│ "
				<< std::numeric_limits<int>::min() << "\t│ "
				<< std::numeric_limits<int>::max() << '\n'
				<< "float\t│ "
				<< std::numeric_limits<float>::lowest() << "\t│ "
				<< std::numeric_limits<float>::min() << "\t│ "
				<< std::numeric_limits<float>::max() << '\n'
				<< "double\t│ "
				<< std::numeric_limits<double>::lowest() << "\t│ "
				<< std::numeric_limits<double>::min() << "\t│ "
				<< std::numeric_limits<double>::max() << '\n';
			std::cout << std::endl << std::endl;

			// std::numeric_limits<>::denorm_min()——最小非正规值；
			double eps = std::numeric_limits<double>::denorm_min();
			std::cout << (0 < eps) << std::endl;
			std::cout << (0 < eps / 2) << std::endl;

			// std::numeric_limits<>::infinity;
			std::cout << "std::numeric_limits<unsigned>::infinity() == " << std::numeric_limits<unsigned>::infinity() << std::endl;
			std::cout << "std::numeric_limits<int>::infinity() == " << std::numeric_limits<int>::infinity() << std::endl;
			std::cout << "std::numeric_limits<float>::infinity() == " << std::numeric_limits<float>::infinity() << std::endl;
			std::cout << "std::numeric_limits<double>::infinity() == " << std::numeric_limits<double>::infinity() << std::endl;

			std::cout << "finished." << std::endl;
		}
	}

}

 
 
///////////////////////////////////////////////////////////////////////////////////////////// 模板&模板元编程
namespace TEST_TEMPLATE
{
	namespace TEMPLATE1				// 模板作为元函数的输入：
	{
		template <template <typename> class T1, typename T2>
		struct Fun_			
		{
			using type = typename T1<T2>::type;			
		};

		// 元函数Fun<>——将输入的模板作用于输入的类型之上，返回得到的结果类型；
		/*
			参数1是一个模板；
			参数2是一个类型；
			返回值是一个类型；
			从函数式程序设计的角度来说，Fun<>是一个高阶函数；Fun(T1, t2) == T1(t2);
		*/
		template <template <typename> class T1, typename T2>
		using Fun = typename Fun_<T1, T2>::type;		

		Fun<std::remove_reference, int&> value0 = 1;					// 元函数Fun<>返回的类型是int；
	}

#if 0
	namespace TEMPLATE2		// 模板作为元函数的输出：
	{
		template <bool AddOrRemoveRef> struct Fun_;

		template <>
		struct Fun_<true>
		{
			template <typename T>
			using type = std::add_lvalue_reference<T>;
		};

		template <>
		struct Fun_<false>
		{
			template<typename T>
			using type = std::remove_reference<T>;
		};

		// 元函数Fun<>——
		/*
			输入为true时，输出的是函数模板std::add_lvalue_reference<>：为类型增加左值引用；
			输入为false是，输出的是函数模板std::remove_reference<>：去除类型中的引用；

		*/
		template<typename T>
			template <bool AddOrRemove>
		using Fun = typename Fun_<AddOrRemove>::template type<T>;

		template <typename T>
		using Res_ = Fun<false>;

		Res_<int&>::type value0 = 3;
	}
#endif

	namespace TEMPLATE3				// 容器模板：
	{
		template <int... Vals> struct IntContainer;


	}

	namespace TEMPLATE4
	{
		template <typename T>
		struct RemoveReferenceConst_
		{
		private:
			using inter_type = typename std::remove_reference<T>::type;			// 输入的类型，如果是引用的话则去除引用属性；

		public:
			using type = typename std::remove_const<inter_type>::type;			// 输出的类型，去除原有的const属性；
		};

		// 元函数RemoveReferenceConst<>——去除输入类型的引用属性和const属性；
		template <typename T>
		using RemoveReferenceConst = typename RemoveReferenceConst_<T>::type;

		RemoveReferenceConst<const float&> value0 = 4;
	}

	namespace TEMPLATE5			// 分支结构
	{
		struct A; struct B; struct C;

		template<typename T>
		struct Fun_ 
		{
			constexpr static size_t  value = 0;
		};

		template <typename T>
		constexpr size_t Goo = 0;

		// 特化1：
		template <>
		struct Fun_<A>
		{
			constexpr static size_t value = 1;
		};

		template <>
		constexpr size_t Goo<A> = 1;

		// 特化2：
		template <>
		struct Fun_<B>
		{
			constexpr static size_t value = 2;
		};

		template <>
		constexpr size_t Goo<B> = 2;

		constexpr size_t value0 = Fun_<B>::value;
 
	}

	void test0() 
	{
		templateTest("hahaha");
		templateTest(111);
	}

	// 测试TEMPLATE1——模板作为元函数的输入
	void test1() 
	{
		debugDisp("TEMPLATE1::value0 == ", TEMPLATE1::value0);
		debugDisp("typeid(TEMPLATE1::value0).name()== ", typeid(TEMPLATE1::value0).name());

		debugDisp("TEMPLATE4::value0 == ", TEMPLATE4::value0);
		debugDisp("typeid(TEMPLATE4::value0).name()== ", typeid(TEMPLATE4::value0).name());

		debugDisp("test1 finished.");
	}

	void test2() {}
	 
}



///////////////////////////////////////////////////////////////////////////////////////////// 第三方库
namespace TEST_THIRD_LIBS 
{
	namespace MY_BOOST
	{
		// 使用boost::tie()来解包：
		void test1()
		{
			// 1. 可以解包std::pair
			std::pair<int, double> p1{ -1, 3.14 };
			int numINT1 = 0;
			double numDB1 = 0;
			boost::tie(numINT1, numDB1) = p1;
			debugDisp("numINT1 == ", numINT1);
			debugDisp("numDB1 == ", numDB1);

			// 2. 可以解包std::tuple，但是貌似对std::tuple不好使
			boost::tuple<int, double, const char*> t1 = boost::make_tuple(2, 0.99, "hahaha");
			const char* pStr1 = nullptr;
			boost::tie(numINT1, numDB1, pStr1) = t1;
			debugDisp("numINT1 == ", numINT1);
			debugDisp("numDB1 == ", numDB1);
			debugDisp("pStr1 == ", pStr1);


			debugDisp("finished.");
		}

	}



}



///////////////////////////////////////////////////////////////////////////////////////////// 面向对象
namespace TEST_OOP 
{

	class String
	{
	private:
		char* dataStr = nullptr;

	public:
		String() {}
		String(const char* str0)
		{
			this->dataStr = new char[512];
			strcpy(this->dataStr, str0);
		}
		~String()
		{
			delete[] this->dataStr;
		}

		const char* getStr() const
		{
			return this->dataStr;
		}

		friend std::istream& operator >> (std::istream& is, String& str)
		{
			char tmpStr[512];
			is >> tmpStr;
			delete str.dataStr;
			str.dataStr = new char[512];
			strcpy(str.dataStr, tmpStr);
			return is;
		}

		friend std::ostream& operator<<(std::ostream& os, const String& str)
		{
			os << str.dataStr;
			return os;
		}
	};

	namespace PRIVATE
	{
		class foo
		{
		public:
			foo(const int num0) :num(num0)
			{}

			void disp()
			{
				std::cout << this->num << std::endl;
			}

			void goo1(int* p)
			{
				*p = 88;
			}

			void goo2()
			{
				int* ptr = &this->num;
				goo1(ptr);
				std::cout << this->num << std::endl;
			}

		private:
			int num;
		};

		void test1()
		{
			foo obj1(99);
			obj1.disp();
			obj1.goo2();
			obj1.disp();

		}

	}
	 
}

 

int main()
{    
	TEST_BIT::test1();

	// TEST_STL::STL_SET_MAP::test3();

	debugDisp("main() finished."); 

	return 0;
}