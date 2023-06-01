#include <string>
#include<iostream>
#include <cstddef>
#include <memory>
#include <iterator>

#include <cstdio>


#include "basicTypes_����.h"



// ֪ʶ��
/*
			1. �����ά�ȱ�����һ���������ʽ
			
			2. �ַ�����������ԣ�
							�������ַ�������������ʼ��char[]��ע��ĩβԪ����'\0'������������ò���ǲ���ȫ�ģ�����
			3. size_t���ͣ�
							�����±�һ�㶨��Ϊsize_t����
							��һ��������ص��޷�������
							��<cstddef>�ж���
							����Ƶ��㹻���Ա��ܱ�ʾ�ڴ����������Ĵ�С��
			4. �������������
							�������±�Խ�硣
							һ�����������鲻������ֻ���Լ�С�ġ�

			5. ���õ����顪��������
				 ��������ã�
								int (&arri)[10];		// arri��һ��10Ԫ��int��������á�

			6. ָ������飺
								 int *(piarr)[10];					// piarr�Ǻ���10��int*ָ��Ԫ�ص����顣
				�����ָ�룺
									int (*parri)[10];						// parri�������ָ�룬ָ��һ��10Ԫ�ص�int���顣
									float (*parrf)[] = {1.11, 2.22, 3.33};			// parrf��float�����ָ�롣


			7. ������Ϊ�����Ĳ���
							��������һ�����飬������ֵ���ݻ������ô��ݣ����˻�Ϊ������Ԫ�ص�ָ�롣
							void printf(const int[]);	// []�ڲ���Ҫд������д��Ҳ��д
																				// ��Ϊ��������ָ�����ʽ���ݽ������ģ�������������Ϣ��
																				// �����ϴ��ݵ���const int*
			8. ����ĳ�ʼ��������test4
							ȫ�������Ԫ��ֵ���Զ���ʼ��Ϊ0���ֲ����鲻���ʼ����
							����ʹ��memset()����������Ԫ��ֵ��ʼ��Ϊ0�����Ҵ˺������ʱ�̶����Խ���������Ԫ��ֵ��0��
						
*/



virtualModule* basicTypes_array_module::getInstance()		// �̲߳���ȫ�ĵ���ģʽ
{
	if (nullptr != p_moduleIns)
	{
		delete p_moduleIns;
	}
	p_moduleIns = new basicTypes_array_module;
	return p_moduleIns;
}





// test0: �������������ʼ���������÷�
void basicTypes_array_module::test0(void)
{
	std::cout << "\n\n\n\n" << std::endl;
	std::cout << "test0: �������������ʼ��" << std::endl;

	// ��������ʱ������ά�ȱ�����һ���������ʽ��
	int arri1[5];

	const unsigned int size1 = 4;
	constexpr unsigned int size2 = 3;
	float arrf1[size1];
	float arrf2[size2];				// ���������ָ��size1�ǳ�����size2�ǳ������ʽ�Ļ������벻ͨ����


	// ����ʱ�������ʼֵ������Բ�дά�ȣ�
	int arri2[] = {1,2,3};


	// �б��ʼ������ֻ��ʼ���������顣
	int arri3[5] = { 9 };					// ��Ԫ����Ϊ9������Ԫ��Ĭ�ϳ�ʼ����ֵΪ0��
	for (int i: arri3) 
	{
		std::cout << "\t" << i;
	}
	std::cout << std::endl;


	// ʹ��sizeof���Ի�ȡ�����������Ԫ����
	std::cout << "\tarri1������Ϊ��sizeof(arri1) == " << sizeof(arri1) << std::endl;
	std::cout << "\tarrf1��Ԫ����ĿΪ��sizeof(arrf1)/sizeof(float) == " << sizeof(arrf1) / sizeof(float) << std::endl;
}




