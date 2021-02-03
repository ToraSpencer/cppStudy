#pragma once

#include "basicTools/basicTools.h"
#include "syntax_表达式.h"
#include "syntax_关键字.h"
#include "syntax_基本语句、新增语句.h"
#include "syntax_几个特殊运算符.h"
#include "syntax_类型转换.h"
#include "syntax_声明、定义、初始化.h"
#include "syntax_重载运算符.h"
#include "syntax_内存管理.h"
#include "syntax_预处理指令.h"

#pragma comment(lib, "basicTools.lib")


#ifdef DLL_EXPORTS
#define DLL_API __declspec(dllexport) 
#else
#define DLL_API __declspec(dllimport)
#endif


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
protected:
	chap_syntax() = default;

public:
	void showModuleList();
	static virtualChap* getInstance();
	bool selectModule(const int molEnum);
};



extern "C"
{
	DLL_API void* getChap();
}
