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


/////////////////////////////////////////////////////////////////////// ǰ������
class myString;
static std::ostream& operator<<(std::ostream& os, const myString& str);             // ����Ҫ��static����Ϊ�ж���ļ������˱�ͷ�ļ�����������˺����������޶��ڱ��ļ��ڣ�������ض������

 
/////////////////////////////////////////////////////////////////////// ȫ�ֱ��������Ͷ���
class classFoo
{
    // ��װ��һ���ַ�����һ�����ֵ��࣬����չʾ�������ܡ�
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
	//	0. static��Ա����
	//				���������������ĳ������
	//				ֻ�洢һ�ݣ�Ϊ���ж����С�
	//				�����������ʼ����
	static int objCount;


	// 1. ���캯������������
	//			ע�⣺û�з������ͱ�ʶ��
	Person(void);
	Person(std::string name, unsigned int age, std::string address, std::string career);
	Person(const Person& p);				// �������캯��		
											//			�淶������������Ķ������������Ϊconst�����Ա����䲻�ᱻ���ġ�			
	virtual ~Person(void);


	//	2. ���static����
	//			ֻ�ܷ������static����
	//			����Ҳ��Ҫ�����ڹ������static���ݡ�
	static int getObjCount(void);




	//	3. �Գ�Ա���ݵ�get/set����
	//			ע�⣺
	//				Ϊ�˱�֤��װ�ԣ�����ֱ���޸Ļ��߶�ȡ�����˽�г�Ա������ͨ��public������ʵ�֡�
	//				Ϊ��ʹ��const����ĳ�Ա����Ҳ���Ա���ȡ��get������Ҫ����Ϊconst
	std::string getName(void)	const;
	unsigned int getAge(void)	const;
	std::string getAddress(void)	const;
	std::string getCareer(void)	const;
	void setName(std::string name);
	void setAge(unsigned int age);
	void setAdress(std::string address);
	void setCareer(std::string career);


	//	4. ��������������ĺ���


	//	5. ��������
	virtual void say(void);








	// OOP��ԭ������˽�л�����Ϊ���л�
protected:							// ��Ϊ�����п�������������������Ӧ�̳���ȥ����������Ϊprotected������private
	std::string name;
	unsigned int age;
	std::string address;
	std::string career;
};



class Grandfather: public Person			// �̳�ʱʹ���������б�class derivation list��,��ָ���̳е��࣬�ͼ̳з�ʽ��
{
//	�̳е����ݣ�
//				@ֻ��Ȩ��Ϊpublic��protected�ĳ�Ա���Ա��̳е��������С�
//				@���캯���������������ᱻ�̳С�
//				@�̳ж�����static�����Ǹ����๲�õġ�
//	�̳з�ʽ��
//				public�̳С����̳����ĳ�ԱȨ�޲��䡣
//				protected�̳С����̳����ĳ�Ա�����protected;
//				private�̳С����̳����ĳ�Ա�����private;



public:
//	1. �̳��еĹ��캯��������������
//				����Ĺ��캯������������������֮ǰ���丸��Ĺ��캯���������������ᱻ���á�
//				����һ�����������ʱ�����Զ����������Ĺ��캯�����Գ�ʼ���̳����Ļ���ĳ�Ա���ݡ�
//				���������������ĳ�Ա���ݣ�����Ҫ�����µĹ��캯������ʼ����
//				����������û�������ĳ�Ա���ݣ�����Ҫ�����µĹ��캯����
	Grandfather(void);
	Grandfather(std::string name, unsigned int age, std::string address, std::string career, std::string gender);
	Grandfather(const Grandfather& gf);
	~Grandfather(void);

	void setGender(std::string);
	std::string getGender(void)	const;

	void say(void);		// ���ǻ����еĺ���say


protected:
	std::string gender;
};



class Dog
{
public:
//		���û�й��캯����ϵͳ���Զ�����һ���޲εĹ��캯����
	
	void bark(void);

};



class HuskieDog : public Dog
{
public:
//		��������û�������ĳ�Ա���ݣ����Բ���Ҫ�����µĹ��캯����

	void bark(void);		// ���ǻ����еĺ���bark;

};





//������ࣺVector����������������
class Vector							 
{
public:
//		0. static��Ա���ݡ�
	static int objCount;


//		1. ���졢����������
	Vector(void);
	Vector(float x, float y);
	~Vector(void);						


//		2. static��Ա����
	static int getObjCount(void)
	{
		return Vector::objCount;
	}

//		3. �Գ�Ա����get / set�ĺ���
	float getX(void)	const;
	float getY(void)	const;
	void setX(float x);
	void setY(float y);

//		4. ���������


//		5. ��������
	virtual void say(void) = 0;				// "= 0;"��ʾ���麯��						


protected:
	float x, y;

};




//�����ࣺVector2d������ά������
class Vector2d :public Vector 
{
//		������Ԫ����������Ԫ�������Է��ʱ����Protected��private��Ա��
	friend std::ostream& operator<<(std::ostream&, const Vector2d&);

public:
//		0. static��Ա���ݡ�
//		1. ���졢����������
	Vector2d(void);
	Vector2d(float x, float y);
	Vector2d(const Vector2d& v);
	~Vector2d(void);

//		2. static��Ա����
//		3. �Գ�Ա����get / set�ĺ���
//		4. ��������������ĺ���
	float operator *(const Vector2d& v)	const;				// ���س˷������


//		5. ��������.
	float dot(const Vector2d& v)	const;					// ������ˡ�
	void say(void)  override;										// �ؼ���override������־�Ÿ��Ǽ̳ж����ĺ���					 


};



//      ��Ա��������ָ����ࡣ
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



// ������baseTypePrinter������ӡ�������ͱ���
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


//      ������FooPrinter�������������Ǵ�ӡclassFoo����
class FooPrinter
{
    // ������ʾ�����ô�����
private:
    unsigned int count;

public:
	FooPrinter();

	void operator()(const classFoo& f);
    
	unsigned int getCount(void);

};





/***************************************************************************
***************************************************************************/
// ����ʵ��
// printFoo����������ӡclassFoo����
inline void printFoo(const classFoo& f)
{
    std::cout << "\t"<< f.str << "----" << f.age; 
}

 
 // ��ӡ�������͵ı�����
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
