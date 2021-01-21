#pragma once
#include "iostream"

// 前置声明
 




// 模块类的抽象基类
struct virtualModule
{
protected:
	virtual void test0() = 0;
	virtual void test1() = 0;
	virtual void test2() = 0;
	virtual void test3() = 0;
	virtual void test4() = 0;
	virtual void test5() = 0;
	virtual void test6() = 0;

public:
	static virtualModule* p_moduleIns;
	virtual ~virtualModule() = default;
	void run(unsigned testID);
};


// 章节类的抽象基类
struct virtualChap
{
public:
	virtualModule* pm;		// 当前查看的模块的指针，需要让caller可以访问，
							//	to be optimized: 其实更规范的作法是设计成友元，然后依然设置为protected成员
	static virtualChap* p_chapIns;
	virtual ~virtualChap();

	virtual void showModuleList() = 0;
	virtual void selectModule(const int molEnum) = 0;
	virtual void runTest(const unsigned testID);
};


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



