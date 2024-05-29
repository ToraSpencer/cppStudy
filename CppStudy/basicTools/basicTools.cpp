#include "basicTools.h"


// ��������inStream�������ո��Ʊ����ȡһ�ַ�
char GetChar(std::istream &inStream)
{
	char ch;
	while ((ch = (inStream).peek()) != EOF	// �ļ�������(peek()�������������н���1�ַ�,���ĵ�ǰλ�ò���)
		&& ((ch = (inStream).get()) == ' '		// �ո�( get()�������������н���1�ַ�,���ĵ�ǰλ�������1��λ��)
			|| ch == '\t'));
	return ch;
}


// ��mes����ͨ���쳣����
Error::Error(const char *mes)
{
	strcpy_s(message, mes);				// �����쳣��Ϣ
}


//  ��ʾ�쳣��Ϣ
void Error::Show()const
{
	std::cout << message << std::endl;			// ��ʾ�쳣��Ϣ	
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
	case 7:
		test7();
		break;
	default:
		break;
	}
}


virtualChap* virtualChap::p_chapIns = nullptr;


virtualChap::~virtualChap()
{
	// std::cout << "������chapϵ����ĵ���������" << std::endl;
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
		std::cout << "��ǰû��ȷ���κ�ģ��" << std::endl;
		return;
	}
	this->pm->run(testID);
}


bool virtualChap::isNullModule() const
{
	if (nullptr == this->pm) 
		return true;
	else 
		return false;
}


myString::myString(const myString& str)                                // ����������������ָ��ʽ��Ӧ���Լ�ʵ�ֿ������캯�������ظ�ֵ���������ʵ�����������ϵͳ����ǳ�����Ŀ������캯����
{
	const char* cStr = str.c_str();
	int size = strlen(cStr) + 1;

	char* tempStr = new char[size];
	strcpy_s(tempStr, size ,cStr);
	this->pc = tempStr;
}
 