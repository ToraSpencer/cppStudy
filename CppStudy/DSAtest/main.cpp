#include <iostream>
#include <vector>
#include <queue>
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


////////////////////////////////////////////////////////////////////////////////////////////// 二叉树
namespace BINARY_TREE
{
	// TreeNode类——二叉树节点类
	template <typename T>
	class TreeNode
	{
	public:
		T val;
		TreeNode* left;
		TreeNode* right;
		TreeNode() : val(0), left(nullptr), right(nullptr) {}
		TreeNode(const T x) : val(x), left(nullptr), right(nullptr) {}
		TreeNode(const T x, TreeNode* left, TreeNode* right) : val(x), left(left), right(right) {}
	};


	// 二叉树的最大深度：
	/*
		给定一个二叉树 root ，返回其最大深度。
			二叉树的最大深度：从根节点到最远叶子节点的最长路径上的节点数。
	*/
	template <typename T>
	int maxDepth(TreeNode<T>* root)
	{
		if (root == NULL)
			return 0;

		int depth = 0;
		std::queue<TreeNode<T>*> que;
		que.push(root);
		while (!que.empty())
		{
			int size = que.size();
			depth++;											  // 记录深度
			for (int i = 0; i < size; i++)
			{
				TreeNode<T>* node = que.front();
				que.pop();
				if (node->left)
					que.push(node->left);
				if (node->right)
					que.push(node->right);
			}
		}
		return depth;
	}


	void test0()
	{
		/* 
							   3
							 /   \
						   9      20
								 /	   \
							  15       7
		*/
		TreeNode<int>* ptrRoot = nullptr;
		TreeNode<int> tn0, tn00, tn01, tn010, tn011;
		tn0.val = 3;
		tn00.val = 9;
		tn01.val = 20;
		tn010.val = 15;
		tn011.val = 7;
		tn0.left = &tn00;
		tn0.right = &tn01;
		tn01.left = &tn010;
		tn01.right = &tn011;
		ptrRoot = &tn0;

		debugDisp("maxDepth(ptrRoot) == ", maxDepth(ptrRoot)); 

		debugDisp("test0 finished.");
	}

	
	// 二叉树序列化（转换为1维数组）：
	template <typename T>
	void BT2Array(TreeNode<T>* ptrNode, T* arrayHead, int i, int j, \
		const std::pair<int, int>& size = std::make_pair(0, 0))
	{
		// T为二叉树的根节点，arrayHead是数组的起始地址，ij表示当前节点在数组中的位置
		int ti = 0;
		int tj = 0;						// 如果节点有孩子,其孩子的j坐标为 j±(height-i+1)/2
		int width = size.first;
		int height = size.second;

		if (nullptr != ptrNode)					//如果该位置有节点
		{
			*(arrayHead + i * width + j) = ptrNode->val;			// 向数组该点填入字符
			if (nullptr != ptrNode->left)			// 有左右孩子给对应的连接线,左右孩子的值在下一层递归赋
			{
				//将该点与其左孩子之间的连线全部填上'/'
				for (ti = i + 1, tj = j - 1; tj > j - (height - i + 1) / 2; tj--)
				{
					*(arrayHead + ti * width + tj) = -1;
					ti++;
				}
			}
			if (nullptr != ptrNode->right)
			{
				for (ti = i + 1, tj = j + 1; tj < j + (height - i + 1) / 2; tj++)
				{
					*(arrayHead + ti * width + tj) = 1;
					ti++;
				}
			}

			// 经过循环,ti恰好指到其孩子所在的层
			BT2Array(ptrNode->left, arrayHead, ti, j - (height - i + 1) / 2, std::make_pair(width, height));
			BT2Array(ptrNode->right, arrayHead, ti, j + (height - i + 1) / 2, std::make_pair(width, height));
		}
	}


	// 控制台上打印二叉树
	template <typename T>
	void printBT(TreeNode<T>* ptrNode)
	{ 
		// 1. 动态数组申请空间
		int n = maxDepth(ptrNode);				 // 深度 
		int width = (2 << n) - 3;						 // 2^(n+1)-3；左移1位就相当于乘以2的1次方
		int height = (2 << (n - 1)) - 1;				// 2^n-1 
		T* a = new T[width *height];						
		for (int i = 0; i < height; i++)				// 空间初始化为0
			for (int j = 0; j < width; j++)
				*(a + (i * width) + j) = 0;

		// 2. 二叉树序列化
		BT2Array(ptrNode, a, 0, (width - 1) / 2, std::make_pair(width, height));

		// 3. 打印
		for (int i = 0; i < height; i++)
		{
			for (int j = 0; j < width; j++)
			{
				if (*(a + (i * width) + j) == -1)
					printf("/");
				else if (*(a + (i * width) + j) == 1)
					printf("\\");
				else if (*(a + (i * width) + j) == 0)
					printf(" ");
				else
					std::cout << *(a + (i * width) + j); 
			}
			printf("\n");
		}

		// 释放内存
		delete[] a;		
	}


	void test1() 
	{ 
		TreeNode<int>* ptrRoot = nullptr;
		TreeNode<int> tn0, tn00, tn01, tn010, tn011;
		tn0.val = 3;
		tn00.val = 9;
		tn01.val = 20;
		tn010.val = 15;
		tn011.val = 7;
		tn0.left = &tn00;
		tn0.right = &tn01;
		tn01.left = &tn010;
		tn01.right = &tn011;
		ptrRoot = &tn0; 
		printBT(ptrRoot);

		TreeNode<char>* ptrRoot2 = new TreeNode<char>{'B'};
		ptrRoot2->left = new TreeNode<char>{ 'I' };
		ptrRoot2->right = new TreeNode<char>{ 'N' };
		ptrRoot2->left->left = new TreeNode<char>{ 'A' };
		ptrRoot2->left->right = new TreeNode<char>{ 'R' };
		ptrRoot2->right->left = new TreeNode<char>{ 'Y' };
		printBT(ptrRoot2);

		debugDisp("test1 finished.");

	}

}



int main(int argc, char** argv)
{
	BINARY_TREE::test1();

	debugDisp("main finished.");

	return 0;
}
