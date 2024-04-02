#include <iostream>
#include <vector>
#include <list>
#include <stack>
#include <queue>
#include <map>
#include <unordered_map>
#include <algorithm>

#include "myDSA.h"


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



////////////////////////////////////////////////////////////////////////////////////////////// 数组
namespace ARRAY
{
	// 两数之和
	/*
		给定一个整数数组 nums 和一个整数目标值 target，
			请你在该数组中找出 和为目标值 target  的那 两个 整数，并返回它们的数组下标。
			你可以假设每种输入只会对应一个答案。但是，数组中同一个元素在答案里不能重复出现。
	*/
	std::vector<int> twoSum(const std::vector<int>& nums, const int target)
	{
		/*
			常规思路是使用双重的for循环来遍历输入向量中所有的数对，找出符合要求的那一对；
					时间复杂度为O(n^2)，空间复杂度为O(1)

			借用哈希表的话，可以用空间换时间
					下面的代码展示了时间复杂度为O(n)，空间复杂度为O(n)的方法

		*/
		std::unordered_map<int, int> map;				// 键为nums中的数字，值为其索引；
		for (int i = 0; i < nums.size(); ++i)
		{
			auto iter = map.find(target - nums[i]);
			if (iter != map.end())
				return std::vector<int>{iter->second, i};
			map[nums[i]] = i;
		}
		return std::vector<int>{};
	}


	void test0()
	{
		std::vector<int> retVec = twoSum(std::vector<int>{11, 2, 7, 15}, 9);
		traverseSTL(retVec, disp<int>);

		debugDisp("test0 finished.");
	}

}



////////////////////////////////////////////////////////////////////////////////////////////// 字符串
namespace STRING 
{
	// 回文串判断
	/*
		若在将所有大写字符转换为小写字符、并移除所有非字母数字字符之后，短语正着读和反着读都一样。则可以认为该短语是一个回文串 。
				字母和数字都属于字母数字字符。

		给你一个字符串 s，如果它是 回文串 ，返回 true ；否则，返回 false 。

	示例 ：
		输入: s = "A man, a plan, a canal: Panama"
		输出：true
		解释："amanaplanacanalpanama" 是回文串。
		示例 2：

		输入：s = "race a car"
		输出：false
		解释："raceacar" 不是回文串。
		示例 3：

		输入：s = " "
		输出：true
		解释：在移除非字母数字字符之后，s 是一个空字符串 "" 。
		由于空字符串正着反着读都一样，所以是回文串。
  
	提示：1 <= s.length <= 2 * 10^5
	
	*/
	void test0() 
	{


	}


}



////////////////////////////////////////////////////////////////////////////////////////////// 排序
/*
	时间复杂度是 O(nlog⁡n)的排序算法：
		归并排序
				适用于链表
		堆排序
				
		快速排序
				最差时间复杂度是O(n^2)
  

*/
namespace SORTING 
{
	// 合并两个有序数组（单调递增）
	bool mergeSequence(std::vector<int>& vec1, const std::vector<int>& vec2)
	{
		int index1 = 0;
		int index2 = 0;
		const int count1 = vec1.size();
		const int count2 = vec2.size();
		std::vector<int> vecOut;
		vecOut.reserve(count1 + count2);

		while (index1 < count1 && index2 < count2)
		{
			if (vec1[index1] <= vec2[index2])
			{
				vecOut.push_back(vec1[index1]);
				index1++;
			}
			else
			{
				vecOut.push_back(vec2[index2]);
				index2++;
			}
		}
		if (count1 == index1)
			vecOut.insert(vecOut.end(), vec2.begin() + index2, vec2.end());
		else
			vecOut.insert(vecOut.end(), vec1.begin() + index1, vec1.end());

		vec1.clear();
		vec1 = std::move(vecOut);

		return true;
	}
	 

