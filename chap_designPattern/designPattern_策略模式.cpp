#include <string>
#include<iostream>

#include <map>
#include <cstdio>

#include "designPattern_策略模式.h"



/*
	和工厂模式的区别：
			核心在于：在策略调用者和策略之间加了一层抽象层——策略接口类strategy。
			策略的调用有了统一的形式——策略调用者使用strategy指针，该指针是多态的，具体要看指向的是哪个策略实例。
			策略本质上是策略功能类的对象，继承了strategy接口，具体的算法代码都封装在类方法中。这样可以很方便地扩展，有新的策略需要加入的话，只需要继承strategy接口新增一个子类就可以了。

*/

namespace STRATEGY_PATTERN_AS1
{
	enum language { english, chinese };

	class welcomeScreen				// 展示欢迎屏幕——策略接口
	{
	public:
		virtual void welcome() = 0;
	};

	class welcomeEng : public welcomeScreen				// 展示英文欢迎屏幕——策略功能类
	{
		virtual void welcome() override
		{
			std::cout << "nothing is impossible!" << std::endl;
		}

	};

	class welcomeChi : public welcomeScreen				// 展示中文欢迎屏幕——策略功能类
	{
		virtual void welcome() override
		{
			std::cout << "哈哈" << std::endl;
		}
	};

	class television		
	{
	private:
		welcomeScreen* pw;
		television() = default;					// 禁用无参构造，实例化一个telivision的时候必须指定语言。


	public:

		television(welcomeScreen* pw0) : pw(pw0) {}
		~television()
		{
			delete this->pw;
		}

		void showWelcome()
		{
			this->pw->welcome();
		}

		void setLanguage(language lan)
		{
			switch (lan)
			{
			case english:
				delete this->pw;
				this->pw = new welcomeEng();
				break;

			case chinese:
				delete this->pw;
				this->pw = new welcomeChi();
				break;


			};
		}

	};
}


virtualModule* designPattern_strategy_module::getInstance()		// 线程不安全的单例模式
{
	if (nullptr != p_moduleIns)
	{
		delete p_moduleIns;
	}
	p_moduleIns = new designPattern_strategy_module;
	return p_moduleIns;
}



// test1：测试策略模式应用场景1
void designPattern_strategy_module::test0()
{
	using namespace STRATEGY_PATTERN_AS1;

	welcomeScreen* pws = nullptr;
	pws = new welcomeChi();

	television tl(pws);			// telivision是策略调用者。
	tl.showWelcome();

	tl.setLanguage(english);
	tl.showWelcome();

}


void designPattern_strategy_module::test1() {}

void designPattern_strategy_module::test2() {}

void designPattern_strategy_module::test3() {}

void designPattern_strategy_module::test4() {}

void designPattern_strategy_module::test5() {}

void designPattern_strategy_module::test6() {}