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
	// 基于链表的归并排序——目标时间复杂度O(nlogn)，常数空间复杂度
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
	void test1() 
	{
	}

}