// test1:  ָ������顢�����ָ�롣
void basicTypes_array_module::test1(void)
{
	int* (arr1)[10];			// arr1��ָ�������, arr1��������
	int (*arr2)[10];			// arr2�������ָ�룬�������û��������

	std::cout << "\n\n\n\n" << std::endl;
	std::cout << "test1: ָ������顢�����ָ�롣" << std::endl;

	std::cout << "sizeof(int) == " << sizeof(int) << std::endl;
	std::cout << "sizeof(int*) == " << sizeof(int*) << std::endl;
	std::cout << "sizeof(void*) == " << sizeof(void*) << std::endl;


	std::cout << "sizeof(arr1) == " << sizeof(arr1) << std::endl;      // sizeof(������)���ص����������������
	std::cout << "sizeof(arr2) == " << sizeof(arr2) << std::endl;      // arr2������������ֻ��һ��ָ�룬C++������ָ����������һ���ģ��ɻ���������


	// ʹ��ָ�����鴴����ά���飬ÿ��Ԫ�����ɲ���ȡ�
	int intArr0[3] = {1,2,3};
	int intArr1[4] = {11,12,13,14};
	int intArr2[5] = {21, 22, 23, 24, 25};

	int* ptrArr[3] = {&intArr0[0], &intArr1[0], & intArr2[0]};
	
	std::cout << ptrArr[0][0] << std::endl;
	std::cout << ptrArr[1][1] << std::endl;
	std::cout << ptrArr[2][2] << std::endl;
}



// test2: ��C++11����׼�⺯��begin(), end()����������
void basicTypes_array_module::test2(void)
{
	std::cout << "\n\n\n\n" << std::endl;
	std::cout << "test2: ��C++11����׼�⺯��begin(), end()����������" << std::endl;


	// begin(), end()����������ͷ�ļ�<iterator>
	// ����������ֱ𷵻��������Ԫ��ָ�롢β��ָ�롣
	int arri1[] = {1,2,3,4,5};
	int* pi = arri1;

	std::cout << "\t��������arri1:" << std::endl;
	while (pi != std::end(arri1))
	{
		std::cout << "\t" << *(pi++);
	}
	std::cout << std::endl;


}



// test3: ������Ϊ��������
namespace ARRAY_ARG 
{

	// ������Ϊ�������ݸ������������ڼ���Զ��˻�Ϊָ�롣
	static void foo(const int arr[])
	{
		std::cout << "sizeof(arg) == " << sizeof(arr) << std::endl;			// ע��sizeof()�ǲ�����(operator)�����Ǻ�����

	}
}

void basicTypes_array_module::test3(void)
{
	using namespace ARRAY_ARG;
	std::cout << "\n\n\n\n" << std::endl;
	std::cout << "test3: ������Ϊ��������"<< std::endl;

	int arr[] = {1,2,3,4,5};

	std::cout << sizeof(arr) << std::endl;			// ���Ϊ20��ע��sizeof()�ǲ�����(operator)�����Ǻ��������鴫�ݸ�sizeof�����˻�Ϊָ�롣sizeof(arg)Ҳ����д��sizeof arg;
	foo(arr);													// ��ӡ���Ϊ4��32λ����

	
}



// test4: ����ĳ�ʼ��
void basicTypes_array_module::test4(void)
{
	std::cout << "\n\n\n\n" << std::endl;
	std::cout << " test4: ����ĳ�ʼ��"<< std::endl;

	auto fDisp = [](int* pi, int len)
	{
		for (int i = 0; i<len; i++)
		{
			std::cout << *pi << "  ";
			pi++;
		}
		std::cout << std::endl;
	};


	auto foo = [&fDisp]()
	{
		int arri[10];		// arri��lambda���ʽ�ڣ���һ���ֲ��������
		fDisp(arri, 10);	// ��ʱ������ӡarri������Ԫ�أ����Կ���û�г�ʼ����
		memset(arri, 0, sizeof(arri));
		fDisp(arri, 10);	// ��ʱ��ӡȫ��Ϊ0��
	};


	foo();
}


void basicTypes_array_module::test5() {}


void basicTypes_array_module::test6() {}