#include <stdlib.h>
#include <cstdio>
#include <iostream>
#include <cstdio>
using namespace std;



/*
**	general note:
**		1） testX()函数都应该声明为static函数，这样只在其所在文件内有效。若在全项目内都有效的话，
**			 不同源文件里都定义了相同的test0,test1...会出现duplicate symbold的错误。
**
**
**
*/


/***************************************************************************
***************************************************************************/
// 全局变量、类型定义
void(*pfun[100])(void) = {NULL};
int inputTag;							// 菜单界面中判断输入是否有效的标识符。
int inputNum;							// 菜单界面中用户输入的整数
int interfaceLevel;						// 当前菜单界面的层级，主菜单是一级。




/***************************************************************************
***************************************************************************/
// extern变量



/***************************************************************************
***************************************************************************/
// 函数声明



/***************************************************************************
***************************************************************************/
// extern函数
extern void reset_pfun(void);
extern void traverse_pfun(void);

extern void set_fun_dataType_string(void);
extern void set_fun_dataType_reference(void);
extern void set_fun_STL_iterator(void);
extern void set_fun_UP_assert(void);
extern void set_fun_function_vararg(void);
extern void set_fun_stdlib_regex(void);
extern void set_fun_stdlib_numeric_lib(void);
extern void set_fun_syntax_specialOperator(void);
extern void set_fun_dataType_EUS(void);
extern void set_fun_syntax_keyword(void);
extern void set_fun_syntax_overloaded_operator(void);
extern void set_fun_OOP_class_template(void);
extern void set_fun_function_function_template(void);
extern void set_fun_syntax_type_conversion(void);
extern void set_fun_syntax_expression(void);
extern void set_fun_syntax_statement(void);
extern void set_fun_stdlib_type_support_lib(void);
extern void set_fun_stdlib_numeric_lib(void);
extern void set_fun_stdlib_IO_lib(void);
extern void set_fun_stdlib_thread_support_lib(void);
extern void set_fun_STL_algorithm_lib(void);
extern void set_fun_STL_linear_container(void);
extern void set_fun_STL_set(void);
extern void set_fun_STL_adapter(void);
extern void set_fun_STL_list(void);
extern void set_fun_STL_map(void);
extern void set_fun_OOP_class_object(void);
extern void set_fun_OOP_function_object(void);
extern void set_fun_OOP_polymorphism(void);
extern void set_fun_function_inline(void);
extern void set_fun_function_basic(void);
extern void set_fun_UP_preprocessing(void);
extern void set_fun_UP_memory_management(void);
extern void set_fun_dataType_function_pointer(void);
extern void set_fun_dataType_built_in_types(void);
extern void set_fun_dataType_pointer(void);
extern void set_fun_dataType_array(void);
extern void set_fun_exception_basic(void);
extern void set_fun_exception_std_exception(void);




extern void start_dataType_string(void);
extern void start_dataType_reference(void);
extern void start_STL_iterator(void);
extern void start_UP_assert(void);
extern void start_function_vararg(void);
extern void start_stdlib_regex(void);
extern void start_stdlib_numeric_lib(void);
extern void start_syntax_specialOperator(void);
extern void start_dataType_EUS(void);
extern void start_syntax_keyword(void);
extern void start_syntax_overloaded_operator(void);
extern void start_OOP_class_template(void);
extern void start_function_function_template(void);
extern void start_syntax_statement(void);
extern void start_syntax_type_conversion(void);
extern void start_syntax_expression(void);
extern void start_stdlib_numeric_lib(void);
extern void start_stdlib_type_support_lib(void);
extern void start_stdlib_IO_lib(void);
extern void start_stdlib_thread_support_lib(void);
extern void start_STL_algorithm_lib(void);
extern void start_STL_linear_container(void);
extern void start_STL_set(void);
extern void start_STL_adapter(void);
extern void start_STL_list(void);
extern void start_STL_map(void);
extern void start_OOP_class_object(void);
extern void start_OOP_function_object(void);
extern void start_OOP_polymorphism(void);
extern void start_function_inline(void);
extern void start_function_basic(void);
extern void start_UP_preprocessing(void);
extern void start_UP_memory_management(void);
extern void start_dataType_function_pointer(void);
extern void start_dataType_built_in_types(void);
extern void start_dataType_pointer(void);
extern void start_dataType_array(void);
extern void start_exception_basic(void);
extern void start_exception_std_exception(void);





