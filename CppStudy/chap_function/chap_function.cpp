 #include "chap_function.h"



void chap_function::showModuleList()
{
	std::cout << "************����**************" << std::endl;
	std::cout << "1.function��������ָ��" << std::endl;
	std::cout << "2.function������������" << std::endl;
	std::cout << "3.function�����ɱ��������" << std::endl;
	std::cout << "4.function��������ģ��" << std::endl;
	std::cout << "5.function����������" << std::endl;
	std::cout << "-1. �˳�" << std::endl;
	std::cout << std::endl << std::endl;

}


virtualChap* chap_function::getInstance()
{
	if (nullptr != p_chapIns)
	{
		delete p_chapIns;
	}
	p_chapIns = new chap_function;
	return p_chapIns;
}


bool chap_function::selectModule(const int molEnum)
{
	switch (molEnum)
	{
	case MODULE_FUNCTION_POINTER:
		this->pm = function_function_pointer_module::getInstance();
		break;
	case MODULE_INLINE_FUNCTION:
		this->pm = function_inline_function_module::getInstance();
		break;
	case MODULE_VARIADIC_FUNCTION:
		this->pm = function_variadic_function_module::getInstance();
		break;
	case MODULE_FUNCTION_TEMPLATE:
		this->pm = function_function_template_module::getInstance();
		break;
	case MODULE_FUNCTOR:
		this->pm = function_functor_module::getInstance();
		break;
	default:
		return false;
	}
	return true;

}


void* getChap()
{
	return reinterpret_cast<void*>(chap_function::getInstance());
}