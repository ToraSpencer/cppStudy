#include <iostream>
#include <vector>
#include <stack>
#include <queue>
#include <map>
#include <unordered_map>
#include <algorithm>

#include "myDSA.h"


////////////////////////////////////////////////////////////////////////////////////////////// DEBUG 接口
namespace MY_DEBUG
{
	static std::string g_debugPath = "E:/";

	// lambda——打印std::cout支持的类型变量。
	template <typename T>
	static auto disp = [](const T& arg)
	{
		std::cout << arg << ", ";
	};

	static void debugDisp()			// 递归终止
	{						//		递归终止设为无参或者一个参数的情形都可以。
		std::cout << std::endl;
		return;
	}


	template <typename T, typename... Types>
	static void debugDisp(const T& firstArg, const Types&... args)
	{
		std::cout << firstArg << " ";
		debugDisp(args...);
	}


	// 传入函数子或函数指针遍历stl容器
	template<typename T, typename F>
	void traverseSTL(T& con, F f)
	{
		std::for_each(con.begin(), con.end(), f);
		std::cout << std::endl;
	}


	// 反向遍历
	template<typename T, typename F>
	void revTraverseSTL(T& con, F f)
	{
		std::for_each(con.rbegin(), con.rend(), f);
		std::cout << std::endl;
	}
}
using namespace MY_DEBUG;



////////////////////////////////////////////////////////////////////////////////////////////// 数组
namespace ARRAY
{
	// 两数之和
	/*
		给定一个整数数组 nums 和一个整数目标值 target，
			请你在该数组中找出 和为目标值 target  的那 两个 整数，并返回它们的数组下标。
			你可以假设每种输入只会对应一个答案。但是，数组中同一个元素在答案里不能重复出现。
	*/
	std::vector<int> twoSum(const std::vector<int>& nums, const int target)
	{
		/*
			常规思路是使用双重的for循环来遍历输入向量中所有的数对，找出符合要求的那一对；
					时间复杂度为O(n^2)，空间复杂度为O(1)

			借用哈希表的话，可以用空间换时间
					下面的代码展示了时间复杂度为O(n)，空间复杂度为O(n)的方法

		*/
		std::unordered_map<int, int> map;				// 键为nums中的数字，值为其索引；
		for (int i = 0; i < nums.size(); ++i)
		{
			auto iter = map.find(target - nums[i]);
			if (iter != map.end())
				return std::vector<int>{iter->second, i};
			map[nums[i]] = i;
		}
		return std::vector<int>{};
	}


	void test0()
	{
		std::vector<int> retVec = twoSum(std::vector<int>{11, 2, 7, 15}, 9);
		traverseSTL(retVec, disp<int>);

		debugDisp("test0 finished.");
	}

}


////////////////////////////////////////////////////////////////////////////////////////////// 字符串
namespace STRING 
{
	// 回文串判断
	/*
		若在将所有大写字符转换为小写字符、并移除所有非字母数字字符之后，短语正着读和反着读都一样。则可以认为该短语是一个回文串 。
				字母和数字都属于字母数字字符。

		给你一个字符串 s，如果它是 回文串 ，返回 true ；否则，返回 false 。
	示例 ：
		输入: s = "A man, a plan, a canal: Panama"
		输出：true
		解释："amanaplanacanalpanama" 是回文串。
		示例 2：

		输入：s = "race a car"
		输出：false
		解释："raceacar" 不是回文串。
		示例 3：

		输入：s = " "
		输出：true
		解释：在移除非字母数字字符之后，s 是一个空字符串 "" 。
		由于空字符串正着反着读都一样，所以是回文串。
  
	提示：1 <= s.length <= 2 * 10^5
	
	*/
	void test0() 
	{


	}


}


