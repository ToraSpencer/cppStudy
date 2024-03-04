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

};




