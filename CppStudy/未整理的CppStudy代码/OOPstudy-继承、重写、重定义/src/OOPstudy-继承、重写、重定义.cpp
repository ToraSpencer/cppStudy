/* 重写(覆盖):override
 *		定义：子类中定义了一个与父类完全相同的虚函数，则称重写（覆盖）了父类的这个虚函数。
 *		注意：被重写的函数必须是虚函数
 *			 只可以重写方法，不可以重写变量。
 *			 某函数重写了父类的虚函数，这个函数即使不加上virtual关键字系统也认为是虚函数。
 *
 *
 * 重定义（隐藏）:redefine
 *		定义：如果在父类和子类中有相同名字的成员，那么在子类中。会将父类的成员隐藏。
 *			 隐藏的效果：无论在子类的内部或者外部（通过子类成员）访问该成员，都是访问子类的同名成员； 如果在子类内部或者外部（通过子类成员）访问同名的成员函数，则需要根据函数调用的规则来调用子类的同名成员函数；否则调用失败；
 *
 */

#include <iostream>
#include <string>
using namespace std;

class Person
{protected :
    string  _name;
public:
	virtual ~Person(){}
    virtual void BuyTickets(){cout<<" 买票-全票"<< endl;}
};

class Student : public Person
{protected :
    int _num ; //学号

public:
	 virtual ~Student(){}
     void BuyTickets(){cout<<" 买票-半价"<<endl ;}
};


void testOverride()
{
	cout << "重写（覆盖）的测试：" << endl;
    Person p;
    Person* pp = new Person();
    Student s;
    Student* ps = new Student();
    p.BuyTickets();
    pp->BuyTickets();
    s.BuyTickets();
    ps->BuyTickets();
}

class A
{
protected:
    A(int x=2):_a(x){}
public:
    void show(int a)
    {
        cout<<"A::shou()"<<endl;
    }
    int _a;
};

class B:public A
{
public:
    B(int x=1)
        :_a(x)
    {}

public:
    void show(int a,int b)
    {
        cout<<"B::shou()"<<endl;
        cout<<_a<<endl;
    }
    int _a;
};

void testRedifine()
{
    B b;
    cout<<(b._a)<<endl;
    //b.show(1);
}


int main()
{
	testOverride();
	return 0;
}

