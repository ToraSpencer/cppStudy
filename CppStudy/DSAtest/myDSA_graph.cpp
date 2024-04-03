#include "myDSA_graph.h"


////////////////////////////////////////////////////////////////////////////////////////////// DEBUG �ӿ�
namespace MY_DEBUG
{
	static std::string g_debugPath = "E:/";

	// lambda������ӡstd::cout֧�ֵ����ͱ�����
	template <typename T>
	static auto disp = [](const T& arg)
	{
		std::cout << arg << ", ";
	};

	template <typename T>
	static auto dispCorrected = [](const T& arg)
	{
		if(arg == std::numeric_limits<T>::max())			// ʹ�õ�ǰ�������ֵ����ʾռλ����
			std::cout << "placeholder, ";
		else
			std::cout << arg << ", ";
	};


	static void debugDisp()			// �ݹ���ֹ
	{						//		�ݹ���ֹ��Ϊ�޲λ���һ�����������ζ����ԡ�
		std::cout << std::endl;
		return;
	}


	template <typename T, typename... Types>
	static void debugDisp(const T& firstArg, const Types&... args)
	{
		std::cout << firstArg << " ";
		debugDisp(args...);
	}


	// ���뺯���ӻ���ָ�����stl����
	template<typename T, typename F>
	void traverseSTL(T& con, F f)
	{
		std::for_each(con.begin(), con.end(), f);
		std::cout << std::endl;
	}


	// �������
	template<typename T, typename F>
	void revTraverseSTL(T& con, F f)
	{
		std::for_each(con.rbegin(), con.rend(), f);
		std::cout << std::endl;
	}
}
using namespace MY_DEBUG;



namespace GRAPH
{ 
	// build graph
	void test0() 
	{
		Graph g1({0, 1,2,3,4,5});

		g1.insertEdge(0, 1);
		g1.insertEdge(0, 2);
		g1.insertEdge(0, 3);
		g1.insertEdge(0, 4);
		g1.insertEdge(0, 5);
		g1.insertEdge(1, 2);
		g1.insertEdge(2, 3);
		g1.insertEdge(3, 4);
		g1.insertEdge(4, 5);
		g1.insertEdge(0, 5);

		debugDisp("test0 finished.");
	}


	// graph�ĸ��ֱ���
	void test1() 
	{

	}


	// GRAPH�е���̻�
	/*
		����һ���� n ������� ˫��ͼ��ÿ�����㰴�� 0 �� n - 1 ��ǡ�
		ͼ�еı��ɶ�ά�������� edges ��ʾ������ edges[i] = [ui, vi] ��ʾ���� ui �� vi ֮�����һ���ߡ�
		ÿ�Զ������ͨ��һ�������ӣ����Ҳ����������������Ķ��㡣
		����ͼ�� ��� ���ĳ��ȡ���������ڻ����򷵻� -1 ��
				����ָ��ͬһ�ڵ㿪ʼ�ͽ���������·���е�ÿ���߽�ʹ��һ�Ρ�

		ʾ�� 1��
				���룺n = 7, edges = [[0,1],[1,2],[2,0],[3,4],[4,5],[5,6],[6,3]]
				�����3
				���ͣ�������С��ѭ���ǣ�0 -> 1 -> 2 -> 0 
		ʾ�� 2��
				���룺n = 4, edges = [[0,1],[0,2]]
				�����-1
				���ͣ�ͼ�в�����ѭ��

		int findShortestCycle(int n, vector<vector<int>>& edges) {}
	*/
	void test2() 
	{

	}


