#ifndef EXAMPLE_H_

#define EXAMPLE_H_

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <functional>
#include <exception>
#include <utility>
#include <cstring>

#include <cstdio>


/////////////////////////////////////////////////////////////////////// 前置声明
class myString;
static std::ostream& operator<<(std::ostream& os, const myString& str);             // 必须要加static，因为有多个文件包含了本头文件，如果不将此函数作用域限定在本文件内，会出现重定义错误。

 
/////////////////////////////////////////////////////////////////////// 全局变量、类型定义
class classFoo
{
    // 封装了一个字符串和一个数字的类，用于展示函数功能。
public:
    std::string str;
    int age;

    classFoo() = default;
	classFoo(const std::string& str1, const int& age1);
	~classFoo();
	void setAge(int age1);
};



class Person
{
	//
public:
	//	0. static成员数据
	//				属于整个类而不是某个对象。
	//				只存储一份，为所有对象共有。
	//				必须在类外初始化。
	static int objCount;


	// 1. 构造函数、析构函数
	//			注意：没有返回类型标识符
	Person(void);
	Person(std::string name, unsigned int age, std::string address, std::string career);
	Person(const Person& p);				// 拷贝构造函数		
											//			规范的做法：传入的对象的引用设置为const，可以保护其不会被更改。			
	virtual ~Person(void);


	//	2. 类的static函数
	//			只能访问类的static数据
	//			作用也主要是用于管理类的static数据。
	static int getObjCount(void);




	//	3. 对成员数据的get/set函数
	//			注意：
	//				为了保证封装性，不能直接修改或者读取对象的私有成员。而是通过public函数来实现。
	//				为了使得const对象的成员数据也可以被读取，get函数都要设置为const
	std::string getName(void)	const;
	unsigned int getAge(void)	const;
	std::string getAddress(void)	const;
	std::string getCareer(void)	const;
	void setName(std::string name);
	void setAge(unsigned int age);
	void setAdress(std::string address);
	void setCareer(std::string career);


	//	4. 类内重载运算符的函数


	//	5. 其他函数
	virtual void say(void);








	// OOP的原则：数据私有化，行为公有化
protected:							// 因为该类有可能派生，以下数据理应继承下去，所以设置为protected而不是private
	std::string name;
	unsigned int age;
	std::string address;
	std::string career;
};



class Grandfather: public Person			// 继承时使用类派生列表（class derivation list）,来指明继承的类，和继承方式。
{
//	继承的内容：
//				@只有权限为public和protected的成员可以被继承到派生类中。
//				@构造函数、析构函数不会被继承。
//				@继承而来的static数据是父子类共用的。
//	继承方式：
//				public继承——继承来的成员权限不变。
//				protected继承——继承来的成员都变成protected;
//				private继承——继承来的成员都变成private;



public:
//	1. 继承中的构造函数、析构函数：
//				子类的构造函数、析构函数被调用之前，其父类的构造函数、析构函数都会被调用。
//				创建一个派生类对象时，会自动调用其基类的构造函数，以初始化继承来的基类的成员数据。
//				派生类中若新增的成员数据，则需要构造新的构造函数来初始化。
//				若派生类中没有新增的成员数据，则不需要声明新的构造函数。
	Grandfather(void);
	Grandfather(std::string name, unsigned int age, std::string address, std::string career, std::string gender);
	Grandfather(const Grandfather& gf);
	~Grandfather(void);

	void setGender(std::string);
	std::string getGender(void)	const;

	void say(void);		// 覆盖基类中的函数say


protected:
	std::string gender;
};



class Dog
{
public:
//		如果没有构造函数，系统会自动分配一个无参的构造函数。
	
	void bark(void);

};



class HuskieDog : public Dog
{
public:
//		派生类中没有新增的成员数据，所以不需要声明新的构造函数。

	void bark(void);		// 覆盖基类中的函数bark;

};





//抽象基类：Vector——抽象向量基类
class Vector							 
{
public:
//		0. static成员数据。
	static int objCount;


//		1. 构造、析构函数。
	Vector(void);
	Vector(float x, float y);
	~Vector(void);						


//		2. static成员函数
	static int getObjCount(void)
	{
		return Vector::objCount;
	}

//		3. 对成员数据get / set的函数
	float getX(void)	const;
	float getY(void)	const;
	void setX(float x);
	void setY(float y);

//		4. 重载运算符


//		5. 其他函数
	virtual void say(void) = 0;				// "= 0;"表示纯虚函数						


protected:
	float x, y;

};




//派生类：Vector2d——二维向量类
class Vector2d :public Vector 
{
//		声明友元函数——友元函数可以访问本类的Protected，private成员。
	friend std::ostream& operator<<(std::ostream&, const Vector2d&);

public:
//		0. static成员数据。
//		1. 构造、析构函数。
	Vector2d(void);
	Vector2d(float x, float y);
	Vector2d(const Vector2d& v);
	~Vector2d(void);

//		2. static成员函数
//		3. 对成员数据get / set的函数
//		4. 类内重载运算符的函数
	float operator *(const Vector2d& v)	const;				// 重载乘法运算符


//		5. 其他函数.
	float dot(const Vector2d& v)	const;					// 向量点乘。
	void say(void)  override;										// 关键字override——标志着覆盖继承而来的函数					 


};



//      成员数据中有指针的类。
class myString 
{
private:
    char* p_data;

public:
    friend std::ostream& operator<<(std::ostream&, const myString&);
	myString() = default;
	myString(const char* cStr);
	myString(const myString& str);
	virtual ~myString();
	char* getCstr() const;
	myString& operator=(const myString& str);
};



// 函数子baseTypePrinter——打印基本类型变量
class baseTypePrinter
{
public:
	baseTypePrinter() = default;

	template<typename T>
	void operator()(const T& arg)
	{
		cout << arg << "\t";
	}

};


//      函数子FooPrinter————功能是打印classFoo对象。
class FooPrinter
{
    // 可以显示被调用次数。
private:
    unsigned int count;

public:
	FooPrinter();

	void operator()(const classFoo& f);
    
	unsigned int getCount(void);

};





/***************************************************************************
***************************************************************************/
// 函数实现
// printFoo————打印classFoo对象
inline void printFoo(const classFoo& f)
{
    std::cout << "\t"<< f.str << "----" << f.age; 
}

 
 // 打印内置类型的变量：
 template <typename T>
 inline void printElem(T &elem)
 {
     std::cout << "\t" << elem;
 }


 static std::ostream& operator<<(std::ostream& os, const myString& str)
 {
     char* cStr = str.getCstr();

     os << cStr;

     return os;
 }





#endif
