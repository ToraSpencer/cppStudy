#include <cstdlib>
#include <cstdio>


#include <string>
#include<iostream>

#include <memory>					// ʹ��memset()������Ҫ#include <memory.h>��<string.h>

#include "syntax_�ڴ����.h"

#define EPS 1e-10					//����ǳ�С��һ����EPSilon�������������������ֵʱ����Ϊ0
#define PI 3.14159



// ֪ʶ��
/*
		�ڴ�������ࣺ
			ջ�������������Զ������ͷš�
			������������Ա���䡢�ͷ�
			�������ڴ������г�����ġ�
			ȫ��������̬�����������ȫ�ֱ�����static�������������������ڼ䶼���ڡ�
			���������������const�������������ȣ�
			�����������ϵͳ�ͷš�
			������������������CPUִ�еĻ���ָ�


		�ڴ����ķ�ʽ��
			1. ��̬�����䡪����ȫ�ֱ���
			2. ջ�Ϸ���
			3. ���Ϸ��䡪����ʹ��malloc, new��allocator<T>����


		�����ڴ�������
			Ұָ�����
					ʹ����Ұָ�룬�����˲��÷��ʵ��ڴ档
					�����������ָ����ָ���ڴ汻�ͷź�Ҫ��ָ������

			�����ͷ�
					��һ���ڴ��ͷŶ��

			�ڴ�й¶
					��������������ɳ���δ���ͷ��Ѿ�����ʹ�õ��ڴ�������
					solution�����ڴ�ʹ���������ͷ�

		malloc��new���Լ�free��delete������
				new��delete����ִ�й��졢����������malloc, free������


		�ڴ����ĸ���
			��������ȡ�ڴ��ʱ�����ڴ��ȡ��������һ��������󲿷ִ���������4byte, 8byte�ȵ�λ����ȡ�ڴ档
			�����ڴ��ȡ������4byte����ȡ32λ��int������ʱ�򣬴�����ֻ�ܴӵ�ַΪ4�ı������ڴ��ȡ���ݡ�
			����ʹ��Ԥ����ָ��#pragma pack(n)��ָ������ϵ��n������ʾ�ڴ��ȡ����Ϊnbyte
			�ṹ���е��ڴ����
			��������ԭ��һ���ṹ��ʵ����ռ�Ĵ洢�ռ䲻�����г�Ա�Ĵ�С�Ӻͣ����п��ܴ���һЩ�ն���
			��Щ�ն�ʹ��ָ��鿴ò�������ֵ���պ���Զ����˽⡣


		ע�⶯̬���顪�����ϴ������������ͨ���������
			��̬���鲻��ʹ��begin(),end()


		allocator<T>��ģ��
			������<memory>ͷ�ļ��С�
			����������C�����е�malloc�����Կ���һƬδ�������ݶ�����ڴ�ռ䡣
*/



//	malloc����������̬�ڴ����
/*
malloc����������̬�ڴ����
����ԭ�ͣ�
void*  malloc(std::size_t size);				// <cstdlib>

*/

 

virtualModule* syntax_memory_management_module::getInstance()		// �̲߳���ȫ�ĵ���ģʽ
{
	if (nullptr != p_moduleIns)
	{
		delete p_moduleIns;
	}
	p_moduleIns = new syntax_memory_management_module;
	return p_moduleIns;
}



namespace TEST_STRUCT 
{
	struct stru
	{
		char a;
		short b;
		int c;
		long d;							// 32λϵͳ��long�Ĵ�С��4�ֽڣ�64λϵͳ����8�ֽڡ�
		char e;
		long long f;				// long long�Ĵ�С��8�ֽڡ�
	};
}




// test0: C++�е��ڴ����
void syntax_memory_management_module::test0(void)
{
	std::cout << "\n\n\n\n" << std::endl;
	std::cout << "test0��C++�е��ڴ����" << std::endl;

	int i1;											// ջ��
	char str1[] = "abc";				// ջ��
	char* pc;										// ջ��
	char str2[] = "123";				// "123"���ַ����������������ֳ�������str2��ջ��
	const char* str3 = "123";				// str3��ָ���ַ���������"123"��ָ�롣
	static int i2 = 2;							// ȫ��������̬����
	auto p1 = (char*)malloc(10);		// ��������Ŀռ��ڶ�����
	auto p2 = (char*)malloc(20);		// ��������Ŀռ��ڶ�����
	free(p1);
	free(p2);

}