	// GRAPH���·��
	/*
		����һ���� n ���ڵ�������Ȩͼ���ڵ���Ϊ 0 �� n - 1 ��
		ͼ�еĳ�ʼ�������� edges ��ʾ������ edges[i] = [fromi, toi, edgeCosti] ��ʾ�� fromi �� toi ��һ������Ϊ edgeCosti �ıߡ�
		����ʵ��һ�� Graph �ࣺ
				Graph(int n, int[][] edges) ��ʼ��ͼ�� n ���ڵ㣬�������ʼ�ߡ�
				addEdge(int[] edge) ��߼������һ���ߣ����� edge = [from, to, edgeCost] ��
						���ݱ�֤���������֮ǰ��Ӧ�������ڵ�֮��û������ߡ�
				int shortestPath(int node1, int node2) ���شӽڵ� node1 �� node2 ��·�� ��С ���ۡ�
						���·�������ڣ����� -1 ��һ��·���Ĵ�����·�������бߴ���֮�͡�

		���룺
				["Graph", "shortestPath", "shortestPath", "addEdge", "shortestPath"]
				[[4, [[0, 2, 5], [0, 1, 2], [1, 2, 1], [3, 0, 3]]], [3, 2], [0, 3], [[1, 3, 4]], [0, 3]]
		�����
				[null, 6, -1, null, 6]

		���ͣ�
				Graph g = new Graph(4, [[0, 2, 5], [0, 1, 2], [1, 2, 1], [3, 0, 3]]);
				g.shortestPath(3, 2);			// ���� 6 ���� 3 �� 2 �����·�����һ��ͼ��ʾ��3 -> 0 -> 1 -> 2 ���ܴ���Ϊ 3 + 2 + 1 = 6 ��
				g.shortestPath(0, 3);			// ���� -1 ��û�д� 0 �� 3 ��·����
				g.addEdge([1, 3, 4]);			// ���һ���ڵ� 1 ���ڵ� 3 �ıߣ��õ��ڶ���ͼ��
				g.shortestPath(0, 3);			// ���� 6 ���� 0 �� 3 �����·��Ϊ 0 -> 1 -> 3 ���ܴ���Ϊ 2 + 4 = 6 ��

		class Graph {
			public:
				Graph(int n, vector<vector<int>>& edges) {}
				void addEdge(vector<int> edge) {}
				int shortestPath(int node1, int node2) {}
			};

		Your Graph object will be instantiated and called as such:
			 * Graph* obj = new Graph(n, edges);
			 * obj->addEdge(edge);
			 * int param_2 = obj->shortestPath(node1,node2); 
	*/
	void test3() 
	{

	}


	// practice�����ҵ�С��ķ���
	/*
		С������ n ���ˣ����� 1 �� n ��˳���š����Գƣ���Щ������һ����������С�򷨹١�
		���С�򷨹���Ĵ��ڣ���ô��
				1. С�򷨹ٲ��������κ��ˡ�
				2. ÿ���ˣ�����С�򷨹٣���������λС�򷨹١�
				ֻ��һ����ͬʱ�������� 1 ������ 2 ��
				����һ������ trust ������ trust[i] = [ai, bi] ��ʾ���Ϊ ai �������α��Ϊ bi ���ˡ�
		���С�򷨹ٴ��ڲ��ҿ���ȷ��������ݣ��뷵�ظ÷��ٵı�ţ����򣬷��� -1 ��

		ʾ�� ��
				���룺n = 2, trust = [[1,2]]
				�����2
				���룺n = 3, trust = [[1,3],[2,3]]
				�����3
				���룺n = 3, trust = [[1,3],[2,3],[3,1]]
				�����-1
	*/
	int findJudge(int N, const std::vector<std::vector<int>>& trust)
	{
		/*
			trust�е������൱��graph�е�����ߣ�
			����ȼ��ڣ�
					�ж�n���ڵ������ͼ���Ƿ���ĳ���ڵ�ͬʱ���㣺
							1. ���Ϊ(n - 1)��
							2. ����Ϊ0��
		*/
		const int k = N + 1;
		std::vector<bool> trustPeople(k, false);
		std::vector<int> beTrust(k, 0);									 // ����������
		for (auto& v : trust)
		{
			trustPeople[v[0]] = true;
			beTrust[v[1]]++;
		}
		for (int i = 1; i <= N; ++i)
			if (!trustPeople[i] && beTrust[i] == N - 1)
				return i;
		return -1;
	}

	void test4()
	{
		debugDisp("result == ", findJudge(3, std::vector<std::vector<int>>{ \
			std::vector<int>{1, 3}, std::vector<int>{2, 3} }));
		 
	}

}
