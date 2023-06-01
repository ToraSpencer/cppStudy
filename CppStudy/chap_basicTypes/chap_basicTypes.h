#pragma once
#include "basicTools/basicTools.h"
#include "basicTypes_��������.h"
#include "basicTypes_����.h"
#include "basicTypes_c����ַ�����string��wstring.h"
#include "basicTypes_�ԡ�Ԫ��.h"
#include "basicTypes_ö�١������塢�ṹ��.h"
#include "basicTypes_ָ�롢����ָ�롢�ڴ�й©.h"
#include "basicTypes_����.h"
 


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
