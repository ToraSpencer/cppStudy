#pragma once

#include <windows.h>

#include "basicTools/basicTools.h"
#include "designPattern/chap_designPatter.h"


#pragma comment(lib, "./Release/basicTools.lib")

extern HMODULE Hdll;
using VOIDP = void*;
using pVV = VOIDP(*)(void);

enum CHAP_ENUM
{
	CHAP_DATA_TYPE = 1,
	CHAP_DESIGN_PATTERN,
};


struct reader
{
private:
	virtualChap* pc;		// 当前查看的章节。

	reader();

public:
	static reader* getInstance();

	~reader() noexcept;

	void showChapList();

	void selectChap(const CHAP_ENUM ch);

	void selectMol(const int molEnum);

	void runTest(const unsigned testID);
};



