#include <iostream>
#include <vector>
#include <list>
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

	// 函数子——打印std::cout支持的类型变量。
	template <typename	T>
	class disp
	{
	public:
		void operator()(const T& arg)
		{
			std::cout << arg << ", ";
		}
	};


	// 函数子——打印std::pair
	template <typename pairType>
	class dispPair
	{
	public:
		void operator()(const pairType& p)
		{
			std::cout << "(" << p.first << ", " << p.second << "), ";
		}
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
	}


	// 反向遍历
	template<typename T, typename F>
	void revTraverseSTL(T& con, F f)
	{
		std::for_each(con.rbegin(), con.rend(), f); 
	}
}
using namespace MY_DEBUG;



////////////////////////////////////////////////////////////////////////////////////////////// 暂时不知如何分类：
namespace TEST_UNKNOWN
{
	// JZOF14: 调整数组顺序使奇数位于偶数前面
	/*
			输入一个整数数组，实现一个函数来调整该数组中数字的顺序，
					使得所有奇数位于数组的前半部分，所有偶数位于数组的后半部分。
	*/
	void test0()
	{
		/*
			    void Reorder（int ＊pData, unsigned int length, bool （＊func）（int））
    {
        if（pData == NULL || length == 0）
            return;

        int ＊pBegin = pData;
        int ＊pEnd = pData + length - 1;

        while（pBegin < pEnd）
        {
            while（pBegin < pEnd && !func（＊pBegin））
                pBegin ++;
            while（pBegin < pEnd && func（＊pEnd））
                pEnd --;

            if（pBegin < pEnd）
            {
                int temp = ＊pBegin;
                ＊pBegin = ＊pEnd;
                ＊pEnd = temp;
            }
        }
    }
    bool isEven（int n）
    {
        return （n & 1） == 0;
    }

		void ReorderOddEven（int ＊pData, unsigned int length）
	{
		Reorder（pData, length, isEven）;
	}
		*/
	}


}



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
		traverseSTL(retVec, disp<int>());

		debugDisp("test0 finished.");
	}


	// JZOF3: 二维数组查找：
	/*
		在一个二维数组中，每一行都按照从左到右递增的顺序排序，
			每一列都按照从上到下递增的顺序排序。
			请完成一个函数，输入这样的一个二维数组和一个整数，判断数组中是否含有该整数。
	*/
	void test1()
	{

	}


	// test2：基于数组的快速排序；
	/*
		基于分而治之（二分）的思想；
		处理过程是自顶向下的——分割的时候就已经对数组操作了；
		时间复杂度
	*/

	// 分割操作：将数组按照基准值pivot分成两段，前段都不大于pivot，后段都大于pivot; 返回和pivot相等的元素索引；
	int partition(std::vector<int>& arr, int startIdx, int endIdx) 
	{
		int pivot = arr[endIdx];						// 选择最后一个元素作为基准值
		int idx1 = startIdx;
		int idx2 = startIdx;

		// 双指针方法——遍历所有元素，将小于基准值的元素交换到前面；
		while (idx2 < endIdx)
		{
			if (arr[idx2] < pivot)
			{
				std::swap(arr[idx1], arr[idx2]);				 
				idx1++;
			}
			idx2++;
		}
		std::swap(arr[idx1], arr[endIdx]);		// 将选定的作为基准值的最后一个元素交换到idx1的位置；此时0~idx1的元素都不大于pivot;

		return idx1;
	}


	// 递归函数：
	void quickSortRec(std::vector<int>& arr, int startIdx, int endIdx)
	{
		// 1. 递归终止——当startIdx == endIdx时，数组中的这一段只有一个元素，什么也不做；

		// 2. 递归递推——二分、递归调用：
		if (startIdx < endIdx) 
		{
			int pivotIdx = partition(arr, startIdx, endIdx);

			quickSortRec(arr, startIdx, pivotIdx - 1);
			quickSortRec(arr, pivotIdx + 1, endIdx);
		}
	}

	// 快速排序主函数
	void quickSort(std::vector<int>& arr)
	{
		int n = arr.size();
		quickSortRec(arr, 0, n - 1);
	}


	void test2() 
	{
		std::vector<int> arr = { -1, -23, -1, -7, 99, -1, 0}; 
		quickSort(arr);

		traverseSTL(arr, disp<int>{});
		debugDisp("\n");
		debugDisp("test2 finished.");
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


	// JZOF4: 字符串中替换空格：
	/*
		请实现一个函数，把字符串中的每个空格替换成"%20"。
			例如输入“We are happy.”，则输出“We%20are%20happy.”。
	*/
	void test1()
	{

	}
}



