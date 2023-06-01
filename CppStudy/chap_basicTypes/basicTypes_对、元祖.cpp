#include <cstdio>
#include <cstring>
#include <cstdio>

#include <utility>
#include <string>
#include <iostream>
#include <vector>						//vector类模板在头文件<vector>中
#include <algorithm>
#include <iterator>




#include "basicTypes_对、元祖.h"


// pair————二元组结构体
/*
定义于头文件<utility>
 



*/


virtualModule* basicTypes_pair_tuple_module::getInstance()		// 线程不安全的单例模式
{
	if (nullptr != p_moduleIns)
	{
		delete p_moduleIns;
	}
	p_moduleIns = new basicTypes_pair_tuple_module;
	return p_moduleIns;
}



void basicTypes_pair_tuple_module::test0(void)
{

}


void basicTypes_pair_tuple_module::test1(void) 
{

}



void basicTypes_pair_tuple_module::test2(void)
{

}




void basicTypes_pair_tuple_module::test3(void)
{

}




void basicTypes_pair_tuple_module::test4(void)
{

}




void basicTypes_pair_tuple_module::test5(void)
{

}




void basicTypes_pair_tuple_module::test6(void)
{

}