	bool mergeSort(const std::vector<int>::iterator& begin, const std::vector<int>::iterator& end)
	{
		const size_t elemCount = std::distance(begin, end);

		// 递归终止——需要排序的序列元素数目不大于2时：
		if (elemCount < 0)
			return false;
		if (elemCount < 2)
			return true;
		if (2 == elemCount)
			if (*begin > *(begin + 1))
				std::swap(*begin, *(begin + 1));

		// 递归递推——需要排序的序列元素数目大于2时，将其二分分别排列后，再整合成单调有序的序列；
		if (elemCount > 2)
		{
			std::vector<int> vec1, vec2;
			std::vector<int>::iterator middle = begin + elemCount / 2;
			mergeSort(begin, middle);
			mergeSort(middle, end);
			vec1.insert(vec1.end(), begin, middle);
			vec2.insert(vec2.end(), middle, end);
			mergeSequence(vec1, vec2);
			auto iter = begin;
			for (size_t i = 0; i < elemCount; ++i)
			{
				*iter = vec1[i];
				iter++;
			}
		}
		 
		return true;
	}


	void test0() 
	{
		std::vector<int> vec1{ 1, 2, 3, };
		std::vector<int> vec2{ 2, 5, 6 }; 
		mergeSequence(vec1, vec2); 
		traverseSTL(vec1, disp<int>);
		debugDisp("\n");

		//
		std::vector<int> numVec{54, 12, 45, -1, -99, 8, 9, 0, 12};
		mergeSort(numVec.begin(), numVec.end());
		traverseSTL(numVec, disp<int>);
		 
		debugDisp("test0() finished.");
	}
 
}



////////////////////////////////////////////////////////////////////////////////////////////// 图
namespace GRAPH 
{
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
	 
	void test0()
	{
		debugDisp("result == ", findJudge(3, std::vector<std::vector<int>>{ \
				std::vector<int>{1, 3}, std::vector<int>{2, 3} }));

		debugDisp("test0() finished.");
	}
 
}



////////////////////////////////////////////////////////////////////////////////////////////// 递归
namespace RECURSION
{
	int factorial(const int num) 
	{
		int result = 0;

		// 递归终止1：
		if (num < 0)
			return -std::numeric_limits<int>::max(); 

		// 递归终止2：
		if (1 == num || 0 == num)
			return 1;

		// 递归递推：
		return num * factorial(num - 1); 
	}

	void test0() 
	{
		debugDisp("result == ", factorial(-4));

		debugDisp("test0 finished.");
	}
}



////////////////////////////////////////////////////////////////////////////////////////////// 回溯法
namespace BACKTRACKING 
{
	// 生成括号
	/*
		数字 n 代表生成括号的对数，请你设计一个函数，用于能够生成所有可能的并且 有效的 括号组合。
		vector<string> generateParenthesis(int n) 

		输入：n = 3
		输出：["((()))","(()())","(())()","()(())","()()()"] 

		输入：n = 1
		输出：["()"]
	
	*/
	void test0() {}

	 
	// 组合求和问题(Combination Sum)
	int combinationSum(std::list<int>& combList, const int target ) 
	{

		return 0;
	}

	using namespace std;


	void CombinationSum(vector<int>& candidates, \
		int target, vector<int>& combination, vector<vector<int>>& result, \
		const int startIdx) 
	{
		// 如果 target 为 0，说明找到了一组组合
		if (target == 0)
		{
			result.push_back(combination);
			return;
		}

		// 递归递推——当前组合序列最后一个数字为num，递归

		// 递归终止1——若当前组合序列和大于目标和，则


		// 从 start 开始遍历 candidates 数组
		for (int i = startIdx; i < candidates.size(); i++)
		{
			// 如果当前候选数字大于 target，结束本次循环
			if (candidates[i] > target)
				continue;

			// 避免重复的数字
			if (i > startIdx && candidates[i] == candidates[i - 1])
				continue;

			combination.push_back(candidates[i]);			// 将当前候选数字加入组合 
			CombinationSum(candidates, target - candidates[i], combination, result, i + 1);	// 从当前位置的下一个位置开始寻找下一个组合
			combination.pop_back();				// 回溯，将上一步加入的数字移出组合
		}
	} 


