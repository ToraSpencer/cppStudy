#include <string>
#include <iostream>
#include <fstream>
#include <vector>						//vector��ģ����ͷ�ļ�<vector>��
#include <list>
#include <deque>
#include <cstdio>

#include "STL_��������.h"


// ֪ʶ��
/*
				1. vector�ײ��ǿɶ�̬����������˳���֧�������ȡ�����ǲ���ɾ����ʱ��
				
				2. vector��������ʱ���·����ڴ棬���е�����ʧЧ
				
				3. vectorִ�в������ʱ����û�з������������ڴ����·��䣬�����Ԫ�غ�ĵ�����ʧЧ��ǰ��ĵ�������Ȼ��Ч��
				
				4. ��C++11��STL����������ʹ���б��ʼ����

				5.  ������������ɾ���
							����
									push_back()			
									insert()			����������λ������Ԫ�أ�����һ���Բ�����Ԫ�ء�
									emplace(), 
									emplace_back()
									ע�⣺forwad_list��֧��push_back()��emplace_back()		

							ɾ��
									erase() 
									clear() 
							
							�飺
									��������û��find(), count()���������������У�����ʹ��STL�㷨���е�find����ʵ�֡�

							�ģ�
									swap() 
									assign()
									resize()			// ������Ԫ�����������ֽ�����

									
									

				6. �ײ�ṹ
							vector��������			˳���
							list��������			˫������
							forward_list��������	��������
							deque����				˫�˶���
							

*/




virtualModule* STL_linear_container_module::getInstance()		// �̲߳���ȫ�ĵ���ģʽ
{
	if (nullptr != p_moduleIns)
	{
		delete p_moduleIns;
	}
	p_moduleIns = new STL_linear_container_module;
	return p_moduleIns;
}




// test0():�������캯������ʼ��������
void STL_linear_container_module::test0(void)
{
	std::vector<int> vi1;												// ����һ����������


	std::cout << "\n\n\n\n" << std::endl;
	std::cout << "test0(): �������캯������ʼ��������" << std::endl << std::endl;

	std::cout << "\tvi1.empty == " << vi1.empty() << std::endl;
	std::cout << std::endl;


	// 1. ָ��������������
	std::vector<int> vi2(3);
	std::cout << "vi2.capacity() ==  " << vi2.capacity() << std::endl;
	traverseSTL(vi2, disp<int>);
	std::cout << std::endl;

	vi2.push_back(1);
	vi2.push_back(2);
	vi2.push_back(3);
	vi2.push_back(4);

	// 	1.1 push_back��ȥ�ĸ�Ԫ��֮��vi2���Զ����ݣ�
	std::cout << "vi2.size() == " << vi2.size() << std::endl;
	traverseSTL(vi2, disp<int>);
	std::cout << std::endl << std::endl;


	// 2. ָ��������������Ԫ��ͳһ��ʼֵ��
	std::vector<int> vi3(3, 10); 		
	traverseSTL(vi3, disp<int>);
	std::cout << std::endl;

	// 3. ʹ�ó�ʼ���б��ʼ��vector������
	std::vector<int> vi4 = {1,2,3,4};										// ��������ʵ�������������ǵ�Ч�ġ�
	int arr[] = { 1, 2, 3 };


	// 4. ��������������������
	std::vector<int> vi5(arr, arr + 3);									
}



