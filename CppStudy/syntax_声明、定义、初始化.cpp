#include <iosfwd>
#include <ios>
#include <istream>
#include <ostream>
#include <iostream>
#include <string>
#include <typeinfo>

#include <cstdio>


using namespace std;

#define EPS 1e-10					//定义非常小的一个量EPSilon，当浮点数不大于这个值时，视为0
#define PI 3.14159



// syntax_声明、定义、初始化
/*
				 
*/


/***************************************************************************
***************************************************************************/
// extern变量
extern void(*pfun[100])(void);
extern int inputTag, inputNum, interfaceLevel;



/***************************************************************************
***************************************************************************/
// 函数声明
void set_fun_syntax__declare_define_initialize(void);
void start_syntax__declare_define_initialize(void);

static void test0(void);
static void test1(void);
static void test2(void);
static void test3(void);
static void test4(void);


/***************************************************************************
***************************************************************************/
// extern函数
void traverse_pfun(void);


/***************************************************************************
***************************************************************************/
// 自定义类的实现
class AAA 
{
private:
	int numi;
	float numf;

public:
	AAA()
	{}

	void disp()
	{
		cout << "AAA类型的对象中：numi == " << this->numi << "， numf == " << this ->numf << endl;
	}
};



/***************************************************************************
***************************************************************************/
// 函数定义
void set_fun_syntax_declare_define_initialize(void) 
{

}



void start_syntax_declare_define_initialize(void) {}





//
AAA a_global;
int numi_global;
float numf_global;
static void test0(void) 
{
	extern int intName;			// 声明——声明一个名字
	int intDefined;				// 定义——创建一个数据实体，和一个名字绑定起来。

	// 函数体外是全局变量，函数体内是局部变量，main函数也算。
	//	全局基本类型变量会自动初始化为0值，局部基本类型的变量不会自动初始化。
	//	定义类对象的时候，不管是局部的还是全局的，都会自动调用无参构造函数。
	//	未初始化的局部变量不可使用。
	AAA a_local;
	int numi_local;
	float numf_local;

	a_global.disp();
	cout << "numi_global =="<< numi_global << endl;
	cout << "" << numf_global << endl;

	// 类的构造函数中，可以不显示初始化成员数据。
	//		然后用该构造函数构造的全局对象会自动将成员数据初始化为0值。
	//		局部对象成员数据不会自动初始化，为随机值，但是不会影响该对象的使用。
	a_local.disp();



}
