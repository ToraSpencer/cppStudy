#pragma once
#include <iostream>
#include <vector>
#include <initializer_list>
#include <queue>
#include <unordered_set>
#include <unordered_map>
#include <algorithm>
 

#if 0

template <typename T>
class ListNode
{
public:
	T data;
	ListNode* prior;
	ListNode* next;

public:

	// constructor and destructor:
	ListNode() :data(0), prior(nullptr), next(nullptr)
	{}

	ListNode(const T data0) :data(data0), prior(nullptr), next(nullptr)
	{}

	~ListNode() {}

	// 读方法
	T getData()
	{
		return this->data;
	}

	ListNode* getNext()
	{
		return this->next;
	}

	ListNode* getPrior()
	{
		return this->prior;
	}

	ListNode* getHead()
	{
		ListNode* ptrNode = this;
		while (nullptr != ptrNode->prior)
			ptrNode = ptrNode->prior;
		return ptrNode;
	}

	ListNode* getTail()
	{
		ListNode* ptrNode = this;
		while (nullptr != ptrNode->next)
			ptrNode = ptrNode->next;
		return ptrNode;
	}

	ListNode* getNode(const int index)
	{
		if (index < 0)
			return nullptr;

		ListNode* pn = getHead();
		for (int i = 0; i < index; ++i)
		{
			pn = pn->next;
			if (nullptr == pn)
				return nullptr;
		}
		return pn;
	}

	int size()
	{
		int nodesCount = 1;
		ListNode* pn = getHead();
		while (nullptr != pn->getNext())
		{
			pn = pn->getNext();
			nodesCount++;
		}
		return nodesCount;
	}

	// 写方法：
	bool push_back(ListNode* ptrNode)
	{
		if (nullptr == ptrNode)
			return false;
		ListNode* pn = getTail();
		pn->next = ptrNode;
		ptrNode->prior = pn;

		return true;
	}

	bool push_back(const T elem)
	{
		ListNode* pn = getTail();
		pn->next = new ListNode(elem);
		pn->next->prior = pn;
		return true;
	}

	bool push_front(ListNode* ptrNode)
	{
		if (nullptr == ptrNode)
			return false;

		ListNode* pn = getHead();
		pn->prior = ptrNode;
		ptrNode->next = pn;

		return true;
	}

	bool push_front(const T elem)
	{
		ListNode* pn = getHead();
		pn->prior = new ListNode(elem);
		pn->prior->next = pn;
		return true;
	}

	bool pop_front()
	{
		ListNode* pn = getHead();
		ListNode* pn2 = pn->getNext();
		if (nullptr == pn2)					// size为1
			return false;

		delete pn;
		pn2->prior = nullptr;

		return true;
	}

	bool pop_back()
	{
		ListNode* pn = getTail();
		ListNode* pn2 = pn->getPrior();
		if (nullptr == pn2)		// size为1
			return false;

		delete pn;
		pn2->next = nullptr;

		return true;
	}

	bool insertPrior(ListNode* ptrNode)
	{
		if (nullptr == ptrNode)
			return false;

		ListNode* pn = this->prior;
		if (nullptr == pn)					  // a. 前面没有节点
		{
			ptrNode->prior = nullptr;
			ptrNode->next = this;
			this->prior = ptrNode;
		}
		else                          		      // b.  前面有节点：
		{
			pn->next = ptrNode;
			ptrNode->prior = pn;
			ptrNode->next = this;
			this->prior = ptrNode;
		}
		return true;
	}

	bool insertNext(ListNode* ptrNode)
	{
		if (nullptr == ptrNode)
			return false;

		ListNode* pn = this->next;
		if (nullptr == pn)					  // a. 后面没有节点
		{
			this->next = ptrNode;
			ptrNode->prior = this;
			ptrNode->next = nullptr;
		}
		else                                       // b. 后面有节点；
		{
			this->next = ptrNode;
			ptrNode->prior = this;
			ptrNode->next = pn;
			pn->prior = ptrNode;
		}

		return true;
	}

