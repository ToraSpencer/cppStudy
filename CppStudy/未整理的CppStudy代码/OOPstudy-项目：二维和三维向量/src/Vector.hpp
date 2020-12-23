/*抽象类，所有向量类的最根部的基类。
 *
 */

#define pi 3.14159

#include <string>
#include <iostream>
#include <cmath>
#include <typeinfo>
using namespace std;

#ifndef SRC_VECTOR_HPP_
#define SRC_VECTOR_HPP_


class Vector
{public:
	virtual ~Vector(){}

	virtual void sayHi()
	{cout << "I'm a vector!" << endl; }

	virtual void disp() = 0;

	virtual void normalize() = 0;

	static void showCount()
	{cout << "Vcount = " << Vcount << endl;}

protected:
	static int Vcount;				//static成员变量只能在类体外初始化，但是static const成员变量可以再类体内直接赋值。。
};

int Vector::Vcount = 0;







#endif /* SRC_VECTOR_HPP_ */
