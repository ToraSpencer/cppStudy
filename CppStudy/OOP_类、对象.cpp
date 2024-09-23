
#include "example.h"

#include <cstdio>

#include <iostream>
#include <string>
#include <typeinfo>
using namespace std;

#define EPS 1e-10					//����ǳ�С��һ����EPSilon�������������������ֵʱ����Ϊ0
#define PI 3.14159



// ֪ʶ��
/*
			��װ
					���ض�������Ժ�ʵ��ϸ�ڣ������⹫���ӿںͶ�����н�����
					C++�е�class��һ�ַ�װ��
					��װ���洦
							ȷ���û��Ĵ��벻��������ƻ���װ�����״̬��
							����װ����ľ���ʵ��ϸ�ڿ�����ʱ�ı䣬����������û�����Ĵ��롣

			Ƕ����
					����������໥������
					���������������������пɼ������������Ͳ��ɼ��ˡ�
					һ��Ƕ����������������ڲ�������ʹ��

			�ӿ���(������)
					�ӿ����޷���ʵ���������Բ����ڽӿ���Ķ���
					���ǿ��Դ��ڽӿ����ָ�룬����ָ��������󣬿���ʵ�ֶ�̬��


			���Ա�ķ��ࣺ
					public��Ա
							0. static��Ա���ݡ�
							1. ���졢����������
							2. static��Ա����
							3. �Գ�Ա����get/set�ĺ���
							4. ��������������ĺ���
							5. ��������

					protected/private��Ա
							1. ˽�С�������Ա����
							2. ˽�С�������Ա����
					

			���&ǳ����
					ǳ����ֻ����ָ�룬ǳ����֮���������ָ��ָ��ͬһ����Դ��
					�����������Դ��ָ�롣
					

			thisָ��
					thisָ������ָ��ǰ������һ��ָ�볣��������constָ�룩��

					thisָ����ÿ����static��Ա���������ز�����

					�ڳ�Ա������ʼǰ���죬�ڳ�Ա�����������

					thisָ�벻ռ�ö���Ŀռ䡣

					�βα�����const���ı���������this�βε����ͣ��� bool same_isbn(const Sales_item &rhs) const�����ֺ�����Ϊ��������Ա����������ʱthis���Ƕ������ǵײ�const��
					
					return *this��������


			����Ĭ�ϲ����ĳ�Ա������
					�޲ι��캯��
					�������캯��
					��������
					��ֵ���������
					ȡ��ַ���������
					ȡ��ַ�����const����
					

			const����
					const����ĳ�Ա�����У�����ר������mutable���εı��������������ɸ��ġ�
					cosnt���󲻿��Ե����Լ��ķ�const�ĳ�Ա������
					�������β��б�����ĳ����󣬿������Ƹ��β�Ϊconst���󣬿��Ա����������Ķ��󲻱��޸ġ�
					ʵ����һ��const����ĸ�ʽ��
					const ���� �������������б�

					

			��Ա�����޶��ؼ��֣�
					public
							��ȫû���ơ�
					protected
							����Ĳ�ͬ����֮�䲻���Ի�����ʶԷ���protected��Ա��
					private
							����Ĳ�ͬ����֮�䲻���Ի�����ʶԷ���private��Ա��
							���������֮�䲻���Ի�����ʶԷ���private��Ա

			��Ա������������
					�����ڶ���ĳ�Ա�����������ġ�
					private����ֻ�ܱ�������������ʹ�á�


			Ĭ�Ϲ��캯����
							����δ�������캯����ϵͳ�����һ��Ĭ�ϵĹ��캯����
							���󴴽�ʱϵͳ�Զ����á�
							

			�������캯��
							�������Ϊһ�������������á�
							ʹ��һ�������ȥ��ʼ���������һ������ʱ��ϵͳ�Զ����ÿ������캯����ʵ�֡�
							������δ�����������캯����ϵͳ���Զ�����һ��Ĭ�ϵģ�������ʼ������

			��ʼ���б�
							ð�źͻ�����֮��Ĵ��룺 Sales_item(): units_sold(0), revenue(0.0) { }

			
			����������
							��δ��������������ϵͳ���Զ�����һ����


			���಻�ܼ̳��Ը������Դ
							���캯��������������operator=()����Ԫ��

			static��Ա�ļ̳�
							�����static�����ͺ������������б��̳У������ܷ����Կ��ƣ����磬�����private���еľͲ��ɷ��ʣ�
							���Ҷ�static������˵��������͸����е�static�����ǹ��ÿռ�ģ����������static�����������ü�����ʱ��Ҫ�ر�ע�⡣
							
			������ʵ�ַ���
							�������������ʵ�ַ��뿪��д������д��.h�ļ��У�ʵ��д��.cpp�ļ��С�
							������ຬ��static���ݣ������ʼ��һ��Ҫ��.cpp�ļ�����ɣ���������.h����ɣ�������ܻ�����ض���������⡣
							ע��������а�������ģ��Ļ�����ú���ģ�岻��������ʵ�ַ��롣

*/

 
// extern����
extern void(*pfun[100])(void);
extern int inputTag, inputNum, interfaceLevel;

 
// ��������
std::ostream& operator<<(std::ostream&, const Vector2d&);

