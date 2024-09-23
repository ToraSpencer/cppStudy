#include <iostream>
#include <string>
#include <typeinfo>

#include <cstdio>

#include "shapes.h" 
using namespace std;

#define EPS 1e-10					//定义非常小的一个量EPSilon，当浮点数不大于这个值时，视为0
#define PI 3.14159



// 知识点：
/*
		虚函数
					定义
								virtual关键字修饰的类内函数。
								虚函数不会静态绑定（即编译器不会对该函数进行链接），而是运行的时候才动态绑定。
					tips
								基类声明了一个虚函数，子类中该函数也是虚的。
								类中构造函数不可以是虚的，析构函数可以是。
								基类中成员函数可以分为两类：
					 					1. 希望直接被子类继承的成员函数
					 					2. 希望子类覆盖的函数????一般都设置成虚函数。
							


		纯虚函数
					定义
								虚函数声明的末尾加上“=0”就变成了纯虚函数。
								纯虚函数只有声明没有实现。			
					作用
								当一个类中有纯虚函数时，该类是一个抽象类，无法被实例化。此时该类存在的意义就是定义了一些接口规范。
					tips	
								纯虚函数必须在派生类中被实现。
								
								
								
		多态
					定义
							简单的说就是多种形态。具体的说就是一个函数在不同情形下会执行不同的行为。
					实现
							多态在C++中有两种实现，一种是函数重载，一种是类方法的多态。
							函数重载是指允许多个函数重名——只要它们的参数列表不同。
							类方法的多态——类之间有继承关系时，它们的方法可以有不同的实现，但是名字是相同的，调用这种方法执行什么行为具体要看是哪个对象调用。
							类方法多态实现的重点是虚函数——当一个方法被声明为virtual时，将不会实行静态绑定，而是会在运行时进行动态绑定。——这样的多态是运行时的多态。
					好处
							多态的好处是实现了接口重用，一个接口有多个实现。



		关键字override（c++11)
					写在某个类成员函数声明之后，标志该函数覆盖了基类中的同名虚函数。
					若未覆成功，编译会报错。




		？？？为什么虚函数效率低？
					因为虚函数需要增加一次间接的寻址。
					一般的静态绑定的函数编译的时候就已经确定了函数的地址，而虚函数是在运行时执行动态绑定，运行时才去确定函数的地址，多了一个步骤，自然效率低。
					虽然效率低，但是带来了运行时的多态。


		基类的析构函数应该设置成虚的
					因为每个析构函数只会清理自己的成员，如果多态情形下，一个基类指针或引用指向了一个子类对象，此时析构就会出错，产生未定义的行为，可能会析构不完全造成内存泄漏。




		





/***************************************************************************
***************************************************************************/
// 全局变量、类型定义
 

 
// extern变量
extern void(*pfun[100])(void);
extern int inputTag, inputNum, interfaceLevel;

 
// 函数声明
void set_fun_OOP_polymorphism(void);
void start_OOP_polymorphism(void);

static void test0(void);
static void test1(void);
static void test2(void);
static void test3(void);
static void test4(void);

 
// extern函数
void traverse_pfun(void);
 
// 自定义类的实现
class Animal
{
public:
    void no_virtual()
    {
        cout << "动物的非虚函数" << endl;
    }
    virtual void has_virtual()
    {
        cout << "动物的虚函数" << endl;
    }
};


class Cat : public Animal
{
public:
    void no_virtual()
    {
        cout << "猫的非虚函数" << endl;
    }
    virtual void has_virtual()
    {
        cout << "猫的虚函数" << endl;
    }
};

 



/***************************************************************************
***************************************************************************/
// 函数定义
void set_fun_OOP_polymorphism(void) 
{
	 pfun[0] = test0;
	 pfun[1] = test1;
}



void start_OOP_polymorphism(void)
{
	// 界面层级符置为3，进入三级界面：
	interfaceLevel = 3;
	while (3 == interfaceLevel)
	{
		cout << "\n\n\n\n" << endl;
		cout << "**************************MENU: OOP_OOP_polymorphism**********************" << endl;
		cout << "Please choose a demon function to run:" << endl;
		cout << "-2: Run all existed demon function." << endl;
		cout << "-1: Back to the previous interface." << endl;
		cout << "0. test0:  " << endl;
		cout << "1. test1：虚函数和非虚函数在派生类中重写 " << endl;


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


		case 1:
			(*pfun[1])();


		default:
			printf("Invalid input. Please input again:\n");
			break;
		}


	}
}



// test0：静态关联、动态关联的多态
static void test0(void) 
{
    Shape* ps = NULL;
    Point p1(1,2);
    Square s1(2,3,4);
    Cube c1(3,4,5);

    cout << "\n\n\n\n" << endl;
    cout << "test0: 静态关联、动态关联的多态" << endl;
    
	// 静态关联的多态：编译时就已经确定了函数的版本
    cout << "静态关联的多态：编译时就已经确定了函数的版本" << endl;
    p1.shapeName();
    cout << p1 << endl;
    s1.shapeName();
    c1.shapeName();
    cout << endl;

    // 动态关联的多态：编译时没有确定函数的版本，运行时才确定：
    cout << "动态关联的多态：编译时没有确定函数的版本，运行时才确定" << endl;
    ps = &p1;
    ps->shapeName();
    cout << endl;
    
}



// test1：虚函数和非虚函数在派生类中重写
static void test1(void)
{
	  // 可能会被继承的类方法应该声明为虚的，否则在调用的时候回发生问题。
    Animal* animal = new Cat();             // 动物指针指向猫对象，预期调用猫的方法。
    animal->no_virtual();             // 这里是执行非虚函数，所以是静态绑定，用哪个函数版本取决于指针的类型，而不关心指针指向对象的类型。
    animal->has_virtual();            // 这里是执行虚函数，所以是动态绑定，用哪个版本取决于指针所指向的对象是什么类型。
    
    
    Animal animal2;

    Cat* cat = static_cast<Cat*>(&animal2);       //  这里是动物指针向下造型为猫指针，因为动物指针原来指向的是动物对象，所以这个向下造型是不安全的，如果用dynamic_cast将不会通过。
    cat->no_virtual();                  // 实际上执行了猫版本的非虚函数         
    cat->has_virtual();                 //  实际上执行了动物版本的虚函数
 

}
