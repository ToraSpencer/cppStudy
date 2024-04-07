#pragma once
#include <iostream>
#include <initializer_list>
#include <vector>
#include <string>
#include <stack>
#include <queue>
#include <unordered_map>
#include <iterator>
#include <algorithm>
#include <numeric>
#include <exception>
#include <stdexcept>

#include "triMesh.h"
#include "myDSA_list.h"


#define DEFAULT_SIZE 1000					 
 


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
	T val;											// �ڵ�ֵ
	GraphEdge* pFirstEdge;				// �ڽӱ�������׸�����ָ�룻

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
	int nodeNum, nodeMaxNum, edgeNum;				// �ڵ���Ŀ������Ķ��������Ŀ�ͱ���
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
	Graph(const std::vector<T>& vec)			
	{
		this->nodeNum = vec.size();
		this->nodeMaxNum = DEFAULT_SIZE;
		this->edgeNum = 0;
		this->pnVec.reserve(vec.size());
		for (const auto& elem : vec)
			pnVec.push_back(new GraphNode<T>(elem));
	}


	// �������캯���������
	Graph(const Graph& g) :nodeNum(g.nodeNum), \
		nodeMaxNum(g.nodeMaxNum), edgeNum(g.edgeNum)			 
	{		 
		std::unordered_map<GraphNode<T>*, GraphNode<T>*> map;	// ��-�¶���ָ���ӳ���
		
		// 1. ������㣬������-�¶���ָ���ӳ���
		this->pnVec.resize(nodeNum);
		for (int i = 0; i < nodeNum; ++i)
		{
			this->pnVec[i] = new GraphNode<T>(g.pnVec[i]->val);
			map.insert(std::make_pair(g.pnVec[i], this->pnVec[i]));
		}

		// 2. ���ɱ����ݣ�
		GraphNode<T>* pnOld = nullptr;
		GraphNode<T>* pnNew = nullptr;
		GraphNode<T>* pnConn = nullptr;
		for (int i = 0; i < nodeNum; ++i)
		{
			pnOld = g.pnVec[i];
			pnNew = this->pnVec[i];
			traverseList(pnOld->pFirstEdge, [&](GraphEdge* pe) 
				{
					pnConn = map[pe->val];		// �ϵĶ�������ӳ����µģ�
					pnNew->pFirstEdge->append(pnConn);
				});
		}
	}

	~Graph()
	{
		for (auto& pn : this->pnVec)
		{
			destroy(pn->pFirstEdge);
			delete pn;
		}
		this->pnVec.clear();
	}


// create methods:

	// ����һ������ߣ�
	GraphEdge* addEdge(const int vaIdx, const int vbIdx) 
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


// operator override:
	const Graph& operator=(const Graph& g)
	{
		this->nodeNum = g.nodeNum;
		this->nodeMaxNum = g.nodeMaxNum;
		this->edgeNum = g.edgeNum;		

		// 1. ������㣬������-�¶���ָ���ӳ���
		std::unordered_map<GraphNode<T>*, GraphNode<T>*> map;	// ��-�¶���ָ���ӳ���
		this->pnVec.resize(nodeNum);
		for (int i = 0; i < nodeNum; ++i)
		{
			this->pnVec[i] = new GraphNode<T>(g.pnVec[i]->val);
			map.insert(std::make_pair(g.pnVec[i], this->pnVec[i]));
		}

		// 2. ���ɱ����ݣ�
		GraphNode<T>* pnOld = nullptr;
		GraphNode<T>* pnNew = nullptr;
		GraphNode<T>* pnConn = nullptr;
		for (int i = 0; i < nodeNum; ++i)
		{
			pnOld = g.pnVec[i];
			pnNew = this->pnVec[i];
			traverseList(pnOld->pFirstEdge, [&](GraphEdge* pe)
				{
					pnConn = map[pe->val];		// �ϵĶ�������ӳ����µģ�
					pnNew->pFirstEdge->append(pnConn);
				});
		}

		return *this;
	}
};
using Graph3D = Graph<verF>;						// ��ά���ƹ��ɵ�ͼ


