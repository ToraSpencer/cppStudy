#pragma once

#include "basicTools/basicTools.h"

using std::cout;
using std::endl;


////////////////////////////////////////////////////////////////////////////////////////////////// ǰ������
template <class ElemType>
class AdjMatrixUndirGraph;

template <class ElemType, class WeightType>
class AdjMatrixUndirNetwork;

template <class ElemType>
struct AdjListGraphVex;

struct AdjListGraphArc;

template <class ElemType>
class AdjListDirGraph;


////////////////////////////////////////////////////////////////////////////////////////////////// ������

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


// ����ͼ��ģ��(�ڽӾ����ʾ��undirected graph with adjacent matrix form)
template <class ElemType>
class AdjMatrixUndirGraph
{
protected:
	int vexNum, vexMaxNum, arcNum;			// ������Ŀ������Ķ��������Ŀ�ͱ���
	int **arcs;							    // ����Ϣ�ڽӾ��󡪡���һ����ά����
	ElemType *vertexes;						// ������Ϣ�����顪����һ��һά����
	mutable Status *tag;					// ��־����

public:
	AdjMatrixUndirGraph(ElemType es[], int vertexNum, int vertexMaxNum = DEFAULT_SIZE);		// ����es[]Ϊ����,�������ΪvertexNum,����Ķ��������ĿΪvertexMaxNum,����Ϊ0
	AdjMatrixUndirGraph(int vertexMaxNum = DEFAULT_SIZE);
	AdjMatrixUndirGraph(const AdjMatrixUndirGraph<ElemType> &g);	 
	~AdjMatrixUndirGraph();

	void Clear();			              	 
	bool IsEmpty();               
	int GetOrder(ElemType &d) const;				// �󶥵������	
	Status GetElem(int v, ElemType &d) const;		// �󶥵��Ԫ��ֵ	
	Status SetElem(int v, const ElemType &d);		// ���ö����Ԫ��ֵ
	int GetVexNum() const;						// ���ض������			 
	int GetArcNum() const;						// ���ر���			 
	int FirstAdjVex(int v) const;				// ���ض���v�ĵ�һ���ڽӵ�			 
	int NextAdjVex(int v1, int v2) const;		 // ���ض���v1�������v2����һ���ڽӵ�			 
	void InsertVex(const ElemType &d);			 // ����Ԫ��ֵΪd�Ķ���		 
	void InsertArc(int v1, int v2);			     // ���붥��Ϊv1��v2�ı�			 
	void DeleteVex(const ElemType &d);			 // ɾ��Ԫ��ֵΪd�Ķ���			 
	void DeleteArc(int v1, int v2);			     // ɾ������Ϊv1��v2�ı�			 
	Status GetTag(int v) const;			         // ���ض���v�ı�־		 
	void SetTag(int v, Status val) const;			 // ���ö���v�ı�־Ϊval		 
	void Display();									// ��ӡ����ͼ���ڽӾ���
	AdjMatrixUndirGraph<ElemType> &operator =(const AdjMatrixUndirGraph<ElemType> &g);
};


// ������������Ȩͼ�����ڽӾ����ʾ��
template <class ElemType, class WeightType>
class AdjMatrixUndirNetwork
{
protected:
	// �ڽӾ�������ݳ�Ա:
	int vexNum, vexMaxNum, edgeNum;			// ������Ŀ������Ķ��������Ŀ�ͱ���
	int **arcs;							// ��ű���Ϣ�ڽӾ���
	ElemType *vertexes;						// ��Ŷ�����Ϣ������ 
	Status *tag;							// ��־����
	WeightType infinity;					// �����

public:
	// �ڽӾ������͵ķ�������:
	AdjMatrixUndirNetwork(ElemType es[], int vertexNum, int vertexMaxNum = DEFAULT_SIZE,
		WeightType infinit = (WeightType)DEFAULT_INFINITY);
	// ������es[]Ϊ����,�������ΪvertexNum,����Ķ��������ĿΪvertexMaxNum,����Ϊ0������ͼ
	AdjMatrixUndirNetwork(int vertexMaxNum = DEFAULT_SIZE, WeightType infinit = (WeightType)DEFAULT_INFINITY);
	// ��������Ķ��������ĿΪvertexMaxNum,����Ϊ0������ͼ
	~AdjMatrixUndirNetwork();					// ��������
	void Clear();			              // ���ͼ			 
	bool IsEmpty();                 // �ж�����ͼ�Ƿ�Ϊ�� 
	int GetOrder(ElemType &e) const;// �󶥵�����	
	Status GetElem(int v, ElemType &e) const;// �󶥵��Ԫ��ֵ	
	Status SetElem(int v, const ElemType &e);// ���ö����Ԫ��ֵ
	WeightType GetInfinity() const;				// ���������			 
	int GetVexNum() const;					// ���ض������			 
	int GetEdgeNum() const;					// ���ر���			 
	int FirstAdjVex(int v) const;		// ���ض���v�ĵ�һ���ڽӵ�			 
	int NextAdjVex(int v1, int v2) const;		 // ���ض���v1�������v2����һ���ڽӵ�			 
	void InsertVex(const ElemType &e);			 // ����Ԫ��ֵΪe�Ķ���		 
	void DeleteVex(const ElemType &e);			 // ɾ��Ԫ��ֵΪe�Ķ���			 
	void InsertArc(int v1, int v2, WeightType w);	// ���붥��Ϊv1��v2,ȨΪw�ı�			 
	void DeleteArc(int v1, int v2);			// ɾ������Ϊv1��v2�ı�			 
	WeightType GetWeight(int v1, int v2) const;	// ���ض���Ϊv1��v2�ıߵ�Ȩֵ
	Status GetTag(int v) const;			         // ���ض���v�ı�־		 
	void SetTag(int v, Status val) const;	   // ���ö���v�ı�־Ϊval		 
	AdjMatrixUndirNetwork(const AdjMatrixUndirNetwork<ElemType, WeightType> &g);	// ���ƹ��캯��
	AdjMatrixUndirNetwork<ElemType, WeightType> &operator =(const AdjMatrixUndirNetwork<ElemType, WeightType> &g);
	// ��ֵ�������
	void Display();	                         // ��ʾ�ڽӾ�������ͼ
};


// ����ͼ������ģ�壨�ڽӱ��ʾ����������������һ������ڵ�
template <class ElemType>
struct AdjListGraphVex
{
	ElemType data;						// �����ֵ
	AdjListGraphArc* firstArc;			// ָ���ڽ�����߽���ָ��

	AdjListGraphVex();
	AdjListGraphVex(ElemType val, AdjListGraphArc *adj = NULL);

};


