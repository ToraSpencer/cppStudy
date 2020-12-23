#include "base.h"
#include "derived2.h"

derived2::derived2():base(),name("derived2Obj"),ID(2),value(2),level(2)
{cout << "a derived2 object is instantiated." << endl;}

derived2::derived2(string na,int id,float va,int le):base(na,id),name(na),ID(id),value(va),level(le)
{cout << "a derived2 object is instantiated." << endl;}

derived2::~derived2()
{cout << "a derived2 object is destroyed." << endl;}

void derived2::disp()
{
	cout << this->name << ": ID = " << this->ID << ", value = " << this->value << ", level = " << this->level <<", I'm a derived2 class object." << endl;
}

