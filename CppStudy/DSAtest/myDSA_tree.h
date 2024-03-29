#pragma once

#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <algorithm>


// TreeNode�ࡪ���������ڵ���
template <typename T>
class TreeNode
{

// ��Ա����
public:
	T val;
	TreeNode* left;
	TreeNode* right;

	// constructor & destructor:
	TreeNode() : val(0), left(nullptr), right(nullptr) {}
	TreeNode(const T x) : val(x), left(nullptr), right(nullptr) {}
	TreeNode(const T x, TreeNode* left, TreeNode* right) : val(x), left(left), right(right) {}


// get������

	// �����Ե�ǰ�ڵ�Ϊ���ڵ�Ķ������������ȣ�
	int maxDepth()
	{
		int depth = 0;
		std::queue<TreeNode<T>*> que;
		que.push(this);
		do
		{
			int size = que.size();
			depth++;											  // ��¼���
			for (int i = 0; i < size; i++)
			{
				TreeNode<T>* node = que.front();
				que.pop();
				if (nullptr != node->left)
					que.push(node->left);
				if (nullptr != node->right)
					que.push(node->right);
			}
		} while (!que.empty());
		return depth;
	}


// д������ 
};


// ����̨�ϴ�ӡ�������ڵ����Ϣ
template <typename T>
static auto dispTreeNode = [](const TreeNode<T>* ptrNode)
{
	if(nullptr == ptrNode)
		std::cout << "placeholder, ";
	else
		std::cout << ptrNode->val << ", ";
};


enum class TRAVERSE_BT_TYPE
{		
	PreOrder,					// ���������������ȱ���
	InOrder,					// �������
	PostOrder,				// �������
	LevelOrder,				// ���������������ȱ���
};


// ����������
template <typename T, typename Func>
void traverseBT(TreeNode<T>* ptrNode, Func func, \
	const TRAVERSE_BT_TYPE type = TRAVERSE_BT_TYPE::PreOrder)
{
	TreeNode<T>* ptrCurrentNode = nullptr;
	TreeNode<T>* pa = nullptr;
	TreeNode<T>* pb = nullptr;
	if (type == TRAVERSE_BT_TYPE::LevelOrder)		// �������Ρ�������������������нṹʵ�֣�
	{
		if (nullptr == ptrNode) 
			return; 
		std::queue<TreeNode<T>*> queue;
		queue.push(ptrNode);
		while (!queue.empty())
		{
			ptrCurrentNode = queue.front();
			pa = ptrCurrentNode->left;
			pb = ptrCurrentNode->right;
			queue.pop();
			func(ptrCurrentNode);
			if (nullptr != pa)
				queue.push(pa);
			if (nullptr != pb)
				queue.push(pb);
		}
	}
	else   // �ȡ��С������������ȡ�������ȷ��ʽڵ㣨���ú�����func�����ڽڵ㣩������ִ�еݹ飨�����ڵ㣩
	{
		// �ݹ���ֹ1��������ǰ�ڵ�Ϊ�գ�
		if (nullptr == ptrNode) 
			return; 

		// �ݹ���ֹ2��������ǰ�ڵ�ΪҶ��
		pa = ptrNode->left;
		pb = ptrNode->right;
		if (nullptr == pa && nullptr == pb)
		{
			func(ptrNode);
			return;
		}

		// �ݹ���ơ����Ե�ǰ�ڵ�����Һ��ӵݹ���ñ�������
		switch (type)
		{
		case TRAVERSE_BT_TYPE::PreOrder:
			func(ptrNode);
			traverseBT(pa, func);
			traverseBT(pb, func);
			break;

		case TRAVERSE_BT_TYPE::InOrder:
			traverseBT(pa, func);
			func(ptrNode);
			traverseBT(pb, func);
			break;

		case TRAVERSE_BT_TYPE::PostOrder:
			traverseBT(pa, func);
			traverseBT(pb, func);
			func(ptrNode);
			break;

		default:
			break;
		}
	} 
}


// printBT()ʹ�õ����л����������������Ǻܱ�׼��
template <typename T>
void BT2Array(TreeNode<T>* ptrNode, T* arrayHead, int i, int k, \
	const std::pair<int, int>& size = std::make_pair(0, 0))
{
	// TΪ�������ĸ��ڵ㣬arrayHead���������ʼ��ַ��ij��ʾ��ǰ�ڵ��������е�λ��
	int ti = 0;
	int tk = 0;						// ����ڵ��к���,�亢�ӵ�k����Ϊ k��(height-i+1)/2
	int width = size.first;
	int height = size.second;

	if (nullptr != ptrNode)					// �����λ���нڵ�
	{
		*(arrayHead + i * width + k) = ptrNode->val;			// �������λ������Ԫ�أ�
		if (nullptr != ptrNode->left)			// �����Һ��Ӹ���Ӧ��������,���Һ��ӵ�ֵ����һ��ݹ鸳
		{
			//���õ���������֮�������ȫ������'/'
			for (ti = i + 1, tk = k - 1; tk > k - (height - i + 1) / 2; tk--)
			{
				*(arrayHead + ti * width + tk) = -1;
				ti++;
			}
		}
		if (nullptr != ptrNode->right)
		{
			for (ti = i + 1, tk = k + 1; tk < k + (height - i + 1) / 2; tk++)
			{
				*(arrayHead + ti * width + tk) = 1;
				ti++;
			}
		}

		// ����ѭ��,tiǡ��ָ���亢�����ڵĲ�
		BT2Array(ptrNode->left, arrayHead, ti, k - (height - i + 1) / 2, std::make_pair(width, height));
		BT2Array(ptrNode->right, arrayHead, ti, k + (height - i + 1) / 2, std::make_pair(width, height));
	}
} 