////////////////////////////////////////////////////////////////////////////////////////////// 排序&查找
/*
	时间复杂度是 O(nlog⁡n)的排序算法：
		归并排序
				适用于链表
		堆排序
				
		快速排序
				最差时间复杂度是O(n^2)
  

*/
namespace SORTING_SEARCHING 
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
	 

	bool mergeSort(const std::vector<int>::iterator& begin, const std::vector<int>::iterator& end)
	{
		const size_t elemCount = std::distance(begin, end);

		// 递归终止——需要排序的序列元素数目不大于2时：
		if (elemCount < 0)
			return false;
		if (elemCount < 2)
			return true;
		if (2 == elemCount)
			if (*begin > *(begin + 1))
				std::swap(*begin, *(begin + 1));

		// 递归递推——需要排序的序列元素数目大于2时，将其二分分别排列后，再整合成单调有序的序列；
		if (elemCount > 2)
		{
			std::vector<int> vec1, vec2;
			std::vector<int>::iterator middle = begin + elemCount / 2;
			mergeSort(begin, middle);
			mergeSort(middle, end);
			vec1.insert(vec1.end(), begin, middle);
			vec2.insert(vec2.end(), middle, end);
			mergeSequence(vec1, vec2);
			auto iter = begin;
			for (size_t i = 0; i < elemCount; ++i)
			{
				*iter = vec1[i];
				iter++;
			}
		}
		 
		return true;
	}


	void test0() 
	{
		std::vector<int> vec1{ 1, 2, 3, };
		std::vector<int> vec2{ 2, 5, 6 }; 
		mergeSequence(vec1, vec2); 
		traverseSTL(vec1, disp<int>());
		debugDisp("\n");

		//
		std::vector<int> numVec{54, 12, 45, -1, -99, 8, 9, 0, 12};
		mergeSort(numVec.begin(), numVec.end());
		traverseSTL(numVec, disp<int>());
		 
		debugDisp("test0() finished.");
	}
 

	// JZOF8: 查找旋转数组中的最小数字
	/*
		把一个数组最开始的若干个元素搬到数组的末尾，我们称之为数组的旋转。
			输入一个递增排序的数组的一个旋转，输出旋转数组的最小元素。
			例如数组{3,4,5,1,2}为{1,2,3,4,5}的一个旋转，该数组的最小值为1。
	*/
	void test1()
	{}
}
 


////////////////////////////////////////////////////////////////////////////////////////////// 递归
namespace RECURSION
{
	// 递归函数——尾递归求阶乘：
	int factorial(const int num) 
	{
		int result = 0;

		// 递归终止1：
		if (num < 0)
			return -std::numeric_limits<int>::max(); 

		// 递归终止2：
		if (1 == num || 0 == num)
			return 1;

		// 递归递推：
		return num * factorial(num - 1); 
	}

	void test0() 
	{
		debugDisp("result == ", factorial(-4));

		debugDisp("test0 finished.");
	}


	// JZOF9: 求斐波那契数列
	/*
		写一个函数，输入n，求斐波那契（Fibonacci）数列的第n项。
			斐波那契数列的定义如下
				f(0) ==0, f(1) == 1, 
				n > 1时：f(n) == f(n-1) + f(n-2)
	*/
	unsigned long long fibonacci(const unsigned n)
	{
		/*
			直接递归的话，n很大时会生成海量的递归实例，时间复杂度会达到指数级？？？
			下面给出时间复杂度为O(n)的方法：
		*/
		if(0 == n)
			return 0;
		if(1 == n)
			return 1;

		// 要点1: 输出数据应该为上限很大的类型，防止上溢出；
		unsigned long long a = 0;
		unsigned long long b = 1;
		unsigned long long result = 0;

		// 要点2：不需要空间复杂度为O(n)，只需要记录前两个结果就行了；
		for(int i = 2; i <= n; ++i)
		{
			result = a + b;
			a = b;
			b = result;
		}

		return result; 
	}


	void test1()
	{
		for(int i = 0; i <= 10; ++i)
		{
			char str[256];
			sprintf(str, "fibonacci(%d) == ", i);
			debugDisp(str, fibonacci(i));
		} 

		debugDisp("test1 finished.");
	}


