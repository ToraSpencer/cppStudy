#pragma once

#include "basicTools/basicTools.h"

using std::cout;
using std::endl;


////////////////////////////////////////////////////////////////////////////////////////////////// 前置声明
template <class ElemType>
class AdjMatrixUndirGraph;

template <class ElemType, class WeightType>
class AdjMatrixUndirNetwork;

template <class ElemType>
struct AdjListGraphVex;

struct AdjListGraphArc;

template <class ElemType>
class AdjListDirGraph;


////////////////////////////////////////////////////////////////////////////////////////////////// 类声明

struct DSA_graph_module : public virtualModule
{
protected:
	DSA_graph_module() = default;

public:
	static virtualModule* getInstance();
	virtual void test0();
	virtual void test1();
	virtual void test2();
	virtual void test3();
	virtual void test4();
	virtual void test5();
	virtual void test6();
};


// 无向图类模板(邻接矩阵表示，undirected graph with adjacent matrix form)
template <class ElemType>
class AdjMatrixUndirGraph
{
protected:
	int vexNum, vexMaxNum, arcNum;			// 顶点数目、允许的顶点最大数目和边数
	int **arcs;							    // 边信息邻接矩阵——是一个二维数组
	ElemType *vertexes;						// 顶点信息的数组——是一个一维数组
	mutable Status *tag;					// 标志数组

public:
	AdjMatrixUndirGraph(ElemType es[], int vertexNum, int vertexMaxNum = DEFAULT_SIZE);		// 数组es[]为顶点,顶点个数为vertexNum,允许的顶点最大数目为vertexMaxNum,边数为0
	AdjMatrixUndirGraph(int vertexMaxNum = DEFAULT_SIZE);
	AdjMatrixUndirGraph(const AdjMatrixUndirGraph<ElemType> &g);	 
	~AdjMatrixUndirGraph();

	void Clear();			              	 
	bool IsEmpty();               
	int GetOrder(ElemType &d) const;				// 求顶点的索引	
	Status GetElem(int v, ElemType &d) const;		// 求顶点的元素值	
	Status SetElem(int v, const ElemType &d);		// 设置顶点的元素值
	int GetVexNum() const;						// 返回顶点个数			 
	int GetArcNum() const;						// 返回边数			 
	int FirstAdjVex(int v) const;				// 返回顶点v的第一个邻接点			 
	int NextAdjVex(int v1, int v2) const;		 // 返回顶点v1的相对于v2的下一个邻接点			 
	void InsertVex(const ElemType &d);			 // 插入元素值为d的顶点		 
	void InsertArc(int v1, int v2);			     // 插入顶点为v1和v2的边			 
	void DeleteVex(const ElemType &d);			 // 删除元素值为d的顶点			 
	void DeleteArc(int v1, int v2);			     // 删除顶点为v1和v2的边			 
	Status GetTag(int v) const;			         // 返回顶点v的标志		 
	void SetTag(int v, Status val) const;			 // 设置顶点v的标志为val		 
	void Display();									// 打印无向图的邻接矩阵
	AdjMatrixUndirGraph<ElemType> &operator =(const AdjMatrixUndirGraph<ElemType> &g);
};


// 无向网（即有权图）（邻接矩阵表示）
template <class ElemType, class WeightType>
class AdjMatrixUndirNetwork
{
protected:
	// 邻接矩阵的数据成员:
	int vexNum, vexMaxNum, edgeNum;			// 顶点数目、允许的顶点最大数目和边数
	int **arcs;							// 存放边信息邻接矩阵
	ElemType *vertexes;						// 存放顶点信息的数组 
	Status *tag;							// 标志数组
	WeightType infinity;					// 无穷大

public:
	// 邻接矩阵类型的方法声明:
	AdjMatrixUndirNetwork(ElemType es[], int vertexNum, int vertexMaxNum = DEFAULT_SIZE,
		WeightType infinit = (WeightType)DEFAULT_INFINITY);
	// 以数组es[]为顶点,顶点个数为vertexNum,允许的顶点最大数目为vertexMaxNum,边数为0的无向图
	AdjMatrixUndirNetwork(int vertexMaxNum = DEFAULT_SIZE, WeightType infinit = (WeightType)DEFAULT_INFINITY);
	// 构造允许的顶点最大数目为vertexMaxNum,边数为0的无向图
	~AdjMatrixUndirNetwork();					// 析构函数
	void Clear();			              // 清空图			 
	bool IsEmpty();                 // 判断无向图是否为空 
	int GetOrder(ElemType &e) const;// 求顶点的序号	
	Status GetElem(int v, ElemType &e) const;// 求顶点的元素值	
	Status SetElem(int v, const ElemType &e);// 设置顶点的元素值
	WeightType GetInfinity() const;				// 返回无穷大			 
	int GetVexNum() const;					// 返回顶点个数			 
	int GetEdgeNum() const;					// 返回边数			 
	int FirstAdjVex(int v) const;		// 返回顶点v的第一个邻接点			 
	int NextAdjVex(int v1, int v2) const;		 // 返回顶点v1的相对于v2的下一个邻接点			 
	void InsertVex(const ElemType &e);			 // 插入元素值为e的顶点		 
	void DeleteVex(const ElemType &e);			 // 删除元素值为e的顶点			 
	void InsertArc(int v1, int v2, WeightType w);	// 插入顶点为v1和v2,权为w的边			 
	void DeleteArc(int v1, int v2);			// 删除顶点为v1和v2的边			 
	WeightType GetWeight(int v1, int v2) const;	// 返回顶点为v1和v2的边的权值
	Status GetTag(int v) const;			         // 返回顶点v的标志		 
	void SetTag(int v, Status val) const;	   // 设置顶点v的标志为val		 
	AdjMatrixUndirNetwork(const AdjMatrixUndirNetwork<ElemType, WeightType> &g);	// 复制构造函数
	AdjMatrixUndirNetwork<ElemType, WeightType> &operator =(const AdjMatrixUndirNetwork<ElemType, WeightType> &g);
	// 赋值语句重载
	void Display();	                         // 显示邻接矩阵无向图
};


// 有向图顶点类模板（邻接表表示）————类似于一个链表节点
template <class ElemType>
struct AdjListGraphVex
{
	ElemType data;						// 顶点的值
	AdjListGraphArc* firstArc;			// 指向邻接链表边结点的指针

	AdjListGraphVex();
	AdjListGraphVex(ElemType val, AdjListGraphArc *adj = NULL);

};


// 有向图边类模板（邻接表表示）
struct AdjListGraphArc
{
	// 数据成员:
	int adjVex;							// 该有向边指向的顶点的索引。
	AdjListGraphArc *nextArc;			// 下一条相邻边结点的指针，一条边链表表示了某一个顶点的所有邻边。
							  
	AdjListGraphArc();					// 无参数的构造函数
	AdjListGraphArc(int v, AdjListGraphArc * next = NULL);
};


// 有向图类模板（邻接表表示）——图顶点很多边很少时，邻接矩阵会很稀疏，浪费空间。
template <class ElemType>
class AdjListDirGraph
{
//protected:
public:
	int vexNum, vexMaxNum, arcNum;			// 顶点数目、允许的顶点最大数目和边数
	AdjListGraphVex<ElemType> *vexTable;	// 顶点表——一维数组，每个数组元素实际上是一条链表
	mutable Status *tag;			        // 标志数组				

public:
	AdjListDirGraph(ElemType es[], int vertexNum, int vertexMaxNum = DEFAULT_SIZE);
	AdjListDirGraph(int vertexMaxNum = DEFAULT_SIZE);
	AdjListDirGraph(const AdjListDirGraph<ElemType> &g);
	~AdjListDirGraph();