// ����̨�ϴ�ӡ������
template <typename T>
void printBT(TreeNode<T>* ptrNode)
{ 
	// 1. ��̬��������ռ�
	int n = ptrNode->maxDepth();				 // ��� 
	int width = (2 << n) - 3;						 // a << b��ʾ��a�Ķ�����λ�����ƶ�bλ����λ��0���ϡ��ȼ���������a *= std::pow(2, b);
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
	std::cout << std::endl;

	// �ͷ��ڴ�
	delete[] a;
}
 

template <typename T>
void destroy(TreeNode<T>* ptrNode) 
{
	// �ݹ���ֹ1��������ǰ�ڵ�Ϊ�գ�do nothing;
	if (nullptr == ptrNode)
		return;

	// �ݹ���ֹ2��������ǰ�ڵ���Ҷ�ӣ�����delete
	TreeNode<T>* pa = ptrNode->left;
	TreeNode<T>* pb = ptrNode->right;
	if (nullptr == pa && nullptr == pb)
	{
		delete ptrNode;
		ptrNode = nullptr;
		return;
	}
	else  // �ݹ���ơ�������ǰ�ڵ㲻Ϊ���Ҳ�ΪҶ�ӣ���������Һ��ӽڵ�ݹ���ñ�������
	{
		destroy(pa);
		pa = nullptr;
		destroy(pb);
		pb == nullptr;
	}	 
}


// BT�����л�����������ȱ�����������������սڵ���ռλ��ռλ��
template <typename T>
bool serializeBT(std::vector<T>& vecOut, TreeNode<T>* ptrRoot)
{
	vecOut.clear();

	// 1. 
	std::list<T> valList;
	std::queue<TreeNode<T>*> queue; 
	const T placeholder = std::numeric_limits<T>::max();			// ʹ�õ�ǰ�������ֵ����ʾ�սڵ�ռλ����
	if (nullptr == ptrRoot)
		return true;

	// 2. ���������ѭ����
	queue.push(ptrRoot);
	while (!queue.empty())
	{
		TreeNode<T>* ptrCurrentNode = queue.front();
		queue.pop(); 
		if (nullptr == ptrCurrentNode)
		{
			valList.push_back(placeholder);
			continue;
		}
		else
		{
			valList.push_back(ptrCurrentNode->val);
			queue.push(ptrCurrentNode->left);
			queue.push(ptrCurrentNode->right);
		} 
	}  

	// 3. �����
	vecOut.insert(vecOut.end(), valList.begin(), valList.end());

	return true;
}



template <typename T>
bool deserializeBT(TreeNode<T>* ptrRoot, const std::vector<T>& vecOut)
{
	destroy(ptrRoot);

	

	return true;
}


 // ��ת�����������������񻯣����������нڵ����Һ��ӵߵ�
template <typename T>
void reverseBT(TreeNode<T>* ptrNode) 
{
	/*
		�ݹ���ƣ�������ǰ�ڵ�����Һ��ӣ�Ȼ������Һ��Ӽ������ñ�������
		�ݹ���ֹ����ǰ�ڵ��ǿյ�ʱ����ֹ��
	*/ 

	// 1. �ݹ���ֹ��
	if (nullptr == ptrNode)
		return;

	// 2. �ݹ���ƣ�
	TreeNode<T>* pa = ptrNode->left;
	TreeNode<T>* pb = ptrNode->right;	 
	ptrNode->left = pb;
	ptrNode->right = pa;
	reverseBT(pa);
	reverseBT(pb);
}




////////////////////////////////////////////////////////////////////////////////////////////// �������������㷨
/*
	����BST�������㷨
		ֱ�ӹ���BST����

		����AVL��������

		���ں����������

	���ڶѵ������㷨��

*/

namespace TREE 
{
	void test0();
	void test1();
	void test2();
	void test3();
	void test4();
	void test5();
	void test6();
	void test7();
	void test8();
	void test9();
	void test10();
	void test11();
	void test12();
	void test13();
	void test14();
	void test15();
	void test16();
}