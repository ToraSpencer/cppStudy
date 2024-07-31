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
			std::cout << "PH, ";
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
 
#if 1
void strBT2Array(TreeNode<std::string>* ptrNode, std::string* arrayHead, int i, int k, \
	const std::pair<int, int>& size = std::make_pair(0, 0))
{  
	const std::string PH = std::string{};				// placeholder, 占位符 
	const std::string FS = "/";						// forward slash, 前斜杠/ 
	const std::string BS = "\\";						// backward slash, 后斜杠\ 

	// arrayHead是数组的起始地址，ij表示当前节点在数组中的位置
	int ti = 0;
	int tk = 0;						// 如果节点有孩子,其孩子的k坐标为 k±(height-i+1)/2
	int width = size.first;
	int height = size.second;

	if (nullptr != ptrNode)					// 如果该位置有节点
	{
		*(arrayHead + i * width + k) = ptrNode->val;			// 向数组该位置填入元素；
		if (nullptr != ptrNode->left)			// 有左右孩子给对应的连接线,左右孩子的值在下一层递归赋
		{
			// 将该点与其左孩子之间的连线全部填上'/'
			for (ti = i + 1, tk = k - 1; tk > k - (height - i + 1) / 2; tk--)
			{
				*(arrayHead + ti * width + tk) = FS;
				ti++;
			}
		}
		if (nullptr != ptrNode->right)
		{
			for (ti = i + 1, tk = k + 1; tk < k + (height - i + 1) / 2; tk++)
			{
				*(arrayHead + ti * width + tk) = BS;
				ti++;
			}
		}

		// 经过循环,ti恰好指到其孩子所在的层
		strBT2Array(ptrNode->left, arrayHead, ti, k - (height - i + 1) / 2, std::make_pair(width, height));
		strBT2Array(ptrNode->right, arrayHead, ti, k + (height - i + 1) / 2, std::make_pair(width, height));
	}
}


// 控制台上打印节点元素为字符串的BT
void printStrBT(TreeNode<std::string>* ptrNode)
{
	const std::string PH = std::string{};				// placeholder, 占位符 
	const std::string FS = "/";						// forward slash, 前斜杠/ 
	const std::string BS = "\\";						// backward slash, 后斜杠\ 

	// 1. 动态数组申请空间
	int n = ptrNode->maxDepth();				 // 深度 
	int width = (2 << n) - 3;						 // a << b表示把a的二进制位向左移动b位，低位用0补上。等价于做运算a *= std::pow(2, b);
	int height = (2 << (n - 1)) - 1;				// 2^n-1 
	std::vector<std::string> dataArr(width * height);
	std::string* arr = &dataArr[0]; 
	for (int i = 0; i < height; i++)				// 空间初始化为占位符
		for (int j = 0; j < width; j++)
			*(arr + (i * width) + j) = PH;

	// 2. 序列化
	strBT2Array(ptrNode, arr, 0, (width - 1) / 2, std::make_pair(width, height));

	// 3. 打印
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			if (*(arr + (i * width) + j) == FS)
				printf("/");
			else if (*(arr + (i * width) + j) == BS)
				printf("\\");
			else if (*(arr + (i * width) + j) == PH)
				printf(" ");
			else
				std::cout << *(arr + (i * width) + j);
		}
		printf("\n");
	}
	std::cout << std::endl; 
}

#endif


