#include "basicTools.h"

virtualModule* virtualModule::p_moduleIns = nullptr;


void virtualModule::run(unsigned testID)
{
	switch (testID)
	{
	case 0:
		test0();
		break;
	case 1:
		test1();
		break;
	case 2:
		test2();
		break;
	case 3:
		test3();
		break;
	case 4:
		test4();
		break;
	case 5:
		test5();
		break;
	case 6:
		test6();
		break;
	default:
		break;
	}
}


virtualChap* virtualChap::p_chapIns = nullptr;


virtualChap::~virtualChap()
{
	// std::cout << "调用了chap系列类的的析构函数" << std::endl;
	if (this->pm != nullptr)
	{
		delete this->pm;
		this->pm = nullptr;
	}
}


void virtualChap::runTest(const unsigned testID)
{
	if (nullptr == this->pm)
	{
		std::cout << "当前没有确定任何模块" << std::endl;
		return;
	}
	this->pm->run(testID);
}

