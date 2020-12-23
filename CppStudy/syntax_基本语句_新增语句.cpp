#include <cstdio>
#include <string>
#include <iostream>
#include <vector>						//vector类模板在头文件<vector>中

#include <cstdio>


using namespace std;




/*
					while(){}
					do()	while{};
					for循环
					（C11）范围for循环
					switch case

			(C++11)范围for循环：
					格式：for(元素类型 elem:  c) {...}					// c是容器对象。


*/





/***************************************************************************
***************************************************************************/
// 全局变量、类型定义
template <typename T, size_t S>
class MyArray														// 自定义数组容器类模板，带类型参数T，和非类型参数S
{
public:
	T& operator[](size_t i);									// 重载下标运算符
	const T& operator[](size_t i) const;					// 重载下标运算符，const版本函数重载。
																			//				因为需要MyArray的const对象使用下标运算符时，返回的元素引用也是const

	T* begin(void);													// 获取起始迭代器。
	const T* begin(void)	const;							// 获取起始迭代器，const版本函数重载
																			//				因为需要MyArray的const对象使用begin函数时，返回的迭代器也是const的
																			//				注意这里是底层const，迭代器指向的数据是常量，迭代器自身不是常量，指向的位置可以改变。
	T* end(void);													// 获取尾后迭代器。
	const T* end(void) const;



private:
	//	成员数据：
	T arr[S];													// 元素类型为T， 容量为S的数组。

};



/***************************************************************************
***************************************************************************/
// extern变量
extern void(*pfun[100])(void);
extern int inputTag, inputNum, interfaceLevel;


/***************************************************************************
***************************************************************************/
// 函数声明
void set_fun_syntax_statement(void);
void start_syntax_statement(void);


static void test0(void);
static void test1(void);
static void test2(void);
static void test3(void);
static void test4(void);


/***************************************************************************
***************************************************************************/
// extern函数
template <typename T>
extern void traverse_vector(const vector<T>&, void(*pVisit)(const T&));

extern void traverse_pfun(void);



/***************************************************************************
***************************************************************************/
// 自定义类的实现
template <typename T, size_t S>
T&  MyArray<T,S>:: operator[](size_t i) 
{
	return this->arr[i];												// 可以增加异常保护：当下标越界的时候抛出异常。
}


template <typename T, size_t S>
const T& MyArray<T, S>:: operator[](size_t i) const
{
	return const_cast<MyArray&>(*this)[i];				// ？？？？
}


template <typename T, size_t S>
T* MyArray<T, S>:: begin(void) 
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
	return const_cast<MyArray*>(this)->end();			// end()指针转型成const指针
}


/***************************************************************************
***************************************************************************/
// 函数定义
void set_fun_syntax_statement(void) 
{
	pfun[0] = test0;
}



void start_syntax_statement(void) 
{
	// 界面层级符置为3，进入三级界面：
	interfaceLevel = 3;
	while (3 == interfaceLevel)
	{
		cout << "\n\n\n\n" << endl;
		cout << "**************************MENU: STL_linear_container**********************" << endl;
		cout << "Please choose a demon function to run:" << endl;
		cout << "-2: Run all existed demon function." << endl;
		cout << "-1: Back to the previous interface." << endl;
		cout << "0. test0: （C++11）范围for循环语句" << endl;


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


// test0: （C++11）范围for循环语句
static void test0(void)
{
	// 范围for循环本质上是使用容器的迭代器来实现，只要一个容器定义了begin()和end()函数，就可以使用范围for循环：
	vector<int> vi1 = { 0,1,2,3,4,5 };
	int count = 0;
	char str[20];
	MyArray<float, 5> af1;

	cout << "test0: （C++11）范围for循环语句" << endl;


	// 使用范围for循环语句遍历打印vector对象中的元素：
	cout << "\t使用范围for循环语句遍历打印vector对象中的元素：for(const int& elem: vi1){...}" << endl;
	for (const int& elem : vi1)											// 可以无脑地是用auto elem来声明容器中的元素。
	{
		sprintf(str, "\tvi1[%d] == ", count++);
		cout << str << elem << endl;
	}
	cout << endl;


	// 使用范围for循环遍历赋值自定义容器MyArray中的元素，并遍历打印。
	cout << "\t使用范围for循环遍历赋值自定义容器MyArray中的元素，并遍历打印。" << endl;
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
		cout << str << e2 << endl;
	}
	cout << endl;


}