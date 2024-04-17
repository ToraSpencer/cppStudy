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
		std::cout << p.name << ", male, age: " << p.age << ", career: " << p.job << std::endl;
	else
		std::cout << p.name << ", female, age: " << p.age << ", career: " << p.job << std::endl;
}


 
// test0: std::map, std::unordered_map���ó�Ա��
void STL_map_module::test0(void)
{
	std::cout << "\n\n\n\n" << std::endl;
	std::cout << "test0: std::map, std::unordered_map���ó�Ա" << std::endl;

	std::map<int, std::string>  mis;
	std::map<int, std::string>::iterator iter1;
	pairPrinter pp; 

	//	1. insert()���������ֵ�ԣ�
	mis.insert(std::make_pair(6, "xiaohong"));			// ����pair����
	mis.insert(std::make_pair(5,"ali"));


	//	2.operator[]()���������������Ӧֵ�����ã�ע���������������ڣ������ֵ������ɸü�ֵ�ԣ���Ĭ��constructor������ֵ����
	debugDisp("\noperator[](): ");
	debugDisp("mis[5] == ", mis[5]);

	mis[5] = "bli";
	debugDisp("mis[5] == ", mis[5]);
	debugDisp("mis.size() == ", mis.size());

	//			�������������ڣ������ֵ������ɸü�ֵ�ԣ���Ĭ��constructor������ֵ����
	debugDisp("mis[1] == ", mis[1]);
	debugDisp("mis.size() == ", mis.size());
	debugDisp("\n");


	//	3. erase()������������������ɾ����Ӧ�ļ�ֵ�ԣ�
	/*
		ɾ��������ָ��ļ�ֵ�ԣ�
				iterator erase( const_iterator pos ); 

		ɾ������������ָ����Χ�ڵļ�ֵ�ԣ�
				iterator erase( iterator first, iterator last ); 
				iterator erase( const_iterator first, const_iterator last ); 

		ɾ���������Ӧ�ļ�ֵ�ԣ�����ɾ�����ļ�ֵ��������
				size_type erase( const Key& key );
	*/
	debugDisp("\nerase()����: ");
	debugDisp("mis.erase(1) == ", mis.erase(1));
	for_each(mis.begin(), mis.end(), pp);
	debugDisp("\n");


	//	4. find()������������ļ������ض�Ӧ�ĵ����������û���ҵ��򷵻�β���������
	debugDisp("\nfind()����: ");
	iter1 = mis.find(5);			
	debugDisp("iter1->first == ", iter1->first);
	debugDisp("iter1->second == ", iter1->second);
	mis.erase(iter1);										// erase()�������������ɾ��Ԫ��
	
	for_each(mis.begin(), mis.end(), pp);
	std::cout << std::endl;
}


// test2: Ĭ��/�Զ���Ƚ���
struct edgeComparator			// �ϸ�����(strict weak ordering)�Ƚ���
{
public:
	bool operator()(const std::pair<int, int>& edge1, const std::pair<int, int>& edge2) const
	{
		if (edge2.first < edge1.first)
			return true;
		else if (edge2.first > edge1.first)
			return false;
		else
		{
			if (edge2.second < edge1.second)
				return true;
			else
				return false;
		}
	}
};


void STL_map_module::test1() 
{
	debugDisp("\n\n\n\n");
	debugDisp("Ĭ��/�Զ���Ƚ�����");

	// 1. Ĭ�ϱȽ�����
	std::set<float> set1;
	std::map<int, float> map1;
	std::multimap<int, char> mmap1;
	set1.insert(3);
	set1.insert(2);
	set1.insert(5);
	set1.insert(99);
	set1.insert(-1);								// std::setĬ�������°�Ԫ�ش�С��������
	map1.insert({ 3, -1.5 });
	map1.insert({ 1, 3.5 });
	map1.insert({ -1, 1.6 });
	map1.insert({ 88, 9.1 });
	map1.insert({ 6, -7.5 });				// std::mapĬ�������°�����С�������У� 
	mmap1.insert({ 3, 'b' });
	mmap1.insert({ 1, 'z' });
	mmap1.insert({ -1, 'y' });
	mmap1.insert({ 88, 'z' });
	mmap1.insert({ 3, 'a' });
	mmap1.insert({ 3, 'b' });				// std::multimap��Ĭ�������°�����С�������У�ͬ����pair����ԭʼ����������У�

	debugDisp("set1: ");
	traverseSTL(set1, disp<int>());
	debugDisp("map1: ");
	traverseSTLmap(map1, dispPair<std::pair<int, float>>());
	debugDisp("mmap1:");
	traverseSTLmap(mmap1, dispPair<std::pair<int, char>>());

	// 2. �����ǻ������͵�set��map����Ҫ�����Զ���Ƚ�������
	std::set<std::pair<int, int>, edgeComparator> edgeSet1;
	auto retPair1 = edgeSet1.insert({ 1,  2 });
	retPair1 = edgeSet1.insert({ 2, 3 });
	retPair1 = edgeSet1.insert({ -1, 0 });
	retPair1 = edgeSet1.insert({ -2, -1 });
	retPair1 = edgeSet1.insert({ 1, 3 });
	retPair1 = edgeSet1.insert({ 1, 2 });
	debugDisp("edgeSet1: ");
	traverseSTL(edgeSet1, dispPair<std::pair<int, int>>());

	// 3. ��Ϊ�Ƚ�����lambda: 
	auto edgeComLambda = [](const std::pair<int, int>& edge1, \
		const std::pair<int, int>& edge2) ->bool
	{
		if (edge2.first < edge1.first)
			return true;
		else if (edge2.first > edge1.first)
			return false;
		else
		{
			if (edge2.second < edge1.second)
				return true;
			else
				return false;
		}
	};
	std::set<std::pair<int, int>, decltype(edgeComLambda)> edgeSet2;			// ģ���������������
	auto retPair2 = edgeSet2.insert({ 1,  2 });
	retPair2 = edgeSet2.insert({ 2, 3 });
	retPair2 = edgeSet2.insert({ -1, 0 });
	retPair2 = edgeSet2.insert({ -2, -1 });
	retPair2 = edgeSet2.insert({ 1, 3 });
	retPair2 = edgeSet2.insert({ 1, 2 });
	debugDisp("edgeSet2: ");
	traverseSTL(edgeSet2, dispPair<std::pair<int, int>>());

	debugDisp("test1 finished.");
}


// test2: multimap�Ļ���ʹ�÷�����API
void STL_map_module::test2(void)
{
	// multimap�п����м���ͬ��Ԫ�أ���ͬ����Ԫ�ػ����ڴ洢��
	// multimapû���±����㣬����api��std::map���ơ�
	std::cout << "\n\n\n\n" << std::endl;
	std::cout << "multimap�Ļ���ʹ�÷�����api" << std::endl;

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


// test3: Ӧ�ó�������vector��multimapʵ�ֵı������������������Ϣ��
void STL_map_module::test3(void)
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


void STL_map_module::test4(void)
{}


void STL_map_module::test5(void)
{}


void STL_map_module::test6(void) 
{}