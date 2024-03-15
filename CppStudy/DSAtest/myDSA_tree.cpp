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

		// 1. 先序遍历：
		traverseBT(ptrRoot, dispTreeNode<int>, TRAVERSE_BT_TYPE::PreOrder);
		debugDisp("\n");
		traverseBT(ptrRoot, dispTreeNode<int>, TRAVERSE_BT_TYPE::InOrder);
		debugDisp("\n");
		traverseBT(ptrRoot, dispTreeNode<int>, TRAVERSE_BT_TYPE::PostOrder);
		debugDisp("\n");
		traverseBT(ptrRoot, dispTreeNode<int>, TRAVERSE_BT_TYPE::LevelOrder); 
		debugDisp("\n");

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

		std::vector<int> valVec;
		printBT(ptrRoot);
		serializeBT(valVec, ptrRoot);
		traverseSTL(valVec, dispCorrected<int>);

		debugDisp("test4 finished.");
	}
}
