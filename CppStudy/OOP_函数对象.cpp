#include <iostream>
#include <string>
#include <typeinfo>


#include <cstdio>

#include "example.h"

using namespace std;

#define EPS 1e-10					//����ǳ�С��һ����EPSilon�������������������ֵʱ����Ϊ0
#define PI 3.14159



// C++��������̡����������󣨺����ӣ���ͷ�ļ�functional
/*
	�������󣨺����ӣ��ࣺ
			��һ�����н������()����Ϊ��Ա���������������һ�����������࣬��ʵ������һ����������
			ʹ����������ʽ�ͺ�������һ��������Ҳȷʵ�����˺������á�
			����������Ա��溯���ĵ���״̬������ʵ�ֺ����ص���
			
	<functional>ͷ�ļ�
			��׼���еĺ���������ģ��
			
	lambda���ʽ��c++11��
			������һ��������������Ҳ��һ���ɵ��õı��ʽ��

			�����б�
				[=,&a,&b]		�����ô��ݵķ�ʽ��׽����a��b����ֵ���ݷ�ʽ��׽�������б���;
				[&,a,this]		��ֵ���ݵķ�ʽ��׽����a��this�����ô��ݷ�ʽ��׽�������б�����
			
			
			��׽�б���������ظ����ݡ�����һЩ���Ӿ��ǵ��͵��ظ����ᵼ�±���ʱ�ڵĴ���
				X [=,a]	�������������Ѿ���ֵ���ݷ�ʽ��׽�����б����������ظ���׽a�ˣ��ᱨ���;
				X [&,&this]������������&�Ѿ������ô��ݷ�ʽ��׽�����б������ٲ�׽thisҲ��һ���ظ���
					

*/

  
// extern����
extern void(*pfun[100])();
extern int inputTag, inputNum, interfaceLevel;
 
// ��������
void set_fun_OOP_function_object();
void start_OOP_function_object();

static void test0();
static void test1();
static void test2();
static void test3();
static void test4();

 
// extern����
void traverse_pfun();
 

// �Զ������ʵ��
 
 
// ��������
void set_fun_OOP_function_object() 
{
	 pfun[0] = test0;
	 pfun[1] = test1;
}



void start_OOP_function_object()
{
	// ����㼶����Ϊ3�������������棺
	interfaceLevel = 3;
	while (3 == interfaceLevel)
	{
		cout << "\n\n\n\n" << endl;
		cout << "**************************MENU: OOP_function_object**********************" << endl;
		cout << "Please choose a demon function to run:" << endl;
		cout << "-2: Run all existed demon function." << endl;
		cout << "-1: Back to the previous interface." << endl;
		cout << "0. test0: ��������Ļ������ܡ��ص㡣" << endl;
		cout << "1. test1��<functional>�еĳ��ú���������ģ��" << endl;
		cout << "2. test2: �򵥵�lambda���ʽ" << endl;


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
			


		default:
			printf("Invalid input. Please input again:\n");
			break;
		}


	}
}



// test0: ��������Ļ������ܡ��ص㡣
static void test0() 
{
	cout << "\n\n\n\n" << endl;
	cout << "test0: ��������Ļ������ܡ��ص�" << endl;

	vector<classFoo> vf;
    classFoo f1;
    classFoo f2("xiaoming", 12);
    classFoo f3("xiaohong", 23);
    classFoo f4("laowang", 87);
    FooPrinter ffoo;
 
    vf.push_back(f1);
    vf.push_back(f2);
    vf.push_back(f2);
    vf.push_back(f3);
    vf.push_back(f4);

    cout << "���ݺ���������" << endl;
    for_each(vf.begin(), vf.end(), printFoo);

    cout << "���ݺ����ӱ�����" << endl;
    auto ffoo1 = for_each(vf.begin(), vf.end(), ffoo);
    cout << endl;
	// ��ʾ�����ӱ����ô�����
	// ffooֻ����for_each�����б���������û�б����ã����������õ��Ǳ������Ķ���ffoo1
	cout << "\tffoo.getCount() == " << ffoo.getCount() << endl;
    cout << "\tffoo1.getCount() == " << ffoo1.getCount() << endl;
    

 
 
}



// test1��<functional>�еĳ��ú�����ģ�壺
static void test1()
{
	cout << "\n\n\n\n" << endl;
	cout << "test1��<functional>�еĳ��ú���������ģ��" << endl;

	plus<int> plus_int;
	int result = 0;
	result = plus_int(5,6);
	cout << "\t plus_int(5,6) == " << plus_int(5,6) << endl;

}



// test2: �򵥵�lambda���ʽ
static void test2()
{
	cout << "\n\n\n\n" << endl;
	cout << "test2: �򵥵�lambda���ʽ" << endl;


	// û�в�����û�з���ֵ��lambda���ʽ
	auto functor1 = []() {cout << "hello" << endl; };	 
	functor1(); 


	// �в������з���ֵ��lambda���ʽ
	auto functor2 = [](const string& a, const string& b) -> bool    // β����ָʾ����ֵ�����͡�
	{
		return a.size() < b.size(); 
	};
	string str1 = "hahaha";
	string str2 = "haha";
	if(functor2(str1, str2))
	{
		cout << "str1��str2��" << endl;
	}
	else
	{
		cout << "str1��str2��" << endl;
	}


	// ���㷨���е��㷨����lambda���ʽ��������
	vector<string> vi = {"hahah","hello","lalala"};
	//			�����Ͳ���Ҫ��ȫ�ַ�Χ���ٶ��ⶨ�庯�������ࡣ
	for_each(vi.begin(), vi.end(), [](const string& str) {cout << str << endl; });




}




static void test3()
{



}
