
#include "example.h"

#include <cstdio>

#include <iostream>
#include <string>
#include <typeinfo>
using namespace std;

#define EPS 1e-10					//定义非常小的一个量EPSilon，当浮点数不大于这个值时，视为0
#define PI 3.14159



// 知识点
/*
			封装
					隐藏对象的属性和实现细节，仅对外公开接口和对象进行交互。
					C++中的class是一种封装。
					封装的益处
							确保用户的代码不会无意间破坏封装对象的状态。
							被封装的类的具体实现细节可以随时改变，而无需调整用户级别的代码。

			嵌套类
					和外层类是相互独立的
					其名字在外层类的作用域中可见，外层类以外就不可见了。
					一般嵌套类就是在外层类的内部方法中使用

			接口类(抽象类)
					接口类无法被实例化，所以不存在接口类的对象。
					但是可以存在接口类的指针，用于指向子类对象，可以实现多态。


			类成员的分类：
					public成员
							0. static成员数据。
							1. 构造、析构函数。
							2. static成员函数
							3. 对成员数据get/set的函数
							4. 类内重载运算符的函数
							5. 其他函数

					protected/private成员
							1. 私有、保护成员数据
							2. 私有、保护成员函数
					

			深拷贝&浅拷贝
					浅拷贝只拷贝指针，浅拷贝之后会有两个指针指向同一块资源。
					深拷贝拷贝了资源和指针。
					

			this指针
					this指针总是指向当前对象，是一个指针常量（顶层const指针）。

					this指针是每个非static成员函数的隐藏参数。

					在成员函数开始前构造，在成员结束后清除。

					this指针不占用对象的空间。

					形参表后面的const，改变了隐含的this形参的类型，如 bool same_isbn(const Sales_item &rhs) const，这种函数称为“常量成员函数”，此时this即是顶层又是底层const。
					
					return *this？？？？


			空类默认产生的成员函数：
					无参构造函数
					拷贝构造函数
					析构函数
					赋值运算符重载
					取地址运算符重载
					取地址运算符const重载
					

			const对象
					const对象的成员数据中，除了专门用了mutable修饰的变量，其他都不可更改。
					cosnt对象不可以调用自己的非const的成员函数。
					函数的形参列表中有某类对象，可以限制该形参为const对象，可以保护传进来的对象不被修改。
					实例化一个const对象的格式：
					const 类名 对象名（参数列表）

					

			成员访问限定关键字：
					public
							完全没限制。
					protected
							该类的不同对象之间不可以互相访问对方的protected成员。
					private
							该类的不同对象之间不可以互相访问对方的private成员。
							父子类对象之间不可以互相访问对方的private成员

			成员函数（方法）
					在类内定义的成员函数是内联的。
					private方法只能被类内其他方法使用。


			默认构造函数；
							若类未声明构造函数，系统会分配一个默认的构造函数。
							对象创建时系统自动调用。
							

			拷贝构造函数
							输入参数为一个本类对象的引用。
							使用一个类对象去初始化该类的另一个对象时，系统自动调用拷贝构造函数来实现。
							若类中未声明拷贝构造函数，系统会自动分配一个默认的，用来初始化对象。

			初始化列表
							冒号和花括号之间的代码： Sales_item(): units_sold(0), revenue(0.0) { }

			
			析构函数：
							若未声明析构函数，系统会自动分配一个。


			子类不能继承自父类的资源
							构造函数、析构函数、operator=()、友元。

			static成员的继承
							父类的static变量和函数在派生类中被继承，但是受访问性控制（比如，父类的private域中的就不可访问）
							而且对static变量来说，派生类和父类中的static变量是共用空间的，这点在利用static变量进行引用计数的时候要特别注意。
							
			类声明实现分离
							建议类的声明和实现分离开来写，声明写在.h文件中，实现写在.cpp文件中。
							如果该类含有static数据，则其初始化一定要在.cpp文件中完成，不可以在.h中完成，否则可能会出现重定义符号问题。
							注意如果类中包含函数模板的话，则该函数模板不可以声明实现分离。

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
std::ostream& operator<<(std::ostream&, const Vector2d&);

void set_fun_OOP_class_object(void);
void start_OOP_class_object(void);

static void test0(void);
static void test1(void);
static void test2(void);
static void test3(void);
static void test4(void);
static void test5(void);


/***************************************************************************
***************************************************************************/
// extern函数
extern void traverse_pfun(void);



