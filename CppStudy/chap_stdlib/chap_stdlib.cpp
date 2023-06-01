#include "chap_stdlib.h"



void chap_stdlib::showModuleList()
{
	std::cout << "************C++标准库**************" << std::endl;
	std::cout << "1.stdlib——IO库" << std::endl;
	std::cout << "2.stdlib——数值库" << std::endl;
	std::cout << "3.stdlib——工具库" << std::endl;
	std::cout << "4.stdlib——类型支持库" << std::endl;
	std::cout << "5.stdlib——线程支持库" << std::endl;
	std::cout << "6.stdlib——正则表达式" << std::endl;
	std::cout << "-1. 退出" << std::endl;
	std::cout << std::endl << std::endl;

}


virtualChap* chap_stdlib::getInstance()
{
	if (nullptr != p_chapIns)
	{
		delete p_chapIns;
	}
	p_chapIns = new chap_stdlib;
	return p_chapIns;
}


bool chap_stdlib::selectModule(const int molEnum)
{
	switch (molEnum)
	{
	case MODULE_IO:
		this->pm = stdlib_io_module::getInstance();
		break;
	case MODULE_NUMERICAL:
		this->pm = stdlib_numerical_module::getInstance();
		break;
	case MODULE_TOOLS:
		this->pm = stdlib_tools_module::getInstance();
		break;
	case MODULE_TYPE_SUPPORT:
		this->pm = stdlib_type_support_module::getInstance();
		break;
	case MODULE_THREAD_SUPPORT:
		this->pm = stdlib_thread_support_module::getInstance();
		break;
	case MODULE_REGEX:
		this->pm = stdlib_regex_module::getInstance();
		break;
	default:
		return false;
	}
	return true;

}


void* getChap()
{
	return reinterpret_cast<void*>(chap_stdlib::getInstance());
}