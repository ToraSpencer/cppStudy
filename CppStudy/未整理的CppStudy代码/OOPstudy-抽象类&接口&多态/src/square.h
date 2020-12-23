#include "figure.h"

#ifndef SRC_SQUARE_H_
#define SRC_SQUARE_H_

class square: public figure
{public:
	square():figure(),length(1)
	{cout << "a square object is instantiated." << endl;}

	void say()
	{cout << "I'm a square!" << endl;}

	virtual void getArea()
	{
		float area = length*length;
		cout << "the area of the square is " << area << endl;
	}

protected:
	float length;

};



#endif /* SRC_SQUARE_H_ */