	// JZOF11: 求数值的整数次方：
	/*
		实现函数 double Power（double base, int exponent），
			求 base 的exponent次方。不得使用库函数，同时不需要考虑大数问题。
	*/
	double myPower(const double base, const int exponent)
	{
		/*
			直接递归的话，时间复杂度是O(n);
			如果使用二分的思想的话，可以实现O(logn)的时间复杂度：
				若n为偶数：f(n) = f(n/2) * f(n/2);
				若n为级数：f(n) = base * f((n-1)/2) *f((n-2)/2)
		*/
		double result = 0;
		const bool notNeg = (exponent >= 0);
		const int N = notNeg ? exponent: (-exponent);
		if(0 == N % 2)
		{
						
		}
		else
		{
			
		}

		return result;
	}
	void test2()
	{

	}


	// JZOF12: 打印1到最大的n位数
	/*
		 输入数字n，按顺序打印出从1最大的n位十进制数。
		 比如输入3，则打印出1、2、3一直到最大的3位数即999。

		 答案：
			 void Print1ToMaxOfNDigits （int n）
			{
				if（n <= 0）
					return;

				char＊ number = new char[n + 1];
				number[n] = '\0';
				for（int i = 0; i < 10; ++i）
				{
					number[0] = i + '0';
					Print1ToMaxOfNDigitsRecursively（number, n, 0）;
				}
				delete[] number;
			}

			void Print1ToMaxOfNDigitsRecursively（char＊ number, int length, int
			index）
			{
				if（index == length - 1）
				{
					PrintNumber（number）;
					return;
				}

				for（int i = 0; i < 10; ++i）
				{
					number[index + 1] = i + '0';
					Print1ToMaxOfNDigitsRecursively（number, length, index + 1）;
				}
			}
	*/
	void test3() {}
}



////////////////////////////////////////////////////////////////////////////////////////////// 贪婪算法、动态规划、蛮力算法
namespace GREEDY_DYNAMIC_BRUTAL
{
	// 递归函数：求解所有可能的组合（基于回溯法）；可用于蛮力算法
	void generateCombinations(std::vector<std::vector<int>>& combs, \
		std::list<int>& tmpList, const int n, const int m, const int num)
	{
		/*
			void generateCombinations(
					std::vector<std::vector<int>>& combs,				输出的向量，每个元素为一个组合向量；
					std::list<int>& tmpList,										辅助容器变量；
					const int n,															生成组合的元素为0, 1, 2, ...(n-1)一共n个整数；
					const int m,															组合中的元素数
					const int num														当前组合中尝试添加的元素
					)

		*/

		// 递归终止：若当前的链表tmpList中已经添加的元素达到m个
		if (tmpList.size() == m)
		{
			std::vector<int> tmpVec;
			tmpVec.insert(tmpVec.end(), tmpList.begin(), tmpList.end());
			combs.push_back(tmpVec);
			return;
		}

		// 递归递推：从当前索引开始，尝试添加数到组合中
		for (int i = num; i < n; ++i)
		{
			const int numNext = i + 1;
			tmpList.push_back(i);
			generateCombinations(combs, tmpList, n, m, numNext);
			tmpList.pop_back();															// 回溯；					
		}
	}


