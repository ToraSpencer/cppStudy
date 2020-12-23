#include "Vector.hpp"
#include "Vector2D.hpp"

int main()
{
	Vector* pv= NULL;					//创建一个指针变量，如果不急着用的话，最好设为NULL
	Vector2D<int>* pc1 = NULL;
	Vector2D<double>* pc2 = NULL;
	Vector2D<int> vc1(1,2);
	Vector2D<double> vc2 = Vector2D<double>();
	Vector2D<double> vc3 = Vector2D<double>::polar(1,pi/2);

	pc1 = &vc1;
	pc2 = &vc2;

	pc1->disp();
	pc2->disp();
	vc3.disp();


	return 0;
}
