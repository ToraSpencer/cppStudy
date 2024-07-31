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
			std::cout << "PH, ";
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
 
#if 1
void strBT2Array(TreeNode<std::string>* ptrNode, std::string* arrayHead, int i, int k, \
	const std::pair<int, int>& size = std::make_pair(0, 0))
{  
	const std::string PH = std::string{};				// placeholder, ռλ�� 
	const std::string FS = "/";						// forward slash, ǰб��/ 
	const std::string BS = "\\";						// backward slash, ��б��\ 

	// arrayHead���������ʼ��ַ��ij��ʾ��ǰ�ڵ��������е�λ��
	int ti = 0;
	int tk = 0;						// ����ڵ��к���,�亢�ӵ�k����Ϊ k��(height-i+1)/2
	int width = size.first;
	int height = size.second;

	if (nullptr != ptrNode)					// �����λ���нڵ�
	{
		*(arrayHead + i * width + k) = ptrNode->val;			// �������λ������Ԫ�أ�
		if (nullptr != ptrNode->left)			// �����Һ��Ӹ���Ӧ��������,���Һ��ӵ�ֵ����һ��ݹ鸳
		{
			// ���õ���������֮�������ȫ������'/'
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

		// ����ѭ��,tiǡ��ָ���亢�����ڵĲ�
		strBT2Array(ptrNode->left, arrayHead, ti, k - (height - i + 1) / 2, std::make_pair(width, height));
		strBT2Array(ptrNode->right, arrayHead, ti, k + (height - i + 1) / 2, std::make_pair(width, height));
	}
}


// ����̨�ϴ�ӡ�ڵ�Ԫ��Ϊ�ַ�����BT
void printStrBT(TreeNode<std::string>* ptrNode)
{
	const std::string PH = std::string{};				// placeholder, ռλ�� 
	const std::string FS = "/";						// forward slash, ǰб��/ 
	const std::string BS = "\\";						// backward slash, ��б��\ 

	// 1. ��̬��������ռ�
	int n = ptrNode->maxDepth();				 // ��� 
	int width = (2 << n) - 3;						 // a << b��ʾ��a�Ķ�����λ�����ƶ�bλ����λ��0���ϡ��ȼ���������a *= std::pow(2, b);
	int height = (2 << (n - 1)) - 1;				// 2^n-1 
	std::vector<std::string> dataArr(width * height);
	std::string* arr = &dataArr[0]; 
	for (int i = 0; i < height; i++)				// �ռ��ʼ��Ϊռλ��
		for (int j = 0; j < width; j++)
			*(arr + (i * width) + j) = PH;

	// 2. ���л�
	strBT2Array(ptrNode, arr, 0, (width - 1) / 2, std::make_pair(width, height));

	// 3. ��ӡ
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
	// BT�������ȣ�
	void test0()
	{
		/*
			����һ��BT root �������������ȡ�
					BT�������ȣ��Ӹ��ڵ㵽��ԶҶ�ӽڵ���·���ϵĽڵ�����

			����ʹ�ò��������˼·ʵ�������ȵļ��㣺
		*/
		constexpr int PH = std::numeric_limits<int>::max();
		TreeNode<int>* ptrRoot = nullptr;
		TreeNode<int>* pn = nullptr;
		ptrRoot = deserializeBT_levelOrder(std::vector<int>{5, 0, 8, -1, 3, 6, 9, PH, PH, 1, 4});
		printBT(ptrRoot);

		// 1. maxDepth()������
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


	// ���ֱ�������
	void test1()
	{
		constexpr int PH = std::numeric_limits<int>::max();
		TreeNode<int>* ptrRoot = deserializeBT_levelOrder(std::vector<int>{\
			8, 3, 10, 2, 6, PH, 14, PH, PH, \
			4, 7, 13, PH});
		printBT(ptrRoot);

		// 1. ���ֱ���������
		debugDisp("�ݹ���������������������򡢺���");
		traverseBT(ptrRoot, dispTreeNode<int>, TRAVERSE_BT_TYPE::LevelOrder, true);
		debugDisp("\n");
		traverseBT(ptrRoot, dispTreeNode<int>, TRAVERSE_BT_TYPE::PreOrder, true);
		debugDisp("\n");
		traverseBT(ptrRoot, dispTreeNode<int>, TRAVERSE_BT_TYPE::InOrder, true);
		debugDisp("\n");
		traverseBT(ptrRoot, dispTreeNode<int>, TRAVERSE_BT_TYPE::PostOrder, true);
		debugDisp("\n");

		debugDisp("�ǵݹ���������������������򡢺���");
		traverseBT_noRecur(ptrRoot, dispTreeNode<int>, TRAVERSE_BT_TYPE::LevelOrder, true);
		debugDisp("\n");
		traverseBT_noRecur(ptrRoot, dispTreeNode<int>, TRAVERSE_BT_TYPE::PreOrder, true);
		debugDisp("\n");
		traverseBT_noRecur(ptrRoot, dispTreeNode<int>, TRAVERSE_BT_TYPE::InOrder, true);
		debugDisp("\n");
		traverseBT_noRecur(ptrRoot, dispTreeNode<int>, TRAVERSE_BT_TYPE::PostOrder, true);
		debugDisp("\n");

		// 2. ʹ���������С������������ؽ�BT:
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


	// ��תBT
	/*
	����һ��BT�ĸ��ڵ� root ����ת���BT������������ڵ㡣

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
		TreeNode<int>* ptrRoot3 = deserializeBT_levelOrder(std::vector<int>{ 9, 2, 3, PH, PH, 4, 5});
		printBT(ptrRoot3);
		destroy(ptrRoot3);

		debugDisp("test4 finished.");
	}


	// BT������·����
	/*
		����һ��BT�ĸ��ڵ� root ���� ����˳�� ���������дӸ��ڵ㵽Ҷ�ӽڵ��·����
		 vector<string> binaryTreePaths(TreeNode* root) {}
		���룺root = [1,2,3,null,5]
		�����["1->2->5","1->3"]

		���룺root = [1]
		�����["1"]

		class Solution {
			public:
				void construct_paths(TreeNode* root, string path, vector<string>& paths)
				{
					if (root != nullptr)
					{
						path += to_string(root->val);
						if (root->left == nullptr && root->right == nullptr)
						{  // ��ǰ�ڵ���Ҷ�ӽڵ�
							paths.push_back(path);                              // ��·�����뵽����
						} else
						{
							path += "->";  // ��ǰ�ڵ㲻��Ҷ�ӽڵ㣬�����ݹ����
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
		// ��ģ����������ǰBT������·�����ڣ����ڵ�+������������·�����ͣ����ڵ�+������������·����
		if (nullptr == pn)
			return;

		// 1. �ѻ��۵�·��ĩβ���뵱ǰ�ڵ�ֵ
		std::string currentPath{ recordStr };
		currentPath += std::to_string(pn->val);

		// 2. 
		if (nullptr == pn->left && nullptr == pn->right)
			paths.push_back(currentPath);				// a. �ݹ���ֹ������ǰ��Ҷ�ӽڵ㣬��ǰ·���ۼ���ϣ�ѹ��paths�У�
		else
		{
			// b. �ݹ���ơ���
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
		constexpr int PH = std::numeric_limits<int>::max();
		TreeNode<int>* pn = nullptr;
		TreeNode<int>* ptrRoot1 = deserializeBT_levelOrder(std::vector<int>{\
			8, 3, 10, 2, 6, PH, 14, PH, PH, \
			4, 7, 13, PH});
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
		ptrRoot2 = buildBST(8, std::vector<int>{5, 0, -1, 3, 6, 9, 1, 4});
		printBT(ptrRoot1);
		printBT(ptrRoot2);
		debugDisp("isBST(ptrRoot1) == ", isBST(ptrRoot1));
		debugDisp("isBST(ptrRoot2) == ", isBST(ptrRoot2));

		// 3. ����BST
		pn = searchBST(ptrRoot1, 7);
		debugDisp("pn->val == ", pn->val);
		pn = searchBST(ptrRoot1, 99);
		debugDisp("(nullptr == pn) == ", nullptr == pn);

		destroy(ptrRoot1);
		destroy(ptrRoot2);
		debugDisp("test6 finished.");
	}


	// BST��Ӧ�ã�
	void test66()
	{
		TreeNode<int>* ptrRoot1 = nullptr;
		TreeNode<int>* ptrRoot2 = nullptr;
		TreeNode<int>* ptrRoot3 = nullptr;
		TreeNode<int>* ptrRoot4 = nullptr;

		TreeNode<int>* pn = nullptr;

		// 1. BST��һ���BT����Ԫ���ٶȸ��죬�������Ƕ��ֲ���
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

		// 2. ���ϲ�����


		debugDisp("test66 finished.");
	}


	// ƽ��BST

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

		// 1. �ж�BT�Ƿ���ƽ���
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

		// 2. ��һ��BSTƽ�⻯��
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


	// JZOF18: �����ӽṹ
	/*
		��������BTA��B���ж�B�ǲ���A���ӽṹ��BT���Ķ������£�
			struct BinaryTreeNode
			{
				int                    m_nValue;
				BinaryTreeNode��       m_pLeft;
				BinaryTreeNode��       m_pRight;
			};

	*/
	void test8()
	{
		/*
				bool DoesTree1HaveTree2��BinaryTreeNode�� pRoot1, BinaryTreeNode��
	pRoot2��
	{
		if��pRoot2 == NULL��
			return true;

		if��pRoot1 == NULL��
			return false;

		if��pRoot1->m_nValue != pRoot2->m_nValue��
			return false;


		return DoesTree1HaveTree2��pRoot1->m_pLeft, pRoot2->m_pLeft�� &&
			DoesTree1HaveTree2��pRoot1->m_pRight, pRoot2->m_pRight��;
	}
		*/
	}


	// JZOF24: BST�ĺ����������
	/*
		����һ���������飬�жϸ������ǲ���ĳ�����������ĺ�������Ľ����
		������򷵻� true�����򷵻� false���������������������������ֶ�������ͬ��
		����һ���������飬�жϸ������ǲ���ĳ�����������ĺ�������Ľ����
		������򷵻� true�����򷵻� false���������������������������ֶ�������ͬ��
	*/
	void test9()
	{
		/*
			void FindPath��BinaryTreeNode�� pRoot, int expectedSum��
	{
		if��pRoot == NULL��
			return;

		std::vector<int> path;
		int currentSum = 0;
		FindPath��pRoot, expectedSum, path, currentSum��;
	}

	void FindPath
	��
		BinaryTreeNode��   pRoot,
		int                expectedSum,
		std::vector<int>& path,
		int&               currentSum
	��
	{
		currentSum += pRoot->m_nValue;
		path.push_back��pRoot->m_nValue��;

		// �����Ҷ��㣬����·���Ͻ��ĺ͵��������ֵ
		// ��ӡ������·��
		bool isLeaf = pRoot->m_pLeft == NULL && pRoot->m_pRight == NULL;
		if��currentSum == expectedSum && isLeaf��
		{
			printf��"A path is found: "��;
			std::vector<int>::iterator iter = path.begin����;
			for��; iter != path.end����; ++ iter��
				printf��"%d\t", ��iter��;

			printf��"\n"��;
		}

		// �������Ҷ��㣬����������ӽ��
		if��pRoot->m_pLeft != NULL��
			FindPath��pRoot->m_pLeft, expectedSum, path, currentSum��;
		if��pRoot->m_pRight != NULL��
			FindPath��pRoot->m_pRight, expectedSum, path, currentSum��;

		// �ڷ��ص������֮ǰ����·����ɾ����ǰ��㣬
		// ����currentSum�м�ȥ��ǰ����ֵ
		currentSum -= pRoot->m_nValue;
		path.pop_back����;
	}

		*/
	}


	// JZOF27: BST��˫������
	/*
		����һ�ö��������������ö���������ת����һ�������˫������
		Ҫ���ܴ����κ��µĽ�㣬ֻ�ܵ������н��ָ���ָ��
		��������ͼ4.12����ߵĶ����������������ת��֮�������˫������
			struct BinaryTreeNode
			{
				int                    m_nValue;
				BinaryTreeNode��       m_pLeft;
				BinaryTreeNode��       m_pRight;
			};
	*/
	void test10()
	{
		/*
					BinaryTreeNode�� Convert��BinaryTreeNode�� pRootOfTree��
	{
		BinaryTreeNode ��pLastNodeInList = NULL;
		ConvertNode��pRootOfTree, &pLastNodeInList��;

		// pLastNodeInListָ��˫�������β��㣬
		// ������Ҫ����ͷ���
		BinaryTreeNode ��pHeadOfList = pLastNodeInList;
		while��pHeadOfList != NULL && pHeadOfList->m_pLeft != NULL��
			pHeadOfList = pHeadOfList->m_pLeft;

		return pHeadOfList;
	}

	void ConvertNode��BinaryTreeNode�� pNode, BinaryTreeNode����
	pLastNodeInList��
	{
		if��pNode == NULL��
			return;

		BinaryTreeNode ��pCurrent = pNode;

		if ��pCurrent->m_pLeft != NULL��
			ConvertNode��pCurrent->m_pLeft, pLastNodeInList��;

		pCurrent->m_pLeft = ��pLastNodeInList;
		if����pLastNodeInList != NULL��
			����pLastNodeInList��->m_pRight = pCurrent;

		��pLastNodeInList = pCurrent;

		if ��pCurrent->m_pRight != NULL��
			ConvertNode��pCurrent->m_pRight, pLastNodeInList��;
	}

		*/
	}


	// JZOF39: ��Ŀ�����ж�ƽ��BT 
	/*
		����һ��BT�ĸ���㣬�жϸ����ǲ���ƽ��BT��
		���ĳBT����������������������������1����ô������һ��ƽ��BT��
			struct BinaryTreeNode
			{
				int                    m_nValue;
				BinaryTreeNode��       m_pLeft;
				BinaryTreeNode��       m_pRight;
			};
	*/
	void test11()
	{
		/*
				bool IsBalanced��BinaryTreeNode�� pRoot, int�� pDepth��
			{
				if��pRoot == NULL��
				{
					��pDepth = 0;
					return true;
				}

				int left, right;
				if��IsBalanced��pRoot->m_pLeft, &left��
					&& IsBalanced��pRoot->m_pRight, &right����
				{
					int diff = left - right;
					if��diff <= 1 && diff >= -1��
					{
						��pDepth = 1 + ��left > right ? left : right��;
						return true;
					}
				}

				return false;
			}

		bool IsBalanced��BinaryTreeNode�� pRoot��
		{
			int depth = 0;
			return IsBalanced��pRoot, &depth��;
		}

		*/

	}


	// JZOF50: ��������������͹�������
	/*
		������������㣬�����ǵ���͹������ȡ�
	*/
	void test12()
	{
		/*
				bool GetNodePath��TreeNode�� pRoot, TreeNode�� pNode, list<TreeNode��>&
	path��
	{
		if��pRoot == pNode��
			return true;

		bool found = false;

		vector<TreeNode��>::iterator i = pRoot->m_vChildren.begin����;
		while��!found && i < pRoot->m_vChildren.end������
		{
			found = GetNodePath����i, pNode, path��;
			++i;
		}

		if��!found��
			path.pop_back����;
		return found;
	}

	TreeNode�� GetLastCommonNode
	��
		const list<TreeNode��>& path1,
		const list<TreeNode��>& path2
	��
	{
		list<TreeNode��>::const_iterator iterator1 = path1.begin����;
		list<TreeNode��>::const_iterator iterator2 = path2.begin����;

		TreeNode�� pLast = NULL;

		while��iterator1 != path1.end���� && iterator2 != path2.end������
		{
			if����iterator1 == ��iterator2��
				pLast = ��iterator1;

			iterator1++;
			iterator2++;
		}

		return pLast;
	}

	TreeNode�� GetLastCommonParent��TreeNode�� pRoot, TreeNode�� pNode1,
	TreeNode�� pNode2��
	{
		if��pRoot == NULL || pNode1 == NULL || pNode2 == NULL��
			return NULL;

		list<TreeNode��> path1;
		GetNodePath��pRoot, pNode1, path1��;

		list<TreeNode��> path2;
		GetNodePath��pRoot, pNode2, path2��;

		return GetLastCommonNode��path1, path2��;
	}

		*/
	}

	
	// ����OSGB�ļ��е���״�洢�ṹ��
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
