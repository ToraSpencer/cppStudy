#include "chap_syntax.h"



void chap_syntax::showModuleList()
{
	std::cout << "************基本语法SYNTAX**************" << std::endl;
	std::cout << "1.syntax——关键字" << std::endl;
	std::cout << "2.syntax——表达式" << std::endl;
	std::cout << "3.syntax——基本语句、新增语句" << std::endl;
	std::cout << "4.syntax——几个特殊运算符" << std::endl;
	std::cout << "5.syntax——声明、定义、初始化" << std::endl;
	std::cout << "6.syntax——类型转换" << std::endl;
	std::cout << "7.syntax——重载运算符" << std::endl;
	std::cout << "8.syntax——内存管理" << std::endl;
	std::cout << "9.syntax——预处理指令" << std::endl;
	std::cout << "-1. 退出" << std::endl;
	std::cout << std::endl << std::endl;

}


virtualChap* chap_syntax::getInstance()
{
	if (nullptr != p_chapIns)
	{
		delete p_chapIns;
	}
	p_chapIns = new chap_syntax;
	return p_chapIns;
}


bool chap_syntax::selectModule(const int molEnum)
{
	switch (molEnum)
	{
	case MODULE_KEYWORD:
		this->pm = syntax_keyword_module::getInstance();
		break;
	case MODULE_EXPRESSION:
		this->pm = syntax_expression_module::getInstance();
		break;
	case MODULE_BASIC_STATEMENT:
		this->pm = syntax_basic_statement_module::getInstance();
		break;
	case MODULE_OPERATOR:
		this->pm = syntax_operator_module::getInstance();
		break;
	case MODULE_DECLARE_DEFINE_INITIALIZE:
		this->pm = syntax_declare_define_initialize_module::getInstance();
		break;
	case MODULE_TYPE_CAST:
		this->pm = syntax_type_cast_module::getInstance();
		break;
	case MODULE_OVERLOADED_OPERATOR:
		this->pm = syntax_overloaded_operator_module::getInstance();
		break;
	case MODULE_MEMORY_MANAGEMENT:
		this->pm = syntax_memory_management_module::getInstance();
		break;
	case MODULE_PREPROCESSING_INSTRUCTION:
		this->pm = syntax_preprocessing_instruction_module::getInstance();
		break;
	default:
		return false;
	}
	return true;

}


void* getChap()
{
	return reinterpret_cast<void*>(chap_syntax::getInstance());
}