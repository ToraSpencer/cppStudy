#include "base.h"
#include "derived1.h"
#include "derived2.h"
using namespace std;

int main()
{
	base* p0 = NULL;
	derived1* p1 = NULL;
	derived2* p2 = NULL;

	p0 = new base();
	p1 = new derived1();
	p2 = new derived2();

	base o0 = *p0;
	derived1 o1 = *p1;
	derived2 o2 = *p2;

	p0->disp();
	p1->disp();
	p2->disp();


	//向上造型：子类对象转换为父类对象。
	cout << endl << "upcast:" << endl;
	derived1* pa = NULL;
	pa = new derived1("a",1,1);
	derived1 a = *pa;
	a.disp();

	cout << endl << "1. upcast via a derived object assign value to a base object:" << endl ;
	base a_new = base();		//将派生类对象直接赋值给一个基类对象。
	a_new = a;
	a_new.disp();

	cout << endl << "2. upcast via pointer assignment: base pointer point to a derived object:" << endl ;
	base* pa_new = NULL;		//手动令一个基类指针指向派生类对象。
	pa_new = pa;				//等价于pa_new = &a;
	pa_new->disp();

	cout << endl << "3. upcast via dynamic_cast a derived pointer to a base pointer:" << endl;
								//用dynamic_cast命令让一个派生类对象的指针
	pa_new = NULL;				//重置。
	pa_new = dynamic_cast<base*>(pa);
	pa_new->disp();











	//cout << endl << "upcast via direct value assignment:" << endl;
	//base temp = base();					//向上造型方法1：子类对象给父类对象赋值，产生的父类对象拥有原子类对象的部分信息



	//cout << endl << "upcaste via dynamic_cast:" << endl;
	//derived1 temp1 = derived1("temp1",1992,0.5);			//向上造型方法2：使用dynamic_cast;
	//base* new_pt = dynamic_cast<base*>(pt);




	return 0;
}