// ����ͼ����ģ�壨�ڽӱ��ʾ��
struct AdjListGraphArc
{
	// ���ݳ�Ա:
	int adjVex;							// �������ָ��Ķ����������
	AdjListGraphArc *nextArc;			// ��һ�����ڱ߽���ָ�룬һ���������ʾ��ĳһ������������ڱߡ�
							  
	AdjListGraphArc();					// �޲����Ĺ��캯��
	AdjListGraphArc(int v, AdjListGraphArc * next = NULL);
};


// ����ͼ��ģ�壨�ڽӱ��ʾ������ͼ����ܶ�ߺ���ʱ���ڽӾ�����ϡ�裬�˷ѿռ䡣
template <class ElemType>
class AdjListDirGraph
{
//protected:
public:
	int vexNum, vexMaxNum, arcNum;			// ������Ŀ������Ķ��������Ŀ�ͱ���
	AdjListGraphVex<ElemType> *vexTable;	// �������һά���飬ÿ������Ԫ��ʵ������һ������
	mutable Status *tag;			        // ��־����				

public:
	AdjListDirGraph(ElemType es[], int vertexNum, int vertexMaxNum = DEFAULT_SIZE);
	AdjListDirGraph(int vertexMaxNum = DEFAULT_SIZE);
	AdjListDirGraph(const AdjListDirGraph<ElemType> &g);
	~AdjListDirGraph();


	bool IsEmpty();
	int GetOrder(ElemType &e) const;            // �󶥵�e������	
	Status GetElem(int v, ElemType &e) const;
	int GetVexNum() const;						 	 
	int GetArcNum() const;						// ������ͼ�ı�������			 
	int FirstAdjVex(int v) const;				// ��������Ϊv�Ķ���ĵ�һ���ڽӵ�		 
	int NextAdjVex(int v1, int v2) const;		// ������ͼ�ж���v1�������v2����һ���ڽӵ�		
	Status GetTag(int v) const;				    // �󶥵�v�ı�־	
	Status GetRevAdjList(AdjListDirGraph<ElemType>& list) const;		// �õ����ڽӱ�����ڽӱ�

	Status InsertVex(const ElemType &e);		// ����Ԫ��ֵΪe�Ķ���		 
	void InsertArc(int v1, int v2);				// ����Ӷ���v1��v2�ı�			 
	void DeleteVex(const ElemType &e);			// ɾ��Ԫ��ֵΪe�Ķ���			 
	void DeleteArc(int v1, int v2);			    // ɾ���Ӷ���Ϊv1��v2�ı�			 
	
	void Clear();
	Status SetElem(int v, const ElemType& e);
	void SetTag(int v, Status tag) const;	    // ���ö���v�ı�־Ϊtag	 
	AdjListDirGraph<ElemType> &operator = (const AdjListDirGraph<ElemType> &g); // ���ظ�ֵ����� 
	void Display();								// ��ӡ����ͼ���ڽӱ� 
	bool displayRow(const int index);							// ��ӡ����ΪIndex��һ������

};


// Kruskal����
template <class ElemType, class WeightType>
class KruskalEdge
{
public:
	ElemType vertex1, vertex2;		// �ߵĶ���
	WeightType weight;				// �ߵ�Ȩֵ
	KruskalEdge(ElemType v1, ElemType v2, WeightType w);	// ���캯��
	KruskalEdge() {};	            // ���캯��
	KruskalEdge<ElemType, WeightType> &operator =(const KruskalEdge<ElemType, WeightType> &Ed); // ��ֵ�������
	bool operator <=(const KruskalEdge<ElemType, WeightType> &Ed);		// ����<=��ϵ���� 
	bool operator >(const KruskalEdge<ElemType, WeightType> &Ed);		// ����>��ϵ����
};


// Prim�㷨��ʹ�� 
template <class ElemType, class WeightType>
struct CloseArcType
{
	WeightType lowweight;
	int nearvertex;
};

 

////////////////////////////////////////////////////////////////////////////////////////////////// ��������

// ͼ�Ĺ������(breadth firsts)����
template <class ElemType>
void BFSTraverse(const AdjMatrixUndirGraph<ElemType> &g, void(*Visit)(const ElemType &));


// ͼ�Ĺ����������(breadth first search)
template <class ElemType>
void BFS(const AdjMatrixUndirGraph<ElemType> &g, int v, void(*Visit)(const ElemType &));


// ͼ���������(depth firsts)����
template <class ElemType>
void DFSTraverse(const AdjMatrixUndirGraph<ElemType> &g, void(*Visit)(const ElemType &));


// ͼ�������������(depth firsts search)
template <class ElemType>
void DFS(const AdjMatrixUndirGraph<ElemType> &g, int v, void(*Visit)(const ElemType &));


// ��Kruskal�㷨������g����С����������
template <class ElemType, class WeightType>
void MiniSpanTreeKruskal(const AdjMatrixUndirNetwork<ElemType, WeightType> &g);


// ��Prim�㷨��u0����������g����С������
template <class ElemType, class WeightType>
void MiniSpanTreePrim(const AdjMatrixUndirNetwork<ElemType, WeightType> &g, int u0);


////////////////////////////////////////////////////////////////////////////////////////////////// ʵ�ֲ���
template <class ElemType>
AdjMatrixUndirGraph<ElemType>::AdjMatrixUndirGraph(ElemType es[], int vertexNum, int vertexMaxNum)
// �����������������Ԫ��Ϊes[],�������ΪvertexNum,����Ķ��������ĿΪvertexMaxNum,����Ϊ0������ͼ