void set_fun_OOP_class_object(void);
void start_OOP_class_object(void);

static void test0(void);
static void test1(void);
static void test2(void);
static void test3(void);
static void test4(void);
static void test5(void);
 
// extern����
extern void traverse_pfun(void);
 

// ��������


// operator<<������������<<���������Vector2d����Ϣд�뵽������С�
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
	// ����㼶����Ϊ3�������������棺
	interfaceLevel = 3;
	while (3 == interfaceLevel)
	{
		cout << "\n\n\n\n" << endl;
		cout << "**************************MENU: OOP_CLASS_OBJECT**********************" << endl;
		cout << "Please choose a demon function to run:" << endl;
		cout << "-2: Run all existed demon function." << endl;
		cout << "-1: Back to the previous interface." << endl;
		cout << "0. test0: ��Ͷ���Ļ���֪ʶ����Person.hpp." << endl;
		cout << "1. test1: ��ļ̳С���Grandfather.hpp" << endl;
		cout << "2. test2: �������Vector������Vector2d����Vector.hpp" << endl;
		cout << "3. test3: ��Ա���ݴ���ָ����࣬�����ǳ������" << endl;


		inputTag = scanf("%d", &inputNum);

		// ������ֵ�����������������롣
		if (inputTag != 1)
		{
			printf("Invalid input. Please input again:\n");
			setbuf(stdin, NULL);
			continue;
		}

		// ��������������ֵ����Ӧ��
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




// test0: ��Ͷ���Ļ���֪ʶ����Person.hpp.
void test0(void)
{
	Person person1;
	Person person2 = Person();
	Person person3("xiaoming", 22, "Shanghai, China", "teacher");
	Person person4 = Person("Cindy", 10, "New York, USA", "student");
	Dog wangwang;

	cout << "\n\n\n\n" << endl;
	cout << "test0: ��Ͷ���Ļ���֪ʶ����Person.hpp." << endl;
	
	person1.say();
	person2.say();
	person3.say();
	person4.say();
	wangwang.bark();
	cout << endl;

	cout << "����Person���set������" << endl;
	person2.setName("Tom");
	person2.setAge(44);
	person2.setAdress("Tokyo, Japan");
	person2.setCareer("programmer");
	person2.say();
	cout << endl;



	// ��ֱ�ӵ���static����:
	cout << "��ֱ�ӵ���static��������Person::getObjCount == " << Person::getObjCount()  << endl;


}




// test1: ��ļ̳С���Grandfather.hpp
void test1(void) 
{
	cout << "\n\n\n\n" << endl;
	cout << "test1����ļ̳С���Grandfather.hpp" << endl;

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



// test2: �������Vector������Vector2d����Vector.hpp
void test2(void) 
{
	cout << "\n\n\n\n" << endl;
	cout << "test2���������Vector������Vector2d����Vector.hpp" << endl;

	Vector2d v1;
	Vector2d v2(3,4);
	Vector2d v3(2,2);

	cout << "v1 == " << v1 << endl;
	cout << "v2 == " << v2 << endl;
	cout << endl;

	cout << "v2*v3 == " << v2 * v3 << endl;
	cout << "v2.dot(v3) == " << v2.dot(v3) << endl;



}



// test3: ��Ա���ݴ���ָ����࣬�����ǳ������
static void test3(void)
{
	cout << "\n\n\n\n" << endl;
	cout << "test3: ��Ա���ݴ���ָ����࣬�����ǳ������" << endl;

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
