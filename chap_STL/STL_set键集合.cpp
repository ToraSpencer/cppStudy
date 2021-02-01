#include <iostream>
#include <set>
#include <string>
#include <typeinfo>
#include <algorithm>
#include <utility>



#include <cstdio>


#include "STL_set键集合.h" 
using namespace std;

#define EPS 1e-10					//定义非常小的一个量EPSilon，当浮点数不大于这个值时，视为0
#define PI 3.14159


// 知识点
/*
	1. 所有关联容器：set, map, multiset, multimap底层都是红黑树
	
	2. 特点是插入、删除效率高。
				插入的时候只需要稍做变换，然后把节点的指针指向新的节点就可以了。
				删除的时候类似，稍做变换后把指向删除节点的指针指向其他节点也OK了。
				这里的一切操作就是指针换来换去，和内存移动没有关系，所以不会引发迭代器失效的问题。

	3. 常用方法
	 			begin() end() rbegin rend() 返回迭代器
				clear()   　 清空容器。
				empty() 　　　判断set容器是否为空
				max_size() 　 返回set容器可能包含的元素最大个数
				size() 　　　　 返回当前set容器中的元素个数

	4. 和map的区别是map中的元素有key和value两个数据，set中的元素只有key一个数据。

	5. 放入set中的元素都会自动排序。按照元素的<运算符升序排列。

	6. set的迭代器天生就是const的，只能读不能写，因为改动set的元素有可能会造成乱序，这是不允许的。

*/












// STL——关联容器：set, map, multiset, multimap
/*
		set 					唯一键的集合，按照键排序
		map 					键值对的集合，按照键排序，键是唯一的
		multiset 				键的集合，按照键排序
		multimap 				键值对的集合，按照键排序
 
共性：
		底层是红黑树实现。
		查找迅速————O(log n) 复杂度
		不可以直接修改元素，只能先删后插
		都含有比较器value_compare，是一个函数子，用来规定集合中键的排序的规则
*/




// STL——无序关联容器：unordered_set, unordered_map, unordered_multiset, unordered_multimap
/*
		(C++11 起)unordered_set 						唯一键的集合，按照键生成散列
		(C++11 起)unordered_map 						键值对的集合，按照键生成散列，键是唯一的
		(C++11 起)unordered_multiset					键的集合，按照键生成散列
		(C++11 起)unordered_multimap 					键值对的集合，按照键生成散列
 

共性：
		底层是哈希结构。
		查找迅速—————均摊 O(1) ，最坏情况 O(n) 的复杂度

*/


virtualModule* STL_set_module::getInstance()		// 线程不安全的单例模式
{
	if (nullptr != p_moduleIns)
	{
		delete p_moduleIns;
	}
	p_moduleIns = new STL_set_module;
	return p_moduleIns;
}





// test0: set的基本使用方法、API
void STL_set_module::test0(void) 
{
	cout << "\n\n\n\n" << endl;
	cout << "test0: set的基本使用方法、API" << endl;

	// 基本类型的set:
	// 		插入到set中的基本类型元素会默认从小到大排序，插入到合适的位置。
	set<int> seti1;									// 构造方法1
	set<int>::iterator iter_i;
	baseTypePrinter btp;

	seti1.insert(1);
	seti1.insert(0);
	seti1.insert(9);
	seti1.insert(8);
	seti1.insert(11);
	seti1.insert(-3);

	for_each(seti1.begin(), seti1.end(), btp);


	// 		若想要修改元素排序的方式，则构造时

 


}


// test1: set的查找接口
void STL_set_module::test1(void)
{
	cout << "\n\n\n\n" << endl;
	cout << "test1: set的查找接口" << endl;

	set<int> seti1;									// 构造方法1
	set<int>::iterator iter_i1;
	pair<set<int>::iterator, set<int>::iterator> pi1;

	seti1.insert(1);
	seti1.insert(0);
	seti1.insert(9);
	seti1.insert(8);
	seti1.insert(11);
	seti1.insert(-3);

	//	find————查找成功返回指向搜索结果的迭代器，查找失败返回尾后迭代器
	iter_i1 = seti1.find(-3);					
	if(iter_i1 == seti1.end())
	{
		cout << "\tseti1中没有-3这个元素" << endl;

	}
	else
	{
		cout << "\titer_i是指向seti1中元素-3的迭代器。" << endl;

	}


	// lower_bound———返回set中首个小于等于指定元素的元素迭代器
	iter_i1 = seti1.lower_bound(1);
	if(iter_i1 == seti1.end())
	{
		cout << "\tseti1中没有小于等于1的元素" << endl;

	}
	else
	{
		cout << "\tseti1中首个小于等于1的元素为：*iter_i1 == " << *iter_i1 << endl;

	}



	// upper_bound————返回set中首个大于等于指定元素的元素迭代器
	iter_i1 = seti1.upper_bound(1);
	if(iter_i1 == seti1.end())
	{
		cout << "\tseti1中没有大于等于1的元素" << endl;

	}
	else
	{
		cout << "\tseti1中首个大于等于1的元素为：*iter_i1 == " << *iter_i1 << endl;

	}


	// equal_range————返回一个pari，分别包含lower_bound和upper_bound可以返回的迭代器
	pi1 = seti1.equal_range(1);
	if(pi1.first != seti1.end())
	{
		cout << "\t*pi1.first == " << *pi1.first << endl;
	}
	if(pi1.second != seti1.end())
	{
	cout << "\t*pi1.second == " << *pi1.second << endl;
	}


}


void STL_set_module::test2(void) {}


void STL_set_module::test3(void) {}


void STL_set_module::test4(void) {}


void STL_set_module::test5(void) {}


void STL_set_module::test6(void) {}