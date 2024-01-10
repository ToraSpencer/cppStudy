#pragma once

#include <windows.h>

#include "basicTools/basicTools.h"
#include "chap_basicTypes/chap_basicTypes.h"
#include "chap_designPattern/chap_designPattern.h"
#include "chap_STL/chap_STL.h"
#include "chap_syntax/chap_syntax.h"
#include "chap_function/chap_function.h"
#include "chap_stdlib/chap_stdlib.h"
#include "chap_errorHandling/chap_errorHandling.h"
#include "chap_DSA/chap_DSA.h"


extern HMODULE g_Hdll;
using VOIDP = void*;
using pVV = VOIDP(*)(void);


enum CHAP_ENUM
{
	NO_CHAP = 0,
	CHAP_BASIC_TYPES = 1,
	CHAP_DESIGN_PATTERN,
	CHAP_STL,
	CHAP_SYNTAX,
	CHAP_FUNCTION,
	CHAP_STDLIB,
	CHAP_EXCEPTION,
	CHAP_DSA,
};


struct reader
{
private:
	virtualChap* pc;						// 当前查看的章节。
	CHAP_ENUM currentChap;		// 当前查看章节对应的枚举常量。
	reader();

public:
	static reader* getInstance();

	~reader() noexcept;

	void showChapList();

	void showModuleList();

	bool selectChap(const CHAP_ENUM ch);

	bool selectMol(const int molEnum);

	void runTest(const unsigned testID);

	bool isNullChap() const;
	bool isNullModule() const;
};



