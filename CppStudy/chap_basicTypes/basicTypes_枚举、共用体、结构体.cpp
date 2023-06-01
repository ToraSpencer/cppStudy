#include <iostream>
#include <string>
#include <typeinfo>

#include <memory>
#include <vector>
#include <cstddef>
#include <cstdio>
#include <new>


#include "basicTypes_ö�١������塢�ṹ��.h"
 

#define EPS 1e-10					//����ǳ�С��һ����EPSilon�������������������ֵʱ����Ϊ0
#define PI 3.14159



// ֪ʶ��
/*
			1. union�����塪������������г�Առ��ͬһ���ڴ棬�޸�һ����Ա��Ӱ���������г�Ա��
			
			2. ö���ص㣺
							Ԫ��ֵ����������ֵ��
							
			3. �ṹ���е��ڴ�������⣬���UP_�ڴ�����½ڡ�




*/


virtualModule* basicTypes_enum_union_struct_module::getInstance()		// �̲߳���ȫ�ĵ���ģʽ
{
	if (nullptr != p_moduleIns)
	{
		delete p_moduleIns;
	}
	p_moduleIns = new basicTypes_enum_union_struct_module;
	return p_moduleIns;
}



namespace TEST_STRUCT
{
	struct person
	{
		std::string name;
		bool sex;
		unsigned age;
		std::string job;
	};


	struct controlWord				// ʹ����λ�ֶεĽṹ�壬����ÿ����Ա����һ���ֶΡ�
	{
		unsigned int word1 : 4;   	// 4bitΪword1��ֵ
		unsigned int : 4;        		// 4bitΪ�հ׵�ռλ
		bool word2 : 1;
		bool word3 : 1;
	};


	typedef struct
	{
		char a;
		short b;
		int c;
		long d;							// 32λϵͳ��long�Ĵ�С��4�ֽڣ�64λϵͳ����8�ֽڡ�
		char e;
		long long f;				// long long�Ĵ�С��8�ֽڡ�
	}stru;


	auto dispPerson = [](const TEST_STRUCT::person& p)
	{
		auto dispL = [](auto&& arg)			// arg��һ���������á�
		{
			std::cout << arg << std::endl;
		};

		//std::cout << p.name << std::endl;
		//std::cout << p.sex << std::endl;
		//std::cout << p.age << std::endl;
		//std::cout << p.job << std::endl;
		dispL(p.name);
		dispL(p.sex);
		return;
	};


}
 

namespace TEST_UNION 
{
	typedef union data
	{
		int numi;
		float numf;
		char ch;
	} unionData;
}



// test0: �ṹ��Ļ���ʹ�÷���
void basicTypes_enum_union_struct_module::test0(void)
{
	using namespace TEST_STRUCT;

	std::cout << "\n\n\n\n" << std::endl;
	std::cout << "test0: �ṹ��Ļ���ʹ�÷���" << std::endl;

	// �ṹ��ʵ����ʼ����
	//		ע��C�������ṹ��ʵ��ʱǰ��Ҫ��struct
	//				һ��C��ʹ��typedef   person{.....}person; �����ĸ�ʽ�����ṹ�壬Ȼ������ʵ����ʱ��Ͳ���дstruct��
	person p1 = {"xiaoming", true, 18, "doctor"};
	person p2 = {};						// ��ʱ���г�ԱֵΪ0


	dispPerson(p1);
	std::cout << std::endl;
	dispPerson(p2);
	std::cout << std::endl;


}



