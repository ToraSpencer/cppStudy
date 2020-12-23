#include <string>
#include <iostream>
#include <fstream>
#include <vector>						//vector类模板在头文件<vector>中

#include <cstdio>


using namespace std;




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





 


/***************************************************************************
***************************************************************************/
// 全局变量、类型定义
class Complex					// 自定义复数类
{
private:
	float real;
	float imag;
public:
	// 构造、析构函数
	Complex();
	Complex(float x, float y);

	// get/set方法
	double getReal()	const;
	double getImag()	const;

	// 普通方法
	string toString();

	// 重载运算符
	Complex operator+(Complex& cc);					//重载加号运算符，使其可以做复数的加法运算。
	operator double();								//重载运算符double()，当复数虚部为0时，可以用此运算符将复数转换为double类型数据。

};



/***************************************************************************
***************************************************************************/
// extern变量
extern void(*pfun[100])(void);
extern int inputTag, inputNum, interfaceLevel;


/***************************************************************************
***************************************************************************/
// 函数声明
template <typename T>
void traverse_vector(const vector<T>&, void(*pVisit)(const T&));			// 遍历向量的操作。

template <typename T>
void print(const T&);													// 只读操作：打印出元素的值。

void set_fun_STL_linear_container(void);
void start_STL_linear_container(void);


static void test0(void);
static void test1(void);
static void test2(void);
static void test3(void);
static void test4(void);
static void test5(void);
static void test6(void);
static void test7(void);
static void test8(void);
static void test9(void);
static void test10(void);
static void test11(void);


/***************************************************************************
***************************************************************************/
// extern函数
extern void traverse_pfun(void);



/***************************************************************************
***************************************************************************/
// 自定义类的实现



/***************************************************************************
***************************************************************************/
// 函数定义
template <typename T>
void traverse_vector(const vector<T>& v, void(*pVisit)(const T&))		// 遍历向量的操作。
{
	for (auto elem : v)
	{
		(*pVisit)(elem);
	}
}



template <typename T>
void print(const T& elem)															// 只读操作：打印出元素的值。
{
	cout << "\t" << elem << endl;
}



void set_fun_STL_linear_container(void)
{
	pfun[0] = test0;
	pfun[1] = test1;
	pfun[2] = test2;
	pfun[3] = test3;
	pfun[4] = test4;
	pfun[5] = test5;

}



void start_STL_linear_container(void)
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
		cout << "0. test0(): vector与其他线性容器相比特有的特点" << endl;
		cout << "1. test1(): 向量构造函数、初始化方法" << endl;
		cout << "2. test2(): vector访问、操作单个元素的成员方法" << endl;
		cout << "3. test3(): vector的迭代器" << endl;
		cout << "4. test4(): vector的其他成员方法" << endl;
		cout << "5. test5(): vector迭代器失效问题" << endl;
		cout << "6. test6(): 元素放入线性容器的拷贝过程" << endl;
		cout << "7. test7(): 一个应用场景。" << endl;

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

		case 6:
			(*pfun[6])();
			break;


		case 7:
			(*pfun[7])();
			break;
 

		default:
			printf("Invalid input. Please input again:\n");
			break;
		}


	}
}



// test0(): vector与其他线性容器相比特有的特点：
static void test0(void)
{
	vector<int>vi;
	vector<int>::iterator iter_i;
	vector<int>::const_iterator citer_i;

	vi.push_back(1);
	vi.push_back(2);
	vi.push_back(3);
	vi.push_back(4);
	vi.push_back(5);
	vi.push_back(6);

	cout << "\n\n\n\n" << endl;
	cout << "test0(): vector与其他线性容器相比特有的特点：" << endl << endl;


	// 1. vector, string, array可以使用下标v[i]直接访问元素：
	for (int i = 0; i <= vi.size() - 1; i++)
	{
		cout << "\t" << vi[i] ;
	}
	cout << endl;

}





// test1():向量构造函数、初始化方法。
static void test1(void)
{
	vector<int> vi1;												// 构造一个空向量。






	cout << "\n\n\n\n" << endl;
	cout << "test1(): 向量构造函数、初始化方法。" << endl << endl;

	cout << "\tvi1.empty == " << vi1.empty() << endl;
	cout << endl;


	// 1. 指定向量的容量。
	vector<int> vi2(3);			
	cout << "vi2.capacity() ==  " << vi2.capacity() << endl;
	traverse_vector(vi2, print);
	cout << endl;

	vi2.push_back(1);
	vi2.push_back(2);
	vi2.push_back(3);
	vi2.push_back(4);

	// 	1.1 push_back进去四个元素之后，vi2会自动扩容：
	cout << "vi2.size() == " << vi2.size() << endl;
	traverse_vector(vi2, print);
	cout << endl << endl;


	// 2. 指定向量的容量和元素统一初始值。
	vector<int> vi3(3, 10); 		
	traverse_vector(vi3, print);
	cout << endl;

	// 3. 使用初始化列表初始化vector和数组
	vector<int> vi4 = {1,2,3,4};										// 上下两种实例化对象的语句是等效的。
	int arr[] = { 1, 2, 3 };


	// 4. 输入数组来构造向量。
	vector<int> vi5(arr, arr + 3);									





}




// test2(): 线性容器的增删查改
static void test2(void)
{
	cout << "\n\n\ntest2():线性容器的增删查改" << endl << endl;




}



