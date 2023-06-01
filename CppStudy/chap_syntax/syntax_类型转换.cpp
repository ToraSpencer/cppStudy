#include <iostream>
#include <string>
#include <typeinfo>

#include <cstdio>

#include "syntax_����ת��.h"
 

#define EPS 1e-10					//����ǳ�С��һ����EPSilon�������������������ֵʱ����Ϊ0
#define PI 3.14159

//	֪ʶ��
/*	
 
		C����ǿ������ת��
					(T)arg;

			
		������ʽǿ������ת����
					static_cast 		
								����ִ��������������֮���ת����
								����ִ���м̳й�ϵ��ָ�롢���õ�ת�������������֮���ת�����黹����dynamic_cast����ȫ��
								

					dynamic_cast 		
								����ִ���м̳й�ϵ��������ָ�롢���õ�ת����
								ת��ǰ�����Ͱ�ȫ��飬�������ȫ�Ļ���ת��ʧ�ܣ�����NULLָ�롣
								�������͵�ʱ��һ��Ҫʹ�ã������ָ��/����ת��Ϊ������ָ��/���ã���ʱ�����׷�����ȫ���⡣
								

					const_cast 
								����ȥ�������������const���ԣ�һ�㲻��ʹ�á�

					reinterpret_cast 
								������C����ǿ������ת��������ȫ��


	
		���Ͱ�ȫת����
					����ת���ɸ����ǰ�ȫ�ģ�����ת���������ǲ���ȫ�ġ�
					�������Ϊ�������Ϣ�Ƕ��ڸ���ģ�����ת���ɸ���ʱ�����˶���һЩ��Ϣ�����Ǹ���ת��������Ļ���������Ϣ�ն����ǲ���ȫ�ġ� 

*/


virtualModule* syntax_type_cast_module::getInstance()		// �̲߳���ȫ�ĵ���ģʽ
{
	if (nullptr != p_moduleIns)
	{
		delete p_moduleIns;
	}
	p_moduleIns = new syntax_type_cast_module;
	return p_moduleIns;
}



// test0: const_cast
void syntax_type_cast_module::test0(void)
{
	int  numi1 = 5;
	const int* pci1 = NULL;
	int* pi1 = NULL;

	std::cout << "test0: const_cast" << std::endl;

	pci1 = &numi1;											 			// constָ��pci1ָ��numi1���ǵײ�const��������ͨ��pci1���޸�numi1��ֵ��
	pi1 = const_cast<int*>(pci1);						 	 // ʹ��pci1��pi1��ֵ������ʹ��const_cast�Ƴ���const���ԡ�


	*pi1 = 6;
	std::cout << "\tpci1 = &numi1; pi1 = const_cast<int*>(pci1);	 *pi1 = 6; " << std::endl;
	std::cout <<"\tnumi1 == " << numi1 << std::endl;

}


// test1: ʹ��dynamic_cast()ʵ����������(downcast)
namespace DYNAMIC_CAST_EXAMPLE 
{
	class Pet
	{
	public: virtual ~Pet() {}
	};


	class Tortoise : public Pet {};


	class Rabbit : public Pet {};


}

void syntax_type_cast_module::test1(void)
{
	using namespace DYNAMIC_CAST_EXAMPLE;
	Pet* pet = new Rabbit;							// ָ�����Ӷ����petָ�롣
	
	Tortoise* tortoise = dynamic_cast<Tortoise*>(pet);	// Petָ����ͼ��������ΪTortoiseָ�룬��Ӧ��ʧ�ܵ�
	Rabbit* rabbit = dynamic_cast<Rabbit*>(pet);		// Petָ��ָ����������ΪRabbitָ�룬��Ӧ�ǳɹ��ģ���ΪPetָ��ԭ��ָ��ľ���Rabbit����

	
	if (tortoise == NULL)					// ת��ʧ��dynamic_cast���᷵��NULLָ�롣
	{
			printf("Petָ����������ΪTortoiseָ��ʧ��\n");
	}
	else
	{
			printf("Petָ����������ΪTortoiseָ��ɹ�\n");
	}
	
	if (rabbit == NULL)
	{
			printf("Petָ����������ΪRabbitָ��ʧ��\n");
	}
	else
	{
			printf("Petָ����������ΪRabbitָ��ɹ�\n");
	}
}


void syntax_type_cast_module::test2(void) 
{}


void syntax_type_cast_module::test3(void)
{}


void syntax_type_cast_module::test4(void)
{}


void syntax_type_cast_module::test5(void)
{}


void syntax_type_cast_module::test6(void)
{}
