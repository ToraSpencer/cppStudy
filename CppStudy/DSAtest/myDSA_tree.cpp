#include "myDSA_tree.h"


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


namespace TREE
{
	// 二叉树的最大深度：
	/*
		给定一个二叉树 root ，返回其最大深度。
			二叉树的最大深度：从根节点到最远叶子节点的最长路径上的节点数。
	*/
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

		debugDisp("ptrRoot->maxDepth() == ", ptrRoot->maxDepth());
		debugDisp("ptrRoot->right->maxDepth() == ", ptrRoot->right->maxDepth());

		debugDisp("test0 finished.");
	}


	// 各种遍历方法
	void test1() 
	{
		constexpr int placeholder = std::numeric_limits<int>::max();
		TreeNode<int>* ptrRoot = deserializeBT_levelOrder(std::vector<int>{\
			8, 3, 10, 2, 6, placeholder, 14, placeholder, placeholder, \
			4, 7, 13, placeholder});
		printBT(ptrRoot);
		 
		// 1. 各种遍历方法：
		traverseBT(ptrRoot, dispTreeNode<int>, TRAVERSE_BT_TYPE::LevelOrder);  
		debugDisp("\n");
		traverseBT(ptrRoot, dispTreeNode<int>, TRAVERSE_BT_TYPE::PreOrder); 
		debugDisp("\n");
		traverseBT(ptrRoot, dispTreeNode<int>, TRAVERSE_BT_TYPE::InOrder); 
		debugDisp("\n");
		traverseBT(ptrRoot, dispTreeNode<int>, TRAVERSE_BT_TYPE::PostOrder); 
		debugDisp("\n");

		// 2. 使用先序序列、中序序列来重建BT:
		TreeNode<int>* ptrRoot1 = buildBT(std::vector<int>{8, 3, 2, 6, 4, 7, 10, 14, 13},\
			std::vector<int>{2, 3, 4, 6, 7, 8, 10, 13, 14});
		printBT(ptrRoot1);

		destroy(ptrRoot);
		destroy(ptrRoot1);
		debugDisp("test1 finished.");
	}


	// print BT
	void test2()
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

		TreeNode<char>* ptrRoot2 = new TreeNode<char>{ 'B' };
		ptrRoot2->left = new TreeNode<char>{ 'I' };
		ptrRoot2->right = new TreeNode<char>{ 'N' };
		ptrRoot2->left->left = new TreeNode<char>{ 'A' };
		ptrRoot2->left->right = new TreeNode<char>{ 'R' };
		ptrRoot2->right->left = new TreeNode<char>{ 'Y' };
		printBT(ptrRoot2);

		debugDisp("test1 finished.");

	}


	// 翻转二叉树
	/*
	给你一棵二叉树的根节点 root ，翻转这棵二叉树，并返回其根节点。 

	示例 1：
		输入：root = [4,2,7,1,3,6,9]
		输出：[4,7,2,9,6,3,1]
	示例 2：
	输入：root = [2,1,3]
	输出：[2,3,1]
	示例 3：
	输入：root = []
	输出：[]
	提示：
	树中节点数目范围在 [0, 100] 内
	-100 <= Node.val <= 100	
	*/
	void test3() 
	{
		TreeNode<int>* ptrRoot = nullptr;
		TreeNode<int> tn0, tn00, tn01, tn010, tn011;
		{
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
		}
		printBT(ptrRoot);

		reverseBT(ptrRoot);
		printBT(ptrRoot);


		debugDisp("test3 finished.");
	}


	// BT的序列化、反序列化。 
	void test4()
	{
		// 0. prepare data:
		constexpr int placeholder = std::numeric_limits<int>::max();
		TreeNode<int>* ptrRoot = nullptr;
		TreeNode<int> tn0, tn00, tn01, tn010, tn011, tn0101, tn0111;
		{
			tn0.val = 3;
			tn00.val = 9;
			tn01.val = 20;
			tn010.val = 15;
			tn011.val = 7;
			tn0101.val = 88;
			tn0111.val = -5;

			tn0.left = &tn00;
			tn0.right = &tn01;
			tn01.left = &tn010;
			tn01.right = &tn011;
			tn010.right = &tn0101;
			tn011.right = &tn0111;
			ptrRoot = &tn0;
		}

		std::vector<int> valVec;
		printBT(ptrRoot); 

		// 1. 基于先序遍历
		serializeBT_preOrder(valVec, ptrRoot);
		traverseSTL(valVec, dispCorrected<int>);
		TreeNode<int>* ptrRoot1 = deserializeBT_preOrder(valVec);
		printBT(ptrRoot1);
		destroy(ptrRoot1);
		
		// 2. 基于层序遍历：
		valVec.clear();
		serializeBT_levelOrder(valVec, ptrRoot);
		traverseSTL(valVec, dispCorrected<int>);
		TreeNode<int>* ptrRoot2 = deserializeBT_levelOrder(valVec);
		printBT(ptrRoot2);
		destroy(ptrRoot2);

		// 3. 
		TreeNode<int>* ptrRoot3 = deserializeBT_levelOrder(std::vector<int>{ 9, 2, 3, placeholder, placeholder, 4, 5});
		printBT(ptrRoot3);
		destroy(ptrRoot3);

		debugDisp("test4 finished.");
	}


	// BT的所有路径：
	/*
		给你一个二叉树的根节点 root ，按 任意顺序 ，返回所有从根节点到叶子节点的路径。 
		 vector<string> binaryTreePaths(TreeNode* root) {}
		输入：root = [1,2,3,null,5]
		输出：["1->2->5","1->3"]

		输入：root = [1]
		输出：["1"]
	
	*/
	void test5() 
	{


	}


	// 不同的BST
	/*
		给你一个整数 n ，请你生成并返回所有由 n 个节点组成且节点值从 1 到 n 互不相同的不同 二叉搜索树 。
				可以按 任意顺序 返回答案。

		 vector<TreeNode*> generateTrees(int n) {}

		输入：n = 3
		输出：[[1,null,2,null,3],[1,null,3,2],[2,1,3],[3,1,null,null,2],[3,2,null,1]] 

		输入：n = 1
		输出：[[1]]	
	*/
	void test6() 
	{
		// 0. 使用层序序列化的方式构建一个BST:
		constexpr int placeholder = std::numeric_limits<int>::max();
		TreeNode<int>* pn = nullptr;
		TreeNode<int>* ptrRoot1 = deserializeBT_levelOrder(std::vector<int>{\
			8, 3, 10, 2, 6, placeholder, 14, placeholder, placeholder, \
			4, 7, 13, placeholder});
		TreeNode<int>* ptrRoot2 = deserializeBT_levelOrder(std::vector<int>{1, 2, 3, 4, 5, 6, 7});
		printBT(ptrRoot1);
		printBT(ptrRoot2);

		// 1. 如果一个BT是BST，则其中序遍历得到的序列是单调递增序列；
		traverseBT(ptrRoot1, dispTreeNode<int>, TRAVERSE_BT_TYPE::InOrder); 
		traverseBT(ptrRoot2, dispTreeNode<int>, TRAVERSE_BT_TYPE::InOrder); 
		debugDisp("isBST(ptrRoot1) == ", isBST(ptrRoot1));
		debugDisp("isBST(ptrRoot2) == ", isBST(ptrRoot2));
		destroy(ptrRoot1);
		destroy(ptrRoot2);

		// 2. 
		ptrRoot1 = buildBST(8, std::vector<int>{3, 10, 2, 6, 14, 4, 7, 13});
		ptrRoot2 = buildBST(8, std::vector<int>{4, 13, 7, 3, 2, 10, 6, 14});
		printBT(ptrRoot1);
		printBT(ptrRoot2);
		debugDisp("isBST(ptrRoot1) == ", isBST(ptrRoot1));
		debugDisp("isBST(ptrRoot2) == ", isBST(ptrRoot2));
		pn = searchBST(ptrRoot1, 7);
		debugDisp("pn->val == ", pn->val);
		pn = searchBST(ptrRoot1, 99);
		debugDisp("(nullptr == pn) == ", nullptr == pn);

		destroy(ptrRoot1);
		destroy(ptrRoot2);
		debugDisp("test6 finished.");
	}


	// 平衡BT
	void test7() 
	{
		constexpr int placeholder = std::numeric_limits<int>::max();
		TreeNode<int>* ptrRoot1 = deserializeBT_levelOrder(std::vector<int>{\
			8, 3, 10, 2, 6, placeholder, 14, placeholder, placeholder, \
			4, 7, 13, placeholder});
		TreeNode<int>* ptrRoot2 = deserializeBT_levelOrder(std::vector<int>{\
			1,2,3,4,5,6,7,8,9});
		printBT(ptrRoot1);
		printBT(ptrRoot2);

		debugDisp("isBalanced(ptrRoot1) == ", isBalanced(ptrRoot1));
		debugDisp("isBalanced(ptrRoot2) == ", isBalanced(ptrRoot2));

		destroy(ptrRoot1);
		destroy(ptrRoot2);
		debugDisp("test7 finished.");
	}
}
