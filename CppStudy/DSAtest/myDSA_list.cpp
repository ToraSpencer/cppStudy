#include "myDSA_list.h"


////////////////////////////////////////////////////////////////////////////////////////////// DEBUG �ӿ�
namespace MY_DEBUG
{
	static std::string g_debugPath = "E:/";

	// lambda������ӡstd::cout֧�ֵ����ͱ�����
	template <typename T>
	static auto disp = [](const T& arg)
	{
		std::cout << arg << ", ";
	};

	static void debugDisp()			// �ݹ���ֹ
	{						//		�ݹ���ֹ��Ϊ�޲λ���һ�����������ζ����ԡ�
		std::cout << std::endl;
		return;
	}


	template <typename T, typename... Types>
	static void debugDisp(const T& firstArg, const Types&... args)
	{
		std::cout << firstArg << " ";
		debugDisp(args...);
	}


	// ���뺯���ӻ���ָ�����stl����
	template<typename T, typename F>
	void traverseSTL(T& con, F f)
	{
		std::for_each(con.begin(), con.end(), f);
		std::cout << std::endl;
	}


	// �������
	template<typename T, typename F>
	void revTraverseSTL(T& con, F f)
	{
		std::for_each(con.rbegin(), con.rend(), f);
		std::cout << std::endl;
	}
}
using namespace MY_DEBUG;



namespace LIST
{ 
	// ��������Ĺ鲢���򡪡�Ŀ��ʱ�临�Ӷ�O(nlogn)�������ռ临�Ӷ�
	using ListNode = SLlistNode<int>;
	ListNode* merge(ListNode* head1, ListNode* head2)
	{
		ListNode* dummyHead = new ListNode(0);
		ListNode* temp = dummyHead;
		ListNode* temp1 = head1;
		ListNode* temp2 = head2;
		while (temp1 != nullptr && temp2 != nullptr)
		{
			if (temp1->val <= temp2->val)
			{
				temp->next = temp1;
				temp1 = temp1->next;
			}
			else
			{
				temp->next = temp2;
				temp2 = temp2->next;
			}
			temp = temp->next;
		}
		if (temp1 != nullptr)
			temp->next = temp1;
		else if (temp2 != nullptr)
			temp->next = temp2;

		return dummyHead->next;
	}


	ListNode* sortList(ListNode* head, ListNode* tail)
	{
		if (head == nullptr)
			return head;

		if (head->next == tail)
		{
			head->next = nullptr;
			return head;
		}

		ListNode* slow = head;
		ListNode* fast = head;
		while (fast != tail)
		{
			slow = slow->next;
			fast = fast->next;
			if (fast != tail)
				fast = fast->next;

		}
		ListNode* mid = slow;
		ListNode* list1 = sortList(head, mid);
		ListNode* list2 = sortList(mid, tail);
		ListNode* sorted = merge(list1, list2);
		return sorted;
	}


	ListNode* sortList(ListNode* head)
	{
		return sortList(head, nullptr);
	}


	void test0()
	{
		using ListNode = SLlistNode<int>;
		ListNode* pHead = make_list<int>({ 2, 3, -1, -23, -1, -7, 99, -1, 0 });
		traverseList(pHead, [](ListNode* pn)
			{
				std::cout << pn->val << ", ";
			});
		debugDisp("\n");

		pHead = eraseNode(pHead, pHead->next);
		traverseList(pHead, [](ListNode* pn)
			{
				std::cout << pn->val << ", ";
			});
		debugDisp("\n");

		pHead = eraseNode(pHead, pHead);
		traverseList(pHead, [](ListNode* pn)
			{
				std::cout << pn->val << ", ";
			});
		debugDisp("\n");

		pHead = sortList(pHead);
		traverseList(pHead, [](ListNode* pn)
			{
				std::cout << pn->val << ", ";
			});
		debugDisp("\n");

		destroy(pHead);
		debugDisp("test1 finished.");
	}


	// ��������
	/*
		����һ�������ͷ�ڵ� head ���ж��������Ƿ��л���
		�����������ĳ���ڵ㣬����ͨ���������� next ָ���ٴε���������д��ڻ���
				Ϊ�˱�ʾ���������еĻ�������ϵͳ�ڲ�ʹ������ pos ����ʾ����β���ӵ������е�λ�ã������� 0 ��ʼ����
				ע�⣺pos ����Ϊ�������д��� ��������Ϊ�˱�ʶ�����ʵ�������
		��������д��ڻ� ���򷵻� true �� ���򣬷��� false ��

		ʾ�� 1��
		���룺head = [3,2,0,-4], pos = 1
		�����true
		���ͣ���������һ��������β�����ӵ��ڶ����ڵ㡣

		ʾ�� 2��
		���룺head = [1,2], pos = 0
		�����true
		���ͣ���������һ��������β�����ӵ���һ���ڵ㡣

		ʾ�� 3��
		���룺head = [1], pos = -1
		�����false
		���ͣ�������û�л���
	*/
	void test1() 
	{
	}

}

