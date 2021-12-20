#include <string>
#include <iostream>
#include <fstream>
#include <vector>						//vector类模板在头文件<vector>中
#include <list>
#include <deque>
#include <cstdio>

#include "STL_线性容器.h"


// 知识点
/*
				1. vector底层是可动态扩充容量的顺序表，支持随机存取，但是插入删除费时。
				
				2. vector容量更改时重新分配内存，所有迭代器失效
				
				3. vector执行插入操作时，若没有发生容量更改内存重新分配，则插入元素后的迭代器失效，前面的迭代器依然有效。
				
				4. （C++11）STL容器都可以使用列表初始化。

				5.  线性容器的增删查改
							增：
									push_back()			
									insert()			可以在任意位置增加元素，可以一次性插入多个元素。
									emplace(), 
									emplace_back()
									注意：forwad_list不支持push_back()和emplace_back()		

							删：
									erase() 
									clear() 
							
							查：
									线性容器没有find(), count()方法，关联容器有，可以使用STL算法库中的find函数实现。

							改：
									swap() 
									assign()
									resize()			// 输入是元素数，不是字节数。

									
									

				6. 底层结构
							vector————			顺序表
							list————			双向链表
							forward_list————	单向链表
							deque——				双端队列
							

*/




virtualModule* STL_linear_container_module::getInstance()		// 线程不安全的单例模式
{
	if (nullptr != p_moduleIns)
	{
		delete p_moduleIns;
	}
	p_moduleIns = new STL_linear_container_module;
	return p_moduleIns;
}




// test0():向量构造函数、初始化方法。
void STL_linear_container_module::test0(void)
{
	std::vector<int> vi1;												// 构造一个空向量。


	std::cout << "\n\n\n\n" << std::endl;
	std::cout << "test0(): 向量构造函数、初始化方法。" << std::endl << std::endl;

	std::cout << "\tvi1.empty == " << vi1.empty() << std::endl;
	std::cout << std::endl;


	// 1. 指定向量的容量。
	std::vector<int> vi2(3);
	std::cout << "vi2.capacity() ==  " << vi2.capacity() << std::endl;
	traverseSTL(vi2, disp<int>);
	std::cout << std::endl;

	vi2.push_back(1);
	vi2.push_back(2);
	vi2.push_back(3);
	vi2.push_back(4);

	// 	1.1 push_back进去四个元素之后，vi2会自动扩容：
	std::cout << "vi2.size() == " << vi2.size() << std::endl;
	traverseSTL(vi2, disp<int>);
	std::cout << std::endl << std::endl;


	// 2. 指定向量的容量和元素统一初始值。
	std::vector<int> vi3(3, 10); 		
	traverseSTL(vi3, disp<int>);
	std::cout << std::endl;

	// 3. 使用初始化列表初始化vector和数组
	std::vector<int> vi4 = {1,2,3,4};										// 上下两种实例化对象的语句是等效的。
	int arr[] = { 1, 2, 3 };


	// 4. 输入数组来构造向量。
	std::vector<int> vi5(arr, arr + 3);									
}



// test1(): 线性容器的增删查改
void STL_linear_container_module::test1(void)
{
	std::cout << "\n\n\ntest1():线性容器的增删查改" << std::endl << std::endl;

	// lambda——执行条件判断的函数子
	auto badValue = [](const int& num) -> bool
	{
		if (num == 4)
		{
			return true;
		}
		else
		{
			return false;
		}
	};

	std::vector<int> vi1{ 1,2,3,4,5,4,6,7,8,9,4 };
	std::list<int> li1{ 1,2,3,4,5,4,6,7,8,9,4 };
	std::deque<int> di1{ 1,2,3,4,5,4,6,7,8,9,4 };

	// 增——insert()方法插入元素
	auto iter1 = vi1.begin();
	iter1++;
	iter1 = vi1.insert(iter1, 999);						// 在当前迭代器指向的元素之前插入新元素；若成功，则返回插入新元素的迭代器；
	traverseSTL(vi1, disp<int>);
	std::cout << "*iter1 == " << *iter1 << std::endl;
	
	//		数组区间拷贝到顺序表STL容器——vector中
	int arri[] = { 1,2,3,4,5,6,77,88,999 };
	std::vector<int> vi2(9);
	memcpy(&vi2[0], &arri[0], sizeof(int) * 9);
	traverseSTL(vi2, disp<decltype(vi1[0])>);

	// 删除元素：

	//		earase()重载1——删除迭代器指定的元素
	vi1.erase(vi1.begin());
	traverseSTL(vi1, disp<decltype(vi1[0])>);

	//		erase()重载2——删除一对迭代器指定范围的元素
	li1.erase(++li1.begin(), --li1.end());	// list的迭代器是双向迭代器，不是vector那样的随机访问迭代器，不支持常数加减功能,++可以。
	traverseSTL(li1, disp<decltype(*li1.begin())>);

	//		erase()方法和remove_if()接口配合成特殊的操作，条件删除STL线性容器中的元素
	vi1.erase(remove_if(vi1.begin(), vi1.end(), badValue), vi1.end());
	traverseSTL(vi1, disp<decltype(vi1[0])>);

	//		erase()方法返回值的应用——返回值是被删除元素下一个元素的迭代器
	for (std::deque<int>::iterator iter = di1.begin(); iter != di1.end();)
	{
		// 条件删除元素，并且在删除的时候打印字符串。
		if (badValue(*iter))
		{
			std::cout << "删除了一个元素。" << std::endl;
			iter = di1.erase(iter);		// 获得被删除元素下一个元素的迭代器
		}
		else
		{
			++iter;
		}
	}
	traverseSTL(di1, disp<decltype(*di1.begin())>);

}



