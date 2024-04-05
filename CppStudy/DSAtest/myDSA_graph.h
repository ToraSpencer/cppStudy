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


// 枚举类——BT的遍历类型
enum class TRAVERSE_GRAPH_TYPE
{		
	depthFirst,
	breadthFirst,
};


// GraphNode类——图顶点类
template <typename T>
class GraphNode 
{ 
	using GraphEdge = SLlistNode<GraphNode*>;		// 用存储顶点指针的链表节点来表示边；
public:
	T val;									// 节点值
	GraphEdge* pFirstEdge;					// 邻接边链表的首个结点的指针；

public:
	GraphNode():val(0), pFirstEdge(nullptr) {}
	GraphNode(const T val0, GraphEdge* pe0 = nullptr)\
		:val(val0), pFirstEdge(pe0) {}
}; 


// Graph类——基于邻接表有向图类
template<typename T>
struct Graph 
{
	using GraphEdge = SLlistNode<GraphNode<T>*>;		// 用存储顶点指针的链表节点来表示边；
public:
	int nodeNum, nodeMaxNum, edgeNum;		// 节点数目、允许的顶点最大数目和边数
	std::vector<GraphNode<T>*> pnVec;					// 节点指针数组；

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

	// 插入一条有向边：
	GraphEdge* insertEdge(const int vaIdx, const int vbIdx) 
	{
		// 0. 错误检查
		if (vaIdx > this->nodeNum || vbIdx > this->nodeNum || vaIdx < 0 || vbIdx < 0)
			return nullptr;
		if (vaIdx == vbIdx)			// 不允许首尾顶点相同的边存在；
			return nullptr;

		GraphNode<T>* pa = this->pnVec[vaIdx];
		GraphNode<T>* pb = this->pnVec[vbIdx];
		GraphEdge* pe1 = nullptr;
		GraphEdge* pe2 = nullptr; 

		if (nullptr == pa->pFirstEdge)
		{
			// A. 若顶点a没有发出有向边，则直接为其添加一条新有向边：
			pa->pFirstEdge = new GraphEdge(pb);
			this->edgeNum++;
			return pa->pFirstEdge;
		}
		else
		{
			// B. 若顶点a已存在发出的有向边：

			//		B1. 找到链表最后一个节点，同时检查待插入的边是否已经存在；
			pe1 = pa->pFirstEdge;
			while (nullptr != pe1)				
			{
				pe2 = pe1;
				pe1 = pe1->next;
				if (pb == pe2->val)
					return nullptr;					// 待插入的边已经存在；
			}

			//		B2. 边链表尾部插入新的边节点；
			pe2->next = new GraphEdge(pb);					// 此时pe2指向边链表最后一个节点；	
			this->edgeNum++;
			return pe2->next;
		}		 
	}
};


// 遍历图(to be completed)
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


// 控制台上打印图顶点的信息
template <typename T>
static auto dispGraphNode = [](const GraphNode<T>* ptrNode)
{
	if(nullptr == ptrNode)
		std::cout << "placeholder, ";
	else
		std::cout << ptrNode->val << ", ";
};

////////////////////////////////////////////////////////////////////////////////////////////// 测试函数：
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