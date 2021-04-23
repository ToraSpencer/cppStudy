#include "basicTools.h"


// 从输入流inStream中跳过空格及制表符获取一字符
char GetChar(std::istream &inStream)
{
	char ch;
	while ((ch = (inStream).peek()) != EOF	// 文件结束符(peek()函数从输入流中接受1字符,流的当前位置不变)
		&& ((ch = (inStream).get()) == ' '	// 空格( get()函数从输入流中接受1字符,流的当前位置向后移1个位置)
			|| ch == '\t'));
	return ch;
}




// 由mes构构通用异常对象
Error::Error(const char *mes)
{
	strcpy_s(message, mes);				// 复制异常信息
}


//  显示异常信息
void Error::Show()const
{
	std::cout << message << std::endl;			// 显示异常信息	
}


virtualModule* virtualModule::p_moduleIns = nullptr;


void virtualModule::run(unsigned testID)
{
	switch (testID)
	{
	case 0:
		test0();
		break;
	case 1:
		test1();
		break;
	case 2:
		test2();
		break;
	case 3:
		test3();
		break;
	case 4:
		test4();
		break;
	case 5:
		test5();
		break;
	case 6:
		test6();
		break;
	default:
		break;
	}
}


virtualChap* virtualChap::p_chapIns = nullptr;


virtualChap::~virtualChap()
{
	// std::cout << "调用了chap系列类的的析构函数" << std::endl;
	if (this->pm != nullptr)
	{
		delete this->pm;
		this->pm = nullptr;
	}
}


void virtualChap::runTest(const unsigned testID)
{
	if (nullptr == this->pm)
	{
		std::cout << "当前没有确定任何模块" << std::endl;
		return;
	}
	this->pm->run(testID);
}


bool virtualChap::isNullModule() const
{
	if (nullptr == this->pm) 
	{
		return true;
	}
	else 
	{
		return false;
	}
}


myString::myString(const myString& str)                                // ！！！类数据中有指针式，应该自己实现拷贝构造函数、重载赋值运算符，以实现深拷贝。否则系统分配浅拷贝的拷贝构造函数。
{
	const char* cStr = str.c_str();
	int size = strlen(cStr) + 1;

	char* tempStr = new char[size];
	strcpy_s(tempStr, size ,cStr);
	this->pc = tempStr;
}

 
