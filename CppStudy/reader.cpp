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


// 打印章节列表
void reader::showChapList()
{
	std::cout << "************章节列表***************" << std::endl;
	std::cout << "1. 基本类型" << std::endl;
	std::cout << "2. 设计模式" << std::endl;
	std::cout << "3. STL" << std::endl;
	std::cout << "4. 基本语法" << std::endl;
	std::cout << "5. 函数" << std::endl;
	std::cout << "6. C++标准库" << std::endl;
	std::cout << "7. 错误处理" << std::endl;
	std::cout << "8. 数据结构与算法" << std::endl;
	std::cout << std::endl << std::endl;
}


// 打印模块列表
void reader::showModuleList() 
{
	if (this->pc == nullptr) 
	{
		std::cout << "当前未指定章节。" << std::endl;
		return;
	}
	this->pc->showModuleList();
}


// 选择章节：
bool reader::selectChap(const CHAP_ENUM ch)
{
	// 选择章节和当前章节相同的话，则什么都不做。
	if (this->currentChap == ch && this->currentChap!=CHAP_ENUM::NO_CHAP)		 
		return true; 

	if (pc != nullptr && g_Hdll != nullptr)
	{
		delete this->pc;
		this->pc = nullptr;
		FreeLibrary(g_Hdll);
	}

	pVV pfunc = nullptr;
	switch (ch)
	{
	case CHAP_BASIC_TYPES:					// 基本类型章节
	{
		g_Hdll = LoadLibrary(L"chap_basicTypes.dll");
		if (g_Hdll == nullptr)
		{
			std::cout << "动态库加载失败" << std::endl;
			return false;
		}
		pfunc = (pVV)(GetProcAddress(g_Hdll, "getChap"));
		if (pfunc == nullptr)
		{
			std::cout << "动态库函数获取失败" << std::endl;
			return false;
		}
		this->pc = reinterpret_cast<chap_designPattern*>((*pfunc)());
		this->currentChap = CHAP_ENUM::CHAP_BASIC_TYPES;
		break;
	}

	case CHAP_DESIGN_PATTERN:				// 设计模式章节
		g_Hdll = LoadLibrary(L"chap_designPattern.dll");
		if (g_Hdll == nullptr)
		{
			std::cout << "动态库加载失败" << std::endl;
			return false;
		}
		pfunc = (pVV)(GetProcAddress(g_Hdll, "getChap"));
		if (pfunc == nullptr)
		{
			std::cout << "动态库函数获取失败" << std::endl;
			return false;
		}
		this->pc = reinterpret_cast<chap_designPattern*>((*pfunc)());
		this->currentChap = CHAP_ENUM::CHAP_DESIGN_PATTERN;
		break;


	case CHAP_STL:
		g_Hdll = LoadLibrary(L"chap_STL.dll");
		if (g_Hdll == nullptr)
		{
			std::cout << "动态库加载失败" << std::endl;
			return false;
		}
		pfunc = (pVV)(GetProcAddress(g_Hdll, "getChap"));
		if (pfunc == nullptr)
		{
			std::cout << "动态库函数获取失败" << std::endl;
			return false;
		}
		this->pc = reinterpret_cast<chap_STL*>((*pfunc)());
		this->currentChap = CHAP_ENUM::CHAP_STL;
		break;


	case CHAP_SYNTAX:
		g_Hdll = LoadLibrary(L"chap_syntax.dll");
		if (g_Hdll == nullptr)
		{
			std::cout << "动态库加载失败" << std::endl;
			return false;
		}
		pfunc = (pVV)(GetProcAddress(g_Hdll, "getChap"));
		if (pfunc == nullptr)
		{
			std::cout << "动态库函数获取失败" << std::endl;
			return false;
		}
		this->pc = reinterpret_cast<chap_syntax*>((*pfunc)());
		this->currentChap = CHAP_ENUM::CHAP_SYNTAX;
		break;

	case CHAP_FUNCTION:
		g_Hdll = LoadLibrary(L"chap_function.dll");
		if (g_Hdll == nullptr)
		{
			std::cout << "动态库加载失败" << std::endl;
			return false;
		}
		pfunc = (pVV)(GetProcAddress(g_Hdll, "getChap"));
		if (pfunc == nullptr)
		{
			std::cout << "动态库函数获取失败" << std::endl;
			return false;
		}
		this->pc = reinterpret_cast<chap_function*>((*pfunc)());
		this->currentChap = CHAP_ENUM::CHAP_STDLIB;
		break;

	case CHAP_STDLIB:
		g_Hdll = LoadLibrary(L"chap_stdlib.dll");
		if (g_Hdll == nullptr)
		{
			std::cout << "动态库加载失败" << std::endl;
			return false;
		}
		pfunc = (pVV)(GetProcAddress(g_Hdll, "getChap"));
		if (pfunc == nullptr)
		{
			std::cout << "动态库函数获取失败" << std::endl;
			return false;
		}
		this->pc = reinterpret_cast<chap_stdlib*>((*pfunc)());
		this->currentChap = CHAP_ENUM::CHAP_STDLIB;
		break;

	case CHAP_EXCEPTION:
		g_Hdll = LoadLibrary(L"chap_errorHandling.dll");
		if (g_Hdll == nullptr)
		{
			std::cout << "动态库加载失败" << std::endl;
			return false;
		}
		pfunc = (pVV)(GetProcAddress(g_Hdll, "getChap"));
		if (pfunc == nullptr)
		{
			std::cout << "动态库函数获取失败" << std::endl;
			return false;
		}
		this->pc = reinterpret_cast<chap_errorHandling*>((*pfunc)());
		this->currentChap = CHAP_ENUM::CHAP_EXCEPTION;
		break;

	case CHAP_DSA:
		g_Hdll = LoadLibrary(L"chap_DSA.dll");
		if (g_Hdll == nullptr)
		{
			std::cout << "动态库加载失败" << std::endl;
			return false;
		}
		pfunc = (pVV)(GetProcAddress(g_Hdll, "getChap"));
		if (pfunc == nullptr)
		{
			std::cout << "动态库函数获取失败" << std::endl;
			return false;
		}
		this->pc = reinterpret_cast<chap_DSA*>((*pfunc)());
		this->currentChap = CHAP_ENUM::CHAP_DSA;
		break;

	default:
		return false;
	}
	return true;
}


bool reader::selectMol(const int molEnum)
{
	if (this->pc == nullptr) 
		return true; 

	return this->pc->selectModule(molEnum);
}


void reader::runTest(const unsigned testID)
{
	this->pc->pm->run(testID);
}


bool reader::isNullChap() const
{
	if (this->pc == nullptr) 
		return true; 
	else 
		return false; 
}


bool reader::isNullModule() const 
{
	if (isNullChap()) 
		return true; 

	if (this->pc->isNullModule()) 
		return true; 
	else  
		false;  
}