	// 将本节点提取出链表，变成孤立节点；
	bool extract()
	{
		ListNode* pn1 = this->prior;
		ListNode* pn2 = this->next;
		if (nullptr != pn1)
			pn1->next = pn2;
		if (nullptr != pn2)
			pn2->prior = pn1;

		this->prior = nullptr;
		this->next = nullptr;

		return true;
	}

	bool erase(ListNode* ptrNode)
	{
		if (nullptr == ptrNode || this == ptrNode)
			return false;

		ListNode* pn1 = ptrNode->prior;
		ListNode* pn2 = ptrNode->next;
		if (nullptr != pn1)
			pn1->next = pn2;
		if (nullptr != pn2)
			pn2->prior = pn1;

		delete ptrNode;

		return true;
	}
};

template <typename T>
class List
{
public:
	ListNode* head;
	ListNode* tail;

public:
	List() :head(nullptr), tail(nullptr) {}

	List() : {}
};


template<typename T, typename Func>
void traverseList(ListNode<T>* ptrNode, Func fun)
{
	if (nullptr == ptrNode)
		return;
	ListNode<T>* pn = ptrNode->getHead();
	while (nullptr != pn)
	{
		fun(pn);
		pn = pn->getNext();
	}

}


template <typename T>
void destroy(ListNode<T>* ptrNode)
{
	if (nullptr == ptrNode)
		return;
	ListNode<T>* pn = ptrNode->getHead();
	ListNode<T>* pn2 = nullptr;
	while (nullptr != pn)
	{
		pn2 = pn->getNext();
		delete pn;
		pn = pn2;
	}
}

#endif


// SLlistNode类——单向链表节点类
template <typename T>
class SLlistNode
{
public:
	T val;
	SLlistNode* next;

public:
	SLlistNode() :val(0), next(nullptr) {}
	SLlistNode(const T x) : val(x), next(nullptr) {}
	SLlistNode(const T x, SLlistNode* next) : val(x), next(next) {}
};


// 删除以head为首节点的整条链表；
template <typename T>
void destroy(SLlistNode<T>* head)
{
	if (nullptr == head)
		return;

	SLlistNode<T>* pn0 = head;
	SLlistNode<T>* pn1 = nullptr;
	while (nullptr != pn0)
	{
		pn1 = pn0->next;
		delete pn0;
		pn0 = pn1;
	}
}


// 删掉链表中的某个节点，返回head节点；
template<typename T>
SLlistNode<T>* eraseNode(SLlistNode<T>* ptrHead, SLlistNode<T>* ptrNode)
{
	SLlistNode<T>* pn0 = ptrHead;
	if (nullptr == ptrHead)
		return nullptr;
	if (nullptr == ptrNode)
		return ptrHead;				// do nothing;

	SLlistNode<T>* next0 = ptrNode->next;
	if (ptrNode == ptrHead)
	{
		delete ptrHead;
		return next0;
	}

	SLlistNode<T>* prior0 = ptrHead;
	while (prior0->next != ptrNode)
		prior0 = prior0->next;
	delete ptrNode;
	prior0->next = next0;

	return ptrHead;
}


// 由std::vector<>生成链表
template <typename T>
SLlistNode<T>* make_list(const std::vector<T>& vec)
{
	if (vec.empty())
		return nullptr;

	SLlistNode<T>* pn0 = nullptr;
	SLlistNode<T>* pHead = nullptr;
	auto iter = vec.rbegin();
	pHead = new SLlistNode<T>(*iter);
	iter++;
	for (; iter != vec.rend(); iter++)
	{
		pn0 = new SLlistNode<T>(*iter, pHead);
		pHead = pn0;
	}
	return pHead;
}


// 输入函数子遍历链表；
template<typename T, typename Func>
void traverseList(SLlistNode<T>* ptrHead, Func fun)
{
	if (nullptr == ptrHead)
		return;
	SLlistNode<T>* pn = ptrHead;
	while (nullptr != pn)
	{
		fun(pn);
		pn = pn->next;
	}
}
 

namespace LIST
{
	void test0();
	void test1();
	void test2(); 
	void test4();
	void test5();
	void test6();
	void test7();
}