	// 背包问题：
	void test0()
	{
		/*
			背包问题：
					要往背包中装入一些物品，每个物品有各自的价值和重量，背包能装的最大重量优先，求如何使得装入的物品价值总量最大。
					01背包问题——若物品只能一整个放入，不能拆分，则是01背包问题；
					完全背包问题——若物品可以被选择无限次，则是完全背包问题；

			计算每个物品的性价比，从高到低排序，以此次序取物品；
			间复杂度为O(nlogn)，空间复杂度为 O(1)；其中 n 为物品数量
			贪心算法具有快速、简单的特点，但不保证得到最优解。

		*/


		// greedy algorithm——一定是全局最优解；时间复杂度O(2^n)
		auto knapsack_greedy = [](std::vector<int>& selectedIdxes, \
			const std::vector<int>& itemWeights, const std::vector<int>& itemValues, \
			const int capacity, const bool isKnapsack01 = true, const bool isKnapsackCom = false) ->std::pair<int, int>
		{
			int totalVal = 0;
			int totalWeights = 0;
			const int itemsCount = static_cast<int>(itemWeights.size());
			selectedIdxes.clear();

			// (to be completed)暂时只考虑非完全01背包问题；
			if (isKnapsack01 && !isKnapsackCom)
			{
				// 1. 计算所有物品的性价比：
				std::map<double, int> ppRatio;			// key是性价比，value是物品索引；
				for (int i = 0; i < itemsCount; ++i)
				{
					double pp = static_cast<double>(itemValues[i]) / static_cast<double>(itemWeights[i]);
					ppRatio.insert({pp, i});
				}				

				// 2. 按性价比由高到低的次序放入物品：
				for (auto iter = ppRatio.rbegin(); iter != ppRatio.rend(); ++iter)
				{
					const int index = iter->second;
					totalWeights += itemWeights[index];
					if (totalWeights > capacity)
					{
						totalWeights -= itemWeights[index];
						break;
					}
					totalVal += itemValues[index];
					selectedIdxes.push_back(index);
				}
			}

			return { totalVal, totalWeights};
		};

		// dynamic programming:——时间复杂度和空间复杂度都为O(n*m)，m为背包容量；
		auto knapsack_dynamic = [](std::vector<int>& selectedIdxes, \
			const std::vector<int>& itemWeights, const std::vector<int>& itemValues, \
			const int capacity, const bool isKnapsack01 = true, const bool isKnapsackCom = false)->std::pair<int, int>
		{
			int totalVal = 0;
			int totalWeights = 0;
			const int itemsCount = static_cast<int>(itemWeights.size());
			std::vector<std::vector<int>> KDtable;							// 索引为[i][k]的元素表示背包容量为k时，尝试放入索引为0~i的物品所能得到的最大价值；
			std::vector<std::vector<std::list<int>>> KDcombs;		// 存储KDtable每一个元素对应的物品索引组合；
			selectedIdxes.clear();
			KDtable.resize(itemsCount);
			KDcombs.resize(itemsCount);
			for (auto& vec : KDtable)
				vec.resize(capacity + 1, 0);
			for (auto& vec : KDcombs)
				vec.resize(capacity + 1);

			// (to be completed)暂时只考虑非完全01背包问题；
			if (isKnapsack01 && !isKnapsackCom)
			{
				// 1. 生成KDtable第一行——尝试放入第一个物品
				for (int k = 0; k <= capacity; ++k)
				{
					if (itemWeights[0] <= k)
					{
						KDtable[0][k] = itemValues[0];
						KDcombs[0][k].push_back(0);
					}
				}

				// 2. 填充KDtable其他行——先求解的是子问题，后面问题的解可以由之前得到的子问题的解组合而来；
				for (int i = 1; i < itemsCount; i++)					// 各行为不同可选择的物品
				{		
					for (int k = 1; k <= capacity; k++)				// 各列为不同规格的背包；
					{
						// 尝试在背包容量为k时，放入索引为i的物品：
						if (itemWeights[i] > k)
						{
							// a. 物品重量大于背包容量，最大价值和上方的值相同； 
							KDtable[i][k] = KDtable[i - 1][k];				
							KDcombs[i][k] = KDcombs[i - 1][k];
						}
						else 
						{
							// b. 物品可以装入背包，比较装入该物品和不装入该物品的最大价值，取较大值
							int val1 = KDtable[i - 1][k];									// 候选者1：背包规格相同，可选物品除去当前物品以外情形下的解；
							int val2 = KDtable[i - 1][k - itemWeights[i]] + itemValues[i];		// 候选者2：放入当前物品背包恰好放满的最优解； 	
							if (val1 > val2)			// 当前最优解必然在两个候选者之间；
							{
								KDtable[i][k] = KDtable[i - 1][k];
								KDcombs[i][k] = KDcombs[i - 1][k];
							}
							else
							{
								KDtable[i][k] = KDtable[i - 1][k - itemWeights[i]] + itemValues[i];
								KDcombs[i][k] = KDcombs[i - 1][k - itemWeights[i]];
								KDcombs[i][k].push_back(i);
							}
						}
					}
				}
				totalVal = KDtable[itemsCount - 1][capacity];
				selectedIdxes.insert(selectedIdxes.end(),\
					KDcombs[itemsCount - 1][capacity].begin(), KDcombs[itemsCount - 1][capacity].end());
				for (const auto& index : selectedIdxes)
					totalWeights += itemWeights[index];
			}
			return { totalVal, totalWeights };
		};

		// brutal:
		auto knapsack_brutal = [](std::vector<int>& selectedIdxes, \
			const std::vector<int>& itemWeights, const std::vector<int>& itemValues, \
			const int capacity, const bool isKnapsack01 = true, const bool isKnapsackCom = false)->std::pair<int, int>
		{
			int totalVal = 0;
			int totalWeights = 0;
			int maxTotalVal = 0;
			int totalWeightsRet = 0;
			const int itemsCount = static_cast<int>(itemWeights.size());
			selectedIdxes.clear();

			// (to be completed)暂时只考虑非完全01背包问题；
			if (isKnapsack01 && !isKnapsackCom)
			{
				for (int selectedCount = 1; selectedCount <= itemsCount; ++selectedCount) 
				{
					// if1. 获取当前取物品数selectedCount所对应的所有组合：
					std::vector<std::vector<int>> combs;
					std::list<int> tmpList;
					generateCombinations(combs, tmpList, itemsCount, selectedCount, 0);

					// if2. 遍历所有组合，求最大价值：
					for (const auto& vec : combs)
					{
						// iff1. 求当前组合对应的总价值、总重量；
						totalVal = 0;
						totalWeights = 0;
						traverseSTL(vec, [&totalVal, &totalWeights, &itemValues, &itemWeights](const int index) 
							{
								totalVal += itemValues[index];
								totalWeights += itemWeights[index];
							});

						// iff2. 若总重量超标则跳过
						if (totalWeights > capacity)		
							continue;

						// iff3. 更新总价值最大值及其对应组合；
						if (totalVal > maxTotalVal)
						{
							maxTotalVal = totalVal;
							totalWeightsRet = totalWeights;
							selectedIdxes = vec;
						}
					}
				}
			}

			return { maxTotalVal, totalWeightsRet };
		};

		// 0.
		const int capacity = 10;
		std::vector<int> itemWeights{ 3, 2, 1, 5 };
		std::vector<int> itemValues{ 200, 150, 80, 160 };
		std::pair<int, int> retPair;

		// 1. greedy:
		std::vector<int> selectedIdxes;
		retPair = knapsack_greedy(selectedIdxes, itemWeights, itemValues, capacity, true, false);
		debugDisp("knapsack_greedy: totalVal == ", retPair.first, ", totalWeights == ", retPair.second);		
		debugDisp("selectedIdxes: ");
		traverseSTL(selectedIdxes, disp<int>());
		debugDisp("\n");

		// 2. dynamic:
		selectedIdxes.clear();
		retPair = knapsack_dynamic(selectedIdxes, itemWeights, itemValues, capacity, true, false);
		debugDisp("knapsack_dynamic: totalVal == ", retPair.first, ", totalWeights == ", retPair.second);
		debugDisp("selectedIdxes: ");
		traverseSTL(selectedIdxes, disp<int>());
		debugDisp("\n");


		// 3. brutal:
		selectedIdxes.clear();
		retPair = knapsack_brutal(selectedIdxes, itemWeights, itemValues, capacity, true, false);
		debugDisp("knapsack_brutal: totalVal == ", retPair.first, ", totalWeights == ", retPair.second);
		debugDisp("selectedIdxes: ");
		traverseSTL(selectedIdxes, disp<int>());
		debugDisp("\n");

		debugDisp("test0 finished.");
	}


