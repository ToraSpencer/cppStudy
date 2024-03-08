#include <iostream>
#include <set>
#include <map>
#include <string>
#include <vector>
#include <typeinfo>
#include <algorithm>
#include <utility>  				// 提供pair类型

#include <cstdio>
#include "STL_map键值对集合.h"

 
#define EPS 1e-10					// 定义非常小的一个量EPSilon，当浮点数不大于这个值时，视为0
#define PI 3.14159


 


// 知识点
/*
	 1. std::map, multimap, unordered_map, unordered_multimap基本属性
					1. 元素是pair对象
					2. 不允许元素的键相同，但是multi-开头的std::map和set可以
					3. 如果不是开头为unordered指定的无序容器，则按顺序保存内部的元素。

		2. std::map的几种构造函数格式


		3. std::map、set排序的底层原理——使用运算符"<"来比较元素


		4. 无序关联容器——unordered_map和unordered_set都是使用哈希函数来组织元素。


		5. std::map的常用方法
					1. 增
									insert()
									
					2. 删
									erase()——3重载
									
					3. 查		
									find(), count(), lower_bound(), upper_bound()

					4. 改（访问）		
									下标运算[]
				


*/


virtualModule* STL_map_module::getInstance()		// 线程不安全的单例模式
{
	if (nullptr != p_moduleIns)
	{
		delete p_moduleIns;
	}
	p_moduleIns = new STL_map_module;
	return p_moduleIns;
}

 

struct person
{
	std::string name;
	bool sex;
	int age;
	std::string job;
};


  
void dispPerson(person& p)
{
	if(p.age)
		std::cout << p.name << ", male, age: " << p.age << ", career: " << p.job << std::endl;
	else
		std::cout << p.name << ", female, age: " << p.age << ", career: " << p.job << std::endl;
}


 
// test0: std::map, std::unordered_map常用成员：
void STL_map_module::test0(void)
{
	std::cout << "\n\n\n\n" << std::endl;
	std::cout << "test0: std::map, std::unordered_map常用成员" << std::endl;

	std::map<int, std::string>  mis;
	std::map<int, std::string>::iterator iter1;
	pairPrinter pp; 

	//	1. insert()——插入键值对：
	mis.insert(std::make_pair(6, "xiaohong"));			// 插入pair对象
	mis.insert(std::make_pair(5,"ali"));


	//	2.operator[]()——返回输入键对应值的引用；注：如果输入键不存在，则在字典中生成该键值对，用默认constructor构造其值对象；
	debugDisp("\noperator[](): ");
	debugDisp("mis[5] == ", mis[5]);

	mis[5] = "bli";
	debugDisp("mis[5] == ", mis[5]);
	debugDisp("mis.size() == ", mis.size());

	//			如果输入键不存在，则在字典中生成该键值对，用默认constructor构造其值对象；
	debugDisp("mis[1] == ", mis[1]);
	debugDisp("mis.size() == ", mis.size());
	debugDisp("\n");


	//	3. erase()——输入键或迭代器，删除对应的键值对；
	/*
		删除迭代器指向的键值对：
				iterator erase( const_iterator pos ); 

		删除两个迭代器指定范围内的键值对：
				iterator erase( iterator first, iterator last ); 
				iterator erase( const_iterator first, const_iterator last ); 

		删除输入键对应的键值对，返回删除掉的键值对数量；
				size_type erase( const Key& key );
	*/
	debugDisp("\nerase()方法: ");
	debugDisp("mis.erase(1) == ", mis.erase(1));
	for_each(mis.begin(), mis.end(), pp);
	debugDisp("\n");


	//	4. find()——查找输入的键，返回对应的迭代器，如果没有找到则返回尾后迭代器；
	debugDisp("\nfind()方法: ");
	iter1 = mis.find(5);			
	mis.erase(iter1);										// erase()方法输入迭代器删除元素
	
	for_each(mis.begin(), mis.end(), pp);
	std::cout << std::endl;
}


// test1: multimap的基本使用方法、API
void STL_map_module::test1(void)
{
	// multimap中可以有键相同的元素，相同键的元素会相邻存储。
	// multimap没有下标运算，其他api和std::map类似。
	std::cout << "\n\n\n\n" << std::endl;
	std::cout << "test1: multimap的基本使用方法、api" << std::endl;

	std::multimap<std::string, int> mmss;
	pairPrinter pp;

	mmss.insert(std::make_pair("xiaohong", 16));
	mmss.insert(std::make_pair("xiaoming", 17));
	mmss.insert(std::make_pair("xiaohong", 8));
	mmss.insert(std::make_pair("xiaohong", 2));
	mmss.insert(std::make_pair("laowang", 1));
	for_each(mmss.begin(), mmss.end(), pp);
	std::cout << std::endl;


	// 查找并打印出某一键的全部元素：
	std::cout << "\t查找出multimap中某键的所有元素" << std::endl;
	int num = mmss.count("xiaohong");							// multimap::count()————返回某键元素的个数。
	std::multimap<std::string, int>::iterator iter1 = mmss.find("xiaohong");	// 返回第一个键为xiaohong的元素的迭代器
	for(int i = 1; i<=num; i++)
	{
		std::cout << "\t";
		//pp(*(iter1++));
	}
	std::cout << std::endl;

}


// test2: 应用场景——vector和multimap实现的便于搜索的有序个人信息表
void STL_map_module::test2(void)
{
	std::cout << "\n\n\n\n" << std::endl;
	std::cout << "test2: std::map/multimap应用场景——便于搜索的有序个人信息表" << std::endl;

	person p1 = { "xiaoming", true,  10, "student" };
	person p2 = { "xiaohong", false,  11, "doctor" };
	person p3 = { "xiaolan", true,  12, "teacher" };
	person p4 = { "xiaohuang", true,  10, "teacher" };
	person p5 = { "laowang", true,  13, "worker" };
	person p6 = { "laoli", false,  10, "famer" };
	person p7 = { "xiaoming", false,  10, "famer" };


	// 数据存入向量中
	std::vector<person> vp;
	vp.push_back(p1);
	vp.push_back(p2);
	vp.push_back(p3);
	vp.push_back(p4);
	vp.push_back(p5);
	vp.push_back(p6);
	vp.push_back(p7);


	// 建立便于数据搜索的multimap:
	std::multimap<std::string, int> m_name;			// 姓名搜索表，元素键是该人姓名，值是该人在vp向量中的下标。
	std::multimap<int, int> m_age;					// 年龄搜索表
	for(int i=0; i<=6; i++)
	{
		m_name.insert(std::make_pair(vp[i].name, i));
		m_age.insert(std::make_pair(vp[i].age, i));
	}


	// 搜索并打印数据：
	std::multimap<std::string, int>::iterator iter1;
	std::multimap<int, int>::iterator iter2;
	int num;
	
	//		搜索名字“xiaoming”
	num = m_name.count("xiaoming");
	iter1 = m_name.find("xiaoming");
	for(int i = 1; i<= num; i++)
	{
		std::cout << "\t";
		dispPerson(vp[(*iter1).second]);
		iter1++;
	}
	std::cout << std::endl;

	//		搜索年龄10
	num = m_age.count(10);
	iter2 = m_age.find(10);
	for(int i = 1; i<= num; i++)
	{
		std::cout << "\t";
		dispPerson(vp[(*iter2).second]);
		iter2++;
	}
	std::cout << std::endl;


}


void STL_map_module::test3(void)
{}


void STL_map_module::test4(void)
{}


void STL_map_module::test5(void)
{}


void STL_map_module::test6(void) 
{}