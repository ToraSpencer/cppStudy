#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <stack>
#include <queue>
#include <unordered_map>
#include <algorithm>
#include <exception>
#include <stdexcept>


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


// ö���ࡪ��BT�ı�������
enum class TRAVERSE_BT_TYPE
{		
	// ������ȱ�����
	PreOrder,					// �������
	InOrder,					// �������
	PostOrder,				// �������

	// ������ȱ��������������
	LevelOrder,				
};


// ����BT
template <typename T, typename Func>
void traverseBT(TreeNode<T>* ptrNode, Func func, \
	const TRAVERSE_BT_TYPE type = TRAVERSE_BT_TYPE::PreOrder, const bool skipNP = true)
{
	TreeNode<T>* ptrCurrentNode = nullptr;
	TreeNode<T>* pa = nullptr;
	TreeNode<T>* pb = nullptr;
	if (type == TRAVERSE_BT_TYPE::LevelOrder)		// �������Ρ�������������������нṹʵ�֣�
	{
		std::queue<TreeNode<T>*> queue;
		if (nullptr == ptrNode)
		{
			if (!skipNP)
				func(ptrNode);
			return;
		}

		queue.push(ptrNode);
		while (!queue.empty())
		{
			// ȡ�ڵ���Լ���ӡ� ������ӡ����ӡ� ���ʽڵ㣻
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
	else		 // ������ȱ��������ȡ��С�����ȡ�������ȷ��ʽڵ㣨���ú�����func�����ڽڵ㣩������ִ�еݹ飨�����ڵ㣩
	{
		// �ݹ���ֹ1��������ǰ�ڵ�Ϊ�գ�
		if (nullptr == ptrNode)
		{
			if (!skipNP)
				func(ptrNode);
			return;
		}

		// �ݹ���ֹ2��������ǰ�ڵ�ΪҶ��
		pa = ptrNode->left;
		pb = ptrNode->right;
		if (nullptr == pa && nullptr == pb)
		{
			func(ptrNode);
			if (!skipNP)
			{
				func(pa);
				func(pb);
			}
			return;
		}

		// �ݹ���ơ����Ե�ǰ�ڵ�����Һ��ӵݹ���ñ�������
		switch (type)
		{
		case TRAVERSE_BT_TYPE::PreOrder:
			func(ptrNode);
			traverseBT(pa, func, type, skipNP);
			traverseBT(pb, func, type, skipNP);
			break;

		case TRAVERSE_BT_TYPE::InOrder:
			traverseBT(pa, func, type, skipNP);
			func(ptrNode);
			traverseBT(pb, func, type, skipNP);
			break;

		case TRAVERSE_BT_TYPE::PostOrder:
			traverseBT(pa, func, type, skipNP);
			traverseBT(pb, func, type, skipNP);
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


// ����̨�ϴ�ӡBT
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

	// 2. ���л�
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
 

// ɾ����ptrNodeΪ���ڵ��BT
template <typename T>
void destroy(TreeNode<T>*& ptrNode) 
{
	// �ݹ���ֹ1��������ǰ�ڵ�Ϊ�գ�do nothing;
	if (nullptr == ptrNode)
		return;

	// �ݹ���ֹ2��������ǰ�ڵ���Ҷ�ӣ�����delete
	TreeNode<T>*& pa = ptrNode->left;
	TreeNode<T>*& pb = ptrNode->right;
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


// BT�����л��������ڹ�����ȱ�����������������սڵ���ռλ��ռλ��
template <typename T>
bool serializeBT_levelOrder (std::vector<T>& vecOut, TreeNode<T>* ptrRoot)
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


// BT�ķ����л��������ڹ�����ȱ�����
template <typename T>
TreeNode<T>* deserializeBT_levelOrder(const std::vector<T>& vecVal) 
{
	const T placeholder = std::numeric_limits<T>::max();
	std::queue<TreeNode<T>*> QS, QF;
	TreeNode<T>* ptrRoot = nullptr;
	TreeNode<T>* pn = nullptr;
	TreeNode<T>* pa = nullptr;
	TreeNode<T>* pb = nullptr;

	// 0.
	if (vecVal.empty())
		return ptrRoot;

	// 1. �������нڵ㣻
	for (const auto elem : vecVal)
	{
		if (placeholder == elem)
			QS.push(nullptr);
		else
			QS.push(new TreeNode<T>(elem));
	}

	// 2. ���Ӹ��ӵ�ѭ����
	ptrRoot = QS.front();
	pn = ptrRoot;
	QS.pop();
	QF.push(pn);
	while (!QF.empty())			
	{
		pn = QF.front();
		QF.pop();

		if (QS.empty())			// �ӽڵ�ջ���˵Ļ�������ʣ�µĸ��ڵ�ȫ����Ҷ�ӽڵ㣻
			continue;
		pa = QS.front();
		QS.pop();
		pn->left = pa;

		if (QS.empty())
			continue;
		pb = QS.front();
		QS.pop();
		pn->right = pb;

		if (nullptr != pa)
			QF.push(pa);
		if (nullptr != pb)
			QF.push(pb);
	}

	return ptrRoot;
} 


// BT�����л����������������
template <typename T>
bool serializeBT_preOrder(std::vector<T>& vecOut, TreeNode<T>* ptrRoot)
{
	const T placeholder = std::numeric_limits<T>::max();
	const int maxDepth = ptrRoot->maxDepth();
	const int maxSize = std::pow(2, maxDepth) - 1;					// ���ΪmaxDepth�����������Ľڵ�����
	TreeNode<T>* ptrCurrentNode = nullptr;
	TreeNode<T>* pa = nullptr;
	TreeNode<T>* pb = nullptr;
	vecOut.reserve(maxSize); 
	 
	traverseBT(ptrRoot, [&vecOut, placeholder](TreeNode<T>* pn)\
	{
		if (nullptr == pn)
			vecOut.push_back(placeholder);
		else
			vecOut.push_back(pn->val);
	}, TRAVERSE_BT_TYPE::PreOrder, false);
 
	return true;
}
 

// �ݹ麯�����������л�����������ȡԪ�أ������л�BT����deserializeBT_preOrder()�е���
template <typename T>
TreeNode<T>* buildBT(std::queue<T>& queue)
{
	const T placeholder = std::numeric_limits<T>::max();
	TreeNode<T>* pn = nullptr;

	// �ݹ���ֹ1�����������е�Ԫ����ȫ��ȡ��
	if (queue.empty())
		return pn;

	// �ݹ���ֹ2����ǰԪ��Ϊռλ������Ӧ�սڵ㣻
	const T elem = queue.front();
	queue.pop();
	if (placeholder == elem) 		
		return pn; 

	// �ݹ���ƣ�������ǰ�ڵ㣬val��ֵΪ���������еĵ�ǰԪ�أ� 
	pn = new TreeNode<T>(elem);
	pn->left = buildBT(queue);
	pn->right = buildBT(queue); 

	return pn;
}
 

// BT�ķ����л������������������
template <typename T>
TreeNode<T>* deserializeBT_preOrder(const std::vector<T>& vecVal)
{
	const T placeholder = std::numeric_limits<T>::max();
	TreeNode<T>* ptrRoot = nullptr;

	if (vecVal.empty())
		return ptrRoot;
	
	std::queue<T> queue;
	for (const auto& elem : vecVal)
		queue.push(elem);
	ptrRoot = buildBT(queue);
	return ptrRoot;
}


 // ��תBT��BT���񻯣����������нڵ����Һ��ӵߵ�
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



////////////////////////////////////////////////////////////////////////////////////////////// BST��أ�

// �ж�һ��BT�����Ƿ���BST
template<typename T>
bool isBST(TreeNode<T>* ptrRoot)
{
	/*
		BT�ĳ�Ҫ������������������ɵ������ǵ��������ģ�
	*/

	std::vector<T> valVec;
	if (nullptr == ptrRoot)
		return true;

	const int maxDepth = ptrRoot->maxDepth();
	valVec.reserve(std::pow(2, maxDepth) - 1);
	traverseBT(ptrRoot, [&valVec](TreeNode<T>* np)
		{
			valVec.push_back(np->val);

		}, TRAVERSE_BT_TYPE::InOrder);
	valVec.shrink_to_fit();
	for (int i = 0; i < valVec.size() - 1; ++i) 
		if (valVec[i] >= valVec[i + 1])
			return false; 

	return true;
}


// BST�в����½ڵ�
template<typename T>
TreeNode<T>* insert_BST(TreeNode<T>*& pn, const T data) 
{
	/*
		TreeNode<T>* insert_BST(				���ص�ǰBST����ĸ��ڵ㣨�Ǿ��Եĸ��ڵ㣬������û���ˣ���
			TreeNode<T>*& ptrRoot,			������ڵ��BST�ĸ��ڵ㣻�������Ϊnullptr��������һ��BST�ڵ����
			const T data									����ڵ��ֵ��
			)

	*/
	TreeNode<T>* pnNew = nullptr;

	// �ݹ���ֹ������ǰ�ڵ�ָ��Ϊ�գ�����һ���½ڵ�
	if (nullptr == pn)
	{
		pn = new TreeNode<T>(data);
		return pn;
	}

	// �ݹ���ơ�����dataС�ڵ�ǰ�ڵ�ֵ�����������������˽ڵ㣻
	if (data == pn->val) 
		throw(std::invalid_argument("BST cannot have two nodes with same value."));							// !!!error: BST����������ֵͬ�Ľڵ㣬�׳��쳣��
	else if (data < pn->val)
		insert_BST(pn->left, data);
	else 
		insert_BST(pn->right, data);
}


// ����һ��BST����
template <typename T>
TreeNode<T>* buildBST(const T headVal, const std::vector<T>& valVec)
{
	TreeNode<T>* ptrRoot = new TreeNode<T>(headVal);
	for (const auto& elem : valVec)
		insert_BST(ptrRoot, elem);
	return ptrRoot;
}


// ��BST������ֵΪdata�Ľڵ�
template <typename T>
TreeNode<T>* searchBST(TreeNode<T>* ptrRoot, const T data) 
{ 	
	// �ݹ���ֹ1��	
	if (nullptr == ptrRoot)
		return nullptr;

	// �ݹ���ֹ2��
	if (data == ptrRoot->val)
		return ptrRoot;
	
	// �ݹ���ƣ�
	if (data < ptrRoot->val)
		searchBST(ptrRoot->left, data);
	else
		searchBST(ptrRoot->right, data); 
}


////////////////////////////////////////////////////////////////////////////////////////////// ƽ��BT��أ�
   
// �ж���pnΪ���ڵ��BT�Ƿ���ƽ��ģ�
template<typename T>
bool isBalanced(TreeNode<T>* ptrRoot)
{
	/*
		ÿ���ڵ�����������ĸ߶Ȳ�ľ���ֵ������1��
			һ��BT��ƽ��BT�����ҽ�������������Ҳ����ƽ��BT�� 
	*/

	// ���Ժ��������BT�� ���ǰ��������Ƿ�ƽ��ģ�����ľͿ϶��Ƿ�ƽ��ģ�
	std::list<TreeNode<T>*> nodePtrList;
	if (nullptr == ptrRoot)
		return true;

	traverseBT(ptrRoot, [&nodePtrList](TreeNode<T>* np)
		{
			nodePtrList.push_back(np);
		}, TRAVERSE_BT_TYPE::PostOrder);

	for (auto np : nodePtrList)
	{
		int DL = (nullptr == np->left) ? 0 : np->left->maxDepth();
		int DR = (nullptr == np->right) ? 0 : np->right->maxDepth();
		if (std::abs(DL - DR) > 1)
			return false;
	}
	return true;
}



////////////////////////////////////////////////////////////////////////////////////////////// ����BT�������㷨
/*
	����BST�������㷨
		ֱ�ӹ���BST����

		����AVL��������

		���ں����������

	���ڶѵ������㷨��

*/ 


#if 0
template <typename T>
TreeNode<T>* buildHeap(const std::vector<T>& valVec)
{
	TreeNode<T>* ptrRoot = nullptr;
	if (valVec.empty())
		return nullptr;

	const T max = valVec[0];
	for (const auto elem : valVec)
		if (max < elem)
			max = elem;

	ptrRoot = new TreeNode<T>(max);
	

	return ptrRoot;
}
#endif



////////////////////////////////////////////////////////////////////////////////////////////// ���Ժ�����
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