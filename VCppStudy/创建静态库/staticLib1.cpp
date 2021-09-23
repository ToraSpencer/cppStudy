// 创建静态库
/*
		创建生成静态库的项目——创建visual c++ win32控制台应用程序，在应用程序类型中选择“静态库”
		生成的静态库默认名称为项目名称，要想修改可以进入项目属性→ 常规→ 目标文件名。


*/



#include <iostream>
#include "staticLib1.h"



int add(int a, int b)
{
	std::cout << "调用了静态库staticLib1中的add函数。" << std::endl;

	return a + b;
}
