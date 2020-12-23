#include <iosfwd>
#include <ios>
#include <istream>
#include <ostream>
#include <iostream>
#include <fstream>
#include <sstream>				// 字符串流头文件
//#include <syncstream>				// C++20起
#include <iomanip>
#include <streambuf>
#include <string>
#include <typeinfo>



#include <cstdio>




#ifdef linux
#include <cstrubg>				// 需要使用stderror()函数
#endif



using namespace std;

#define EPS 1e-10					//定义非常小的一个量EPSilon，当浮点数不大于这个值时，视为0
#define PI 3.14159



// 知识点
/*
	常用的格式化操纵符
			setiosflags()			使用多种枚举常量来设定输出格式：
			setw()					设置宽度
			setprecision()			设置浮点数精度。
			hex						以十六进制形式输出整数
			fixed					以普通小数形式输出浮点数
			scientific				以科学计数法形式输出浮点数
			left					左对齐，即在宽度不足时将填充字符添加到右边。默认情形是右对齐。



	C++中重要的几个流对象
			cin————istream类
							从标准输入读取数据。
							
			cout————ostream类
					从标准输出写入数据。
					
			cerr————ostream类
					用于输出程序错误消息，写入到标准错误。
					
			clog————ostream类
					类似于cerr，但是有缓冲，缓冲区满时被输出。


	C中重要的几个流对象
			stdin
			stdout
			stderr


	C中IO相关的函数
			scanf()					从标准输入stdin（键盘）读取格式化输入数据
			printf()				数据格式化输出到标准输出stdout（屏幕）上。
			fprintf()				数据格式化输入到流对象中。
			strerror()			接收错误号并从内部数组中搜索，返回一个指向错误消息字符串的指针。生成的错误字符串取决于开发平台和编译器。


	C++IO类型的特点
			对象不可以赋值、赋值

			对象不能存入容器。

			函数形参和返回的一般都是流类型的引用，不能是对象。而且是非const的引用，因为读写一个流对象会改变其状态。
						典型的例子就是在对流输入/输出操作符>>/<<进行运算符重载的时候，返回类型是引用。
						例——	istream& operator>>(istream& is, Complex& cc);	



	缓冲区
				每个输入输出流都管理一个缓冲区。
				缓冲区的作用：保存程序读写的数据。
				以下情况会导致缓冲区刷新：
						1. 程序正常结束。
						2. 缓冲区满。
						3. 使用endl、flush等操纵符来刷新。
				几个重要的操纵符
						endl
						ends
						flush
						unitbuf


	cin对象的重要方法：
				cin.get() 						//一次只能读取一个字符
				cin.get(一个参数) 				//读一个字符
				cin.get(三个参数) 				//可以读字符串
				cin.getline()					// 从cin对象中读一行，存入到string对象中。
				cin.ignore()
				cin.putback()


	fstream类的几个重要方法
				两种构造函数
								fstream(str);					// str是文件路径
								fstream(str, mode);		// mode是打开模式
											in	以读的方式打开
											out	以写的方式打开
											app	每次写操作前均定位到文件末尾
											ate	打开文件后立即定位到文件末尾
											trunc	截断文件
											binary	以二进制方式进行IO操作。
				open()
				close()
				is_open()
								返回一个bool值，说明文件是否成功打开并且尚未关闭。

	string流类——stringstream
				用于像string对象输入数据，或者接受string对象输出的数据。
				重要方法
							str()
										重载1				str(void)——返回stringstream对象内封装的string对象
										重载2				str(str1)——将字符串str1对象拷贝到当前stringstream对象中。
										应用				可以应用stringstream对象将任意类型数据转换为string.


*/


// 未整理的函数原型
/*
		int scanf(const char *format, ...) 
		
		int printf(const char *format, ...)
		
		int fprintf(FILE *stream, const char *format, ...)
		
		char *strerror(int errnum)
					在头文件<string.h>中定义





/*





// 其他相对不重要的知识点
/*
		IO库头文件：
					<iosfwd>			所有IO中的类的前置声明
					<ios> 				std::ios_base 类、	std::basic_ios 类模板、 数个 typedef
					<istream> 		std::basic_istream 类模板、 数个 typedef
					<ostream> 		std::basic_ostream、 std::basic_iostream 类模板、	数个 typedef
					<iostream>		数个标准流对象
					<fstream> 		std::basic_fstream、 std::basic_ifstream、	std::basic_ofstream 类模板、	数个typedef
					<sstream> 		std::basic_stringstream、	std::basic_istringstream、 std::basic_ostringstream 类模板、 数个 typedef
					<syncstream>	(C++20 起) std::basic_osyncstream、 std::basic_syncbuf、 一些typedef
					<strstream> 	(C++98 中弃用)  
					<iomanip> 		控制IO格式的辅助函数
					<streambuf> 		std::basic_streambuf 类模板
					<cstdio>			C 风格输入输出函数


		IO库中的类：
					ifstream
							————<fstream>
							输入文件流类型

					ofstream
							————<fstream>
							输出文件流类型

					fstream
							————<fstream>
							输入输出文件流类型
							可以读也可以写
							
					类的继承关系：
							istream → ifstream
									→ istringstream

					

*/



