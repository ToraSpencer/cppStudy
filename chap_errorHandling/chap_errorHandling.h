#pragma once

#include "basicTools/basicTools.h"
#include "errorHandling_��׼�쳣.h"
#include "errorHandling_�����쳣����.h"
#include "errorHandling_����.h"

#pragma comment(lib, "basicTools.lib")


#ifdef DLL_EXPORTS
#define DLL_API __declspec(dllexport) 
#else
#define DLL_API __declspec(dllimport)
#endif


enum EXCEPTON_MODULE
{
	MODULE_BASIC_EXCEPTION = 1,
	MODULE_STD_EXCEPTION,
	MODULE_ASSERT,
};


struct chap_errorHandling : public virtualChap
{
protected:
	chap_errorHandling() = default;

public:
	void showModuleList();
	static virtualChap* getInstance();
	bool selectModule(const int molEnum);
};



extern "C"
{
	DLL_API void* getChap();
}
