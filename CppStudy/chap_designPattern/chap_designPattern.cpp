#include "chap_designPattern.h"


void chap_designPattern::showModuleList()
{
	std::cout << "**********���ģʽDESIGN_PATTERN**************" << std::endl;
	std::cout << "1.���ģʽ��������ģʽ" << std::endl;
	std::cout << "2.���ģʽ��������ģʽ" << std::endl;
	std::cout << "3.���ģʽ��������ģʽ" << std::endl;
	std::cout << "4.���ģʽ��������ģʽ" << std::endl;
	std::cout << "-1. �˳�" << std::endl;
	std::cout << std::endl << std::endl;
}


virtualChap* chap_designPattern::getInstance()
{
	if (nullptr != p_chapIns)
	{
		delete p_chapIns;
	}
	p_chapIns = new chap_designPattern;
	return p_chapIns;
}


bool chap_designPattern::selectModule(const int molEnum)
{
	switch (molEnum)
	{
	case MODULE_STRATEGY:
		this->pm = designPattern_strategy_module::getInstance();
		break;
	case MODULE_FACTORY:
		this->pm = designPattern_factory_module::getInstance();
		break;
	case MODULE_SINGLETON:
		this->pm = designPattern_singleton_module::getInstance();
		break;
	case MODULE_PROXY:
		this->pm = designPattern_proxy_module::getInstance();
		break;
	default:
		return false;
	}
	return true;
}


void* getChap()
{
	return reinterpret_cast<void*>(chap_designPattern::getInstance());
}