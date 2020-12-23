#include "square.h"

#ifndef SRC_CUBE_H_
#define SRC_CUBE_H_

class cube: public square
{public:
	cube():square(),length(1){cout << "a cube object is instantiated." << endl;}

	void say(){cout << "I'm a cube!" << endl;}

	void getArea()
	{
		float area = 6*length*length;
		cout << "the area of the circle is " << area << endl;
	}

protected:
	float length;

};





#endif /* SRC_CUBE_H_ */
