#include <iosfwd>
#include <ios>
#include <istream>
#include <ostream>
#include <iostream>
#include <string>
#include <typeinfo>

#include <cstdio>

#include "syntax_���������塢��ʼ��.h"
 
#define EPS 1e-10					//����ǳ�С��һ����EPSilon�������������������ֵʱ����Ϊ0
#define PI 3.14159



// syntax_���������塢��ʼ��
/*
				 
*/


virtualModule* syntax_declare_define_initialize_module::getInstance()		// �̲߳���ȫ�ĵ���ģʽ
{
	if (nullptr != p_moduleIns)
	{
		delete p_moduleIns;
	}
	p_moduleIns = new syntax_declare_define_initialize_module;
	return p_moduleIns;
}

 
 

// test0: �Զ���ʼ������
namespace AUTOMATIC_INITIALIZATION 
{
	class AAA
	{
	private:
		int numi;
		float numf;

	public:
		AAA()
		{}

		void disp()
		{
			std::cout << "AAA���͵Ķ����У�numi == " << this->numi << "�� numf == " << this->numf << std::endl;
		}
	};


	AAA a_global;
	int numi_global;
	float numf_global;

}

void syntax_declare_define_initialize_module::test0(void)
{
	using namespace AUTOMATIC_INITIALIZATION;
	extern int intName;			// ������������һ������
	int intDefined;				// ���塪������һ������ʵ�壬��һ�����ְ�������

	// ����������ȫ�ֱ��������������Ǿֲ�������main����Ҳ�㡣
	//	ȫ�ֻ������ͱ������Զ���ʼ��Ϊ0ֵ���ֲ��������͵ı��������Զ���ʼ����
	//	����������ʱ�򣬲����Ǿֲ��Ļ���ȫ�ֵģ������Զ������޲ι��캯����
	//	δ��ʼ���ľֲ���������ʹ�á�
	AAA a_local;
	int numi_local;
	float numf_local;

	a_global.disp();
	std::cout << "numi_global =="<< numi_global << std::endl;
	std::cout << "" << numf_global << std::endl;

	// ��Ĺ��캯���У����Բ���ʾ��ʼ����Ա���ݡ�
	//		Ȼ���øù��캯�������ȫ�ֶ�����Զ�����Ա���ݳ�ʼ��Ϊ0ֵ��
	//		�ֲ������Ա���ݲ����Զ���ʼ����Ϊ���ֵ�����ǲ���Ӱ��ö����ʹ�á�
	a_local.disp();

}


void syntax_declare_define_initialize_module::test1(void) 
{

}

void syntax_declare_define_initialize_module::test2(void)
{

}


void syntax_declare_define_initialize_module::test3(void)
{

}


void syntax_declare_define_initialize_module::test4(void)
{

}


void syntax_declare_define_initialize_module::test5(void)
{

}

void syntax_declare_define_initialize_module::test6(void)
{

}