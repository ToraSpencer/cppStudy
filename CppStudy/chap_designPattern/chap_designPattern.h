#pragma once
#include "basicTools/basicTools.h"
#include "designPattern_����ģʽ.h"
#include "designPattern_����ģʽ.h"
#include "designPattern_����ģʽ.h"
#include "designPattern_����ģʽ.h"

#pragma comment(lib, "basicTools.lib")


#ifdef DLL_EXPORTS
#define DLL_API __declspec(dllexport) 
#else
#define DLL_API __declspec(dllimport)
#endif


enum DESIGNPATTERN_MODULE
{
	MODULE_STRATEGY = 1,
	MODULE_FACTORY,
	MODULE_SINGLETON,
	MODULE_PROXY,
};


struct chap_designPattern : public virtualChap
{
protected:
	chap_designPattern() = default;

public:
	void showModuleList();
	static virtualChap* getInstance();
	bool selectModule(const int molEnum);
};



extern "C"
{
	DLL_API void* getChap();

}
