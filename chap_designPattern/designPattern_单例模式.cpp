#include <string>
#include<iostream>

#include <cstdio>
#include "designPattern_单例模式.h"

 


// 单例模式
/*
	应用场景：
	操作系统中的任务管理器就应该是单例的，不能允许有多个任务管理器（task manager）实例。
	还有其他的某些窗口也应该是单例的，比如文档编辑器的工具箱，颜色设置窗口等等。

*/



// 简单的线程不安全的单例模式。
namespace SIMPLE_SINGLETON		
{
	class taskManager
	{
	private:
		static taskManager* tm_instance;				// 唯一实例，数据实体分配在堆上。
		taskManager() = default;								// 构造函数都设为私有的。
		taskManager(const taskManager&) {}				// 如果不写的话，则会生成public的默认拷贝构造函数，外部可以进行拷贝构造。
		~taskManager() = default;							// 同上。

	public:
		static taskManager* getInstance()
		{
			if (nullptr == tm_instance)
			{
				tm_instance = new taskManager;
				std::cout << "生成了一个任务管理器实例。" << std::endl;
			}
			else
				std::cout << "已有任务管理器实例，返回其指针。" << std::endl;
			return tm_instance;
		}
	};
	taskManager* taskManager::tm_instance = nullptr;		// 初始化为空指针。
}



// meyer's singleton——一种简洁优美的线程安全的单例模式
namespace MEYERS_SINGLETON				
{
	class taskManager
	{
	private:
		taskManager() = default;
		taskManager(const taskManager&) {}
		~taskManager() = default;

	public:
		static taskManager& getInstance()		// 注意返回的是引用
		{
			static taskManager tm_instance;		// 函数内的static变量——函数第一次调用时创建该变量，出函数栈后变量也不释放，
												//		重复调用函数不会重复创建对象。且函数内的static变量是线程安全的。
			return tm_instance;
		}
	};
}



virtualModule* designPattern_singleton_module::getInstance()		// 线程不安全的单例模式
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