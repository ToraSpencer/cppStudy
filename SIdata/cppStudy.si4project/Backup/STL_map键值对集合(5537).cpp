#include <iostream>
#include <set>
#include <map>
#include <string>
#include <vector>
#include <typeinfo>
#include <algorithm>
#include <utility>  				// �ṩpair����

#include <cstdio>
#include "STL_map��ֵ�Լ���.h"

 
#define EPS 1e-10					// ����ǳ�С��һ����EPSilon�������������������ֵʱ����Ϊ0
#define PI 3.14159


 


// ֪ʶ��
/*
	 1. std::map, multimap, unordered_map, unordered_multimap��������
					1. Ԫ����pair����
					2. ������Ԫ�صļ���ͬ������multi-��ͷ��std::map��set����
					3. ������ǿ�ͷΪunorderedָ����������������˳�򱣴��ڲ���Ԫ�ء�

		2. std::map�ļ��ֹ��캯����ʽ


		3. std::map��set����ĵײ�ԭ����ʹ�������"<"���Ƚ�Ԫ��


		4. ���������������unordered_map��unordered_set����ʹ�ù�ϣ��������֯Ԫ�ء�


		5. std::map�ĳ��÷���
					1. ��
									insert()
									
					2. ɾ
									erase()����3����
									
					3. ��		
									find(), count(), lower_bound(), upper_bound()

					4. �ģ����ʣ�		
									�±�����[]
				


*/


virtualModule* STL_map_module::getInstance()		// �̲߳���ȫ�ĵ���ģʽ
{
	if (nullptr != p_moduleIns)
	{
		delete p_moduleIns;
	}
	p_moduleIns = new STL_map_module;
	return p_moduleIns;
}

 

struct person
{
	std::string name;
	bool sex;
	int age;
	std::string job;
};


  
void dispPerson(person& p)
{
	if(p.age)
	{
		std::cout << p.name << ", male, age: " << p.age << ", career: " << p.job << std::endl;
	}
	else
	{
		std::cout << p.name << ", female, age: " << p.age << ", career: " << p.job << std::endl;
	}
	
	
}



 

 
// test0: std::map�Ļ���ʹ�÷�����API
void STL_map_module::test0(void)
{
	std::cout << "\n\n\n\n" << std::endl;
	std::cout << "test0: std::map�Ļ���ʹ�÷�����API" << std::endl;

	std::map<int, std::string>  mis;
	std::map<int, std::string>::iterator iter1;
	pairPrinter pp;


	// ��ɾ���
	std::cout << "\tmap����ɾ��ģ�" << std::endl;

	//			ʹ��insert������Ԫ��
	mis.insert(std::make_pair(6, "xiaohong"));			// ����pair����
	mis.insert(std::make_pair(5,"ali"));

	//			ʹ���±�����������ӡ��޸�Ԫ��
	mis[1] = "xiaoming";								// �±���������޸ü�ʱ�����ü����иü�ʱ�޸ĸü���						
	mis[33] = "laowang";
	mis[33] = "laoli";	
	for_each(mis.begin(), mis.end(), pp);
	std::cout << std::endl;

	//			erase()���������ɾ��Ԫ��
	mis.erase(1);				
	for_each(mis.begin(), mis.end(), pp);
	std::cout << std::endl;


	//			find()�������������Ԫ��
	iter1 = mis.find(33);
	mis.erase(iter1);				// erase()�������������ɾ��Ԫ��
	for_each(mis.begin(), mis.end(), pp);
	std::cout << std::endl;
}


// test1: multimap�Ļ���ʹ�÷�����API
void STL_map_module::test1(void)
{

	// multimap�п����м���ͬ��Ԫ�أ���ͬ����Ԫ�ػ����ڴ洢��
	// multimapû���±����㣬����api��std::map���ơ�
	std::cout << "\n\n\n\n" << std::endl;
	std::cout << "test1: multimap�Ļ���ʹ�÷�����api" << std::endl;

	std::multimap<std::string, int> mmss;
	pairPrinter pp;

	mmss.insert(std::make_pair("xiaohong", 16));
	mmss.insert(std::make_pair("xiaoming", 17));
	mmss.insert(std::make_pair("xiaohong", 8));
	mmss.insert(std::make_pair("xiaohong", 2));
	mmss.insert(std::make_pair("laowang", 1));
	for_each(mmss.begin(), mmss.end(), pp);
	std::cout << std::endl;


	// ���Ҳ���ӡ��ĳһ����ȫ��Ԫ�أ�
	std::cout << "\t���ҳ�multimap��ĳ��������Ԫ��" << std::endl;
	int num = mmss.count("xiaohong");							// multimap::count()������������ĳ��Ԫ�صĸ�����
	std::multimap<std::string, int>::iterator iter1 = mmss.find("xiaohong");	// ���ص�һ����Ϊxiaohong��Ԫ�صĵ�����
	for(int i = 1; i<=num; i++)
	{
		std::cout << "\t";
		//pp(*(iter1++));
	}
	std::cout << std::endl;

}


// test2: Ӧ�ó�������vector��multimapʵ�ֵı������������������Ϣ��
void STL_map_module::test2(void)
{
	std::cout << "\n\n\n\n" << std::endl;
	std::cout << "test2: std::map/multimapӦ�ó��������������������������Ϣ��" << std::endl;

	person p1 = { "xiaoming", true,  10, "student" };
	person p2 = { "xiaohong", false,  11, "doctor" };
	person p3 = { "xiaolan", true,  12, "teacher" };
	person p4 = { "xiaohuang", true,  10, "teacher" };
	person p5 = { "laowang", true,  13, "worker" };
	person p6 = { "laoli", false,  10, "famer" };
	person p7 = { "xiaoming", false,  10, "famer" };


	// ���ݴ���������
	std::vector<person> vp;
	vp.push_back(p1);
	vp.push_back(p2);
	vp.push_back(p3);
	vp.push_back(p4);
	vp.push_back(p5);
	vp.push_back(p6);
	vp.push_back(p7);


	// ������������������multimap:
	std::multimap<std::string, int> m_name;			// ����������Ԫ�ؼ��Ǹ���������ֵ�Ǹ�����vp�����е��±ꡣ
	std::multimap<int, int> m_age;					// ����������
	for(int i=0; i<=6; i++)
	{
		m_name.insert(std::make_pair(vp[i].name, i));
		m_age.insert(std::make_pair(vp[i].age, i));
	}


	// ��������ӡ���ݣ�
	std::multimap<std::string, int>::iterator iter1;
	std::multimap<int, int>::iterator iter2;
	int num;
	
	//		�������֡�xiaoming��
	num = m_name.count("xiaoming");
	iter1 = m_name.find("xiaoming");
	for(int i = 1; i<= num; i++)
	{
		std::cout << "\t";
		dispPerson(vp[(*iter1).second]);
		iter1++;
	}
	std::cout << std::endl;

	//		��������10
	num = m_age.count(10);
	iter2 = m_age.find(10);
	for(int i = 1; i<= num; i++)
	{
		std::cout << "\t";
		dispPerson(vp[(*iter2).second]);
		iter2++;
	}
	std::cout << std::endl;


}


void STL_map_module::test3(void)
{}


void STL_map_module::test4(void)
{}


void STL_map_module::test5(void)
{}


void STL_map_module::test6(void) 
{}