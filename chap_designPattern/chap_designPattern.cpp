#include "chap_designPattern.h"


void chap_designPattern::showModuleList()
{
	std::cout << "**********设计模式DESIGN_PATTERN**************" << std::endl;
	std::cout << "1.设计模式——策略模式" << std::endl;
	std::cout << "2.设计模式——工厂模式" << std::endl;
	std::cout << "3.设计模式——单例模式" << std::endl;
	std::cout << "4.设计模式——代理模式" << std::endl;
	std::cout << "-1. 退出" << std::endl;
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


void chap_designPattern::selectModule(const int molEnum)
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
		break;
	}

}


void* getChap()
{
	return reinterpret_cast<void*>(chap_designPattern::getInstance());
}