	// 最长公共子串：
	void test1() 
	{
		std::string str1 = "abdcbab";
		std::string str2 = "bdcbabb";				// 最长公共子串是bdcbab



		debugDisp("test1 finished.");
	}
	 

}


////////////////////////////////////////////////////////////////////////////////////////////// 回溯法
namespace BACKTRACKING 
{
	// 生成括号
	/*
		数字 n 代表生成括号的对数，请你设计一个函数，用于能够生成所有可能的并且 有效的 括号组合。
		vector<string> generateParenthesis(int n) 

		输入：n = 3
		输出：["((()))","(()())","(())()","()(())","()()()"] 

		输入：n = 1
		输出：["()"]
	
	*/
	void test0() {}

	 
	// 组合求和问题(Combination Sum)
	int combinationSum(std::list<int>& combList, const int target ) 
	{

		return 0;
	}

	using namespace std;


	void CombinationSum(vector<int>& candidates, \
		int target, vector<int>& combination, vector<vector<int>>& result, \
		const int startIdx) 
	{
		// 如果 target 为 0，说明找到了一组组合
		if (target == 0)
		{
			result.push_back(combination);
			return;
		}

		// 递归递推——当前组合序列最后一个数字为num，递归

		// 递归终止1——若当前组合序列和大于目标和，则


		// 从 start 开始遍历 candidates 数组
		for (int i = startIdx; i < candidates.size(); i++)
		{
			// 如果当前候选数字大于 target，结束本次循环
			if (candidates[i] > target)
				continue;

			// 避免重复的数字
			if (i > startIdx && candidates[i] == candidates[i - 1])
				continue;

			combination.push_back(candidates[i]);			// 将当前候选数字加入组合 
			CombinationSum(candidates, target - candidates[i], combination, result, i + 1);	// 从当前位置的下一个位置开始寻找下一个组合
			combination.pop_back();				// 回溯，将上一步加入的数字移出组合
		}
	} 


