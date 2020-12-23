#include <iostream>
#include <string>
#include <typeinfo>
#include <vector>
#include <list>
 

#include <cstdio>


using namespace std;

#define EPS 1e-10					//定义非常小的一个量EPSilon，当浮点数不大于这个值时，视为0
#define PI 3.14159



// STL——list双向链表
/*
**	数据结构基础是双向链表————每个节点含有两个指针，分别指向前一个节点和后一个节点。
**	实现了链表的所有功能。
**
**
** 优势：
** 		任何位置执行插入、删除的时间复杂度都是O(1);
** 		双向链表特性：push_back(),pop_back,push_front,pop_front()
**
**
** 劣势：
**		不支持随机存取，不提供at()函数和下标操作。
*/

 




/***************************************************************************
***************************************************************************/
// 全局变量、类型定义




/***************************************************************************
***************************************************************************/
// extern变量
extern void(*pfun[100])(void);
extern int inputTag, inputNum, interfaceLevel;



/***************************************************************************
***************************************************************************/
// 函数声明
void set_fun_STL_list(void);
void start_STL_list(void);

template <typename T>
void dispList(const list<T>& l);

static void test0(void);
static void test1(void);
static void test2(void);
static void test3(void);
static void test4(void);


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
void set_fun_STL_list (void)
{
	pfun[0] = test0;
	pfun[1] = test1;
}



void start_STL_list (void)
{
	// 界面层级符置为3，进入三级界面：
	interfaceLevel = 3;
	while (3 == interfaceLevel)
	{
		cout << "\n\n\n\n" << endl;
		cout << "**************************MENU: STL_list**********************" << endl;
		cout << "Please choose a demon function to run:" << endl;
		cout << "-2: Run all existed demon function." << endl;
		cout << "-1: Back to the previous interface." << endl;
		cout << "0. test0:  list的构造、析构函数 " << endl;
		cout << "1. test1：list元素的访问、操作" << endl;


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


		case 1:
			(*pfun[1])();


		default:
			printf("Invalid input. Please input again:\n");
			break;
		}


	}
}



// 遍历打印list的函数：
template <typename T>
void dispList(const list<T>& l)
{
	auto beg = l.begin();
	auto end = l.end();

	while (beg != end)
	{
		cout << "\t" << *beg;
		beg++;
	}
	cout << endl;
	return;
}



// test0:  list的构造、析构函数
static void test0(void)
{
	cout << "\n\n\n\n" << endl;
	cout << "test0:  list的构造、析构函数" << endl;

	// explicit list(size_type n);	构造含n个0元素的list；
	cout << "\t构造含n个0元素的list：list<int> l1(5);" << endl;
	list<int> l1(5);
	dispList(l1);
	cout << endl;

	// list(size_type n, T val);	构造含n个val元素的list
	cout << "\t构造含n个val元素的list：list<double> l2(5,8);" << endl;
	list<double> l2(5, 8);
	dispList(l2);
	cout << endl;

	// 使用指针或迭代器，圈定一系列元素来初始化list；
	cout << "\t使用指针或迭代器，圈定一系列元素来初始化list；" << endl;
	int arr[] = { 1,2,3,4,5,6,7,8 };
	int* p1 = arr;
	int* p2 = &arr[8];
	list<int> l31(p1, p2);							// 两个指针或迭代器指定的范围是左闭区间[p1,p2)
	list<int>::iterator it1 = l31.begin();
	list<int>::iterator it2 = l31.end();
	it1++;
	it2--;
	list<int> l32(it1, it2);
	dispList(l31);
	dispList(l32);
	cout << endl;
}


// test1：list元素的访问、操作
static void test1(void)
{
	cout << "\n\n\n\n" << endl;
	cout << "test1：list元素的访问、操作" << endl;


	list<int> l = list<int>();

	// 从首端、尾端放入单个元素：push_front(), push_back()
	//		void push_front(const T& x);
	//		void push_front(T&& x);
	//		void push_back(const T& x);
	//		void push_back(T&& x);
	cout << "\t从首端、尾端放入单个元素：push_front(), push_back()" << endl;
	l.push_front(3);
	l.push_front(2);
	l.push_front(1);
	l.push_back(4);
	l.push_back(5);
	l.push_back(6);
	dispList(l);
	cout << endl;

	// 获取首段、尾端第一个元素：front(), back()
	//		T&  front();
	//		const T& front() const;
	//		T&  back();
	//		const T& back() const;
	cout << "\t获取首段、尾端第一个元素：front(), back()" << endl;
	cout << "\tl.front() = " << l.front() << endl;
	cout << "\tl.back(0 = " << l.back() << endl;
	cout << endl;



	// 插入元素insert();
	//		iterator insert(const_iterator position, const T& x);
	cout << "\t插入元素insert()" << endl;
	list<int> l1(3, 0);
	dispList(l1);
	cout << "\tl1.insert(l1.begin(),11);" << endl;
	l1.insert(l1.begin(), 88);
	dispList(l1);



	//		iterator insert(const_iterator position, size_type n, const T& x);
	list<int>::iterator iter = l1.begin();
	iter++;
	l1.insert(iter, 3, 77);
	cout << "\tl1.insert(iter,3,77);" << endl;
	dispList(l1);



	//		template <class InputIterator>
	//    		iterator insert (const_iterator position, InputIterator first,
	// 		                    InputIterator last);
	//		iterator insert(const_iterator position, initializer_list<T>);
}