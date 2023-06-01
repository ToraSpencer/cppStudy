#include <string>
#include<iostream>

#include <map>
#include <cstdio>

#include "designPattern_����ģʽ.h"


/*
	�͹���ģʽ������
			�������ڣ��ڲ��Ե����ߺͲ���֮�����һ�����㡪�����Խӿ���strategy��
			���Եĵ�������ͳһ����ʽ�������Ե�����ʹ��strategyָ�룬��ָ���Ƕ�̬�ģ�����Ҫ��ָ������ĸ�����ʵ����
			���Ա������ǲ��Թ�����Ķ��󣬼̳���strategy�ӿڣ�������㷨���붼��װ���෽���С�
			�������Ժܷ������չ�����µĲ�����Ҫ����Ļ���ֻ��Ҫ�̳�strategy�ӿ�����һ������Ϳ����ˡ�

*/


namespace STRATEGY_PATTERN_AS1
{
	enum language { english, chinese };

	// չʾ��ӭ��Ļ�������Խӿ�
	class welcomeScreen				
	{
	public:
		virtual void welcome() = 0;			// ����Ĳ�ͬ�Ĳ��Դ��룬��д�ڸ÷�����ʵ���С�
	};

	// չʾӢ�Ļ�ӭ��Ļ�������Թ�����
	class welcomeEng : public welcomeScreen				
	{
		virtual void welcome() override
		{
			std::cout << "nothing is impossible!" << std::endl;
		}
	};

	// չʾ���Ļ�ӭ��Ļ�������Թ�����
	class welcomeChi : public welcomeScreen				
	{
		virtual void welcome() override
		{
			std::cout << "����" << std::endl;
		}
	};


	class television		
	{
	private:
		welcomeScreen* pw;
		television() = default;					// �����޲ι��죬ʵ����һ��telivision��ʱ�����ָ�����ԡ�

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


virtualModule* designPattern_strategy_module::getInstance()		// �̲߳���ȫ�ĵ���ģʽ
{
	if (nullptr != p_moduleIns)
		delete p_moduleIns;

	p_moduleIns = new designPattern_strategy_module;
	return p_moduleIns;
}



// test1�����Բ���ģʽӦ�ó���1
void designPattern_strategy_module::test0()
{
	using namespace STRATEGY_PATTERN_AS1;

	welcomeScreen* pws = nullptr;
	pws = new welcomeChi();

	television tl(pws);					// telivision�ǲ��Ե����ߡ�
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