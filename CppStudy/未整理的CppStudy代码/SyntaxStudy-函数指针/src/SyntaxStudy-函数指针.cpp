#include <iostream>
#include <string>
#include <cmath>
#include <typeinfo>
using namespace std;

/*函数指针
 *	函数的类型由返回值、形参列表决定，和函数名无关。函数指针也一样。
 */

float add(float a,float b){return a+b;}


// 计算器类
class calculator
{public:
	calculator(){}

	static void say()
	{
		cout << "a machine to be used to calculate." << endl;
	}

	int add(int a, int b){return a+b;}

	void disp() const {cout << "i'm a calculator object." << endl;}
};



//输入参数为函数指针的函数模板。
template <typename T>
T calculate(const T& a, const T& b, T(*pf)(const T&, const T&))			//进行两个数的运算的接口函数
{
	T result = pf(a,b);
	return result;
}



//普通函数模板
template <typename T>
T Add(const T& a, const T& b){return a+b;}



//普通函数模板
template <typename T>
T Minus(const T& a, const T& b){return a-b;}

class A
{
public:
    int fun(int a, char c)
    {
        cout<<"this is fun call:"<<a<<" "<<c<<endl;
        return a;
    }
};

class B
{
    public:
    // B 的成员函数fun1,参数是double，
    //返回值是A的成员函数指针int(A::*)(int, char)
    int (A::*fun1(double d))(int, char)
    {
        cout<<d<<endl;
        return &A::fun;
    }
};

//全局函数的指针：
void test1()
{
	float (*pf)(float, float);
	pf = add;
	cout << "pf(1,2) = " << pf(1,2) << endl;

}



//类方法的指针：
void test2()
{
	//类static方法：
	void (*pfs)()= NULL;
	pfs = &calculator::say;
	(*pfs)();

	//类的普通成员方法：
	int (calculator::*pf)(int, int) = NULL;
	pf = &calculator::add;
	calculator c1;
	cout << "(c1.*pf)(1,2) = " << (c1.*pf)(1,2) << endl;

	//类的const成员方法：
	void (calculator::*pfc)()const = NULL;
	pfc = &calculator::disp;
	(c1.*pfc)();
}

//函数指针作为另一个函数的输入参数。
void test3()
{
	cout << "calculate(1,2,Add) = " << calculate(1,2,Add) << endl;
	cout << "calculate(1,2,Minus) = " << calculate(1,2,Minus) << endl;
}

//返回函数指针的函数。
void test4()
{
	   A mytest;
	    B mytest2;
	    int (A::*p)(int, char) = mytest2.fun1(3.33);
	    (mytest.*p)(1, 'a');

}


int main()
{
	//test1();
	test2();
	//test3();

	return 0;
}




