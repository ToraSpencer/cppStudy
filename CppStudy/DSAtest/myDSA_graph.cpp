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


	static void debugWriteVers(const char* fileName, const std::vector<verF>& vers)
	{
		char path[512] = { 0 };
		snprintf(path, 512, "%s%s.obj", g_debugPath.c_str(), fileName);
		writeOBJ(path, vers);
	}


	static void debugWriteVers(const char* fileName, const std::vector<verD>& vers)
	{
		char path[512] = { 0 };
		snprintf(path, 512, "%s%s.obj", g_debugPath.c_str(), fileName);
		writeOBJ(path, vers);
	}


	static void debugWriteMesh(const char* fileName, const triMeshD& triMesh)
	{
		char path[512] = { 0 };
		snprintf(path, 512, "%s%s.obj", g_debugPath.c_str(), fileName);
		writeOBJ(path, triMesh);
	}


	static void debugWriteMesh(const char* fileName, const triMeshF& triMesh)
	{
		char path[512] = { 0 };
		snprintf(path, 512, "%s%s.obj", g_debugPath.c_str(), fileName);
		writeOBJ(path, triMesh);
	}

}
using namespace MY_DEBUG;

 

namespace GRAPH
{
	// build graph
	void getCircleVers3D(std::vector<verF>& vers, const size_t versCount)
	{
		const float pi = 3.14159;
		vers.clear();
		vers.resize(versCount, verF{ 0, 0, 0 });
		for (size_t i = 1; i < versCount; ++i)
		{
			const float radius = ((i - 1) / 6 + 1) * 1.0;
			const float theta = (i - 1) % 6 * pi / 3;
			vers[i].x = radius * cos(theta);
			vers[i].y = radius * sin(theta);
		}
	}


	void test0()
	{
		using GraphEdge = SLlistNode<GraphNode<int>*>;		// 用存储顶点指针的链表节点来表示边；
		const float pi = 3.14159;

		Graph<int> g1({ 0, 1,2,3,4, 5 });
		g1.addEdge(0, 1);
		g1.addEdge(0, 2);
		g1.addEdge(0, 3);
		g1.addEdge(0, 4);
		g1.addEdge(0, 5);
		g1.addEdge(1, 2);
		g1.addEdge(2, 3);
		g1.addEdge(3, 4);
		g1.addEdge(4, 5);
		g1.addEdge(0, 5);

		// 
		const int nodesCount = g1.pnVec.size();

		// 建立图节点-节点索引映射表：
		std::unordered_map<GraphNode<int>*, int> map;
		for (int i = 0; i < g1.pnVec.size(); ++i)
			map.insert(std::make_pair(g1.pnVec[i], i));

		// 节点按索引映射为XOY平面上的坐标点；
		std::vector<verF> poses;
		getCircleVers3D(poses, g1.pnVec.size());

		// 所有节点格式的边数据转换为edgeI格式： 
		std::vector<edgeI> edges;
		for (const auto pn : g1.pnVec)					// 收集每个顶点发出的第一条边；
		{
			if (nullptr == pn->pFirstEdge)
				continue;
			traverseList(pn->pFirstEdge, [&map, &edges, &pn](GraphEdge* pe)
				{
					if (nullptr == pe)
						return;
					int vaIdx = pn->val;
					int vbIdx = map[pe->val];
					edges.push_back(edgeI(vaIdx, vbIdx));
				});
		}

		writeOBJ("E:/g1.obj", poses, edges);

		debugDisp("test0 finished.");
	}


	void test00()
	{
		triMeshD mesh;
		readOBJ(mesh, "./myData/roundSurf.obj");
		Graph<verF> g;
		triMesh2Graph(g, mesh);
		objWriteGraph3D("E:/graph.obj", g);

		debugDisp("test00 finished.");
	}


	// graph的各种遍历 
	void test1()
	{
		// 生成深度优先遍历的路径，转换为边的形式打印出来：
		triMeshD mesh;
		std::vector<edgeI> path;

		std::vector<verF> vers;
		getCircleVers3D(vers, 8);
		Graph<verF> g(vers);
		g.addEdge(0, 1);
		g.addEdge(0, 2);
		g.addEdge(0, 3);
		g.addEdge(0, 4);
		g.addEdge(0, 5);
		g.addEdge(1, 2);
		g.addEdge(2, 3);
		g.addEdge(3, 4);
		g.addEdge(4, 5);
		g.addEdge(0, 5);
		g.addEdge(5, 6);
		g.addEdge(6, 7);

		const int versCount = static_cast<int>(g.pnVec.size());
		int vaIdx = 0;
		int vbIdx = 0;
		objWriteGraph3D("E:/graph.obj", g);

		// 顶点-索引映射表：
		std::unordered_map<GraphNode<verF>*, int> map;
		for (int i = 0; i < versCount; ++i)
			map.insert(std::make_pair(g.pnVec[i], i));



		debugDisp("test1 finished.");
	}


