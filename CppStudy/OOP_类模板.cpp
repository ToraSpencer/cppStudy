#include <string>
#include<iostream>
#include <cstddef>
#include <memory>

#include <cstdio>

using namespace std;


/*
	类模板

*/

 
// 全局变量、类型定义
template <typename T, size_t N>
class Foo				// 封装起来的数组类模板，定义了一些操作
{
private:
	// 私有数据
	T arr[N];

public:
	// 构造、析构函数
	Foo() = default;						// =default：显示地要求编译器自动生成一个无参构造函数。							
	Foo(initializer_list<T> l);			// 使用initializer_list来构造
	Foo(T*, int);								// 输入数组首地址，和容量，来构造
	~Foo();		


	// 其他方法
	void disp(void);


};
 
// extern变量
extern void(*pfun[100])(void);
extern int inputTag, inputNum, interfaceLevel;

 
// 函数声明

void set_fun_OOP_class_template(void);
void start_OOP_class_template(void);

static void test0(void);
static void test1(void);
static void test2(void);
static void test3(void);
static void test4(void);

 
// extern函数
extern void traverse_pfun(void);

 
// 自定义类的实现


 
// 函数定义
template <typename T, size_t N>
Foo<T, N>::Foo(initializer_list<T> l)
{
	// 需要判断初始化列表l中的元素是否大于N，大于N的话要么抛出异常，要么只使用前N个元素
	// this->arr = new T[N];
	T* pData = this->arr;
	for(auto iter = begin(l); iter!=end(l); iter++)
	{
		*pData = *iter;
		  pData++;
	} 	
	cout << "A Foo object has been instantiated." << endl;
}



template <typename T, size_t N>
Foo<T, N>::Foo(T* p, int num)
{
	// 若num不在合理的范围内，抛出异常，或者返回一个空的Foo对象。
	// this->arr = new T[N];
	T* pData = this->arr;

	for(int i = 1; i <= num; i++)
	{
		*pData = *p;
		pData++;
		p++;
	}
	cout << "A Foo object has been instantiated." << endl;

}



template <typename T, size_t N>
Foo<T, N>::~Foo()
{	
 
	cout<< "A Foo object has been eliminated." << endl;

}



template <typename T, size_t N>
void Foo<T, N>::disp(void)
{
	for(auto elem:(this->arr))
	{
		cout << "\t" << elem;
	}
	cout << endl;
}





void set_fun_OOP_class_template(void) 
{
  pfun[0] = test0;
}



void start_OOP_class_template(void) 
{
	// 界面层级符置为3，进入三级界面：
	interfaceLevel = 3;
	while (3 == interfaceLevel)
	{
		cout << "\n\n\n\n" << endl;
		cout << "**************************MENU: OOP_class_template**********************" << endl;
		cout << "Please choose a demon function to run:" << endl;
		cout << "-2: Run all existed demon function." << endl;
		cout << "-1: Back to the previous interface." << endl;
		cout << "0: test0: 简单的自定义类模板的使用" << endl;


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

		default:
			printf("Invalid input. Please input again:\n");
			break;
		}


	}
}



// test0: 简单的自定义类模板的使用.
static void test0()
{
	int arri[10] = {1,2,3,4,5,6,7,8,9,10};
	Foo<float, 5> Farrf1;
	Foo<int, 10> Farri1(arri, 10);
	Foo<int, 5> Farri2 = {-1,-2,-3,-4,-5};
	
	cout << "\n\n\n\n" << endl;
	cout << "test0: 简单的自定义类模板的使用" << endl;
	Farrf1.disp();
	Farri1.disp();
	Farri2.disp();



}

