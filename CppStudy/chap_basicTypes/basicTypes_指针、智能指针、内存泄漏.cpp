#include <iostream>
#include <string>
#include <typeinfo>

#include <memory>
#include <vector>
#include <cstddef>
#include <new>

#include <cstdio>

#include "basicTypes_ָ�롢����ָ�롢�ڴ�й©.h"

#define EPS 1e-10					//����ǳ�С��һ����EPSilon�������������������ֵʱ����Ϊ0
#define PI 3.14159



// ֪ʶ��
/*
			1. ָ�������״̬������ָ�롢Ұָ�롢����ָ�루ָ��ʵ�����ݶ���
						��ָ��
									��ֵΪ0��ָ��
									��ָ���κ����ݶ���

						Ұָ��
									δ����ʼ����ָ�룬��ָ���ڴ汻�ͷ�֮���ָ�롣
									��ʱָ��ָ���λ��δ֪�������������
									һ��ʹ��Ұָ��Ļ������������ᱨ��




			2. ���ú�ָ�������
							(1). ���ñ��뱻��ʼ����ָ�벻��Ҫ��
							(2). ���ó�ʼ��֮�󲻿ɸı䣬ָ�����
							(3). �����ڿ����ã����ڿ�ָ�롣





			3. ��������ָ����ģ��shared_ptr, unique_ptr, weak_ptr�Ļ�����Ϣ(C++11)
							����ָ����Ҫ��������Ѷ��󣬶���ջ����û�б�Ҫʹ�ã��õĻ����ܻ��������쳣��
							
							shared_ptr
									�ɹ��������ָ�롣
									����5��shared_ptrָ��ָ��ͬһ�����ݶ���������ݶ�������ü���Ϊ5
									һ����������ü�������0ʱ���ᱻ���٣��ڴ���ͷš�
							
							unique����ptr
									���ɹ���ģ�Ψһ������ָ�롣
			



			4. shared_ptr��unique_ptr�ıȽ�
							(1) shared_ptr, unique_ptr��ͬ�Ľӿڣ�
											p.get()
														��������ָ������д洢��ָ�롣
											p			
														�������жϣ�������ָ��pָ��һ�������򷵻�true
											*p
											p->member
											p.swap(q)
														��������ָ�����p,q�д洢��ָ��
											p.reset(��ָͨ��)
														��������ָ��ָ��Ķ���
							

							(2) shared_ptr���еĽӿ�
											p.use_count()
														����һ��long, ������pָ��Ķ���ǰ�����ٸ�shared_ptrָ��ָ��
											p.unique()
														���p�Ƿ���unique�ģ�����ָ��Ķ���ǰֻ��p��һ��shared_ptrָ��ָ���򷵻�true

							(3) unique_ptr���еĽӿڣ�
											p.release()
														���ر�����������ָͨ�룬���ޱ���������򷵻�NULL

														

			5. �����Ĳ���Ұָ��Ĵ���
							����ָ�������ʱ��δ��ʼ����
							delete����free��һ��ָ���Ժ�δ����ָ������
							�����ڲ�������һ��ָ��ջ�ڴ��ָ�롣��Ϊջ�ڴ��ں���������ͻ��ͷš�


			6. �ڴ�й©��memory leak�� 
							��1�����ڴ�й© ��Heap leak����
											���ڴ�ָ���ǳ���������ͨ��malloc,realloc new�ȴӶ��з����һ���ڴ档����������ƵĴ������ⲿ���ڴ�û�б��ͷţ���ô�˺�����ڴ潫���ᱻʹ�ã��ͻ����Heap Leak. 	
							��2��ϵͳ��Դй¶��Resource Leak��.
											��Ҫָ����ʹ��ϵͳ�������Դ���� Bitmap,handle ,SOCKET��û��ʹ����Ӧ�ĺ����ͷŵ�������ϵͳ��Դ���˷ѣ����ؿɵ���ϵͳЧ�ܽ��ͣ�ϵͳ���в��ȶ��� 

							����һ����ַ�ʽ�ǳ�������ʱ��Խ����ռ���ڴ�Խ�࣬�����þ�ȫ���ڴ棬����ϵͳ������

							�ɳ��������һ���ڴ棬��û���κ�һ��ָ��ָ��������ô����ڴ��й¶�ˡ�

			7. ��η�ֹ�ڴ�й©
							���õı���ϰ�ߣ���new��deleteҪ��֤�ɶԳ��֣�new���������ݶ���ʹ�����֮��Ҫ��ʱ���ͷŵ������߾���ʹ������ָ�롣
						


			8. ����ڴ�й©��;��
							1. ʹ�ù������BoundsChecker����һ������ʱ�����⹤�ߣ�����Ҫ��λ��������ʱ�ڷ����ĸ��ִ���


			


			9. �ڴ�й©���޸�;��



*/


// make_shared<T>()������������һ��shared_ptrָ��
/* 
������  
	���ٶ�̬�ڴ�ռ䣬����shared_ptr����
	Դ��ͷ�ļ�<memory>
	���ɵ�T���Ͷ���ĳ�ʼֵ��Ĭ�ϵġ�
	���ӣ�shared_ptr<int> p = make_shared<int>(42);

						
	����1��
		shared_ptr<T> make_shared( Args&&... args 			����T����Ĺ��캯�������б�
															);	
		����ֵ��
			ָ���������T���Ͷ����shared_ptrָ�롣
			

	����2��
		shared_ptr<T> make_shared();

		����ֵ��
			ͬ�ϡ�
								 
  
*/
 


