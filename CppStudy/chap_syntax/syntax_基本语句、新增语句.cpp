#include <cstdio>
#include <string>
#include <iostream>
#include <vector>						//vector��ģ����ͷ�ļ�<vector>��

#include <cstdio>


#include "syntax_������䡢�������.h"



/*
	while(){}

	do()	while{};

	forѭ��

	(C++11)��Χforѭ����
	��ʽ��for(Ԫ������ elem:  c) {...}					// c����������


	switch case



*/




virtualModule* syntax_basic_statement_module::getInstance()		// �̲߳���ȫ�ĵ���ģʽ
{
	if (nullptr != p_moduleIns)
	{
		delete p_moduleIns;
	}
	p_moduleIns = new syntax_basic_statement_module;
	return p_moduleIns;
}




// test0: ��C++11����Χforѭ�����
namespace RANGE_FOR_LOOP 
{

	template <typename T, size_t S>
	class MyArray														// �Զ�������������ģ�壬�����Ͳ���T���ͷ����Ͳ���S
	{
	public:
		T& operator[](size_t i);									// �����±������
		const T& operator[](size_t i) const;					// �����±��������const�汾�������ء�
																//				��Ϊ��ҪMyArray��const����ʹ���±������ʱ�����ص�Ԫ������Ҳ��const

		T* begin(void);													// ��ȡ��ʼ��������
		const T* begin(void)	const;							// ��ȡ��ʼ��������const�汾��������
																//				��Ϊ��ҪMyArray��const����ʹ��begin����ʱ�����صĵ�����Ҳ��const��
																//				ע�������ǵײ�const��������ָ��������ǳ����������������ǳ�����ָ���λ�ÿ��Ըı䡣
		T* end(void);													// ��ȡβ���������
		const T* end(void) const;



	private:
		//	��Ա���ݣ�
		T arr[S];													// Ԫ������ΪT�� ����ΪS�����顣

	};


	template <typename T, size_t S>
	T&  MyArray<T, S>:: operator[](size_t i)
	{
		return this->arr[i];												// ���������쳣���������±�Խ���ʱ���׳��쳣��
	}


	template <typename T, size_t S>
	const T& MyArray<T, S>:: operator[](size_t i) const
	{
		return const_cast<MyArray&>(*this)[i];				// ��������
	}


	template <typename T, size_t S>
	T* MyArray<T, S>::begin(void)
	{
		return arr;
	}


	template <typename T, size_t S>
	const T* MyArray<T, S>::begin(void)	const
	{
		return const_cast<MyArray*>(this)->begin();
	}


	template <typename T, size_t S>
	T* MyArray<T, S>::end(void)
	{
		return (arr + S);
	}


	template <typename T, size_t S>
	const T* MyArray<T, S>::end(void)	const
	{
		return const_cast<MyArray*>(this)->end();			// end()ָ��ת�ͳ�constָ��
	}



}

 
void syntax_basic_statement_module::test0(void)
{
	using namespace RANGE_FOR_LOOP;
	// ��Χforѭ����������ʹ�������ĵ�������ʵ�֣�ֻҪһ������������begin()��end()�������Ϳ���ʹ�÷�Χforѭ����
	std::vector<int> vi1 = { 0,1,2,3,4,5 };
	int count = 0;
	char str[20];
	MyArray<float, 5> af1;

	std::cout << "test0: ��C++11����Χforѭ�����" << std::endl;

	// ʹ�÷�Χforѭ����������ӡvector�����е�Ԫ�أ�
	std::cout << "\tʹ�÷�Χforѭ����������ӡvector�����е�Ԫ�أ�for(const int& elem: vi1){...}" << std::endl;
	for (const int& elem : vi1)											// �������Ե�����auto elem�����������е�Ԫ�ء�
	{
		sprintf(str, "\tvi1[%d] == ", count++);
		std::cout << str << elem << std::endl;
	}
	std::cout << std::endl;


	// ʹ�÷�Χforѭ��������ֵ�Զ�������MyArray�е�Ԫ�أ���������ӡ��
	std::cout << "\tʹ�÷�Χforѭ��������ֵ�Զ�������MyArray�е�Ԫ�أ���������ӡ��" << std::endl;
	count = 0;
	for (auto& e1 : af1)
	{
		e1 = float(count--);
	}

	auto const& af2 = af1;
	count = 0;

	for (auto& e2 : af2)
	{
		sprintf(str, "\taf2[%d] == ", count++);
		std::cout << str << e2 << std::endl;
	}
	std::cout << std::endl;


}


void syntax_basic_statement_module::test1(void) 
{

}


void syntax_basic_statement_module::test2(void)
{

}


void syntax_basic_statement_module::test3(void)
{

}


void syntax_basic_statement_module::test4(void)
{

}


void syntax_basic_statement_module::test5(void)
{

}


void syntax_basic_statement_module::test6(void)
{

}