	bool IsEmpty();
	int GetOrder(ElemType &e) const;            // 求顶点e的索引	
	Status GetElem(int v, ElemType &e) const;
	int GetVexNum() const;						 	 
	int GetArcNum() const;						// 求有向图的边数个数			 
	int FirstAdjVex(int v) const;				// 返回索引为v的顶点的第一个邻接点		 
	int NextAdjVex(int v1, int v2) const;		// 求有向图中顶点v1的相对于v2的下一个邻接点		
	Status GetTag(int v) const;				    // 求顶点v的标志	
	Status GetRevAdjList(AdjListDirGraph<ElemType>& list) const;		// 得到此邻接表的逆邻接表

	Status InsertVex(const ElemType &e);		// 插入元素值为e的顶点		 
	void InsertArc(int v1, int v2);				// 插入从顶点v1到v2的边			 
	void DeleteVex(const ElemType &e);			// 删除元素值为e的顶点			 
	void DeleteArc(int v1, int v2);			    // 删除从顶点为v1到v2的边			 
	
	void Clear();
	Status SetElem(int v, const ElemType& e);
	void SetTag(int v, Status tag) const;	    // 设置顶点v的标志为tag	 
	AdjListDirGraph<ElemType> &operator = (const AdjListDirGraph<ElemType> &g); // 重载赋值运算符 
	void Display();								// 打印有向图的邻接表 
	bool displayRow(const int index);							// 打印索引为Index的一条链表

};


// Kruskal边类
template <class ElemType, class WeightType>
class KruskalEdge
{
public:
	ElemType vertex1, vertex2;		// 边的顶点
	WeightType weight;				// 边的权值
	KruskalEdge(ElemType v1, ElemType v2, WeightType w);	// 构造函数
	KruskalEdge() {};	            // 构造函数
	KruskalEdge<ElemType, WeightType> &operator =(const KruskalEdge<ElemType, WeightType> &Ed); // 赋值语句重载
	bool operator <=(const KruskalEdge<ElemType, WeightType> &Ed);		// 重载<=关系运算 
	bool operator >(const KruskalEdge<ElemType, WeightType> &Ed);		// 重载>关系运算
};


// Prim算法中使用 
template <class ElemType, class WeightType>
struct CloseArcType
{
	WeightType lowweight;
	int nearvertex;
};

 

////////////////////////////////////////////////////////////////////////////////////////////////// 函数声明

// 图的广度优先(breadth firsts)遍历
template <class ElemType>
void BFSTraverse(const AdjMatrixUndirGraph<ElemType> &g, void(*Visit)(const ElemType &));


// 图的广度优先搜索(breadth first search)
template <class ElemType>
void BFS(const AdjMatrixUndirGraph<ElemType> &g, int v, void(*Visit)(const ElemType &));


// 图的深度优先(depth firsts)遍历
template <class ElemType>
void DFSTraverse(const AdjMatrixUndirGraph<ElemType> &g, void(*Visit)(const ElemType &));


// 图的深度优先搜索(depth firsts search)
template <class ElemType>
void DFS(const AdjMatrixUndirGraph<ElemType> &g, int v, void(*Visit)(const ElemType &));


// 用Kruskal算法构造网g的最小代价生成树
template <class ElemType, class WeightType>
void MiniSpanTreeKruskal(const AdjMatrixUndirNetwork<ElemType, WeightType> &g);


// 用Prim算法从u0出发构造网g的最小生成树
template <class ElemType, class WeightType>
void MiniSpanTreePrim(const AdjMatrixUndirNetwork<ElemType, WeightType> &g, int u0);


////////////////////////////////////////////////////////////////////////////////////////////////// 实现部分
template <class ElemType>
AdjMatrixUndirGraph<ElemType>::AdjMatrixUndirGraph(ElemType es[], int vertexNum, int vertexMaxNum)
// 操作结果：构造数据元素为es[],顶点个数为vertexNum,允许的顶点最大数目为vertexMaxNum,边数为0的无向图

{
	if (vertexMaxNum < 0)
		throw Error("允许的顶点最大数目不能为负!");        // 抛出异常

	if (vertexMaxNum < vertexNum)
		throw Error("顶点数目不能大于允许的顶点最大数目!");// 抛出异常

	vexNum = vertexNum;
	vexMaxNum = vertexMaxNum;
	arcNum = 0;

	vertexes = new ElemType[vexMaxNum];      // 生成生成顶点信息数组
	tag = new Status[vexMaxNum];			       // 生成标志数组
	arcs = (int **)new int *[vexMaxNum];     // 生成邻接矩阵
	for (int v = 0; v < vexMaxNum; v++)
		arcs[v] = new int[vexMaxNum];

	for (int v = 0; v < vexNum; v++) 
	{
		vertexes[v] = es[v];
		tag[v] = UNVISITED;
		for (int u = 0; u < vexNum; u++)
			arcs[v][u] = 0;
	}
}

template <class ElemType>
AdjMatrixUndirGraph<ElemType>::AdjMatrixUndirGraph(int vertexMaxNum)
// 操作结果：构造允许顶点的最大数目为vertexMaxNum的空无向图
{
	if (vertexMaxNum < 0)
		throw Error("允许的顶点最大数目不能为负!");// 抛出异常

	vexNum = 0;
	vexMaxNum = vertexMaxNum;
	arcNum = 0;

	vertexes = new ElemType[vexMaxNum];     // 生成生成顶点信息数组
	tag = new Status[vexMaxNum];			      // 生成标志数组
	arcs = (int **)new int *[vexMaxNum];    // 生成邻接矩阵
	for (int v = 0; v < vexMaxNum; v++)
		arcs[v] = new int[vexMaxNum];
}

template <class ElemType>
void AdjMatrixUndirGraph<ElemType>::Clear()
// 操作结果：把无向图的顶点数和边数设置为0.			 
{
	vexNum = 0;
	arcNum = 0;
}

template <class ElemType>
bool AdjMatrixUndirGraph<ElemType>::IsEmpty()
// 操作结果：如果无向图为空返回true,否则返回false.
{
	return vexNum == 0;
}

template <class ElemType>
AdjMatrixUndirGraph<ElemType>::~AdjMatrixUndirGraph()
// 操作结果：释放对象所占用的空间
{
	delete[]vertexes;					// 释放顶点数据
	delete[]tag;						    // 释放标志

	for (int v = 0; v < vexMaxNum; v++)	// 释放邻接矩阵的行
		delete[]arcs[v];
	delete[]arcs;					    // 释放邻接矩阵
}

template <class ElemType>
int AdjMatrixUndirGraph<ElemType>::GetOrder(ElemType &d) const
// 操作结果：求顶点d的序号.顶点的序号从0开始，图中不存在顶点d时，返回-1. 
{
	for (int v = 0; v < vexNum; v++)
		if (vertexes[v] == d)
			return v;	    // 顶点d存在,返回它的序号 
	return -1;	        // 顶点d不存在,返回-1
}

template <class ElemType>
Status AdjMatrixUndirGraph<ElemType>::GetElem(int v, ElemType &d) const
// 操作结果：求序号为v的顶点值, v的取值范围为0 ≤ v ＜ vexNum, v合法时函数
// 通过d取得顶点值，并返回ENTRY_FOUND；否则函数返回NOT_PRESENT
{
	if (v < 0 || v >= vexNum)
		return NOT_PRESENT;	// v范围错,返回元素不存在
	else {
		d = vertexes[v];	  // 将顶点v的元素值赋给d
		return ENTRY_FOUND;	// 返回元素存在
	}
}

