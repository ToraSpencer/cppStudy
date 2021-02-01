#include "example.h"


// 	 0. Person类的static成员数据的初始化：
int Person::objCount = 0;				 // "::"表示域操作符。

										 // 	 1. Person类的构造函数
Person::Person() : name("unknow"), age(0), address("unknown"), career("unknown")		 // 成员初始化列表——构造函数中用来初始化类成员
{
	Person::objCount++;

	std::cout << "the empty-argument constructor of class Person has been called." << std::endl;
}


Person::Person(std::string name, unsigned int age, std::string address, std::string career)
{
	this->name = name; 																 // 使用this指针对对象的成员数据赋值。					 
	this->age = age;
	this->address = address;
	this->career = career;
	Person::objCount++;

	std::cout << "the argument-contained constructor of class Person has been called." << std::endl;
}


Person::Person(const Person& p)
{
	this->name = p.getName();
	this->age = p.getAge();
	this->address = p.getAddress();
	this->career = p.getCareer();
	Person::objCount++;

	std::cout << "the copy constructor of class Person has been called." << std::endl;
}


Person::~Person(void)
{
	std::cout << "A Person object has been eliminated." << std::endl;
	Person::objCount--;
}


int Person::getObjCount(void)
{
	return Person::objCount;
}


// 	 2. Person类成员数据的get/set函数

std::string Person::getName(void) const
{
	return this->name;
}


unsigned int Person::getAge(void) const
{
	return this->age;
}


std::string Person::getAddress(void) const
{
	return this->address;
}


std::string Person::getCareer(void) const
{
	return this->career;
}


void Person::setName(std::string name)
{
	this->name = name;
}


void Person::setAge(unsigned int age)
{
	this->age = age;
}


void Person::setAdress(std::string address)
{
	this->address = address;
}


void Person::setCareer(std::string career)
{
	this->career = career;
}


// 	 3. Person类的重载运算符函数

// 	 4. Person类的其他函数：
void Person::say(void)
{
	std::cout << "Hello, my name is " << this->name << ". I'm " << this->age  \
		<< " years old. I live in " << this->address << ". I'm a " << this->career \
		<< "." << std::endl;
}


Grandfather::Grandfather(void) :Person(), gender("male")			 // 派生类构造函数的初始化列表
{
	Grandfather::objCount++;

	std::cout << "the empty-argument constructor of class Grandfather has been called." << std::endl;
}


Grandfather::Grandfather(std::string name, unsigned int age, std::string address, std::string career, std::string gender) :\
Person(name, age, address, career), gender(gender)
{
	Grandfather::objCount++;

	std::cout << "the argument-contained constructor of class Grandfather has been called." << std::endl;
}


Grandfather::Grandfather(const Grandfather& gf)
{
	this->name = gf.getName();
	this->age = gf.getAge();
	this->address = gf.getAddress();
	this->career = gf.getCareer();
	this->gender = gf.getGender();

	Grandfather::objCount++;
	std::cout << "the copy constructor of class Grandfather has been called." << std::endl;
}


Grandfather::~Grandfather(void)
{
	std::cout << "A Grandfather object has been eliminated." << std::endl;
}


void Grandfather::setGender(std::string gender)
{
	this->gender = gender;
}


std::string Grandfather::getGender(void)	 const
{
	return this->gender;
}


void Grandfather::say(void)
{
	std::cout << "Hello, my name is " << this->name << ". My gender is " << this->gender \
		<< ". I'm " << this->age << " years old. I live in " << this->address << ". I'm a " \
		<< this->career << "." << std::endl;
}


void Dog::bark(void)
{
	std::cout << "KKP." << std::endl;
}



void HuskieDog::bark(void)
{
	std::cout << "I'm a Huskie dog, KKP!" << std::endl;
}


int Vector::objCount = 0;

Vector::Vector(void) :x(0), y(0)
{
	Vector::objCount++;
}


Vector::Vector(float x, float y) : x(x), y(y)
{
	Vector::objCount++;
}


Vector::~Vector(void)
{}