/***************************************************************************
***************************************************************************/
// 全局变量、类型定义
struct myDate 
{
	int year, month, day;
};



/***************************************************************************
***************************************************************************/
// extern变量
extern void(*pfun[100])(void);
extern int inputTag, inputNum, interfaceLevel;



/***************************************************************************
***************************************************************************/
// 函数声明
void set_fun_stdlib_IO_lib(void);
void start_stdlib_IO_lib(void);

template<typename T>
inline string toString(const T&);					// string流对象实现的将基本类型转换为string类型的函数

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
void set_fun_stdlib_IO_lib(void)
{
	pfun[0] = test0;
	pfun[1] = test1;
	pfun[2] = test2;
	pfun[3] = test3;
	pfun[4] = test4;

}


void start_stdlib_IO_lib(void)
{
	// 界面层级符置为3，进入三级界面：
	interfaceLevel = 3;
	while (3 == interfaceLevel)
	{
		cout << "\n\n\n\n" << endl;
		cout << "**************************MENU: stdlib_IO_lib**********************" << endl;
		cout << "Please choose a demon function to run:" << endl;
		cout << "-2: Run all existed demon function." << endl;
		cout << "-1: Back to the previous interface." << endl;
		cout << "0. test0: <iomanip>中的操纵符(manipulator)来控制输出格式：" << endl;
		cout << "1. test1：文件流类——ifstream, ofstream" << endl;
		cout << "2. test2: 使用cin对象来接收输入" << endl;
		cout << "3. test3：string流" << endl;
		cout << "4. test4: 使用scanf()的返回值进行输入合法检验" << endl;

			

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

		case 3:
			(*pfun[3])();

		case 4:
			(*pfun[4])();

		default:
			printf("Invalid input. Please input again:\n");
			break;
		}


	}
}


template <typename T>
inline string toString(const T& arg)
{
	ostringstream os;
	os << arg;
	return os.str();							// string流类的str()方法——返回其封装的字符串对象。
}




// test0: <iomanip>中的操纵符(manipulator)来控制输出格式：
static void test0(void)
{
	double d1, d2, d3;
	d1 = 3.1415926;
	d2 = 232.2345;
	d3 = 90989.111;

	cout << "\n\n\n\n" << endl;
	cout << "test0: <iomanip>中的操纵符(manipulator)来控制输出格式：" << endl;


	// setw()或cout.width()————指定输出浮点数的宽度，超出部分自动补空格，默认右对齐。
	cout << setw(10) << d1 << endl;
	cout.width(10);								// 输出一次后该设定便失效
	cout << d2 << endl;
	cout.width(10);
	cout << d3 << endl;
	cout << endl << endl;


	// setiosflags()————使用多种枚举常量来设定输出格式：
	cout << "左对齐格式——ios_base::left" << endl;
	cout << setiosflags(ios_base::left) << setw(20) << d1 << endl;			// 设置左对齐
	cout << setw(20)<< d2 << endl;
	cout << resetiosflags(ios_base::left) << setw(20) << d3 << endl;			// 设置一次后一直有效，需要手动撤销
	cout << "正数前加正号——ios_base::showpos" << endl;
	cout << setiosflags(ios_base::showpos) << 1234 << endl;
	cout << resetiosflags(ios_base::showpos);							// 手动撤销格式
	cout << endl << endl;


	// setprecision()————设置浮点数精度：
	cout << "setprecision()————设置浮点数精度：" << endl;
	cout << setprecision(1) << d2 << endl;					// 此时setprecision()设置的是有效数字位数；位数不够用时默认使用科学计数法ios_base::scientific
	cout << setiosflags(ios_base::fixed) << setprecision(1) << d2 << endl;
																					// 指定定点标记输出ios_base::fixed输出时，setprecision设置的是小数点后保留位数。


}





