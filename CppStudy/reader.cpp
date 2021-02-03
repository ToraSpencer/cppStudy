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
	std::cout << "************章节列表***************" << std::endl;
	std::cout << "1. 基本类型" << std::endl;
	std::cout << "2. 设计模式" << std::endl;
	std::cout << "3. STL" << std::endl;
	std::cout << "4. 基本语法" << std::endl;
	std::cout << "5. 函数" << std::endl;
	std::cout << "6. C++标准库" << std::endl;
	std::cout << "7. 异常" << std::endl;

	std::cout << std::endl << std::endl;
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


bool reader::selectChap(const CHAP_ENUM ch)
{
	if (this->currentChap == ch && this->currentChap!=CHAP_ENUM::NO_CHAP)		// 选择章节和当前章节相同的话，则什么都不做。
	{
		return true;
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
	case CHAP_BASIC_TYPES:					// 基本类型章节
		Hdll = LoadLibrary(L"chap_basicTypes.dll");
		if (Hdll == nullptr)
		{
			std::cout << "动态库加载失败" << std::endl;
			return false;
		}
		pfunc = (pVV)(GetProcAddress(Hdll, "getChap"));
		if (pfunc == nullptr)
		{
			std::cout << "动态库函数获取失败" << std::endl;
			return false;
		}
		this->pc = reinterpret_cast<chap_designPattern*>((*pfunc)());
		this->currentChap = CHAP_ENUM::CHAP_BASIC_TYPES;
		break;


	case CHAP_DESIGN_PATTERN:				// 设计模式章节
		Hdll = LoadLibrary(L"chap_designPattern.dll");
		if (Hdll == nullptr)
		{
			std::cout << "动态库加载失败" << std::endl;
			return false;
		}
		pfunc = (pVV)(GetProcAddress(Hdll, "getChap"));
		if (pfunc == nullptr)
		{
			std::cout << "动态库函数获取失败" << std::endl;
			return false;
		}
		this->pc = reinterpret_cast<chap_designPattern*>((*pfunc)());
		this->currentChap = CHAP_ENUM::CHAP_DESIGN_PATTERN;
		break;


	case CHAP_STL:
		Hdll = LoadLibrary(L"chap_STL.dll");
		if (Hdll == nullptr)
		{
			std::cout << "动态库加载失败" << std::endl;
			return false;
		}
		pfunc = (pVV)(GetProcAddress(Hdll, "getChap"));
		if (pfunc == nullptr)
		{
			std::cout << "动态库函数获取失败" << std::endl;
			return false;
		}
		this->pc = reinterpret_cast<chap_STL*>((*pfunc)());
		this->currentChap = CHAP_ENUM::CHAP_STL;
		break;


	case CHAP_SYNTAX:
		Hdll = LoadLibrary(L"chap_syntax.dll");
		if (Hdll == nullptr)
		{
			std::cout << "动态库加载失败" << std::endl;
			return false;
		}
		pfunc = (pVV)(GetProcAddress(Hdll, "getChap"));
		if (pfunc == nullptr)
		{
			std::cout << "动态库函数获取失败" << std::endl;
			return false;
		}
		this->pc = reinterpret_cast<chap_syntax*>((*pfunc)());
		this->currentChap = CHAP_ENUM::CHAP_SYNTAX;
		break;

	case CHAP_FUNCTION:
		Hdll = LoadLibrary(L"chap_function.dll");
		if (Hdll == nullptr)
		{
			std::cout << "动态库加载失败" << std::endl;
			return false;
		}
		pfunc = (pVV)(GetProcAddress(Hdll, "getChap"));
		if (pfunc == nullptr)
		{
			std::cout << "动态库函数获取失败" << std::endl;
			return false;
		}
		this->pc = reinterpret_cast<chap_function*>((*pfunc)());
		this->currentChap = CHAP_ENUM::CHAP_STDLIB;
		break;

	case CHAP_STDLIB:
		Hdll = LoadLibrary(L"chap_stdlib.dll");
		if (Hdll == nullptr)
		{
			std::cout << "动态库加载失败" << std::endl;
			return false;
		}
		pfunc = (pVV)(GetProcAddress(Hdll, "getChap"));
		if (pfunc == nullptr)
		{
			std::cout << "动态库函数获取失败" << std::endl;
			return false;
		}
		this->pc = reinterpret_cast<chap_stdlib*>((*pfunc)());
		this->currentChap = CHAP_ENUM::CHAP_STDLIB;
		break;

	case CHAP_EXCEPTION:
		Hdll = LoadLibrary(L"chap_exception.dll");
		if (Hdll == nullptr)
		{
			std::cout << "动态库加载失败" << std::endl;
			return false;
		}
		pfunc = (pVV)(GetProcAddress(Hdll, "getChap"));
		if (pfunc == nullptr)
		{
			std::cout << "动态库函数获取失败" << std::endl;
			return false;
		}
		this->pc = reinterpret_cast<chap_exception*>((*pfunc)());
		this->currentChap = CHAP_ENUM::CHAP_EXCEPTION;
		break;


	default:
		return false;
	}
	return true;

}


bool reader::selectMol(const int molEnum)
{
	if (this->pc == nullptr)
	{
		return true;
	}

	return this->pc->selectModule(molEnum);
}


void reader::runTest(const unsigned testID)
{
	this->pc->pm->run(testID);
}


bool reader::isNullChap() const
{
	if (this->pc == nullptr)
	{
		return true;
	}
	else
	{
		return false;
	}
}



bool reader::isNullModule() const 
{
	if (isNullChap())
	{
		return true;
	}

	if (this->pc->isNullModule())
	{
		return true;
	}
	else 
	{
		false;
	}

}