// test1: C�еĶ�̬�ڴ�Ļ���ʹ��
void syntax_memory_management_module::test1(void)
{
	std::cout << "\n\n\n\n" << std::endl;
	std::cout << " test1: C�еĶ�̬�ڴ�Ļ���ʹ��" << std::endl;


	// C�����еĶ�̬�ڴ���صĻ������������º�������stdlib.h��
	/*
	1. malloc������calloc���������������Ϸ����µ��ڴ�����
	malloc()���ٵ��ڴ�δ��ʼ������Ҫ��memset()��ʼ��
	calloc()���ٵ��ڴ��ǳ�ʼ���˵ġ�
	2. realloc�����������������ѷ�����ڴ�����
	3. free�������������ͷ��ѷ�����ڴ�����
	*/

	//			ʹ��malloc����δ��ʼ���Ķ��ڴ棬��ʼ��֮ǰ������ʹ�á�
	int* pi1 = (int*)malloc(100);							// ����100���ֽڵĶ��ڴ棬�������׵�ַint*���͵�ָ�롣
															// malloc()ֱ�ӷ��ص���void���͵�ָ�롣
	int* pi2 = (int*)malloc(25 * sizeof(int));			// ͬ��


														//			����ڴ��Ƿ����ɹ�
	if (pi1)
	{
		std::cout << "malloc()������ڴ�ɹ�" << std::endl;
	}
	else
	{
		std::cout << "malloc������ڴ�ʧ��" << std::endl;
		return;
	}

	//			ʹ��memset��һ���ڴ��е�����ȫ���趨Ϊָ����ֵ
	/*
		void *memset(	void *buffer,					�ڴ��Ӧ��ָ�������
						int c,								�����ڴ��ֵ
						int count							�ڴ�ĳ���
						)
	*/
	memset(pi1, 'a', 100);					// ����S��'a'���pi1��ָ�Ķ��ڴ档
	char* pc1 = (char*)pi1;
	*(pc1 + 5) = '\0';
	printf("%s", pc1);


	//			ʹ��free()�ͷŶ��ڴ档
	free(pi1);
	free(pi2);

}


// test2: C++�еĶ�̬�ڴ�Ļ���ʹ��
void syntax_memory_management_module::test2(void)
{
	std::cout << "\n\n\n\n" << std::endl;
	std::cout << " test2: C++�еĶ�̬�ڴ�Ļ���ʹ��" << std::endl;

	// ʹ��new���䶯̬�ڴ���Ѷ���
	int* pi1 = new int;											// �������ڴ�ʧ�����׳�std::bad_alloc���͵��쳣��
	int* pi2 = new (std::nothrow) int; 					// �������ڴ�ʧ���򷵻�һ����ָ�룬���׳��쳣��
	float* pf1 = new float(3.14159);				// ���䶯̬�ڴ棬�����г�ʼ����
	int* parri1 = new int[5];							// ���䶯̬�������Ҫָ��Ԫ�ظ���
														// ��̬���鲢����һ��������������󣬲���ʹ��begin(), end(), ��Χforѭ��
	TEST_STRUCT::stru* pclass1 = new TEST_STRUCT::stru();		// ���������Ҫ���ù��캯����

	// ʹ��delete���ͷŶ�̬�ڴ棻
	delete pi1;
	delete pi2;
	delete[] parri1;									// �ͷŶ�̬���飬delete֮��Ҫ��[]
	delete pclass1;										// delete����󣬱�����ִ�������������� 


	// �ͷ��ڴ�֮��ָ��Ҫ�ÿա�
	pi1 = NULL;
	parri1 = NULL;
	pclass1 = NULL;
}


// test3: �ṹ���е��ڴ����
void syntax_memory_management_module::test3(void)
{
	std::cout << "\n\n\n\n" << std::endl;
	std::cout << " test3: �ṹ���е��ڴ����" << std::endl;

	TEST_STRUCT::stru s1 = { 1,2,3,4,5,6 };
	unsigned char* pc = NULL;
	pc = reinterpret_cast<unsigned char*>(&s1);

	// s1���ڴ�Ӧ���������ģ�
	/*
	char a; short b; int c; long d; char e; long long f;

	axbbcccc
	dddddddd
	exxxxxxx
	ffffffff
	����һ��ռ32�ֽڣ��ṹ��ʵ���ڲ������ݷֲ�����ʹ��һ��unsigned char*ָ�����鿴��֤��
	*/


	std::cout << "sizeof(s1) == " << sizeof(s1) << std::endl;
	std::cout << "�ṹ��ʵ��s1�ڲ����ݷֲ���" << std::endl;
	for (int i = 1; i <= 32; i++)
	{
		printf("%d. 0x%x\n", i, *pc);
		pc++;
		if (i >= 32)
		{
			break;
		}
	}
}




void syntax_memory_management_module::test4(void)
{


}



void syntax_memory_management_module::test5(void)
{


}



void syntax_memory_management_module::test6(void)
{


}
