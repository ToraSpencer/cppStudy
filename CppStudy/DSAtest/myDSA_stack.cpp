#include "myDSA_stack.h"


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
	bool checkValidParentheses(const char* str)				// 若字符串是合法的（不含未封口的括号），返回true；
	{
		const size_t charsCount = std::strlen(str);

		// 1. simple cases:
		if (charsCount == 0)
			return true;
		if (charsCount % 2 == 1)
			return false;

		// 2. 生成字典：
		std::unordered_map<char, char> mapParen;
		mapParen.insert({ ')', '(' });
		mapParen.insert({ ']', '[' });
		mapParen.insert({ '}', '{' });

		// 3. 逐个检查字符：若当前待压入栈的字符和栈顶字符可配对，则将两者都删除；
		std::stack<char> stack1;
		for (size_t i = 0; i < charsCount; ++i)
		{
			if (!stack1.empty())
			{
				auto iter = mapParen.find(str[i]);
				if (iter->second == stack1.top())
				{
					stack1.pop();
					continue;
				}
			}
			stack1.push(str[i]);
		}

		return stack1.empty();
	}


	void test0()
	{ 
		debugDisp("checkValidParentheses(\"\") == ", checkValidParentheses(""));
		debugDisp("checkValidParentheses(\"()[] {}\") == ", checkValidParentheses("()[]{}"));
		debugDisp("checkValidParentheses(\"()[}\") == ", checkValidParentheses("()[}"));

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
		// 解析：
		/*
			 
		*/
		MinStack<int> s1;
		s1.push(-2);
		s1.push(2);
		s1.push(-3);
		debugDisp("s1.getMin() == ", s1.getMin());
		s1.pop();
		debugDisp("s1.top() == ", s1.top());
		debugDisp("s1.getMin() == ", s1.getMin());

		s1.push(2);
		s1.push(5);
		s1.push(-99);
		debugDisp("s1.getMin() == ", s1.getMin());
		debugDisp("s1.pop() == ", s1.pop());
		debugDisp("s1.pop() == ", s1.pop());
		debugDisp("s1.pop() == ", s1.pop());
		debugDisp("s1.pop() == ", s1.pop());
		debugDisp("s1.pop() == ", s1.pop());
		try
		{
			s1.pop();
		}
		catch (const std::exception& e)
		{
			debugDisp("使用try-catch语句捕获到了异常，异常解释字符串：e.what() == ", e.what());
		}
		  
		debugDisp("test1() finished.");
	}
}

