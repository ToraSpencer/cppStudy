#pragma once
#include "basicTools/basicTools.h"
#include "STL_iterator������.h"
#include "STL_map��ֵ�Լ���.h"
#include "STL_set������.h"
#include "STL_����������.h"
#include "STL_�㷨��.h"
#include "STL_��������.h"

#pragma comment(lib, "basicTools.lib")


#ifdef DLL_EXPORTS
#define DLL_API __declspec(dllexport) 
#else
#define DLL_API __declspec(dllimport)
#endif


enum STL_MODULE
{
	MODULE_LINEAR_CONTAINER = 1,
	MODULE_ADAPTER,
	MODULE_SET,
	MODULE_MAP,
	MODULE_ITERATOR,
	MODULE_ALGORITHM,
};


struct chap_STL : public virtualChap
{
protected:
	chap_STL() = default;

public:
	void showModuleList();
	static virtualChap* getInstance();
	bool selectModule(const int molEnum);
};



extern "C"
{
	DLL_API void* getChap();
}
