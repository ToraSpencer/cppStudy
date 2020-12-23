//注意编译的先后次序。
#include <iostream>
#include <string>
using namespace std;


class B;							//前向声明。此时没有给出明确类定义，只能声明B类对象的指针（地址）。

class A
{public:
	friend class B;					//声明B是本类友元类，可以访问本类的私有和保护成员。
	A():x(1){}
	void disp()
	{cout << "A object: x = " << this->x << endl;}
	void dispB(B *pb);				//此时不可以写dispB方法的实现，因为B类还没有被明确定义。

private:
	int x;
};

class B
{public:
	friend class A;					//声明A是本类的友元类，可以访问本类的私有和保护成员。
	B():y(2){}
	void disp()
	{cout << "B object: y = " << this->y << endl;}
	void dispA(A *pa)				//输入参数为A对象的指针，读取A对象的数据。
	{cout << "B get A object: x = " << pa->x << endl;}
private:
	int y;
};


void A::dispB(B *pb)
{cout << "A get B object: y = " << pb->y << endl;}

int main()
{
	A *pa = NULL;
	B *pb = NULL;
	pa = new A();
	pb = new B();
	pa->disp();
	pb->disp();
	pa->dispB(pb);
	pb->dispA(pa);

	system("pause");

	return 0;
}

