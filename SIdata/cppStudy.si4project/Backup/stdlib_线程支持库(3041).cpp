#include <thread>
#include <mutex>
#include <future>
#include <condition_variable>


#include <iostream>
#include <string>
#include <typeinfo>

#include <cstdio>
#include "stdlib_�߳�֧�ֿ�.h"

#define EPS 1e-10								//����ǳ�С��һ����EPSilon�������������������ֵʱ����Ϊ0
#define PI 3.14159



// C++��׼�⡪���߳�֧�ֿ�
/*
**			(C++11 ��)<thread> 												std::thread �༰֧�ֺ���
**			(C++20 ��)<stop_token> 										std::jthread ��ֹͣ�Ǻ�
**			(C++11 ��)<mutex> 												����ԭ��
**			(C++14 ��)<shared_mutex> 									����Ļ���ԭ��
**			 (C++11 ��)<future>	 											�첽�����ԭ��
**			(C++11 ��)<condition_variable> 						 	�̵߳ȴ�����
**			 (C++20 ��)<semaphore> 										�ź���
**			 (C++20 ��)<latch>	 												��
**			 (C++20 ��)<barrier>	 											����
**
**
*/


// ����
/*
	������ɣ�
			1.����
			2.����
			3.���̿��ƿ�(PCB)

*/


// �߳�
/*
	�߳��ǽ����е�һ��ʵ�壬�Ǳ�ϵͳ��������͵��ȵĻ�����λ��
	Ҳ��˵���߳���CPU��ִ�е��ȵ���С��λ��
	Ҳ����˵�����̱������ܻ�ȡCPUʱ�䣬ֻ�������̲߳ſ��ԡ�

	�̡߳����̵ıȽ�
			�̲߳������ϵͳ�ĵ��ȣ�����CPU�ľ������õ������ʱ��Ƭ����ô������CPU�����С�
			�����̸����ȡ����ϵͳ�������Դ�����ڴ档


*/


virtualModule* stdlib_thread_support_module::getInstance()		// �̲߳���ȫ�ĵ���ģʽ
{
	if (nullptr != p_moduleIns)
	{
		delete p_moduleIns;
	}
	p_moduleIns = new stdlib_thread_support_module;
	return p_moduleIns;
}



void stdlib_thread_support_module::test0(void)
{

}


// test1�� <ctime>����C����ʱ�䡢���ڹ��ߡ�
void stdlib_thread_support_module::test1(void)
{}


// test2:
void stdlib_thread_support_module::test2(void)
{
	using namespace std::chrono;

	//ѭ��1��
	auto start = system_clock::now();

	long int num = 10000000;
	for (int i = 0; i != num; i++)
	{
		int* b = new int[10]();
		delete[] b;
	}

	auto end = system_clock::now();
	auto duration = duration_cast<microseconds>(end - start);
	std::cout << "����1������"
		<< double(duration.count()) * microseconds::period::num / microseconds::period::den << "��" << std::endl;


	//ѭ��2
	start = system_clock::now();

	int num2 = num >> 1;
	for (int i = 0; i != num2; i++) {
		int* b = new int[10]();
		delete[] b;
	}
	for (int i = num2; i != num; i++) {
		int* b = new int[10]();
		delete[] b;
	}

	end = system_clock::now();
	duration = duration_cast<microseconds>(end - start);
	std::cout << "����2������"
		<< double(duration.count()) * microseconds::period::num / microseconds::period::den << "��" << std::endl;

	//ѭ��3
	start = system_clock::now();

	//testfuc2(num);

	end = system_clock::now();
	duration = duration_cast<microseconds>(end - start);
	std::cout << "����3������"
		<< double(duration.count()) * microseconds::period::num / microseconds::period::den << "��" << std::endl;


}


void stdlib_thread_support_module::test3(void)
{}



void stdlib_thread_support_module::test4(void)
{}



void stdlib_thread_support_module::test5(void)
{}


void stdlib_thread_support_module::test6(void) {}