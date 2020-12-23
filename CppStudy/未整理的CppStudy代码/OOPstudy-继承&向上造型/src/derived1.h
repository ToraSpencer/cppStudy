#include "base.h"
using namespace std;

#ifndef SRC_derived1_H_
#define SRC_derived1_H_

	class derived1: public base
	{public:
		derived1();
		derived1(string na, int id, float va);
		~derived1();
		void disp();

	protected:
		string name;
		int ID;
		float value;
	};


#endif /* SRC_derived1_H_ */
