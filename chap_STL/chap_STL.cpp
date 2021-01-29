#include "chap_STL.h"


void chap_STL::showModuleList()
{
	std::cout << "1.STL——线性容器" << std::endl;
	std::cout << "2.STL——容器适配器" << std::endl;
	std::cout << "3.STL——set键结合" << std::endl;
	std::cout << "4.STL——map键值对集合" << std::endl;
	std::cout << "5.STL——iterator迭代器" << std::endl;
	std::cout << "6.STL——算法库" << std::endl;
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


void chap_STL::selectModule(const int molEnum)
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
		break;
	}

}


void* getChap()
{
	return reinterpret_cast<void*>(chap_STL::getInstance());
}