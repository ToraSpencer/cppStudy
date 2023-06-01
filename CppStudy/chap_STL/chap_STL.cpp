#include "chap_STL.h"
 


void chap_STL::showModuleList()
{
	std::cout << "************STL**************" << std::endl;
	std::cout << "1.STL������������" << std::endl;
	std::cout << "2.STL��������������" << std::endl;
	std::cout << "3.STL����set�����" << std::endl;
	std::cout << "4.STL����map��ֵ�Լ���" << std::endl;
	std::cout << "5.STL����iterator������" << std::endl;
	std::cout << "6.STL�����㷨��" << std::endl;
	std::cout << "-1. �˳�" << std::endl;
	std::cout << std::endl << std::endl;

}


virtualChap* chap_STL::getInstance()
{
	if (nullptr != p_chapIns)
	{
		delete p_chapIns;
	}
	p_chapIns = new chap_STL;
	return p_chapIns;
}


bool chap_STL::selectModule(const int molEnum)
{
	switch (molEnum)
	{
	case MODULE_LINEAR_CONTAINER:
		this->pm = STL_linear_container_module::getInstance();
		break;
	case MODULE_ADAPTER:
		this->pm = STL_adapter_module::getInstance();
		break;
	case MODULE_SET:
		this->pm = STL_set_module::getInstance();
		break;
	case MODULE_MAP:
		this->pm = STL_map_module::getInstance();
		break;
	case MODULE_ITERATOR:
		this->pm = STL_iterator_module::getInstance();
		break;
	case MODULE_ALGORITHM:
		this->pm = STL_algorithm_module::getInstance();
		break;
	default:
		return false;
	}
	return true;

}


void* getChap()
{
	return reinterpret_cast<void*>(chap_STL::getInstance());
}