// test1(): ������������ɾ���
void STL_linear_container_module::test1(void)
{
	std::cout << "\n\n\ntest1():������������ɾ���" << std::endl << std::endl;

	// lambda����ִ�������жϵĺ�����
	auto badValue = [](const int& num) -> bool
	{
		if (num == 4)
		{
			return true;
		}
		else
		{
			return false;
		}
	};

	std::vector<int> vi1{ 1,2,3,4,5,4,6,7,8,9,4 };
	std::list<int> li1{ 1,2,3,4,5,4,6,7,8,9,4 };
	std::deque<int> di1{ 1,2,3,4,5,4,6,7,8,9,4 };

	// ������insert()��������Ԫ��
	auto iter1 = vi1.begin();
	iter1++;
	iter1 = vi1.insert(iter1, 999);						// �ڵ�ǰ������ָ���Ԫ��֮ǰ������Ԫ�أ����ɹ����򷵻ز�����Ԫ�صĵ�������
	traverseSTL(vi1, disp<int>);
	std::cout << "*iter1 == " << *iter1 << std::endl;
	
	//		�������俽����˳���STL��������vector��
	int arri[] = { 1,2,3,4,5,6,77,88,999 };
	std::vector<int> vi2(9);
	memcpy(&vi2[0], &arri[0], sizeof(int) * 9);
	traverseSTL(vi2, disp<decltype(vi1[0])>);

	// ɾ��Ԫ�أ�

	//		earase()����1����ɾ��������ָ����Ԫ��
	vi1.erase(vi1.begin());
	traverseSTL(vi1, disp<decltype(vi1[0])>);

	//		erase()����2����ɾ��һ�Ե�����ָ����Χ��Ԫ��
	li1.erase(++li1.begin(), --li1.end());	// list�ĵ�������˫�������������vector������������ʵ���������֧�ֳ����Ӽ�����,++���ԡ�
	traverseSTL(li1, disp<decltype(*li1.begin())>);

	//		erase()������remove_if()�ӿ���ϳ�����Ĳ���������ɾ��STL���������е�Ԫ��
	vi1.erase(remove_if(vi1.begin(), vi1.end(), badValue), vi1.end());
	traverseSTL(vi1, disp<decltype(vi1[0])>);

	//		erase()��������ֵ��Ӧ�á�������ֵ�Ǳ�ɾ��Ԫ����һ��Ԫ�صĵ�����
	for (std::deque<int>::iterator iter = di1.begin(); iter != di1.end();)
	{
		// ����ɾ��Ԫ�أ�������ɾ����ʱ���ӡ�ַ�����
		if (badValue(*iter))
		{
			std::cout << "ɾ����һ��Ԫ�ء�" << std::endl;
			iter = di1.erase(iter);		// ��ñ�ɾ��Ԫ����һ��Ԫ�صĵ�����
		}
		else
		{
			++iter;
		}
	}
	traverseSTL(di1, disp<decltype(*di1.begin())>);

}



// test2():vector��list�ĵ�����
void STL_linear_container_module::test2(void)
{
	std::cout << "\n\n\ntest3():vector�ĵ�����" << std::endl << std::endl;

	std::vector<int>vi;
	std::vector<int>::iterator iter_i;
	std::vector<int>::const_iterator citer_i;

	vi.push_back(1);
	vi.push_back(2);
	vi.push_back(3);
	vi.push_back(4);
	vi.push_back(5);
	vi.push_back(6);

	// 1. ʹ��const_iterator������vector������Ԫ�ء�
	std::cout << "use const_iterator to traverse all the items on the vector container:" << std::endl;
	for (citer_i = vi.begin(); citer_i != vi.end(); citer_i++)
	{
		std::cout << *citer_i << std::endl;
	}							//const_iteratorֻ�ܷ���Ԫ�أ��������޸�Ԫ�ء�
	std::cout << std::endl;


	// 2. ʹ��iterator���޸�vector�е�Ԫ�ء�
	std::cout << "use iterator to change the vector's item's value: " << std::endl;
	iter_i = vi.begin();								//������ָ���һ��Ԫ�ء�
	*iter_i = -1;
	std::cout << "vi[0] == " << *iter_i << std::endl;
	iter_i++;
	*iter_i = -2;
	std::cout << "vi[1] == " << *iter_i << std::endl;
	iter_i += 1;
	*iter_i = -3;
	std::cout << "vi[2] == " << *iter_i << std::endl;
	std::cout << std::endl;

	// 3. list�ĵ�����
	std::list<int> numlist{ 1,2,3,4,5,6,7,8,9 };

	//			3.1 std::list�ĵ�����ֻ֧��++��--����֧��һ���������ⳣ��λ��
	for (unsigned i = 0; i < 2; ++i)
	{
		numlist.erase(numlist.begin());
		numlist.erase(--numlist.end());
	}
	traverseSTL(numlist, disp<int>);

	//			3.2 std::list�ĵ�����ִ��erase()֮�������ʧЧ������ɾ��Ԫ����һ��Ԫ�صĵ�����
	numlist = std::list<int>{ 1,2,3,4,5,6,7,8,9 };
	auto iter1 = numlist.begin();
	iter1 = numlist.erase(iter1);
	std::cout << "*iter1 == " << *iter1 << std::endl;
	traverseSTL(numlist, disp<int>);

}