	void test1() 
	{
		// 给定一个数组和一个目标数，从数组中选取若干个数字使它们的和等于目标数，找出所有可能的组合。
		
		// 0.
		std::vector<int> candidates = { 2, 3, 6, 7, 11, 24, 23, 1, 10, -1, -2, -3 };
		std::vector<std::vector<int>> results;
		const int target = 24;

		// 1. 
		vector<int> combination;
		std::sort(candidates.begin(), candidates.end());
		CombinationSum(candidates, target, combination, results, 0); 
		for (const auto& vec : results)
		{
			traverseSTL(vec, disp<int>);
			std::cout << std::endl;
		}

		debugDisp("test1 finished.");
	}


	// 
}


namespace TMP_QUEENS
{
	using namespace std;

	// 检查在 (row, col) 位置放置皇后是否合法
	bool isSafe(vector<vector<int>>& board, int row, int col) {
		// 检查列是否安全
		for (int i = 0; i < row; i++) {
			if (board[i][col] == 1)
				return false;
		}

		// 检查左上到右下对角线是否安全
		for (int i = row, j = col; i >= 0 && j >= 0; i--, j--) {
			if (board[i][j] == 1)
				return false;
		}

		// 检查右上到左下对角线是否安全
		for (int i = row, j = col; i >= 0 && j < board.size(); i--, j++) {
			if (board[i][j] == 1)
				return false;
		}

		return true;
	}

	// 解决八皇后问题
	bool solveNQueens(vector<vector<int>>& board, int row) {
		// 如果所有行都已经放置了皇后，则返回 true
		if (row == board.size())
			return true;

		for (int col = 0; col < board.size(); col++)
		{
			// 检查当前位置是否安全
			if (isSafe(board, row, col))
			{

				// 放置皇后
				board[row][col] = 1;

				// 递归尝试下一行
				if (solveNQueens(board, row + 1))
					return true;

				// ！！！如果不能放置皇后，则回溯
				board[row][col] = 0;
			}
		}

		// 如果在该行的任何位置都不能放置皇后，则返回 false
		return false;
	}

	// 打印棋盘
	void printBoard(vector<vector<int>>& board)
	{
		for (int i = 0; i < board.size(); i++)
		{
			for (int j = 0; j < board.size(); j++)
			{
				cout << board[i][j] << " ";
			}
			cout << endl;
		}
	}


	int testQueens()
	{
		int n = 8; // 棋盘大小
		vector<vector<int>> board(n, vector<int>(n, 0)); // 初始化棋盘

		// 解决八皇后问题
		if (solveNQueens(board, 0))
		{
			cout << "Solution found:\n";
			printBoard(board);
		}
		else
			cout << "No solution exists!\n";


		return 0;
	}

}




namespace TMP_BST
{
	using namespace std;
	using treeNode = TreeNode<int>; 

# if 0
	template<typename T>
	BiTree<T>* insert_bst(T data, BiTree<T>*& bst)
	{
		if (!bst) 
		{ 

			bst = new BiTree<T>;
			bst->data = data;
			bst->right = bst->left = NULL;
		}
		else     //开始找要插入元素的位置
		{
			if (data < bst->data) //递归插入左子树
				bst->left = insert_bst(data, bst->left);

			if (data > bst->data)//递归插入右子树
				bst->right = insert_bst(data, bst->right);
		}

		return bst;
	} 
#endif

	void test0() {}
}


int main(int argc, char** argv)
{
	TREE::test1(); 

	// BACKTRACKING::test1();

	// TMP_BST::test0();


	debugDisp("main finished.");


	return 0;
}
