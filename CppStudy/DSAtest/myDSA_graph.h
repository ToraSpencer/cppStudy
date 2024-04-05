#pragma once
#include <iostream>
#include <initializer_list>
#include <vector>
#include <string>
#include <stack>
#include <queue>
#include <unordered_map>
#include <algorithm>
#include <exception>
#include <stdexcept>

#include "myDSA_list.h"


#define DEFAULT_SIZE 1000					 
 

template <typename T>
struct Doublet
{
	T x;
	T y;
	Doublet():x(0), y(0){}
	Doublet(const T x0, const T y0): x(x0), y(y0){}
};


// ö���ࡪ��BT�ı�������
enum class TRAVERSE_GRAPH_TYPE
{		
	depthFirst,
	breadthFirst,
};


// GraphNode�ࡪ��ͼ������
template <typename T>
class GraphNode 
{ 
	using GraphEdge = SLlistNode<GraphNode*>;		// �ô洢����ָ�������ڵ�����ʾ�ߣ�
public:
	T val;									// �ڵ�ֵ
	GraphEdge* pFirstEdge;					// �ڽӱ�������׸�����ָ�룻

public:
	GraphNode():val(0), pFirstEdge(nullptr) {}
	GraphNode(const T val0, GraphEdge* pe0 = nullptr)\
		:val(val0), pFirstEdge(pe0) {}
}; 


// Graph�ࡪ�������ڽӱ�����ͼ��
template<typename T>
struct Graph 
{
	using GraphEdge = SLlistNode<GraphNode<T>*>;		// �ô洢����ָ�������ڵ�����ʾ�ߣ�
public:
	int nodeNum, nodeMaxNum, edgeNum;		// �ڵ���Ŀ������Ķ��������Ŀ�ͱ���
	std::vector<GraphNode<T>*> pnVec;					// �ڵ�ָ�����飻

public:

// constructor and destructor
	Graph() :nodeNum(0), nodeMaxNum(DEFAULT_SIZE), edgeNum(0) {}
	Graph(const std::initializer_list<T>& ilist) 
	{
		this->nodeNum = ilist.size();
		this->nodeMaxNum = DEFAULT_SIZE;
		this->edgeNum = 0;
		this->pnVec.reserve(ilist.size());
		for (const auto& elem : ilist)
			pnVec.push_back(new GraphNode<T>(elem)); 
	}
	~Graph()
	{
		for (auto& pn : pnVec)
			delete pn;
	}

// create methods:

	// ����һ������ߣ�
	GraphEdge* insertEdge(const int vaIdx, const int vbIdx) 
	{
		// 0. ������
		if (vaIdx > this->nodeNum || vbIdx > this->nodeNum || vaIdx < 0 || vbIdx < 0)
			return nullptr;
		if (vaIdx == vbIdx)			// ��������β������ͬ�ıߴ��ڣ�
			return nullptr;

		GraphNode<T>* pa = this->pnVec[vaIdx];
		GraphNode<T>* pb = this->pnVec[vbIdx];
		GraphEdge* pe1 = nullptr;
		GraphEdge* pe2 = nullptr; 

		if (nullptr == pa->pFirstEdge)
		{
			// A. ������aû�з�������ߣ���ֱ��Ϊ�����һ��������ߣ�
			pa->pFirstEdge = new GraphEdge(pb);
			this->edgeNum++;
			return pa->pFirstEdge;
		}
		else
		{
			// B. ������a�Ѵ��ڷ���������ߣ�

			//		B1. �ҵ��������һ���ڵ㣬ͬʱ��������ı��Ƿ��Ѿ����ڣ�
			pe1 = pa->pFirstEdge;
			while (nullptr != pe1)				
			{
				pe2 = pe1;
				pe1 = pe1->next;
				if (pb == pe2->val)
					return nullptr;					// ������ı��Ѿ����ڣ�
			}

			//		B2. ������β�������µı߽ڵ㣻
			pe2->next = new GraphEdge(pb);					// ��ʱpe2ָ����������һ���ڵ㣻	
			this->edgeNum++;
			return pe2->next;
		}		 
	}
};


// ����ͼ(to be completed)
template <typename T, typename Func>
void traverseGraph(GraphNode<T>* ptrNode, Func func, \
	const TRAVERSE_GRAPH_TYPE type = TRAVERSE_GRAPH_TYPE::depthFirst, \
	const bool skipNP = true)
{
	GraphNode<T>* pn1 = nullptr;
	GraphNode<T>* pn2 = nullptr;
	std::unordered_map<GraphNode<T>*, bool> visited;
	if(TRAVERSE_GRAPH_TYPE::depthFirst == type)
	{
		
	}
}


// ����̨�ϴ�ӡͼ�������Ϣ
template <typename T>
static auto dispGraphNode = [](const GraphNode<T>* ptrNode)
{
	if(nullptr == ptrNode)
		std::cout << "placeholder, ";
	else
		std::cout << ptrNode->val << ", ";
};

////////////////////////////////////////////////////////////////////////////////////////////// ���Ժ�����
namespace GRAPH
{
	void test0();
	void test1();
	void test2();
	void test3();
	void test4();
	void test5();
	void test6();
	void test7();
	void test8();
	void test9();
	void test10();
	void test11();
	void test12();
	void test13();
	void test14();
	void test15();
	void test16();
}