// ������������ͼ(to be completed)
/*
 	�����������BFS�Ͷ���queue���ܹ���
			һ���ڵ�pn������
			�� �ýڵ��һϵ��1����ڵ㱻ѹ����У��������
			�� ����һϵ�ж����1����ڵ㡪����pn��2����ڵ㡪����ѹ����У�������ʣ�

	�����������DFS��ջstack���ܹ���
			һ���ڵ�pn������
			�� �ýڵ��һϵ�е�1����ڵ㱻ѹ��ջ��ջ���ڵ㡪������һϵ�нڵ�����һ��������ջ�������ʣ�
			�� �����ջ���ڵ��һϵ��1����ڵ㱻ѹ��ջ��ջ���ڵ��ջ�������ʣ�
			*	ջ�ṹ�͵ݹ���ܹ����������������ͨ������дΪ�ݹ���ʽ��
			
*/
template <typename T, typename Func>
void traverseGraph(Graph<T>& g, Func func, \
	const TRAVERSE_GRAPH_TYPE type = TRAVERSE_GRAPH_TYPE::depthFirst, \
	const bool skipNP = true)
{
	using GraphEdge = SLlistNode<GraphNode<T>*>;				// �ô洢����ָ�������ڵ�����ʾ�ߣ�

	GraphNode<T>* pnCurr = nullptr;
	GraphNode<T>* pnNbr = nullptr;
	const int nodesCount = g.nodeNum;
	std::unordered_set<GraphNode<T>*> visited; 
	std::stack<GraphNode<T>*> st;
	st.push(g.pnVec[0]);
	if(TRAVERSE_GRAPH_TYPE::depthFirst == type)
	{
		while (!st.empty())
		{
			pnCurr = st.top();
			st.pop();

			auto iter = visited.find(pnCurr);
			if (iter != visited.end())
				continue;
			if (iter == visited.end())
				visited.insert(pnCurr); 

			// 1. ���ʵ�ǰ���㣻
			func(pnCurr);

			// 2. ��ǰ����1�����ڵĶ���ѹ��ջ��
			traverseList(pnCurr->pFirstEdge, [&](GraphEdge* pe) 
				{
					pnNbr = pe->val;
					if (visited.end() == visited.find(pnNbr))			// δ���ʹ��Ķ���ѹ��ջ��
						st.push(pnNbr);
				});
		} 
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
 

// �����ʾ����ά����ͼת��ΪGraph��ʾ����to be completed;
template <typename T>
bool getGraph3D(Graph3D& g, const std::vector<TRIANGLE_MESH::triplet<T>>& poses, \
	const std::vector<edgeI>& edges)
{



	return true;
}

 

////////////////////////////////////////////////////////////////////////////////////////////// ����任��
template <typename TVO, typename TVI>
bool triMesh2Graph(Graph<TRIANGLE_MESH::triplet<TVO>>& g, \
	const TRIANGLE_MESH::triMesh<TVI, int>& mesh) 
{
	using verO = TRIANGLE_MESH::triplet<TVO>;
	const int versCount = mesh.vertices.size();
	const int trisCount = mesh.triangles.size();
	std::vector<verO> versTmp(versCount);
	for (int i = 0; i < versCount; ++i)
		versTmp[i] = mesh.vertices[i].cast<TVO>();

	g = Graph<verO>{versTmp};
	for (const auto& t : mesh.triangles)
	{
		g.addEdge(t.x, t.y);
		g.addEdge(t.y, t.z);
		g.addEdge(t.z, t.x);
	}

	return true;
}


template <typename TVO, typename TVI>
bool graph2Array(std::vector<TRIANGLE_MESH::triplet<TVO>>& vers, \
	std::vector<edgeI>& edges, const Graph<TRIANGLE_MESH::triplet<TVI>>& g) 
{
	using verO = TRIANGLE_MESH::triplet<TVO>;
	using GraphEdge = SLlistNode<GraphNode<TRIANGLE_MESH::triplet<TVI>>*>;			// �ô洢����ָ�������ڵ�����ʾ�ߣ�
	const int n = static_cast<int>(g.pnVec.size());
	if (n <= 0)
		return false;
	vers.clear();
	edges.clear();
	vers.reserve(n);
	edges.reserve(n * (n - 1));					// n���ڵ������ͼ����n*(n -1)���ߣ�

	// 1. ����ͼ�ڵ�-�ڵ�����ӳ���
	std::unordered_map<GraphNode<TRIANGLE_MESH::triplet<TVI>>*, int> map;
	for (int i = 0; i < g.pnVec.size(); ++i)
		map.insert(std::make_pair(g.pnVec[i], i));

	// 2. ���������ʾ�Ķ��㡢�����ݣ�
	for (const auto& pn : g.pnVec)
	{
		vers.push_back(pn->val.cast<TVO>());
		if (nullptr == pn->pFirstEdge)
			continue;
		int vaIdx = map[pn];			// ��ǰ�����������
		traverseList(pn->pFirstEdge, [&map, &edges, vaIdx](GraphEdge* pe)
			{
				if (nullptr == pe)
					return;
				int vbIdx = map[pe->val];
				edges.push_back(edgeI(vaIdx, vbIdx));
			});
	}
	edges.shrink_to_fit();
	 
	return true;
}


// ��ά���궥��ͼд�뵽OBJ�ļ��С���to be completed;
template <typename T>
bool objWriteGraph3D(const char* fileName, const Graph<TRIANGLE_MESH::triplet<T>>& g)
{
	std::vector<verF> vers;
	std::vector<edgeI> edges;
	if (!graph2Array(vers, edges, g))
		return false;
	writeOBJ(fileName, vers, edges);

	return true;
}


// Double��ʾ�ı�����ת��Ϊstd::vector<int>��ʾ���ڽӱ� 
template <typename TI>
bool edges2vvList(std::vector<std::vector<int>>& vvList,\
	const std::vector<TRIANGLE_MESH::doublet<TI>>& edges) 
{
	vvList.clear();
	std::vector<TI> tmpVec;
	int n = 0;
	int index = 0;
	tmpVec.reserve(2 * edges.size());
	for (const auto& e : edges)
	{
		tmpVec.push_back(e.x);
		tmpVec.push_back(e.y);
	}

	n = static_cast<int>(std::max(tmpVec.begin(), tmpVec.end()));
	vvList.resize(n);
	for (const auto& e : edges)
	{
		index = static_cast<int>(e.x);
		vvList[index].push_back(static_cast<int>(e.y));
	} 
 
	return true;
}


////////////////////////////////////////////////////////////////////////////////////////////// ���Ժ�����
namespace GRAPH
{
	void test0();
	void test00();
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