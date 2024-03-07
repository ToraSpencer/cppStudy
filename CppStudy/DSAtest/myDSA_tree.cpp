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


	// ���������л���ת��Ϊ1ά���飩��
	template <typename T>
	void BT2Array(TreeNode<T>* ptrNode, T* arrayHead, int i, int j, \
		const std::pair<int, int>& size = std::make_pair(0, 0))
	{
		// TΪ�������ĸ��ڵ㣬arrayHead���������ʼ��ַ��ij��ʾ��ǰ�ڵ��������е�λ��
		int ti = 0;
		int tj = 0;						// ����ڵ��к���,�亢�ӵ�j����Ϊ j��(height-i+1)/2
		int width = size.first;
		int height = size.second;

		if (nullptr != ptrNode)					//�����λ���нڵ�
		{
			*(arrayHead + i * width + j) = ptrNode->val;			// ������õ������ַ�
			if (nullptr != ptrNode->left)			// �����Һ��Ӹ���Ӧ��������,���Һ��ӵ�ֵ����һ��ݹ鸳
			{
				//���õ���������֮�������ȫ������'/'
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

			// ����ѭ��,tiǡ��ָ���亢�����ڵĲ�
			BT2Array(ptrNode->left, arrayHead, ti, j - (height - i + 1) / 2, std::make_pair(width, height));
			BT2Array(ptrNode->right, arrayHead, ti, j + (height - i + 1) / 2, std::make_pair(width, height));
		}
	}


	// ����̨�ϴ�ӡ������
	template <typename T>
	void printBT(TreeNode<T>* ptrNode)
	{
		// 1. ��̬��������ռ�
		int n = ptrNode->maxDepth();				 // ��� 
		int width = (2 << n) - 3;						 // 2^(n+1)-3������1λ���൱�ڳ���2��1�η�
		int height = (2 << (n - 1)) - 1;				// 2^n-1 
		T* a = new T[width * height];
		for (int i = 0; i < height; i++)				// �ռ��ʼ��Ϊ0
			for (int j = 0; j < width; j++)
				*(a + (i * width) + j) = 0;

		// 2. ���������л�
		BT2Array(ptrNode, a, 0, (width - 1) / 2, std::make_pair(width, height));

		// 3. ��ӡ
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

		// �ͷ��ڴ�
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

		TreeNode<char>* ptrRoot2 = new TreeNode<char>{ 'B' };
		ptrRoot2->left = new TreeNode<char>{ 'I' };
		ptrRoot2->right = new TreeNode<char>{ 'N' };
		ptrRoot2->left->left = new TreeNode<char>{ 'A' };
		ptrRoot2->left->right = new TreeNode<char>{ 'R' };
		ptrRoot2->right->left = new TreeNode<char>{ 'Y' };
		printBT(ptrRoot2);

		debugDisp("test1 finished.");

	}

}
