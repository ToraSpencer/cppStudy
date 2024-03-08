#include "myDSA_stack.h"


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



namespace STACK
{
	// practice������Ч�����ţ�
	/*
		����һ��ֻ���� '('��')'��'{'��'}'��'['��']' ���ַ��� s ���ж��ַ����Ƿ���Ч��
		��Ч�ַ��������㣺
				�����ű�������ͬ���͵������űպϡ�
				�����ű�������ȷ��˳��պϡ�
				ÿ�������Ŷ���һ����Ӧ����ͬ���͵������š�

		ʾ�� ��
				���룺s = "()"
				�����true
				���룺s = "()[]{}"
				�����true
				���룺s = "(]"
				�����false

		��ʾ��
				1 <= s.length <= 104
				s �������� '()[]{}' ���
	*/
	bool checkValidParentheses(const char* str)				// ���ַ����ǺϷ��ģ�����δ��ڵ����ţ�������true��
	{
		const size_t charsCount = std::strlen(str);

		// 1. simple cases:
		if (charsCount == 0)
			return true;
		if (charsCount % 2 == 1)
			return false;

		// 2. �����ֵ䣺
		std::unordered_map<char, char> mapParen;
		mapParen.insert({ ')', '(' });
		mapParen.insert({ ']', '[' });
		mapParen.insert({ '}', '{' });

		// 3. �������ַ�������ǰ��ѹ��ջ���ַ���ջ���ַ�����ԣ������߶�ɾ����
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


	// practice������Сջ
	/*
		�������һ�� ��Сջ �����ṩ push ��pop ��top �����������ڳ���ʱ���ڼ�������СԪ�ص�ջ��
		ʵ�� MinStack ��:
				MinStack() ��ʼ����ջ����
				void push(int val) ��Ԫ��val�����ջ��
				void pop() ɾ����ջ������Ԫ�ء�
				int top() ��ȡ��ջ������Ԫ�ء�
				int getMin() ��ȡ��ջ�е���СԪ�ء�

		ʾ��:
				���룺
						["MinStack","push","push","push","getMin","pop","top","getMin"]
						[[],[-2],[2],[-3],[],[],[],[]]
				�����
						[null,null,null,null,-3,null,2,-2]

	*/
	void test1()
	{
		// ������
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
			debugDisp("ʹ��try-catch��䲶�����쳣���쳣�����ַ�����e.what() == ", e.what());
		}
		  
		debugDisp("test1() finished.");
	}
}

