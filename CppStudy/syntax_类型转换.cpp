#include <iostream>
#include <string>
#include <typeinfo>

#include <cstdio>


using namespace std;

#define EPS 1e-10					//定义非常小的一个量EPSilon，当浮点数不大于这个值时，视为0
#define PI 3.14159

//	知识点
/*	
 
		C风格的强制类型转换
					(T)arg;

			
		四种显式强制类型转换：
					static_cast 		
								可以执行内置数据类型之间的转换。
								可以执行有继承关系的指针、引用的转换，但是类对象之间的转换建议还是用dynamic_cast更安全。
								

					dynamic_cast 		
								可以执行有继承关系的类对象的指针、引用的转换。
								转换前会类型安全检查，如果不安全的话则转换失败，返回NULL指针。
								向下造型的时候一定要使用，如基类指针/引用转换为派生类指针/引用，此时很容易发生安全问题。
								

					const_cast 
								可以去除、增添变量的const属性，一般不会使用。

					reinterpret_cast 
								类似于C风格的强制类型转换，不安全。


	
		类型安全转换：
					子类转换成父类是安全的，父类转换成子类是不安全的。
					可以理解为子类的信息是多于父类的，子类转换成父类时，大不了丢掉一些信息，但是父类转换成子类的话，会有信息空洞，是不安全的。 

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
void set_fun_syntax_type_conversion(void);
void start_syntax_type_conversion(void);

static void test0(void);
static void test1(void);
static void test2(void);
static void test3(void);
static void test4(void);



/***************************************************************************
***************************************************************************/
// extern函数
extern void traverse_pfun(void);



/***************************************************************************
***************************************************************************/
// 自定义类的实现


class Pet 
{
    public: virtual ~Pet() {} 
};


class Tortoise : public Pet {};


class Rabbit : public Pet {};




/***************************************************************************
***************************************************************************/
// 函数定义
void set_fun_syntax_type_conversion(void) 
{
	pfun[0] = test0;
}



void start_syntax_type_conversion(void)
{
	// 界面层级符置为3，进入三级界面：
	interfaceLevel = 3;
	while (3 == interfaceLevel)
	{
		cout << "\n\n\n\n" << endl;
		cout << "**************************MENU: syntax_type_conversoin_template**********************" << endl;
		cout << "Please choose a demon function to run:" << endl;
		cout << "-2: Run all existed demon function." << endl;
		cout << "-1: Back to the previous interface." << endl;
		cout << "0: test0: const_cast" << endl;


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

		default:
			printf("Invalid input. Please input again:\n");
			break;
		}


	}
}



// test0: const_cast
static void test0(void)
{
	int  numi1 = 5;
	const int* pci1 = NULL;
	int* pi1 = NULL;

	cout << "test0: const_cast" << endl;

	pci1 = &numi1;											 			// const指针pci1指向numi1，是底层const。不可以通过pci1来修改numi1的值。
	pi1 = const_cast<int*>(pci1);						 	 // 使用pci1给pi1赋值，但是使用const_cast移除了const属性。


	*pi1 = 6;
	cout << "\tpci1 = &numi1; pi1 = const_cast<int*>(pci1);	 *pi1 = 6; " << endl;
	cout <<"\tnumi1 == " << numi1 << endl;

}


// test1: 使用dynamic_cast()实现向下造型(downcast)
static void test1(void)
{
	Pet* pet = new Rabbit;							// 指向兔子对象的pet指针。
	
	Tortoise* tortoise = dynamic_cast<Tortoise*>(pet);	// Pet指针试图向下造型为Tortoise指针，理应是失败的
	Rabbit* rabbit = dynamic_cast<Rabbit*>(pet);		// Pet指针指针向下造型为Rabbit指针，理应是成功的，因为Pet指针原先指向的就是Rabbit对象。

	
	if (tortoise == NULL)					// 转换失败dynamic_cast将会返回NULL指针。
	{
			printf("Pet指针向下造型为Tortoise指针失败\n");
	}
	else
	{
			printf("Pet指针向下造型为Tortoise指针成功\n");
	}
	
	if (rabbit == NULL)
	{
			printf("Pet指针向下造型为Rabbit指针失败\n");
	}
	else
	{
			printf("Pet指针向下造型为Rabbit指针成功\n");
	}



}
