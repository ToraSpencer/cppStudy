#pragma once


#include "basicTools/basicTools.h"



struct designPattern_singleton_module : public virtualModule
{
protected:
	designPattern_singleton_module() = default;

public:
	static virtualModule* getInstance();
	virtual void test0();
	virtual void test1();
	virtual void test2();
	virtual void test3();
	virtual void test4();
	virtual void test5();
	virtual void test6();
};