/***************************************************************************
***************************************************************************/
// 函数定义


// operator<<————重载<<运算符，将Vector2d的信息写入到输出流中。
std::ostream& operator<<(std::ostream& os, const Vector2d& v) 
{
	os << "(" << v.getX() << ", " << v.getY() << ")";

	return os;
}


void set_fun_OOP_class_object(void) 
{
	pfun[0] = test0;
	pfun[1] = test1;
	pfun[2] = test2;
	pfun[3] = test3;
	pfun[4] = test4;
	pfun[5] = test5;
}


void start_OOP_class_object(void) 
{
	// 界面层级符置为3，进入三级界面：
	interfaceLevel = 3;
	while (3 == interfaceLevel)
	{
		cout << "\n\n\n\n" << endl;
		cout << "**************************MENU: OOP_CLASS_OBJECT**********************" << endl;
		cout << "Please choose a demon function to run:" << endl;
		cout << "-2: Run all existed demon function." << endl;
		cout << "-1: Back to the previous interface." << endl;
		cout << "0. test0: 类和对象的基本知识——Person.hpp." << endl;
		cout << "1. test1: 类的继承——Grandfather.hpp" << endl;
		cout << "2. test2: 抽象基类Vector的子类Vector2d——Vector.hpp" << endl;
		cout << "3. test3: 成员数据带有指针的类，深拷贝，浅拷贝。" << endl;


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




// test0: 类和对象的基本知识——Person.hpp.
void test0(void)
{
	Person person1;
	Person person2 = Person();
	Person person3("xiaoming", 22, "Shanghai, China", "teacher");
	Person person4 = Person("Cindy", 10, "New York, USA", "student");
	Dog wangwang;

	cout << "\n\n\n\n" << endl;
	cout << "test0: 类和对象的基本知识——Person.hpp." << endl;
	
	person1.say();
	person2.say();
	person3.say();
	person4.say();
	wangwang.bark();
	cout << endl;

	cout << "测试Person类的set函数。" << endl;
	person2.setName("Tom");
	person2.setAge(44);
	person2.setAdress("Tokyo, Japan");
	person2.setCareer("programmer");
	person2.say();
	cout << endl;



	// 类直接调用static函数:
	cout << "类直接调用static函数——Person::getObjCount == " << Person::getObjCount()  << endl;


}




// test1: 类的继承——Grandfather.hpp
void test1(void) 
{
	cout << "\n\n\n\n" << endl;
	cout << "test1：类的继承——Grandfather.hpp" << endl;

	Grandfather person1 = Grandfather();
	Grandfather person2 = Grandfather("wangyi", 88, "Shanghai, China", "farmer", "male");
	HuskieDog dog1 = HuskieDog();


	person1.say();
	dog1.bark();
	cout << endl;

	cout << "person1 = person2; person1.say();" << endl;
	person1 = person2;
	person1.say();

}



// test2: 抽象基类Vector的子类Vector2d——Vector.hpp
void test2(void) 
{
	cout << "\n\n\n\n" << endl;
	cout << "test2：抽象基类Vector的子类Vector2d——Vector.hpp" << endl;

	Vector2d v1;
	Vector2d v2(3,4);
	Vector2d v3(2,2);

	cout << "v1 == " << v1 << endl;
	cout << "v2 == " << v2 << endl;
	cout << endl;

	cout << "v2*v3 == " << v2 * v3 << endl;
	cout << "v2.dot(v3) == " << v2.dot(v3) << endl;



}



// test3: 成员数据带有指针的类，深拷贝，浅拷贝。
static void test3(void)
{
	cout << "\n\n\n\n" << endl;
	cout << "test3: 成员数据带有指针的类，深拷贝，浅拷贝。" << endl;

	myString str1 = myString();
	myString str2 = myString("hello world");
	myString str3 = myString(str2);

	cout << str1 << endl;
	cout << str2 << endl;
	cout << str3 << endl;

	str1 = str2;
	cout << str1 << endl;

}



static void test4(void)
{}



static void test5(void)
{}
