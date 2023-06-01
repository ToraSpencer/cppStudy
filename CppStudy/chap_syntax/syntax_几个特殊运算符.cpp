#include <iostream>
#include <string>
#include <typeinfo>

#include <cstdio>

#include "syntax_�������������.h" 


#define EPS 1e-10					//����ǳ�С��һ����EPSilon�������������������ֵʱ����Ϊ0
#define PI 3.14159


// sizeof()�����������һ�������������ռ���ڴ��ֽ�����	
/*
    sizeof(����);           ��sizeof(num)
    sizeof(������);         ��sizeof(int)
			 
*/




// ��Ŀ�������b ? x : y;   
/*
    ��������b����bֵΪtrue���������ʽx�������ؽ����
        ��bֵΪfalse���������ʽy�������ؼ�������
			 
*/

virtualModule* syntax_operator_module::getInstance()		// �̲߳���ȫ�ĵ���ģʽ
{
	if (nullptr != p_moduleIns)
	{
		delete p_moduleIns;
	}
	p_moduleIns = new syntax_operator_module;
	return p_moduleIns;
}

 
// test0: sizeof()�����
void syntax_operator_module::test0(void)
{
    std::cout << "\n\n\n\n" << std::endl;
	std::cout << "test0: sizeof()�����" << std::endl;

    int arri[5];
    std::cout << "\t����arriռ�ڴ棺sizeof(arri) == " << sizeof(arri) << std::endl;
    std::cout << "\t����arri��Ԫ������sizeof(arri)/sizeof(int) == " << sizeof(arri)/sizeof(int) << std::endl;

    // ����ָ��ռ�ڴ涼��һ���ģ��ɲ���ϵͳλ��������64λϵͳ��ָ��ռ8�ֽڣ��������ֳ���
    int* pi;
    double* pd;
    void* pv;
    std::cout << "\t" << sizeof(pi) << std::endl;
    std::cout << "\t" << sizeof(pd) << std::endl;
    std::cout << "\t" << sizeof(pv) << std::endl;

}



// test1: ��Ŀ�����
void syntax_operator_module::test1(void)
{
    std::cout << "\n\n\n\n" << std::endl;
	std::cout << "test1: ��Ŀ�����" << std::endl;


    // Ӧ�����ӡ��������ж�������������������ż����
    int inputValid = 0;
    int num;
    std::string str;

    std::cout << "������һ��������" << std::endl;
    while(0 == inputValid)
    {
        setbuf(stdin, NULL);
        inputValid = scanf("%d", &num);
        
        if(0 == inputValid)
        {
            std::cout << "���벻�Ϸ������������롣" << std::endl;
            setbuf(stdin, NULL);
        }
    }
    str = (num%2 == 0) ? "ż��": "����";
    std::cout << "�����������" << str << std::endl;
     
}



void syntax_operator_module::test2(void)
{


}


void syntax_operator_module::test3(void)
{


}


void syntax_operator_module::test4(void)
{


}


void syntax_operator_module::test5(void)
{


}


void syntax_operator_module::test6(void)
{


}