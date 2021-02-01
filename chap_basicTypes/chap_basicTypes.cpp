#include "chap_basicTypes.h"


void chap_basicTypes::showModuleList()
{
	std::cout << "**********基本类型BASIC TYPES**************" << std::endl;
	std::cout << "1.基本类型——内置类型" << std::endl;
	std::cout << "2.基本类型——数组" << std::endl;
	std::cout << "3.基本类型——c风格字符串、string、wstring" << std::endl;
	std::cout << "4.基本类型——指针、智能指针、内存泄漏" << std::endl;
	std::cout << "5.基本类型——引用" << std::endl;
	std::cout << "6.基本类型——对、元祖" << std::endl;
	std::cout << "7.基本类型——枚举、共用体、结构体" << std::endl;
	std::cout << "-1. 退出" << std::endl;
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



void chap_basicTypes::selectModule(const int molEnum)
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
		break;
	}

}


void* getChap()
{
	return reinterpret_cast<void*>(chap_basicTypes::getInstance());
}


