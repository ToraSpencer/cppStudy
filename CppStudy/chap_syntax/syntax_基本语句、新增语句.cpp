#include <cstdio>
#include <string>
#include <iostream>
#include <vector>						//vector类模板在头文件<vector>中

#include <cstdio>


#include "chap_syntax.h"



/*
	while(){}

	do()	while{};

	for循环

	(C++11)范围for循环：
	格式：for(元素类型 elem:  c) {...}					// c是容器对象。


	switch case



*/

 


// test0: （C++11）范围for循环语句
namespace RANGE_FOR_LOOP 
{

	template <typename T, size_t S>
	class MyArray														// 自定义数组容器类模板，带类型参数T，和非类型参数S
	{
	public:
		T& operator[](size_t i);									// 重载下标运算符
		const T& operator[](size_t i) const;					// 重载下标运算符，const版本函数重载。
																//				因为需要MyArray的const对象使用下标运算符时，返回的元素引用也是const

		T* begin();													// 获取起始迭代器。
		const T* begin()	const;							// 获取起始迭代器，const版本函数重载
																//				因为需要MyArray的const对象使用begin函数时，返回的迭代器也是const的
																//				注意这里是底层const，迭代器指向的数据是常量，迭代器自身不是常量，指向的位置可以改变。
		T* end();													// 获取尾后迭代器。
		const T* end() const;



	private:
		//	成员数据：
		T arr[S];													// 元素类型为T， 容量为S的数组。

	};


	template <typename T, size_t S>
	T&  MyArray<T, S>:: operator[](size_t i)
	{
		return this->arr[i];												// 可以增加异常保护：当下标越界的时候抛出异常。
	}


	template <typename T, size_t S>
	const T& MyArray<T, S>:: operator[](size_t i) const
	{
		return const_cast<MyArray&>(*this)[i];				// ？？？？
	}


	template <typename T, size_t S>
	T* MyArray<T, S>::begin()
	{
		return arr;
	}


	template <typename T, size_t S>
	const T* MyArray<T, S>::begin()	const
	{
		return const_cast<MyArray*>(this)->begin();
	}


	template <typename T, size_t S>
	T* MyArray<T, S>::end()
	{
		return (arr + S);
	}


	template <typename T, size_t S>
	const T* MyArray<T, S>::end()	const
	{
		return const_cast<MyArray*>(this)->end();			// end()指针转型成const指针
	}



}

 


	void syntax_basic_statement_module::test0()
	{
		using namespace RANGE_FOR_LOOP;
		// 范围for循环本质上是使用容器的迭代器来实现，只要一个容器定义了begin()和end()函数，就可以使用范围for循环：
		std::vector<int> vi1 = { 0,1,2,3,4,5 };
		int count = 0;
		char str[20];
		MyArray<float, 5> af1;

		std::cout << "test0: （C++11）范围for循环语句" << std::endl;

		// 使用范围for循环语句遍历打印vector对象中的元素：
		std::cout << "\t使用范围for循环语句遍历打印vector对象中的元素：for(const int& elem: vi1){...}" << std::endl;
		for (const int& elem : vi1)											// 可以无脑地是用auto elem来声明容器中的元素。
		{
			sprintf(str, "\tvi1[%d] == ", count++);
			std::cout << str << elem << std::endl;
		}
		std::cout << std::endl;


		// 使用范围for循环遍历赋值自定义容器MyArray中的元素，并遍历打印。
		std::cout << "\t使用范围for循环遍历赋值自定义容器MyArray中的元素，并遍历打印。" << std::endl;
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


	void syntax_basic_statement_module::test1()
	{

	}


	void syntax_basic_statement_module::test2()
	{

	}


	void syntax_basic_statement_module::test3()
	{

	}


	void syntax_basic_statement_module::test4()
	{

	}


	void syntax_basic_statement_module::test5()
	{

	}


	void syntax_basic_statement_module::test6()
	{

	}


	void syntax_basic_statement_module::test7() {}


	virtualModule* syntax_basic_statement_module::getInstance()		// 线程不安全的单例模式
	{
		if (nullptr != p_moduleIns)
		{
			delete p_moduleIns;
		}
		p_moduleIns = new syntax_basic_statement_module;
		return p_moduleIns;
	} 