#pragma once

#include "basicTools/basicTools.h" 
#pragma comment(lib, "basicTools.lib")


#ifdef CHAP_SYNTAX_EXPORTS
#define DLL_API __declspec(dllexport) 
#else
#define DLL_API __declspec(dllimport)
#endif


extern "C"
{
	DLL_API void* getChap();
}


enum SYNTAX_MODULE
{
	MODULE_EXPRESSION = 1,
	MODULE_KEYWORD,
	MODULE_BASIC_STATEMENT,
	MODULE_OPERATOR,
	MODULE_TYPE_CAST,
	MODULE_DECLARE_DEFINE_INITIALIZE,
	MODULE_OVERLOADED_OPERATOR,
	MODULE_MEMORY_MANAGEMENT,
	MODULE_PREPROCESSING_INSTRUCTION,
};


struct chap_syntax : public virtualChap
{ 
	chap_syntax() = default; 
	void showModuleList();
	static virtualChap* getInstance();
	bool selectModule(const int molEnum);
};

  
//
struct syntax_keyword_module : public virtualModule
{
	static virtualModule* getInstance();
	virtual void test0();
	virtual void test1();
	virtual void test2();
	virtual void test3();
	virtual void test4();
	virtual void test5();
	virtual void test6();
	virtual void test7();
};


struct syntax_expression_module : public virtualModule
{
	static virtualModule* getInstance();
	virtual void test0();
	virtual void test1();
	virtual void test2();
	virtual void test3();
	virtual void test4();
	virtual void test5();
	virtual void test6();
	virtual void test7();
};


struct syntax_basic_statement_module : public virtualModule
{
	static virtualModule* getInstance();
	virtual void test0();
	virtual void test1();
	virtual void test2();
	virtual void test3();
	virtual void test4();
	virtual void test5();
	virtual void test6();
	virtual void test7();
};


struct syntax_operator_module : public virtualModule
{
	static virtualModule* getInstance();
	virtual void test0();
	virtual void test1();
	virtual void test2();
	virtual void test3();
	virtual void test4();
	virtual void test5();
	virtual void test6();
	virtual void test7();
};


struct syntax_type_cast_module : public virtualModule
{
	static virtualModule* getInstance();
	virtual void test0();
	virtual void test1();
	virtual void test2();
	virtual void test3();
	virtual void test4();
	virtual void test5();
	virtual void test6();
	virtual void test7();
};


struct syntax_memory_management_module : public virtualModule
{
	static virtualModule* getInstance();
	virtual void test0();
	virtual void test1();
	virtual void test2();
	virtual void test3();
	virtual void test4();
	virtual void test5();
	virtual void test6();
	virtual void test7();
};


struct syntax_declare_define_initialize_module : public virtualModule
{
	static virtualModule* getInstance();
	virtual void test0();
	virtual void test1();
	virtual void test2();
	virtual void test3();
	virtual void test4();
	virtual void test5();
	virtual void test6();
	virtual void test7();
};


struct syntax_preprocessing_instruction_module : public virtualModule
{
	static virtualModule* getInstance();
	virtual void test0();
	virtual void test1();
	virtual void test2();
	virtual void test3();
	virtual void test4();
	virtual void test5();
	virtual void test6();
	virtual void test7();
};


struct syntax_overloaded_operator_module : public virtualModule
{
	static virtualModule* getInstance();
	virtual void test0();
	virtual void test1();
	virtual void test2();
	virtual void test3();
	virtual void test4();
	virtual void test5();
	virtual void test6();
	virtual void test7();
};
