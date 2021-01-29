#include <iostream>
#include <set>
#include <map>
#include <string>
#include <vector>
#include <typeinfo>
#include <algorithm>
#include <utility>  				// 提供pair类型


#include <cstdio>

#include "example.h" 
using namespace std;

#define EPS 1e-10					// 定义非常小的一个量EPSilon，当浮点数不大于这个值时，视为0
#define PI 3.14159


 


// 知识点
/*
	 1. map, multimap, unordered_map, unordered_multimap基本属性
					1. 元素是pair对象
					2. 不允许元素的键相同，但是multi-开头的map和set可以
					3. 如果不是开头为unordered指定的无序容器，则按顺序保存内部的元素。

		2. map的几种构造函数格式


		3. map、set排序的底层原理——使用运算符"<"来比较元素


		4. 无序关联容器——unordered_map和unordered_set都是使用哈希函数来组织元素。


		5. map的常用方法
					1. 增
									insert()
									
					2. 删
									erase()——3重载
									
					3. 查		
									find(), count(), lower_bound(), upper_bound()

					4. 改（访问）		
									下标运算[]
				


*/




/***************************************************************************
***************************************************************************/
// 全局变量、类型定义
struct person
{
	string name;
	bool sex;
	int age;
	string job;
};



/***************************************************************************
***************************************************************************/
// extern变量
extern void(*pfun[100])(void);
extern int inputTag, inputNum, interfaceLevel;



/***************************************************************************
***************************************************************************/
// 函数声明
inline void dispPerson(person&); 

void set_fun_STL_map(void);
void start_STL_map(void);

static void test0(void);
static void test1(void);
static void test2(void);
static void test3(void);
static void test4(void);
static void test5(void);


/***************************************************************************
***************************************************************************/
// extern函数
void traverse_pfun(void);


/***************************************************************************
***************************************************************************/
// 自定义类的实现


/***************************************************************************
***************************************************************************/
// 函数定义
inline void dispPerson(person& p) 
{
	if(p.age)
	{
		cout << p.name << ", male, age: " << p.age << ", career: " << p.job << endl;
	}
	else
	{
		cout << p.name << ", female, age: " << p.age << ", career: " << p.job << endl;
	}
	
	
}



void set_fun_STL_map(void)
{
	pfun[0] = test0;
	pfun[1] = test1;
	pfun[2] = test2;
	pfun[3] = test3;
	pfun[4] = test4;
	pfun[5] = test5;
}



void start_STL_map(void)
{
	// 界面层级符置为3，进入三级界面：
	interfaceLevel = 3;
	while (3 == interfaceLevel)
	{
		cout << "\n\n\n\n" << endl;
		cout << "**************************MENU: STL——map**********************" << endl;
		cout << "Please choose a demon function to run:" << endl;
		cout << "-2: Run all existed demon function." << endl;
		cout << "-1: Back to the previous interface." << endl;
		cout << "0. test0: map的基本使用方法、API" << endl;
		cout << "1. test1: multimap的基本使用方法、API" << endl;
		cout << "2. test2: map/multimap应用场景——便于搜索的有序个人信息表" << endl;

		inputTag = scanf("%d", &inputNum);

		// 若输入值不是整数，重新输入。
		if (inputTag != 1)
		{
			printf("Invalid input. Please input again:\n");
			setbuf(stdin, NULL);
			continue;
		}

		// 对三级界面输入值的响应。
		switch (inputNum)
		{
		case -2:
			traverse_pfun();
			break;

		case -1:
			interfaceLevel = 2;
			break;

		case 0:
			(*pfun[0])();
			break;

		case 1:
			(*pfun[1])();
			break;

		case 2:
			(*pfun[2])();
			break;

		case 3:
			(*pfun[3])();
			break;

		case 4:
			(*pfun[4])();
			break;

		case 5:
			(*pfun[5])();
			break;

		default:
			printf("Invalid input. Please input again:\n");
			break;
		}


	}
}