	void test1() 
	{
		// 给定一个数组和一个目标数，从数组中选取若干个数字使它们的和等于目标数，找出所有可能的组合。
		
		// 0.
		std::vector<int> candidates = { 2, 3, 6, 7, 11, 24, 23, 1, 10, -1, -2, -3 };
		std::vector<std::vector<int>> results;
		const int target = 24;

		// 1. 
		vector<int> combination;
		std::sort(candidates.begin(), candidates.end());
		CombinationSum(candidates, target, combination, results, 0); 
		for (const auto& vec : results)
		{
			traverseSTL(vec, disp<int>());
			std::cout << std::endl;
		}

		debugDisp("test1 finished.");
	}


	// 
}



namespace TMP_QUEENS
{
	using namespace std;

	// 检查在 (row, col) 位置放置皇后是否合法
	bool isSafe(vector<vector<int>>& board, int row, int col) {
		// 检查列是否安全
		for (int i = 0; i < row; i++) {
			if (board[i][col] == 1)
				return false;
		}

		// 检查左上到右下对角线是否安全
		for (int i = row, j = col; i >= 0 && j >= 0; i--, j--) {
			if (board[i][j] == 1)
				return false;
		}

		// 检查右上到左下对角线是否安全
		for (int i = row, j = col; i >= 0 && j < board.size(); i--, j++) {
			if (board[i][j] == 1)
				return false;
		}

		return true;
	}

	// 解决八皇后问题
	bool solveNQueens(vector<vector<int>>& board, int row) {
		// 如果所有行都已经放置了皇后，则返回 true
		if (row == board.size())
			return true;

		for (int col = 0; col < board.size(); col++)
		{
			// 检查当前位置是否安全
			if (isSafe(board, row, col))
			{

				// 放置皇后
				board[row][col] = 1;

				// 递归尝试下一行
				if (solveNQueens(board, row + 1))
					return true;

				// ！！！如果不能放置皇后，则回溯
				board[row][col] = 0;
			}
		}

		// 如果在该行的任何位置都不能放置皇后，则返回 false
		return false;
	}

	// 打印棋盘
	void printBoard(vector<vector<int>>& board)
	{
		for (int i = 0; i < board.size(); i++)
		{
			for (int j = 0; j < board.size(); j++)
			{
				cout << board[i][j] << " ";
			}
			cout << endl;
		}
	}


	int testQueens()
	{
		int n = 8; // 棋盘大小
		vector<vector<int>> board(n, vector<int>(n, 0)); // 初始化棋盘

		// 解决八皇后问题
		if (solveNQueens(board, 0))
		{
			cout << "Solution found:\n";
			printBoard(board);
		}
		else
			cout << "No solution exists!\n";


		return 0;
	}

}

 

 

namespace TEST_MY_IO 
{
	void test0() 
	{
		triMeshF mesh;
		bool ret = readOBJ(mesh, "./myData/roundSurf.obj");
		writeOBJ("E:/versIn.obj", mesh);

		// 打印边：
		std::vector<triangleI> tris0(10);
		std::vector<edgeI> edges0;
		for (size_t i = 0; i < 10; ++i)
			tris0[i] = mesh.triangles[i];
		tris2edges(edges0, tris0);
		writeOBJ("E:/edges0.obj", mesh.vertices, edges0);
		

		debugDisp("test0 finished.");
	}
	 
}

 

int main(int argc, char** argv)
{
	// RECURSION::test1(); 

	// TREE::test7();

	// TEST_MY_IO::test0();

	// STACK::test2();

	LIST::test0();
	ARRAY::test2();

	// GRAPH::test5();

	// GREEDY_DYNAMIC_BRUTAL::test0();

	debugDisp("main finished.");


	return 0;
}
