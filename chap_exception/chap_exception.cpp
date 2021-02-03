#include "chap_exception.h"
#include "exception_标准异常.h"
#include "exception_基本异常处理.h"



void chap_exception::showModuleList()
{
	std::cout << "************异常**************" << std::endl;
	std::cout << "1.exception——基本异常处理" << std::endl;
	std::cout << "2.exception——标准异常" << std::endl;
	std::cout << "-1. 退出" << std::endl;
	std::cout << std::endl << std::endl;

}


virtualChap* chap_exception::getInstance()
{
	if (nullptr != p_chapIns)
	{
		delete p_chapIns;
	}
	p_chapIns = new chap_exception;
	return p_chapIns;
}


bool chap_exception::selectModule(const int molEnum)
{
	switch (molEnum)
	{
	case MODULE_BASIC_EXCEPTION:
		this->pm = exception_basic_exception_module::getInstance();
		break;
	case MODULE_STD_EXCEPTION:
		this->pm = exception_std_exception_module::getInstance();
		break;
 
	default:
		return false;
	}
	return true;

}


void* getChap()
{
	return reinterpret_cast<void*>(chap_exception::getInstance());
}