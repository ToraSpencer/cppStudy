#include "chap_syntax.h"



void chap_syntax::showModuleList()
{
	std::cout << "************�����﷨SYNTAX**************" << std::endl;
	std::cout << "1.syntax�����ؼ���" << std::endl;
	std::cout << "2.syntax�������ʽ" << std::endl;
	std::cout << "3.syntax����������䡢�������" << std::endl;
	std::cout << "4.syntax�����������������" << std::endl;
	std::cout << "5.syntax�������������塢��ʼ��" << std::endl;
	std::cout << "6.syntax��������ת��" << std::endl;
	std::cout << "7.syntax�������������" << std::endl;
	std::cout << "8.syntax�����ڴ����" << std::endl;
	std::cout << "9.syntax����Ԥ����ָ��" << std::endl;
	std::cout << "-1. �˳�" << std::endl;
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