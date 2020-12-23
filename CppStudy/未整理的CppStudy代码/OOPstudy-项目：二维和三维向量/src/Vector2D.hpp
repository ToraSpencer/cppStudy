/*二维平面上、笛卡尔坐标系下的向量。
 */
#include "Vector.hpp"

#ifndef SRC_Vector2D_HPP_
#define SRC_Vector2D_HPP_

template <typename T>
class Vector2D: public Vector
{public:
	Vector2D();
	Vector2D(T x0,T y0);
	~Vector2D();

	void disp();
	void normalize();
	void say();
	static void showCount();
	static Vector2D<double> polar(T r0,T theta0);	//输入极坐标，返回一个向量对象。

protected:
	T x,y,r;
	static T VCcount;							//static成员变量只能在类体外初始化，但是static const成员变量可以再类体内直接赋值。。
};

template <typename T>
T Vector2D<T>::VCcount = 0;

template <typename T>
Vector2D<T>::Vector2D()
{
	x = (T)1;
	y = (T)1;
	r = sqrt(x*x+y*y);
	Vcount++;
	VCcount++;
}

template <typename T>
Vector2D<T>::Vector2D(T x0,T y0):x(x0),y(y0)
{
	r = sqrt(x*x+y*y);
	Vcount++;
	VCcount++;
}

template <typename T>
Vector2D<T>::~Vector2D()
{
	Vcount--;
	VCcount--;
	cout << "a cartesian 2D vector is destroyed." << endl;
}

template <typename T>
void Vector2D<T>::disp()
		{
			cout << "(" << this->x << ", " << this->y << ")" << endl;
		}

template <typename T>
void Vector2D<T>::normalize()
		{
			this->x = this->x/this->r;
			this->y = this->y/this->r;
			this->r = 1;
		}

template <typename T>
void Vector2D<T>::say()
		{
			cout << "I'm a Cartesian 2D vector!" << endl;
		}

template <typename T>
void Vector2D<T>::showCount()
		{
			cout << "VCcount = " << VCcount << endl;
		}

template <typename T>
Vector2D<double> Vector2D<T>::polar(T r0,T theta0)
{
	double x0 = (double)r0*cos((double)theta0);
	double y0 = (double)r0*sin((double)theta0);
	Vector2D<double> temp(x0,y0);
	return temp;
}

#endif /* SRC_Vector2D_HPP_ */
