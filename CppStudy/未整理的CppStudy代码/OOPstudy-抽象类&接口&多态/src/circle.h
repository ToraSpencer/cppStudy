#include "figure.h"
#define pi 3.14159

#ifndef SRC_CIRCLE_H_
#define SRC_CIRCLE_H_

class circle: public figure
{public:
	circle():figure(),r(1)
	{cout << "a circle object is instantiated." << endl;}

	void say()
	{cout << "I'm a circle!" << endl;}

	virtual void getArea()
	{
		float area = pi*r*r;
		cout << "the area of the circle is " << area << endl;
	}

protected:
	float r;
};





#endif /* SRC_CIRCLE_H_ */
