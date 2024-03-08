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



////////////////////////////////////////////////////////////////////////////////////////////// 排序
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




namespace GRAPH 
{
	// practice——找到小镇的法官
	/*
		小镇里有 n 个人，按从 1 到 n 的顺序编号。传言称，这些人中有一个暗地里是小镇法官。
		如果小镇法官真的存在，那么：
				1. 小镇法官不会信任任何人。
				2. 每个人（除了小镇法官）都信任这位小镇法官。
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
		/*
			trust中的数对相当于graph中的有向边；
			问题等价于：
					判断n个节点的有向图中是否有某个节点同时满足：
							1. 入度为(n - 1)；
							2. 出度为0；
		*/
		const int k = N + 1;
		std::vector<bool> trustPeople(k, false);
		std::vector<int> beTrust(k, 0);									 // 被别人相信
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
	// TREE::test1();

	// SORTING::test0();
	
	// GRAPH::test0();

	STACK::test1();

	debugDisp("main finished.");

	return 0;
}
