#include "basicTools.h"



virtualModule* virtualModule::p_moduleIns = nullptr;


void virtualModule::run(unsigned testID)
{
	switch (testID)
	{
	case 1:
		test1();
		break;
	case 2:
		test2();
		break;
	default:
		break;
	}
}


virtualChap* virtualChap::p_chapIns = nullptr;


virtualChap::~virtualChap()
{
	std::cout << "调用了chap系列类的的析构函数" << std::endl;
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


reader::reader()
{
	this->pc = nullptr;
}


reader* reader::getInstance()		// 不像chapter和module一样分配在堆上，可以使用meyer's singleton
{
	static reader caller_instance;
	return &caller_instance;
}


reader::~reader()		noexcept	// 要从最底层开始向上依次delete指针。
{
	if (this->pc != nullptr)
	{
		delete this->pc;
		this->pc = nullptr;
	}
}


void reader::showChapList()
{
	std::cout << "1. dataType" << std::endl;
	std::cout << "2. design pattern" << std::endl;
}


void reader::selectChap(const CHAP_ENUM ch)
{
	// to be optimized: 希望对现有的this->pc指向的chapter对象做类型判断，如果和接收的ch对应的类型一样，则不需要做任何操作。
	if (pc != nullptr)
	{
		delete this->pc;
		this->pc = nullptr;
	}

	switch (ch)
	{
	case CHAP_DATA_TYPE:
		// 加载动态库。。。
		//this->pc = chap1::getInstance();
		break;
	case CHAP_DESIGN_PATTERN:
		//this->pc = chap2::getInstance();
		break;
	default:
		break;
	}



}


void reader::selectMol(const int molEnum)
{
	if (this->pc == nullptr)
	{
		return;
	}
	this->pc->selectModule(molEnum);
}


void reader::runTest(const unsigned testID)
{
	this->pc->pm->run(testID);
}