////////////////////////////////////////////////////////////////////////////////////////////// 二叉树
namespace BINARY_TREE
{
	// 二叉树的最大深度：
	/*
		给定一个二叉树 root ，返回其最大深度。
			二叉树的最大深度：从根节点到最远叶子节点的最长路径上的节点数。
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

	
	// 二叉树序列化（转换为1维数组）：
	template <typename T>
	void BT2Array(TreeNode<T>* ptrNode, T* arrayHead, int i, int j, \
		const std::pair<int, int>& size = std::make_pair(0, 0))
	{
		// T为二叉树的根节点，arrayHead是数组的起始地址，ij表示当前节点在数组中的位置
		int ti = 0;
		int tj = 0;						// 如果节点有孩子,其孩子的j坐标为 j±(height-i+1)/2
		int width = size.first;
		int height = size.second;

		if (nullptr != ptrNode)					//如果该位置有节点
		{
			*(arrayHead + i * width + j) = ptrNode->val;			// 向数组该点填入字符
			if (nullptr != ptrNode->left)			// 有左右孩子给对应的连接线,左右孩子的值在下一层递归赋
			{
				//将该点与其左孩子之间的连线全部填上'/'
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

			// 经过循环,ti恰好指到其孩子所在的层
			BT2Array(ptrNode->left, arrayHead, ti, j - (height - i + 1) / 2, std::make_pair(width, height));
			BT2Array(ptrNode->right, arrayHead, ti, j + (height - i + 1) / 2, std::make_pair(width, height));
		}
	}


	// 控制台上打印二叉树
	template <typename T>
	void printBT(TreeNode<T>* ptrNode)
	{ 
		// 1. 动态数组申请空间
		int n = ptrNode->maxDepth();				 // 深度 
		int width = (2 << n) - 3;						 // 2^(n+1)-3；左移1位就相当于乘以2的1次方
		int height = (2 << (n - 1)) - 1;				// 2^n-1 
		T* a = new T[width *height];						
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

		// 释放内存
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

		TreeNode<char>* ptrRoot2 = new TreeNode<char>{'B'};
		ptrRoot2->left = new TreeNode<char>{ 'I' };
		ptrRoot2->right = new TreeNode<char>{ 'N' };
		ptrRoot2->left->left = new TreeNode<char>{ 'A' };
		ptrRoot2->left->right = new TreeNode<char>{ 'R' };
		ptrRoot2->right->left = new TreeNode<char>{ 'Y' };
		printBT(ptrRoot2);

		debugDisp("test1 finished.");

	}

}


namespace SORTING 
{
	// 合并两个有序数组（单调递增）
	bool mergeSequence(std::vector<int>& vec1, const std::vector<int>& vec2)
	{
		int index1 = 0;
		int index2 = 0;
		const int count1 = vec1.size();
		const int count2 = vec2.size();
		std::vector<int> vecOut;
		vecOut.reserve(count1 + count2);

		while (index1 < count1 && index2 < count2)
		{
			if (vec1[index1] <= vec2[index2])
			{
				vecOut.push_back(vec1[index1]);
				index1++;
			}
			else
			{
				vecOut.push_back(vec2[index2]);
				index2++;
			}
		}
		if (count1 == index1)
			vecOut.insert(vecOut.end(), vec2.begin() + index2, vec2.end());
		else
			vecOut.insert(vecOut.end(), vec1.begin() + index1, vec1.end());

		vec1.clear();
		vec1 = std::move(vecOut);

		return true;
	}
	
	  
	void test0() 
	{
		std::vector<int> vec1{ 1, 2, 3, };
		std::vector<int> vec2{ 2, 5, 6 }; 
		mergeSequence(vec1, vec2); 
		
		
		traverseSTL(vec1, disp<int>);
		debugDisp("test0() finished.");
	}

}


namespace STACK 
{
	// practice——有效的括号：
	/*
		给定一个只包括 '('，')'，'{'，'}'，'['，']' 的字符串 s ，判断字符串是否有效。
		有效字符串需满足：
				左括号必须用相同类型的右括号闭合。
				左括号必须以正确的顺序闭合。
				每个右括号都有一个对应的相同类型的左括号。

		示例 ：
				输入：s = "()"
				输出：true
				输入：s = "()[]{}"
				输出：true 
				输入：s = "(]"
				输出：false 

		提示：
				1 <= s.length <= 104
				s 仅由括号 '()[]{}' 组成
	*/
	bool isValidParentheses(std::string s)
	{
		if (s.length() % 2 != 0) 
			return false;					//一但是奇数说明不是有效的括号

		std::map<char, char> wordbook;			//建立哈希表
		wordbook.insert(std::map<char, char>::value_type(')', '('));
		wordbook.insert(std::map<char, char>::value_type(']', '['));
		wordbook.insert(std::map<char, char>::value_type('}', '{'));
		std::stack<char> mystack;				//建立栈
		for (int i = 0; i < s.length(); i++)
		{
			if (s[i] == '[' || s[i] == '{' || s[i] == '(')//匹配到左括号
				mystack.push(s[i]);//放入栈中
			else if (s[i] == ']' || s[i] == '}' || s[i] == ')')//匹配到右括号
			{
				if (mystack.empty()) return false;

				//匹配到右括号，栈中应该存在左括号。否则就是无效的括号
				if (wordbook[s[i]] == mystack.top())		//与栈顶元素进行匹配
				{
					mystack.pop();		//匹配成功删除栈顶元素
					continue;
				}
				else 
					return false;
			}
		}
		if (mystack.empty()) 
			return true;		//有效的括号到最后检测结束栈中应没有元素
		else
			return false;
	}