namespace TREE
{
	// BT的最大深度：
	void test0()
	{
		/*
			给定一个BT root ，返回其最大深度。
					BT的最大深度：从根节点到最远叶子节点的最长路径上的节点数。

			这里使用层序遍历的思路实现最大深度的计算：
		*/
		constexpr int PH = std::numeric_limits<int>::max();
		TreeNode<int>* ptrRoot = nullptr;
		TreeNode<int>* pn = nullptr;
		ptrRoot = deserializeBT_levelOrder(std::vector<int>{5, 0, 8, -1, 3, 6, 9, PH, PH, 1, 4});
		printBT(ptrRoot);

		// 1. maxDepth()最大深度
		debugDisp("ptrRoot->maxDepth() == ", ptrRoot->maxDepth());
		debugDisp("ptrRoot->right->maxDepth() == ", ptrRoot->right->maxDepth());

		// 2. 
		debugDisp("isBST(ptrRoot) == ", isBST(ptrRoot));
		pn = searchBST(ptrRoot, 4);
		pn->right = new TreeNode<int>(99);
		printBT(ptrRoot);
		debugDisp("ptrRoot->maxDepth() == ", ptrRoot->maxDepth());
		debugDisp("isBST(ptrRoot) == ", isBST(ptrRoot));

		debugDisp("test0 finished.");
	}


