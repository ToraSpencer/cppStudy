#pragma once
#include <iostream>
#include <vector>
#include <list>
#include <string>
#include <stack>
#include <queue>
#include <unordered_map>
#include <algorithm>
#include <exception>
#include <stdexcept>


// Ŀ¼
/*
	�������Ͷ���
	Create methods
	Read methods
	Update methods
	Delete methods
	BST���
	ƽ��BT���

*/



/////////////////////////////////////////////////////////////////////////////////////////////////////// �������Ͷ���

// TreeNode�ࡪ��BT�ڵ���
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

	// �����Ե�ǰ�ڵ�Ϊ���ڵ��BT�������ȣ�
	int maxDepth()
	{
		// BST������BT�������ɨ�裬����һ���ж��ٲ㣻
		int depth = 0;
		std::queue<TreeNode<T>*> que;			// ʹ�ö��У�Ӧ��BST��˼·��
		que.push(this);

		// ��¼��ȵ�ѭ����
		do
		{
			// dw1. ÿ����һ�����+1��
			depth++;									 

			// dw2. ��ǰ������нڵ�������ӣ������Һ�����ӣ�
			int size = que.size();			
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




///////////////////////////////////////////////////////////////////////////////////////////////////////  Create methods

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


// �ݹ麯���������벻��ռλ��������������С�����������У�����BT����
template <typename T>
TreeNode<T>* buildBT(std::vector<TreeNode<T>*>& npsPRO, std::vector<TreeNode<T>*>& npsIO)
{
	const int nodesCount = npsPRO.size();				// ������0�ڵ�����Σ�
	TreeNode<T>* ptrRoot = nullptr;

	// �ݹ���ֹ��
	if (0 == nodesCount)
		return nullptr;

	if (1 == nodesCount)
		return npsPRO[0];

	if (2 == nodesCount)
	{
		ptrRoot = npsPRO[0];
		if (ptrRoot == npsIO[0])
			ptrRoot->right = npsIO[1];
		else
			ptrRoot->left = npsIO[0];
		return ptrRoot;
	}

	// �ݹ���ƣ�
	std::vector<TreeNode<T>*> npsPRO_left, npsPRO_right, npsIO_left, npsIO_right;
	int nodesCountLeft = 0;
	int pos = 0;
	ptrRoot = npsPRO[0];
	for (; pos < nodesCount; ++pos)
		if (ptrRoot == npsIO[pos])
			break;
	nodesCountLeft = pos;

	if (nodesCountLeft > 0)
	{
		npsPRO_left.insert(npsPRO_left.end(), npsPRO.begin() + 1, npsPRO.begin() + 1 + nodesCountLeft);
		npsIO_left.insert(npsIO_left.end(), npsIO.begin(), npsIO.begin() + nodesCountLeft);
	}

	if (nodesCount - nodesCountLeft - 1 > 0)
	{
		npsPRO_right.insert(npsPRO_right.end(), npsPRO.begin() + 1 + nodesCountLeft, npsPRO.end());
		npsIO_right.insert(npsIO_right.end(), npsIO.begin() + nodesCountLeft + 1, npsIO.end());
	}
	ptrRoot->left = buildBT(npsPRO_left, npsIO_left);
	ptrRoot->right = buildBT(npsPRO_right, npsIO_right);

	return ptrRoot;
}


template <typename T>
TreeNode<T>* buildBT(const std::vector<T>& vecPRO, const std::vector<T>& vecIO)
{
	/*
		��������һ�������ԣ�ǰ���������ʽ����
				���ڵ�, [��������ǰ��������], [��������ǰ��������]
				�����ڵ�����ǰ������еĵ�һ���ڵ㡣
		�����������ʽ����
				[������������������], ���ڵ�, [������������������]

		�ؽ�BT������Ҫ�������������Ž��ж�λ��

		�ؽ��ĵݹ���̣�
				�ݹ���ֹ��
						����ǰ�ڵ���������3��
								��ֱ�ӵõ��������
				�ݹ���ƣ�

	*/
	TreeNode<T>* ptrRoot = nullptr;
	if (vecPRO.empty())
		return nullptr;

	// 1. �������нڵ㣻
	const int nodesCount = vecPRO.size();
	std::unordered_map<T, TreeNode<T>*> map;
	std::vector<TreeNode<T>*> npsPRO(nodesCount), npsIO(nodesCount);
	for (int i = 0; i < nodesCount; ++i)
	{
		npsPRO[i] = new TreeNode<T>(vecPRO[i]);
		map.insert(std::make_pair(vecPRO[i], npsPRO[i]));
	}
	for (int i = 0; i < nodesCount; ++i)
		npsIO[i] = map[vecIO[i]];

	// 2. 
	ptrRoot = buildBT(npsPRO, npsIO);


	return ptrRoot;
}




///////////////////////////////////////////////////////////////////////////////////////////////////////  Read methods

// ����̨�ϴ�ӡBT�ڵ����Ϣ
template <typename T>
static auto dispTreeNode = [](const TreeNode<T>* ptrNode)
{
	if (nullptr == ptrNode)
		std::cout << "*, ";
	else
		std::cout << ptrNode->val << ", ";
};


// printBT()ʹ�õ����л����������������Ǻܱ�׼��
template <typename T>
void BT2Array(TreeNode<T>* ptrNode, T* arrayHead, int i, int k, \
	const std::pair<int, int>& size = std::make_pair(0, 0))
{
	const T PH = std::numeric_limits<T>::max();				// placeholder, ռλ�� 
	const T FS = std::numeric_limits<T>::min();				// forward slash, ǰб��/ 
	const T BS = std::numeric_limits<T>::min() + 1;			// backward slash, ��б��\ 

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
		BT2Array(ptrNode->left, arrayHead, ti, k - (height - i + 1) / 2, std::make_pair(width, height));
		BT2Array(ptrNode->right, arrayHead, ti, k + (height - i + 1) / 2, std::make_pair(width, height));
	}
}


// ����̨�ϴ�ӡBT
template <typename T>
void printBT(TreeNode<T>* ptrNode)
{
	const T PH = std::numeric_limits<T>::max();				// placeholder, ռλ�� 
	const T FS = std::numeric_limits<T>::min();				// forward slash, ǰб�� 
	const T BS = std::numeric_limits<T>::min() + 1;			// backward slash, ��б�� 

	// 1. ��̬��������ռ�
	int n = ptrNode->maxDepth();				 // ��� 
	int width = (2 << n) - 3;						 // a << b��ʾ��a�Ķ�����λ�����ƶ�bλ����λ��0���ϡ��ȼ���������a *= std::pow(2, b);
	int height = (2 << (n - 1)) - 1;				// 2^n-1 
	T* arr = new T[width * height];
	for (int i = 0; i < height; i++)				// �ռ��ʼ��Ϊռλ��
		for (int j = 0; j < width; j++)
			*(arr + (i * width) + j) = PH;

	// 2. ���л�
	BT2Array(ptrNode, arr, 0, (width - 1) / 2, std::make_pair(width, height));

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

	// �ͷ��ڴ�
	delete[] arr;
}


// �ݹ麯����������BT��to be optimized������ǰDFS�в������սڵ�ķ���ò������
template <typename T, typename Func>
void traverseBT(TreeNode<T>* ptrNode, Func func, \
	const TRAVERSE_BT_TYPE type = TRAVERSE_BT_TYPE::PreOrder, \
	const bool skipNP = true)
{
	TreeNode<T>* ptrCn = nullptr;
	TreeNode<T>* pa = nullptr;
	TreeNode<T>* pb = nullptr;
	if (type == TRAVERSE_BT_TYPE::LevelOrder)		// ���������������ȱ��������������нṹʵ�֣�
	{
		std::queue<TreeNode<T>*> qt;
		if (nullptr == ptrNode)
		{
			if (!skipNP)
				func(ptrNode);
			return;
		}
		qt.push(ptrNode);

		// BST��ѭ����
		while (!qt.empty())
		{
			// w1. ȡ���׽ڵ㣬�����������
			ptrCn = qt.front();
			if (nullptr == ptrCn)
			{
				if (!skipNP)
					func(ptrCn);
				qt.pop();
				continue;
			}
			pa = ptrCn->left;
			pb = ptrCn->right;

			// w2. ���׽ڵ���ӡ�����
			qt.pop();
			func(ptrCn);

			// w3. �������
			qt.push(pa);
			qt.push(pb);
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


// ����BT�����ǵݹ鷽����to be optimized������ǰDFS�в������սڵ�ķ���ò������
template <typename T, typename Func>
void traverseBT_noRecur(TreeNode<T>* ptrNode, Func func, \
	const TRAVERSE_BT_TYPE type = TRAVERSE_BT_TYPE::PreOrder, \
	const bool skipNP = true)
{
	// 
	TreeNode<T>* ptrCn = nullptr;
	TreeNode<T>* pa = nullptr;
	TreeNode<T>* pb = nullptr;
	if (nullptr == ptrNode)
		return;

	if (TRAVERSE_BT_TYPE::LevelOrder == type)		// ���������������ȱ��������������нṹʵ�֣�
	{
		std::queue<TreeNode<T>*> qt;
		if (nullptr == ptrNode)
		{
			if (!skipNP)
				func(ptrNode);
			return;
		}
		qt.push(ptrNode);

		// BST��ѭ����
		while (!qt.empty())
		{
			// w1. ȡ���׽ڵ㣬�����������
			ptrCn = qt.front();
			if (nullptr == ptrCn)
			{
				if (!skipNP)
					func(ptrCn);
				qt.pop();
				continue;
			}
			pa = ptrCn->left;
			pb = ptrCn->right;

			// w2. ���׽ڵ���ӡ�����
			qt.pop();
			func(ptrCn);

			// w3. �������
			qt.push(pa);
			qt.push(pb);
		}
	}
	else				   // ����ջstackʵ�ֵ�������ȱ���
	{
		// ����ѹջ����ջ���ʲ����������������ֲ����Ĵ�����Է�Ϊ�������򡢺����������ͣ�
		std::stack<TreeNode<T>*> st;
		std::unordered_map<TreeNode<T>*, int> status;		// -1: δ����,  0: �ѷ���,  1: ��������ɡ�������δ���,  2: �������������, 3: �ѷ���;
		st.push(ptrNode);
		status.insert(std::make_pair(ptrNode, 0));				// �ڵ�ѹջʱ�����Ϊ���ѷ��֡�״̬

		switch (type)
		{
		case TRAVERSE_BT_TYPE::PreOrder:
		{
			// DFS_PRO��ѭ����
			while (!st.empty())
			{
				// w1. ȡջ���ڵ���Ϊ��ǰ�ڵ㣻
				ptrCn = st.top();
				auto iter = status.find(ptrCn);						// ��ǰ�ڵ���״̬�ֵ��ж�Ӧ�ļ�ֵ�ԣ�

				// w2. ������ǰ�ڵ㡪��״̬�����Һ���
				if (nullptr != ptrCn)
				{
					if (iter == status.end())
					{
						auto ret = status.insert(std::make_pair(ptrCn, 0));
						iter = ret.first;
					}
					else
					{
						if (3 == status[ptrCn])
						{
							st.pop();
							continue;
						}
					}
					pa = ptrCn->left;
					pb = ptrCn->right;
				}

				// w3. ��ջ������
				st.pop();
				if (nullptr == ptrCn)
				{
					if (!skipNP)
						func(ptrCn);
					continue;
				}
				func(ptrCn);
				status[ptrCn] = 3;

				// w4. ��������ѹ��ջ
				st.push(pb);

				// w5. ��������ѹ��ջ��
				st.push(pa);
			}
			break;
		}
		case TRAVERSE_BT_TYPE::InOrder:
		{
			// DFS_IO��ѭ����
			while (!st.empty())
			{
				// w1. ȡջ���ڵ���Ϊ��ǰ�ڵ㣻
				ptrCn = st.top();

				// w2. ������ǰ�ڵ㡪��״̬�����Һ���
				auto iter = status.find(ptrCn);						// ��ǰ�ڵ���״̬�ֵ��ж�Ӧ�ļ�ֵ�ԣ�
				if (iter == status.end())
				{
					auto ret = status.insert(std::make_pair(ptrCn, 0));
					iter = ret.first;
				}
				else
				{
					if (3 == status[ptrCn])
					{
						st.pop();
						continue;
					}
				}
				pa = ptrCn->left;
				pb = ptrCn->right;

				// w3. ��������ѹջ��ѭ�����������ף�
				while (0 == iter->second)			// ����ǰ�ڵ�δ���������
				{
					// ww1. ��ǰ�ڵ�״̬�޸ģ�
					status[ptrCn] = 1;					// ����������ɣ�

					if (nullptr == pa)
						break;
					else
					{
						// w2. ������ջ��
						st.push(pa);

						// w3. ��ǰ�ڵ����
						ptrCn = pa;
						pa = ptrCn->left;
						pb = ptrCn->right;

						// w4. ���ҵ�ǰ�ڵ��Ӧ��״̬��
						iter = status.find(ptrCn);
						if (iter == status.end())
						{
							auto ret = status.insert(std::make_pair(ptrCn, 0));
							iter = ret.first;
						}
					}
				}

				// w4. ��ջ������
				st.pop();
				func(ptrCn);
				status[ptrCn] = 3;

				// w5. ��������ѹ��ջ 
				if (nullptr != pb)
					st.push(pb);
			}
			break;
		}
		case TRAVERSE_BT_TYPE::PostOrder:
		{
			// DFS_POO��ѭ����
			while (!st.empty())
			{
				// w1. ȡջ���ڵ���Ϊ��ǰ�ڵ㣻
				ptrCn = st.top();
				auto iter = status.find(ptrCn);						// ��ǰ�ڵ���״̬�ֵ��ж�Ӧ�ļ�ֵ�ԣ�
				if (iter == status.end())
				{
					auto ret = status.insert(std::make_pair(ptrCn, 0));
					iter = ret.first;
				}
				else
				{
					if (3 == status[ptrCn])
					{
						st.pop();
						continue;
					}
				}
				pa = ptrCn->left;
				pb = ptrCn->right;

				// w2. ������ѹջ��ѭ����
				do
				{
					// wc3.1 ����������
					while (0 == iter->second)			// ����ǰ�ڵ�δ���������
					{
						// ww1. ��ǰ�ڵ�״̬�޸ģ�
						status[ptrCn] = 1;					// ����������ɣ�

						if (nullptr == pa)
							break;
						else
						{
							// w2. ������ջ��
							st.push(ptrCn->left);

							// w3. ��ǰ�ڵ����
							ptrCn = pa;
							pa = ptrCn->left;
							pb = ptrCn->right;

							// w4. ���ҵ�ǰ�ڵ��Ӧ��״̬��
							iter = status.find(ptrCn);
							if (iter == status.end())
							{
								auto ret = status.insert(std::make_pair(ptrCn, 0));
								iter = ret.first;
							}
						}
					}

					// wc3.2 ����������
					while (1 == iter->second)
					{
						// w1. ��ǰ�ڵ�״̬�޸ģ�
						status[ptrCn] = 2;					// ����������ɣ�

						if (nullptr == pb)
							break;
						else
						{
							// w2. ������ջ��
							st.push(ptrCn->right);

							// w3. ��ǰ�ڵ����
							ptrCn = pb;
							pa = ptrCn->left;
							pb = ptrCn->right;

							// w4. ���ҵ�ǰ�ڵ��Ӧ��״̬��
							iter = status.find(ptrCn);
							if (iter == status.end())
							{
								auto ret = status.insert(std::make_pair(ptrCn, 0));
								iter = ret.first;
							}
						}
					}
				} while (iter->second < 2);

				// w3. ���ʡ���ֻ��ջ��Ԫ����������������ſ��Գ�ջ���ʣ�
				func(ptrCn);
				status[ptrCn] = 3;
				st.pop();
			}

			break;
		}

		default:
			break;
		}

	}
}


// BT�����л��������ڹ�����ȱ�����������������սڵ���ռλ��ռλ��
template <typename T>
bool serializeBT_levelOrder(std::vector<T>& vecOut, TreeNode<T>* ptrRoot)
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
		TreeNode<T>* ptrCn = queue.front();
		queue.pop();
		if (nullptr == ptrCn)
		{
			valList.push_back(placeholder);
			continue;
		}
		else
		{
			valList.push_back(ptrCn->val);
			queue.push(ptrCn->left);
			queue.push(ptrCn->right);
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
	const int maxSize = std::pow(2, maxDepth) - 1;					// ���ΪmaxDepth����BT�Ľڵ�����
	TreeNode<T>* ptrCn = nullptr;
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


template <typename T>
int countNodes(TreeNode<T>* ptrRoot)
{
	int count = 0;
	traverseBT(ptrRoot, [&count](TreeNode<T>* pn) 
		{
			count++;
		}, TRAVERSE_BT_TYPE::PreOrder, true);
	return count;
}



///////////////////////////////////////////////////////////////////////////////////////////////////////  Update methods

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



///////////////////////////////////////////////////////////////////////////////////////////////////////  Delete methods

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




/////////////////////////////////////////////////////////////////////////////////////////////////////// BST��أ�

// �ж�һ��BT�����Ƿ���BST
template<typename T>
bool isBST(TreeNode<T>* ptrRoot)
{
	/*
		BST�ĳ�Ҫ������������������ɵ������ǵ��������ģ�
	*/

	std::vector<T> valVec;
	if (nullptr == ptrRoot)
		return true;

	// 1. ������������n_max == (2^d - 1)��������
	const int maxDepth = ptrRoot->maxDepth();
	valVec.reserve(std::pow(2, maxDepth) - 1);

	// 2. ���ɽڵ�ֵ�������������
	traverseBT(ptrRoot, [&valVec](TreeNode<T>* np)
		{
			valVec.push_back(np->val);

		}, TRAVERSE_BT_TYPE::InOrder);
	valVec.shrink_to_fit();

	// 3. �ж������Ƿ��ǵ��������ģ�
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


// ����һ��BST���󣬸��ڵ�ֵΪheadVal�����ɵ�BST���ܷǳ���ƽ�⣻
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
	// �������Ƕ��ֲ��ң�ʱ�临�Ӷ�ΪO(logn)��BST����ͽ�Ԫ�ذ���С���Ϸֳ����飬ֻҪ�ݹ�������ȥ����Ȼ��ʵ���˶��ֲ��ң�

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




/////////////////////////////////////////////////////////////////////////////////////////////////////// ƽ��BT��أ�
   
// �ж�BT�Ƿ���ƽ��ģ�
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


// ��BST��ƽ�⣨to be completed��
template<typename T>
TreeNode<T>* makeBalanced(TreeNode<T>* ptrRoot, const std::vector<T>& inOrderVec)
{
	// 



}


template<typename T>
TreeNode<T>* makeBalanced(TreeNode<T>* ptrRoot)
{
	/*
		����һ��̰�Ĺ���
		˼·
			��ƽ�⡹Ҫ������һ�ÿ����������������������ĸ߶Ȳ�ľ���ֵ������ 111��
			������������ǲ����������뷨�������������Ĵ�СԽ��ƽ������������᲻��Խƽ�⣿
			����һ��̰�Ĳ��Եĳ��ξ��γ��ˣ����ǿ���ͨ�����������ԭ���Ķ���������ת��Ϊһ���������У�
				Ȼ�������������еݹ齨������������ [L,R][L, R][L,R]��
			 
		���룺root = [1,null,2,null,3,null,4,null,null]
		�����[2,1,3,null,null,null,4]
		���ͣ��ⲻ��Ψһ����ȷ�𰸣�[3,1,4,null,2,null,null] Ҳ��һ�����еĹ��췽����
	*/
	 


	return true;
}




/////////////////////////////////////////////////////////////////////////////////////////////////////// ����BT�������㷨
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
	void test66();
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