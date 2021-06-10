#include "DSA_图.h"

#define EPS 1e-10					//定义非常小的一个量EPSilon，当浮点数不大于这个值时，视为0
#define PI 3.14159

//***************类方法实现
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
void DSA_graph_module::test0(void) 
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
void DSA_graph_module::test1(void) 
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


// 测试工作项目中的网格结构，及其与自定义graph类的转换：
void DSA_graph_module::test2(void) 
{
	VSMesh mesh;
	mesh.LoadFromFile("../材料/tooth.obj");

	std::cout << "顶点数：" << mesh.vVertice.size();
	std::cout << "三角片数：" << mesh.vSurface.size();

	// 将VSMesh对象转换为邻接表表示的无权有向图：
	

	//		拷贝顶点数据：
	AdjListDirGraph<VFVECTOR3> meshGraph(&mesh.vVertice[0], mesh.vVertice.size(), mesh.vVertice.size() + 1);

	//		插入边数据——遍历每一个三角片，插入其三条有向边
	for (const auto& tri: mesh.vSurface) 
	{
		meshGraph.InsertArc(tri.x, tri.y);
		meshGraph.InsertArc(tri.y, tri.z);
		meshGraph.InsertArc(tri.z, tri.x);
	}


	// 将图表示为VSMesh对象：
	VSMesh mesh2;

	//		拷贝顶点数据：
	unsigned versCount = meshGraph.GetVexNum();
	mesh2.vVertice.resize(versCount);
	for (unsigned i = 0; i< versCount; i++) 
	{
		meshGraph.GetElem(i, mesh2.vVertice[i]);
	}

	//	   生成三角片数据：
	AdjListGraphVex<VFVECTOR3>* pVer = nullptr;
	for (unsigned i = 0; i< versCount; ++i) 
	{
		pVer = &meshGraph.vexTable[i];					// 指向第i个图节点
		AdjListGraphArc* pArc = pVer->firstArc;

		while (pArc != nullptr)			// 遍历索引为i的顶点的所有邻边；
		{
			unsigned index2 = pArc->adjVex;		
			if (index2)
			{
				continue;				// 要求三角片中第一个顶点索引最小；
			}
			AdjListGraphArc* pArc2 = meshGraph.vexTable[index2].firstArc;
		
			while (pArc2 != nullptr)		// 遍历三角片第二个顶点（可能成为）的所有邻边；
			{
				if (pArc2->adjVex) 
				{

				}
				pArc2 = pArc2->nextArc;
			}

			pArc = pArc->nextArc;
		}

	}
}


void DSA_graph_module::test3(void) {}


void DSA_graph_module::test4(void) {}



void DSA_graph_module::test5(void) {}



void DSA_graph_module::test6(void) {}
