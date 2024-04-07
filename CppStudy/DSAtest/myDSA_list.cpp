#include "myDSA_list.h"


////////////////////////////////////////////////////////////////////////////////////////////// DEBUG 接口
namespace MY_DEBUG
{
	static std::string g_debugPath = "E:/";

	// lambda——打印std::cout支持的类型变量。
	template <typename T>
	static auto disp = [](const T& arg)
	{
		std::cout << arg << ", ";
	};

	static void debugDisp()			// 递归终止
	{						//		递归终止设为无参或者一个参数的情形都可以。
		std::cout << std::endl;
		return;
	}


	template <typename T, typename... Types>
	static void debugDisp(const T& firstArg, const Types&... args)
	{
		std::cout << firstArg << " ";
		debugDisp(args...);
	}


	// 传入函数子或函数指针遍历stl容器
	template<typename T, typename F>
	void traverseSTL(T& con, F f)
	{
		std::for_each(con.begin(), con.end(), f);
		std::cout << std::endl;
	}


	// 反向遍历
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


	// 基于链表的归并排序——目标时间复杂度O(nlogn)，常数空间复杂度
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


	// 环形链表
	/*
		给你一个链表的头节点 head ，判断链表中是否有环。
		如果链表中有某个节点，可以通过连续跟踪 next 指针再次到达，则链表中存在环。
				为了表示给定链表中的环，评测系统内部使用整数 pos 来表示链表尾连接到链表中的位置（索引从 0 开始）。
				注意：pos 不作为参数进行传递 。仅仅是为了标识链表的实际情况。
		如果链表中存在环 ，则返回 true 。 否则，返回 false 。

		示例 1：
		输入：head = [3,2,0,-4], pos = 1
		输出：true
		解释：链表中有一个环，其尾部连接到第二个节点。

		示例 2：
		输入：head = [1,2], pos = 0
		输出：true
		解释：链表中有一个环，其尾部连接到第一个节点。

		示例 3：
		输入：head = [1], pos = -1
		输出：false
		解释：链表中没有环。
	*/

	// 版本1——可查询环所在位置；
	bool hasCycle(ListNode* head)
	{
		int pos = -1;					// 标识环的位置；
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
				// debugDisp("pos == ", pos);
				return true;
			}
			index++;
			pn = pn->next;
		}

		return false;
	}


	// 版本2——不可查询环所在位置；
	bool hasCycle2(ListNode* head)
	{
		ListNode* pn = head;
		std::unordered_set<ListNode*> seen;
		while (pn != nullptr)
		{
			if (seen.count(pn))				// 查询当前节点是否在哈希表中已存在；
				return true;
			seen.insert(pn);
			pn = pn->next;
		}
		return false;
	}


	void test1()
	{
		ListNode* head = make_list<int>({ 3, 2, 0, -4 });
		ListNode* pn1 = head->next;
		ListNode* pn2 = head->next->next->next;
		pn2->next = pn1;

		debugDisp("ret1 == ", hasCycle(head));

		debugDisp("ret2 == ", hasCycle2(head));


		debugDisp("test1 finished.");
	}


	// JZOF13: 在O（1）时间删除链表结点
	/*
		给定单向链表的头指针和一个结点指针，定义一个函数在 O（1）时间删除该结点。
		链表结点与函数的定义如下：
		struct ListNode
		{
			int       m_nValue;
			ListNode＊ m_pNext;
		};
		void DeleteNode（ListNode＊＊ pListHead, ListNode＊ pToBeDeleted）;

		在单向链表中删除一个结点，最常规的做法无疑是从链表的头结点开始，顺序遍历查找要删除的结点，并在链表中删除该结点。
		比如在图3.3（a）所示的链表中，我们想删除结点i，可以从链表的头结点a开始顺序遍历，发现结点h的m_pNext指向要删除的结点i，于是我们可以把结点h的m_pNext指向i的下一个结点即结点j。指针调整之后，我们就可以安全地删除结点i并保证链表没有断开（如图3.3（b）所示）。这种思路由于需要顺序查找，时间复杂度自然就是O（n）了。

	*/
	void test2()
	{
		/*

	void DeleteNode（ListNode＊＊ pListHead, ListNode＊ pToBeDeleted）
	{
		if（!pListHead || !pToBeDeleted）
			return;

		// 要删除的结点不是尾结点
		if（pToBeDeleted->m_pNext != NULL）
		{
			ListNode＊ pNext = pToBeDeleted->m_pNext;
			pToBeDeleted->m_nValue = pNext->m_nValue;
			pToBeDeleted->m_pNext = pNext->m_pNext;

			delete pNext;
			pNext = NULL;
		}
		// 链表只有一个结点，删除头结点（也是尾结点）
		else if（＊pListHead == pToBeDeleted）
		{
			delete pToBeDeleted;
			pToBeDeleted = NULL;
			＊pListHead = NULL;
		}
		// 链表中有多个结点，删除尾结点
		else
		{
			ListNode＊ pNode = ＊pListHead;
			while（pNode->m_pNext != pToBeDeleted）
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


	// JZOF15: 链表中倒数第k个结点
	/*
			输入一个链表，输出该链表中倒数第 k 个结点。
			为了符合大多数人的习惯，本题从1 开始计数，即链表的尾结点是倒数第1 个结点。
			例如一个链表有6个结点，从头结点开始它们的值依次是1、2、3、4、5、6。这个链表的倒数第3个结点是值为4的结点。
			struct ListNode
			{
				int       m_nValue;
				ListNode＊ m_pNext;
			};


	*/
	void test3()
	{
		/*
		ListNode＊ FindKthToTail（ListNode＊ pListHead, unsigned int k）
	{
		if（pListHead == NULL || k == 0）
			return NULL;

		ListNode ＊pAhead = pListHead;
		ListNode ＊pBehind = NULL;

		for（unsigned int i = 0; i < k - 1; ++ i）
		{
			if（pAhead->m_pNext != NULL）
				pAhead = pAhead->m_pNext;
			else
			{
				return NULL;
			}
		}

		pBehind = pListHead;
		while（pAhead->m_pNext != NULL）
		{
			pAhead = pAhead->m_pNext;
			pBehind = pBehind->m_pNext;
		}

		return pBehind;
	}

		*/
	}


	// JZOF16: 反转链表
	/*
		定义一个函数，输入一个链表的头结点，反转该链表并输出反转后链表的头结点。链表结点定义如下：
			struct ListNode
			{
				int       m_nKey;
				ListNode＊ m_pNext;
			};
	*/
	void test4()
	{
		/*
		 ListNode＊ ReverseList（ListNode＊ pHead）
		 {
            ListNode＊ pReversedHead = NULL;
            ListNode＊ pNode = pHead;
            ListNode＊ pPrev = NULL;
            while（pNode != NULL）
            {
                  ListNode＊ pNext = pNode->m_pNext;
                  if（pNext == NULL）
                          pReversedHead = pNode;

                  pNode->m_pNext = pPrev;

                  pPrev = pNode;
                  pNode = pNext;
            }

            return pReversedHead;
    } 
		
		*/

	}


}

