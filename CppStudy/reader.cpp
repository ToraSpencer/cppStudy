#include "reader.h"


reader::reader()
{
	this->pc = nullptr;
	this->currentChap = CHAP_ENUM::NO_CHAP;
}


reader* reader::getInstance()		// 不像chapter和module一样分配在堆上，可以使用meyer's singleton
{
	static reader caller_instance;
	return &caller_instance;
}


reader::~reader()		noexcept	// 要从最底层开始向上依次delete指针。
{
	if (this->pc != nullptr)
	{
		delete this->pc;
		this->pc = nullptr;
	}
}


void reader::showChapList()
{
	std::cout << "1. 基本类型" << std::endl;
	std::cout << "2. 设计模式" << std::endl;
}


void reader::showModuleList() 
{
	if (this->pc == nullptr) 
	{
		std::cout << "当前未指定章节。" << std::endl;
		return;
	}
	this->pc->showModuleList();
}


void reader::selectChap(const CHAP_ENUM ch)
{
	if (this->currentChap == ch) 
	{
		return;
	}

	if (pc != nullptr && Hdll != nullptr)
	{
		delete this->pc;
		this->pc = nullptr;
		FreeLibrary(Hdll);
	}

	pVV pfunc = nullptr;

	switch (ch)
	{
	case CHAP_DATA_TYPE:					// 基本类型章节
		// 加载动态库。。。
		//this->pc = chap1::getInstance();
		break;

	case CHAP_DESIGN_PATTERN:				// 设计模式章节
		Hdll = LoadLibrary(L"chap_designPattern.dll");
		if (Hdll == nullptr)
		{
			std::cout << "动态库加载失败" << std::endl;
			return;
		}
		pfunc = (pVV)(GetProcAddress(Hdll, "getChap"));
		if (pfunc == nullptr)
		{
			std::cout << "动态库函数获取失败" << std::endl;
			return;
		}
		this->pc = reinterpret_cast<chap_designPattern*>((*pfunc)());
		this->currentChap = CHAP_ENUM::CHAP_DESIGN_PATTERN;
		break;

	default:
		break;
	}

}


void reader::selectMol(const int molEnum)
{
	if (this->pc == nullptr)
	{
		return;
	}
	this->pc->selectModule(molEnum);
}


void reader::runTest(const unsigned testID)
{
	this->pc->pm->run(testID);
}