	// 各种遍历方法
	void test1()
	{
		constexpr int PH = std::numeric_limits<int>::max();
		TreeNode<int>* ptrRoot = deserializeBT_levelOrder(std::vector<int>{\
			8, 3, 10, 2, 6, PH, 14, PH, PH, \
			4, 7, 13, PH});
		printBT(ptrRoot);

		// 1. 各种遍历方法：
		debugDisp("递归遍历方法：层序、先序、中序、后序：");
		traverseBT(ptrRoot, dispTreeNode<int>, TRAVERSE_BT_TYPE::LevelOrder, true);
		debugDisp("\n");
		traverseBT(ptrRoot, dispTreeNode<int>, TRAVERSE_BT_TYPE::PreOrder, true);
		debugDisp("\n");
		traverseBT(ptrRoot, dispTreeNode<int>, TRAVERSE_BT_TYPE::InOrder, true);
		debugDisp("\n");
		traverseBT(ptrRoot, dispTreeNode<int>, TRAVERSE_BT_TYPE::PostOrder, true);
		debugDisp("\n");

		debugDisp("非递归遍历方法：层序、先序、中序、后序：");
		traverseBT_noRecur(ptrRoot, dispTreeNode<int>, TRAVERSE_BT_TYPE::LevelOrder, true);
		debugDisp("\n");
		traverseBT_noRecur(ptrRoot, dispTreeNode<int>, TRAVERSE_BT_TYPE::PreOrder, true);
		debugDisp("\n");
		traverseBT_noRecur(ptrRoot, dispTreeNode<int>, TRAVERSE_BT_TYPE::InOrder, true);
		debugDisp("\n");
		traverseBT_noRecur(ptrRoot, dispTreeNode<int>, TRAVERSE_BT_TYPE::PostOrder, true);
		debugDisp("\n");

		// 2. 使用先序序列、中序序列来重建BT:
		TreeNode<int>* ptrRoot1 = buildBT(std::vector<int>{8, 3, 2, 6, 4, 7, 10, 14, 13}, \
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


	// 翻转BT
	/*
	给你一棵BT的根节点 root ，翻转这棵BT，并返回其根节点。

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
		constexpr int PH = std::numeric_limits<int>::max();
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
		TreeNode<int>* ptrRoot3 = deserializeBT_levelOrder(std::vector<int>{ 9, 2, 3, PH, PH, 4, 5});
		printBT(ptrRoot3);
		destroy(ptrRoot3);

		debugDisp("test4 finished.");
	}


	// BT的所有路径：
	/*
		给你一个BT的根节点 root ，按 任意顺序 ，返回所有从根节点到叶子节点的路径。
		 vector<string> binaryTreePaths(TreeNode* root) {}
		输入：root = [1,2,3,null,5]
		输出：["1->2->5","1->3"]

		输入：root = [1]
		输出：["1"]

		class Solution {
			public:
				void construct_paths(TreeNode* root, string path, vector<string>& paths)
				{
					if (root != nullptr)
					{
						path += to_string(root->val);
						if (root->left == nullptr && root->right == nullptr)
						{  // 当前节点是叶子节点
							paths.push_back(path);                              // 把路径加入到答案中
						} else
						{
							path += "->";  // 当前节点不是叶子节点，继续递归遍历
							construct_paths(root->left, path, paths);
							construct_paths(root->right, path, paths);
						}
					}
				}

				vector<string> binaryTreePaths(TreeNode* root) {
					vector<string> paths;
					construct_paths(root, "", paths);
					return paths;
				}
			};
	*/


	void getAllPaths(std::vector<std::string>& paths, TreeNode<int>* pn, const char* recordStr = "")
	{
		// 规模缩减——当前BT的所有路径等于（根节点+左子树的所有路径）和（根节点+右子树的所有路径）
		if (nullptr == pn)
			return;

		// 1. 已积累的路径末尾加入当前节点值
		std::string currentPath{ recordStr };
		currentPath += std::to_string(pn->val);

		// 2. 
		if (nullptr == pn->left && nullptr == pn->right)
			paths.push_back(currentPath);				// a. 递归终止——当前是叶子节点，当前路径累计完毕，压入paths中；
		else
		{
			// b. 递归递推——
			currentPath += "->";
			getAllPaths(paths, pn->left, currentPath.c_str());
			getAllPaths(paths, pn->right, currentPath.c_str());
		}
	}


	void test5()
	{
		constexpr int PH = std::numeric_limits<int>::max();
		TreeNode<int>* pRoot = deserializeBT_levelOrder(std::vector<int>{\
			8, 3, 10, 2, 6, PH, 14, PH, PH, 4, 7, 13, PH});
		printBT(pRoot);

		std::vector<std::string> paths;
		getAllPaths(paths, pRoot);

		for (const auto& str : paths)
			debugDisp(str);

		debugDisp("test5 finished.");
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
		constexpr int PH = std::numeric_limits<int>::max();
		TreeNode<int>* pn = nullptr;
		TreeNode<int>* ptrRoot1 = deserializeBT_levelOrder(std::vector<int>{\
			8, 3, 10, 2, 6, PH, 14, PH, PH, \
			4, 7, 13, PH});
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
		ptrRoot2 = buildBST(8, std::vector<int>{5, 0, -1, 3, 6, 9, 1, 4});
		printBT(ptrRoot1);
		printBT(ptrRoot2);
		debugDisp("isBST(ptrRoot1) == ", isBST(ptrRoot1));
		debugDisp("isBST(ptrRoot2) == ", isBST(ptrRoot2));

		// 3. 搜索BST
		pn = searchBST(ptrRoot1, 7);
		debugDisp("pn->val == ", pn->val);
		pn = searchBST(ptrRoot1, 99);
		debugDisp("(nullptr == pn) == ", nullptr == pn);

		destroy(ptrRoot1);
		destroy(ptrRoot2);
		debugDisp("test6 finished.");
	}


	// BST的应用：
	void test66()
	{
		TreeNode<int>* ptrRoot1 = nullptr;
		TreeNode<int>* ptrRoot2 = nullptr;
		TreeNode<int>* ptrRoot3 = nullptr;
		TreeNode<int>* ptrRoot4 = nullptr;

		TreeNode<int>* pn = nullptr;

		// 1. BST比一般的BT搜索元素速度更快，本质上是二分查找
		ptrRoot1 = buildBST(8, std::vector<int>{3, 10, 2, 6, 14, 4, 7, 13});
		ptrRoot2 = buildBST(8, std::vector<int>{5, 0, -1, 3, 6, 9, 1, 4});
		printBT(ptrRoot1);
		debugDisp("isBST(ptrRoot1) == ", isBST(ptrRoot1));

		pn = searchBST(ptrRoot1, 14);
		if (nullptr != pn)
			debugDisp("pn->val == ", pn->val);
		pn = searchBST(ptrRoot1, 15);
		if (nullptr != pn)
			debugDisp("pn->val == ", pn->val);

		// 2. 集合操作：


		debugDisp("test66 finished.");
	}


	// 平衡BST

	TreeNode<int>* build(int l, int r, const std::vector<int>& inorderSeq)
	{
		int midIdx = (l + r) / 2;
		TreeNode<int>* pn = new TreeNode<int>(inorderSeq[midIdx]);
		if (l <= midIdx - 1)
			pn->left = build(l, midIdx - 1, inorderSeq);
		if (midIdx + 1 <= r)
			pn->right = build(midIdx + 1, r, inorderSeq);

		return pn;
	}

	TreeNode<int>* balanceBST(TreeNode<int>* root)
	{
		std::vector<int> inorderSeq;
		inorderSeq.clear();
		traverseBT(root, [&](TreeNode<int>* pn)
			{
				inorderSeq.push_back(pn->val);
			}, TRAVERSE_BT_TYPE::InOrder, true);

		return build(0, inorderSeq.size() - 1, inorderSeq);
	}


	void test7()
	{
		constexpr int PH = std::numeric_limits<int>::max();
		TreeNode<int>* ptrRoot1 = nullptr;
		TreeNode<int>* ptrRoot2 = nullptr;
		TreeNode<int>* ptrRoot3 = nullptr;
		TreeNode<int>* ptrRoot4 = nullptr;

		// 1. 判断BT是否是平衡的
		ptrRoot1 = deserializeBT_levelOrder(std::vector<int>{\
			8, 3, 10, 2, 6, PH, 14, PH, PH, \
			4, 7, 13, PH});
		ptrRoot2 = deserializeBT_levelOrder(std::vector<int>{\
			1, 2, 3, 4, 5, 6, 7, 8, 9});
		printBT(ptrRoot1);
		printBT(ptrRoot2);

		debugDisp("isBalanced(ptrRoot1) == ", isBalanced(ptrRoot1));
		debugDisp("isBalanced(ptrRoot2) == ", isBalanced(ptrRoot2));
		destroy(ptrRoot1);
		destroy(ptrRoot2);

		// 2. 将一个BST平衡化：
		ptrRoot1 = deserializeBT_levelOrder(std::vector<int>{\
			1, PH, 2, PH, 3, PH, 4, PH, PH });
		ptrRoot2 = buildBST(1, std::vector<int>{2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12});
		printBT(ptrRoot1);
		debugDisp("isBST(ptrRoot1) == ", isBST(ptrRoot1));
		debugDisp("isBST(ptrRoot2) == ", isBST(ptrRoot2));

		ptrRoot3 = balanceBST(ptrRoot1);
		ptrRoot4 = balanceBST(ptrRoot2);
		printBT(ptrRoot3);
		printBT(ptrRoot4);

		debugDisp("test7 finished.");
	}


	// JZOF18: 树的子结构
	/*
		输入两棵BTA和B，判断B是不是A的子结构。BT结点的定义如下：
			struct BinaryTreeNode
			{
				int                    m_nValue;
				BinaryTreeNode＊       m_pLeft;
				BinaryTreeNode＊       m_pRight;
			};

	*/
	void test8()
	{
		/*
				bool DoesTree1HaveTree2（BinaryTreeNode＊ pRoot1, BinaryTreeNode＊
	pRoot2）
	{
		if（pRoot2 == NULL）
			return true;

		if（pRoot1 == NULL）
			return false;

		if（pRoot1->m_nValue != pRoot2->m_nValue）
			return false;


		return DoesTree1HaveTree2（pRoot1->m_pLeft, pRoot2->m_pLeft） &&
			DoesTree1HaveTree2（pRoot1->m_pRight, pRoot2->m_pRight）;
	}
		*/
	}


	// JZOF24: BST的后序遍历序列
	/*
		输入一个整数数组，判断该数组是不是某二叉搜索树的后序遍历的结果。
		如果是则返回 true，否则返回 false。假设输入的数组的任意两个数字都互不相同。
		输入一个整数数组，判断该数组是不是某二叉搜索树的后序遍历的结果。
		如果是则返回 true，否则返回 false。假设输入的数组的任意两个数字都互不相同。
	*/
	void test9()
	{
		/*
			void FindPath（BinaryTreeNode＊ pRoot, int expectedSum）
	{
		if（pRoot == NULL）
			return;

		std::vector<int> path;
		int currentSum = 0;
		FindPath（pRoot, expectedSum, path, currentSum）;
	}

	void FindPath
	（
		BinaryTreeNode＊   pRoot,
		int                expectedSum,
		std::vector<int>& path,
		int&               currentSum
	）
	{
		currentSum += pRoot->m_nValue;
		path.push_back（pRoot->m_nValue）;

		// 如果是叶结点，并且路径上结点的和等于输入的值
		// 打印出这条路径
		bool isLeaf = pRoot->m_pLeft == NULL && pRoot->m_pRight == NULL;
		if（currentSum == expectedSum && isLeaf）
		{
			printf（"A path is found: "）;
			std::vector<int>::iterator iter = path.begin（）;
			for（; iter != path.end（）; ++ iter）
				printf（"%d\t", ＊iter）;

			printf（"\n"）;
		}

		// 如果不是叶结点，则遍历它的子结点
		if（pRoot->m_pLeft != NULL）
			FindPath（pRoot->m_pLeft, expectedSum, path, currentSum）;
		if（pRoot->m_pRight != NULL）
			FindPath（pRoot->m_pRight, expectedSum, path, currentSum）;

		// 在返回到父结点之前，在路径上删除当前结点，
		// 并在currentSum中减去当前结点的值
		currentSum -= pRoot->m_nValue;
		path.pop_back（）;
	}

		*/
	}


	// JZOF27: BST与双向链表
	/*
		输入一棵二叉搜索树，将该二叉搜索树转换成一个排序的双向链表。
		要求不能创建任何新的结点，只能调整树中结点指针的指向。
		比如输入图4.12中左边的二叉搜索树，则输出转换之后的排序双向链表。
			struct BinaryTreeNode
			{
				int                    m_nValue;
				BinaryTreeNode＊       m_pLeft;
				BinaryTreeNode＊       m_pRight;
			};
	*/
	void test10()
	{
		/*
					BinaryTreeNode＊ Convert（BinaryTreeNode＊ pRootOfTree）
	{
		BinaryTreeNode ＊pLastNodeInList = NULL;
		ConvertNode（pRootOfTree, &pLastNodeInList）;

		// pLastNodeInList指向双向链表的尾结点，
		// 我们需要返回头结点
		BinaryTreeNode ＊pHeadOfList = pLastNodeInList;
		while（pHeadOfList != NULL && pHeadOfList->m_pLeft != NULL）
			pHeadOfList = pHeadOfList->m_pLeft;

		return pHeadOfList;
	}

	void ConvertNode（BinaryTreeNode＊ pNode, BinaryTreeNode＊＊
	pLastNodeInList）
	{
		if（pNode == NULL）
			return;

		BinaryTreeNode ＊pCurrent = pNode;

		if （pCurrent->m_pLeft != NULL）
			ConvertNode（pCurrent->m_pLeft, pLastNodeInList）;

		pCurrent->m_pLeft = ＊pLastNodeInList;
		if（＊pLastNodeInList != NULL）
			（＊pLastNodeInList）->m_pRight = pCurrent;

		＊pLastNodeInList = pCurrent;

		if （pCurrent->m_pRight != NULL）
			ConvertNode（pCurrent->m_pRight, pLastNodeInList）;
	}

		*/
	}


	// JZOF39: 题目二：判断平衡BT 
	/*
		输入一棵BT的根结点，判断该树是不是平衡BT。
		如果某BT中任意结点的左右子树的深度相差不超过1，那么它就是一棵平衡BT。
			struct BinaryTreeNode
			{
				int                    m_nValue;
				BinaryTreeNode＊       m_pLeft;
				BinaryTreeNode＊       m_pRight;
			};
	*/
	void test11()
	{
		/*
				bool IsBalanced（BinaryTreeNode＊ pRoot, int＊ pDepth）
			{
				if（pRoot == NULL）
				{
					＊pDepth = 0;
					return true;
				}

				int left, right;
				if（IsBalanced（pRoot->m_pLeft, &left）
					&& IsBalanced（pRoot->m_pRight, &right））
				{
					int diff = left - right;
					if（diff <= 1 && diff >= -1）
					{
						＊pDepth = 1 + （left > right ? left : right）;
						return true;
					}
				}

				return false;
			}

		bool IsBalanced（BinaryTreeNode＊ pRoot）
		{
			int depth = 0;
			return IsBalanced（pRoot, &depth）;
		}

		*/

	}


	// JZOF50: 树中两个结点的最低公共祖先
	/*
		输入两个树结点，求它们的最低公共祖先。
	*/
	void test12()
	{
		/*
				bool GetNodePath（TreeNode＊ pRoot, TreeNode＊ pNode, list<TreeNode＊>&
	path）
	{
		if（pRoot == pNode）
			return true;

		bool found = false;

		vector<TreeNode＊>::iterator i = pRoot->m_vChildren.begin（）;
		while（!found && i < pRoot->m_vChildren.end（））
		{
			found = GetNodePath（＊i, pNode, path）;
			++i;
		}

		if（!found）
			path.pop_back（）;
		return found;
	}

	TreeNode＊ GetLastCommonNode
	（
		const list<TreeNode＊>& path1,
		const list<TreeNode＊>& path2
	）
	{
		list<TreeNode＊>::const_iterator iterator1 = path1.begin（）;
		list<TreeNode＊>::const_iterator iterator2 = path2.begin（）;

		TreeNode＊ pLast = NULL;

		while（iterator1 != path1.end（） && iterator2 != path2.end（））
		{
			if（＊iterator1 == ＊iterator2）
				pLast = ＊iterator1;

			iterator1++;
			iterator2++;
		}

		return pLast;
	}

	TreeNode＊ GetLastCommonParent（TreeNode＊ pRoot, TreeNode＊ pNode1,
	TreeNode＊ pNode2）
	{
		if（pRoot == NULL || pNode1 == NULL || pNode2 == NULL）
			return NULL;

		list<TreeNode＊> path1;
		GetNodePath（pRoot, pNode1, path1）;

		list<TreeNode＊> path2;
		GetNodePath（pRoot, pNode2, path2）;

		return GetLastCommonNode（path1, path2）;
	}

		*/
	}

	
	// 测试OSGB文件中的树状存储结构：
	void test13()
	{ 
		TreeNode<std::string>* root = new TreeNode<std::string>("G");
		root->left = new TreeNode<std::string>("M1");
		root->right = new TreeNode<std::string>("G1");
		root->left->left = new TreeNode<std::string>("G2");
		root->left->right = new TreeNode<std::string>("g1");
		root->left->left->left = new TreeNode<std::string>("g2");
		root->right->left = new TreeNode<std::string>("M2");
		root->right->left->left = new TreeNode<std::string>("g3");
		root->right->left->right = new TreeNode<std::string>("g4");

		printStrBT(root);
		debugDisp("\n\n");
		traverseBT(root, dispTreeNode<std::string>, TRAVERSE_BT_TYPE::PreOrder);

		//
		std::vector<std::string> elemVec;
		traverseBT(root, [&elemVec](const TreeNode<std::string>* ptrNode)
			{
				elemVec.push_back(ptrNode->val);
			}, TRAVERSE_BT_TYPE::PreOrder);
		
		// 
		TreeNode<std::string>* rootNew = deserializeBT_preOrder(elemVec);
		// printStrBT(rootNew); 

		debugDisp("test13() finished.");
	} 
}
