#pragma once

#include "basicTools/basicTools.h"
#include "syntax_���ʽ.h"
#include "syntax_�ؼ���.h"
#include "syntax_������䡢�������.h"
#include "syntax_�������������.h"
#include "syntax_����ת��.h"
#include "syntax_���������塢��ʼ��.h"
#include "syntax_���������.h"
#include "syntax_�ڴ����.h"
#include "syntax_Ԥ����ָ��.h"

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
