#pragma once

#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <algorithm>


// TreeNode类——二叉树节点类
template <typename T>
class TreeNode
{

// 成员数据
public:
	T val;
	TreeNode* left;
	TreeNode* right;

	// constructor & destructor:
	TreeNode() : val(0), left(nullptr), right(nullptr) {}
	TreeNode(const T x) : val(x), left(nullptr), right(nullptr) {}
	TreeNode(const T x, TreeNode* left, TreeNode* right) : val(x), left(left), right(right) {}


// get方法：

	// 返回以当前节点为根节点的二叉树的最大深度；
	int maxDepth()
	{
		int depth = 0;
		std::queue<TreeNode<T>*> que;
		que.push(this);
		do
		{
			int size = que.size();
			depth++;											  // 记录深度
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


// 写方法： 
};


// 控制台上打印二叉树节点的信息
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
	PreOrder,					// 先序遍历、深度优先遍历
	InOrder,					// 中序遍历
	PostOrder,				// 后序遍历
	LevelOrder,				// 层序遍历、广度优先遍历
};


// 遍历二叉树
template <typename T, typename Func>
void traverseBT(TreeNode<T>* ptrNode, Func func, \
	const TRAVERSE_BT_TYPE type = TRAVERSE_BT_TYPE::PreOrder)
{
	TreeNode<T>* ptrCurrentNode = nullptr;
	TreeNode<T>* pa = nullptr;
	TreeNode<T>* pb = nullptr;
	if (type == TRAVERSE_BT_TYPE::LevelOrder)		// 特殊情形——层序遍历，借助队列结构实现；
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
	else   // 先、中、后序遍历——取决于是先访问节点（调用函数子func作用于节点）还是先执行递归（搜索节点）
	{
		// 递归终止1——若当前节点为空：
		if (nullptr == ptrNode) 
			return; 

		// 递归终止2——若当前节点为叶子
		pa = ptrNode->left;
		pb = ptrNode->right;
		if (nullptr == pa && nullptr == pb)
		{
			func(ptrNode);
			return;
		}

		// 递归递推——对当前节点的左右孩子递归调用本函数：
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


// printBT()使用的序列化方法，看起来不是很标准；
template <typename T>
void BT2Array(TreeNode<T>* ptrNode, T* arrayHead, int i, int k, \
	const std::pair<int, int>& size = std::make_pair(0, 0))
{
	// T为二叉树的根节点，arrayHead是数组的起始地址，ij表示当前节点在数组中的位置
	int ti = 0;
	int tk = 0;						// 如果节点有孩子,其孩子的k坐标为 k±(height-i+1)/2
	int width = size.first;
	int height = size.second;

	if (nullptr != ptrNode)					// 如果该位置有节点
	{
		*(arrayHead + i * width + k) = ptrNode->val;			// 向数组该位置填入元素；
		if (nullptr != ptrNode->left)			// 有左右孩子给对应的连接线,左右孩子的值在下一层递归赋
		{
			//将该点与其左孩子之间的连线全部填上'/'
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

		// 经过循环,ti恰好指到其孩子所在的层
		BT2Array(ptrNode->left, arrayHead, ti, k - (height - i + 1) / 2, std::make_pair(width, height));
		BT2Array(ptrNode->right, arrayHead, ti, k + (height - i + 1) / 2, std::make_pair(width, height));
	}
} 


// 控制台上打印二叉树
template <typename T>
void printBT(TreeNode<T>* ptrNode)
{ 
	// 1. 动态数组申请空间
	int n = ptrNode->maxDepth();				 // 深度 
	int width = (2 << n) - 3;						 // a << b表示把a的二进制位向左移动b位，低位用0补上。等价于做运算a *= std::pow(2, b);
	int height = (2 << (n - 1)) - 1;				// 2^n-1 
	T* a = new T[width * height];
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
	std::cout << std::endl;

	// 释放内存
	delete[] a;
}
 

template <typename T>
void destroy(TreeNode<T>* ptrNode) 
{
	// 递归终止1——若当前节点为空，do nothing;
	if (nullptr == ptrNode)
		return;

	// 递归终止2——若当前节点是叶子，将其delete
	TreeNode<T>* pa = ptrNode->left;
	TreeNode<T>* pb = ptrNode->right;
	if (nullptr == pa && nullptr == pb)
	{
		delete ptrNode;
		ptrNode = nullptr;
		return;
	}
	else  // 递归递推——若当前节点不为空且不为叶子，则对其左右孩子节点递归调用本函数：
	{
		destroy(pa);
		pa = nullptr;
		destroy(pb);
		pb == nullptr;
	}	 
}


// BT的序列化——广度优先遍历（层序遍历），空节点用占位符占位；
template <typename T>
bool serializeBT(std::vector<T>& vecOut, TreeNode<T>* ptrRoot)
{
	vecOut.clear();

	// 1. 
	std::list<T> valList;
	std::queue<TreeNode<T>*> queue; 
	const T placeholder = std::numeric_limits<T>::max();			// 使用当前类型最大值来表示空节点占位符；
	if (nullptr == ptrRoot)
		return true;

	// 2. 层序遍历的循环：
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

	// 3. 输出：
	vecOut.insert(vecOut.end(), valList.begin(), valList.end());

	return true;
}



template <typename T>
bool deserializeBT(TreeNode<T>* ptrRoot, const std::vector<T>& vecOut)
{
	destroy(ptrRoot);

	

	return true;
}


 // 翻转二叉树（二叉树镜像化）——将所有节点左右孩子颠倒
template <typename T>
void reverseBT(TreeNode<T>* ptrNode) 
{
	/*
		递归递推：交换当前节点的左右孩子，然后对左右孩子继续调用本函数；
		递归终止：当前节点是空的时，终止；
	*/ 

	// 1. 递归终止：
	if (nullptr == ptrNode)
		return;

	// 2. 递归递推：
	TreeNode<T>* pa = ptrNode->left;
	TreeNode<T>* pb = ptrNode->right;	 
	ptrNode->left = pb;
	ptrNode->right = pa;
	reverseBT(pa);
	reverseBT(pb);
}




////////////////////////////////////////////////////////////////////////////////////////////// 基于树的排序算法
/*
	基于BST的排序算法
		直接构建BST排序：

		基于AVL树的排序：

		基于红黑树的排序：

	基于堆的排序算法：

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