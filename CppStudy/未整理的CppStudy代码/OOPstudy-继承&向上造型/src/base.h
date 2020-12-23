#include <iostream>
#include <string>
using namespace std;

#ifndef SRC_BASE_H_
#define SRC_BASE_H_

class base
	{public:
		base();
		base(string na, int id);
		~base();
		void disp();

	protected:
		string name;
		int ID;
	};



#endif /* SRC_BASE_H_ */
