#include "chap_basicTypes.h"


void chap_basicTypes::showModuleList()
{
	std::cout << "**********��������BASIC TYPES**************" << std::endl;
	std::cout << "1.�������͡�����������" << std::endl;
	std::cout << "2.�������͡�������" << std::endl;
	std::cout << "3.�������͡���c����ַ�����string��wstring" << std::endl;
	std::cout << "4.�������͡���ָ�롢����ָ�롢�ڴ�й©" << std::endl;
	std::cout << "5.�������͡�������" << std::endl;
	std::cout << "6.�������͡����ԡ�Ԫ��" << std::endl;
	std::cout << "7.�������͡���ö�١������塢�ṹ��" << std::endl;
	std::cout << "-1. �˳�" << std::endl;
	std::cout <<  std::endl << std::endl;
}


virtualChap* chap_basicTypes::getInstance()
{
	if (nullptr != p_chapIns)
	{
		delete p_chapIns;
	}
	p_chapIns = new chap_basicTypes;
	return p_chapIns;
}



bool chap_basicTypes::selectModule(const int molEnum)
{
	switch (molEnum)
	{
	case MODULE_BUILTIN_TYPES:
		this->pm = basicTypes_builtin_types_module::getInstance();
		break;
	case MODULE_ARRAY:
		this->pm = basicTypes_array_module::getInstance();
		break;
	case MODULE_STRINGS:
		this->pm = basicTypes_strings_module::getInstance();
		break;
	case MODULE_POINTERS:
		this->pm = basicTypes_pointers_module::getInstance();
		break;
	case MODULE_REFERENCE:
		this->pm = basicTypes_reference_module::getInstance();
		break;
	case MODULE_PAIR_TUPLE:
		this->pm = basicTypes_pair_tuple_module::getInstance();
		break;
	case MODULE_ENUM_UNION_STRUCT:
		this->pm = basicTypes_enum_union_struct_module::getInstance();
		break;
	default:
		return false;
	}
	return true;

}


void* getChap()
{
	return reinterpret_cast<void*>(chap_basicTypes::getInstance());
}


