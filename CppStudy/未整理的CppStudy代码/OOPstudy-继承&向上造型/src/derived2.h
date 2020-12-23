#include "base.h"

#ifndef SRC_DERIVED2_H_
#define SRC_DERIVED2_H_

class derived2: public base
{public:
	derived2();
	derived2(string na,int id,float va,int le);
	~derived2();
	void disp();

protected:
	string name;
	int ID;
	float value;
	int level;
};



#endif /* SRC_DERIVED2_H_ */
