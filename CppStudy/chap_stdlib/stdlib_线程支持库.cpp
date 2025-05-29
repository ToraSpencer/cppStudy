#include <thread>
#include <mutex>
#include <future>
#include <condition_variable>


#include <iostream>
#include <string>
#include <typeinfo>

#include <cstdio>
#include "stdlib_�߳�֧�ֿ�.h"

#define EPS 1e-10								// ����ǳ�С��һ����EPSilon�������������������ֵʱ����Ϊ0
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
		delete p_moduleIns;
	p_moduleIns = new stdlib_thread_support_module;
	return p_moduleIns;
}



void stdlib_thread_support_module::test0()
{}


// test1�� 
void stdlib_thread_support_module::test1()
{}


// test2:
void stdlib_thread_support_module::test2()
{}


void stdlib_thread_support_module::test3()
{}



void stdlib_thread_support_module::test4()
{}



void stdlib_thread_support_module::test5()
{}


void stdlib_thread_support_module::test6() {}