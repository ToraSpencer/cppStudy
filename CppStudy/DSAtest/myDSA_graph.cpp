#include "myDSA_graph.h"


////////////////////////////////////////////////////////////////////////////////////////////// DEBUG 接口
namespace MY_DEBUG
{
	static std::string g_debugPath = "E:/";

	// lambda——打印std::cout支持的类型变量。
	template <typename T>
	static auto disp = [](const T& arg)
	{
		std::cout << arg << ", ";
	};

	template <typename T>
	static auto dispCorrected = [](const T& arg)
	{
		if(arg == std::numeric_limits<T>::max())			// 使用当前类型最大值来表示占位符；
			std::cout << "placeholder, ";
		else
			std::cout << arg << ", ";
	};


	static void debugDisp()			// 递归终止
	{						//		递归终止设为无参或者一个参数的情形都可以。
		std::cout << std::endl;
		return;
	}


	template <typename T, typename... Types>
	static void debugDisp(const T& firstArg, const Types&... args)
	{
		std::cout << firstArg << " ";
		debugDisp(args...);
	}


	// 传入函数子或函数指针遍历stl容器
	template<typename T, typename F>
	void traverseSTL(T& con, F f)
	{
		std::for_each(con.begin(), con.end(), f);
		std::cout << std::endl;
	}


	// 反向遍历
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


	// graph的各种遍历
	void test1() 
	{

	}


	// GRAPH中的最短环
	/*
		现有一个含 n 个顶点的 双向图，每个顶点按从 0 到 n - 1 标记。
		图中的边由二维整数数组 edges 表示，其中 edges[i] = [ui, vi] 表示顶点 ui 和 vi 之间存在一条边。
		每对顶点最多通过一条边连接，并且不存在与自身相连的顶点。
		返回图中 最短 环的长度。如果不存在环，则返回 -1 。
				环是指以同一节点开始和结束，并且路径中的每条边仅使用一次。

		示例 1：
				输入：n = 7, edges = [[0,1],[1,2],[2,0],[3,4],[4,5],[5,6],[6,3]]
				输出：3
				解释：长度最小的循环是：0 -> 1 -> 2 -> 0 
		示例 2：
				输入：n = 4, edges = [[0,1],[0,2]]
				输出：-1
				解释：图中不存在循环

		int findShortestCycle(int n, vector<vector<int>>& edges) {}
	*/
	void test2() 
	{

	}


	// GRAPH最短路径
	/*
		给你一个有 n 个节点的有向带权图，节点编号为 0 到 n - 1 。
		图中的初始边用数组 edges 表示，其中 edges[i] = [fromi, toi, edgeCosti] 表示从 fromi 到 toi 有一条代价为 edgeCosti 的边。
		请你实现一个 Graph 类：
				Graph(int n, int[][] edges) 初始化图有 n 个节点，并输入初始边。
				addEdge(int[] edge) 向边集中添加一条边，其中 edge = [from, to, edgeCost] 。
						数据保证添加这条边之前对应的两个节点之间没有有向边。
				int shortestPath(int node1, int node2) 返回从节点 node1 到 node2 的路径 最小 代价。
						如果路径不存在，返回 -1 。一条路径的代价是路径中所有边代价之和。

		输入：
				["Graph", "shortestPath", "shortestPath", "addEdge", "shortestPath"]
				[[4, [[0, 2, 5], [0, 1, 2], [1, 2, 1], [3, 0, 3]]], [3, 2], [0, 3], [[1, 3, 4]], [0, 3]]
		输出：
				[null, 6, -1, null, 6]

		解释：
				Graph g = new Graph(4, [[0, 2, 5], [0, 1, 2], [1, 2, 1], [3, 0, 3]]);
				g.shortestPath(3, 2);			// 返回 6 。从 3 到 2 的最短路径如第一幅图所示：3 -> 0 -> 1 -> 2 ，总代价为 3 + 2 + 1 = 6 。
				g.shortestPath(0, 3);			// 返回 -1 。没有从 0 到 3 的路径。
				g.addEdge([1, 3, 4]);			// 添加一条节点 1 到节点 3 的边，得到第二幅图。
				g.shortestPath(0, 3);			// 返回 6 。从 0 到 3 的最短路径为 0 -> 1 -> 3 ，总代价为 2 + 4 = 6 。

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


	// practice——找到小镇的法官
	/*
		小镇里有 n 个人，按从 1 到 n 的顺序编号。传言称，这些人中有一个暗地里是小镇法官。
		如果小镇法官真的存在，那么：
				1. 小镇法官不会信任任何人。
				2. 每个人（除了小镇法官）都信任这位小镇法官。
				只有一个人同时满足属性 1 和属性 2 。
				给你一个数组 trust ，其中 trust[i] = [ai, bi] 表示编号为 ai 的人信任编号为 bi 的人。
		如果小镇法官存在并且可以确定他的身份，请返回该法官的编号；否则，返回 -1 。

		示例 ：
				输入：n = 2, trust = [[1,2]]
				输出：2
				输入：n = 3, trust = [[1,3],[2,3]]
				输出：3
				输入：n = 3, trust = [[1,3],[2,3],[3,1]]
				输出：-1
	*/
	int findJudge(int N, const std::vector<std::vector<int>>& trust)
	{
		/*
			trust中的数对相当于graph中的有向边；
			问题等价于：
					判断n个节点的有向图中是否有某个节点同时满足：
							1. 入度为(n - 1)；
							2. 出度为0；
		*/
		const int k = N + 1;
		std::vector<bool> trustPeople(k, false);
		std::vector<int> beTrust(k, 0);									 // 被别人相信
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
