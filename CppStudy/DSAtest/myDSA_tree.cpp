#include "myDSA_tree.h"


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


namespace TREE
{
	// �������������ȣ�
	/*
		����һ�������� root �������������ȡ�
			�������������ȣ��Ӹ��ڵ㵽��ԶҶ�ӽڵ���·���ϵĽڵ�����
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


	// ���ֱ�������
	void test1() 
	{
		constexpr int placeholder = std::numeric_limits<int>::max();
		TreeNode<int>* ptrRoot = deserializeBT_levelOrder(std::vector<int>{\
			8, 3, 10, 2, 6, placeholder, 14, placeholder, placeholder, \
			4, 7, 13, placeholder});
		printBT(ptrRoot);
		 
		// 1. ���ֱ���������
		traverseBT(ptrRoot, dispTreeNode<int>, TRAVERSE_BT_TYPE::LevelOrder);  
		debugDisp("\n");
		traverseBT(ptrRoot, dispTreeNode<int>, TRAVERSE_BT_TYPE::PreOrder); 
		debugDisp("\n");
		traverseBT(ptrRoot, dispTreeNode<int>, TRAVERSE_BT_TYPE::InOrder); 
		debugDisp("\n");
		traverseBT(ptrRoot, dispTreeNode<int>, TRAVERSE_BT_TYPE::PostOrder); 
		debugDisp("\n");

		// 2. ʹ���������С������������ؽ�BT:
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


	// ��ת������
	/*
	����һ�ö������ĸ��ڵ� root ����ת��ö�����������������ڵ㡣 

	ʾ�� 1��
		���룺root = [4,2,7,1,3,6,9]
		�����[4,7,2,9,6,3,1]
	ʾ�� 2��
	���룺root = [2,1,3]
	�����[2,3,1]
	ʾ�� 3��
	���룺root = []
	�����[]
	��ʾ��
	���нڵ���Ŀ��Χ�� [0, 100] ��
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


	// BT�����л��������л��� 
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

		// 1. �����������
		serializeBT_preOrder(valVec, ptrRoot);
		traverseSTL(valVec, dispCorrected<int>);
		TreeNode<int>* ptrRoot1 = deserializeBT_preOrder(valVec);
		printBT(ptrRoot1);
		destroy(ptrRoot1);
		
		// 2. ���ڲ��������
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


	// BT������·����
	/*
		����һ���������ĸ��ڵ� root ���� ����˳�� ���������дӸ��ڵ㵽Ҷ�ӽڵ��·���� 
		 vector<string> binaryTreePaths(TreeNode* root) {}
		���룺root = [1,2,3,null,5]
		�����["1->2->5","1->3"]

		���룺root = [1]
		�����["1"]
	
	*/
	void test5() 
	{


	}


	// ��ͬ��BST
	/*
		����һ������ n ���������ɲ����������� n ���ڵ�����ҽڵ�ֵ�� 1 �� n ������ͬ�Ĳ�ͬ ���������� ��
				���԰� ����˳�� ���ش𰸡�

		 vector<TreeNode*> generateTrees(int n) {}

		���룺n = 3
		�����[[1,null,2,null,3],[1,null,3,2],[2,1,3],[3,1,null,null,2],[3,2,null,1]] 

		���룺n = 1
		�����[[1]]	
	*/
	void test6() 
	{
		// 0. ʹ�ò������л��ķ�ʽ����һ��BST:
		constexpr int placeholder = std::numeric_limits<int>::max();
		TreeNode<int>* pn = nullptr;
		TreeNode<int>* ptrRoot1 = deserializeBT_levelOrder(std::vector<int>{\
			8, 3, 10, 2, 6, placeholder, 14, placeholder, placeholder, \
			4, 7, 13, placeholder});
		TreeNode<int>* ptrRoot2 = deserializeBT_levelOrder(std::vector<int>{1, 2, 3, 4, 5, 6, 7});
		printBT(ptrRoot1);
		printBT(ptrRoot2);

		// 1. ���һ��BT��BST��������������õ��������ǵ����������У�
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


	// ƽ��BT
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