// test2():vector，list的迭代器
void STL_linear_container_module::test2(void)
{
	std::cout << "\n\n\ntest3():vector的迭代器" << std::endl << std::endl;

	std::vector<int>vi;
	std::vector<int>::iterator iter_i;
	std::vector<int>::const_iterator citer_i;

	vi.push_back(1);
	vi.push_back(2);
	vi.push_back(3);
	vi.push_back(4);
	vi.push_back(5);
	vi.push_back(6);

	// 1. 使用const_iterator来遍历vector中所有元素。
	std::cout << "use const_iterator to traverse all the items on the vector container:" << std::endl;
	for (citer_i = vi.begin(); citer_i != vi.end(); citer_i++)
	{
		std::cout << *citer_i << std::endl;
	}							//const_iterator只能访问元素，不可以修改元素。
	std::cout << std::endl;


	// 2. 使用iterator来修改vector中的元素。
	std::cout << "use iterator to change the vector's item's value: " << std::endl;
	iter_i = vi.begin();								//迭代器指向第一个元素。
	*iter_i = -1;
	std::cout << "vi[0] == " << *iter_i << std::endl;
	iter_i++;
	*iter_i = -2;
	std::cout << "vi[1] == " << *iter_i << std::endl;
	iter_i += 1;
	*iter_i = -3;
	std::cout << "vi[2] == " << *iter_i << std::endl;
	std::cout << std::endl;

	// 3. list的迭代器
	std::list<int> numlist{ 1,2,3,4,5,6,7,8,9 };

	//			3.1 std::list的迭代器只支持++和--，不支持一次性移任意常数位。
	for (unsigned i = 0; i < 2; ++i)
	{
		numlist.erase(numlist.begin());
		numlist.erase(--numlist.end());
	}
	traverseSTL(numlist, disp<int>);

	//			3.2 std::list的迭代器执行erase()之后迭代器失效，返回删除元素下一个元素的迭代器
	numlist = std::list<int>{ 1,2,3,4,5,6,7,8,9 };
	auto iter1 = numlist.begin();
	iter1 = numlist.erase(iter1);
	std::cout << "*iter1 == " << *iter1 << std::endl;
	traverseSTL(numlist, disp<int>);

}



// test3(): 优先使用容器操作区间的方法，而不是操作单个元素的方法——effective STL
void STL_linear_container_module::test3(void)
{
	// assign()——范围性地初始化本容器。
	std::vector<int> vi1, vi2;
	vi1.assign(6, 999);				// 用六个999初始化vi1容器

	auto iter1 = vi1.begin();
	auto iter2 = vi1.end();
	iter1 += 3;
	vi2.assign(iter1, iter2);		// 用迭代器iter1,iter2指示的vi2中的区间初始化vi1;

	traverseSTL(vi1, disp<decltype(vi1[0])>);
	traverseSTL(vi2, disp<decltype(vi2[0])>);
 
}




// test4()——vector迭代器失效问题
void STL_linear_container_module::test4(void)
{
	// vector的内存重新分配的话，所有迭代器都会失效。

	std::vector<int> v1 = {1,2,3};		// 初始时v1容量为3，可以使用v1.capacity()查看。
	auto iter1 = v1.begin();
	v1.push_back(4);							// 此时v1容量发生改变，内存重新分配，所有迭代器失效。
	std::cout << *iter1 << std::endl;			// 此时程序会崩溃出错，因为迭代器已经失效。

}




// test5()——元素放入线性容器中的拷贝过程
void STL_linear_container_module::test5(void)
{
	// 指针、或行为像指针的类对象被存入vector时，发生的是浅拷贝
	int num1 = 999;
	int num2 = 888;
	int num3 = 777;
	int* p1 = &num1;
	int* p2 = &num2;
	int* p3 = &num3;

	std::vector<int*> vec;
	vec.push_back(p1);
	vec.push_back(p2);
	vec.push_back(p3);

	for (const auto& elem : vec)
	{
		std::cout << *elem << ", ";
	}
	std::cout << std::endl;

	*p1 = 111;
	*p2 = 222;
	*p3 = 333;

	for (const auto& elem : vec)
	{
		std::cout << *elem << ", ";
	}
	std::cout << std::endl;

}




// test6()——应用场景
void STL_linear_container_module::test6(void)
{
	// 应用场景——处理string对象，然后通过该对象生成相应的文件句柄。
	//		处理下面的string对象，希望在文件名后面添加后缀"_x", "_y"，表示x和y坐标的向量数据。
	std::string str = "data.dat";


	// 查——find()函数；线性容器本身没有find方法
	auto iter = find(str.begin(), str.end(), 'x');
	if (iter == str.end())
	{
		std::cout << "error" << std::endl;
	}
	auto dis = distance(str.begin(), iter);


	// 增——insert()方法——任意位置插入，并且可以一次性插入多个元素
	/*
		basic_string& insert( size_type index,
								const CharT* s
								);
	*/
	str.insert(dis, "_x");
	std::cout << str << std::endl;
	std::fstream file(str, std::ios::out);
	file.close();

}