	// GRAPH中的最短环——to be completed
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
		// 0. input data:
		std::vector<std::vector<int>> edges{ {0, 1},{1, 2},{2, 0},{3, 4},{4, 5},{5, 6},{6, 3} };

		// 1. 生成邻接表：
		std::vector<std::vector<int>> vvList;
		vvEdges2vvList(vvList, edges, false);

		// 2. 基于DFS的方法搜索环（暂时不考虑多联通情形）
		int index = 0;
		const int n = vvList.size();				// 节点数量；
		std::stack<int> st;
		std::vector<bool> visited(n, false);
		st.push(0);
		while (!st.empty())
		{
			// w1
			index = st.top();
			st.pop();
			if (visited[index])
				continue;

			// w2. 操作当前节点
			visited[index] = true;


			// w3. 当前节点1领域内节点入栈：
			
		}



		debugDisp("test2 finished.");
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
	void test4()
	{
		auto findJudge = [](int N, const std::vector<std::vector<int>>&trust)->int
		{
			/*
				trust中的数对相当于graph中的有向边；
				问题等价于：
						判断n个节点的有向图中是否有某个节点同时满足：
								1. 入度为(n - 1)；
								2. 出度为0；
			*/
			const int k = N + 1;
			std::vector<bool> trustPeople(k, false);			// 第i个元素表示节点i是否相信某一个人
			std::vector<int> beTrust(k, 0);							// 第i个元素表示节点i被多少个人相信；
			for (auto& v : trust)
			{
				trustPeople[v[0]] = true;
				beTrust[v[1]]++;
			}
			for (int i = 1; i <= N; ++i)
				if (!trustPeople[i] && beTrust[i] == N - 1)		// 验证这个不相信任何人的节点，是否被N-1个人相信；
					return i;
			return -1;
		};

		debugDisp("result == ", findJudge(3, std::vector<std::vector<int>>{ \
			std::vector<int>{1, 3}, std::vector<int>{2, 3}, std::vector<int>{3, 1}}));
		 
	}
	 

	// practice——课程表：
	/*
		你这个学期必须选修 numCourses 门课程，记为 0 到 numCourses - 1 。
		在选修某些课程之前需要一些先修课程。
		先修课程按数组 prerequisites 给出，其中 prerequisites[i] = [ai, bi] ，表示如果要学习课程 ai 则 必须 先学习课程  bi 。
		例如，先修课程对 [0, 1] 表示：想要学习课程 0 ，你需要先完成课程 1 。
		请你判断是否可能完成所有课程的学习？如果可以，返回 true ；否则，返回 false 。

		示例 1：
				输入：numCourses = 2, prerequisites = [[1,0]]
				输出：true
				解释：总共有 2 门课程。学习课程 1 之前，你需要完成课程 0 。这是可能的

		示例 2：
				输入：numCourses = 2, prerequisites = [[1,0],[0,1]]
				输出：false

		
		bool canFinish(int numCourses, vector<vector<int>>& prerequisites) 
	*/
	void test5() 
	{
		/*
			只要在prerequisites对应的有向图中，不存在环，就可以完成所有课程的学习；否则不可以；
		*/

		auto canFinish = [](const int numCourses, \
			const std::vector<std::vector<int>>& prerequisites)->bool
			{ 
				// 0. 生成邻接表：（注意prerequisites中的[a, b]视为边[b, a]）
				std::vector<std::vector<int>> vvList;
				int index = 0;
				const int n = numCourses;
				const int edgesCount = static_cast<int>(prerequisites.size());
				vvList.resize(n);
				for (int i = 0; i < edgesCount; ++i)
				{
					index = prerequisites[i][1];
					vvList[index].push_back(prerequisites[i][0]);
				}

				// 1. 统计所有节点的入度
				std::vector<int> relyCourse(n, 0);
				for (int i = 0; i < edgesCount; ++i) 
				{
					index = prerequisites[i][0];
					relyCourse[index]++;
				}

				// 2. 找到第一个入度为0的节点； 
				std::list<int> base;				// 可以作为最基础课程的课程，视为一个单连通图的根节点；
				for (int i = 0; i < n; ++i)
					if (0 == relyCourse[i])
						base.push_back(i);
				if (base.empty())
					return false;						// 所有节点入度都不为0，说明找不到可以作为最基础课程的课程；

				// 3. 从第一个入度为0的节点开始，进行广度优先遍历（！！！注意图可能不是单连通的！！！）
				std::queue<int> qt;
				int startIdx = base.front();
				base.pop_front();
				qt.push(startIdx);
				while (!qt.empty() || !base.empty())
				{ 
					if (qt.empty())
					{
						// w4. 若队列已空，则尝试压入其他联通区域的根节点； 
						if (!base.empty())
						{
							startIdx = base.front();
							base.pop_front();
							qt.push(startIdx);
						} 
					}
					else
					{
						// w1. 队首节点出队，作为当前节点；
						index = qt.front();
						qt.pop(); 

						// w2. 对当前节点的操作——修改其他节点的入度：假设删除该节点，被入的节点入度-1；
						for (const auto& toIdx : vvList[index])
							relyCourse[toIdx]--;

						// w3. 当前节点的未访问的1领域节点压入队列；
						for (const auto& indexNbr : vvList[index])
							if (0 == relyCourse[indexNbr])					// 只有入度减到0的课程才可以修；
								qt.push(indexNbr);
					} 
				}

				// 4. 队列清空之后，检查是否还有节点入度不为0：
				int accum = std::accumulate(relyCourse.begin(), relyCourse.end(), 0);
				return (0 == accum);			// 等于0表示此时所有节点入度都为0，原图中不存在环，可以完成所有课程的学习；
			};

		debugDisp("canFinish(3, { {1, 0}, {1, 2}, {0, 1} }) == ", canFinish(3, { {1, 0}, {1, 2}, {0, 1} }));
		debugDisp("canFinish(2, { {1, 0}, {0, 1} }) == ", canFinish(2, { {1, 0}, {0, 1} }));
		debugDisp("canFinish(5, { {1, 4} ,{2, 4}, {3, 1}, {3, 2} }) == ", canFinish(5, { {1, 4} ,{2, 4}, {3, 1}, {3, 2} }));
		debugDisp("test5 finished.");
	}


