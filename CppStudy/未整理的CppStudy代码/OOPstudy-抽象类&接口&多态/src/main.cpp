
#include "square.h"
#include "circle.h"
#include "cube.h"

int main()
{
	figure *p = NULL;
	square objS = square();
	circle objC = circle();
	cube objCU = cube();
	p = &objS;
	p->say();
	p->getArea();

	p = &objC;
	p->say();
	p->getArea();

	p = NULL;
	p = &objCU;
	p->say();
	p->getArea();








	return 0;
}