virtualModule* basicTypes_pointers_module::getInstance()		// �̲߳���ȫ�ĵ���ģʽ
{
	if (nullptr != p_moduleIns)
	{
		delete p_moduleIns;
	}
	p_moduleIns = new basicTypes_pointers_module;
	return p_moduleIns;
}


// test0: ʹ�ùؼ���new��deleteֱ�ӹ����ڴ档
void basicTypes_pointers_module::test0(void)
{
	std::cout << "\n\n\n\n" << std::endl;
	std::cout << "test0: ʹ�ùؼ���new��deleteֱ�ӹ����ڴ档" << std::endl;
 
	int *p1 = new int; 							// �������ڴ�ʧ�����׳�std::bad_alloc
	int *p2 = new (std::nothrow) int; 		// �������ڴ�ʧ���򷵻�һ����ָ��              
	int *p0 = new int;        
	                         
	delete p0;   

	int i(1024);              
	std::string s(10, '9');


	// δ�����������ѳ�ʼ���˵����ݶ���
	int *pi = new int(1024);  
	std::string *ps = new std::string(10, '9');
 
 

	std::vector<int> *pv = new std::vector<int>; 	// empty vector
	for (int i = 0; i != 10; ++i)
	{
		pv->push_back(i);              // add elements to the allocated vector
	}


	std::cout << "*pi: " << *pi
	     << "\ti: " << i << std::endl
	     << "*ps: " << *ps
	     << "\ts: " << s << std::endl;
	
	for (auto b = pv->begin(); b != pv->end(); ++b)
	{
		std::cout << *b << " ";
	}
	
	std::cout << std::endl;


	// �ڴ�ʹ������Ժ���Ҫɾ�����Ӧ��ָ�룬���������ڴ�й©
	delete pi;   
	delete ps;  
	delete pv;   
	
 
	// �����ڴ�Ŀ��ٺ��ͷţ�
	int *pia = new int[42];  
	delete [] pia; 			// �ͷ������ڴ��ʱ��Ҫ��delete֮�����[]
	typedef int arrT[42];   
	int *p = new arrT;      
	delete [] p;           

}



// test1������ָ��shared_ptr, unique_ptr�Ļ���ʹ��
void basicTypes_pointers_module::test1(void)
{
	float f1 = 1.10;
	std::shared_ptr<float> pf1;						// Ĭ�Ϲ��캯��������һ���յ�shared_ptrָ�� 
	std::shared_ptr<float> pf2(&f1);					// ������ָͨ�빹��shared_ptrָ��
	std::shared_ptr<float> pf3(new float(1.11));		// ������ָͨ�빹�죬��Ϲؼ���new
	std::shared_ptr<int> pi1;
	std::shared_ptr<int> pi2 = std::make_shared<int>(12);	// ʹ��make_shared��������shared_ptrָ��

	std::cout << "\n\n\n\n" << std::endl;
	std::cout << "test1������ָ��shared_ptr, unique_ptr" << std::endl;

	std::cout << "\tpi1.use_count() == " << pi2.use_count() << std::endl;
	std::cout << "\tpi1.unique() == " << pi2.unique() << std::endl;

	pi1 = pi2;
	std::cout << "pi1 = pi2; �� pi1,pi2����ͬһ�����ݶ���" << std::endl;
	std::cout << "\tpi1.use_count() == " << pi2.use_count() << std::endl;
	std::cout << "\tpi1.unique() == " << pi2.unique() << std::endl;

}



// test2: �Զ�������ʹ������ָ��shared_ptr, unique_ptr
void basicTypes_pointers_module::test2(void)
{

	// ����ָ��Ĭ��ʹ��delete���ͷŶ����ڴ档�Զ������͵ģ���Ҫ��ɾ�����ſ���ʹ��delete

}



// test3: ��ָ��
void basicTypes_pointers_module::test3(void)
{
	std::cout << "\n\n\n\n" << std::endl;
	std::cout << "test3����ָ��" << std::endl;

	// ʹ�ÿ�ָ�������ʲ����ڵ��ڴ�ռ䣬��������ָ���쳣���Ӷ��������
	// ����ʹ��p==NULL���ʽ���ص�boolֵ���ж��Ƿ��ǿ�ָ��
	int *pi1 = NULL;
	int *pi2 = NULL;

	if (pi1 == NULL && pi1 == NULL && pi2 == NULL && pi2 == NULL)
	{
		std::cout << "pi1��pi2���ǿ�ָ�롣д��NULL��nullptr�����ԡ�" << std::endl;
	}

	std::cout << "(int)(pi1 == NULL) == " << (int)(pi1 == NULL) << std::endl;
	std::cout << "(int)(pi1 == NULL)" << (int)(pi2 == NULL) << std::endl;



}


void basicTypes_pointers_module::test4(void) {}
 
 
void basicTypes_pointers_module::test5(void) {}



void basicTypes_pointers_module::test6(void)
{


}
