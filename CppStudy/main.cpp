#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <cmath>
#include <windows.h>

//#include "chap_designPattern/chap_designPatter.h"
#include "reader.h"

using namespace std;

HMODULE Hdll = nullptr;

int main()
{
	reader* pr = reader::getInstance();
	pr->selectChap(CHAP_DESIGN_PATTERN);
	pr->showChapList();
	pr->selectMol(DESIGNPATTERN_MODULE::MODULE_PROXY);
	pr->showModuleList();
	pr->runTest(0);
	pr->selectMol(DESIGNPATTERN_MODULE::MODULE_FACTORY);
	pr->showModuleList();
	pr->runTest(0);


	getchar();
	return 0;
}



