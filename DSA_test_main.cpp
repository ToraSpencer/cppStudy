#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>


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


// ����
namespace ARRAY 
{
	// ����֮��
	/*
		����һ���������� nums ��һ������Ŀ��ֵ target��
			�����ڸ��������ҳ� ��ΪĿ��ֵ target  ���� ���� ���������������ǵ������±ꡣ
			����Լ���ÿ������ֻ���Ӧһ���𰸡����ǣ�������ͬһ��Ԫ���ڴ��ﲻ���ظ����֡�
	*/
	std::vector<int> twoSum(const std::vector<int>& nums, const int target)
	{
		/*
			����˼·��ʹ��˫�ص�forѭ���������������������е����ԣ��ҳ�����Ҫ�����һ�ԣ�
					ʱ�临�Ӷ�ΪO(n^2)���ռ临�Ӷ�ΪO(1)

			���ù�ϣ��Ļ��������ÿռ任ʱ��
					����Ĵ���չʾ��ʱ�临�Ӷ�ΪO(n)���ռ临�Ӷ�ΪO(n)�ķ���

		*/
		std::unordered_map<int, int> map;				// ��Ϊnums�е����֣�ֵΪ��������
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


// ������
namespace BINARY_TREE 
{
	struct TreeNode 
	{
		int val;
		TreeNode *left;
		TreeNode *right;
		TreeNode() : val(0), left(nullptr), right(nullptr) {}
		TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
		TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
	};
 

	// �������������ȣ�
	/*
		����һ�������� root �������������ȡ�
			�������������ȣ��Ӹ��ڵ㵽��ԶҶ�ӽڵ���·���ϵĽڵ�����
	*/
	int maxDepth(TreeNode* root)
	{

	}


	void test0() 
	{

	}

}
  


int main(int argc, char** argv) 
{
	test0();

	debugDisp("main finished.");

	return 0;
}
