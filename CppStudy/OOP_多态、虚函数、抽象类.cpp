#include <iostream>
#include <string>
#include <typeinfo>

#include <cstdio>

#include "shapes.h" 
using namespace std;

#define EPS 1e-10					//����ǳ�С��һ����EPSilon�������������������ֵʱ����Ϊ0
#define PI 3.14159



// ֪ʶ�㣺
/*
		�麯��
					����
								virtual�ؼ������ε����ں�����
								�麯�����ᾲ̬�󶨣�������������Ըú����������ӣ����������е�ʱ��Ŷ�̬�󶨡�
					tips
								����������һ���麯���������иú���Ҳ����ġ�
								���й��캯������������ģ��������������ǡ�
								�����г�Ա�������Է�Ϊ���ࣺ
					 					1. ϣ��ֱ�ӱ�����̳еĳ�Ա����
					 					2. ϣ�����า�ǵĺ���????һ�㶼���ó��麯����
							


		���麯��
					����
								�麯��������ĩβ���ϡ�=0���ͱ���˴��麯����
								���麯��ֻ������û��ʵ�֡�			
					����
								��һ�������д��麯��ʱ��������һ�������࣬�޷���ʵ��������ʱ������ڵ�������Ƕ�����һЩ�ӿڹ淶��
					tips	
								���麯���������������б�ʵ�֡�
								
								
								
		��̬
					����
							�򵥵�˵���Ƕ�����̬�������˵����һ�������ڲ�ͬ�����»�ִ�в�ͬ����Ϊ��
					ʵ��
							��̬��C++��������ʵ�֣�һ���Ǻ������أ�һ�����෽���Ķ�̬��
							����������ָ������������������ֻҪ���ǵĲ����б�ͬ��
							�෽���Ķ�̬������֮���м̳й�ϵʱ�����ǵķ��������в�ͬ��ʵ�֣�������������ͬ�ģ��������ַ���ִ��ʲô��Ϊ����Ҫ�����ĸ�������á�
							�෽����̬ʵ�ֵ��ص����麯��������һ������������Ϊvirtualʱ��������ʵ�о�̬�󶨣����ǻ�������ʱ���ж�̬�󶨡����������Ķ�̬������ʱ�Ķ�̬��
					�ô�
							��̬�ĺô���ʵ���˽ӿ����ã�һ���ӿ��ж��ʵ�֡�



		�ؼ���override��c++11)
					д��ĳ�����Ա��������֮�󣬱�־�ú��������˻����е�ͬ���麯����
					��δ���ɹ�������ᱨ��




		������Ϊʲô�麯��Ч�ʵͣ�
					��Ϊ�麯����Ҫ����һ�μ�ӵ�Ѱַ��
					һ��ľ�̬�󶨵ĺ��������ʱ����Ѿ�ȷ���˺����ĵ�ַ�����麯����������ʱִ�ж�̬�󶨣�����ʱ��ȥȷ�������ĵ�ַ������һ�����裬��ȻЧ�ʵ͡�
					��ȻЧ�ʵͣ����Ǵ���������ʱ�Ķ�̬��


		�������������Ӧ�����ó����
					��Ϊÿ����������ֻ�������Լ��ĳ�Ա�������̬�����£�һ������ָ�������ָ����һ��������󣬴�ʱ�����ͻ��������δ�������Ϊ�����ܻ���������ȫ����ڴ�й©��




		





/***************************************************************************
***************************************************************************/
// ȫ�ֱ��������Ͷ���
 

 
// extern����
extern void(*pfun[100])(void);
extern int inputTag, inputNum, interfaceLevel;

 
// ��������
void set_fun_OOP_polymorphism(void);
void start_OOP_polymorphism(void);

static void test0(void);
static void test1(void);
static void test2(void);
static void test3(void);
static void test4(void);

 
// extern����
void traverse_pfun(void);
 
// �Զ������ʵ��
class Animal
{
public:
    void no_virtual()
    {
        cout << "����ķ��麯��" << endl;
    }
    virtual void has_virtual()
    {
        cout << "������麯��" << endl;
    }
};


class Cat : public Animal
{
public:
    void no_virtual()
    {
        cout << "è�ķ��麯��" << endl;
    }
    virtual void has_virtual()
    {
        cout << "è���麯��" << endl;
    }
};

 



/***************************************************************************
***************************************************************************/
// ��������
void set_fun_OOP_polymorphism(void) 
{
	 pfun[0] = test0;
	 pfun[1] = test1;
}



void start_OOP_polymorphism(void)
{
	// ����㼶����Ϊ3�������������棺
	interfaceLevel = 3;
	while (3 == interfaceLevel)
	{
		cout << "\n\n\n\n" << endl;
		cout << "**************************MENU: OOP_OOP_polymorphism**********************" << endl;
		cout << "Please choose a demon function to run:" << endl;
		cout << "-2: Run all existed demon function." << endl;
		cout << "-1: Back to the previous interface." << endl;
		cout << "0. test0:  " << endl;
		cout << "1. test1���麯���ͷ��麯��������������д " << endl;


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


		case 1:
			(*pfun[1])();


		default:
			printf("Invalid input. Please input again:\n");
			break;
		}


	}
}



// test0����̬��������̬�����Ķ�̬
static void test0(void) 
{
    Shape* ps = NULL;
    Point p1(1,2);
    Square s1(2,3,4);
    Cube c1(3,4,5);

    cout << "\n\n\n\n" << endl;
    cout << "test0: ��̬��������̬�����Ķ�̬" << endl;
    
	// ��̬�����Ķ�̬������ʱ���Ѿ�ȷ���˺����İ汾
    cout << "��̬�����Ķ�̬������ʱ���Ѿ�ȷ���˺����İ汾" << endl;
    p1.shapeName();
    cout << p1 << endl;
    s1.shapeName();
    c1.shapeName();
    cout << endl;

    // ��̬�����Ķ�̬������ʱû��ȷ�������İ汾������ʱ��ȷ����
    cout << "��̬�����Ķ�̬������ʱû��ȷ�������İ汾������ʱ��ȷ��" << endl;
    ps = &p1;
    ps->shapeName();
    cout << endl;
    
}



// test1���麯���ͷ��麯��������������д
static void test1(void)
{
	  // ���ܻᱻ�̳е��෽��Ӧ������Ϊ��ģ������ڵ��õ�ʱ��ط������⡣
    Animal* animal = new Cat();             // ����ָ��ָ��è����Ԥ�ڵ���è�ķ�����
    animal->no_virtual();             // ������ִ�з��麯���������Ǿ�̬�󶨣����ĸ������汾ȡ����ָ������ͣ���������ָ��ָ���������͡�
    animal->has_virtual();            // ������ִ���麯���������Ƕ�̬�󶨣����ĸ��汾ȡ����ָ����ָ��Ķ�����ʲô���͡�
    
    
    Animal animal2;

    Cat* cat = static_cast<Cat*>(&animal2);       //  �����Ƕ���ָ����������Ϊèָ�룬��Ϊ����ָ��ԭ��ָ����Ƕ����������������������ǲ���ȫ�ģ������dynamic_cast������ͨ����
    cat->no_virtual();                  // ʵ����ִ����è�汾�ķ��麯��         
    cat->has_virtual();                 //  ʵ����ִ���˶���汾���麯��
 

}