// test3():vector的迭代器
static void test3(void)
{
	cout << "\n\n\ntest3():vector的迭代器" << endl << endl;

	vector<int>vi;
	vector<int>::iterator iter_i;
	vector<int>::const_iterator citer_i;

	vi.push_back(1);
	vi.push_back(2);
	vi.push_back(3);
	vi.push_back(4);
	vi.push_back(5);
	vi.push_back(6);

	// 使用const_iterator来遍历vector中所有元素。
	cout << "use const_iterator to traverse all the items on the vector container:" << endl;
	for (citer_i = vi.begin(); citer_i != vi.end(); citer_i++)
	{
		cout << *citer_i << endl;
	}							//const_iterator只能访问元素，不可以修改元素。
	cout << endl;


	// 使用iterator来修改vector中的元素。
	cout << "use iterator to change the vector's item's value: " << endl;
	iter_i = vi.begin();								//迭代器指向第一个元素。
	*iter_i = -1;
	cout << "vi[0] == " << *iter_i << endl;
	iter_i++;
	*iter_i = -2;
	cout << "vi[1] == " << *iter_i << endl;
	iter_i += 1;
	*iter_i = -3;
	cout << "vi[2] == " << *iter_i << endl;
	cout << endl;


	// vector的迭代器失效问题：
	vector<int> vec;
	vec.push_back(1);
	vec.push_back(2);
	vec.push_back(3);
	vec.push_back(4);


	vector<int>::iterator  iter1 = vec.begin();
	vector<int>::iterator  iter2 = iter1;
	iter2++;


	cout << "*iter1 == " << *iter1 << endl;			// 貌似插入操作之后，即使是插入点之前的iterator也失效了。
	cout << "*iter2 == " << *iter2 << endl;


	vec.insert(iter2, 999);


	for (const auto& elem : vec)
	{
		cout << elem << ",  ";
	}
	cout << endl;

	cout << "*iter1 == " << *iter1 << endl;			// 貌似插入操作之后，即使是插入点之前的iterator也失效了。
	cout << "*iter2 == " << *iter2 << endl;

	vector<int>::iterator iter = vec.begin() + 3;
	cout << "*iter == " << *iter << endl;

	cout << distance(vec.begin(), iter) << endl;

}



// test4():vector的其他成员方法。
static void test4(void)
{
	//clear()：清空vector
	//reverse()
	//swap()：两个vector对象之间的元素交换。

	vector<int> vi;
	vi.push_back(1);
	vi.push_back(2);
	vi.push_back(3);


	cout << "\n\n\ntest4():vector的其他成员方法" << endl << endl;

	//empty()：返回bool值表示向量是否为空。
	cout << "vi.empty() = " << vi.empty() << endl;
	cout << endl;


	//size():返回vector现有元素数。
	cout << "vi.size() = " << vi.size() << endl;
	cout << endl;


	//capacity():返回vector当前容量，当vector超容时，容量会自动扩张为原来的两倍。容量对应于开辟的内存空间。
	cout << "vi.capacity() = " << vi.capacity() << endl;
	cout << endl;


	//reverse():设定vector的容量即capacity
	cout << "" << endl;
	vi.reserve(8);
	cout << "vi.capacity() = " << vi.capacity() << endl;


	//max_size():返回STL规定的vector最大能容纳的元素数。
	cout << "vi.max_size() =  " << vi.max_size() << endl;
	cout << endl;
	

	//at(int 索引)：返回元素的引用。
	cout << " vi.at(1) = " << vi.at(1) << endl;
	cout << endl;
}




// test5()——vector迭代器失效问题
static void test5(void)
{
	vector<int> v1 = {1,2,3};		// 初始时v1容量为3，可以使用v1.capacity()查看。
	auto iter1 = v1.begin();
	v1.push_back(4);				// 此时v1容量发生改变，内存重新分配，所有迭代器失效。
	cout << *iter1 << endl;			// 此时程序会崩溃出错，因为迭代器已经失效。

	// 执行插入操作的时候同理。




}




// test6()——元素放入线性容器中的拷贝过程
static void test6(void) 
{
	// 指针、或行为像指针的类对象被存入vector时，发生的是浅拷贝
	int num1 = 999;
	int num2 = 888;
	int num3 = 777;
	int* p1 = &num1;
	int* p2 = &num2;
	int* p3 = &num3;

	vector<int*> vec;
	vec.push_back(p1);
	vec.push_back(p2);
	vec.push_back(p3);

	for (const auto& elem : vec)
	{
		cout << *elem << ", ";
	}
	cout << endl;

	*p1 = 111;
	*p2 = 222;
	*p3 = 333;

	for (const auto& elem : vec)
	{
		cout << *elem << ", ";
	}
	cout << endl;

}




// test7()——应用场景
static void test7(void)
{
	// 应用场景——处理string对象，然后通过该对象生成相应的文件句柄。
	//		处理下面的string对象，希望在文件名后面添加后缀"_x", "_y"，表示x和y坐标的向量数据。
	string str = "data.dat";


	// 查——find()函数；线性容器本身没有find方法
	auto iter = find(str.begin(), str.end(), 'x');
	if (iter == str.end())
	{
		cout << "error" << endl;
	}
	auto dis = distance(str.begin(), iter);


	// 增——insert()方法——任意位置插入，并且可以一次性插入多个元素
	/*
		basic_string& insert( size_type index,
								const CharT* s
								);
	*/
	str.insert(dis, "_x");
	cout << str << endl;
	fstream file(str, ios::out);
	file.close();

}