template <class ElemType>
Status AdjMatrixUndirGraph<ElemType>::SetElem(int v, const ElemType &d)
// 操作结果：设置顶点的元素值v的取值范围为0 ≤ v ＜ vexNum, v合法时函数返回
//	SUCCESS, 否则函数返回RANGE_ERROR
{
	if (v < 0 || v >= vexNum)
		return RANGE_ERROR;	// v范围错,返回位置错
	else {
		vertexes[v] = d;		// 将顶点元素的值改为d 
		return SUCCESS;		  // 返回修改成功
	}
}


// 返回顶点个数	
template <class ElemType>
int AdjMatrixUndirGraph<ElemType>::GetVexNum() const
{
	return vexNum;
}

template <class ElemType>
int AdjMatrixUndirGraph<ElemType>::GetArcNum() const
// 操作结果：返回边数
{
	return arcNum;
}

// 返回顶点v的第1个邻接点的索引
template <class ElemType>
int AdjMatrixUndirGraph<ElemType>::FirstAdjVex(int v) const	 
{
	if (v < 0 || v >= vexNum)
		throw Error("v不合法!");		// 抛出异常

	for (int u = 0; u < vexNum; u++)
		if (arcs[v][u] != 0)
			return u;

	return -1;							// 返回-1表示无邻接点
}

template <class ElemType>
int AdjMatrixUndirGraph<ElemType>::NextAdjVex(int v1, int v2) const
// 操作结果：返回顶点v1的相对于v2的下一个邻接点			 
{
	if (v1 < 0 || v1 >= vexNum)
		throw Error("v1不合法!");	// 抛出异常
	if (v2 < 0 || v2 >= vexNum)
		throw Error("v2不合法!");	// 抛出异常
	if (v1 == v2) throw
		Error("v1不能等于v2!");		// 抛出异常

	for (int u = v2 + 1; u < vexNum; u++)
		if (arcs[v1][u] != 0)
			return u;

	return -1;						// 返回-1表示无下一个邻接点
}

template <class ElemType>
void AdjMatrixUndirGraph<ElemType>::InsertVex(const ElemType &d)		 
{
	if (vexNum == vexMaxNum)
		throw Error("图的顶点数不能超过允许的最大数!");	 

	vertexes[vexNum] = d;
	tag[vexNum] = UNVISITED;
	for (int v = 0; v <= vexNum; v++) 
	{
		arcs[vexNum][v] = 0;
		arcs[v][vexNum] = 0;
	}
	vexNum++;
}

template <class ElemType>
void AdjMatrixUndirGraph<ElemType>::InsertArc(int v1, int v2)
// 操作结果：插入依附顶点v1和v2的边			 
{
	if (v1 < 0 || v1 >= vexNum)
		throw Error("v1不合法!");	// 抛出异常
	if (v2 < 0 || v2 >= vexNum)
		throw Error("v2不合法!");	// 抛出异常
	if (v1 == v2)
		throw Error("v1不能等于v2!");// 抛出异常

	if (arcs[v1][v2] == 0) {	  // 原无向图中没有边(v1, v2) 
		arcNum++;
		arcs[v1][v2] = 1;
		arcs[v2][v1] = 1;
	}
}

template <class ElemType>
void AdjMatrixUndirGraph<ElemType>::DeleteVex(const ElemType &d)
// 操作结果：删除元素为d的顶点			 
{
	int v;
	for (v = 0; v < vexNum; v++)
		if (vertexes[v] == d)
			break;
	if (v == vexNum)
		throw Error("图中不存在要删除的顶点!");	// 抛出异常

	for (int u = 0; u < vexNum; u++)             // 删除与顶点d相关联的边 
		if (arcs[v][u] == 1) {
			arcNum--;
			arcs[v][u] = 0;
			arcs[u][v] = 0;
		}

	vexNum--;
	if (v < vexNum) {
		vertexes[v] = vertexes[vexNum];
		tag[v] = tag[vexNum];
		for (int u = 0; u <= vexNum; u++)
			arcs[v][u] = arcs[vexNum][u];
		for (int u = 0; u <= vexNum; u++)
			arcs[u][v] = arcs[u][vexNum];
	}
}

template <class ElemType>
void AdjMatrixUndirGraph<ElemType>::DeleteArc(int v1, int v2)
// 操作结果：删除依附顶点v1和v2的边			 
{
	if (v1 < 0 || v1 >= vexNum)
		throw Error("v1不合法!");	// 抛出异常
	if (v2 < 0 || v2 >= vexNum)
		throw Error("v2不合法!");	// 抛出异常
	if (v1 == v2)
		throw Error("v1不能等于v2!");// 抛出异常

	if (arcs[v1][v2] != 0) {	// 原无向图存在边(v1, v2)
		arcNum--;
		arcs[v1][v2] = 0;
		arcs[v2][v1] = 0;
	}
}

template <class ElemType>
Status AdjMatrixUndirGraph<ElemType>::GetTag(int v) const
// 操作结果：返回顶点v的标志		 
{
	if (v < 0 || v >= vexNum)
		throw Error("v不合法!");	// 抛出异常

	return tag[v];
}

template <class ElemType>
void AdjMatrixUndirGraph<ElemType>::SetTag(int v, Status val) const
// 操作结果：设置顶点v的标志为val		 
{
	if (v < 0 || v >= vexNum)
		throw Error("v不合法!");	// 抛出异常

	tag[v] = val;
}

template <class ElemType>
AdjMatrixUndirGraph<ElemType>::AdjMatrixUndirGraph(const AdjMatrixUndirGraph<ElemType> &g)
// 操作结果：由无向图的邻接矩阵g构造新无向图的邻接矩阵g——复制构造函数
{
	vexNum = g.vexNum;
	vexMaxNum = g.vexMaxNum;
	arcNum = g.arcNum;

	vertexes = new ElemType[vexMaxNum];		// 生成顶点数据数组
	tag = new Status[vexMaxNum];			// 生成标志数组
	arcs = (int **)new int *[vexMaxNum];	// 生成邻接矩阵
	for (int v = 0; v < vexMaxNum; v++)
		arcs[v] = new int[vexMaxNum];

	for (int v = 0; v < vexNum; v++) {	// 复制顶点数据数组
		vertexes[v] = g.vertexes[v];
		tag[v] = g.tag[v];
		for (int u = 0; u < vexNum; u++)
			arcs[v][u] = g.arcs[v][u];
	}
}

template <class ElemType>
AdjMatrixUndirGraph<ElemType> &AdjMatrixUndirGraph<ElemType>::operator =(const AdjMatrixUndirGraph<ElemType> &g)
// 操作结果：将无向图的邻接矩阵g赋值给当前无向图的邻接矩阵——赋值语句重载
{
	if (&g != this) {
		delete[]vertexes;				// 释放顶点数据
		delete[]tag;						  // 释放标志

		for (int v = 0; v < vexMaxNum; v++)	// 释放邻接矩阵的行
			delete[]arcs[v];
		delete[]arcs;					  // 释放邻接矩阵
		vexNum = g.vexNum;
		vexMaxNum = g.vexMaxNum;
		arcNum = g.arcNum;

		vertexes = new ElemType[vexMaxNum];	 // 生成顶点数据数组
		tag = new Status[vexMaxNum];			   // 生成标志数组
		arcs = (int **)new int *[vexMaxNum]; // 生成邻接矩阵
		for (int v = 0; v < vexMaxNum; v++)
			arcs[v] = new int[vexMaxNum];

		for (int v = 0; v < vexNum; v++) {	 // 复制顶点数据数组
			vertexes[v] = g.vertexes[v];
			tag[v] = g.tag[v];
			for (int u = 0; u < vexNum; u++)
				arcs[v][u] = g.arcs[v][u];
		}
	}
	return *this;
}

