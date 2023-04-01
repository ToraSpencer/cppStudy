#include "dynamicLib1.h"

int funci()
{
	return 999;
}


void dllDisp(void)
{
	std::cout << "�����˶�̬��dynamicLib1�е�MYDLL::disp()����" << std::endl;
}


DLL_API int addNum(const int a, const int b)
{
	return (a+b);
}


DLL_API int addNum(const int a, const int b, const int c)
{
	return (a+b+c);
}


template <typename T>
void dispArg(const T arg)
{
	std::cout << arg << std::endl;
}


void MYDLL::disp(void)
{
	std::cout << "�����˶�̬��dynamicLib1�е�MYDLL::disp()����" << std::endl;
}

void MYDLL::printCurrentPath(void)
{
	TCHAR path[MAX_PATH + 1];
	GetModuleFileName(nullptr, path, MAX_PATH);
	std::wcout.imbue(std::locale(std::locale(), "", LC_CTYPE));
	std::wcout << path << std::endl;
}


double MYDLL::calculator::Add(double a, double b)

{
	std::cout << "�����˶�̬��dynamicLib1�е�MYDLL::add����" << std::endl;
	return a + b;

}



double MYDLL::calculator::Subtract(double a, double b)
{
	std::cout << "�����˶�̬��dynamicLib1�е�MYDLL::calculator::Subtract����" << std::endl;
	return a - b;

}



double MYDLL::calculator::Multiply(double a, double b)
{
	std::cout << "�����˶�̬��dynamicLib1�е�MYDLL::calculator::Multiply����" << std::endl;
	return a * b;

}



double MYDLL::calculator::Divide(double a, double b)
{
	std::cout << "�����˶�̬��dynamicLib1�е�MYDLL::calculator::Divide����" << std::endl;
	return a / b;
}




