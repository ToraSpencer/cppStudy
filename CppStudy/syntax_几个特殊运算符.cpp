#include <iostream>
#include <string>
#include <typeinfo>

#include <cstdio>


using namespace std;

#define EPS 1e-10					//定义非常小的一个量EPSilon，当浮点数不大于这个值时，视为0
#define PI 3.14159


// sizeof()运算符：返回一个对象或类型所占的内存字节数。	
/*
    sizeof(对象);           如sizeof(num)
    sizeof(类型名);         如sizeof(int)
			 
*/




// 三目运算符：b ? x : y;   
/*
    计算条件b，若b值为true，则计算表达式x，并返回结果；
        若b值为false，则计算表达式y，并返回计算结果。
			 
*/



/***************************************************************************
***************************************************************************/
// extern变量
extern void(*pfun[100])(void);
extern int inputTag, inputNum, interfaceLevel;



/***************************************************************************
***************************************************************************/
// 函数声明
void set_fun_syntax_specialOperator(void);
void start_syntax_specialOperator(void);

static void test0(void);
static void test1(void);
static void test2(void);
static void test3(void);
static void test4(void);


/***************************************************************************
***************************************************************************/
// extern函数
extern void traverse_pfun(void);



/***************************************************************************
***************************************************************************/
// 自定义类的实现




/***************************************************************************
***************************************************************************/
// 函数定义
void set_fun_syntax_specialOperator(void) 
{
	pfun[0] = test0;
    pfun[1] = test1;
    pfun[2] = test2;
}



void start_syntax_specialOperator(void)
{
	// 界面层级符置为3，进入三级界面：
	interfaceLevel = 3;
	while (3 == interfaceLevel)
	{
		cout << "\n\n\n\n" << endl;
		cout << "**************************MENU: syntax_几个特殊的运算符**********************" << endl;
		cout << "Please choose a demon function to run:" << endl;
		cout << "-2: Run all existed demon function." << endl;
		cout << "-1: Back to the previous interface." << endl;
		cout << "0: test0: sizeof()运算符" << endl;
        cout << "1: test1: 三目运算符" << endl;
        cout << "2: test2: " << endl;


		inputTag = scanf("%d", &inputNum);

		// 若输入值不是整数，重新输入。
		if (inputTag != 1)
		{
			printf("Invalid input. Please input again:\n");
			setbuf(stdin, NULL);
			continue;
		}

		// 对三级界面输入值的响应。
		switch (inputNum)
		{
		case -2:
			traverse_pfun();
			break;

		case -1:
			interfaceLevel = 2;
			break;

		case 0:
			(*pfun[0])();
			break;

        case 1:
			(*pfun[1])();
			break;

        case 2:
			(*pfun[2])();
			break;

		default:
			printf("Invalid input. Please input again:\n");
			break;
		}


	}
}


// test0: sizeof()运算符
static void test0(void)
{
    cout << "\n\n\n\n" << endl;
	cout << "test0: sizeof()运算符" << endl;

    int arri[5];
    cout << "\t数组arri占内存：sizeof(arri) == " << sizeof(arri) << endl;
    cout << "\t数组arri含元素数：sizeof(arri)/sizeof(int) == " << sizeof(arri)/sizeof(int) << endl;

    // 所有指针占内存都是一样的，由操作系统位数决定，64位系统下指针占8字节，即机器字长。
    int* pi;
    double* pd;
    void* pv;
    cout << "\t" << sizeof(pi) << endl;
    cout << "\t" << sizeof(pd) << endl;
    cout << "\t" << sizeof(pv) << endl;

}



// test1: 三目运算符
static void test1(void)
{
    cout << "\n\n\n\n" << endl;
	cout << "test1: 三目运算符" << endl;


    // 应用例子————判断输入整数是奇数还是偶数。
    int inputValid = 0;
    int num;
    string str;

    cout << "请输入一个整数：" << endl;
    while(0 == inputValid)
    {
        setbuf(stdin, NULL);
        inputValid = scanf("%d", &num);
        
        if(0 == inputValid)
        {
            cout << "输入不合法，请重新输入。" << endl;
            setbuf(stdin, NULL);
        }
    }
    str = (num%2 == 0) ? "偶数": "奇数";
    cout << "输入的整数是" << str << endl;
     





}


static void test2(void)
{


}