#include "chap_DSA.h"



void chap_DSA::showModuleList()
{
	std::cout << "************���ݽṹ���㷨**************" << std::endl;
	std::cout << "1.DSA����˳���" << std::endl;
	std::cout << "2.DSA���������" << std::endl;
	std::cout << "3.DSA������ϣ��" << std::endl;
	std::cout << "4.DSA����������" << std::endl;
	std::cout << "5.DSA����ͼ" << std::endl;
	std::cout << "-1. �˳�" << std::endl;
	std::cout << std::endl << std::endl;

}


virtualChap* chap_DSA::getInstance()
{
	if (nullptr != p_chapIns)
	{
		delete p_chapIns;
	}
	p_chapIns = new chap_DSA;
	return p_chapIns;
}


bool chap_DSA::selectModule(const int molEnum)
{
	switch (molEnum)
	{
	case MODULE_SEQUENCE_LIST:
		this->pm = DSA_sequence_list_module::getInstance();
		break;
	case MODULE_LINKED_LIST:
		this->pm = DSA_linked_list_module::getInstance();
		break;
	case MODULE_HASHED_LIST:
		this->pm = DSA_hashed_list_module::getInstance();
		break;
	case MODULE_BINARY_TREE:
		this->pm = DSA_binary_tree_module::getInstance();
		break;
	case MODULE_GRAPH:
		this->pm = DSA_graph_module::getInstance();
		break;
	default:
		return false;
	}
	return true;

}


void* getChap()
{
	return reinterpret_cast<void*>(chap_DSA::getInstance());
}