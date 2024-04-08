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
		using GraphEdge = SLlistNode<GraphNode<int>*>;		// �ô洢����ָ�������ڵ�����ʾ�ߣ�
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

		// ����ͼ�ڵ�-�ڵ�����ӳ���
		std::unordered_map<GraphNode<int>*, int> map;
		for (int i = 0; i < g1.pnVec.size(); ++i)
			map.insert(std::make_pair(g1.pnVec[i], i));

		// �ڵ㰴����ӳ��ΪXOYƽ���ϵ�����㣻
		std::vector<verF> poses;
		getCircleVers3D(poses, g1.pnVec.size());

		// ���нڵ��ʽ�ı�����ת��ΪedgeI��ʽ�� 
		std::vector<edgeI> edges;
		for (const auto pn : g1.pnVec)					// �ռ�ÿ�����㷢���ĵ�һ���ߣ�
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


	// graph�ĸ��ֱ��� 
	void test1()
	{
		// ����������ȱ�����·����ת��Ϊ�ߵ���ʽ��ӡ������
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

		// ����-����ӳ���
		std::unordered_map<GraphNode<verF>*, int> map;
		for (int i = 0; i < versCount; ++i)
			map.insert(std::make_pair(g.pnVec[i], i));



		debugDisp("test1 finished.");
	}


	// GRAPH�е���̻�����to be completed
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
		// 0. input data:
		std::vector<std::vector<int>> edges{ {0, 1},{1, 2},{2, 0},{3, 4},{4, 5},{5, 6},{6, 3} };

		// 1. �����ڽӱ�
		std::vector<std::vector<int>> vvList;
		vvEdges2vvList(vvList, edges, false);

		// 2. ����DFS�ķ�������������ʱ�����Ƕ���ͨ���Σ�
		int index = 0;
		const int n = vvList.size();				// �ڵ�������
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

			// w2. ������ǰ�ڵ�
			visited[index] = true;


			// w3. ��ǰ�ڵ�1�����ڽڵ���ջ��
			
		}



		debugDisp("test2 finished.");
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
	void test4()
	{
		auto findJudge = [](int N, const std::vector<std::vector<int>>&trust)->int
		{
			/*
				trust�е������൱��graph�е�����ߣ�
				����ȼ��ڣ�
						�ж�n���ڵ������ͼ���Ƿ���ĳ���ڵ�ͬʱ���㣺
								1. ���Ϊ(n - 1)��
								2. ����Ϊ0��
			*/
			const int k = N + 1;
			std::vector<bool> trustPeople(k, false);			// ��i��Ԫ�ر�ʾ�ڵ�i�Ƿ�����ĳһ����
			std::vector<int> beTrust(k, 0);							// ��i��Ԫ�ر�ʾ�ڵ�i�����ٸ������ţ�
			for (auto& v : trust)
			{
				trustPeople[v[0]] = true;
				beTrust[v[1]]++;
			}
			for (int i = 1; i <= N; ++i)
				if (!trustPeople[i] && beTrust[i] == N - 1)		// ��֤����������κ��˵Ľڵ㣬�Ƿ�N-1�������ţ�
					return i;
			return -1;
		};

		debugDisp("result == ", findJudge(3, std::vector<std::vector<int>>{ \
			std::vector<int>{1, 3}, std::vector<int>{2, 3}, std::vector<int>{3, 1}}));
		 
	}
	 

	// practice�����γ̱�
	/*
		�����ѧ�ڱ���ѡ�� numCourses �ſγ̣���Ϊ 0 �� numCourses - 1 ��
		��ѡ��ĳЩ�γ�֮ǰ��ҪһЩ���޿γ̡�
		���޿γ̰����� prerequisites ���������� prerequisites[i] = [ai, bi] ����ʾ���Ҫѧϰ�γ� ai �� ���� ��ѧϰ�γ�  bi ��
		���磬���޿γ̶� [0, 1] ��ʾ����Ҫѧϰ�γ� 0 ������Ҫ����ɿγ� 1 ��
		�����ж��Ƿ����������пγ̵�ѧϰ��������ԣ����� true �����򣬷��� false ��

		ʾ�� 1��
				���룺numCourses = 2, prerequisites = [[1,0]]
				�����true
				���ͣ��ܹ��� 2 �ſγ̡�ѧϰ�γ� 1 ֮ǰ������Ҫ��ɿγ� 0 �����ǿ��ܵ�

		ʾ�� 2��
				���룺numCourses = 2, prerequisites = [[1,0],[0,1]]
				�����false

		
		bool canFinish(int numCourses, vector<vector<int>>& prerequisites) 
	*/
	void test5() 
	{
		/*
			ֻҪ��prerequisites��Ӧ������ͼ�У������ڻ����Ϳ���������пγ̵�ѧϰ�����򲻿��ԣ�
		*/

		auto canFinish = [](const int numCourses, \
			const std::vector<std::vector<int>>& prerequisites)->bool
			{ 
				// 0. �����ڽӱ���ע��prerequisites�е�[a, b]��Ϊ��[b, a]��
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

				// 1. ͳ�����нڵ�����
				std::vector<int> relyCourse(n, 0);
				for (int i = 0; i < edgesCount; ++i) 
				{
					index = prerequisites[i][0];
					relyCourse[index]++;
				}

				// 2. �ҵ���һ�����Ϊ0�Ľڵ㣻 
				std::list<int> base;				// ������Ϊ������γ̵Ŀγ̣���Ϊһ������ͨͼ�ĸ��ڵ㣻
				for (int i = 0; i < n; ++i)
					if (0 == relyCourse[i])
						base.push_back(i);
				if (base.empty())
					return false;						// ���нڵ���ȶ���Ϊ0��˵���Ҳ���������Ϊ������γ̵Ŀγ̣�

				// 3. �ӵ�һ�����Ϊ0�Ľڵ㿪ʼ�����й�����ȱ�����������ע��ͼ���ܲ��ǵ���ͨ�ģ�������
				std::queue<int> qt;
				int startIdx = base.front();
				base.pop_front();
				qt.push(startIdx);
				while (!qt.empty() || !base.empty())
				{ 
					if (qt.empty())
					{
						// w4. �������ѿգ�����ѹ��������ͨ����ĸ��ڵ㣻 
						if (!base.empty())
						{
							startIdx = base.front();
							base.pop_front();
							qt.push(startIdx);
						} 
					}
					else
					{
						// w1. ���׽ڵ���ӣ���Ϊ��ǰ�ڵ㣻
						index = qt.front();
						qt.pop(); 

						// w2. �Ե�ǰ�ڵ�Ĳ��������޸������ڵ����ȣ�����ɾ���ýڵ㣬����Ľڵ����-1��
						for (const auto& toIdx : vvList[index])
							relyCourse[toIdx]--;

						// w3. ��ǰ�ڵ��δ���ʵ�1����ڵ�ѹ����У�
						for (const auto& indexNbr : vvList[index])
							if (0 == relyCourse[indexNbr])					// ֻ����ȼ���0�Ŀγ̲ſ����ޣ�
								qt.push(indexNbr);
					} 
				}

				// 4. �������֮�󣬼���Ƿ��нڵ���Ȳ�Ϊ0��
				int accum = std::accumulate(relyCourse.begin(), relyCourse.end(), 0);
				return (0 == accum);			// ����0��ʾ��ʱ���нڵ���ȶ�Ϊ0��ԭͼ�в����ڻ�������������пγ̵�ѧϰ��
			};

		debugDisp("canFinish(3, { {1, 0}, {1, 2}, {0, 1} }) == ", canFinish(3, { {1, 0}, {1, 2}, {0, 1} }));
		debugDisp("canFinish(2, { {1, 0}, {0, 1} }) == ", canFinish(2, { {1, 0}, {0, 1} }));
		debugDisp("canFinish(5, { {1, 4} ,{2, 4}, {3, 1}, {3, 2} }) == ", canFinish(5, { {1, 4} ,{2, 4}, {3, 1}, {3, 2} }));
		debugDisp("test5 finished.");
	}


	// practice����ͳ������ͼ���޷����ൽ������
	/*
		����һ������ n ����ʾһ�� ����ͼ ���� n ���ڵ㣬���Ϊ 0 �� n - 1 ��
		ͬʱ����һ����ά�������� edges ������ edges[i] = [ai, bi] ��ʾ�ڵ� ai �� bi ֮����һ�� ���� �ߡ�
		���㷵�� �޷����ൽ�� �Ĳ�ͬ �����Ŀ ��


		
		ʾ�� 1�� 
			���룺n = 3, edges = [[0,1],[0,2],[1,2]]
			�����0
			���ͣ����е㶼�ܻ��ൽ���ζ��û�е���޷����ൽ��������Ƿ��� 0 ��
		
		ʾ�� 2�� 
			���룺n = 7, edges = [[0,2],[0,5],[2,4],[1,6],[5,4]]
			�����14
			���ͣ��ܹ��� 14 ����Ի����޷����
			[[0,1],[0,3],[0,6],[1,2],[1,3],[1,4],[1,5],[2,3],[2,6],[3,4],[3,5],[3,6],[4,6],[5,6]]
			�������Ƿ��� 14 ��

		��1�����������������
				��ͨ����������ͨ������������������֡�
				���Ƚ�����edges������ٽӱ�graph
				Ȼ���캯��DFS������Ϊ����������ͬһ����ͨ�����в��һ�δ���ʹ��ĵ㣬�����ط��ʵĵ�����
				�������е㣬�����ǰ�㻹û�з��ʹ�����˵��������һ���µ���ͨ������
						ͨ��DFS�����㵱ǰ��ͨ�����ĵ���count��
						�����ͨ�����е����е��������ͨ�����е����е㶼�޷��໥���
						��������ͨ�����еĵ�Դ𰸵Ĺ�����count * (n - count)��
				ÿ����Իᱻ�������Σ�����������Ҫ����2��
 
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
