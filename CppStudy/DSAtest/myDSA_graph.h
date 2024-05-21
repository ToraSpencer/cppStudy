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
 
// 目录
/*
	基本类型定义
	表象变换
	Traverse methods
	Create methods
	Read methods
	Update methods
	Delete methods
	最小支撑树相关
	最短路径相关
*/




/////////////////////////////////////////////////////////////////////////////////////////////////////////////// 基本类型定义

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
	T val;											// 节点值
	GraphEdge* pFirstEdge;				// 邻接边链表的首个结点的指针；

public:
	GraphNode():val(0), pFirstEdge(nullptr) {}
	GraphNode(const T val0, GraphEdge* pe0 = nullptr)\
		:val(val0), pFirstEdge(pe0) {}
}; 


// Graph类——基于邻接表的图类（可以是有向图也可以是无向图）
template<typename T>
struct Graph 
{
	using GraphEdge = SLlistNode<GraphNode<T>*>;		// 用存储顶点指针的链表节点来表示边；

public:
	int nodeNum, nodeMaxNum, edgeNum;				// 节点数目、允许的顶点最大数目和边数
	std::vector<GraphNode<T>*> pnVec;					// 节点指针数组；
	bool isDigraph;														// 是否是有向图，默认情形下是；

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


	// 拷贝构造函数（深拷贝）
	Graph(const Graph& g) :nodeNum(g.nodeNum), \
		nodeMaxNum(g.nodeMaxNum), edgeNum(g.edgeNum)			 
	{		 
		std::unordered_map<GraphNode<T>*, GraphNode<T>*> map;	// 老-新顶点指针的映射表；
		
		// 1. 深拷贝顶点，生成老-新顶点指针的映射表；
		this->pnVec.resize(nodeNum);
		for (int i = 0; i < nodeNum; ++i)
		{
			this->pnVec[i] = new GraphNode<T>(g.pnVec[i]->val);
			map.insert(std::make_pair(g.pnVec[i], this->pnVec[i]));
		}

		// 2. 生成边数据：
		GraphNode<T>* pnOld = nullptr;
		GraphNode<T>* pnNew = nullptr;
		GraphNode<T>* pnConn = nullptr;
		for (int i = 0; i < nodeNum; ++i)
		{
			pnOld = g.pnVec[i];
			pnNew = this->pnVec[i];
			traverseList(pnOld->pFirstEdge, [&](GraphEdge* pe) 
				{
					pnConn = map[pe->val];		// 老的顶点索引映射成新的；
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

	// 插入一条有向边
	GraphEdge* addEdge(const int vaIdx, const int vbIdx) 
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
		GraphEdge* peRet = nullptr;

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

	// 插入一条无向边（to be completed）
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

		// 1. 深拷贝顶点，生成老-新顶点指针的映射表；
		std::unordered_map<GraphNode<T>*, GraphNode<T>*> map;	// 老-新顶点指针的映射表；
		this->pnVec.resize(nodeNum);
		for (int i = 0; i < nodeNum; ++i)
		{
			this->pnVec[i] = new GraphNode<T>(g.pnVec[i]->val);
			map.insert(std::make_pair(g.pnVec[i], this->pnVec[i]));
		}

		// 2. 生成边数据：
		GraphNode<T>* pnOld = nullptr;
		GraphNode<T>* pnNew = nullptr;
		GraphNode<T>* pnConn = nullptr;
		for (int i = 0; i < nodeNum; ++i)
		{
			pnOld = g.pnVec[i];
			pnNew = this->pnVec[i];
			traverseList(pnOld->pFirstEdge, [&](GraphEdge* pe)
				{
					pnConn = map[pe->val];		// 老的顶点索引映射成新的；
					pnNew->pFirstEdge->append(pnConn);
				});
		}

		return *this;
	}
};
using Graph3D = Graph<verF>;						// 三维点云构成的图




/////////////////////////////////////////////////////////////////////////////////////////////////////////////// 表象变换

// 三角网格 → 图（to be completed）
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
	using GraphEdge = SLlistNode<GraphNode<TRIANGLE_MESH::triplet<TVI>>*>;			// 用存储顶点指针的链表节点来表示边；
	const int n = static_cast<int>(g.pnVec.size());
	if (n <= 0)
		return false;
	vers.clear();
	edges.clear();
	vers.reserve(n);
	edges.reserve(n * (n - 1));					// n个节点的有向图多有n*(n -1)条边；

	// 1. 建立图节点-节点索引映射表：
	std::unordered_map<GraphNode<TRIANGLE_MESH::triplet<TVI>>*, int> map;
	for (int i = 0; i < g.pnVec.size(); ++i)
		map.insert(std::make_pair(g.pnVec[i], i));

	// 2. 生成数组表示的顶点、边数据：
	for (const auto& pn : g.pnVec)
	{
		vers.push_back(pn->val.cast<TVO>());
		if (nullptr == pn->pFirstEdge)
			continue;
		int vaIdx = map[pn];			// 当前顶点的索引；
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


// 三维坐标顶点图写入到OBJ文件中 
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


// Double表示的边数据转换为std::vector<std::vector<int>>表示的邻接表 
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

	// 1. 确定节点数
	for (const auto& e : edges)
	{
		tmpVec.push_back(e.x);
		tmpVec.push_back(e.y);
	}
	n = static_cast<int>(*std::max_element(tmpVec.begin(), tmpVec.end())) + 1;

	// 2. 生成邻接表：
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


// std::vector<std::vector<int>>表示的边数据转换为std::vector<std::vector<int>>表示的邻接表 
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

	// 1. 确定节点数
	for (const auto& e : edges)
	{
		tmpVec.push_back(e[0]);
		tmpVec.push_back(e[1]);
	}
	n = static_cast<int>(*std::max_element(tmpVec.begin(), tmpVec.end())) + 1;

	// 2. 生成邻接表：
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


// 数组表示的三维点云图转换为Graph表示——to be completed;
template <typename T>
bool getGraph3D(Graph3D& g, const std::vector<TRIANGLE_MESH::triplet<T>>& poses, \
	const std::vector<edgeI>& edges)
{



	return true;
}




/////////////////////////////////////////////////////////////////////////////////////////////////////////////// Traverse methods

// 遍历（搜索）图(to be completed)
/*
 	广度优先搜索BFS和队列queue紧密关联
			一个节点pn被访问
			→ 该节点的一系列1领域节点被压入队列，逐个访问
			→ 上述一系列顶点的1领域节点——即pn的2领域节点——被压入队列，逐个访问；

	深度优先搜索DFS和栈stack紧密关联
			一个节点pn被访问
			→ 该节点的一系列的1领域节点被压入栈，栈顶节点——即这一系列节点的最后一个——出栈、被访问；
			→ 上面的栈顶节点的一系列1领域节点被压入栈，栈顶节点出栈、被访问；
			*	栈结构和递归紧密关联，深度优先搜索通常可以写为递归形式；
			
	每个节点应该有四种状态(
			NOT FOUND, -1								未被发现，即未进入过收集容器（栈或队列）；				
			FOUND		, 0									已被发现，即进入过收集容器（栈或队列）；		
			SEARCHED	, 1									已完成对该节点关联信息的搜索，即不仅该节点已被发现，其关联的节点也都已经被发现；
			VISITED		, 2									已完成对该节点的访问，即已使用func()函数子作用过该节点；一般先从收集容器中弹出该节点再访问；
			);				
*/
template <typename T, typename Func>
void traverseGraph(Graph<T>& g, Func func, \
	const TRAVERSE_GRAPH_TYPE type = TRAVERSE_GRAPH_TYPE::depthFirst, \
	const bool skipNP = true)
{
	using GraphEdge = SLlistNode<GraphNode<T>*>;				// 用存储顶点指针的链表节点来表示边；

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

			// 1. 访问当前顶点；
			func(pnCurr);

			// 2. 当前顶点1领域内的顶点压入栈：
			traverseList(pnCurr->pFirstEdge, [&](GraphEdge* pe) 
				{
					pnNbr = pe->val;
					if (visited.end() == visited.find(pnNbr))			// 未访问过的顶点压入栈；
						st.push(pnNbr);
				});
		} 
	}
}




/////////////////////////////////////////////////////////////////////////////////////////////////////////////// Create methods




/////////////////////////////////////////////////////////////////////////////////////////////////////////////// Read methods

// 控制台上打印图顶点的信息
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



/////////////////////////////////////////////////////////////////////////////////////////////////////////////// 最小支撑树相关
/*
	最小支撑树（Minimum Spanning Tree, MST）
		通常只限于无向图；有向图的生成最小支撑树会很复杂；
		Kruskal算法和Prim算法都是解决最小生成树问题的经典算法，但它们的实现方式和思想有所不同。
		
		Kruskal算法：
			基于边的角度来构建最小生成树。
			它先将所有边按照权重排序，然后依次考虑每条边，如果该边不会形成环路，就将其添加到最小生成树中。
		
		Prim算法：
			基于节点的角度来构建最小生成树。
			它从一个初始节点开始，逐步地向最小生成树中添加节点和边，每次选择与当前最小生成树相连的边中权重最小的那条边所连接的节点，直到所有节点都被包含在最小生成树中。
		
		数据结构：
			Kruskal算法通常使用并查集（Union-Find）数据结构来判断两个节点是否在同一棵树中，以及是否会形成环路。
			Prim算法通常使用优先队列（Priority Queue）来维护当前最小生成树和其余节点之间的边，以便快速找到权重最小的边。
		
		时间复杂度：
			Kruskal算法的时间复杂度通常为O(ElogE)，其中E是边的数量。
			Prim算法的时间复杂度通常为O(V^2) 或 O(ElogV)，其中V是节点的数量，E是边的数量。
					在稀疏图（边的数量接近节点数量）中，Prim算法的效率更高；
					而在稠密图（边的数量接近节点数量的平方）中，Kruskal算法的效率可能更高。
		
		总的来说，Kruskal算法和Prim算法都是有效的最小生成树算法，选择哪种算法取决于具体的应用场景、图的规模以及图的特点。

*/



/////////////////////////////////////////////////////////////////////////////////////////////////////////////// 最短路径相关
/*
	Dijkstra算法是一种用于在加权图中寻找从一个节点到另一个节点的最短路径的算法。
			它由荷兰计算机科学家Edsger W. Dijkstra于1956年提出。

			基本步骤：
					1. 初始化：首先，将起始节点标记为距离为0，其他节点的距离标记为无穷大。
								同时，设置一个集合用于存放已经找到最短路径的节点，初始为空。
					2. 选择最短路径节点：从未标记的节点中选择一个距离最小的节点，并将其标记为已访问。
					3. 更新距离：对于与已访问节点相邻的未访问节点，计算通过当前节点到达它们的距离。
								如果通过当前节点到达它们的距离比它们原有的距离更短，就更新它们的距离。
					4. 重复：重复步骤2和步骤3，直到所有节点都被标记为已访问，或者目标节点的距离已经确定。
					5. 输出最短路径：通过记录每个节点的前驱节点，可以回溯构建出从起始节点到目标节点的最短路径。

			Dijkstra算法适用于没有负权边的图。它保证了每个节点的距离标记在算法结束时都是最短路径的长度。
					然而，如果图中存在负权边，Dijkstra算法可能会导致错误的结果，此时应该使用Bellman-Ford算法或其他更适合的算法。

			总的来说，Dijkstra算法是一种非常常用且有效的最短路径算法，用于解决许多实际问题，比如网络路由、GPS导航等。

*/



////////////////////////////////////////////////////////////////////////////////////////////// 测试函数：
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