// 遍历打印无向图的邻接矩阵
template <class ElemType>
void AdjMatrixUndirGraph<ElemType>::Display()
{
	for (int v = 0; v < vexNum; v++)
		cout << "\t" << vertexes[v];
	cout << endl;

	for (int v = 0; v < vexNum; v++) 
	{
		cout << vertexes[v];
		for (int u = 0; u < vexNum; u++)
			cout << "\t" << arcs[v][u];
		cout << endl;
	}
}



template <class ElemType, class WeightType>
AdjMatrixUndirNetwork<ElemType, WeightType>::AdjMatrixUndirNetwork(ElemType es[], int vertexNum, int vertexMaxNum, WeightType infinit)
// 操作结果：构造数据元素为es[],顶点个数为vertexNum,允许的顶点最大数目为vertexMaxNum,边数为0的无向图
{
	if (vertexMaxNum < 0)
		throw Error("允许的顶点最大数目不能为负!");        // 抛出异常

	if (vertexMaxNum < vertexNum)
		throw Error("顶点数目不能大于允许的顶点最大数目!");// 抛出异常

	vexNum = vertexNum;
	vexMaxNum = vertexMaxNum;
	edgeNum = 0;
	infinity = infinit;

	vertexes = new ElemType[vexMaxNum];     	// 生成生成顶点信息数组
	tag = new Status[vexMaxNum];			 	// 生成标志数组
	arcs = (int **)new int *[vexMaxNum];     	// 生成邻接矩阵
	for (int v = 0; v < vexMaxNum; v++)
		arcs[v] = new int[vexMaxNum];

	for (int v = 0; v < vexNum; v++) {
		vertexes[v] = es[v];
		tag[v] = UNVISITED;
		for (int u = 0; u < vexNum; u++)
			arcs[v][u] = infinity;
		arcs[v][v] = 0;
	}
}

template <class ElemType, class WeightType>
AdjMatrixUndirNetwork<ElemType, WeightType>::AdjMatrixUndirNetwork(int vertexMaxNum, WeightType infinit)
// 操作结果：构造允许顶点的最大数目为vertexMaxNum的空无向图
{
	if (vertexMaxNum < 0)
		throw Error("允许的顶点最大数目不能为负!");// 抛出异常

	vexNum = 0;
	vexMaxNum = vertexMaxNum;
	edgeNum = 0;
	infinity = infinit;

	vertexes = new ElemType[vexMaxNum];     // 生成生成顶点信息数组
	tag = new Status[vexMaxNum];			      // 生成标志数组
	arcs = (int **)new int *[vexMaxNum];    // 生成邻接矩阵
	for (int v = 0; v < vexMaxNum; v++)
		arcs[v] = new int[vexMaxNum];
}

template <class ElemType, class WeightType>
void AdjMatrixUndirNetwork<ElemType, WeightType>::Clear()
// 操作结果：把无向图的顶点数和边数设置为0.			 
{
	vexNum = 0;
	edgeNum = 0;
}

template <class ElemType, class WeightType>
bool AdjMatrixUndirNetwork<ElemType, WeightType>::IsEmpty()
// 操作结果：如果无向图为空返回true,否则返回false.
{
	return vexNum == 0;
}

template <class ElemType, class WeightType>
AdjMatrixUndirNetwork<ElemType, WeightType>::~AdjMatrixUndirNetwork()
// 操作结果：释放对象所占用的空间
{
	delete[]vertexes;					// 释放顶点数据
	delete[]tag;						    // 释放标志

	for (int v = 0; v < vexMaxNum; v++)	// 释放邻接矩阵的行
		delete[]arcs[v];
	delete[]arcs;					    // 释放邻接矩阵
}

template <class ElemType, class WeightType>
int AdjMatrixUndirNetwork<ElemType, WeightType>::GetOrder(ElemType &e) const
// 操作结果：求顶点e的序号.顶点的序号从0开始，图中不存在顶点e时，返回-1. 
{
	for (int v = 0; v < vexNum; v++)
		if (vertexes[v] == e)
			return v;	    // 顶点e存在,返回它的序号 
	return -1;	        // 顶点e不存在,返回-1
}

template <class ElemType, class WeightType>
Status AdjMatrixUndirNetwork<ElemType, WeightType>::GetElem(int v, ElemType &e) const
// 操作结果：求序号为v的顶点值, v的取值范围为0 ≤ v ＜ vexNum, v合法时函数
// 通过e取得顶点值，并返回ENTRY_FOUND；否则函数返回NOT_PRESENT
{
	if (v < 0 || v >= vexNum)
		return NOT_PRESENT;	// v范围错,返回元素不存在
	else {
		e = vertexes[v];	  // 将顶点v的元素值赋给e
		return ENTRY_FOUND;	// 返回元素存在
	}
}

template <class ElemType, class WeightType>
Status AdjMatrixUndirNetwork<ElemType, WeightType>::SetElem(int v, const ElemType &e)
// 操作结果：设置顶点的元素值v的取值范围为0 ≤ v ＜ vexNum, v合法时函数返回
//	SUCCESS, 否则函数返回RANGE_ERROR
{
	if (v < 0 || v >= vexNum)
		return RANGE_ERROR;	// v范围错,返回位置错
	else {
		vertexes[v] = e;		// 将顶点元素的值改为e 
		return SUCCESS;		  // 返回修改成功
	}
}

template <class ElemType, class WeightType>
WeightType AdjMatrixUndirNetwork<ElemType, WeightType>::GetInfinity() const
// 操作结果：返回无穷大
{
	return infinity;
}

template <class ElemType, class WeightType>
int AdjMatrixUndirNetwork<ElemType, WeightType>::GetVexNum() const
// 操作结果：返回顶点个数			 
{
	return vexNum;
}

template <class ElemType, class WeightType>
int AdjMatrixUndirNetwork<ElemType, WeightType>::GetEdgeNum() const
// 操作结果：返回边数
{
	return edgeNum;
}

template <class ElemType, class WeightType>
int AdjMatrixUndirNetwork<ElemType, WeightType>::FirstAdjVex(int v) const
// 操作结果：返回顶点v的第1个邻接点的序号		 
{
	if (v < 0 || v >= vexNum)
		throw Error("v不合法!");// 抛出异常

	for (int u = 0; u < vexNum; u++)
		if (arcs[v][u] != 0 && arcs[v][u] != infinity)
			return u;

	return -1;					// 返回-1表示无邻接点
}

template <class ElemType, class WeightType>
int AdjMatrixUndirNetwork<ElemType, WeightType>::NextAdjVex(int v1, int v2) const
// 操作结果：返回顶点v1的相对于v2的下一个邻接点			 
{
	if (v1 < 0 || v1 >= vexNum)
		throw Error("v1不合法!");	// 抛出异常
	if (v2 < 0 || v2 >= vexNum)
		throw Error("v2不合法!");	// 抛出异常
	if (v1 == v2) throw
		Error("v1不能等于v2!");		// 抛出异常

	for (int u = v2 + 1; u < vexNum; u++)
		if (arcs[v1][u] != 0 && arcs[v1][u] != infinity)
			return u;

	return -1;						// 返回-1表示无下一个邻接点
}