{
	if (vertexMaxNum < 0)
		throw Error("����Ķ��������Ŀ����Ϊ��!");        // �׳��쳣

	if (vertexMaxNum < vertexNum)
		throw Error("������Ŀ���ܴ�������Ķ��������Ŀ!");// �׳��쳣

	vexNum = vertexNum;
	vexMaxNum = vertexMaxNum;
	arcNum = 0;

	vertexes = new ElemType[vexMaxNum];      // �������ɶ�����Ϣ����
	tag = new Status[vexMaxNum];			       // ���ɱ�־����
	arcs = (int **)new int *[vexMaxNum];     // �����ڽӾ���
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
// �������������������������ĿΪvertexMaxNum�Ŀ�����ͼ
{
	if (vertexMaxNum < 0)
		throw Error("����Ķ��������Ŀ����Ϊ��!");// �׳��쳣

	vexNum = 0;
	vexMaxNum = vertexMaxNum;
	arcNum = 0;

	vertexes = new ElemType[vexMaxNum];     // �������ɶ�����Ϣ����
	tag = new Status[vexMaxNum];			      // ���ɱ�־����
	arcs = (int **)new int *[vexMaxNum];    // �����ڽӾ���
	for (int v = 0; v < vexMaxNum; v++)
		arcs[v] = new int[vexMaxNum];
}

template <class ElemType>
void AdjMatrixUndirGraph<ElemType>::Clear()
// ���������������ͼ�Ķ������ͱ�������Ϊ0.			 
{
	vexNum = 0;
	arcNum = 0;
}

template <class ElemType>
bool AdjMatrixUndirGraph<ElemType>::IsEmpty()
// ����������������ͼΪ�շ���true,���򷵻�false.
{
	return vexNum == 0;
}

template <class ElemType>
AdjMatrixUndirGraph<ElemType>::~AdjMatrixUndirGraph()
// ����������ͷŶ�����ռ�õĿռ�
{
	delete[]vertexes;					// �ͷŶ�������
	delete[]tag;						    // �ͷű�־

	for (int v = 0; v < vexMaxNum; v++)	// �ͷ��ڽӾ������
		delete[]arcs[v];
	delete[]arcs;					    // �ͷ��ڽӾ���
}

template <class ElemType>
int AdjMatrixUndirGraph<ElemType>::GetOrder(ElemType &d) const
// ����������󶥵�d�����.�������Ŵ�0��ʼ��ͼ�в����ڶ���dʱ������-1. 
{
	for (int v = 0; v < vexNum; v++)
		if (vertexes[v] == d)
			return v;	    // ����d����,����������� 
	return -1;	        // ����d������,����-1
}

template <class ElemType>
Status AdjMatrixUndirGraph<ElemType>::GetElem(int v, ElemType &d) const
// ��������������Ϊv�Ķ���ֵ, v��ȡֵ��ΧΪ0 �� v �� vexNum, v�Ϸ�ʱ����
// ͨ��dȡ�ö���ֵ��������ENTRY_FOUND������������NOT_PRESENT
{
	if (v < 0 || v >= vexNum)
		return NOT_PRESENT;	// v��Χ��,����Ԫ�ز�����
	else {
		d = vertexes[v];	  // ������v��Ԫ��ֵ����d
		return ENTRY_FOUND;	// ����Ԫ�ش���
	}
}

template <class ElemType>
Status AdjMatrixUndirGraph<ElemType>::SetElem(int v, const ElemType &d)
// ������������ö����Ԫ��ֵv��ȡֵ��ΧΪ0 �� v �� vexNum, v�Ϸ�ʱ��������
//	SUCCESS, ����������RANGE_ERROR
{
	if (v < 0 || v >= vexNum)
		return RANGE_ERROR;	// v��Χ��,����λ�ô�
	else {
		vertexes[v] = d;		// ������Ԫ�ص�ֵ��Ϊd 
		return SUCCESS;		  // �����޸ĳɹ�
	}
}


// ���ض������	
template <class ElemType>
int AdjMatrixUndirGraph<ElemType>::GetVexNum() const
{
	return vexNum;
}

template <class ElemType>
int AdjMatrixUndirGraph<ElemType>::GetArcNum() const
// ������������ر���
{
	return arcNum;
}

// ���ض���v�ĵ�1���ڽӵ������
template <class ElemType>
int AdjMatrixUndirGraph<ElemType>::FirstAdjVex(int v) const	 
{
	if (v < 0 || v >= vexNum)
		throw Error("v���Ϸ�!");		// �׳��쳣

	for (int u = 0; u < vexNum; u++)
		if (arcs[v][u] != 0)
			return u;

	return -1;							// ����-1��ʾ���ڽӵ�
}

template <class ElemType>
int AdjMatrixUndirGraph<ElemType>::NextAdjVex(int v1, int v2) const
// ������������ض���v1�������v2����һ���ڽӵ�			 
{
	if (v1 < 0 || v1 >= vexNum)
		throw Error("v1���Ϸ�!");	// �׳��쳣
	if (v2 < 0 || v2 >= vexNum)
		throw Error("v2���Ϸ�!");	// �׳��쳣
	if (v1 == v2) throw
		Error("v1���ܵ���v2!");		// �׳��쳣

	for (int u = v2 + 1; u < vexNum; u++)
		if (arcs[v1][u] != 0)
			return u;

	return -1;						// ����-1��ʾ����һ���ڽӵ�
}

template <class ElemType>
void AdjMatrixUndirGraph<ElemType>::InsertVex(const ElemType &d)		 
{
	if (vexNum == vexMaxNum)
		throw Error("ͼ�Ķ��������ܳ�������������!");	 

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
// ���������������������v1��v2�ı�			 
{
	if (v1 < 0 || v1 >= vexNum)
		throw Error("v1���Ϸ�!");	// �׳��쳣
	if (v2 < 0 || v2 >= vexNum)
		throw Error("v2���Ϸ�!");	// �׳��쳣
	if (v1 == v2)
		throw Error("v1���ܵ���v2!");// �׳��쳣

	if (arcs[v1][v2] == 0) {	  // ԭ����ͼ��û�б�(v1, v2) 
		arcNum++;
		arcs[v1][v2] = 1;
		arcs[v2][v1] = 1;
	}
}

template <class ElemType>
void AdjMatrixUndirGraph<ElemType>::DeleteVex(const ElemType &d)
// ���������ɾ��Ԫ��Ϊd�Ķ���			 
{
	int v;
	for (v = 0; v < vexNum; v++)
		if (vertexes[v] == d)
			break;
	if (v == vexNum)
		throw Error("ͼ�в�����Ҫɾ���Ķ���!");	// �׳��쳣

	for (int u = 0; u < vexNum; u++)             // ɾ���붥��d������ı� 
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
// ���������ɾ����������v1��v2�ı�			 
{
	if (v1 < 0 || v1 >= vexNum)
		throw Error("v1���Ϸ�!");	// �׳��쳣
	if (v2 < 0 || v2 >= vexNum)
		throw Error("v2���Ϸ�!");	// �׳��쳣
	if (v1 == v2)
		throw Error("v1���ܵ���v2!");// �׳��쳣

	if (arcs[v1][v2] != 0) {	// ԭ����ͼ���ڱ�(v1, v2)
		arcNum--;
		arcs[v1][v2] = 0;
		arcs[v2][v1] = 0;
	}
}

template <class ElemType>
Status AdjMatrixUndirGraph<ElemType>::GetTag(int v) const
// ������������ض���v�ı�־		 
{
	if (v < 0 || v >= vexNum)
		throw Error("v���Ϸ�!");	// �׳��쳣

	return tag[v];
}

template <class ElemType>
void AdjMatrixUndirGraph<ElemType>::SetTag(int v, Status val) const
// ������������ö���v�ı�־Ϊval		 
{
	if (v < 0 || v >= vexNum)
		throw Error("v���Ϸ�!");	// �׳��쳣

	tag[v] = val;
}

template <class ElemType>
AdjMatrixUndirGraph<ElemType>::AdjMatrixUndirGraph(const AdjMatrixUndirGraph<ElemType> &g)
// ���������������ͼ���ڽӾ���g����������ͼ���ڽӾ���g�������ƹ��캯��
{
	vexNum = g.vexNum;
	vexMaxNum = g.vexMaxNum;
	arcNum = g.arcNum;

	vertexes = new ElemType[vexMaxNum];		// ���ɶ�����������
	tag = new Status[vexMaxNum];			// ���ɱ�־����
	arcs = (int **)new int *[vexMaxNum];	// �����ڽӾ���
	for (int v = 0; v < vexMaxNum; v++)
		arcs[v] = new int[vexMaxNum];

	for (int v = 0; v < vexNum; v++) {	// ���ƶ�����������
		vertexes[v] = g.vertexes[v];
		tag[v] = g.tag[v];
		for (int u = 0; u < vexNum; u++)
			arcs[v][u] = g.arcs[v][u];
	}
}

template <class ElemType>
AdjMatrixUndirGraph<ElemType> &AdjMatrixUndirGraph<ElemType>::operator =(const AdjMatrixUndirGraph<ElemType> &g)
// ���������������ͼ���ڽӾ���g��ֵ����ǰ����ͼ���ڽӾ��󡪡���ֵ�������
{
	if (&g != this) {
		delete[]vertexes;				// �ͷŶ�������
		delete[]tag;						  // �ͷű�־

		for (int v = 0; v < vexMaxNum; v++)	// �ͷ��ڽӾ������
			delete[]arcs[v];
		delete[]arcs;					  // �ͷ��ڽӾ���
		vexNum = g.vexNum;
		vexMaxNum = g.vexMaxNum;
		arcNum = g.arcNum;

		vertexes = new ElemType[vexMaxNum];	 // ���ɶ�����������
		tag = new Status[vexMaxNum];			   // ���ɱ�־����
		arcs = (int **)new int *[vexMaxNum]; // �����ڽӾ���
		for (int v = 0; v < vexMaxNum; v++)
			arcs[v] = new int[vexMaxNum];

		for (int v = 0; v < vexNum; v++) {	 // ���ƶ�����������
			vertexes[v] = g.vertexes[v];
			tag[v] = g.tag[v];
			for (int u = 0; u < vexNum; u++)
				arcs[v][u] = g.arcs[v][u];
		}
	}
	return *this;
}

// ������ӡ����ͼ���ڽӾ���
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
// �����������������Ԫ��Ϊes[],�������ΪvertexNum,����Ķ��������ĿΪvertexMaxNum,����Ϊ0������ͼ
{
	if (vertexMaxNum < 0)
		throw Error("����Ķ��������Ŀ����Ϊ��!");        // �׳��쳣

	if (vertexMaxNum < vertexNum)
		throw Error("������Ŀ���ܴ�������Ķ��������Ŀ!");// �׳��쳣

	vexNum = vertexNum;
	vexMaxNum = vertexMaxNum;
	edgeNum = 0;
	infinity = infinit;

	vertexes = new ElemType[vexMaxNum];     	// �������ɶ�����Ϣ����
	tag = new Status[vexMaxNum];			 	// ���ɱ�־����
	arcs = (int **)new int *[vexMaxNum];     	// �����ڽӾ���
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
// �������������������������ĿΪvertexMaxNum�Ŀ�����ͼ
{
	if (vertexMaxNum < 0)
		throw Error("����Ķ��������Ŀ����Ϊ��!");// �׳��쳣

	vexNum = 0;
	vexMaxNum = vertexMaxNum;
	edgeNum = 0;
	infinity = infinit;

	vertexes = new ElemType[vexMaxNum];     // �������ɶ�����Ϣ����
	tag = new Status[vexMaxNum];			      // ���ɱ�־����
	arcs = (int **)new int *[vexMaxNum];    // �����ڽӾ���
	for (int v = 0; v < vexMaxNum; v++)
		arcs[v] = new int[vexMaxNum];
}

template <class ElemType, class WeightType>
void AdjMatrixUndirNetwork<ElemType, WeightType>::Clear()
// ���������������ͼ�Ķ������ͱ�������Ϊ0.			 
{
	vexNum = 0;
	edgeNum = 0;
}

template <class ElemType, class WeightType>
bool AdjMatrixUndirNetwork<ElemType, WeightType>::IsEmpty()
// ����������������ͼΪ�շ���true,���򷵻�false.
{
	return vexNum == 0;
}

template <class ElemType, class WeightType>
AdjMatrixUndirNetwork<ElemType, WeightType>::~AdjMatrixUndirNetwork()
// ����������ͷŶ�����ռ�õĿռ�
{
	delete[]vertexes;					// �ͷŶ�������
	delete[]tag;						    // �ͷű�־

	for (int v = 0; v < vexMaxNum; v++)	// �ͷ��ڽӾ������
		delete[]arcs[v];
	delete[]arcs;					    // �ͷ��ڽӾ���
}

template <class ElemType, class WeightType>
int AdjMatrixUndirNetwork<ElemType, WeightType>::GetOrder(ElemType &e) const
// ����������󶥵�e�����.�������Ŵ�0��ʼ��ͼ�в����ڶ���eʱ������-1. 
{
	for (int v = 0; v < vexNum; v++)
		if (vertexes[v] == e)
			return v;	    // ����e����,����������� 
	return -1;	        // ����e������,����-1
}

template <class ElemType, class WeightType>
Status AdjMatrixUndirNetwork<ElemType, WeightType>::GetElem(int v, ElemType &e) const
// ��������������Ϊv�Ķ���ֵ, v��ȡֵ��ΧΪ0 �� v �� vexNum, v�Ϸ�ʱ����
// ͨ��eȡ�ö���ֵ��������ENTRY_FOUND������������NOT_PRESENT
{
	if (v < 0 || v >= vexNum)
		return NOT_PRESENT;	// v��Χ��,����Ԫ�ز�����
	else {
		e = vertexes[v];	  // ������v��Ԫ��ֵ����e
		return ENTRY_FOUND;	// ����Ԫ�ش���
	}
}

template <class ElemType, class WeightType>
Status AdjMatrixUndirNetwork<ElemType, WeightType>::SetElem(int v, const ElemType &e)
// ������������ö����Ԫ��ֵv��ȡֵ��ΧΪ0 �� v �� vexNum, v�Ϸ�ʱ��������
//	SUCCESS, ����������RANGE_ERROR
{
	if (v < 0 || v >= vexNum)
		return RANGE_ERROR;	// v��Χ��,����λ�ô�
	else {
		vertexes[v] = e;		// ������Ԫ�ص�ֵ��Ϊe 
		return SUCCESS;		  // �����޸ĳɹ�
	}
}

template <class ElemType, class WeightType>
WeightType AdjMatrixUndirNetwork<ElemType, WeightType>::GetInfinity() const
// ������������������
{
	return infinity;
}

template <class ElemType, class WeightType>
int AdjMatrixUndirNetwork<ElemType, WeightType>::GetVexNum() const
// ������������ض������			 
{
	return vexNum;
}

template <class ElemType, class WeightType>
int AdjMatrixUndirNetwork<ElemType, WeightType>::GetEdgeNum() const
// ������������ر���
{
	return edgeNum;
}

template <class ElemType, class WeightType>
int AdjMatrixUndirNetwork<ElemType, WeightType>::FirstAdjVex(int v) const
// ������������ض���v�ĵ�1���ڽӵ�����		 
{
	if (v < 0 || v >= vexNum)
		throw Error("v���Ϸ�!");// �׳��쳣

	for (int u = 0; u < vexNum; u++)
		if (arcs[v][u] != 0 && arcs[v][u] != infinity)
			return u;

	return -1;					// ����-1��ʾ���ڽӵ�
}

template <class ElemType, class WeightType>
int AdjMatrixUndirNetwork<ElemType, WeightType>::NextAdjVex(int v1, int v2) const
// ������������ض���v1�������v2����һ���ڽӵ�			 
{
	if (v1 < 0 || v1 >= vexNum)
		throw Error("v1���Ϸ�!");	// �׳��쳣
	if (v2 < 0 || v2 >= vexNum)
		throw Error("v2���Ϸ�!");	// �׳��쳣
	if (v1 == v2) throw
		Error("v1���ܵ���v2!");		// �׳��쳣

	for (int u = v2 + 1; u < vexNum; u++)
		if (arcs[v1][u] != 0 && arcs[v1][u] != infinity)
			return u;

	return -1;						// ����-1��ʾ����һ���ڽӵ�
}

template <class ElemType, class WeightType>
void AdjMatrixUndirNetwork<ElemType, WeightType>::InsertVex(const ElemType &e)
// ������������붥��e			 
{
	if (vexNum == vexMaxNum)
		throw Error("ͼ�Ķ��������ܳ�������������!");	// �׳��쳣

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
// ���������������������v1��v2�ı�			 
{
	if (v1 < 0 || v1 >= vexNum)
		throw Error("v1���Ϸ�!");	// �׳��쳣
	if (v2 < 0 || v2 >= vexNum)
		throw Error("v2���Ϸ�!");	// �׳��쳣
	if (v1 == v2)
		throw Error("v1���ܵ���v2!");// �׳��쳣

	if (arcs[v1][v2] == infinity) {	  // ԭ����ͼ��û�б�(v1, v2) 
		edgeNum++;
		arcs[v1][v2] = w;
		arcs[v2][v1] = w;
	}
}

template <class ElemType, class WeightType>
void AdjMatrixUndirNetwork<ElemType, WeightType>::DeleteVex(const ElemType &e)
// ���������ɾ��Ԫ��Ϊe�Ķ���			 
{
	int v;
	for (v = 0; v < vexNum; v++)
		if (vertexes[v] == e)
			break;
	if (v == vexNum)
		throw Error("ͼ�в�����Ҫɾ���Ķ���!");	// �׳��쳣

	for (int u = 0; u < vexNum; u++)             // ɾ���붥��e������ı� 
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
// ���������ɾ����������v1��v2�ı�			 
{
	if (v1 < 0 || v1 >= vexNum)
		throw Error("v1���Ϸ�!");	// �׳��쳣
	if (v2 < 0 || v2 >= vexNum)
		throw Error("v2���Ϸ�!");	// �׳��쳣
	if (v1 == v2)
		throw Error("v1���ܵ���v2!");// �׳��쳣

	if (arcs[v1][v2] != infinity) {	// ԭ����ͼ���ڱ�(v1, v2)
		edgeNum--;
		arcs[v1][v2] = infinity;
		arcs[v2][v1] = infinity;
	}
}

template <class ElemType, class WeightType>
WeightType AdjMatrixUndirNetwork<ElemType, WeightType>::GetWeight(int v1, int v2) const
// ������������ض���Ϊv1��v2�ıߵ�Ȩֵ
{
	if (v1 < 0 || v1 >= vexNum) throw Error("v1���Ϸ�!");	// �׳��쳣
	if (v2 < 0 || v2 >= vexNum) throw Error("v2���Ϸ�!");	// �׳��쳣

	return arcs[v1][v2];
}

template <class ElemType, class WeightType>
Status AdjMatrixUndirNetwork<ElemType, WeightType>::GetTag(int v) const
// ������������ض���v�ı�־		 
{
	if (v < 0 || v >= vexNum)
		throw Error("v���Ϸ�!");	// �׳��쳣

	return tag[v];
}

template <class ElemType, class WeightType>
void AdjMatrixUndirNetwork<ElemType, WeightType>::SetTag(int v, Status val) const
// ������������ö���v�ı�־Ϊval		 
{
	if (v < 0 || v >= vexNum)
		throw Error("v���Ϸ�!");	// �׳��쳣

	tag[v] = val;
}

template <class ElemType, class WeightType>
AdjMatrixUndirNetwork<ElemType, WeightType>::AdjMatrixUndirNetwork(const AdjMatrixUndirNetwork<ElemType, WeightType> &g)
// ���������������ͼ���ڽӾ���g����������ͼ���ڽӾ���g�������ƹ��캯��
{
	vexNum = g.vexNum;
	vexMaxNum = g.vexMaxNum;
	edgeNum = g.edgeNum;
	infinity = g.infinity;

	vertexes = new ElemType[vexMaxNum];		// ���ɶ�����������
	tag = new Status[vexMaxNum];			// ���ɱ�־����
	arcs = (int **)new int *[vexMaxNum];	// �����ڽӾ���
	for (int v = 0; v < vexMaxNum; v++)
		arcs[v] = new int[vexMaxNum];

	for (int v = 0; v < vexNum; v++) {	// ���ƶ�����������
		vertexes[v] = g.vertexes[v];
		tag[v] = g.tag[v];
		for (int u = 0; u < vexNum; u++)
			arcs[v][u] = g.arcs[v][u];
	}
}

template <class ElemType, class WeightType>
AdjMatrixUndirNetwork<ElemType, WeightType> &AdjMatrixUndirNetwork<ElemType, WeightType>::operator =(const AdjMatrixUndirNetwork<ElemType, WeightType> &g)
// ���������������ͼ���ڽӾ���g��ֵ����ǰ����ͼ���ڽӾ��󡪡���ֵ�������
{
	if (&g != this) {
		delete[]vertexes;				// �ͷŶ�������
		delete[]tag;						  // �ͷű�־

		for (int v = 0; v < vexMaxNum; v++)	// �ͷ��ڽӾ������
			delete[]arcs[v];
		delete[]arcs;					  // �ͷ��ڽӾ���
		vexNum = g.vexNum;
		vexMaxNum = g.vexMaxNum;
		edgeNum = g.edgeNum;
		infinity = g.infinity;

		vertexes = new ElemType[vexMaxNum];	 // ���ɶ�����������
		tag = new Status[vexMaxNum];			   // ���ɱ�־����
		arcs = (int **)new int *[vexMaxNum]; // �����ڽӾ���
		for (int v = 0; v < vexMaxNum; v++)
			arcs[v] = new int[vexMaxNum];

		for (int v = 0; v < vexNum; v++) {	 // ���ƶ�����������
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
				cout << "\t" << "��";
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
// ������������춥������Ϊes[],������ΪnumVex,�������ΪvertexNum,����Ϊ0������ͼ
{
	if (vertexMaxNum < 0)
		throw Error("����Ķ��������Ŀ����Ϊ��!");        // �׳��쳣

	if (vertexMaxNum < vertexNum)
		throw Error("������Ŀ���ܴ�������Ķ��������Ŀ!");// �׳��쳣

	vexNum = vertexNum;
	vexMaxNum = vertexMaxNum;
	arcNum = 0;

	tag = new Status[vexMaxNum];
	vexTable = new AdjListGraphVex<ElemType>[vexMaxNum];

	// �����������ݣ�
	std::memcpy(vexTable, es, vertexNum * sizeof(ElemType));

	// ��ʼ��tag��firstArc;
	for (int v = 0; v < vexNum; v++) 
	{
		tag[v] = UNVISITED;
		vexTable[v].firstArc = nullptr;
	}
}

template <class ElemType>
AdjListDirGraph<ElemType>::AdjListDirGraph(int vertexMaxNum)
// ������������춥�������ĿΪvertexMaxNum�Ŀ�����ͼ
{
	if (vertexMaxNum < 0)
		throw Error("����Ķ��������Ŀ����Ϊ��!");// �׳��쳣

	vexNum = 0;
	vexMaxNum = vertexMaxNum;
	arcNum = 0;

	tag = new Status[vexMaxNum];
	vexTable = new AdjListGraphVex<ElemType>[vexMaxNum];
}

template <class ElemType>
AdjListDirGraph<ElemType>::~AdjListDirGraph()
// ����������ͷ��ڽӱ�����ͼ��ռ�ÿռ�
{
	Clear();                                // �ͷű߽��
	delete[]tag;							// �ͷű�־
	delete[]vexTable;						// �ͷ��ڽӱ�
}

template <class ElemType>
void AdjListDirGraph<ElemType>::Clear()
// ����������ͷ����еı߽�㣬��������ͼ�Ķ������ͱ�������Ϊ0.			 
{
	AdjListGraphArc *p;
	for (int v = 0; v < vexNum; v++) {	// �ͷű߽��
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
// ����������������ͼΪ�շ���true,���򷵻�false.
{
	return vexNum == 0;
}


// �󶥵�e������.�������Ŵ�0��ʼ��ͼ�в����ڶ���eʱ���� - 1.
template <class ElemType>
int AdjListDirGraph<ElemType>::GetOrder(ElemType& e) const
{
	int v;
	for (v = 0; v < vexNum; v++)
		if (e == vexTable[v].data)
			break;

	if (v < 0 || v >= vexNum)
		return -1;			// ����e������,����-1
	else
		return v;			// ����e����,����������� 
}


// ������Ϊv�Ķ���ֵ
template <class ElemType>
Status AdjListDirGraph<ElemType>::GetElem(int v, ElemType &e) const
{
	if (v < 0 || v >= vexNum)
		return NOT_PRESENT;			// Ԫ�ز�����
	else 
	{
		e = vexTable[v].data;		// ������v��Ԫ��ֵ����e
		return ENTRY_FOUND;			// Ԫ�ش���
	}
}

template <class ElemType>
Status AdjListDirGraph<ElemType>::SetElem(int v, const ElemType &e)
// ������������ö����Ԫ��ֵv��ȡֵ��ΧΪ0 �� v �� vexNum, v�Ϸ�ʱ��������
//	SUCCESS, ����������RANGE_ERROR
{
	if (v < 0 || v >= vexNum)
		return RANGE_ERROR;			// λ�ô�
	else {
		vexTable[v].data = e;		// ����Ԫ��
		return SUCCESS;				// �ɹ�
	}
}

template <class ElemType>
int AdjListDirGraph<ElemType>::GetVexNum() const
// ������������ض������			 
{
	return vexNum;
}

template <class ElemType>
int AdjListDirGraph<ElemType>::GetArcNum() const
// ������������ر�������
{
	return arcNum;
}

template <class ElemType>
int AdjListDirGraph<ElemType>::FirstAdjVex(int v) const			 
{
	if (v < 0 || v >= vexNum)
		throw Error("v���Ϸ�!");// �׳��쳣

	if (vexTable[v].firstArc == NULL)
		return -1;              // �������ڽӵ�
	else
		return vexTable[v].firstArc->adjVex;
}

template <class ElemType>
int AdjListDirGraph<ElemType>::NextAdjVex(int v1, int v2) const
// ������������ض���v1�������v2����һ���ڽӵ�			 
{
	AdjListGraphArc *p;
	if (v1 < 0 || v1 >= vexNum)
		throw Error("v1���Ϸ�!");	// �׳��쳣
	if (v2 < 0 || v2 >= vexNum)
		throw Error("v2���Ϸ�!");	// �׳��쳣
	if (v1 == v2)
		throw Error("v1���ܵ���v2!");// �׳��쳣

	p = vexTable[v1].firstArc;
	while (p != NULL && p->adjVex != v2)
		p = p->nextArc;

	if (p == NULL || p->nextArc == NULL)
		return -1;                   // ��������һ���ڽӵ�
	else
		return p->nextArc->adjVex;
}

template <class ElemType>
Status AdjListDirGraph<ElemType>::InsertVex(const ElemType &e)
// ����������ڶ����ı�β����Ԫ��ֵΪe�Ķ��㡣			 
{
	if (vexNum == vexMaxNum)
		return OVER_FLOW;			// ������� 

	vexTable[vexNum].data = e;
	vexTable[vexNum].firstArc = NULL;
	tag[vexNum] = UNVISITED;
	vexNum++;
	return SUCCESS;
}

// ���붥��Ϊv1��v2,ȨΪw�ı�	
template <class ElemType>
void AdjListDirGraph<ElemType>::InsertArc(int v1, int v2)		 
{
	if (v1 < 0 || v1 >= vexNum)
		throw Error("v1���Ϸ�!");	 
	if (v2 < 0 || v2 >= vexNum)
		throw Error("v2���Ϸ�!"); 
	if (v1 == v2)
		throw Error("v1���ܵ���v2!"); 

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
		throw Error("�������Ѿ�����!"); 
}

template <class ElemType>
void AdjListDirGraph<ElemType>::DeleteVex(const ElemType &e)
// ���������ɾ��Ԫ��ֵΪe�Ķ���			 
{
	int v;
	AdjListGraphArc *p, *q;
	for (v = 0; v < vexNum; v++)
		if (vexTable[v].data == e)
			break;
	if (v == vexNum)
		throw Error("ͼ�в�����Ҫɾ���Ķ���!");	// �׳��쳣

	for (int u = 0; u < vexNum; u++)           // ɾ������e�Ļ� 
		if (u != v)
			DeleteArc(u, v);

	p = vexTable[v].firstArc;                  // ɾ����e�����Ļ� 
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
// ���������ɾ������Ϊv1��v2�ı�			 
{
	if (v1 < 0 || v1 >= vexNum)
		throw Error("v1���Ϸ�!");	// �׳��쳣
	if (v2 < 0 || v2 >= vexNum)
		throw Error("v2���Ϸ�!");	// �׳��쳣
	if (v1 == v2) throw
		Error("v1���ܵ���v2!");		// �׳��쳣

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
		Error("v1��v2û�л���");		// �׳��쳣
}

template <class ElemType>
Status AdjListDirGraph<ElemType>::GetTag(int v) const
// ������������ض���v�ı�־		 
{
	if (v < 0 || v >= vexNum)
		throw Error("v���Ϸ�!");		// �׳��쳣

	return tag[v];
}



// �õ����ڽӱ�
template <class ElemType>
Status AdjListDirGraph<ElemType>::GetRevAdjList(AdjListDirGraph<ElemType>& list) const
{
	// ���ڽӱ��У�ĳ�ڽӵ��趨Ϊָ��õ�ĵ㡣
	list.vexNum = this->vexNum;
	list.arcNum = 0;
 
	//		������������
	for (int v = 0; v < list.vexNum; v++)
	{
		list.tag[v] = UNVISITED;
		list.vexTable[v].data = this->vexTable[v].data;
		list.vexTable[v].firstArc = NULL;
	}

	//		����ԭͼ���������ڽӱ���ڱ����ݣ�
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
// ������������ö���v�ı�־Ϊval		 
{
	if (v < 0 || v >= vexNum)
		throw Error("v���Ϸ�!");		// �׳��쳣

	tag[v] = val;
}

template <class ElemType>
AdjListDirGraph<ElemType>::AdjListDirGraph(const AdjListDirGraph<ElemType> &g)
// ���������������ͼ���ڽӾ���g����������ͼ���ڽӾ���g�������ƹ��캯��
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
// ���������������ͼ���ڽӾ���g��ֵ����ǰ����ͼ���ڽӾ��󡪡���ֵ�������
{
	if (&g != this)
	{
		Clear();                                    // �ͷŵ�ǰ����ͼ�߽��
		delete[]tag;								// �ͷŵ�ǰ����ͼ��־���� 
		delete[]vexTable;							// �ͷŵ�ǰ����ͼ����� 

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

// ��ʾ�ڽӾ�������ͼ
template <class ElemType>
void AdjListDirGraph<ElemType>::Display()
{
	AdjListGraphArc* p;
	std::cout << "����ͼ����" << vexNum << "�����㣬" << arcNum << "���ߡ�" << std::endl;
	
	for (int v = 0; v < vexNum; v++) 
	{	// ��ʾ��v���ڽ�����
		std::cout << vexTable[v].data << ":\t(" << v << ")";				// ��ʾ�����
		p = vexTable[v].firstArc;
		while (p != nullptr) 
		{
			std::cout << "-->(" << p->adjVex << ")";
			p = p->nextArc;
		}
		std::cout << std::endl;
	}
}


// ��ӡ����ΪIndex��һ���ڽ�����
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


// ͼ�Ĺ������(breadth firsts)����
template <class ElemType>
void BFSTraverse(const AdjMatrixUndirGraph<ElemType> &g, void(*Visit)(const ElemType &))
{
	int v;
	for (v = 0; v < g.GetVexNum(); v++)
		g.SetTag(v, UNVISITED);				// ��ÿ��������δ���ʱ�־

	for (v = 0; v < g.GetVexNum(); v++)
		if (g.GetTag(v) == UNVISITED)
			BFS(g, v, Visit); 				// ����δ���ʵĶ���v��ʼ���й����������
}


// ͼ�Ĺ����������(breadth first search)
template <class ElemType>
void BFS(const AdjMatrixUndirGraph<ElemType>& g, int v, void(*Visit)(const ElemType&))
{
	// ����������Ӷ���v�������й����������
	LinkQueue<int> q;
	int u, w;
	ElemType e;
	g.SetTag(v, VISITED);						// �����ʱ�־
	g.GetElem(v, e);							// ȡ����v������Ԫ��ֵ 
	Visit(e);									// ���ʶ���v
	q.EnQueue(v);	                            // ����v��� 
	while (!q.IsEmpty()) {
		q.DelQueue(u);
		for (w = g.FirstAdjVex(u); w != -1; w = g.NextAdjVex(u, w))
			if (g.GetTag(w) == UNVISITED) 
			{ 
				// ��u��δ���ʹ����ڽӶ���w���з���
				g.SetTag(w, VISITED);
				g.GetElem(w, e);
				Visit(e);
				q.EnQueue(w);
			}
	}
}


// ͼ���������(depth firsts)����
template <class ElemType>
void DFSTraverse(const AdjMatrixUndirGraph<ElemType> &g, void(*Visit)(const ElemType &))
{
	int v;
	for (v = 0; v < g.GetVexNum(); v++)
		g.SetTag(v, UNVISITED);// ��ÿ����������δ���ʱ�־

	for (v = 0; v < g.GetVexNum(); v++)

		if (g.GetTag(v) == UNVISITED)
			DFS(g, v, Visit);// ����δ���ʵĶ���v��ʼ��������������� 
}

// ͼ�������������(depth firsts search)
template <class ElemType>
void DFS(const AdjMatrixUndirGraph<ElemType> &g, int v, void(*Visit)(const ElemType &))
{
	ElemType e;
	g.SetTag(v, VISITED);		// ���ö���v�ѷ��ʱ�־
	g.GetElem(v, e);			// ȡ����v������Ԫ��ֵ 
	Visit(e);					// ���ʶ���v
	for (int w = g.FirstAdjVex(v); w != -1; w = g.NextAdjVex(v, w))
	{
		if (g.GetTag(w) == UNVISITED)
		{
			DFS(g, w, Visit);	// ��v����δ���ʹ����ڽӶ���w��ʼ���������������
		}
	}

}


template <class ElemType, class WeightType>
KruskalEdge<ElemType, WeightType>::KruskalEdge(ElemType v1, ElemType v2, WeightType w)
// �������: �ɶ���v1��v2��Ȩw����ߡ������캯��
{	// ���캯��
	vertex1 = v1;					// ����vertex1
	vertex2 = v2;					// ����vertex2
	weight = w;						// Ȩweight
}

template <class ElemType, class WeightType>
bool KruskalEdge<ElemType, WeightType>::operator <= (const KruskalEdge<ElemType, WeightType> &Ed)
// �������������<=��ϵ����
{
	return (weight <= Ed.weight);
}

template <class ElemType, class WeightType>
bool KruskalEdge<ElemType, WeightType>::operator > (const KruskalEdge<ElemType, WeightType> &Ed)
// �������������>��ϵ����
{
	return (weight > Ed.weight);
}


template<class ElemType, class WeightType>
KruskalEdge<ElemType, WeightType> &KruskalEdge<ElemType, WeightType>::operator = (const KruskalEdge<ElemType, WeightType> &Ed)
// �����������ջcopy��ֵ����ǰջ--��ֵ�������
{
	if (&Ed != this) {
		vertex1 = Ed.vertex1;					// ����vertex1
		vertex2 = Ed.vertex2;					// ����vertex2
		weight = Ed.weight;						// Ȩweight
	}
	return *this;
}


#if 0
// ��Kruskal�㷨������g����С����������
template <class ElemType, class WeightType>
void MiniSpanTreeKruskal(const AdjMatrixUndirNetwork<ElemType, WeightType> &g)
{
	int count, VexNum = g.GetVexNum();
	KruskalEdge<ElemType, WeightType> KEdge;
	MinHeap<KruskalEdge<ElemType, WeightType>> ha(g.GetEdgeNum());
	ElemType  *kVex, v1, v2;
	kVex = new ElemType[VexNum];	// ���嶥������,�洢������Ϣ 
	for (int i = 0; i < VexNum; i++)
		g.GetElem(i, kVex[i]);
	UFSets<ElemType> f(kVex, VexNum);// ���ݶ������鹹�첢�鼯 
	for (int v = 0; v < g.GetVexNum(); v++)
		for (int u = g.FirstAdjVex(v); u >= 0; u = g.NextAdjVex(v, u))
			if (v < u) {	// ��v < u�ı߲��뵽��С�� 
				g.GetElem(v, v1);
				g.GetElem(u, v2);
				KEdge.vertex1 = v1;
				KEdge.vertex2 = v2;
				KEdge.weight = g.GetWeight(v, u);
				ha.Insert(KEdge);
			}
	count = 0;					    // ��ʾ�Ѿ���ѡ�ı���

	while (count < VexNum - 1) {
		ha.DeleteTop(KEdge);        // �ӶѶ�ȡһ����
		v1 = KEdge.vertex1;
		v2 = KEdge.vertex2;
		if (f.Differ(v1, v2)) {	// ���������������㲻��ͬһ������
			cout << "��:( " << v1 << ", " << v2 << " ) Ȩ:" << KEdge.weight << endl; // ����߼�Ȩֵ
			f.Union(v1, v2);		// �������������ڵ����ϲ���һ����
			count++;
		}
	}
}
#endif

// ��Prim�㷨��u0����������g����С������
template <class ElemType, class WeightType>
void MiniSpanTreePrim(const AdjMatrixUndirNetwork<ElemType, WeightType> &g, int u0)
{
	// ��ʼ������������g,u0Ϊg��һ������
	WeightType min;
	ElemType v1, v2;
	int vexnum = g.GetVexNum();
	CloseArcType<ElemType, WeightType> * closearc;

	if (u0 < 0 || u0 >= vexnum)
		throw Error("����u0������!"); // �׳��쳣

	int u, v, k;						// ��ʾ�������ʱ���� 
	closearc = new CloseArcType<ElemType, WeightType>[vexnum];	// ����洢�ռ�
	for (v = 0; v < vexnum; v++)
	{
		// ��ʼ����������adjVex�����Զ�������־����ʱU = {v0}
		closearc[v].nearvertex = u0;
		closearc[v].lowweight = g.GetWeight(u0, v);
	}
	closearc[u0].nearvertex = -1;
	closearc[u0].lowweight = 0;

	for (k = 1; k < vexnum; k++)
	{
		// ѡ��������������g.GetVexNum() - 1������
		min = g.GetInfinity();
		v = u0;// ѡ��ʹ�ñ�<w, adjVex[w]>Ϊ����V-U��U�ľ�����СȨֵ�ı�
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
			cout << "��:( " << v1 << ", " << v2 << " ) Ȩ:" << min << endl; // ����߼�Ȩֵ
			closearc[v].lowweight = 0;		// ��w����U
			for (u = g.FirstAdjVex(v); u != -1; u = g.NextAdjVex(v, u)) 	// �¶��㲢��U������ѡ����С��
			{
				if (closearc[u].lowweight != 0 && (g.GetWeight(v, u) < closearc[u].lowweight))
				{
					// <v, w>Ϊ�µ���С��
					closearc[u].lowweight = g.GetWeight(v, u);
					closearc[u].nearvertex = v;
				}
			}

		}

	}
	delete[]closearc;			// �ͷŴ洢�ռ�  
}

