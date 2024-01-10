#include "reader.h"


reader::reader()
{
	this->pc = nullptr;
	this->currentChap = CHAP_ENUM::NO_CHAP;
}


reader* reader::getInstance()		// ����chapter��moduleһ�������ڶ��ϣ�����ʹ��meyer's singleton
{
	static reader caller_instance;
	return &caller_instance;
}


reader::~reader()		noexcept	// Ҫ����ײ㿪ʼ��������deleteָ�롣
{
	if (this->pc != nullptr)
	{
		delete this->pc;
		this->pc = nullptr;
	}
}


// ��ӡ�½��б�
void reader::showChapList()
{
	std::cout << "************�½��б�***************" << std::endl;
	std::cout << "1. ��������" << std::endl;
	std::cout << "2. ���ģʽ" << std::endl;
	std::cout << "3. STL" << std::endl;
	std::cout << "4. �����﷨" << std::endl;
	std::cout << "5. ����" << std::endl;
	std::cout << "6. C++��׼��" << std::endl;
	std::cout << "7. ������" << std::endl;
	std::cout << "8. ���ݽṹ���㷨" << std::endl;
	std::cout << std::endl << std::endl;
}


// ��ӡģ���б�
void reader::showModuleList() 
{
	if (this->pc == nullptr) 
	{
		std::cout << "��ǰδָ���½ڡ�" << std::endl;
		return;
	}
	this->pc->showModuleList();
}


// ѡ���½ڣ�
bool reader::selectChap(const CHAP_ENUM ch)
{
	// ѡ���½ں͵�ǰ�½���ͬ�Ļ�����ʲô��������
	if (this->currentChap == ch && this->currentChap!=CHAP_ENUM::NO_CHAP)		 
		return true; 

	if (pc != nullptr && g_Hdll != nullptr)
	{
		delete this->pc;
		this->pc = nullptr;
		FreeLibrary(g_Hdll);
	}

	pVV pfunc = nullptr;
	switch (ch)
	{
	case CHAP_BASIC_TYPES:					// ���������½�
	{
		g_Hdll = LoadLibrary(L"chap_basicTypes.dll");
		if (g_Hdll == nullptr)
		{
			std::cout << "��̬�����ʧ��" << std::endl;
			return false;
		}
		pfunc = (pVV)(GetProcAddress(g_Hdll, "getChap"));
		if (pfunc == nullptr)
		{
			std::cout << "��̬�⺯����ȡʧ��" << std::endl;
			return false;
		}
		this->pc = reinterpret_cast<chap_designPattern*>((*pfunc)());
		this->currentChap = CHAP_ENUM::CHAP_BASIC_TYPES;
		break;
	}

	case CHAP_DESIGN_PATTERN:				// ���ģʽ�½�
		g_Hdll = LoadLibrary(L"chap_designPattern.dll");
		if (g_Hdll == nullptr)
		{
			std::cout << "��̬�����ʧ��" << std::endl;
			return false;
		}
		pfunc = (pVV)(GetProcAddress(g_Hdll, "getChap"));
		if (pfunc == nullptr)
		{
			std::cout << "��̬�⺯����ȡʧ��" << std::endl;
			return false;
		}
		this->pc = reinterpret_cast<chap_designPattern*>((*pfunc)());
		this->currentChap = CHAP_ENUM::CHAP_DESIGN_PATTERN;
		break;


	case CHAP_STL:
		g_Hdll = LoadLibrary(L"chap_STL.dll");
		if (g_Hdll == nullptr)
		{
			std::cout << "��̬�����ʧ��" << std::endl;
			return false;
		}
		pfunc = (pVV)(GetProcAddress(g_Hdll, "getChap"));
		if (pfunc == nullptr)
		{
			std::cout << "��̬�⺯����ȡʧ��" << std::endl;
			return false;
		}
		this->pc = reinterpret_cast<chap_STL*>((*pfunc)());
		this->currentChap = CHAP_ENUM::CHAP_STL;
		break;


	case CHAP_SYNTAX:
		g_Hdll = LoadLibrary(L"chap_syntax.dll");
		if (g_Hdll == nullptr)
		{
			std::cout << "��̬�����ʧ��" << std::endl;
			return false;
		}
		pfunc = (pVV)(GetProcAddress(g_Hdll, "getChap"));
		if (pfunc == nullptr)
		{
			std::cout << "��̬�⺯����ȡʧ��" << std::endl;
			return false;
		}
		this->pc = reinterpret_cast<chap_syntax*>((*pfunc)());
		this->currentChap = CHAP_ENUM::CHAP_SYNTAX;
		break;

	case CHAP_FUNCTION:
		g_Hdll = LoadLibrary(L"chap_function.dll");
		if (g_Hdll == nullptr)
		{
			std::cout << "��̬�����ʧ��" << std::endl;
			return false;
		}
		pfunc = (pVV)(GetProcAddress(g_Hdll, "getChap"));
		if (pfunc == nullptr)
		{
			std::cout << "��̬�⺯����ȡʧ��" << std::endl;
			return false;
		}
		this->pc = reinterpret_cast<chap_function*>((*pfunc)());
		this->currentChap = CHAP_ENUM::CHAP_STDLIB;
		break;

	case CHAP_STDLIB:
		g_Hdll = LoadLibrary(L"chap_stdlib.dll");
		if (g_Hdll == nullptr)
		{
			std::cout << "��̬�����ʧ��" << std::endl;
			return false;
		}
		pfunc = (pVV)(GetProcAddress(g_Hdll, "getChap"));
		if (pfunc == nullptr)
		{
			std::cout << "��̬�⺯����ȡʧ��" << std::endl;
			return false;
		}
		this->pc = reinterpret_cast<chap_stdlib*>((*pfunc)());
		this->currentChap = CHAP_ENUM::CHAP_STDLIB;
		break;

	case CHAP_EXCEPTION:
		g_Hdll = LoadLibrary(L"chap_errorHandling.dll");
		if (g_Hdll == nullptr)
		{
			std::cout << "��̬�����ʧ��" << std::endl;
			return false;
		}
		pfunc = (pVV)(GetProcAddress(g_Hdll, "getChap"));
		if (pfunc == nullptr)
		{
			std::cout << "��̬�⺯����ȡʧ��" << std::endl;
			return false;
		}
		this->pc = reinterpret_cast<chap_errorHandling*>((*pfunc)());
		this->currentChap = CHAP_ENUM::CHAP_EXCEPTION;
		break;

	case CHAP_DSA:
		g_Hdll = LoadLibrary(L"chap_DSA.dll");
		if (g_Hdll == nullptr)
		{
			std::cout << "��̬�����ʧ��" << std::endl;
			return false;
		}
		pfunc = (pVV)(GetProcAddress(g_Hdll, "getChap"));
		if (pfunc == nullptr)
		{
			std::cout << "��̬�⺯����ȡʧ��" << std::endl;
			return false;
		}
		this->pc = reinterpret_cast<chap_DSA*>((*pfunc)());
		this->currentChap = CHAP_ENUM::CHAP_DSA;
		break;

	default:
		return false;
	}
	return true;
}


bool reader::selectMol(const int molEnum)
{
	if (this->pc == nullptr) 
		return true; 

	return this->pc->selectModule(molEnum);
}


void reader::runTest(const unsigned testID)
{
	this->pc->pm->run(testID);
}


bool reader::isNullChap() const
{
	if (this->pc == nullptr) 
		return true; 
	else 
		return false; 
}


bool reader::isNullModule() const 
{
	if (isNullChap()) 
		return true; 

	if (this->pc->isNullModule()) 
		return true; 
	else  
		false;  
}