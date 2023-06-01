#include "chap_errorHandling.h"
#include "errorHandling_标准异常.h"
#include "errorHandling_基本异常处理.h"



void chap_errorHandling::showModuleList()
{
	std::cout << "************异常**************" << std::endl;
	std::cout << "1.errorHandling——基本异常处理" << std::endl;
	std::cout << "2.errorHandling——标准异常" << std::endl;
	std::cout << "3.errorHandling——断言" << std::endl;
	std::cout << "-1. 退出" << std::endl;
	std::cout << std::endl << std::endl;

}


virtualChap* chap_errorHandling::getInstance()
{
	if (nullptr != p_chapIns)
		delete p_chapIns;
	p_chapIns = new chap_errorHandling;
	return p_chapIns;
}


bool chap_errorHandling::selectModule(const int molEnum)
{
	switch (molEnum)
	{
	case MODULE_BASIC_EXCEPTION:
		this->pm = errorHandling_basic_exception_module::getInstance();
		break;
	case MODULE_STD_EXCEPTION:
		this->pm = errorHandling_std_exception_module::getInstance();
		break;
	case MODULE_ASSERT:
		this->pm = errorHandling_assert_module::getInstance();
		break;
	default:
		return false;
	}
	return true;

}


void* getChap()
{
	return reinterpret_cast<void*>(chap_errorHandling::getInstance());
}