// test3(): ����ʹ��������������ķ����������ǲ�������Ԫ�صķ�������effective STL
void STL_linear_container_module::test3(void)
{
	// assign()������Χ�Եس�ʼ����������
	std::vector<int> vi1, vi2;
	vi1.assign(6, 999);				// ������999��ʼ��vi1����

	auto iter1 = vi1.begin();
	auto iter2 = vi1.end();
	iter1 += 3;
	vi2.assign(iter1, iter2);		// �õ�����iter1,iter2ָʾ��vi2�е������ʼ��vi1;

	traverseSTL(vi1, disp<decltype(vi1[0])>);
	traverseSTL(vi2, disp<decltype(vi2[0])>);
 
}




// test4()����vector������ʧЧ����
void STL_linear_container_module::test4(void)
{
	// vector���ڴ����·���Ļ������е���������ʧЧ��

	std::vector<int> v1 = {1,2,3};		// ��ʼʱv1����Ϊ3������ʹ��v1.capacity()�鿴��
	auto iter1 = v1.begin();
	v1.push_back(4);							// ��ʱv1���������ı䣬�ڴ����·��䣬���е�����ʧЧ��
	std::cout << *iter1 << std::endl;			// ��ʱ��������������Ϊ�������Ѿ�ʧЧ��

}




// test5()����Ԫ�ط������������еĿ�������
void STL_linear_container_module::test5(void)
{
	// ָ�롢����Ϊ��ָ�������󱻴���vectorʱ����������ǳ����
	int num1 = 999;
	int num2 = 888;
	int num3 = 777;
	int* p1 = &num1;
	int* p2 = &num2;
	int* p3 = &num3;

	std::vector<int*> vec;
	vec.push_back(p1);
	vec.push_back(p2);
	vec.push_back(p3);

	for (const auto& elem : vec)
	{
		std::cout << *elem << ", ";
	}
	std::cout << std::endl;

	*p1 = 111;
	*p2 = 222;
	*p3 = 333;

	for (const auto& elem : vec)
	{
		std::cout << *elem << ", ";
	}
	std::cout << std::endl;

}




// test6()����Ӧ�ó���
void STL_linear_container_module::test6(void)
{
	// Ӧ�ó�����������string����Ȼ��ͨ���ö���������Ӧ���ļ������
	//		���������string����ϣ�����ļ���������Ӻ�׺"_x", "_y"����ʾx��y������������ݡ�
	std::string str = "data.dat";


	// �顪��find()������������������û��find����
	auto iter = find(str.begin(), str.end(), 'x');
	if (iter == str.end())
	{
		std::cout << "error" << std::endl;
	}
	auto dis = distance(str.begin(), iter);


	// ������insert()������������λ�ò��룬���ҿ���һ���Բ�����Ԫ��
	/*
		basic_string& insert( size_type index,
								const CharT* s
								);
	*/
	str.insert(dis, "_x");
	std::cout << str << std::endl;
	std::fstream file(str, std::ios::out);
	file.close();

}

