#pragma once
#include "basicTools/basicTools.h"
#include "function_����ָ��.h"
#include "function_��������.h"
#include "function_�ɱ��������.h"
#include "function_����ģ��.h"
#include "function_������.h"
 
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
