#include <iostream>
#include <string>
using namespace std;

#ifndef SRC_FIGURE_H_
#define SRC_FIGURE_H_

class figure
{public:
	virtual ~figure() = 0;

	virtual void say()
	{cout << "I'm a abstract figure" << endl;}

	virtual void getArea() = 0;
};


#endif /* SRC_FIGURE_H_ */
