#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>


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


// 数组
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


// 二叉树
namespace BINARY_TREE 
{
	struct TreeNode 
	{
		int val;
		TreeNode *left;
		TreeNode *right;
		TreeNode() : val(0), left(nullptr), right(nullptr) {}
		TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
		TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
	};
 

	// 二叉树的最大深度：
	/*
		给定一个二叉树 root ，返回其最大深度。
			二叉树的最大深度：从根节点到最远叶子节点的最长路径上的节点数。
	*/
	int maxDepth(TreeNode* root)
	{

	}


	void test0() 
	{

	}

}
  


int main(int argc, char** argv) 
{
	test0();

	debugDisp("main finished.");

	return 0;
}
