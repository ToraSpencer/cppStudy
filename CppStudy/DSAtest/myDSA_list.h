#pragma once
#include <iostream>
#include <vector>
#include <initializer_list>
#include <queue>
#include <unordered_set>
#include <unordered_map>
#include <algorithm>
  

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

// 
	SLlistNode* append(const T x)
	{
		SLlistNode<T>* pn0 = this;
		SLlistNode<T>* pn1 = this->next;
		while (nullptr != pn1)
		{
			pn0 = pn1;
			pn1 = pn1->next;
		}
		pn1 = new SLlistNode(x);
		
		return pn1;
	}

	SLlistNode* append(SLlistNode* pn)
	{
		SLlistNode<T>* pn0 = this;
		SLlistNode<T>* pn1 = this->next;
		while (nullptr != pn1)
		{
			pn0 = pn1;
			pn1 = pn1->next;
		}
		pn1 = pn;

		return pn1;
	}

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