#include <iostream>
#include <string>
#include <typeinfo>


#include <cstdio>

#include "chap_syntax.h"

#define EPS 1e-10					//����ǳ�С��һ����EPSilon�������������������ֵʱ����Ϊ0
#define PI 3.14159



// ֪ʶ��
/*
			const
					constָ�롪�����㡢�ײ�const
								һ���ж���const���βκ�û�����ĺ����޷����֡� Record lookup(Phone* const)�� Record lookup(Phone*)�޷����֡�
								�෴���Ƿ���ĳ���ײ�const�βο������֡� Record lookup(Account*)�� Record lookup(const Account*)�������֡�

					const�ͺ�ĶԱȡ���const�����Ⱥ����ȫ����Ϊconst���������ʱ�����д����顣

					������ʹ��const�β�
								ֵ���ݵ��ββ���Ҫconst����
								���á�ָ���β�ʹ��const���Σ����Ա����������ݲ��ᱻ�����޸ġ�

					����ǰ��const����
								��ͨ�������෽��ǰ�����Լ�const���Σ���ʾ��������ֵ��const�������޸ġ�
								
					�������const����
								ֻ�з�static���෽�����Լ�const���Σ���const���ں���֮��
								��ʾ���෽����thisָ����constָ�룬���ܸ������Ա��ֵ��
		
			static
					Դ�ļ���static����Դ�ļ��ڵ�static����ֻ���ڱ�Դ�ļ��ڱ����ʺ͵��á�
					������static����������static�����൱��һ��ȫ�ֱ�����
					����static�������ڵ�static��Ա�����������������У�������ĳһ��������Ҫ�������ʼ�����ھ�̬�洢���С�
										 static�෽��ֻ�ܷ���static��Ա������static�෽������Ϊ������ʹ��thisָ�롣



			auto
					C��C++�ж���auto�����������кܴ�Ĳ�ͬ��
					
			extern 
			explicit

		C++�������C�����ӵĹؼ��֣�
				using 			 
						1. �����ռ�,�����ڵ����ֵ�ʹ��
									(a) using namespace �����ռ���;
									(b) using �����ռ���::����;
						2. ʹ�����ͱ�����
									(a) ��ʶ�� attr(��ѡ) = ���ͱ�ʶ ;
									(b)	template < ģ���β��б� >
 											using ��ʶ�� attr(��ѡ) = ���ͱ�ʶ ;

 											
				auto
				
				decltype
						decltype(f()) sum = x;			// �ƶ�sum�������Ǻ���f�ķ������͡�
*/
 

	virtualModule* syntax_keyword_module::getInstance()		// �̲߳���ȫ�ĵ���ģʽ
	{
		if (nullptr != p_moduleIns)
		{
			delete p_moduleIns;
		}
		p_moduleIns = new syntax_keyword_module;
		return p_moduleIns;
	}

	 
	// test0: �ؼ���const
	void syntax_keyword_module::test0() 
	{
		int numi1 = 11;
		int numi2 = 22;
		int* pi1 = NULL;
		int* const cpi1 = &numi1;							// ��һ������const������ָ�뱾����һ��������cpi1������ָ������λ�á�
		const int* pci1 = &numi1;							// ��һ���ײ�const������ָ��ָ���������һ��������
		//				������ͨ��pci1���޸���ָ���numi1��ֵ
		//				���Ǹ�ָ�����ָ������λ�á�
		const int* const cpci1 = &numi1;			//	��һ���ǵײ�const���ڶ����Ƕ���const��ָ�뱾���ǳ������涨��ָ�������ҲӦ���ǳ�����		

		std::cout << "\n\n\n\n" << std::endl;
		std::cout << "test0: �ؼ���const" << std::endl;


		std::cout << "\t����/�ײ�const" << std::endl;
		// ����const��ָ�뱾����һ������ 
		std::cout << "\t\tint* const cpi1 = &numi1;	*cpci1 == " << *cpi1 << "��������const" << std::endl;


		pi1 = const_cast<int*>(cpi1);							// ����ʹ��const_castȥ��cpi1��const���ԣ� pi1ָ���λ�ÿ����޸ģ�
		pi1 = &numi2;
		std::cout << "\t\tpi1 = const_cast<int*>(cpi1); pi1 = &numi2; *pi1 == " << *pi1 << std::endl;


		// �ײ�const��ָ��ָ���������һ������
		std::cout << "\t\tconst int* pci1 = &numi1; *pci1 == " << *pci1 << "�����ײ�const" << std::endl;
		pci1 = &numi2;												// �ײ�constָ�����ָ������λ�ã�
		std::cout << "\t\tpci1 = &numi2; *pci1 ==  " << *pci1 << std::endl;


		// ���㡢�ײ�const����ͬʱ���֡���ָ�뱾���ǳ�����ָ�������Ҳ�ǳ�����
		std::cout << "\t\tconst int* const cpci1 = &numi1; *cpci1 == " << *cpci1 << "�������㡢�ײ�const����ͬʱ����" << std::endl;
		std::cout << std::endl;

	}


	// test1: �ؼ���static
	namespace KEYWORD_STATIC
	{
		static int foo1()
		{
			int num = 1;
			num++;
			return num;
		}
		 

		static int foo2()
		{
			static int num = 1;		// �������ڵ�static����ʵ���Ͼ���ȫ�ֱ���������һ�κ�֮�����������Ч��
			num++;
			return num;
		}
	}


	void syntax_keyword_module::test1()
	{
		using namespace KEYWORD_STATIC;
		std::cout << "\n\n\n\n" << std::endl;
		std::cout << "test0: �ؼ���static" << std::endl;


		// ������static���������ڵ�static�����൱��һ��ȫ�ֱ�����
		for (int i = 0; i < 5; i++)
		{
			std::cout << "foo1 == " << foo1() << std::endl;
		}

		for (int i = 0; i < 5; i++)
		{
			std::cout << "foo2 == " << foo2() << std::endl;
		}

	}


	// test2: const�ؼ��֣�����
	void syntax_keyword_module::test2()
	{


	}


	// test3()����constexpr�ؼ��֣��������ʽ
	namespace KEYWORD_CONSTEXPR
	{
		// �������ʽ ==  �����ڳ���
		/*
			constexpr����������ģ������ƣ�
				�����з���ֵ��������void���ͣ�constexpr����Ŀ����������ñ����ڳ���������û�з���ֵ��constexpr�ǲ�����ġ�
				����ʹ��ѭ�����
				������ʹ�þֲ�����
				����ֻ����һ��return��䣻
				ʹ��ǰ�������ж��壻
		*/
		constexpr size_t fib(const size_t n)
		{
			if (n == 0 || n == 1)
				return n;
			else
				return fib(n - 1) + fib(n - 2);
		}

		template <size_t N>
		constexpr size_t Fib()
		{
			return Fib<N - 1>() + Fib<N - 2>();
		}

		template <>
		constexpr size_t Fib<0>()
		{
			return 0;
		}

		template <>
		constexpr size_t Fib<1>()
		{
			return 1;
		}
	}


	void syntax_keyword_module::test3()
	{
		using namespace KEYWORD_CONSTEXPR;

		debugDisp("\n\n\n\n");
		debugDisp("test3()����constexpr�ؼ��֣������ڳ���");

		// 1. constexpr�������޶��ñ����Ǳ����ڳ�������const���������Ǳ����ڳ���Ҳ�����������ڳ�����
		{
			constexpr int compile_time = 100;		// �����ڳ���
			const int run_time = std::rand();			// ����ʱ����
		}

		// 2. constexpr���������ܱ����ڳ���������������Եõ������ڵķ���ֵ��
		{
			int arr1[fib(3)];											// ��������ʱ������ߴ�����Ǳ����ڳ�������������ʧ�ܣ�
			int arr2[Fib<2>()];
			debugDisp("arr1 size == ", sizeof(arr1) / sizeof(int));
			debugDisp("arr2 size == ", sizeof(arr2) / sizeof(int));
		}

		// 3. constexpr����Ҳ���Խ��ܷǱ����ڳ�������������õ�����ֵ�Ͳ��Ǳ�����ֵ��
		{
			const size_t num1 = fib(static_cast<size_t>(std::rand() % 10));		// ����ʱ�������Ǳ����ڳ����� 
			//int arr1[fib(num1)];						// ����ʧ�ܣ���Ϊfib()����������Ǳ����ڳ��������Է���ֵҲ���Ǳ�����ֵ��

		}

		debugDisp("syntax_keyword_module::test3() finished.");
	}


	void syntax_keyword_module::test4()
	{


	}


	void syntax_keyword_module::test5()
	{


	}


	void syntax_keyword_module::test6()
	{


	} 


	void syntax_keyword_module::test7()
	{


	}
