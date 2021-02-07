#pragma once

#include "basicTools/basicTools.h"
#include "DSA_Ë³Ðò±í.h"
#include "DSA_Á´±í.h"
#include "DSA_¹þÏ£±í.h"
#include "DSA_¶þ²æÊ÷.h"
#include "DSA_Í¼.h"


#pragma comment(lib, "basicTools.lib")


#ifdef DLL_EXPORTS
#define DLL_API __declspec(dllexport) 
#else
#define DLL_API __declspec(dllimport)
#endif


enum DSA_MODULE
{
	MODULE_SEQUENCE_LIST = 1,
	MODULE_LINKED_LIST,
	MODULE_HASHED_LIST,
	MODULE_BINARY_TREE,
	MODULE_GRAPH,
};


struct chap_DSA : public virtualChap
{
protected:
	chap_DSA() = default;

public:
	void showModuleList();
	static virtualChap* getInstance();
	bool selectModule(const int molEnum);
};



extern "C"
{
	DLL_API void* getChap();
}
