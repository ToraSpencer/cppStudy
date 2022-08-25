#include <stdlib.h>
#include <cstdio>
#include <iostream>
#include <cstdio>
using namespace std;

 
void(*pfun[100])(void) = {NULL};
int inputTag;							// �˵��������ж������Ƿ���Ч�ı�ʶ����
int inputNum;							// �˵��������û����������
int interfaceLevel;						// ��ǰ�˵�����Ĳ㼶�����˵���һ����


 
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
extern void set_fun_errorHandling_basic(void);
extern void set_fun_errorHandling_std_exception(void);




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
extern void start_errorHandling_basic(void);
extern void start_errorHandling_std_exception(void);





/***************************************************************************
***************************************************************************/
// ��������
int main(int argc, char** argv)
{
	inputNum = 99;
	inputTag = 0;
	interfaceLevel = 1;

	reset_pfun();

 
	// ������ѭ������ѡ���½�
	while (1 == interfaceLevel)
	{
		cout << "\n\n\n\n" << endl;
		cout << "**************************MAIN MENU**********************" << endl;
		cout << "Please input a number to choose a function setting plan:" << endl;
		cout << "1. ��������" << endl;
		cout << "2. C++ �﷨" << endl;
		cout << "3. OOP" << endl;
		cout << "4. C++ ��׼��" << endl;
		cout << "5. STL" << endl;
		cout << "6. �ײ�ԭ��" << endl;
		cout << "7. ����" << endl;
		cout << "8. �쳣����" << endl;
		cout << "9. ���ģʽ" << endl;
		cout << "10. ��ʱ��֪����η��������" << endl;
		cout << "-1. Quit" << endl;


		inputTag = scanf("%d", &inputNum);


		// ������ֵ�����������������롣
		if (0 == inputTag)
		{
			cout << "Invalid input. Please input again:" << endl;
			setbuf(stdin, NULL);			// stdin��������Ĭ�ϻ�����תΪ�޻�����������������˻������е����ݡ�
											// ��Ҫ��fflush����ջ��������ú����ܶ������֧�ֵò��á�
			continue;
		}


		// ������������ֵ����Ӧ��
		switch (inputNum)
		{
		case -1:							// �˳�����
		{
			interfaceLevel = 0;
			break;
		}

		case 1:								// 1. data type�½ڡ�
		{
			// ����㼶����Ϊ2������������棺
			interfaceLevel = 2;
			while (2 == interfaceLevel)
			{
				cout << "\n\n\n\n" << endl;
				cout << "**************************DATA TYPE MENU**********************" << endl;
				cout << "Please input a number to choose a function setting plan:" << endl;
				cout << "-1. Back to the previous interface" << endl;
				cout << "0. dataType_��������" << endl;
				cout << "1. dataType_ָ�롢����ָ��" << endl;
				cout << "2. dataType_����ָ��" << endl;
				cout << "3. dataType_����" << endl;
				cout << "4. dataType_ö�١������塢�ṹ��" << endl;
				cout << "5. dataType_����" << endl;
				cout << "6. dataType_c����ַ�����string" << endl;

				inputTag = scanf("%d", &inputNum);

				// ������ֵ�����������������롣
				if (0 == inputTag)
				{
					cout << "Invalid input. Please input again:" << endl;
					setbuf(stdin, NULL);			// stdin��������Ĭ�ϻ�����תΪ�޻�����������������˻������е����ݡ�
													// ��Ҫ��fflush����ջ��������ú����ܶ������֧�ֵò��á�
					continue;
				}

				// �Զ�����������ֵ����Ӧ��
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

		case 2:								// 2. C++ syntax�½�
		{
			// ����㼶����Ϊ2������������棺
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
				cout << "3. syntax_����ת��" << endl;
				cout << "4. syntax_���ʽ" << endl;
				cout << "5. syntax_��������������" << endl;

				inputTag = scanf("%d", &inputNum);

				// ������ֵ�����������������롣
				if (0 == inputTag)
				{
					cout << "Invalid input. Please input again:" << endl;
					setbuf(stdin, NULL);			// stdin��������Ĭ�ϻ�����תΪ�޻�����������������˻������е����ݡ�
													// ��Ҫ��fflush����ջ��������ú����ܶ������֧�ֵò��á�
					continue;
				}

				// �Զ�����������ֵ����Ӧ��
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

		case 3:								// 3. OOP�½�
		{
			// ����㼶����Ϊ2������������棺
			interfaceLevel = 2;
			while (2 == interfaceLevel)
			{
				cout << "\n\n\n\n" << endl;
				cout << "**************************OOP MENU**********************" << endl;
				cout << "Please input a number to choose a function setting plan:" << endl;
				cout << "-1. Back to the previous interface" << endl;
				cout << "0. OOP_�ࡢ����" << endl;
				cout << "1. OOP_��������" << endl;
				cout << "2. OOP_��ģ��" << endl;
				cout << "3. OOP_��̬���麯����������" << endl;

				inputTag = scanf("%d", &inputNum);

				// ������ֵ�����������������롣
				if (0 == inputTag)
				{
					cout << "Invalid input. Please input again:" << endl;
					setbuf(stdin, NULL);			// stdin��������Ĭ�ϻ�����תΪ�޻�����������������˻������е����ݡ�
													// ��Ҫ��fflush����ջ��������ú����ܶ������֧�ֵò��á�
					continue;
				}

				// �Զ�����������ֵ����Ӧ��
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

		case 4:								// 4. std library�½�
		{
			// ����㼶����Ϊ2������������棺
			interfaceLevel = 2;
			while (2 == interfaceLevel)
			{
				cout << "\n\n\n\n" << endl;
				cout << "**************************STD LIBRARY SYNTAX MENU**********************" << endl;
				cout << "Please input a number to choose a function setting plan:" << endl;
				cout << "-1. Back to the previous interface" << endl;
				cout << "0. stdlib_IO_lib" << endl;
				cout << "1. stdlib_numeric_lib" << endl;
				cout << "2. stdlib_�߳�֧�ֿ�" << endl;
				cout << "3. stdlib_���߿�" << endl;
				cout << "4. stdlib_��ֵ��" << endl;
				cout << "5. stdlib_������ʽ" << endl;
				cout << "6. stdlib_����֧�ֿ�" << endl;
 

				inputTag = scanf("%d", &inputNum);

				// ������ֵ�����������������롣
				if (0 == inputTag)
				{
					cout << "Invalid input. Please input again:" << endl;
					setbuf(stdin, NULL);			// stdin��������Ĭ�ϻ�����תΪ�޻�����������������˻������е����ݡ�
													// ��Ҫ��fflush����ջ��������ú����ܶ������֧�ֵò��á�
					continue;
				}

				// �Զ�����������ֵ����Ӧ��
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

		case 5:								// 5. STL�½�
		{
			// ����㼶����Ϊ2������������棺
			interfaceLevel = 2;
			while (2 == interfaceLevel)
			{
				cout << "\n\n\n\n" << endl;
				cout << "**************************STL MENU**********************" << endl;
				cout << "Please input a number to choose a function setting plan:" << endl;
				cout << "-1. Back to the previous interface" << endl;
				cout << "0. STL������������" << endl;
				cout << "1. " << endl;
				cout << "2. STL�����㷨��" << endl;
				cout << "3. STL����set����" << endl;
				cout << "4. STL��������������" << endl;
				cout << "5. STL����list˫������" << endl;
				cout << "6. STL����map��ֵ�Լ���" << endl;
				cout << "7. STL����iterator������" << endl;


				inputTag = scanf("%d", &inputNum);

				// ������ֵ�����������������롣
				if (0 == inputTag)
				{
					cout << "Invalid input. Please input again:" << endl;
					setbuf(stdin, NULL);			// stdin��������Ĭ�ϻ�����תΪ�޻�����������������˻������е����ݡ�
															// ��Ҫ��fflush����ջ��������ú����ܶ������֧�ֵò��á�
					continue;
				}

				// �Զ�����������ֵ����Ӧ��
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

		case 6:								// 6. �ײ�ԭ���½�
		{
			// ����㼶����Ϊ2������������棺
			interfaceLevel = 2;
			while (2 == interfaceLevel)
			{
				cout << "\n\n\n\n" << endl;
				cout << "**************************UNDERLYING PRINCIPLES MENU**********************" << endl;
				cout << "Please input a number to choose a function setting plan:" << endl;
				cout << "-1. Back to the previous interface" << endl;
				cout << "0. UP_�ڴ����" << endl;
				cout << "1. UP_Ԥ��������" << endl;
				cout << "2. UP_����" << endl;


				inputTag = scanf("%d", &inputNum);

				// ������ֵ�����������������롣
				if (0 == inputTag)
				{
					cout << "Invalid input. Please input again:" << endl;
					setbuf(stdin, NULL);			// stdin��������Ĭ�ϻ�����תΪ�޻�����������������˻������е����ݡ�
															// ��Ҫ��fflush����ջ��������ú����ܶ������֧�ֵò��á�
					continue;
				}

				// �Զ�����������ֵ����Ӧ��
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

		case 7:								// 7. �����½�
		{
			// ����㼶����Ϊ2������������棺
			interfaceLevel = 2;
			while (2 == interfaceLevel)
			{
				cout << "\n\n\n\n" << endl;
				cout << "**************************C++ FUNCTION MENU**********************" << endl;
				cout << "Please input a number to choose a function setting plan:" << endl;
				cout << "-1. Back to the previous interface" << endl;
				cout << "0. function_����֪ʶ" << endl;
				cout << "1. function_����������lambda���ʽ" << endl;
				cout << "2. function_����ģ��" << endl;
				cout << "3. function_�ɱ��������" << endl;


				inputTag = scanf("%d", &inputNum);

				// ������ֵ�����������������롣
				if (0 == inputTag)
				{
					cout << "Invalid input. Please input again:" << endl;
					setbuf(stdin, NULL);			// stdin��������Ĭ�ϻ�����תΪ�޻�����������������˻������е����ݡ�
													// ��Ҫ��fflush����ջ��������ú����ܶ������֧�ֵò��á�
					continue;
				}

				// �Զ�����������ֵ����Ӧ��
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
			// ����㼶����Ϊ2������������棺
			interfaceLevel = 2;
			while (2 == interfaceLevel)
			{
				cout << "\n\n\n\n" << endl;
				cout << "**************************C++ EXCEPTION HANDLING MENU**********************" << endl;
				cout << "Please input a number to choose a function setting plan:" << endl;
				cout << "-1. Back to the previous interface" << endl;
				cout << "0. errorHandling_�����쳣����" << endl;
				cout << "1. errorHandling_��׼�쳣" << endl;


				inputTag = scanf("%d", &inputNum);

				// ������ֵ�����������������롣
				if (0 == inputTag)
				{
					cout << "Invalid input. Please input again:" << endl;
					setbuf(stdin, NULL);			// stdin��������Ĭ�ϻ�����תΪ�޻�����������������˻������е����ݡ�
															// ��Ҫ��fflush����ջ��������ú����ܶ������֧�ֵò��á�
					continue;
				}

				// �Զ�����������ֵ����Ӧ��
				switch (inputNum)
				{
				case -1:
					interfaceLevel = 1;
					break;
				case 0:
					reset_pfun();
					set_fun_errorHandling_basic();
					start_errorHandling_basic();
					break;

				case 1:
					reset_pfun();
					set_fun_errorHandling_std_exception();
					start_errorHandling_std_exception();
					break;


				default:
					cout << "Invalid input. Please input again:" << endl;
					break;
				}


			}
			break;
		}
		

		case 9:								// 9. ���ģʽ
		{
			// ����㼶����Ϊ2������������棺
			interfaceLevel = 2;
			while (2 == interfaceLevel)
			{
				cout << "\n\n\n\n" << endl;
				cout << "**************************���ģʽ**********************" << endl;
				cout << "Please input a number to choose a function setting plan:" << endl;
				cout << "-1. Back to the previous interface" << endl;
				cout << "0. ����ģʽ" << endl;
				cout << "1. ����ģʽ" << endl;
				cout << "2. ����ģʽ" << endl;
				cout << "3. ����ģʽ" << endl;


				inputTag = scanf("%d", &inputNum);

				// ������ֵ�����������������롣
				if (0 == inputTag)
				{
					cout << "Invalid input. Please input again:" << endl;
					setbuf(stdin, NULL);			// stdin��������Ĭ�ϻ�����תΪ�޻�����������������˻������е����ݡ�
															// ��Ҫ��fflush����ջ��������ú����ܶ������֧�ֵò��á�
					continue;
				}

				// �Զ�����������ֵ����Ӧ��
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


		case 10:								// 9. ��ʱ��֪����η��������
		{
			// ����㼶����Ϊ2������������棺
			interfaceLevel = 2;
			while (2 == interfaceLevel)
			{
				cout << "\n\n\n\n" << endl;
				cout << "**************************C++ ��ʱ��֪����η��������**********************" << endl;
				cout << "Please input a number to choose a function setting plan:" << endl;
				cout << "-1. Back to the previous interface" << endl;
				cout << "0.  windowsϵͳ����" << endl;
				cout << "1.  " << endl;


				inputTag = scanf("%d", &inputNum);

				// ������ֵ�����������������롣
				if (0 == inputTag)
				{
					cout << "Invalid input. Please input again:" << endl;
					setbuf(stdin, NULL);			// stdin��������Ĭ�ϻ�����תΪ�޻�����������������˻������е����ݡ�
													// ��Ҫ��fflush����ջ��������ú����ܶ������֧�ֵò��á�
					continue;
				}

				// �Զ�����������ֵ����Ӧ��
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

		default:							// default. ���Ϸ����������룺
		{
			cout << "Invalid input. Please input again:" << endl;
			break;
		}

		}
	

	}

 
 

	return 0;




}
