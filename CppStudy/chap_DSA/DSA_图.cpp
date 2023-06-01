#include "DSA_ͼ.h"

#define EPS 1e-10					//����ǳ�С��һ����EPSilon�������������������ֵʱ����Ϊ0
#define PI 3.14159

//***************�෽��ʵ��
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


virtualModule* DSA_graph_module::getInstance()		// �̲߳���ȫ�ĵ���ģʽ
{
	if (nullptr != p_moduleIns)
	{
		delete p_moduleIns;
	}
	p_moduleIns = new DSA_graph_module;
	return p_moduleIns;
}


// ����ͼʵ����������ȱ�����������ȱ�����
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
 

// �������ڽӱ�
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


// ���Թ�����Ŀ�е�����ṹ���������Զ���graph���ת����
void DSA_graph_module::test2(void) 
{
	VSMesh mesh;
	mesh.LoadFromFile("../����/tooth.obj");

	std::cout << "��������" << mesh.vVertice.size();
	std::cout << "����Ƭ����" << mesh.vSurface.size();

	// ��VSMesh����ת��Ϊ�ڽӱ��ʾ����Ȩ����ͼ��
	

	//		�����������ݣ�
	AdjListDirGraph<VFVECTOR3> meshGraph(&mesh.vVertice[0], mesh.vVertice.size(), mesh.vVertice.size() + 1);

	//		��������ݡ�������ÿһ������Ƭ�����������������
	for (const auto& tri: mesh.vSurface) 
	{
		meshGraph.InsertArc(tri.x, tri.y);
		meshGraph.InsertArc(tri.y, tri.z);
		meshGraph.InsertArc(tri.z, tri.x);
	}


	// ��ͼ��ʾΪVSMesh����
	VSMesh mesh2;

	//		�����������ݣ�
	unsigned versCount = meshGraph.GetVexNum();
	mesh2.vVertice.resize(versCount);
	for (unsigned i = 0; i< versCount; i++) 
	{
		meshGraph.GetElem(i, mesh2.vVertice[i]);
	}

	//	   ��������Ƭ���ݣ�
	AdjListGraphVex<VFVECTOR3>* pVer = nullptr;
	for (unsigned i = 0; i< versCount; ++i) 
	{
		pVer = &meshGraph.vexTable[i];					// ָ���i��ͼ�ڵ�
		AdjListGraphArc* pArc = pVer->firstArc;

		while (pArc != nullptr)			// ��������Ϊi�Ķ���������ڱߣ�
		{
			unsigned index2 = pArc->adjVex;		
			if (index2)
			{
				continue;				// Ҫ������Ƭ�е�һ������������С��
			}
			AdjListGraphArc* pArc2 = meshGraph.vexTable[index2].firstArc;
		
			while (pArc2 != nullptr)		// ��������Ƭ�ڶ������㣨���ܳ�Ϊ���������ڱߣ�
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
