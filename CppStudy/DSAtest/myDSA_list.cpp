#include "myDSA_list.h"

#include <stack>


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
	using ListNode = SLlistNode<int>;


	// test0: ��������Ĺ鲢���򡪡�Ŀ
	/*
		���ڷֶ���֮�����֣���˼�룻
		����������Ե����ϵġ����ָ�����ٷָ��ʱ��ŶԻ����ν��в�����
		��ʱ�临�Ӷ�O(nlogn)�������ռ临�Ӷ�
	*/

	
	// �ϲ�������������
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


	// �ݹ麯��������������Ĺ鲢����
	ListNode* sortList(ListNode* head, ListNode* tail = nullptr)
	{
		/*
			��head, tail��ȷ����ǰ�պ󿪵������еĽڵ���й鲢����
			tail == nullptrʱ��ʾ��headһ����������й鲢����
		
		*/

		// 1. �ݹ���ֹ1������Ϊ��
		if (head == nullptr)
			return head;

		// 2. �ݹ���ֹ2������ֻ��һ��Ԫ�أ�
		if (head->next == tail)
		{
			head->next = nullptr;
			return head;
		}

		// 3. �ݹ���ƣ�

		//		3.1 Ѱ���м�ڵ㣺
		ListNode* pn1 = head;
		ListNode* pn2 = head;
		while (pn2 != tail)
		{
			pn1 = pn1->next;
			pn2 = pn2->next;
			if (pn2 != tail)
				pn2 = pn2->next;
		}

		//		3.2 �ָ�����������ֱ�ݹ�����Լ���
		ListNode* mid = pn1;
		ListNode* list1 = sortList(head, mid);
		ListNode* list2 = sortList(mid, tail);

		//		3.3 �ϲ�������������
		ListNode* sorted = merge(list1, list2);

		return sorted;
	}
	 


	void test0()
	{ 
		ListNode* pHead = make_list<int>({ 2, 3, -1, -23, -1, -7, 99, -1, 0 });
		traverseList(pHead, dispListNode<int>()); 
		debugDisp("\n");

		pHead = eraseNode(pHead, pHead->next);
		traverseList(pHead, dispListNode<int>());
		debugDisp("\n");

		pHead = eraseNode(pHead, pHead);
		traverseList(pHead, dispListNode<int>());
		debugDisp("\n");

		debugDisp("sortList: ");
		pHead = sortList(pHead);
		traverseList(pHead, dispListNode<int>());
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
		// lamda�����汾1���ɲ�ѯ������λ�ã������ֵ�
		auto hasCycle = [](ListNode * head)->bool
		{
			int pos = -1;								// ��ʶ����λ�ã�
			ListNode* pn = head;
			int index = 1;
			std::unordered_map<unsigned long, int> map;
			std::pair<std::unordered_map<unsigned long, int>::iterator, bool> retIter;

			if (nullptr == head)
				return false;

			map.insert(std::make_pair(reinterpret_cast<unsigned long>(head), 0));
			while (nullptr != pn->next)
			{
				retIter = map.insert(std::make_pair(reinterpret_cast<unsigned long>(pn->next), index));
				if (!retIter.second)
				{
					pos = std::distance(map.begin(), retIter.first);
					return true;
				}
				index++;
				pn = pn->next;
			}

			return false;
		};


		// lamda�������ɲ�ѯ������λ�ã����ù�ϣ��
		auto hasCycle2 = [](ListNode* head)->bool
		{
			ListNode* pn = head;
			std::unordered_set<ListNode*> seen;
			while (pn != nullptr)
			{
				if (seen.count(pn))				// ��ѯ��ǰ�ڵ��Ƿ��ڹ�ϣ�����Ѵ��ڣ�
					return true;
				seen.insert(pn);
				pn = pn->next;
			}
			return false;
		};

		ListNode* head = make_list<int>({ 3, 2, 0, -4 });
		ListNode* pn1 = head->next;
		ListNode* pn2 = head->next->next->next;
		pn2->next = pn1;

		debugDisp("ret1 == ", hasCycle(head));
		debugDisp("ret2 == ", hasCycle2(head));


		debugDisp("test1 finished.");
	}


	// JZOF13: ��O��1��ʱ��ɾ��������
	/*
		�������������ͷָ���һ�����ָ�룬����һ�������� O��1��ʱ��ɾ���ý�㡣
		�������뺯���Ķ������£�
		struct ListNode
		{
			int       m_nValue;
			ListNode�� m_pNext;
		};
		void DeleteNode��ListNode���� pListHead, ListNode�� pToBeDeleted��;

		�ڵ���������ɾ��һ����㣬�������������Ǵ������ͷ��㿪ʼ��˳���������Ҫɾ���Ľ�㣬����������ɾ���ý�㡣
		������ͼ3.3��a����ʾ�������У�������ɾ�����i�����Դ������ͷ���a��ʼ˳����������ֽ��h��m_pNextָ��Ҫɾ���Ľ��i���������ǿ��԰ѽ��h��m_pNextָ��i����һ����㼴���j��ָ�����֮�����ǾͿ��԰�ȫ��ɾ�����i����֤����û�жϿ�����ͼ3.3��b����ʾ��������˼·������Ҫ˳����ң�ʱ�临�Ӷ���Ȼ����O��n���ˡ�

	*/
	void test2()
	{
		/*

	void DeleteNode��ListNode���� pListHead, ListNode�� pToBeDeleted��
	{
		if��!pListHead || !pToBeDeleted��
			return;

		// Ҫɾ���Ľ�㲻��β���
		if��pToBeDeleted->m_pNext != NULL��
		{
			ListNode�� pNext = pToBeDeleted->m_pNext;
			pToBeDeleted->m_nValue = pNext->m_nValue;
			pToBeDeleted->m_pNext = pNext->m_pNext;

			delete pNext;
			pNext = NULL;
		}
		// ����ֻ��һ����㣬ɾ��ͷ��㣨Ҳ��β��㣩
		else if����pListHead == pToBeDeleted��
		{
			delete pToBeDeleted;
			pToBeDeleted = NULL;
			��pListHead = NULL;
		}
		// �������ж����㣬ɾ��β���
		else
		{
			ListNode�� pNode = ��pListHead;
			while��pNode->m_pNext != pToBeDeleted��
			{
				pNode = pNode->m_pNext;
			}

			pNode->m_pNext = NULL;
			delete pToBeDeleted;
			pToBeDeleted = NULL;
		}
	}
		*/
	}


	// JZOF15: �����е�����k�����
	/*
			����һ����������������е����� k ����㡣
			Ϊ�˷��ϴ�����˵�ϰ�ߣ������1 ��ʼ�������������β����ǵ�����1 ����㡣
			����һ��������6����㣬��ͷ��㿪ʼ���ǵ�ֵ������1��2��3��4��5��6���������ĵ�����3�������ֵΪ4�Ľ�㡣
			struct ListNode
			{
				int       m_nValue;
				ListNode�� m_pNext;
			};


	*/
	void test3()
	{
		/*
		ListNode�� FindKthToTail��ListNode�� pListHead, unsigned int k��
	{
		if��pListHead == NULL || k == 0��
			return NULL;

		ListNode ��pAhead = pListHead;
		ListNode ��pBehind = NULL;

		for��unsigned int i = 0; i < k - 1; ++ i��
		{
			if��pAhead->m_pNext != NULL��
				pAhead = pAhead->m_pNext;
			else
			{
				return NULL;
			}
		}

		pBehind = pListHead;
		while��pAhead->m_pNext != NULL��
		{
			pAhead = pAhead->m_pNext;
			pBehind = pBehind->m_pNext;
		}

		return pBehind;
	}

		*/
	}


	// JZOF16: ��ת����
	/*
		����һ������������һ�������ͷ��㣬��ת�����������ת�������ͷ��㡣�����㶨�����£�
			struct ListNode
			{
				int       m_nKey;
				ListNode�� m_pNext;
			};
	*/
	void test4()
	{  
		// lambda1��������ջ�ṹ
		auto reverseList1 = [](ListNode* pHead)->ListNode*
		{
			//  ����û�л�����;

			// 1. �ڵ���ջ��
			std::stack<ListNode*> pnStack;
			ListNode* pn = pHead;
			while (pn != nullptr)
			{
				pnStack.push(pn);
				pn = pn->next;
			}

			// 2. ����ջ�ṹ�������дÿ���ڵ��е�ָ�룬ʵ������ת��
			ListNode* pHead2 = pnStack.top();
			ListNode* pn2 = nullptr;			// ָ��ջ���ڵ㣻
			pn = pHead2;							// ָ��ǰ���һ���ڵ㣻
			pnStack.pop();
			while (!pnStack.empty())
			{
				pn2 = pnStack.top();
				pn->next = pn2;
				pn = pn->next;
				pnStack.pop();
			}
			pn->next = nullptr;

			return pHead2;
		};

		// lambda2���������κ������ṹ��
		auto reverseList2 = [](ListNode* pHead)->ListNode*
		{
			ListNode* pHead2 = nullptr;
			ListNode* pn = pHead;
			ListNode* pnPrev = nullptr;
			ListNode* pnNext = nullptr;

			// ��¼����д��ǰ����ѭ����
			do
			{ 
				pnNext = pn->next;
				pn->next = pnPrev;							// ��תָ�룻
				pnPrev = pn;
				pn = pnNext;					
			} while (pn->next != nullptr);

			// ���һ�θ�д��
			pn->next = pnPrev;

			return pn;
		};

		// test:
		ListNode* pHead = nullptr;
		ListNode* pHead1 = nullptr;
		ListNode* pHead2 = nullptr;

		pHead = make_list(std::vector<int>{1, 2, 3, 4, 5, 6});
		traverseList(pHead, dispListNode<int>());
		debugDisp("\n");
		pHead1 = reverseList1(pHead);
		traverseList(pHead1, dispListNode<int>());
		debugDisp("\n");

		pHead = make_list(std::vector<int>{1, 2, 3, 4, 5, 6});
		pHead2 = reverseList2(pHead);
		traverseList(pHead2, dispListNode<int>());
		debugDisp("\n");
		destroy(pHead2);

		debugDisp("test4 finished.");
	}


}

