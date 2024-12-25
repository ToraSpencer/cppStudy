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

#ifndef NOMINMAX
#define NOMINMAX
#endif
#include <windows.h>
#include <io.h>

#include "AuxiliaryHeader.h"
 
 
/////////////////////////////////////////////////////////////////////////////////////////////// �������ݽṹ��
namespace AUXILIARY_DSA
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
	 

	// ��������inStream�������ո��Ʊ����ȡһ�ַ�
	char GetChar(std::istream& inStream = std::cin); 
}
using namespace AUXILIARY_DSA; 




	 





 