float Vector::getX(void)	 const
{
	return this->x;
}


float Vector::getY(void)	 const
{
	return this->y;
}


void Vector::setX(float x)
{
	this->x = x;
}


void Vector::setY(float y)
{
	this->y = y;
}



Vector2d::Vector2d(void) :Vector()
{
	std::cout << "the empty-argument constructor of class Vector2d has been called." << std::endl;
	std::cout << "Vector2d objects remained: " << Vector2d::getObjCount() << std::endl;
}


Vector2d::Vector2d(float x, float y) :Vector(x, y)
{
	std::cout << "the argument-contained constructor of class Vector2d has been called." << std::endl;
	std::cout << "Vector2d objects remained: " << Vector2d::getObjCount() << std::endl;
}


Vector2d::Vector2d(const Vector2d& v)
{
	this->x = v.getX();
	this->y = v.getY();

	Vector2d::objCount++;

	std::cout << "the copy constructor of class Vector2d has been called." << std::endl;
	std::cout << "Vector2d objects remained: " << Vector2d::getObjCount() << std::endl;
}


Vector2d::~Vector2d(void)
{
	Vector2d::objCount--;

	std::cout << "A Vector2d object has been eliminated." << std::endl;
	std::cout << "Vector2d objects remained: " << Vector2d::getObjCount() << std::endl;
}


float Vector2d::operator *(const Vector2d& v)	 const			 // 通过调用类内其他成员函数来实现。
{
	float result;

	result = this->dot(v);

	return result;
}


float Vector2d::dot(const Vector2d& v)  const
{
	float result;

	result = this->x * x + this->y * y;

	return result;
}


void Vector2d::say(void)
{
	std::cout << "I'm a Vector2d object!" << std::endl;
}





classFoo::classFoo(const std::string& str1, const int& age1) :str(str1)
{
	if (age1 < 0)
	{
		// 当输入age1参数小于0时，抛出超出范围异常
		throw(std::out_of_range("异常——out of range: 输入年龄应该不小于0."));
	}
	this->age = age1;

}


classFoo::~classFoo()
{
	std::cout << "析构了一个classFoo对象。" << std::endl;
}


void classFoo::setAge(int age1)
{
	if (age1 < 0)
	{
		throw(std::out_of_range("异常——out of range: classFoo::setAge(int)不允许传递小于0的整数参数。"));
	}
	this->age = age1;
}



myString::myString(const char* cStr)                      // 默认情形下，传入空的字符串字面量。
{
	if (cStr)
	{
		this->p_data = new char[strlen(cStr) + 1];
		strcpy(p_data, cStr);
	}
	else        // 未指定初值时
	{
		this->p_data = new char[1];
		*(this->p_data) = '\0';
	}
}


myString::myString(const myString& str)                                // ！！！类数据中有指针式，应该自己实现拷贝构造函数、重载赋值运算符，以实现深拷贝。否则系统分配浅拷贝的拷贝构造函数。
{
	char* cStr = str.getCstr();
	int size = strlen(cStr) + 1;

	this->p_data = new char[size];
	strcpy_s(p_data, cStr);
}

myString::~myString()                                               // 析构函数应写成虚函数，否则子类对象析构时会有内存泄露。
{
	delete[] this->p_data;
}



char* myString::getCstr() const                                           // 获取封装的C风格字符串。
{
	return this->p_data;
}


myString& myString::operator=(const myString& str)         // ！！！重载赋值运算符，注意要实现深拷贝。
{
	// ！！！自我赋值检查
	if (this != &str)
	{
		char* cStr = str.getCstr();
		int size = strlen(cStr) + 1;

		delete[] this->p_data;

		this->p_data = new char[size];
		strcpy(p_data, cStr);
	}

	return *this;
}







FooPrinter::FooPrinter() :count(0) {}

void FooPrinter::operator()(const classFoo& f)
{
	std::cout << "\t" << f.str << "----" << f.age;
	(this->count)++;
}

unsigned int FooPrinter::getCount(void)
{
	return this->count;
}
