#pragma once
#include "basicTools/basicTools.h"
#include "function_函数指针.h"
#include "function_内联函数.h"
#include "function_可变参数函数.h"
#include "function_函数模板.h"
#include "function_函数子.h"
 
#pragma comment(lib, "basicTools.lib")


#ifdef DLL_EXPORTS
#define DLL_API __declspec(dllexport) 
#else
#define DLL_API __declspec(dllimport)
#endif


enum FUNCTION_MODULE
{
	MODULE_FUNCTION_POINTER = 1,
	MODULE_INLINE_FUNCTION,
	MODULE_VARIADIC_FUNCTION,
	MODULE_FUNCTION_TEMPLATE,
	MODULE_FUNCTOR,
};


struct chap_function : public virtualChap
{
protected:
	chap_function() = default;

public:
	void showModuleList();
	static virtualChap* getInstance();
	bool selectModule(const int molEnum);
};



extern "C"
{
	DLL_API void* getChap();
}
