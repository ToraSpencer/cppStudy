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
	所有关联容器：set, map, multiset, multimap底层都是红黑树
	
	特点是插入、删除效率高。
				插入的时候只需要稍做变换，然后把节点的指针指向新的节点就可以了。
				删除的时候类似，稍做变换后把指向删除节点的指针指向其他节点也OK了。
				这里的一切操作就是指针换来换去，和内存移动没有关系，所以不会引发迭代器失效的问题。

	常用方法
	 			begin() end() rbegin rend() 返回迭代器
				clear()   　 清空容器。
				empty() 　　　判断set容器是否为空
				max_size() 　 返回set容器可能包含的元素最大个数
				size() 　　　　 返回当前set容器中的元素个数

	和map的区别是map中的元素有key和value两个数据，set中的元素只有key一个数据。

	放入set中的元素都会自动排序。按照元素的<运算符升序排列。

	set的迭代器天生就是const的，只能读不能写，因为改动set的元素有可能会造成乱序，这是不允许的。


	等价：
		关联容器中不允许存在等价的两个元素，等价和operator==无关，和比较器有关。
		a和b等价的本质是——若(a,b)和(b,a)比较器返回值都是false，则a和b等价。
		默认情形下，STL关联容器的比较器是less<>函数子类模板的实例；即set<string>的默认比较器是less<string>
		less<>函数子的operator()本质上是调用了operator<，若被比较的俩参数前者小于后者，则返回true;
		所以可以说默认比较器本质上取决于operator<

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
		delete p_moduleIns; 
	p_moduleIns = new STL_set_module;
	return p_moduleIns;
}


// 函数子baseTypePrinter——打印基本类型变量
class baseTypePrinter
{
public:
	baseTypePrinter() = default;

	template<typename T>
	void operator()(const T& arg)
	{
		std::cout << arg << "\t";
	}

};


// test0: set的基本使用方法、API 
void STL_set_module::test0() 
{
	debugDisp("\n\n\n\n");
	debugDisp("test0: set的基本使用方法、API：\n");  

	// 基本类型的set——插入到set中的基本类型元素会默认从小到大排序，插入到合适的位置。
	debugDisp("基本类型的set——插入到set中的基本类型元素会默认从小到大排序，插入到合适的位置：");
	{
		set<int> seti1;									 
		set<int>::iterator iter_i; 
		std::pair<set<int>::iterator, bool> retIter;					// insert()方法返回的pair;

		// 1. 1 insert() 方法：
		debugDisp("insert()方法：");
		{
			retIter = seti1.insert(3);
			debugDisp("retIter.second == ", retIter.second);
			debugDisp("*retIter.first == ", *retIter.first);
			retIter = seti1.insert(3);
			debugDisp("retIter.second == ", retIter.second);
			seti1.insert(0);
			seti1.insert(9);
			seti1.insert(8);
			seti1.insert(11);
			seti1.insert(-3);
			for_each(seti1.begin(), seti1.end(), baseTypePrinter{});
			debugDisp(); 

			debugDisp("\n");
		}  

		// 1.2 erase()方法
		debugDisp("erase()方法：");
		{
			size_t retNum{0};
			retNum = seti1.erase(3);
			debugDisp("retNum == ", retNum);
			retNum = seti1.erase(4);
			debugDisp("retNum == ", retNum); 
		}
	} 

	// 		若想要修改元素排序的方式，则构造时传入一个严格弱序(strict weak ordering)比较器
 
	debugDisp("test0() finished.");
}


// test1: set的查找接口
void STL_set_module::test1()
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
		cout << "\tseti1中没有-3这个元素" << endl;

	else
		cout << "\titer_i是指向seti1中元素-3的迭代器。" << endl;


	// lower_bound———返回set中首个小于等于指定元素的元素迭代器
	iter_i1 = seti1.lower_bound(1);
	if(iter_i1 == seti1.end())
		cout << "\tseti1中没有小于等于1的元素" << endl;

	else
		cout << "\tseti1中首个小于等于1的元素为：*iter_i1 == " << *iter_i1 << endl;



	// upper_bound————返回set中首个大于等于指定元素的元素迭代器
	iter_i1 = seti1.upper_bound(1);
	if(iter_i1 == seti1.end())
		cout << "\tseti1中没有大于等于1的元素" << endl;

	else
		cout << "\tseti1中首个大于等于1的元素为：*iter_i1 == " << *iter_i1 << endl;


	// equal_range————返回一个pari，分别包含lower_bound和upper_bound可以返回的迭代器
	pi1 = seti1.equal_range(1);
	if(pi1.first != seti1.end())
		cout << "\t*pi1.first == " << *pi1.first << endl;
	if(pi1.second != seti1.end())
		cout << "\t*pi1.second == " << *pi1.second << endl;

}


// test2: 使用自定义比较器的set:
namespace COMPARER1
{
	// 自定义浮点数比较器；注意！！比较器中要定义“严格弱序”，只能用大于号或小于号，等于时不可返回true
	struct floatComparer
	{
	public:
		bool operator()(const float num1, const float num2) const
		{
			int i1 = static_cast<int>(num1);
			int i2 = static_cast<int>(num2);
			if (i1 < i2)
				return true;	// 返回true表示认为num1小于num2;
			else
				return false;
		};
	};

	// 自定义指针比较器
	struct intPtrComparer
	{
	public:
		bool operator()(const int* pi1, const int* pi2) const
		{
			if (*pi1 < *pi2)
				return true;
			else
				return false;
		}
	};

}
 
void STL_set_module::test2() 
{
	using namespace COMPARER1;

	set<float, floatComparer> fSet;
	fSet.insert(0.5);
	fSet.insert(1);
	fSet.insert(1.1);		// 在自定义比较器下，1和1.1是等价的，set中不允许存在等价的元素，所以此行操作插入不成功。
	traverseSTL(fSet, disp<float>());
}


// test3: 存放指针的set————《effective STL》
/*
	若关联容器中存放的元素是指针，则应该自定义一个比较指针指向元素的比较器。
	否则使用默认比较器比较的将是指针的值。

*/
void STL_set_module::test3() 
{
	using namespace COMPARER1;
	using IPTR = int*;
	IPTR ipArr[5];
	set<IPTR> s1;
	set<IPTR, intPtrComparer> s2;
	for (unsigned i = 0; i<5; ++i)
	{
		ipArr[i] = new int(i + 1);
		s1.insert(ipArr[i]);
		s2.insert(ipArr[i]);
	}

	for (const auto& elem : s1)		// s1中的排序很可能是错误的，因为排序依据的是指针的值
		cout << *elem << ", ";
	cout << endl;

	for (const auto& elem : s2)		// s2使用了自定义比较器，排序是正确的。
		cout << *elem << ", ";
	cout << endl;
}


// test4: std::unordered_set<>——哈希表
void STL_set_module::test4() 
{



	debugDisp("test4() finished.");
}


void STL_set_module::test5() {}


void STL_set_module::test6() {}