#include <iostream>
#include <string>
#include <typeinfo>

#include <memory>
#include <vector>
#include <cstddef>
#include <new>

#include <cstdio>



using namespace std;

#define EPS 1e-10					//定义非常小的一个量EPSilon，当浮点数不大于这个值时，视为0
#define PI 3.14159



// 知识点
/*
			1. 指针的三种状态——空指针、野指针、正常指针（指向实际数据对象）
						空指针
									赋值为0的指针
									不指向任何数据对象

						野指针
									未被初始化的指针，或指向内存被释放之后的指针。
									此时指针指向的位置未知，可能是随机的
									一般使用野指针的话，编译器都会报错。




			2. 引用和指针的区别
							(1). 引用必须被初始化，指针不需要。
							(2). 引用初始化之后不可改变，指针可以
							(3). 不存在空引用，存在空指针。





			3. 三个智能指针类模板shared_ptr, unique_ptr, weak_ptr的基本信息(C++11)
							智能指针主要用来管理堆对象，对于栈对象没有必要使用，用的话可能还会引发异常。
							
							shared_ptr
									可共享的智能指针。
									若有5个shared_ptr指针指向同一个数据对象，则该数据对象的引用计数为5
									一个对象的引用计数降到0时，会被销毁，内存会释放。
							
							unique——ptr
									不可共享的，唯一的智能指针。
			



			4. shared_ptr和unique_ptr的比较
							(1) shared_ptr, unique_ptr相同的接口：
											p.get()
														返回智能指针对象中存储的指针。
											p			
														作条件判断，若智能指针p指向一个对象，则返回true
											*p
											p->member
											p.swap(q)
														交换智能指针对象p,q中存储的指针
											p.reset(普通指针)
														重置智能指针指向的对象。
							

							(2) shared_ptr独有的接口
											p.use_count()
														返回一个long, 表明了p指向的对象当前被多少个shared_ptr指针指向
											p.unique()
														检查p是否是unique的，若其指向的对象当前只被p这一个shared_ptr指针指向，则返回true

							(3) unique_ptr独有的接口：
											p.release()
														返回被管理对象的普通指针，若无被管理对象则返回NULL

														

			5. 常见的产生野指针的错误：
							声明指针变量的时候未初始化。
							delete或者free了一个指针以后，未将该指针悬空
							函数内部，返回一个指向栈内存的指针。因为栈内存在函数结束后就会释放。


			6. 内存泄漏（memory leak） 
							（1）堆内存泄漏 （Heap leak）。
											堆内存指的是程序运行中通过malloc,realloc new等从堆中分配的一块内存。如果程序的设计的错误导致这部分内存没有被释放，那么此后这块内存将不会被使用，就会产生Heap Leak. 	
							（2）系统资源泄露（Resource Leak）.
											主要指程序使用系统分配的资源比如 Bitmap,handle ,SOCKET等没有使用相应的函数释放掉，导致系统资源的浪费，严重可导致系统效能降低，系统运行不稳定。 

							它的一般表现方式是程序运行时间越长，占用内存越多，最终用尽全部内存，整个系统崩溃。

							由程序申请的一块内存，且没有任何一个指针指向它，那么这块内存就泄露了。

			7. 如何防止内存泄漏
							良好的编码习惯，如new和delete要保证成对出现，new出来的数据对象使用完毕之后要及时地释放掉；或者尽量使用智能指针。
						


			8. 检查内存泄漏的途径
							1. 使用工具软件BoundsChecker——一个运行时错误检测工具，它主要定位程序运行时期发生的各种错误。


			


			9. 内存泄漏的修复途径

*/





// make_shared<T>()————创建一个shared_ptr指针
/*. BC------------------------------------------------------------------------
描述：  
	开辟动态内存空间，返回shared_ptr对象
	源于头文件<memory>
	生成的T类型对象的初始值是默认的。
	例子：shared_ptr<int> p = make_shared<int>(42);

						
	重载1：
		shared_ptr<T> make_shared( Args&&... args 			生成T对象的构造函数参数列表。
															);	
		返回值：
			指向构造出来的T类型对象的shared_ptr指针。
			

	重载2：
		shared_ptr<T> make_shared();

		返回值：
			同上。
								 
 
*. EC------------------------------------------------------------------------
*/







/***************************************************************************
***************************************************************************/
// 全局变量、类型定义
class Foo
{
private:

public:


};




/***************************************************************************
***************************************************************************/
// extern变量
extern void(*pfun[100])(void);
extern int inputTag, inputNum, interfaceLevel;



/***************************************************************************
***************************************************************************/
// 函数声明
void set_fun_dataType_pointer(void);
void start_dataType_pointer(void);

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

