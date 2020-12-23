#include "base.h"

base::base():name("baseObj"),ID(0)
{cout << "a base object is instantiated." << endl;}

base::base(string na, int id):name(na),ID(id)
{cout << "a base object is instantiated." << endl;}

base::~base()
{cout << "a base object is destroyed." << endl;}

void base::disp()
{
	cout << this->name << ": ID = " << this->ID << ", I'm a base class object." << endl;
}

