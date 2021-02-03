#pragma once
#include "basicTools/basicTools.h"
#include "STL_iterator迭代器.h"
#include "STL_map键值对集合.h"
#include "STL_set键集合.h"
#include "STL_容器适配器.h"
#include "STL_算法库.h"
#include "STL_线性容器.h"

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