	// practice——统计无向图中无法互相到达点对数
	/*
		给你一个整数 n ，表示一张 无向图 中有 n 个节点，编号为 0 到 n - 1 。
		同时给你一个二维整数数组 edges ，其中 edges[i] = [ai, bi] 表示节点 ai 和 bi 之间有一条 无向 边。
		请你返回 无法互相到达 的不同 点对数目 。


		
		示例 1： 
			输入：n = 3, edges = [[0,1],[0,2],[1,2]]
			输出：0
			解释：所有点都能互相到达，意味着没有点对无法互相到达，所以我们返回 0 。
		
		示例 2： 
			输入：n = 7, edges = [[0,2],[0,5],[2,4],[1,6],[5,4]]
			输出：14
			解释：总共有 14 个点对互相无法到达：
			[[0,1],[0,3],[0,6],[1,2],[1,3],[1,4],[1,5],[2,3],[2,6],[3,4],[3,5],[3,6],[4,6],[5,6]]
			所以我们返回 14 。

		答案1——深度优先搜索：
				连通分量还可以通过深度优先搜索来划分。
				首先将输入edges构造成临接表graph
				然后构造函数DFS，作用为遍历与它在同一个连通分量中并且还未访问过的点，并返回访问的点数。
				遍历所有点，如果当前点还没有访问过，则说明遇到了一个新的连通分量，
						通过DFS来计算当前连通分量的点数count，
						这个连通分量中的所有点与这个连通分量中的所有点都无法相互到达，
						因此这个连通分量中的点对答案的贡献是count * (n - count)。
				每个点对会被计算两次，因此最后结果需要除以2。
 
		   long long countPairs(int n, vector<vector<int>>& edges) 
		   {
					vector<vector<int>> graph(n);
					for (const auto &edge : edges) 
					{
						graph[edge[0]].push_back(edge[1]);
						graph[edge[1]].push_back(edge[0]);
					}

					vector<bool> visited(n, false);
					function<int(int)> dfs = [&](int x) -> int {
						visited[x] = true;
						int count = 1;
						for (auto y : graph[x]) {
							if (!visited[y]) {
								count += dfs(y);
							}
						}
						return count;
					};

					long long res = 0;
					for (int i = 0; i < n; i++) {
						if (!visited[i]) {
							long long count = dfs(i);
							res += count * (n - count);
						}
					}
					return res / 2;
				}
	 
	*/
	void test6() 
	{

	}
}
