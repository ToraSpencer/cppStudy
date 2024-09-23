#include <string>
#include<iostream>
#include <cstddef>
#include <memory>

#include <cstdio>

using namespace std;


/*
	��ģ��

*/

 
// ȫ�ֱ��������Ͷ���
template <typename T, size_t N>
class Foo				// ��װ������������ģ�壬������һЩ����
{
private:
	// ˽������
	T arr[N];

public:
	// ���졢��������
	Foo() = default;						// =default����ʾ��Ҫ��������Զ�����һ���޲ι��캯����							
	Foo(initializer_list<T> l);			// ʹ��initializer_list������
	Foo(T*, int);								// ���������׵�ַ����������������
	~Foo();		


	// ��������
	void disp(void);


};
 
// extern����
extern void(*pfun[100])(void);
extern int inputTag, inputNum, interfaceLevel;

 
// ��������

void set_fun_OOP_class_template(void);
void start_OOP_class_template(void);

static void test0(void);
static void test1(void);
static void test2(void);
static void test3(void);
static void test4(void);

 
// extern����
extern void traverse_pfun(void);

 
// �Զ������ʵ��


 
// ��������
template <typename T, size_t N>
Foo<T, N>::Foo(initializer_list<T> l)
{
	// ��Ҫ�жϳ�ʼ���б�l�е�Ԫ���Ƿ����N������N�Ļ�Ҫô�׳��쳣��Ҫôֻʹ��ǰN��Ԫ��
	// this->arr = new T[N];
	T* pData = this->arr;
	for(auto iter = begin(l); iter!=end(l); iter++)
	{
		*pData = *iter;
		  pData++;
	} 	
	cout << "A Foo object has been instantiated." << endl;
}



template <typename T, size_t N>
Foo<T, N>::Foo(T* p, int num)
{
	// ��num���ں���ķ�Χ�ڣ��׳��쳣�����߷���һ���յ�Foo����
	// this->arr = new T[N];
	T* pData = this->arr;

	for(int i = 1; i <= num; i++)
	{
		*pData = *p;
		pData++;
		p++;
	}
	cout << "A Foo object has been instantiated." << endl;

}



template <typename T, size_t N>
Foo<T, N>::~Foo()
{	
 
	cout<< "A Foo object has been eliminated." << endl;

}



template <typename T, size_t N>
void Foo<T, N>::disp(void)
{
	for(auto elem:(this->arr))
	{
		cout << "\t" << elem;
	}
	cout << endl;
}





void set_fun_OOP_class_template(void) 
{
  pfun[0] = test0;
}



void start_OOP_class_template(void) 
{
	// ����㼶����Ϊ3�������������棺
	interfaceLevel = 3;
	while (3 == interfaceLevel)
	{
		cout << "\n\n\n\n" << endl;
		cout << "**************************MENU: OOP_class_template**********************" << endl;
		cout << "Please choose a demon function to run:" << endl;
		cout << "-2: Run all existed demon function." << endl;
		cout << "-1: Back to the previous interface." << endl;
		cout << "0: test0: �򵥵��Զ�����ģ���ʹ��" << endl;


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

		default:
			printf("Invalid input. Please input again:\n");
			break;
		}


	}
}



// test0: �򵥵��Զ�����ģ���ʹ��.
static void test0()
{
	int arri[10] = {1,2,3,4,5,6,7,8,9,10};
	Foo<float, 5> Farrf1;
	Foo<int, 10> Farri1(arri, 10);
	Foo<int, 5> Farri2 = {-1,-2,-3,-4,-5};
	
	cout << "\n\n\n\n" << endl;
	cout << "test0: �򵥵��Զ�����ģ���ʹ��" << endl;
	Farrf1.disp();
	Farri1.disp();
	Farri2.disp();



}

