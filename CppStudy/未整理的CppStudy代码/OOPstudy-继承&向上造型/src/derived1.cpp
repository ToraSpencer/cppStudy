#include "base.h"
#include "derived1.h"

derived1::derived1():name("derived1Obj"),ID(1),value(1)
{cout << "a derived1 object is instantiated." << endl;}

derived1::derived1(string na, int id, float va):base(na, id),name(na),ID(id),value(va)
{cout << "a derived1 object is instantiated." << endl;}

derived1::~derived1()
{cout << "a derived1 object is destroyed." << endl;}

void derived1::disp()
{
	cout << this->name << ": ID = " << this->ID << ", value = " << this->value << ", I'm a derived1 class object." << endl;
}