// test0: map的基本使用方法、API
static void test0(void) 
{
	cout << "\n\n\n\n" << endl;
	cout << "test0: map的基本使用方法、API" << endl;

	map<int, string>  mis;
	map<int, string>::iterator iter1;
	pairPrinter pp;


	// 增删查改
	cout << "\tmap的增删查改：" << endl;

	//			使用insert来插入元素
	mis.insert(make_pair(6, "xiaohong"));			// 插入pair对象
	mis.insert(make_pair(5,"ali"));

	//			使用下标运算符来增加、修改元素
	mis[1] = "xiaoming";								// 下标运算符：无该键时创建该键，有该键时修改该键。						
	mis[33] = "laowang";
	mis[33] = "laoli";	
	for_each(mis.begin(), mis.end(), pp);
	cout << endl;

	//			erase()方法输入键删除元素
	mis.erase(1);				
	for_each(mis.begin(), mis.end(), pp);
	cout << endl;


	//			find()方法输入键查找元素
	iter1 = mis.find(33);
	mis.erase(iter1);				// erase()方法输入迭代器删除元素
	for_each(mis.begin(), mis.end(), pp);
	cout << endl;
}





// test1: multimap的基本使用方法、API
static void test1(void) 
{

	// multimap中可以有键相同的元素，相同键的元素会相邻存储。
	// multimap没有下标运算，其他api和map类似。
	cout << "\n\n\n\n" << endl;
	cout << "test1: multimap的基本使用方法、api" << endl;

	multimap<string, int> mmss;
	pairPrinter pp;

	mmss.insert(make_pair("xiaohong", 16));
	mmss.insert(make_pair("xiaoming", 17));
	mmss.insert(make_pair("xiaohong", 8));
	mmss.insert(make_pair("xiaohong", 2));
	mmss.insert(make_pair("laowang", 1));
	for_each(mmss.begin(), mmss.end(), pp);
	cout << endl;


	// 查找并打印出某一键的全部元素：
	cout << "\t查找出multimap中某键的所有元素" << endl;
	int num = mmss.count("xiaohong");							// multimap::count()————返回某键元素的个数。
	multimap<string, int>::iterator iter1 = mmss.find("xiaohong");	// 返回第一个键为xiaohong的元素的迭代器
	for(int i = 1; i<=num; i++)
	{
		cout << "\t";
		//pp(*(iter1++));
	}
	cout << endl;

}



// test2: 应用场景——vector和multimap实现的便于搜索的有序个人信息表
static void test2(void) 
{
	cout << "\n\n\n\n" << endl;
	cout << "test2: map/multimap应用场景——便于搜索的有序个人信息表" << endl;

	person p1 = { "xiaoming", true,  10, "student" };
	person p2 = { "xiaohong", false,  11, "doctor" };
	person p3 = { "xiaolan", true,  12, "teacher" };
	person p4 = { "xiaohuang", true,  10, "teacher" };
	person p5 = { "laowang", true,  13, "worker" };
	person p6 = { "laoli", false,  10, "famer" };
	person p7 = { "xiaoming", false,  10, "famer" };


	// 数据存入向量中
	vector<person> vp;
	vp.push_back(p1);
	vp.push_back(p2);
	vp.push_back(p3);
	vp.push_back(p4);
	vp.push_back(p5);
	vp.push_back(p6);
	vp.push_back(p7);


	// 建立便于数据搜索的multimap:
	multimap<string, int> m_name;			// 姓名搜索表，元素键是该人姓名，值是该人在vp向量中的下标。
	multimap<int, int> m_age;					// 年龄搜索表
	for(int i=0; i<=6; i++)
	{
		m_name.insert(make_pair(vp[i].name, i));
		m_age.insert(make_pair(vp[i].age, i));
	}


	// 搜索并打印数据：
	multimap<string, int>::iterator iter1;
	multimap<int, int>::iterator iter2;
	int num;
	
	//		搜索名字“xiaoming”
	num = m_name.count("xiaoming");
	iter1 = m_name.find("xiaoming");
	for(int i = 1; i<= num; i++)
	{
		cout << "\t";
		dispPerson(vp[(*iter1).second]);
		iter1++;
	}
	cout << endl;

	//		搜索年龄10
	num = m_age.count(10);
	iter2 = m_age.find(10);
	for(int i = 1; i<= num; i++)
	{
		cout << "\t";
		dispPerson(vp[(*iter2).second]);
		iter2++;
	}
	cout << endl;


}



static void test3(void) 
{}



static void test4(void)
{}



static void test5(void)
{}