template <class ElemType, class WeightType>
void AdjMatrixUndirNetwork<ElemType, WeightType>::InsertVex(const ElemType &e)
// 操作结果：插入顶点e			 
{
	if (vexNum == vexMaxNum)
		throw Error("图的顶点数不能超过允许的最大数!");	// 抛出异常

	vertexes[vexNum] = e;
	tag[vexNum] = UNVISITED;

	for (int v = 0; v < vexNum; v++) {
		arcs[vexNum][v] = infinity;
		arcs[v][vexNum] = infinity;
	}
	arcs[vexNum][vexNum] = 0;
	vexNum++;
}

template <class ElemType, class WeightType>
void AdjMatrixUndirNetwork<ElemType, WeightType>::InsertArc(int v1, int v2, WeightType w)
// 操作结果：插入依附顶点v1和v2的边			 
{
	if (v1 < 0 || v1 >= vexNum)
		throw Error("v1不合法!");	// 抛出异常
	if (v2 < 0 || v2 >= vexNum)
		throw Error("v2不合法!");	// 抛出异常
	if (v1 == v2)
		throw Error("v1不能等于v2!");// 抛出异常

	if (arcs[v1][v2] == infinity) {	  // 原无向图中没有边(v1, v2) 
		edgeNum++;
		arcs[v1][v2] = w;
		arcs[v2][v1] = w;
	}
}

template <class ElemType, class WeightType>
void AdjMatrixUndirNetwork<ElemType, WeightType>::DeleteVex(const ElemType &e)
// 操作结果：删除元素为e的顶点			 
{
	int v;
	for (v = 0; v < vexNum; v++)
		if (vertexes[v] == e)
			break;
	if (v == vexNum)
		throw Error("图中不存在要删除的顶点!");	// 抛出异常

	for (int u = 0; u < vexNum; u++)             // 删除与顶点e相关联的边 
		if (u != v && arcs[v][u] != infinity) {
			edgeNum--;
			arcs[v][u] = infinity;
			arcs[u][v] = infinity;
		}

	vexNum--;
	if (v < vexNum) {
		vertexes[v] = vertexes[vexNum];
		tag[v] = tag[vexNum];
		for (int u = 0; u <= vexNum; u++)
			arcs[v][u] = arcs[vexNum][u];
		for (int u = 0; u <= vexNum; u++)
			arcs[u][v] = arcs[u][vexNum];
	}
}

template <class ElemType, class WeightType>
void AdjMatrixUndirNetwork<ElemType, WeightType>::DeleteArc(int v1, int v2)
// 操作结果：删除依附顶点v1和v2的边			 
{
	if (v1 < 0 || v1 >= vexNum)
		throw Error("v1不合法!");	// 抛出异常
	if (v2 < 0 || v2 >= vexNum)
		throw Error("v2不合法!");	// 抛出异常
	if (v1 == v2)
		throw Error("v1不能等于v2!");// 抛出异常

	if (arcs[v1][v2] != infinity) {	// 原无向图存在边(v1, v2)
		edgeNum--;
		arcs[v1][v2] = infinity;
		arcs[v2][v1] = infinity;
	}
}

template <class ElemType, class WeightType>
WeightType AdjMatrixUndirNetwork<ElemType, WeightType>::GetWeight(int v1, int v2) const
// 操作结果：返回顶点为v1和v2的边的权值
{
	if (v1 < 0 || v1 >= vexNum) throw Error("v1不合法!");	// 抛出异常
	if (v2 < 0 || v2 >= vexNum) throw Error("v2不合法!");	// 抛出异常

	return arcs[v1][v2];
}

template <class ElemType, class WeightType>
Status AdjMatrixUndirNetwork<ElemType, WeightType>::GetTag(int v) const
// 操作结果：返回顶点v的标志		 
{
	if (v < 0 || v >= vexNum)
		throw Error("v不合法!");	// 抛出异常

	return tag[v];
}

template <class ElemType, class WeightType>
void AdjMatrixUndirNetwork<ElemType, WeightType>::SetTag(int v, Status val) const
// 操作结果：设置顶点v的标志为val		 
{
	if (v < 0 || v >= vexNum)
		throw Error("v不合法!");	// 抛出异常

	tag[v] = val;
}

template <class ElemType, class WeightType>
AdjMatrixUndirNetwork<ElemType, WeightType>::AdjMatrixUndirNetwork(const AdjMatrixUndirNetwork<ElemType, WeightType> &g)
// 操作结果：由无向图的邻接矩阵g构造新无向图的邻接矩阵g——复制构造函数
{
	vexNum = g.vexNum;
	vexMaxNum = g.vexMaxNum;
	edgeNum = g.edgeNum;
	infinity = g.infinity;

	vertexes = new ElemType[vexMaxNum];		// 生成顶点数据数组
	tag = new Status[vexMaxNum];			// 生成标志数组
	arcs = (int **)new int *[vexMaxNum];	// 生成邻接矩阵
	for (int v = 0; v < vexMaxNum; v++)
		arcs[v] = new int[vexMaxNum];

	for (int v = 0; v < vexNum; v++) {	// 复制顶点数据数组
		vertexes[v] = g.vertexes[v];
		tag[v] = g.tag[v];
		for (int u = 0; u < vexNum; u++)
			arcs[v][u] = g.arcs[v][u];
	}
}

template <class ElemType, class WeightType>
AdjMatrixUndirNetwork<ElemType, WeightType> &AdjMatrixUndirNetwork<ElemType, WeightType>::operator =(const AdjMatrixUndirNetwork<ElemType, WeightType> &g)
// 操作结果：将无向图的邻接矩阵g赋值给当前无向图的邻接矩阵——赋值语句重载
{
	if (&g != this) {
		delete[]vertexes;				// 释放顶点数据
		delete[]tag;						  // 释放标志

		for (int v = 0; v < vexMaxNum; v++)	// 释放邻接矩阵的行
			delete[]arcs[v];
		delete[]arcs;					  // 释放邻接矩阵
		vexNum = g.vexNum;
		vexMaxNum = g.vexMaxNum;
		edgeNum = g.edgeNum;
		infinity = g.infinity;

		vertexes = new ElemType[vexMaxNum];	 // 生成顶点数据数组
		tag = new Status[vexMaxNum];			   // 生成标志数组
		arcs = (int **)new int *[vexMaxNum]; // 生成邻接矩阵
		for (int v = 0; v < vexMaxNum; v++)
			arcs[v] = new int[vexMaxNum];

		for (int v = 0; v < vexNum; v++) {	 // 复制顶点数据数组
			vertexes[v] = g.vertexes[v];
			tag[v] = g.tag[v];
			for (int u = 0; u < vexNum; u++)
				arcs[v][u] = g.arcs[v][u];
		}
	}
	return *this;
}

template <class ElemType, class WeightType>
void AdjMatrixUndirNetwork<ElemType, WeightType>::Display()
{

	for (int v = 0; v < vexNum; v++)
		cout << "\t" << vertexes[v];
	cout << endl;

	for (int v = 0; v < vexNum; v++) {
		cout << vertexes[v];
		for (int u = 0; u < vexNum; u++)
			if (arcs[v][u] == infinity)
				cout << "\t" << "∞";
			else
				cout << "\t" << arcs[v][u];
		cout << endl;
	}
}



template <class ElemType>
AdjListGraphVex<ElemType>::AdjListGraphVex()
{
	firstArc = NULL;
}

template <class ElemType>
AdjListGraphVex<ElemType>::AdjListGraphVex(ElemType  val, AdjListGraphArc *adj)
{
	data = val;
	firstArc = adj;
}