// test1��ö�����͵Ļ���ʹ��
void basicTypes_enum_union_struct_module::test1(void)
{
	// ����ö�����͵���ҪĿ���ǣ����ӳ���Ŀɶ��ԡ�
	// ö���������Ҳ����������ô�֮һ������������״̬��
	std::cout << "\n\n\n\n" << std::endl;
	std::cout << "test0: �ṹ��Ļ���ʹ�÷���" << std::endl;



	// ����ö������
	enum weekDay{SUN, MON, TUE, WED, THU, FRI, SAT};		// Ĭ�������£�ö�ٳ���ȡֵΪ0, 1, 2,...	
	enum color{RED, BLUE, GREEN = 1, YELLOW};						// ȡֵ���ظ�����ʱȡֵ�ֱ�Ϊ0,1,1,2		



	// ö�����͵���Ϣ
	std::cout << "typeid(SUN).name() " << typeid(SUN).name() << std::endl;	// ö�ٳ���SUN��������weekDay��weekDay������������
	std::cout << "sizeof(weekDay) == " << sizeof(weekDay) << std::endl;		// ��������ֵ��weekDay���͵Ĵ�С
	std::cout << "sizeof(SUN)" << sizeof(SUN) << std::endl;								// ö�����͵Ĵ�С��ȷ�����������������ֵ��С�����䣬������1,2,4�ֽڣ�һ�������͡�
	

	// �򵥵�Ӧ�þ�����
	int num;
	int inputValid = 0;
	std::string str;
	enum person{alice = 1, bob, cindy, david, eric, frank, grey};
	std::cout << "������Ҫ�鿴��ѡ�ֱ��" << std::endl;
	while(0 == inputValid)
	{
		setbuf(stdin, NULL);
		inputValid = scanf("%d", &num);

		if(0 == inputValid || num < 1 || num > 6)
		{
			std::cout << "���벻�Ϸ������������롣" << std::endl;
			setbuf(stdin, NULL);
		}
	}
	switch(num)
	{
		case 1:
			str = "alice";
			break;

		case 2:
			str = "bob";
			break;

		case 3:
			str = "cindy";
			break;

		case 4:
			str = "eric";
			break;

		case 5:
			str = "frank";
			break;

		case 6:
			str = "grey";
			break;

		default:
			break;
	}
	std::cout << num << "��ѡ����" << str << std::endl;
}



// test2: ������Ļ���ʹ��
void basicTypes_enum_union_struct_module::test2(void)
{
	using namespace TEST_UNION;
	std::cout << "\n\n\n\n" << std::endl;
	std::cout << " test2:  ������Ļ���ʹ��" << std::endl;

	unionData a;
	a.numi = 99;
	printf("sizeof(unionData) == %u\n", sizeof(unionData));
	printf("%d, %f, %c\n", a.numi, a.numf, a.ch);

	// union��һ����Ա�ĸ��ģ���Ӱ�쵽������Ա
	a.numi = 1;
	printf("%d, %f, %c\n", a.numi, a.numf, a.ch);

	a.numf = 3.14;
	printf("%d, %f, %c\n", a.numi, a.numf, a.ch);

	a.ch = 'a';
	printf("%d, %f, %c\n", a.numi, a.numf, a.ch);
	
 
}




// test3: �ṹ���е��ڴ����
void basicTypes_enum_union_struct_module::test3(void)
{
	using namespace TEST_STRUCT;

	std::cout << "\n\n\n\n" << std::endl;
	std::cout << " test3: �ṹ���е��ڴ����" << std::endl;

	stru s1 = {1,2,3,4,5,6};
	unsigned char* pc= NULL;
	pc = reinterpret_cast<unsigned char*>(&s1);

	// s1���ڴ�Ӧ���������ģ�
	/*
		char a; short b; int c; long d; char e; long long f;

		axbbcccc
		dddddddd
		exxxxxxx
		ffffffff
		����һ��ռ32�ֽڣ��ṹ��ʵ���ڲ������ݷֲ�����ʹ��һ��unsigned char*ָ�����鿴��֤��
	*/

	
	std::cout << "sizeof(s1) == " << sizeof(s1) << std::endl;
	std::cout << "�ṹ��ʵ��s1�ڲ����ݷֲ���" << std::endl;
	for(int i = 1; i<=32; i++)
	{
		printf("%d. 0x%x\n" , i, *pc);
		pc++;
		if(i>=32)
		{
			break;
		}
			
	}



}



void basicTypes_enum_union_struct_module::test4(void)
{}



void basicTypes_enum_union_struct_module::test5(void)
{}


void basicTypes_enum_union_struct_module::test6() 
{

}