	void test0() 
	{
		debugDisp("test0() finished.");
	}
		

	// practice——最小栈
	/*
		请你设计一个 最小栈 。它提供 push ，pop ，top 操作，并能在常数时间内检索到最小元素的栈。
		实现 MinStack 类:
				MinStack() 初始化堆栈对象。
				void push(int val) 将元素val推入堆栈。
				void pop() 删除堆栈顶部的元素。
				int top() 获取堆栈顶部的元素。
				int getMin() 获取堆栈中的最小元素。

		示例:
				输入：
						["MinStack","push","push","push","getMin","pop","top","getMin"]
						[[],[-2],[2],[-3],[],[],[],[]]
				输出：
						[null,null,null,null,-3,null,2,-2]
	
	*/
	void test1() 
	{
		debugDisp("test1() finished.");
	}
}


namespace GRAPH 
{
	// practice——找到小镇的法官
	/*
		小镇里有 n 个人，按从 1 到 n 的顺序编号。传言称，这些人中有一个暗地里是小镇法官。
		如果小镇法官真的存在，那么：
				小镇法官不会信任任何人。
				每个人（除了小镇法官）都信任这位小镇法官。
				只有一个人同时满足属性 1 和属性 2 。
				给你一个数组 trust ，其中 trust[i] = [ai, bi] 表示编号为 ai 的人信任编号为 bi 的人。
		如果小镇法官存在并且可以确定他的身份，请返回该法官的编号；否则，返回 -1 。 

		示例 ：
				输入：n = 2, trust = [[1,2]]
				输出：2 
				输入：n = 3, trust = [[1,3],[2,3]]
				输出：3 
				输入：n = 3, trust = [[1,3],[2,3],[3,1]]
				输出：-1
	*/
	int findJudge(int N, const std::vector<std::vector<int>>& trust)
	{
		const int k = N + 1;
		std::vector<bool> trustPeople(k, false);
		std::vector<int> beTrust(k, 0);  //被别人相信
		for (auto& v : trust)
		{
			trustPeople[v[0]] = true;
			beTrust[v[1]]++;
		}
		for (int i = 1; i <= N; ++i)
			if (!trustPeople[i] && beTrust[i] == N - 1)
				return i;
		return -1;
	}


	void test0()
	{
		debugDisp("result == ", findJudge(3, std::vector<std::vector<int>>{ \
				std::vector<int>{1, 3}, std::vector<int>{2, 3} }));

		debugDisp("test0() finished.");
	}

}




int main(int argc, char** argv)
{
	// BINARY_TREE::test0();

	// SORTING::test0();
	
	GRAPH::test0();

	debugDisp("main finished.");

	return 0;
}
