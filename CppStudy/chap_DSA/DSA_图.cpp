#include "DSA_图.h"

#define EPS 1e-10					//定义非常小的一个量EPSilon，当浮点数不大于这个值时，视为0
#define PI 3.14159



AdjListGraphArc::AdjListGraphArc()
{
	this->adjVex = -1;
	this->nextArc = nullptr;
}


AdjListGraphArc::AdjListGraphArc(int v, AdjListGraphArc *next)
{
	adjVex = v;
	nextArc = next;
}


virtualModule* DSA_graph_module::getInstance()		// 线程不安全的单例模式
{
	if (nullptr != p_moduleIns)
	{
		delete p_moduleIns;
	}
	p_moduleIns = new DSA_graph_module;
	return p_moduleIns;
}


// 构造图实例、深度优先遍历、广度优先遍历。
void DSA_graph_module::test0() 
{
	AdjListDirGraph<int> intGraph1;
	intGraph1.InsertVex(0);
	intGraph1.InsertVex(1);
	intGraph1.InsertVex(2);
	intGraph1.InsertArc(0, 1);
	intGraph1.InsertArc(1, 2);
	intGraph1.InsertArc(2, 0);
	intGraph1.Display();

	float numf[10] = {1,2,3,4,5,6,7,8,9,10};
	AdjMatrixUndirGraph<float> floatGraph1(numf, 10);
	floatGraph1.InsertArc(1, 2);
	floatGraph1.InsertArc(3, 2);
	floatGraph1.InsertArc(1, 5);
	floatGraph1.InsertArc(9, 0);
	floatGraph1.InsertArc(7, 8);
	floatGraph1.InsertArc(4, 6);
	floatGraph1.InsertArc(1, 7);
	floatGraph1.Display();

}
 

// 测试逆邻接表
void DSA_graph_module::test1() 
{
	int arrInt[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
	AdjListDirGraph<int> graph1(arrInt, 10);
	graph1.InsertArc(0, 2);
	graph1.InsertArc(0, 4);
	graph1.InsertArc(0, 6);
	graph1.InsertArc(0, 8);
	graph1.InsertArc(1, 2);
	graph1.InsertArc(1, 3);
	graph1.InsertArc(2, 9);
	graph1.InsertArc(3, 8);
	graph1.InsertArc(4, 6);
	graph1.InsertArc(5, 1);
	graph1.InsertArc(5, 2);
	graph1.Display();

	graph1.displayRow(0);

	AdjListDirGraph<int> revGraph1;
	graph1.GetRevAdjList(revGraph1);
	revGraph1.Display();

 
}

 
void DSA_graph_module::test2() {}


void DSA_graph_module::test3() {}


void DSA_graph_module::test4() {}



void DSA_graph_module::test5() {}



void DSA_graph_module::test6() {}
