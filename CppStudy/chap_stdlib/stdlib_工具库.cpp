#include <ctime>
#include <cstdio>
#include <typeinfo>
#include <chrono>

#include <iostream>
#include <string>
#include <typeinfo>

#include <cstdio>

#include "stdlib_���߿�.h"


#ifdef WIN32
#include <windows.h>
#endif

 
#define EPS 1e-10								//����ǳ�С��һ����EPSilon�������������������ֵʱ����Ϊ0
#define PI 3.14159


// C++��׼�⡪�����߿�
/*
	���߿���¿��Է�Ϊ���ࣺ����֧�ֿ⡢ͨ�ÿ�

	���ݣ�
		����ָ���������
		���ں�ʱ��
		��������hash (C++11)
		�ַ���ת�� (C++17)
		���ߺ���
		pair�� tuple (C++11)
		optional (C++17)�� any (C++17)
		variant (C++17)��format (C++20)
 
*/


virtualModule* stdlib_tools_module::getInstance()		// �̲߳���ȫ�ĵ���ģʽ
{
	if (nullptr != p_moduleIns)
	{
		delete p_moduleIns;
	}
	p_moduleIns = new stdlib_tools_module;
	return p_moduleIns;
}


// struct tm����<time.h>�����һ���ṹ�壬������ʱ���ʾ
void stdlib_tools_module::test0()
{
	// C++ ��׼��û���ṩ��ν���������ͣ��̳���C�����������ں�ʱ������Ľṹ�ͺ���
	
	// 1. windowsϵͳ�ṩ�ļ�ʱ�ӿڡ���GetTickCount();
	DWORD start = GetTickCount();			// typedef unsigned long DWORD

	// 2. C���Ա�׼���еļ�ʱ�ӿڡ���clock()��������ʼ���˿̴�����ʱ������¼��ʱ�䣬��λΪ����
	clock_t start_c = clock();
	Sleep(2000);
	clock_t end_c = clock();

	DWORD end = GetTickCount();
	DWORD interval = end - start;
	std::cout << interval << std::endl;				// windows
	std::cout << end_c - start_c << std::endl;		// c����

	// 3. C���Ա�׼�⡪��time()������ȡ1970.1.1 00:00:00���˿̾�����������					 
	time_t now = time(0);
	std::cout << "1970 ��Ŀǰ��������:" << now << std::endl;

	// 4. C���Ա�׼�⡪����ʽ��ʱ����������localtime()
	/*
		std::tm* localtime( const std::time_t *time );
		�����̰߳�ȫ�ģ�������WINDOWS�ṩ��localtime_s(),��linux�ṩ��localtime_r()
	*/

	//  C��׼���ж��������ʱ��ṹ�壺 struct tm;
	tm *ltm = nullptr;

	ltm = localtime(&now);			// ������������ת��Ϊtm����
	std::cout << "��: " << 1900 + ltm->tm_year << std::endl;
	std::cout << "��: " << 1 + ltm->tm_mon << std::endl;
	std::cout << "��: " << ltm->tm_mday << std::endl;
	std::cout << "ʱ��: " << ltm->tm_hour << ":";
	std::cout << ltm->tm_min << ":";
	std::cout << ltm->tm_sec << std::endl;

	struct tm now_tm;
	localtime_s(&now_tm, &now);
	std::cout << "��: " << 1900 + now_tm.tm_year << std::endl;
	std::cout << "��: " << 1 + now_tm.tm_mon << std::endl;
	std::cout << "��: " << now_tm.tm_mday << std::endl;
	std::cout << "ʱ��: " << now_tm.tm_hour << ":";
	std::cout << now_tm.tm_min << ":";
	std::cout << now_tm.tm_sec << std::endl;
}


// c++11��׼��ʱ��<chrono>
void stdlib_tools_module::test1() 
{
	/*
		<chrono>���ṩ������ʱ�ӣ�
				steady_clock 
						�ǵ�����ʱ�ӣ��൱�ڽ������е����
						ֻ���������ʺ����ڼ�¼�����ʱ��
				system_clock 
						��ϵͳ��ʱ�ӣ�
						��Ϊϵͳ��ʱ�ӿ����޸ģ��������������ʱ�� ������ϵͳʱ�����ʱ�����ܲ�׼��
				high_resolution_clock 
						�ǵ�ǰϵͳ�ܹ��ṩ����߾��ȵ�ʱ�ӣ�
						��Ҳ�ǲ������޸ĵġ�
						�൱�� steady_clock �ĸ߾��Ȱ汾��	
	*/
	using namespace std::chrono; 
	time_point<steady_clock> start, end;			// std::chrono::time_point������ʾһ��ʱ��
	microseconds dur;								// using microseconds = std::chrono::duration<long long, micro>������ʾһ��ʱ�䣻

	//ѭ��1��
	start = steady_clock::now();
	long int num = 10000000;
	for (int i = 0; i != num; i++)
	{
		int* b = new int[10]();
		delete[] b;
	}

	// 1. now()����������ȡ��ǰʱ��
	end = steady_clock::now();

	// 2. duration_cast<>()����
	std::chrono::duration<double, std::micro> dur0 = end - start;			// ֱ��������õ������͵�ʱ��
	dur = duration_cast<microseconds>(dur0);										// cast�����͵��г���
	debugDisp("dur0 == ", dur0.count(), ", ��λms");
	debugDisp("dur == ", dur.count(), ", ��λms");

	//ѭ��2
	start = steady_clock::now();
	int num2 = num >> 1;
	for (int i = 0; i != num2; i++)
	{
		int* b = new int[10]();
		delete[] b;
	}
	for (int i = num2; i != num; i++)
	{
		int* b = new int[10]();
		delete[] b;
	}
	end = steady_clock::now();
	dur = duration_cast<microseconds>(end - start);
	debugDisp("����2������", static_cast<double>(dur.count()) * \
		microseconds::period::num / microseconds::period::den, "��");

	//ѭ��3
	start = steady_clock::now();
	end = steady_clock::now();
	dur = duration_cast<microseconds>(end - start);
	debugDisp("����3������", static_cast<double>(dur.count()) * \
		microseconds::period::num / microseconds::period::den, "��");

	debugDisp("test3() finished.");
}


void stdlib_tools_module::test2() {}


void stdlib_tools_module::test3() {}


void stdlib_tools_module::test4() {}


void stdlib_tools_module::test5() {}


void stdlib_tools_module::test6() {}