/***************************************************************************
***************************************************************************/
// 函数定义
int main(int argc, char** argv)
{
	inputNum = 99;
	inputTag = 0;
	interfaceLevel = 1;


	reset_pfun();

	// 主界面循环——选择章节
	while (1 == interfaceLevel)
	{
		cout << "\n\n\n\n" << endl;
		cout << "**************************MAIN MENU**********************" << endl;
		cout << "Please input a number to choose a function setting plan:" << endl;
		cout << "1. 数据类型" << endl;
		cout << "2. C++ 语法" << endl;
		cout << "3. OOP" << endl;
		cout << "4. C++ 标准库" << endl;
		cout << "5. STL" << endl;
		cout << "6. 底层原理" << endl;
		cout << "7. 函数" << endl;
		cout << "8. 异常处理" << endl;
		cout << "9. 暂时不知道如何分类的内容" << endl;
		cout << "-1. Quit" << endl;


		inputTag = scanf("%d", &inputNum);


		// 若输入值不是整数，重新输入。
		if (0 == inputTag)
		{
			cout << "Invalid input. Please input again:" << endl;
			setbuf(stdin, NULL);			// stdin输入流由默认缓冲区转为无缓冲区，这样就清空了缓冲区中的内容。
											// 不要用fflush来清空缓存区，该函数很多编译器支持得不好。
			continue;
		}


		// 对主界面输入值的响应：
		switch (inputNum)
		{
		case -1:							// 退出程序
		{
			interfaceLevel = 0;
			break;
		}

		case 1:								// 1. data type章节。
		{
			// 界面层级符置为2，进入二级界面：
			interfaceLevel = 2;
			while (2 == interfaceLevel)
			{
				cout << "\n\n\n\n" << endl;
				cout << "**************************DATA TYPE MENU**********************" << endl;
				cout << "Please input a number to choose a function setting plan:" << endl;
				cout << "-1. Back to the previous interface" << endl;
				cout << "0. dataType_内置类型" << endl;
				cout << "1. dataType_指针、智能指针" << endl;
				cout << "2. dataType_函数指针" << endl;
				cout << "3. dataType_数组" << endl;
				cout << "4. dataType_枚举、共用体、结构体" << endl;
				cout << "5. dataType_引用" << endl;
				cout << "6. dataType_c风格字符串、string" << endl;

				inputTag = scanf("%d", &inputNum);

				// 若输入值不是整数，重新输入。
				if (0 == inputTag)
				{
					cout << "Invalid input. Please input again:" << endl;
					setbuf(stdin, NULL);			// stdin输入流由默认缓冲区转为无缓冲区，这样就清空了缓冲区中的内容。
													// 不要用fflush来清空缓存区，该函数很多编译器支持得不好。
					continue;
				}

				// 对二级界面输入值的响应：
				switch (inputNum)
				{
				case -1:
					interfaceLevel = 1;
					break;

				case 0:
					reset_pfun();
					set_fun_dataType_pointer();
					start_dataType_pointer();
					break;

				case 1:
					reset_pfun();
					set_fun_dataType_pointer();
					start_dataType_pointer();
					break;
				
				case 2:
					reset_pfun();
					set_fun_dataType_function_pointer();
					start_dataType_function_pointer();
					break;

				case 3:
					reset_pfun();
					set_fun_dataType_array();
					start_dataType_array();
					break;

				case 4:
					reset_pfun();
					set_fun_dataType_EUS();
					start_dataType_EUS();

				case 5:
					reset_pfun();
					set_fun_dataType_reference();
					start_dataType_reference();

				case 6:
					reset_pfun();
					set_fun_dataType_string();
					start_dataType_string();

				default:
					cout << "Invalid input. Please input again:" << endl;
					break;
				}

			}
			break;
		}

		case 2:								// 2. C++ syntax章节
		{
			// 界面层级符置为2，进入二级界面：
			interfaceLevel = 2;
			while (2 == interfaceLevel)
			{
				cout << "\n\n\n\n" << endl;
				cout << "**************************C++ SYNTAX MENU**********************" << endl;
				cout << "Please input a number to choose a function setting plan:" << endl;
				cout << "-1. Back to the previous interface" << endl;
				cout << "0. syntax_statement" << endl;
				cout << "1. syntax_keyword" << endl;
				cout << "2. syntax_overloaded_operator" << endl;
				cout << "3. syntax_类型转换" << endl;
				cout << "4. syntax_表达式" << endl;
				cout << "5. syntax_几个特殊的运算符" << endl;

				inputTag = scanf("%d", &inputNum);

				// 若输入值不是整数，重新输入。
				if (0 == inputTag)
				{
					cout << "Invalid input. Please input again:" << endl;
					setbuf(stdin, NULL);			// stdin输入流由默认缓冲区转为无缓冲区，这样就清空了缓冲区中的内容。
													// 不要用fflush来清空缓存区，该函数很多编译器支持得不好。
					continue;
				}

				// 对二级界面输入值的响应：
				switch (inputNum)
				{
				case -1:
					interfaceLevel = 1;
					break;

				case 0:
					reset_pfun();
					set_fun_syntax_statement();
					start_syntax_statement();
					break;

				case 1:
					reset_pfun();
					set_fun_syntax_keyword();
					start_syntax_keyword();
					break;

				case 2:
					reset_pfun();
					set_fun_syntax_overloaded_operator();
					start_syntax_overloaded_operator();
					break;
				case 3:
					reset_pfun();
					set_fun_syntax_type_conversion();
					start_syntax_type_conversion();
					break;

				case 4:
					reset_pfun();
					set_fun_syntax_expression();
					start_syntax_expression();
					break;

				case 5:
					reset_pfun();
					set_fun_syntax_specialOperator();
					start_syntax_specialOperator();

				default:
					cout << "Invalid input. Please input again:" << endl;
					break;
				}

			}
			break;
		}

		case 3:								// 3. OOP章节
		{
			// 界面层级符置为2，进入二级界面：
			interfaceLevel = 2;
			while (2 == interfaceLevel)
			{
				cout << "\n\n\n\n" << endl;
				cout << "**************************OOP MENU**********************" << endl;
				cout << "Please input a number to choose a function setting plan:" << endl;
				cout << "-1. Back to the previous interface" << endl;
				cout << "0. OOP_类、对象" << endl;
				cout << "1. OOP_函数对象" << endl;
				cout << "2. OOP_类模板" << endl;
				cout << "3. OOP_多态、虚函数、抽象类" << endl;

				inputTag = scanf("%d", &inputNum);

				// 若输入值不是整数，重新输入。
				if (0 == inputTag)
				{
					cout << "Invalid input. Please input again:" << endl;
					setbuf(stdin, NULL);			// stdin输入流由默认缓冲区转为无缓冲区，这样就清空了缓冲区中的内容。
													// 不要用fflush来清空缓存区，该函数很多编译器支持得不好。
					continue;
				}

				// 对二级界面输入值的响应：
				switch (inputNum)
				{
				case -1:
					interfaceLevel = 1;
					break;

				case 0:
					reset_pfun();
					set_fun_OOP_class_object();
					start_OOP_class_object();
					break;

				case 1:
					reset_pfun();
					set_fun_OOP_function_object();
					start_OOP_function_object();
					break;

				case 2:
					reset_pfun();
					set_fun_OOP_class_template();
					start_OOP_class_template();
					break;

				case 3:
					reset_pfun();
					set_fun_OOP_polymorphism();
					start_OOP_polymorphism();
					break;

				default:
					cout << "Invalid input. Please input again:" << endl;
					break;
				}


			}
			break;
		}

		case 4:								// 4. std library章节
		{
			// 界面层级符置为2，进入二级界面：
			interfaceLevel = 2;
			while (2 == interfaceLevel)
			{
				cout << "\n\n\n\n" << endl;
				cout << "**************************STD LIBRARY SYNTAX MENU**********************" << endl;
				cout << "Please input a number to choose a function setting plan:" << endl;
				cout << "-1. Back to the previous interface" << endl;
				cout << "0. stdlib_IO_lib" << endl;
				cout << "1. stdlib_numeric_lib" << endl;
				cout << "2. stdlib_线程支持库" << endl;
				cout << "3. stdlib_工具库" << endl;
				cout << "4. stdlib_数值库" << endl;
				cout << "5. stdlib_正则表达式" << endl;
				cout << "6. stdlib_类型支持库" << endl;
 

				inputTag = scanf("%d", &inputNum);

				// 若输入值不是整数，重新输入。
				if (0 == inputTag)
				{
					cout << "Invalid input. Please input again:" << endl;
					setbuf(stdin, NULL);			// stdin输入流由默认缓冲区转为无缓冲区，这样就清空了缓冲区中的内容。
													// 不要用fflush来清空缓存区，该函数很多编译器支持得不好。
					continue;
				}

				// 对二级界面输入值的响应：
				switch (inputNum)
				{
				case -1:
					interfaceLevel = 1;
					break;

				case 0:
					reset_pfun();
					set_fun_stdlib_IO_lib();
					start_stdlib_IO_lib();
					break;

				case 1:
					reset_pfun();
					set_fun_stdlib_numeric_lib();
					start_stdlib_numeric_lib();
					break;

				case 2:
					reset_pfun();
					set_fun_stdlib_thread_support_lib();
					start_stdlib_thread_support_lib();
					break;

				case 3:
					reset_pfun();

					break;

				case 4:
					reset_pfun();
					set_fun_stdlib_numeric_lib();
					start_stdlib_numeric_lib();
					break;

				case 5:
					reset_pfun();
					set_fun_stdlib_regex();
					start_stdlib_regex();
					break;
					
				case 6:
					reset_pfun();
					set_fun_stdlib_type_support_lib();
					start_stdlib_type_support_lib();
					break;
						
				

				default:
					cout << "Invalid input. Please input again:" << endl;
					break;
				}

			}
			break;
		}

		case 5:								// 5. STL章节
		{
			// 界面层级符置为2，进入二级界面：
			interfaceLevel = 2;
			while (2 == interfaceLevel)
			{
				cout << "\n\n\n\n" << endl;
				cout << "**************************STL MENU**********************" << endl;
				cout << "Please input a number to choose a function setting plan:" << endl;
				cout << "-1. Back to the previous interface" << endl;
				cout << "0. STL——线性容器" << endl;
				cout << "1. " << endl;
				cout << "2. STL——算法库" << endl;
				cout << "3. STL——set集合" << endl;
				cout << "4. STL——容器适配器" << endl;
				cout << "5. STL——list双向链表" << endl;
				cout << "6. STL——map键值对集合" << endl;
				cout << "7. STL——iterator迭代器" << endl;


				inputTag = scanf("%d", &inputNum);

				// 若输入值不是整数，重新输入。
				if (0 == inputTag)
				{
					cout << "Invalid input. Please input again:" << endl;
					setbuf(stdin, NULL);			// stdin输入流由默认缓冲区转为无缓冲区，这样就清空了缓冲区中的内容。
															// 不要用fflush来清空缓存区，该函数很多编译器支持得不好。
					continue;
				}

				// 对二级界面输入值的响应：
				switch (inputNum)
				{
				case -1:
					interfaceLevel = 1;
					break;

				case 0:
					reset_pfun();
					set_fun_STL_linear_container();
					start_STL_linear_container();
					break;

				case 1:
					reset_pfun();
					break;

				case 2:
					reset_pfun();
					set_fun_STL_algorithm_lib();
					start_STL_algorithm_lib();
					break;

				case 3:
					reset_pfun();
					set_fun_STL_set();
					start_STL_set();
					break;

				case 4:
					reset_pfun();
					set_fun_STL_adapter();
					start_STL_adapter();
					break;

				case 5:
					reset_pfun();
					set_fun_STL_list();
					start_STL_list();
					break;

				case 6:
					reset_pfun();
					set_fun_STL_map();
					start_STL_map();
					break;

				case 7:
					reset_pfun();
					set_fun_STL_iterator();
					start_STL_iterator();
					break;
					


				default:
					cout << "Invalid input. Please input again:" << endl;
					break;
				}


			}
			break;
		}

		case 6:								// 6. 底层原理章节
		{
			// 界面层级符置为2，进入二级界面：
			interfaceLevel = 2;
			while (2 == interfaceLevel)
			{
				cout << "\n\n\n\n" << endl;
				cout << "**************************UNDERLYING PRINCIPLES MENU**********************" << endl;
				cout << "Please input a number to choose a function setting plan:" << endl;
				cout << "-1. Back to the previous interface" << endl;
				cout << "0. UP_内存管理" << endl;
				cout << "1. UP_预处理命令" << endl;
				cout << "2. UP_断言" << endl;


				inputTag = scanf("%d", &inputNum);

				// 若输入值不是整数，重新输入。
				if (0 == inputTag)
				{
					cout << "Invalid input. Please input again:" << endl;
					setbuf(stdin, NULL);			// stdin输入流由默认缓冲区转为无缓冲区，这样就清空了缓冲区中的内容。
															// 不要用fflush来清空缓存区，该函数很多编译器支持得不好。
					continue;
				}

				// 对二级界面输入值的响应：
				switch (inputNum)
				{
				case -1:
					interfaceLevel = 1;
					break;

				case 0:
					reset_pfun();
					set_fun_UP_memory_management();
					start_UP_memory_management();
					break;

				case 1:
					reset_pfun();
					set_fun_UP_preprocessing();
					start_UP_preprocessing();
					break;

				case 2:
					reset_pfun();
					set_fun_UP_assert();
					start_UP_assert();
					break;


				default:
					cout << "Invalid input. Please input again:" << endl;
					break;
				}


			}
			break;
		}

		case 7:								// 7. 函数章节
		{
			// 界面层级符置为2，进入二级界面：
			interfaceLevel = 2;
			while (2 == interfaceLevel)
			{
				cout << "\n\n\n\n" << endl;
				cout << "**************************C++ FUNCTION MENU**********************" << endl;
				cout << "Please input a number to choose a function setting plan:" << endl;
				cout << "-1. Back to the previous interface" << endl;
				cout << "0. function_基本知识" << endl;
				cout << "1. function_内联函数、lambda表达式" << endl;
				cout << "2. function_函数模板" << endl;
				cout << "3. function_可变参数函数" << endl;


				inputTag = scanf("%d", &inputNum);

				// 若输入值不是整数，重新输入。
				if (0 == inputTag)
				{
					cout << "Invalid input. Please input again:" << endl;
					setbuf(stdin, NULL);			// stdin输入流由默认缓冲区转为无缓冲区，这样就清空了缓冲区中的内容。
													// 不要用fflush来清空缓存区，该函数很多编译器支持得不好。
					continue;
				}

				// 对二级界面输入值的响应：
				switch (inputNum)
				{
				case -1:
					interfaceLevel = 1;
					break;
				case 0:
					reset_pfun();
					set_fun_function_basic();
					start_function_basic();
					break;

				case 1:
					reset_pfun();
					set_fun_function_inline();
					start_function_inline();
					break;

				case 2:
					reset_pfun();
					set_fun_function_function_template();
					start_function_function_template();
					break;

				case 3:
					reset_pfun();
					set_fun_function_vararg();
					start_function_vararg();
					break;

				default:
					cout << "Invalid input. Please input again:" << endl;
					break;
				}


			}
			break;
		}

		case 8:								// 8. exception
		{
			// 界面层级符置为2，进入二级界面：
			interfaceLevel = 2;
			while (2 == interfaceLevel)
			{
				cout << "\n\n\n\n" << endl;
				cout << "**************************C++ EXCEPTION HANDLING MENU**********************" << endl;
				cout << "Please input a number to choose a function setting plan:" << endl;
				cout << "-1. Back to the previous interface" << endl;
				cout << "0. exception_基本异常处理" << endl;
				cout << "1. exception_标准异常" << endl;


				inputTag = scanf("%d", &inputNum);

				// 若输入值不是整数，重新输入。
				if (0 == inputTag)
				{
					cout << "Invalid input. Please input again:" << endl;
					setbuf(stdin, NULL);			// stdin输入流由默认缓冲区转为无缓冲区，这样就清空了缓冲区中的内容。
															// 不要用fflush来清空缓存区，该函数很多编译器支持得不好。
					continue;
				}

				// 对二级界面输入值的响应：
				switch (inputNum)
				{
				case -1:
					interfaceLevel = 1;
					break;
				case 0:
					reset_pfun();
					set_fun_exception_basic();
					start_exception_basic();
					break;

				case 1:
					reset_pfun();
					set_fun_exception_std_exception();
					start_exception_std_exception();
					break;


				default:
					cout << "Invalid input. Please input again:" << endl;
					break;
				}


			}
			break;
		}
		

		case 9:								// 9. 暂时不知道如何分类的内容
		{
			// 界面层级符置为2，进入二级界面：
			interfaceLevel = 2;
			while (2 == interfaceLevel)
			{
				cout << "\n\n\n\n" << endl;
				cout << "**************************C++ 暂时不知道如何分类的内容**********************" << endl;
				cout << "Please input a number to choose a function setting plan:" << endl;
				cout << "-1. Back to the previous interface" << endl;
				cout << "0.  windows系统函数" << endl;
				cout << "1.  " << endl;


				inputTag = scanf("%d", &inputNum);

				// 若输入值不是整数，重新输入。
				if (0 == inputTag)
				{
					cout << "Invalid input. Please input again:" << endl;
					setbuf(stdin, NULL);			// stdin输入流由默认缓冲区转为无缓冲区，这样就清空了缓冲区中的内容。
															// 不要用fflush来清空缓存区，该函数很多编译器支持得不好。
					continue;
				}

				// 对二级界面输入值的响应：
				switch (inputNum)
				{
				case -1:
					interfaceLevel = 1;
					break;
				case 0:
					reset_pfun();

					break;


				default:
					cout << "Invalid input. Please input again:" << endl;
					break;
				}


			}
			break;
		}

		default:							// default. 不合法的整数输入：
		{
			cout << "Invalid input. Please input again:" << endl;
			break;
		}

		}
	

	}



	return 0;




}
