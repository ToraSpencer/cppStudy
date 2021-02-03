#pragma once
#include "basicTools/basicTools.h"
#include "basicTypes_内置类型.h"
#include "basicTypes_数组.h"
#include "basicTypes_c风格字符串、string、wstring.h"
#include "basicTypes_对、元祖.h"
#include "basicTypes_枚举、共用体、结构体.h"
#include "basicTypes_指针、智能指针、内存泄漏.h"
#include "basicTypes_引用.h"
 
#pragma comment(lib, "basicTools.lib")


#ifdef DLL_EXPORTS
#define DLL_API __declspec(dllexport) 
#else
#define DLL_API __declspec(dllimport)
#endif


enum BASIC_TYPES_MODULE
{
	MODULE_BUILTIN_TYPES = 1,
	MODULE_ARRAY,
	MODULE_STRINGS,
	MODULE_POINTERS,
	MODULE_REFERENCE,
	MODULE_PAIR_TUPLE,
	MODULE_ENUM_UNION_STRUCT,
};


struct chap_basicTypes : public virtualChap
{
protected:
	chap_basicTypes() = default;

public:
	void showModuleList();
	static virtualChap* getInstance();
	bool selectModule(const int molEnum);
};



extern "C"
{
	DLL_API void* getChap();

}
