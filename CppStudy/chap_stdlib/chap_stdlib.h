#pragma once
#include "basicTools/basicTools.h"
#include "stdlib_IO��.h"
#include "stdlib_���߿�.h"
#include "stdlib_��ֵ��.h"
#include "stdlib_����֧�ֿ�.h"
#include "stdlib_�߳�֧�ֿ�.h"
#include "stdlib_������ʽ.h"

#pragma comment(lib, "basicTools.lib")


#ifdef DLL_EXPORTS
#define DLL_API __declspec(dllexport) 
#else
#define DLL_API __declspec(dllimport)
#endif


enum STDLIB_MODULE
{
	MODULE_IO = 1,
	MODULE_TOOLS,
	MODULE_NUMERICAL,
	MODULE_TYPE_SUPPORT,
	MODULE_THREAD_SUPPORT,
	MODULE_REGEX,
};


struct chap_stdlib : public virtualChap
{
protected:
	chap_stdlib() = default;

public:
	void showModuleList();
	static virtualChap* getInstance();
	bool selectModule(const int molEnum);
};



extern "C"
{
	DLL_API void* getChap();
}
