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


// 目录
/*
	基本类型定义
	Create methods
	Read methods
	Update methods
	Delete methods
	BST相关
	平衡BT相关

*/



/////////////////////////////////////////////////////////////////////////////////////////////////////// 基本类型定义

// TreeNode类——BT节点类
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

	// 返回以当前节点为根节点的BT的最大深度；
	int maxDepth()
	{
		// BST作用于BT对象，逐层扫描，数出一共有多少层；
		int depth = 0;
		std::queue<TreeNode<T>*> que;			// 使用队列，应用BST的思路：
		que.push(this);

		// 记录深度的循环：
		do
		{
			// dw1. 每往下一层深度+1；
			depth++;									 

			// dw2. 当前层的所有节点逐个出队，其左右孩子入队；
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


// 写方法： 
};


// 枚举类——BT的遍历类型
enum class TRAVERSE_BT_TYPE
{
	// 深度优先遍历：
	PreOrder,					// 先序遍历
	InOrder,					// 中序遍历
	PostOrder,				// 后序遍历

	// 广度优先遍历（层序遍历）
	LevelOrder,
};




///////////////////////////////////////////////////////////////////////////////////////////////////////  Create methods

// 递归函数——从序列化的向量中提取元素，反序列化BT，在deserializeBT_preOrder()中调用
template <typename T>
TreeNode<T>* buildBT(std::queue<T>& queue)
{
	const T placeholder = std::numeric_limits<T>::max();
	TreeNode<T>* pn = nullptr;

	// 递归终止1：序列向量中的元素已全部取完
	if (queue.empty())
		return pn;

	// 递归终止2：当前元素为占位符，对应空节点；
	const T elem = queue.front();
	queue.pop();
	if (placeholder == elem)
		return pn;

	// 递归递推：创建当前节点，val赋值为序列向量中的当前元素； 
	pn = new TreeNode<T>(elem);
	pn->left = buildBT(queue);
	pn->right = buildBT(queue);

	return pn;
}


// 递归函数——输入不含占位符的先序遍历序列、中序遍历序列，建立BT对象；
template <typename T>
TreeNode<T>* buildBT(std::vector<TreeNode<T>*>& npsPRO, std::vector<TreeNode<T>*>& npsIO)
{
	const int nodesCount = npsPRO.size();				// 不会有0节点的情形；
	TreeNode<T>* ptrRoot = nullptr;

	// 递归终止：
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

	// 递归递推：
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
		对于任意一颗树而言，前序遍历的形式总是
				根节点, [左子树的前序遍历结果], [右子树的前序遍历结果]
				即根节点总是前序遍历中的第一个节点。
		中序遍历的形式总是
				[左子树的中序遍历结果], 根节点, [右子树的中序遍历结果]

		重建BT对象需要对上面两个括号进行定位；

		重建的递归过程：
				递归终止：
						若当前节点数不大于3：
								可直接得到这棵树；
				递归递推：

	*/
	TreeNode<T>* ptrRoot = nullptr;
	if (vecPRO.empty())
		return nullptr;

	// 1. 生成所有节点；
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

// 控制台上打印BT节点的信息
template <typename T>
static auto dispTreeNode = [](const TreeNode<T>* ptrNode)
{
	if (nullptr == ptrNode)
		std::cout << "*, ";
	else
		std::cout << ptrNode->val << ", ";
};


// printBT()使用的序列化方法，看起来不是很标准；
template <typename T>
void BT2Array(TreeNode<T>* ptrNode, T* arrayHead, int i, int k, \
	const std::pair<int, int>& size = std::make_pair(0, 0))
{
	const T PH = std::numeric_limits<T>::max();				// placeholder, 占位符 
	const T FS = std::numeric_limits<T>::min();				// forward slash, 前斜杠/ 
	const T BS = std::numeric_limits<T>::min() + 1;			// backward slash, 后斜杠\ 

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
		BT2Array(ptrNode->left, arrayHead, ti, k - (height - i + 1) / 2, std::make_pair(width, height));
		BT2Array(ptrNode->right, arrayHead, ti, k + (height - i + 1) / 2, std::make_pair(width, height));
	}
}


// 控制台上打印BT
template <typename T>
void printBT(TreeNode<T>* ptrNode)
{
	const T PH = std::numeric_limits<T>::max();				// placeholder, 占位符 
	const T FS = std::numeric_limits<T>::min();				// forward slash, 前斜杠 
	const T BS = std::numeric_limits<T>::min() + 1;			// backward slash, 后斜杠 

	// 1. 动态数组申请空间
	int n = ptrNode->maxDepth();				 // 深度 
	int width = (2 << n) - 3;						 // a << b表示把a的二进制位向左移动b位，低位用0补上。等价于做运算a *= std::pow(2, b);
	int height = (2 << (n - 1)) - 1;				// 2^n-1 
	T* arr = new T[width * height];
	for (int i = 0; i < height; i++)				// 空间初始化为占位符
		for (int j = 0; j < width; j++)
			*(arr + (i * width) + j) = PH;

	// 2. 序列化
	BT2Array(ptrNode, arr, 0, (width - 1) / 2, std::make_pair(width, height));

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

	// 释放内存
	delete[] arr;
}


// 递归函数——遍历BT（to be optimized——当前DFS中不跳过空节点的方法貌似有误）
template <typename T, typename Func>
void traverseBT(TreeNode<T>* ptrNode, Func func, \
	const TRAVERSE_BT_TYPE type = TRAVERSE_BT_TYPE::PreOrder, \
	const bool skipNP = true)
{
	TreeNode<T>* ptrCn = nullptr;
	TreeNode<T>* pa = nullptr;
	TreeNode<T>* pb = nullptr;
	if (type == TRAVERSE_BT_TYPE::LevelOrder)		// 层序遍历（广度优先遍历），借助队列结构实现；
	{
		std::queue<TreeNode<T>*> qt;
		if (nullptr == ptrNode)
		{
			if (!skipNP)
				func(ptrNode);
			return;
		}
		qt.push(ptrNode);

		// BST的循环：
		while (!qt.empty())
		{
			// w1. 取队首节点，对其进行搜索
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

			// w2. 队首节点出队、访问
			qt.pop();
			func(ptrCn);

			// w3. 孩子入队
			qt.push(pa);
			qt.push(pb);
		}
	}
	else		 // 深度优先遍历——先、中、后序取决于是先访问节点（调用函数子func作用于节点）还是先执行递归（搜索节点）
	{
		// 递归终止1——若当前节点为空：
		if (nullptr == ptrNode)
		{
			if (!skipNP)
				func(ptrNode);
			return;
		}

		// 递归终止2——若当前节点为叶子
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

		// 递归递推——对当前节点的左右孩子递归调用本函数：
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


// 遍历BT——非递归方法（to be optimized——当前DFS中不跳过空节点的方法貌似有误）
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

	if (TRAVERSE_BT_TYPE::LevelOrder == type)		// 层序遍历（广度优先遍历），借助队列结构实现；
	{
		std::queue<TreeNode<T>*> qt;
		if (nullptr == ptrNode)
		{
			if (!skipNP)
				func(ptrNode);
			return;
		}
		qt.push(ptrNode);

		// BST的循环：
		while (!qt.empty())
		{
			// w1. 取队首节点，对其进行搜索
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

			// w2. 队首节点出队、访问
			qt.pop();
			func(ptrCn);

			// w3. 孩子入队
			qt.push(pa);
			qt.push(pb);
		}
	}
	else				   // 借助栈stack实现的深度优先遍历
	{
		// 搜索压栈、弹栈访问操作——根据这两种操作的次序可以分为先序、中序、后序三种类型；
		std::stack<TreeNode<T>*> st;
		std::unordered_map<TreeNode<T>*, int> status;		// -1: 未发现,  0: 已发现,  1: 左搜索完成、右搜索未完成,  2: 左右搜索都完成, 3: 已访问;
		st.push(ptrNode);
		status.insert(std::make_pair(ptrNode, 0));				// 节点压栈时即标记为“已发现”状态

		switch (type)
		{
		case TRAVERSE_BT_TYPE::PreOrder:
		{
			// DFS_PRO的循环：
			while (!st.empty())
			{
				// w1. 取栈顶节点作为当前节点；
				ptrCn = st.top();
				auto iter = status.find(ptrCn);						// 当前节点在状态字典中对应的键值对；

				// w2. 搜索当前节点——状态、左右孩子
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

				// w3. 弹栈、访问
				st.pop();
				if (nullptr == ptrCn)
				{
					if (!skipNP)
						func(ptrCn);
					continue;
				}
				func(ptrCn);
				status[ptrCn] = 3;

				// w4. 右搜索、压入栈
				st.push(pb);

				// w5. 左搜索、压入栈；
				st.push(pa);
			}
			break;
		}
		case TRAVERSE_BT_TYPE::InOrder:
		{
			// DFS_IO的循环：
			while (!st.empty())
			{
				// w1. 取栈顶节点作为当前节点；
				ptrCn = st.top();

				// w2. 搜索当前节点——状态、左右孩子
				auto iter = status.find(ptrCn);						// 当前节点在状态字典中对应的键值对；
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

				// w3. 左搜索、压栈的循环，搜索到底；
				while (0 == iter->second)			// 若当前节点未完成左搜索
				{
					// ww1. 当前节点状态修改：
					status[ptrCn] = 1;					// 左搜索已完成；

					if (nullptr == pa)
						break;
					else
					{
						// w2. 左孩子入栈；
						st.push(pa);

						// w3. 当前节点更新
						ptrCn = pa;
						pa = ptrCn->left;
						pb = ptrCn->right;

						// w4. 查找当前节点对应的状态：
						iter = status.find(ptrCn);
						if (iter == status.end())
						{
							auto ret = status.insert(std::make_pair(ptrCn, 0));
							iter = ret.first;
						}
					}
				}

				// w4. 弹栈、访问
				st.pop();
				func(ptrCn);
				status[ptrCn] = 3;

				// w5. 右搜索、压入栈 
				if (nullptr != pb)
					st.push(pb);
			}
			break;
		}
		case TRAVERSE_BT_TYPE::PostOrder:
		{
			// DFS_POO的循环；
			while (!st.empty())
			{
				// w1. 取栈顶节点作为当前节点；
				ptrCn = st.top();
				auto iter = status.find(ptrCn);						// 当前节点在状态字典中对应的键值对；
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

				// w2. 搜索、压栈的循环：
				do
				{
					// wc3.1 左搜索到底
					while (0 == iter->second)			// 若当前节点未完成左搜索
					{
						// ww1. 当前节点状态修改：
						status[ptrCn] = 1;					// 左搜索已完成；

						if (nullptr == pa)
							break;
						else
						{
							// w2. 左孩子入栈；
							st.push(ptrCn->left);

							// w3. 当前节点更新
							ptrCn = pa;
							pa = ptrCn->left;
							pb = ptrCn->right;

							// w4. 查找当前节点对应的状态：
							iter = status.find(ptrCn);
							if (iter == status.end())
							{
								auto ret = status.insert(std::make_pair(ptrCn, 0));
								iter = ret.first;
							}
						}
					}

					// wc3.2 右搜索到底
					while (1 == iter->second)
					{
						// w1. 当前节点状态修改：
						status[ptrCn] = 2;					// 左搜索已完成；

						if (nullptr == pb)
							break;
						else
						{
							// w2. 左孩子入栈；
							st.push(ptrCn->right);

							// w3. 当前节点更新
							ptrCn = pb;
							pa = ptrCn->left;
							pb = ptrCn->right;

							// w4. 查找当前节点对应的状态：
							iter = status.find(ptrCn);
							if (iter == status.end())
							{
								auto ret = status.insert(std::make_pair(ptrCn, 0));
								iter = ret.first;
							}
						}
					}
				} while (iter->second < 2);

				// w3. 访问——只有栈顶元素完成了左右搜索才可以出栈访问；
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


// BT的序列化——基于广度优先遍历（层序遍历），空节点用占位符占位；
template <typename T>
bool serializeBT_levelOrder(std::vector<T>& vecOut, TreeNode<T>* ptrRoot)
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

	// 3. 输出：
	vecOut.insert(vecOut.end(), valList.begin(), valList.end());

	return true;
}


// BT的反序列化——基于广度优先遍历；
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

	// 1. 生成所有节点；
	for (const auto elem : vecVal)
	{
		if (placeholder == elem)
			QS.push(nullptr);
		else
			QS.push(new TreeNode<T>(elem));
	}

	// 2. 链接父子的循环：
	ptrRoot = QS.front();
	pn = ptrRoot;
	QS.pop();
	QF.push(pn);
	while (!QF.empty())
	{
		pn = QF.front();
		QF.pop();

		if (QS.empty())			// 子节点栈空了的话，代表剩下的父节点全都是叶子节点；
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


// BT的序列化——基于先序遍历
template <typename T>
bool serializeBT_preOrder(std::vector<T>& vecOut, TreeNode<T>* ptrRoot)
{
	const T placeholder = std::numeric_limits<T>::max();
	const int maxDepth = ptrRoot->maxDepth();
	const int maxSize = std::pow(2, maxDepth) - 1;					// 深度为maxDepth的满BT的节点数；
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


// BT的反序列化——基于先序遍历；
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

// 翻转BT（BT镜像化）——将所有节点左右孩子颠倒
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



///////////////////////////////////////////////////////////////////////////////////////////////////////  Delete methods

// 删除以ptrNode为根节点的BT
template <typename T>
void destroy(TreeNode<T>*& ptrNode) 
{
	// 递归终止1——若当前节点为空，do nothing;
	if (nullptr == ptrNode)
		return;

	// 递归终止2——若当前节点是叶子，将其delete
	TreeNode<T>*& pa = ptrNode->left;
	TreeNode<T>*& pb = ptrNode->right;
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




/////////////////////////////////////////////////////////////////////////////////////////////////////// BST相关：

// 判断一个BT对象是否是BST
template<typename T>
bool isBST(TreeNode<T>* ptrRoot)
{
	/*
		BST的充要条件：其中序遍历生成的序列是单调递增的；
	*/

	std::vector<T> valVec;
	if (nullptr == ptrRoot)
		return true;

	// 1. 序列容器分配n_max == (2^d - 1)的容量；
	const int maxDepth = ptrRoot->maxDepth();
	valVec.reserve(std::pow(2, maxDepth) - 1);

	// 2. 生成节点值的中序遍历序列
	traverseBT(ptrRoot, [&valVec](TreeNode<T>* np)
		{
			valVec.push_back(np->val);

		}, TRAVERSE_BT_TYPE::InOrder);
	valVec.shrink_to_fit();

	// 3. 判断序列是否是单调递增的；
	for (int i = 0; i < valVec.size() - 1; ++i) 
		if (valVec[i] >= valVec[i + 1])
			return false; 

	return true;
}


// BST中插入新节点
template<typename T>
TreeNode<T>* insert_BST(TreeNode<T>*& pn, const T data) 
{
	/*
		TreeNode<T>* insert_BST(				返回当前BST对象的根节点（是绝对的根节点，往上再没有了）；
			TreeNode<T>*& ptrRoot,			被插入节点的BST的根节点；如果此项为nullptr，则生成一个BST节点对象；
			const T data									插入节点的值；
			)

	*/
	TreeNode<T>* pnNew = nullptr;

	// 递归终止——当前节点指针为空，生成一个新节点
	if (nullptr == pn)
	{
		pn = new TreeNode<T>(data);
		return pn;
	}

	// 递归递推——若data小于当前节点值，则对其左子树插入此节点；
	if (data == pn->val) 
		throw(std::invalid_argument("BST cannot have two nodes with same value."));							// !!!error: BST不可以有相同值的节点，抛出异常；
	else if (data < pn->val)
		insert_BST(pn->left, data);
	else 
		insert_BST(pn->right, data);
}


// 生成一个BST对象，根节点值为headVal，生成的BST可能非常不平衡；
template <typename T>
TreeNode<T>* buildBST(const T headVal, const std::vector<T>& valVec)
{
	TreeNode<T>* ptrRoot = new TreeNode<T>(headVal);
	for (const auto& elem : valVec)
		insert_BST(ptrRoot, elem);
	return ptrRoot;
}


// 在BST中搜索值为data的节点
template <typename T>
TreeNode<T>* searchBST(TreeNode<T>* ptrRoot, const T data) 
{ 	
	// 本质上是二分查找，时间复杂度为O(logn)；BST本身就将元素按大小不断分成两组，只要递归深入下去就自然地实现了二分查找；

	// 递归终止1：	
	if (nullptr == ptrRoot)
		return nullptr;

	// 递归终止2：
	if (data == ptrRoot->val)
		return ptrRoot;
	
	// 递归递推：
	if (data < ptrRoot->val)
		searchBST(ptrRoot->left, data);
	else
		searchBST(ptrRoot->right, data); 
}




/////////////////////////////////////////////////////////////////////////////////////////////////////// 平衡BT相关：
   
// 判断BT是否是平衡的；
template<typename T>
bool isBalanced(TreeNode<T>* ptrRoot)
{
	/*
		每个节点的左右子树的高度差的绝对值不超过1，
			一棵BT是平衡BT，当且仅当其所有子树也都是平衡BT， 
	*/

	// 可以后序遍历此BT， 如果前面的子树是非平衡的，后面的就肯定是非平衡的；
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


// 将BST变平衡（to be completed）
template<typename T>
TreeNode<T>* makeBalanced(TreeNode<T>* ptrRoot, const std::vector<T>& inOrderVec)
{
	// 



}


template<typename T>
TreeNode<T>* makeBalanced(TreeNode<T>* ptrRoot)
{
	/*
		方法一：贪心构造
		思路
			「平衡」要求它是一棵空树或它的左右两个子树的高度差的绝对值不超过 111，
			这很容易让我们产生这样的想法——左右子树的大小越「平均」，这棵树会不会越平衡？
			于是一种贪心策略的雏形就形成了：我们可以通过中序遍历将原来的二叉搜索树转化为一个有序序列，
				然后对这个有序序列递归建树，对于区间 [L,R][L, R][L,R]：
			 
		输入：root = [1,null,2,null,3,null,4,null,null]
		输出：[2,1,3,null,null,null,4]
		解释：这不是唯一的正确答案，[3,1,4,null,2,null,null] 也是一个可行的构造方案。
	*/
	 


	return true;
}




/////////////////////////////////////////////////////////////////////////////////////////////////////// 基于BT的排序算法
/*
	基于BST的排序算法
		直接构建BST排序：

		基于AVL树的排序：

		基于红黑树的排序：

	基于堆的排序算法：

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




////////////////////////////////////////////////////////////////////////////////////////////// 测试函数：
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