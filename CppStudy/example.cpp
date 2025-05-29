#include "example.h"


// 	 0. Person���static��Ա���ݵĳ�ʼ����
int Person::objCount = 0;				 // "::"��ʾ���������

										 // 	 1. Person��Ĺ��캯��
Person::Person() : name("unknow"), age(0), address("unknown"), career("unknown")		 // ��Ա��ʼ���б������캯����������ʼ�����Ա
{
	Person::objCount++;

	std::cout << "the empty-argument constructor of class Person has been called." << std::endl;
}


Person::Person(std::string name, unsigned int age, std::string address, std::string career)
{
	this->name = name; 																 // ʹ��thisָ��Զ���ĳ�Ա���ݸ�ֵ��					 
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


Person::~Person()
{
	std::cout << "A Person object has been eliminated." << std::endl;
	Person::objCount--;
}


int Person::getObjCount()
{
	return Person::objCount;
}


// 	 2. Person���Ա���ݵ�get/set����

std::string Person::getName() const
{
	return this->name;
}


unsigned int Person::getAge() const
{
	return this->age;
}


std::string Person::getAddress() const
{
	return this->address;
}


std::string Person::getCareer() const
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


// 	 3. Person����������������

// 	 4. Person�������������
void Person::say()
{
	std::cout << "Hello, my name is " << this->name << ". I'm " << this->age  \
		<< " years old. I live in " << this->address << ". I'm a " << this->career \
		<< "." << std::endl;
}


Grandfather::Grandfather() :Person(), gender("male")			 // �����๹�캯���ĳ�ʼ���б�
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


Grandfather::~Grandfather()
{
	std::cout << "A Grandfather object has been eliminated." << std::endl;
}


void Grandfather::setGender(std::string gender)
{
	this->gender = gender;
}


std::string Grandfather::getGender()	 const
{
	return this->gender;
}


void Grandfather::say()
{
	std::cout << "Hello, my name is " << this->name << ". My gender is " << this->gender \
		<< ". I'm " << this->age << " years old. I live in " << this->address << ". I'm a " \
		<< this->career << "." << std::endl;
}


void Dog::bark()
{
	std::cout << "KKP." << std::endl;
}



void HuskieDog::bark()
{
	std::cout << "I'm a Huskie dog, KKP!" << std::endl;
}


int Vector::objCount = 0;

Vector::Vector() :x(0), y(0)
{
	Vector::objCount++;
}


Vector::Vector(float x, float y) : x(x), y(y)
{
	Vector::objCount++;
}


Vector::~Vector()
{}



float Vector::getX()	 const
{
	return this->x;
}


float Vector::getY()	 const
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



Vector2d::Vector2d() :Vector()
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


Vector2d::~Vector2d()
{
	Vector2d::objCount--;

	std::cout << "A Vector2d object has been eliminated." << std::endl;
	std::cout << "Vector2d objects remained: " << Vector2d::getObjCount() << std::endl;
}


float Vector2d::operator *(const Vector2d& v)	 const			 // ͨ����������������Ա������ʵ�֡�
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


void Vector2d::say()
{
	std::cout << "I'm a Vector2d object!" << std::endl;
}





classFoo::classFoo(const std::string& str1, const int& age1) :str(str1)
{
	if (age1 < 0)
	{
		// ������age1����С��0ʱ���׳�������Χ�쳣
		throw(std::out_of_range("�쳣����out of range: ��������Ӧ�ò�С��0."));
	}
	this->age = age1;

}


classFoo::~classFoo()
{
	std::cout << "������һ��classFoo����" << std::endl;
}


void classFoo::setAge(int age1)
{
	if (age1 < 0)
	{
		throw(std::out_of_range("�쳣����out of range: classFoo::setAge(int)��������С��0������������"));
	}
	this->age = age1;
}



myString::myString(const char* cStr)                      // Ĭ�������£�����յ��ַ�����������
{
	if (cStr)
	{
		this->p_data = new char[strlen(cStr) + 1];
		strcpy(p_data, cStr);
	}
	else        // δָ����ֵʱ
	{
		this->p_data = new char[1];
		*(this->p_data) = '\0';
	}
}


myString::myString(const myString& str)                                // ����������������ָ��ʽ��Ӧ���Լ�ʵ�ֿ������캯�������ظ�ֵ���������ʵ�����������ϵͳ����ǳ�����Ŀ������캯����
{
	char* cStr = str.getCstr();
	int size = strlen(cStr) + 1;

	this->p_data = new char[size];
	strcpy_s(p_data, cStr);
}

myString::~myString()                                               // ��������Ӧд���麯�������������������ʱ�����ڴ�й¶��
{
	delete[] this->p_data;
}



char* myString::getCstr() const                                           // ��ȡ��װ��C����ַ�����
{
	return this->p_data;
}


myString& myString::operator=(const myString& str)         // ���������ظ�ֵ�������ע��Ҫʵ�������
{
	// ���������Ҹ�ֵ���
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

unsigned int FooPrinter::getCount()
{
	return this->count;
}