void set_fun_dataType_pointer(void)
{
	pfun[0] = test0;
	pfun[1] = test1;
	pfun[2] = test2;
	pfun[3] = test3;
}



void start_dataType_pointer(void)
{
	// 界面层级符置为3，进入三级界面：
	interfaceLevel = 3;
	while (3 == interfaceLevel)
	{
		cout << "\n\n\n\n" << endl;
		cout << "**************************MENU: dataType_pointer**********************" << endl;
		cout << "Please choose a demon function to run:" << endl;
		cout << "-2: Run all existed demon function." << endl;
		cout << "-1: Back to the previous interface." << endl;
		cout << "0. test0: 使用关键字new和delete直接管理内存。" << endl;
		cout << "1. test1：智能指针shared_ptr, unique_ptr的基本使用" << endl;
		cout << "2. test2：自定义类型使用智能指针shared_ptr, unique_ptr" << endl;
		cout << "3. test3: 空指针" << endl;


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

		default:
			printf("Invalid input. Please input again:\n");
			break;
		}


	}
}



// test0: 使用关键字new和delete直接管理内存。
static void test0(void) 
{
	cout << "\n\n\n\n" << endl;
	cout << "test0: 使用关键字new和delete直接管理内存。" << endl;
 
	int *p1 = new int; 							// 若开辟内存失败则抛出std::bad_alloc
	int *p2 = new (nothrow) int; 		// 若开辟内存失败则返回一个空指针
	int i0;                   
	int *p0 = new int;        
	                         
	delete p0;   

	int i(1024);              
	string s(10, '9');       


	// 未命名，但是已初始化了的数据对象
	int *pi = new int(1024);  
	string *ps = new string(10, '9');    
 
 

	vector<int> *pv = new vector<int>; 	// empty vector
	for (int i = 0; i != 10; ++i)
	{
		pv->push_back(i);              // add elements to the allocated vector
	}


	cout << "*pi: " << *pi
	     << "\ti: " << i << endl
	     << "*ps: " << *ps
	     << "\ts: " << s << endl;
	
	for (auto b = pv->begin(); b != pv->end(); ++b)
	{
		cout << *b << " ";
	}
	
	cout << endl;


	// 内存使用完毕以后，需要删除其对应的指针，否则会造成内存泄漏
	delete pi;   
	delete ps;  
	delete pv;   
	
 
	// 数组内存的开辟和释放：
	int *pia = new int[42];  
	delete [] pia; 			// 释放数组内存的时候，要在delete之后加上[]
	typedef int arrT[42];   
	int *p = new arrT;      
	delete [] p;           

}




// test1：智能指针shared_ptr, unique_ptr的基本使用
static void test1(void) 
{
	float f1 = 1.10;
	shared_ptr<float> pf1;						// 默认构造函数，构造一个空的shared_ptr指针 
	shared_ptr<float> pf2(&f1);					// 传递普通指针构造shared_ptr指针
	shared_ptr<float> pf3(new float(1.11));		// 传递普通指针构造，配合关键字new
	shared_ptr<int> pi1;
	shared_ptr<int> pi2 = make_shared<int>(12);	// 使用make_shared函数生成shared_ptr指针

	cout << "\n\n\n\n" << endl;
	cout << "test1：智能指针shared_ptr, unique_ptr" << endl;

	cout << "\tpi1.use_count() == " << pi2.use_count() << endl;
	cout << "\tpi1.unique() == " << pi2.unique() << endl;

	pi1 = pi2;
	cout << "pi1 = pi2; → pi1,pi2共享同一个数据对象：" << endl;
	cout << "\tpi1.use_count() == " << pi2.use_count() << endl;
	cout << "\tpi1.unique() == " << pi2.unique() << endl;

}



// test2: 自定义类型使用智能指针shared_ptr, unique_ptr
static void test2(void)
{

	// 智能指针默认使用delete来释放对象内存。自定义类型的，需要有删除器才可以使用delete

}



// test3: 空指针
static void test3(void)
{
	cout << "\n\n\n\n" << endl;
	cout << "test3：空指针" << endl;

	// 使用空指针来访问不存在的内存空间，会引发空指针异常，从而程序崩溃
	// 可以使用p==NULL表达式返回的bool值来判断是否是空指针
	int *pi1 = NULL;
	int *pi2 = NULL;

	if (pi1 == NULL && pi1 == NULL && pi2 == NULL && pi2 == NULL)
	{
		cout << "pi1和pi2都是空指针。写成NULL或nullptr都可以。" << endl;
	}

	cout << "(int)(pi1 == NULL) == " << (int)(pi1 == NULL) << endl;
	cout << "(int)(pi1 == NULL)" << (int)(pi2 == NULL) << endl;



}





// test4: 
static void test4(void) 
{


}
