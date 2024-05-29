#pragma once
#include <iostream>
#include <algorithm>
#include <cstring>					// ��׼������
#include <iostream>				// ��׼������
#include <limits>					// ����
#include <cmath>					// ���ݺ���
#include <fstream>				// �ļ��������
#include <cctype>					// �ַ�����
#include <ctime>       				// ���ں�ʱ�亯��
#include <cstdlib>					// ��׼��
#include <cstdio>       			// ��׼�������
#include <iomanip>				// �����������ʽ����	
#include <cstdarg> 				// ֧�ֱ䳤��������	
#include <cassert>					// ֧�ֶ���
#include <chrono>

#include <vector>
#include <map>
#include <unordered_map>
#include <windows.h>
#include <io.h>
 
 
/////////////////////////////////////////////////////////////////////////////////////////////// �������ݽṹ��
namespace AUXILIARY
{
	// �궨�塢����
	#define DEFAULT_SIZE 1000			// ȱʡԪ�ظ���
	#define DEFAULT_INFINITY 1000000	// ȱʡ�����
	#define MAX_ERROR_MESSAGE_LEN 100
	#define MAX_PATH          260
	constexpr float VF_EPS = 0.0001f;
	constexpr float VF_EPS_2 = 0.000001f;
	constexpr float VF_MAX = 10000.0f;
	constexpr float VF_MIN = -10000.0f;

	// ��ʾ״̬��ö����
	enum Status {
		SUCCESS, FAIL, UNDER_FLOW, OVER_FLOW, RANGE_ERROR, DUPLICATE_ERROR,
		NOT_PRESENT, ENTRY_INSERTED, ENTRY_FOUND, VISITED, UNVISITED
	};


	// ģ����Ļ���
	struct virtualModule
	{
	protected:
		virtual void test0() {}
		virtual void test1() {}
		virtual void test2() {}
		virtual void test3() {}
		virtual void test4() {}
		virtual void test5() {}
		virtual void test6() {}
		virtual void test7() {}

	public:
		static virtualModule* p_moduleIns;
		virtual ~virtualModule() = default;
		void run(unsigned testID);
	};


	// �½���ĳ������
	struct virtualChap
	{
	public:
		virtualModule* pm;		// ��ǰ�鿴��ģ���ָ�룬��Ҫ��caller���Է��ʣ�
								//	to be optimized: ��ʵ���淶����������Ƴ���Ԫ��Ȼ����Ȼ����Ϊprotected��Ա
		static virtualChap* p_chapIns;
		virtual ~virtualChap();

		virtual void showModuleList() = 0;
		virtual bool selectModule(const int molEnum) = 0;
		virtual void runTest(const unsigned testID);
		bool isNullModule() const;
	};


	// Error�ࡪ���Զ����쳣��
	class Error
	{
	private:
		char message[MAX_ERROR_MESSAGE_LEN];		// �쳣��Ϣ

	public:
		Error(const char* mes = "һ�����쳣!");
		~Error(void) {};
		void Show() const;					// ��ʾ�쳣��Ϣ
	};


	// �Զ���pointer-like�ַ�����
	struct myString
	{
	private:
		const char* pc;
	public:
		myString() = delete;
		myString(const char* pc0) :pc(pc0) {}
		myString(const myString& str);	// Ӧ���Լ�ʵ�ֿ������캯�������ظ�ֵ���������ʵ�����������ϵͳ����ǳ�����Ŀ������캯����

		const char* c_str() const
		{
			return this->pc;
		}
	};

	// ��������inStream�������ո��Ʊ����ȡһ�ַ�
	char GetChar(std::istream& inStream = std::cin); 
}
using namespace AUXILIARY;


/////////////////////////////////////////////////////////////////////////////////////////////// debug��disp�ӿڣ�
namespace MY_DEBUG
{
	// ������baseTypePrinter������ӡ�������ͱ���
	class baseTypePrinter
	{
	public:
		baseTypePrinter() = default;

		template<typename T>
		void operator()(const T& arg)
		{
			std::cout << arg << "\t";
		}

	};


	// ������pairPrinter�������������Ǵ�ӡpair����
	class pairPrinter
	{
	private:
		unsigned int count = 0;

	public:
		pairPrinter() = default;

		template<typename T1, typename T2>
		void operator()(const std::pair<T1, T2>& p)
		{
			std::cout << "\t(" << p.first << ", " << p.second << ")";
			this->count++;
		}

		unsigned int getCount(void)
		{
			return this->count;
		}
	};


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


	// �������stl����
	template<typename T, typename F>
	void revTraverseSTL(T& con, F f)
	{
		std::for_each(con.rbegin(), con.rend(), f);
		std::cout << std::endl;
	}


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
	};



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


	// ����std::chrono���Զ����ʱ��
	using namespace std::chrono;
	class tiktok
	{
	private:
		tiktok() = default;
		tiktok(const tiktok&) {}
		~tiktok() = default;

	public:
		time_point<steady_clock> startTik;
		time_point<steady_clock> endTik;
		unsigned recordCount;
		std::vector<time_point<steady_clock>> records;

		static tiktok& getInstance()
		{
			static tiktok tt_instance;
			return tt_instance;
		}

		// ��ʼ��ʱ
		void start()
		{
			this->startTik = steady_clock::now();
			this->recordCount = 0;
			this->records.clear();
		}

		// ������ʱ������̨�ϴ�ӡʱ��������λΪ��
		void endCout(const char* str)
		{
			this->endTik = steady_clock::now();
			microseconds duration = duration_cast<microseconds>(this->endTik - this->startTik);
			std::cout << str << static_cast<double>(duration.count()) * \
				microseconds::period::num / microseconds::period::den << std::endl;
		}

		// ������ʱ������std::chrono::microseconds���͵�ʱ������
		microseconds endGetCount()
		{
			this->endTik = steady_clock::now();
			microseconds duration = duration_cast<microseconds>(this->endTik - this->startTik);
			return duration;
		}

		// ������ʱ��ʱ����д�뵽fileName���ı��ļ��У���λΪ�룻
		bool endWrite(const char* fileName, const char* str)
		{
			this->endTik = steady_clock::now();
			std::ofstream file(fileName, std::ios_base::out | std::ios_base::app);
			if (!file)
				return false;
			microseconds duration = duration_cast<microseconds>(this->endTik - this->startTik);
			file << str << static_cast<double>(duration.count()) * \
				microseconds::period::num / microseconds::period::den << std::endl;
			file.close();
			return true;
		}

		// ���������¼�˿̵�ʱ�̣�������this->records�����У�
		void takeArecord()
		{
			this->records.push_back(steady_clock::now());
			recordCount++;
		}
	};
}
using namespace MY_DEBUG;




	 





 