// test1：文件流类——ifstream, ofstream
static void test1(void)
{
	// 创建输入、输出文件流对象。程序对文件的读是输入，写是输出
	//		输入输出、流入流出都是以程序的视角来看的，如程序向标准输出对象写入用cout <<..，文件流数据写入程序中的变量用file>>arg
	//		符合编程规范的写法是只写相对路径，不写绝对路径。
	//		ios_base::binary 指定打开模式为二进制，不指定的话默认为文本模式
	//		ios_base::out——输出模式，没有文件则创建文件，有文件则清空文件数据。
	//		ios_base::app——追加模式，即append，写时不清空原有数据，从末尾开始写。
	ofstream writeFile1("test1.xxx");					  
	ofstream writeFile2("test2.xxx", ios_base::out|ios_base::binary); 
	ofstream writeTextFile("myText.txt", ios_base::out);
	ifstream readFile1("test1.xxx");					
	ifstream readFile2("test2.xxx", ios_base::in|ios_base::binary);


	string str1 = "hello world";
	string str11;
	int inum1 = 2019;
	float fnum1 = 2019.4;
	char str2[100];

	cout << "\n\n\n\n" << endl;
	cout << "test1: 使用ifstream, ofstream读写文件	" << endl;


	// 写二进制文件，基本类型变量——可以用write()方法写入，也可以用输出流运算符。
	writeFile1 << str1 << inum1 << fnum1 << endl;
	writeFile1.close();					// ！！操作完之后要关闭文件流


	// 写二进制文件，自定义类型变量——write()方法写入，或使用重载的输出流运算符。
	// write()方法
	/*
		basic_ostream& write( const char_type* s,		待写入的数据的头部指针，强转为char*
						  std::streamsize count			待写入数据字节数。
							)
							
		？？？可以写自定义结构体实例，不可以写类对象；？？？为什么？
	*/
	myDate dt = {2020, 3, 15};
	writeFile2.write(reinterpret_cast<char*>(&dt), sizeof(dt));
	writeFile2.close();

	
	// 写文本文件
	writeTextFile<< str1<<inum1<<fnum1;
	

	


	// 读文件：
	// getline()方法——从流对象中读取数据存储到字符串。
	/*
		basic_istream& getline( char_type* s, 
							std::streamsize count 
							);
					
	*/
	readFile1.getline(str2,30);
	ifstream readTextFile("myText.txt", ios_base::in);
	readTextFile>>str11;		// 直接用输入流运算符
	cout << str2 << endl;
	readFile1.close();


	// 读文件
	// read()方法————二进制文件中读取数据。
	/*
		basic_istream& read( char_type* s,					接收读取数据的变量的头部指针，强转为char*	
						   std::streamsize count			读取输入的字节数。
							);
	*/
	myDate dt_input;
	readFile2.read(reinterpret_cast<char*>(&dt_input), sizeof(dt_input));
	cout << "日期是"<< dt_input.year << "-" << dt_input.month << "-"<< dt_input.day << endl;
	readFile2.close();


}	



// test2: 使用cin对象来接收输入：
static void test2(void)
{
	cout << "\n\n\n\n" << endl;
	cout << "test2: 使用cin对象来接收输入" << endl;


	// 提取运算符">>"———提取cin对象中的数据
	int numi1;
	cout << "请输入一个整数" << endl;
	cin >> numi1;
	cout << "输入的整数是：" << numi1 << endl;
	cout << endl << endl;
	
	

	// cin.get()————类似于>>，但是>>拒绝接受空格，get()可以
	setbuf(stdin, NULL);					// 清空缓冲区
	cout << "请输入一段字符串，以q结束：" << endl;
	char ch;
	while ((ch = cin.get()) != 'q')
	{
		cout.put(ch);
	}
	setbuf(stdin, NULL);					// 清空缓冲区
	cin.clear();
	cout << endl << endl;


	// getline()———从cin中读取一系列字符，并且可以设置终止字符，并且可以存入string对象
	string str;
	cout << "请输入一段字符串，以p结束" << endl;
	getline(cin, str, 'p');					// 从cin中读取一系列字符，存入str对象，以p结束
	cin.clear();
	setbuf(stdin, NULL);					// 清空缓冲区
	cout << "输入的字符串为："<< str << endl;



}



// test3: string流
static void test3(void) 
{
	cout << "\n\n\n\n" << endl;
	cout << "test3: string流" << endl;


	// string流对象实现的toString函数：
	int numi1 = 999;
	string str = toString(numi1);
	cout << str << endl;


	stringstream ss;
	// 字符串拷贝、拼接、格式化等工作都可以通过sstream来实现，比C语言中方便。
	//		格式化字符串
	for (int i = 1; i < 10; i++) 
	{
		ss << "这是第" << i << "次循环";
		cout << ss.str() << endl;
		ss.str("");					// 使用空字符串来替代oss流对象的底层字符串。
	}

	// string对象拼接
	string str1, str2;
	str1 = "hahaha";
	str2 = "wawawa";
	ss << str1 << str2;
	str1 = ss.str();
	ss.str("");
	cout << str1 << endl << endl;;

	// C风格的字符串拼接
	char cstr1[50] = "hahaha";
	char cstr2[50] = "wawawa";
	char cstr3[50] = "1";
	ss << cstr1 << cstr2;
	ss >> cstr1;				// c风格的字符串不可以使用"="赋值，c语言中使用strcpy();
	// 经过上面的流输入操作后，流对象ss处于失效状态，必须调用clear()方法才能再次使用。
	ss.clear();				// clear()方法——使流对象重新处于有效状态。
	ss << cstr1;
	ss >> cstr3;
	ss.str("");
	cout << cstr1 << endl;
	cout << cstr3 << endl;
}



// test4: 使用scanf()的返回值进行输入合法检验
static void test4(void)
{
	cout << "\n\n\n\n" << endl;
	cout << "test4: 使用scanf()的返回值进行输入合法检验" << endl;


	int inputValid = 0;
	int num;
	cout << "请输入一个整数" << endl;
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
	cout << "输入的整数是" << num << endl;


}