template <class ElemType>
AdjListDirGraph<ElemType>::AdjListDirGraph(ElemType es[], int vertexNum, int vertexMaxNum)
// 操作结果：构造顶点数据为es[],顶点数为numVex,顶点个数为vertexNum,边数为0的有向图
{
	if (vertexMaxNum < 0)
		throw Error("允许的顶点最大数目不能为负!");        // 抛出异常

	if (vertexMaxNum < vertexNum)
		throw Error("顶点数目不能大于允许的顶点最大数目!");// 抛出异常

	vexNum = vertexNum;
	vexMaxNum = vertexMaxNum;
	arcNum = 0;

	tag = new Status[vexMaxNum];
	vexTable = new AdjListGraphVex<ElemType>[vexMaxNum];

	// 拷贝顶点数据：
	std::memcpy(vexTable, es, vertexNum * sizeof(ElemType));

	// 初始化tag和firstArc;
	for (int v = 0; v < vexNum; v++) 
	{
		tag[v] = UNVISITED;
		vexTable[v].firstArc = nullptr;
	}
}

template <class ElemType>
AdjListDirGraph<ElemType>::AdjListDirGraph(int vertexMaxNum)
// 操作结果：构造顶点最大数目为vertexMaxNum的空有向图
{
	if (vertexMaxNum < 0)
		throw Error("允许的顶点最大数目不能为负!");// 抛出异常

	vexNum = 0;
	vexMaxNum = vertexMaxNum;
	arcNum = 0;

	tag = new Status[vexMaxNum];
	vexTable = new AdjListGraphVex<ElemType>[vexMaxNum];
}

template <class ElemType>
AdjListDirGraph<ElemType>::~AdjListDirGraph()
// 操作结果：释放邻接表有向图所占用空间
{
	Clear();                                // 释放边结点
	delete[]tag;							// 释放标志
	delete[]vexTable;						// 释放邻接表
}

template <class ElemType>
void AdjListDirGraph<ElemType>::Clear()
// 操作结果：释放所有的边结点，并把有向图的顶点数和边数设置为0.			 
{
	AdjListGraphArc *p;
	for (int v = 0; v < vexNum; v++) {	// 释放边结点
		p = vexTable[v].firstArc;
		while (p != NULL) {
			vexTable[v].firstArc = p->nextArc;
			delete p;
			p = vexTable[v].firstArc;
		}
	}
	vexNum = 0;
	arcNum = 0;
}

template <class ElemType>
bool AdjListDirGraph<ElemType>::IsEmpty()
// 操作结果：如果有向图为空返回true,否则返回false.
{
	return vexNum == 0;
}


// 求顶点e的索引.顶点的序号从0开始，图中不存在顶点e时返回 - 1.
template <class ElemType>
int AdjListDirGraph<ElemType>::GetOrder(ElemType& e) const
{
	int v;
	for (v = 0; v < vexNum; v++)
		if (e == vexTable[v].data)
			break;

	if (v < 0 || v >= vexNum)
		return -1;			// 顶点e不存在,返回-1
	else
		return v;			// 顶点e存在,返回它的序号 
}


// 求索引为v的顶点值
template <class ElemType>
Status AdjListDirGraph<ElemType>::GetElem(int v, ElemType &e) const
{
	if (v < 0 || v >= vexNum)
		return NOT_PRESENT;			// 元素不存在
	else 
	{
		e = vexTable[v].data;		// 将顶点v的元素值赋给e
		return ENTRY_FOUND;			// 元素存在
	}
}

template <class ElemType>
Status AdjListDirGraph<ElemType>::SetElem(int v, const ElemType &e)
// 操作结果：设置顶点的元素值v的取值范围为0 ≤ v ＜ vexNum, v合法时函数返回
//	SUCCESS, 否则函数返回RANGE_ERROR
{
	if (v < 0 || v >= vexNum)
		return RANGE_ERROR;			// 位置错
	else {
		vexTable[v].data = e;		// 顶点元素
		return SUCCESS;				// 成功
	}
}

template <class ElemType>
int AdjListDirGraph<ElemType>::GetVexNum() const
// 操作结果：返回顶点个数			 
{
	return vexNum;
}

template <class ElemType>
int AdjListDirGraph<ElemType>::GetArcNum() const
// 操作结果：返回边数个数
{
	return arcNum;
}

template <class ElemType>
int AdjListDirGraph<ElemType>::FirstAdjVex(int v) const			 
{
	if (v < 0 || v >= vexNum)
		throw Error("v不合法!");// 抛出异常

	if (vexTable[v].firstArc == NULL)
		return -1;              // 不存在邻接点
	else
		return vexTable[v].firstArc->adjVex;
}

template <class ElemType>
int AdjListDirGraph<ElemType>::NextAdjVex(int v1, int v2) const
// 操作结果：返回顶点v1的相对于v2的下一个邻接点			 
{
	AdjListGraphArc *p;
	if (v1 < 0 || v1 >= vexNum)
		throw Error("v1不合法!");	// 抛出异常
	if (v2 < 0 || v2 >= vexNum)
		throw Error("v2不合法!");	// 抛出异常
	if (v1 == v2)
		throw Error("v1不能等于v2!");// 抛出异常

	p = vexTable[v1].firstArc;
	while (p != NULL && p->adjVex != v2)
		p = p->nextArc;

	if (p == NULL || p->nextArc == NULL)
		return -1;                   // 不存在下一个邻接点
	else
		return p->nextArc->adjVex;
}

template <class ElemType>
Status AdjListDirGraph<ElemType>::InsertVex(const ElemType &e)
// 操作结果：在顶点表的表尾插入元素值为e的顶点。			 
{
	if (vexNum == vexMaxNum)
		return OVER_FLOW;			// 返回溢出 

	vexTable[vexNum].data = e;
	vexTable[vexNum].firstArc = NULL;
	tag[vexNum] = UNVISITED;
	vexNum++;
	return SUCCESS;
}

// 插入顶点为v1和v2,权为w的边	
template <class ElemType>
void AdjListDirGraph<ElemType>::InsertArc(int v1, int v2)		 
{
	if (v1 < 0 || v1 >= vexNum)
		throw Error("v1不合法!");	 
	if (v2 < 0 || v2 >= vexNum)
		throw Error("v2不合法!"); 
	if (v1 == v2)
		throw Error("v1不能等于v2!"); 

	AdjListGraphArc* p = nullptr;
	AdjListGraphArc* q = nullptr;
	p = vexTable[v1].firstArc;
	while (p != NULL && p->adjVex != v2) 
	{
		q = p;
		p = p->nextArc;
	}

	if (p == NULL) 
	{
		if (vexTable[v1].firstArc == NULL)
			vexTable[v1].firstArc = new AdjListGraphArc(v2);
		else
			q->nextArc = new AdjListGraphArc(v2);
		arcNum++;
	}
	else
		throw Error("这条边已经存在!"); 
}

template <class ElemType>
void AdjListDirGraph<ElemType>::DeleteVex(const ElemType &e)
// 操作结果：删除元素值为e的顶点			 
{
	int v;
	AdjListGraphArc *p, *q;
	for (v = 0; v < vexNum; v++)
		if (vexTable[v].data == e)
			break;
	if (v == vexNum)
		throw Error("图中不存在要删除的顶点!");	// 抛出异常

	for (int u = 0; u < vexNum; u++)           // 删除到达e的弧 
		if (u != v)
			DeleteArc(u, v);

	p = vexTable[v].firstArc;                  // 删除从e出发的弧 
	while (p != NULL) {
		vexTable[v].firstArc = p->nextArc;
		delete p;
		p = vexTable[v].firstArc;
		arcNum--;
	}

	vexNum--;
	vexTable[v].data = vexTable[vexNum].data;
	vexTable[v].firstArc = vexTable[vexNum].firstArc;
	vexTable[vexNum].firstArc = NULL;
	tag[v] = tag[vexNum];

	for (int u = 0; u < vexNum; u++)
		if (u != v) {
			p = vexTable[u].firstArc;
			while (p != NULL) {
				if (p->adjVex == vexNum)
					p->adjVex = v;
				p = p->nextArc;
			}
		}
}

