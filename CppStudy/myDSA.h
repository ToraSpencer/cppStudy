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

};




