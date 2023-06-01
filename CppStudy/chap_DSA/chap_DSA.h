#pragma once

#include "basicTools/basicTools.h"
#include "DSA_˳���.h"
#include "DSA_����.h"
#include "DSA_��ϣ��.h"
#include "DSA_������.h"
#include "DSA_ͼ.h"


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
