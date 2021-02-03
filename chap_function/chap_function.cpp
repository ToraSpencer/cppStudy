 #include "chap_function.h"



void chap_function::showModuleList()
{
	std::cout << "************函数**************" << std::endl;
	std::cout << "1.function——函数指针" << std::endl;
	std::cout << "2.function——内联函数" << std::endl;
	std::cout << "3.function——可变参数函数" << std::endl;
	std::cout << "4.function——函数模板" << std::endl;
	std::cout << "5.function——函数子" << std::endl;
	std::cout << "-1. 退出" << std::endl;
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