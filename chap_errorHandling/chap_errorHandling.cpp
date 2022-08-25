#include "chap_errorHandling.h"
#include "errorHandling_��׼�쳣.h"
#include "errorHandling_�����쳣����.h"



void chap_errorHandling::showModuleList()
{
	std::cout << "************�쳣**************" << std::endl;
	std::cout << "1.errorHandling���������쳣����" << std::endl;
	std::cout << "2.errorHandling������׼�쳣" << std::endl;
	std::cout << "3.errorHandling��������" << std::endl;
	std::cout << "-1. �˳�" << std::endl;
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