template <class ElemType>
void AdjListDirGraph<ElemType>::DeleteArc(int v1, int v2)
// 操作结果：删除顶点为v1和v2的边			 
{
	if (v1 < 0 || v1 >= vexNum)
		throw Error("v1不合法!");	// 抛出异常
	if (v2 < 0 || v2 >= vexNum)
		throw Error("v2不合法!");	// 抛出异常
	if (v1 == v2) throw
		Error("v1不能等于v2!");		// 抛出异常

	AdjListGraphArc *p, *q;
	p = vexTable[v1].firstArc;
	while (p != NULL && p->adjVex != v2) {
		q = p;
		p = p->nextArc;
	}
	if (p != NULL) {
		if (vexTable[v1].firstArc == p)
			vexTable[v1].firstArc = p->nextArc;
		else
			q->nextArc = p->nextArc;
		delete p;
		arcNum--;
	}
	else
		Error("v1到v2没有弧。");		// 抛出异常
}

template <class ElemType>
Status AdjListDirGraph<ElemType>::GetTag(int v) const
// 操作结果：返回顶点v的标志		 
{
	if (v < 0 || v >= vexNum)
		throw Error("v不合法!");		// 抛出异常

	return tag[v];
}



// 得到逆邻接表
template <class ElemType>
Status AdjListDirGraph<ElemType>::GetRevAdjList(AdjListDirGraph<ElemType>& list) const
{
	// 逆邻接表中，某邻接点设定为指向该点的点。
	list.vexNum = this->vexNum;
	list.arcNum = 0;
 
	//		拷贝顶点数据
	for (int v = 0; v < list.vexNum; v++)
	{
		list.tag[v] = UNVISITED;
		list.vexTable[v].data = this->vexTable[v].data;
		list.vexTable[v].firstArc = NULL;
	}

	//		遍历原图，生成逆邻接表的邻边数据：
	for (int i = 0; i < this->vexNum; ++i) 
	{
		const AdjListGraphArc* pArc = this->vexTable[i].firstArc;
		while (pArc != nullptr) 
		{
			int dstIdx = pArc->adjVex;
			list.InsertArc(dstIdx, i);
			pArc = pArc->nextArc;
		}
	}

	return Status::SUCCESS;
}


template <class ElemType>
void AdjListDirGraph<ElemType>::SetTag(int v, Status val) const
// 操作结果：设置顶点v的标志为val		 
{
	if (v < 0 || v >= vexNum)
		throw Error("v不合法!");		// 抛出异常

	tag[v] = val;
}

template <class ElemType>
AdjListDirGraph<ElemType>::AdjListDirGraph(const AdjListDirGraph<ElemType> &g)
// 操作结果：由有向图的邻接矩阵g构造新有向图的邻接矩阵g——复制构造函数
{
	AdjListGraphArc *p, *q;
	vexNum = g.vexNum;
	vexMaxNum = g.vexMaxNum;
	arcNum = g.arcNum;

	tag = new Status[vexMaxNum];
	vexTable = new AdjListGraphVex<ElemType>[vexMaxNum];
	for (int v = 0; v < vexNum; v++) {
		tag[v] = g.tag[v];
		vexTable[v].data = g.vexTable[v].data;
		vexTable[v].firstArc = NULL;
		p = g.vexTable[v].firstArc;
		while (p != NULL)
			if (vexTable[v].firstArc == NULL) {
				vexTable[v].firstArc = new AdjListGraphArc(p->adjVex);
				q = vexTable[v].firstArc;
				p = p->nextArc;
			}
			else {
				q->nextArc = new AdjListGraphArc(p->adjVex);
				q = q->nextArc;
				p = p->nextArc;
			}
	}
}

template <class ElemType>
AdjListDirGraph<ElemType> &AdjListDirGraph<ElemType>::operator =(const AdjListDirGraph<ElemType> &g)
// 操作结果：将有向图的邻接矩阵g赋值给当前有向图的邻接矩阵——赋值语句重载
{
	if (&g != this)
	{
		Clear();                                    // 释放当前有向图边结点
		delete[]tag;								// 释放当前有向图标志数组 
		delete[]vexTable;							// 释放当前有向图顶点表 

		AdjListGraphArc *p, *q;
		vexNum = g.vexNum;
		vexMaxNum = g.vexMaxNum;
		arcNum = g.arcNum;

		tag = new Status[vexMaxNum];
		vexTable = new AdjListGraphVex<ElemType>[vexMaxNum];
		for (int v = 0; v < vexNum; v++) {
			tag[v] = g.tag[v];
			vexTable[v].data = g.vexTable[v].data;
			vexTable[v].firstArc = NULL;
			p = g.vexTable[v].firstArc;
			while (p != NULL)
				if (vexTable[v].firstArc == NULL) {
					vexTable[v].firstArc = new AdjListGraphArc(p->adjVex);
					q = vexTable[v].firstArc;
					p = p->nextArc;
				}
				else {
					q->nextArc = new AdjListGraphArc(p->adjVex);
					q = q->nextArc;
					p = p->nextArc;
				}
		}
	}
	return *this;
}

// 显示邻接矩阵有向图
template <class ElemType>
void AdjListDirGraph<ElemType>::Display()
{
	AdjListGraphArc* p;
	std::cout << "有向图共有" << vexNum << "个顶点，" << arcNum << "条边。" << std::endl;
	
	for (int v = 0; v < vexNum; v++) 
	{	// 显示第v个邻接链表
		std::cout << vexTable[v].data << ":\t(" << v << ")";				// 显示顶点号
		p = vexTable[v].firstArc;
		while (p != nullptr) 
		{
			std::cout << "-->(" << p->adjVex << ")";
			p = p->nextArc;
		}
		std::cout << std::endl;
	}
}


// 打印索引为Index的一条邻接链表
template <class ElemType>
bool AdjListDirGraph<ElemType>::displayRow(const int index)
{
	if (index >= this->vexNum) 
	{
		return false;
	}

	AdjListGraphArc* pArc = this->vexTable[index].firstArc;
	std::cout << "(" << index << ")";
	while (pArc != nullptr) 
	{
		std::cout << "-->(" << pArc->adjVex << ")";
		pArc = pArc->nextArc;
	}
	std::cout << std::endl;

	return true;
}


// 图的广度优先(breadth firsts)遍历
template <class ElemType>
void BFSTraverse(const AdjMatrixUndirGraph<ElemType> &g, void(*Visit)(const ElemType &))
{
	int v;
	for (v = 0; v < g.GetVexNum(); v++)
		g.SetTag(v, UNVISITED);				// 对每个顶点作未访问标志

	for (v = 0; v < g.GetVexNum(); v++)
		if (g.GetTag(v) == UNVISITED)
			BFS(g, v, Visit); 				// 从尚未访问的顶点v开始进行广度优先搜索
}


