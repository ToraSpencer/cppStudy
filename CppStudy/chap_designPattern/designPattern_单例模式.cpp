#include <string>
#include<iostream>

#include <cstdio>
#include "designPattern_����ģʽ.h"

 


// ����ģʽ
/*
	Ӧ�ó�����
	����ϵͳ�е������������Ӧ���ǵ����ģ����������ж�������������task manager��ʵ����
	����������ĳЩ����ҲӦ���ǵ����ģ������ĵ��༭���Ĺ����䣬��ɫ���ô��ڵȵȡ�

*/



// �򵥵��̲߳���ȫ�ĵ���ģʽ��
namespace SIMPLE_SINGLETON		
{
	class taskManager
	{
	private:
		static taskManager* tm_instance;				// Ψһʵ��������ʵ������ڶ��ϡ�
		taskManager() = default;								// ���캯������Ϊ˽�еġ�
		taskManager(const taskManager&) {}				// �����д�Ļ����������public��Ĭ�Ͽ������캯�����ⲿ���Խ��п������졣
		~taskManager() = default;							// ͬ�ϡ�

	public:
		static taskManager* getInstance()
		{
			if (nullptr == tm_instance)
			{
				tm_instance = new taskManager;
				std::cout << "������һ�����������ʵ����" << std::endl;
			}
			else
				std::cout << "�������������ʵ����������ָ�롣" << std::endl;
			return tm_instance;
		}
	};
	taskManager* taskManager::tm_instance = nullptr;		// ��ʼ��Ϊ��ָ�롣
}



// meyer's singleton����һ�ּ���������̰߳�ȫ�ĵ���ģʽ
namespace MEYERS_SINGLETON				
{
	class taskManager
	{
	private:
		taskManager() = default;
		taskManager(const taskManager&) {}
		~taskManager() = default;

	public:
		static taskManager& getInstance()		// ע�ⷵ�ص�������
		{
			static taskManager tm_instance;		// �����ڵ�static��������������һ�ε���ʱ�����ñ�����������ջ�����Ҳ���ͷţ�
												//		�ظ����ú��������ظ����������Һ����ڵ�static�������̰߳�ȫ�ġ�
			return tm_instance;
		}
	};
}



virtualModule* designPattern_singleton_module::getInstance()		// �̲߳���ȫ�ĵ���ģʽ
{
	if (nullptr != p_moduleIns)
		delete p_moduleIns;

	p_moduleIns = new designPattern_singleton_module;
	return p_moduleIns;
}


void designPattern_singleton_module::test0() {}


void designPattern_singleton_module::test1() {}


void designPattern_singleton_module::test2() {}


void designPattern_singleton_module::test3() {}


void designPattern_singleton_module::test4() {}


void designPattern_singleton_module::test5() {}


void designPattern_singleton_module::test6() {}