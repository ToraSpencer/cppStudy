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
 
// Ŀ¼
/*
	�������Ͷ���
	����任
	Traverse methods
	Create methods
	Read methods
	Update methods
	Delete methods
	��С֧�������
	���·�����
*/




/////////////////////////////////////////////////////////////////////////////////////////////////////////////// �������Ͷ���

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


// Graph�ࡪ�������ڽӱ��ͼ�ࣨ����������ͼҲ����������ͼ��
template<typename T>
struct Graph 
{
	using GraphEdge = SLlistNode<GraphNode<T>*>;		// �ô洢����ָ�������ڵ�����ʾ�ߣ�

public:
	int nodeNum, nodeMaxNum, edgeNum;				// �ڵ���Ŀ������Ķ��������Ŀ�ͱ���
	std::vector<GraphNode<T>*> pnVec;					// �ڵ�ָ�����飻
	bool isDigraph;														// �Ƿ�������ͼ��Ĭ���������ǣ�

public:

// constructor and destructor
	Graph(const bool isDigraph = true) :nodeNum(0), nodeMaxNum(DEFAULT_SIZE), edgeNum(0), isDigraph(isDigraph) {}
	Graph(const std::initializer_list<T>& ilist, const bool isDigraph = true)
	{
		this->nodeNum = ilist.size();
		this->nodeMaxNum = DEFAULT_SIZE;
		this->edgeNum = 0;
		this->isDigraph = isDigraph;
		this->pnVec.reserve(ilist.size());
		for (const auto& elem : ilist)
			pnVec.push_back(new GraphNode<T>(elem)); 
	}
	Graph(const std::vector<T>& vec, const bool isDigraph = true)
	{
		this->nodeNum = vec.size();
		this->nodeMaxNum = DEFAULT_SIZE;
		this->edgeNum = 0;
		this->isDigraph = isDigraph;
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

	// ����һ�������
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
		GraphEdge* peRet = nullptr;

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

	// ����һ������ߣ�to be completed��
	GraphEdge* addUndiEdge(const int vaIdx, const int vbIdx)
	{
		return nullptr;
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




/////////////////////////////////////////////////////////////////////////////////////////////////////////////// ����任

// �������� �� ͼ��to be completed��
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

	g = Graph<verO>{ versTmp };
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


// ��ά���궥��ͼд�뵽OBJ�ļ��� 
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


// Double��ʾ�ı�����ת��Ϊstd::vector<std::vector<int>>��ʾ���ڽӱ� 
template <typename TI>
bool edges2vvList(std::vector<std::vector<int>>& vvList, \
	const std::vector<TRIANGLE_MESH::doublet<TI>>& edges, const bool isDigraph = true)
{
	vvList.clear();
	std::vector<TI> tmpVec;
	int n = 0;
	int vaIdx = 0;
	int vbIdx = 0;
	tmpVec.reserve(2 * edges.size());

	// 1. ȷ���ڵ���
	for (const auto& e : edges)
	{
		tmpVec.push_back(e.x);
		tmpVec.push_back(e.y);
	}
	n = static_cast<int>(*std::max_element(tmpVec.begin(), tmpVec.end())) + 1;

	// 2. �����ڽӱ�
	vvList.resize(n);
	for (const auto& e : edges)
	{
		vaIdx = static_cast<int>(e.x);
		vbIdx = static_cast<int>(e.y);
		vvList[vaIdx].push_back(vbIdx);
		if (!isDigraph)
			vvList[vbIdx].push_back(vaIdx);
	}

	return true;
}


// std::vector<std::vector<int>>��ʾ�ı�����ת��Ϊstd::vector<std::vector<int>>��ʾ���ڽӱ� 
template <typename TI>
bool vvEdges2vvList(std::vector<std::vector<int>>& vvList, \
	const std::vector<std::vector<TI>>& edges, const bool isDigraph = true)
{
	vvList.clear();
	std::vector<TI> tmpVec;
	int n = 0;
	int vaIdx = 0;
	int vbIdx = 0;
	tmpVec.reserve(2 * edges.size());

	// 1. ȷ���ڵ���
	for (const auto& e : edges)
	{
		tmpVec.push_back(e[0]);
		tmpVec.push_back(e[1]);
	}
	n = static_cast<int>(*std::max_element(tmpVec.begin(), tmpVec.end())) + 1;

	// 2. �����ڽӱ�
	vvList.resize(n);
	for (const auto& e : edges)
	{
		vaIdx = static_cast<int>(e[0]);
		vbIdx = static_cast<int>(e[1]);
		vvList[vaIdx].push_back(vbIdx);
		if (!isDigraph)
			vvList[vbIdx].push_back(vaIdx);
	}

	return true;
}


// �����ʾ����ά����ͼת��ΪGraph��ʾ����to be completed;
template <typename T>
bool getGraph3D(Graph3D& g, const std::vector<TRIANGLE_MESH::triplet<T>>& poses, \
	const std::vector<edgeI>& edges)
{



	return true;
}




/////////////////////////////////////////////////////////////////////////////////////////////////////////////// Traverse methods

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
			
	ÿ���ڵ�Ӧ��������״̬(
			NOT FOUND, -1								δ�����֣���δ������ռ�������ջ����У���				
			FOUND		, 0									�ѱ����֣���������ռ�������ջ����У���		
			SEARCHED	, 1									����ɶԸýڵ������Ϣ���������������ýڵ��ѱ����֣�������Ľڵ�Ҳ���Ѿ������֣�
			VISITED		, 2									����ɶԸýڵ�ķ��ʣ�����ʹ��func()���������ù��ýڵ㣻һ���ȴ��ռ������е����ýڵ��ٷ��ʣ�
			);				
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




/////////////////////////////////////////////////////////////////////////////////////////////////////////////// Create methods




/////////////////////////////////////////////////////////////////////////////////////////////////////////////// Read methods

// ����̨�ϴ�ӡͼ�������Ϣ
template <typename T>
static auto dispGraphNode = [](const GraphNode<T>* ptrNode)
{
	if (nullptr == ptrNode)
		std::cout << "placeholder, ";
	else
		std::cout << ptrNode->val << ", ";
};




/////////////////////////////////////////////////////////////////////////////////////////////////////////////// Update methods



/////////////////////////////////////////////////////////////////////////////////////////////////////////////// Delete methods



/////////////////////////////////////////////////////////////////////////////////////////////////////////////// ��С֧�������
/*
	��С֧������Minimum Spanning Tree, MST��
		ͨ��ֻ��������ͼ������ͼ��������С֧������ܸ��ӣ�
		Kruskal�㷨��Prim�㷨���ǽ����С����������ľ����㷨�������ǵ�ʵ�ַ�ʽ��˼��������ͬ��
		
		Kruskal�㷨��
			���ڱߵĽǶ���������С��������
			���Ƚ����б߰���Ȩ������Ȼ�����ο���ÿ���ߣ�����ñ߲����γɻ�·���ͽ�����ӵ���С�������С�
		
		Prim�㷨��
			���ڽڵ�ĽǶ���������С��������
			����һ����ʼ�ڵ㿪ʼ���𲽵�����С����������ӽڵ�ͱߣ�ÿ��ѡ���뵱ǰ��С�����������ı���Ȩ����С�������������ӵĽڵ㣬ֱ�����нڵ㶼����������С�������С�
		
		���ݽṹ��
			Kruskal�㷨ͨ��ʹ�ò��鼯��Union-Find�����ݽṹ���ж������ڵ��Ƿ���ͬһ�����У��Լ��Ƿ���γɻ�·��
			Prim�㷨ͨ��ʹ�����ȶ��У�Priority Queue����ά����ǰ��С������������ڵ�֮��ıߣ��Ա�����ҵ�Ȩ����С�ıߡ�
		
		ʱ�临�Ӷȣ�
			Kruskal�㷨��ʱ�临�Ӷ�ͨ��ΪO(ElogE)������E�Ǳߵ�������
			Prim�㷨��ʱ�临�Ӷ�ͨ��ΪO(V^2) �� O(ElogV)������V�ǽڵ��������E�Ǳߵ�������
					��ϡ��ͼ���ߵ������ӽ��ڵ��������У�Prim�㷨��Ч�ʸ��ߣ�
					���ڳ���ͼ���ߵ������ӽ��ڵ�������ƽ�����У�Kruskal�㷨��Ч�ʿ��ܸ��ߡ�
		
		�ܵ���˵��Kruskal�㷨��Prim�㷨������Ч����С�������㷨��ѡ�������㷨ȡ���ھ����Ӧ�ó�����ͼ�Ĺ�ģ�Լ�ͼ���ص㡣

*/



/////////////////////////////////////////////////////////////////////////////////////////////////////////////// ���·�����
/*
	Dijkstra�㷨��һ�������ڼ�Ȩͼ��Ѱ�Ҵ�һ���ڵ㵽��һ���ڵ�����·�����㷨��
			���ɺ����������ѧ��Edsger W. Dijkstra��1956�������

			�������裺
					1. ��ʼ�������ȣ�����ʼ�ڵ���Ϊ����Ϊ0�������ڵ�ľ�����Ϊ�����
								ͬʱ������һ���������ڴ���Ѿ��ҵ����·���Ľڵ㣬��ʼΪ�ա�
					2. ѡ�����·���ڵ㣺��δ��ǵĽڵ���ѡ��һ��������С�Ľڵ㣬��������Ϊ�ѷ��ʡ�
					3. ���¾��룺�������ѷ��ʽڵ����ڵ�δ���ʽڵ㣬����ͨ����ǰ�ڵ㵽�����ǵľ��롣
								���ͨ����ǰ�ڵ㵽�����ǵľ��������ԭ�еľ�����̣��͸������ǵľ��롣
					4. �ظ����ظ�����2�Ͳ���3��ֱ�����нڵ㶼�����Ϊ�ѷ��ʣ�����Ŀ��ڵ�ľ����Ѿ�ȷ����
					5. ������·����ͨ����¼ÿ���ڵ��ǰ���ڵ㣬���Ի��ݹ���������ʼ�ڵ㵽Ŀ��ڵ�����·����

			Dijkstra�㷨������û�и�Ȩ�ߵ�ͼ������֤��ÿ���ڵ�ľ��������㷨����ʱ�������·���ĳ��ȡ�
					Ȼ�������ͼ�д��ڸ�Ȩ�ߣ�Dijkstra�㷨���ܻᵼ�´���Ľ������ʱӦ��ʹ��Bellman-Ford�㷨���������ʺϵ��㷨��

			�ܵ���˵��Dijkstra�㷨��һ�ַǳ���������Ч�����·���㷨�����ڽ�����ʵ�����⣬��������·�ɡ�GPS�����ȡ�

*/



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