// 图的广度优先搜索(breadth first search)
template <class ElemType>
void BFS(const AdjMatrixUndirGraph<ElemType>& g, int v, void(*Visit)(const ElemType&))
{
	// 操作结果：从顶点v出发进行广度优先搜索
	LinkQueue<int> q;
	int u, w;
	ElemType e;
	g.SetTag(v, VISITED);						// 作访问标志
	g.GetElem(v, e);							// 取顶点v的数据元素值 
	Visit(e);									// 访问顶点v
	q.EnQueue(v);	                            // 顶点v入队 
	while (!q.IsEmpty()) {
		q.DelQueue(u);
		for (w = g.FirstAdjVex(u); w != -1; w = g.NextAdjVex(u, w))
			if (g.GetTag(w) == UNVISITED) 
			{ 
				// 对u尚未访问过的邻接顶点w进行访问
				g.SetTag(w, VISITED);
				g.GetElem(w, e);
				Visit(e);
				q.EnQueue(w);
			}
	}
}


// 图的深度优先(depth firsts)遍历
template <class ElemType>
void DFSTraverse(const AdjMatrixUndirGraph<ElemType> &g, void(*Visit)(const ElemType &))
{
	int v;
	for (v = 0; v < g.GetVexNum(); v++)
		g.SetTag(v, UNVISITED);// 对每个顶点设置未访问标志

	for (v = 0; v < g.GetVexNum(); v++)

		if (g.GetTag(v) == UNVISITED)
			DFS(g, v, Visit);// 从尚未访问的顶点v开始进行深度优先搜索 
}

// 图的深度优先搜索(depth firsts search)
template <class ElemType>
void DFS(const AdjMatrixUndirGraph<ElemType> &g, int v, void(*Visit)(const ElemType &))
{
	ElemType e;
	g.SetTag(v, VISITED);		// 设置顶点v已访问标志
	g.GetElem(v, e);			// 取顶点v的数据元素值 
	Visit(e);					// 访问顶点v
	for (int w = g.FirstAdjVex(v); w != -1; w = g.NextAdjVex(v, w))
	{
		if (g.GetTag(w) == UNVISITED)
		{
			DFS(g, w, Visit);	// 从v的尚未访问过的邻接顶点w开始进行深度优先搜索
		}
	}

}


template <class ElemType, class WeightType>
KruskalEdge<ElemType, WeightType>::KruskalEdge(ElemType v1, ElemType v2, WeightType w)
// 操作结果: 由顶点v1、v2和权w构造边——构造函数
{	// 构造函数
	vertex1 = v1;					// 顶点vertex1
	vertex2 = v2;					// 顶点vertex2
	weight = w;						// 权weight
}

template <class ElemType, class WeightType>
bool KruskalEdge<ElemType, WeightType>::operator <= (const KruskalEdge<ElemType, WeightType> &Ed)
// 操作结果：重载<=关系运算
{
	return (weight <= Ed.weight);
}

template <class ElemType, class WeightType>
bool KruskalEdge<ElemType, WeightType>::operator > (const KruskalEdge<ElemType, WeightType> &Ed)
// 操作结果：重载>关系运算
{
	return (weight > Ed.weight);
}


template<class ElemType, class WeightType>
KruskalEdge<ElemType, WeightType> &KruskalEdge<ElemType, WeightType>::operator = (const KruskalEdge<ElemType, WeightType> &Ed)
// 操作结果：将栈copy赋值给当前栈--赋值语句重载
{
	if (&Ed != this) {
		vertex1 = Ed.vertex1;					// 顶点vertex1
		vertex2 = Ed.vertex2;					// 顶点vertex2
		weight = Ed.weight;						// 权weight
	}
	return *this;
}


#if 0
// 用Kruskal算法构造网g的最小代价生成树
template <class ElemType, class WeightType>
void MiniSpanTreeKruskal(const AdjMatrixUndirNetwork<ElemType, WeightType> &g)
{
	int count, VexNum = g.GetVexNum();
	KruskalEdge<ElemType, WeightType> KEdge;
	MinHeap<KruskalEdge<ElemType, WeightType>> ha(g.GetEdgeNum());
	ElemType  *kVex, v1, v2;
	kVex = new ElemType[VexNum];	// 定义顶点数组,存储顶点信息 
	for (int i = 0; i < VexNum; i++)
		g.GetElem(i, kVex[i]);
	UFSets<ElemType> f(kVex, VexNum);// 根据顶点数组构造并查集 
	for (int v = 0; v < g.GetVexNum(); v++)
		for (int u = g.FirstAdjVex(v); u >= 0; u = g.NextAdjVex(v, u))
			if (v < u) {	// 将v < u的边插入到最小堆 
				g.GetElem(v, v1);
				g.GetElem(u, v2);
				KEdge.vertex1 = v1;
				KEdge.vertex2 = v2;
				KEdge.weight = g.GetWeight(v, u);
				ha.Insert(KEdge);
			}
	count = 0;					    // 表示已经挑选的边数

	while (count < VexNum - 1) {
		ha.DeleteTop(KEdge);        // 从堆顶取一条边
		v1 = KEdge.vertex1;
		v2 = KEdge.vertex2;
		if (f.Differ(v1, v2)) {	// 边所依附的两顶点不在同一棵树上
			cout << "边:( " << v1 << ", " << v2 << " ) 权:" << KEdge.weight << endl; // 输出边及权值
			f.Union(v1, v2);		// 将两个顶点所在的树合并成一棵树
			count++;
		}
	}
}
#endif

// 用Prim算法从u0出发构造网g的最小生成树
template <class ElemType, class WeightType>
void MiniSpanTreePrim(const AdjMatrixUndirNetwork<ElemType, WeightType> &g, int u0)
{
	// 初始条件：存在网g,u0为g的一个顶点
	WeightType min;
	ElemType v1, v2;
	int vexnum = g.GetVexNum();
	CloseArcType<ElemType, WeightType> * closearc;

	if (u0 < 0 || u0 >= vexnum)
		throw Error("顶点u0不存在!"); // 抛出异常

	int u, v, k;						// 表示顶点的临时变量 
	closearc = new CloseArcType<ElemType, WeightType>[vexnum];	// 分配存储空间
	for (v = 0; v < vexnum; v++)
	{
		// 初始化辅助数组adjVex，并对顶点作标志，此时U = {v0}
		closearc[v].nearvertex = u0;
		closearc[v].lowweight = g.GetWeight(u0, v);
	}
	closearc[u0].nearvertex = -1;
	closearc[u0].lowweight = 0;

	for (k = 1; k < vexnum; k++)
	{
		// 选择生成树的其余g.GetVexNum() - 1个顶点
		min = g.GetInfinity();
		v = u0;// 选择使得边<w, adjVex[w]>为连接V-U到U的具有最小权值的边
		for (u = 0; u < vexnum; u++)
		{
			if (closearc[u].lowweight != 0 && closearc[u].lowweight < min)
			{
				v = u;
				min = closearc[u].lowweight;
			}
		}

		if (v != u0)
		{
			g.GetElem(closearc[v].nearvertex, v1);
			g.GetElem(v, v2);
			cout << "边:( " << v1 << ", " << v2 << " ) 权:" << min << endl; // 输出边及权值
			closearc[v].lowweight = 0;		// 将w并入U
			for (u = g.FirstAdjVex(v); u != -1; u = g.NextAdjVex(v, u)) 	// 新顶点并入U后重新选择最小边
			{
				if (closearc[u].lowweight != 0 && (g.GetWeight(v, u) < closearc[u].lowweight))
				{
					// <v, w>为新的最小边
					closearc[u].lowweight = g.GetWeight(v, u);
					closearc[u].nearvertex = v;
				}
			}

		}

	}
	delete[]closearc;			// 释放存储空间  
}

