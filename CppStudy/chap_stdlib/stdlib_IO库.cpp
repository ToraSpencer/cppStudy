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

#include "stdlib_IO库.h"


#include <cstdio>


#ifdef linux
#include <cstrubg>				// 需要使用stderror()函数
#endif

#define EPS 1e-10					//定义非常小的一个量EPSilon，当浮点数不大于这个值时，视为0
#define PI 3.14159

// 知识点
/*
	常用的格式化操纵符
			setiosflags()			使用多种枚举常量来设定输出格式：
			setw()					设置宽度
			setprecision()			设置浮点数精度。
			oct						以八进制形式输出整数
			dec						以十进制形式输出整数
			hex						以十六进制形式输出整数
			fixed					以普通小数形式输出浮点数
			scientific				以科学计数法形式输出浮点数
			left					左对齐，即在宽度不足时将填充字符添加到右边。默认情形是右对齐。



	C++中重要的几个流对象
			cin————istream类
							从标准输入读取数据。
							
			std::cout————ostream类
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
						3. 使用std::endl、flush等操纵符来刷新。
				几个重要的操纵符
						std::endl
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
										重载1				str()——返回stringstream对象内封装的string对象
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
					<ios> 				std::std::ios_base 类、	std::basic_ios 类模板、 数个 typedef
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


virtualModule* stdlib_io_module::getInstance()		// 线程不安全的单例模式
{
	if (nullptr != p_moduleIns)
	{
		delete p_moduleIns;
	}
	p_moduleIns = new stdlib_io_module;
	return p_moduleIns;
}


// test0: 控制输出格式：
void stdlib_io_module::test0()
{
	double d1, d2, d3;
	d1 = 3.1415926;
	d2 = 232.2345;
	d3 = 90989.111;

	debugDisp("\n\n\n\n");
	debugDisp("test0: <iomanip>中的操纵符(manipulator)来控制输出格式：\n");  

	// setw()或std::cout.width()————指定输出浮点数的宽度，超出部分自动补空格，默认右对齐。
	{
		debugDisp("setw()或std::cout.width()————指定输出浮点数的宽度，超出部分自动补空格，默认右对齐");
		std::cout << std::setw(10) << d1 << std::endl;
		std::cout.width(10);								// 输出一次后该设定便失效
		std::cout << d2 << std::endl;
		std::cout.width(10);
		std::cout << d3 << std::endl;

		debugDisp();
	} 

	// 使用std::oct, std::dec, std::hex指定不同进制输出整型数：
	{
		debugDisp("使用std::oct, std::dec, std::hex指定不同进制输出整型数：");
		std::cout << std::oct << 1024 << std::endl;
		std::cout << std::dec << 1024 << std::endl;
		std::cout << std::hex << 1024 << std::endl;

		debugDisp();
	}

	// setiosflags()————使用多种枚举常量来设定输出格式：
	{
		debugDisp("左对齐格式——std::ios_base::left："); 
		std::cout << std::setiosflags(std::ios_base::left) << std::setw(20) << d1 << std::endl;			// 设置左对齐
		std::cout << std::setw(20) << d2 << std::endl;
		std::cout << std::resetiosflags(std::ios_base::left) << std::setw(20) << d3 << std::endl;			// 设置一次后一直有效，需要手动撤销
		
		debugDisp("正数前加正号——std::ios_base::showpos"); 
		std::cout << std::setiosflags(std::ios_base::showpos) << 1234 << std::endl;
		std::cout << std::resetiosflags(std::ios_base::showpos);							// 手动撤销格式
	
		debugDisp();
	}


	// setprecision()————设置浮点数精度：
	{
		debugDisp("setprecision()————设置浮点数精度："); 
		std::cout << std::setprecision(1) << d2 << std::endl;					// 此时setprecision()设置的是有效数字位数；位数不够用时默认使用科学计数法std::ios_base::scientific
		std::cout << std::setiosflags(std::ios_base::fixed) << std::setprecision(1) << d2 << std::endl;

		// 指定定点标记输出std::ios_base::fixed输出时，setprecision设置的是小数点后保留位数。
		debugDisp();
	} 

	// C语言中的格式控制： 
	/*
		%c	字符输出到缓冲区，不转换。
		%d	整数转成十进位。
		%f	倍精确度数字转成浮点数。
					例：%08.2f
									0是 "填空字元" 表示,如果长度不足时就用0来填满；
									8格式化后总长度；
									2f小数位长度，即2位；
		%o	整数转成八进位。
		%s	字符串输出到缓冲区，不转换。
		%x	整数转成小写十六进位。
		%X	整数转成大写十六进位。
	*/
	{
		debugDisp("C语言中的格式控制： ");

		char str[100] = { 0 };
		sprintf(str, "d1 == %.9f;", d1);
		std::cout << str << std::endl;

		debugDisp();
	} 

	debugDisp("test0() finished.");
}



// test1：文件流类——ifstream, ofstream
namespace TEST_FILESTREAM 
{
	struct myDate
	{
		int year, month, day;
	};
}

void stdlib_io_module::test1()
{
	// 输入、输出文件流对象。 
	/*
			输入输出、流入流出都是以程序的视角来看的，
					如程序向标准输出对象写入用std::cout <<..，文件流数据写入程序中的变量用file>>arg
			符合编程规范的写法是只写相对路径，不写绝对路径。
			std::ios_base::binary 指定打开模式为二进制，不指定的话默认为文本模式
			std::ios_base::out——输出模式，没有文件则创建文件，有文件则清空文件数据。
			std::ios_base::app——追加模式，即append，写时不清空原有数据，从末尾开始写。
	*/
	using namespace TEST_FILESTREAM;

	std::ofstream writeFile1("test1.xxx");
	std::ofstream writeFile2("test2.xxx", std::ios_base::out|std::ios_base::binary);
	std::ofstream writeTextFile("myText.txt", std::ios_base::out);
	std::ifstream readFile1("testTxt.txt");
	std::ifstream readFile2("test2.xxx", std::ios_base::in|std::ios_base::binary);

	std::string str1 = "hello world";
	std::string str11;
	int inum1 = 2019;
	float fnum1 = 2019.4f;
	char str2[512];

	debugDisp("\n\n\n\n"); 
	debugDisp("test1: 使用ifstream, ofstream读写文件	");

	// 1. fstream重载了!运算符，返回一个bool，用来判断文件句柄是否打开成功：
	std::fstream testFile("E:/一个不存在的文件.aaa", std::ios_base::in);
	if (!testFile)
		debugDisp("文件句柄testFile打开失败。");

	// 2. 写二进制文件

	//			2.1 基本类型变量——可以用write()方法写入，或使用重载的输出流运算符。
	writeFile1 << str1 << inum1 << fnum1 << std::endl;
	writeFile1.close();					// ！！操作完之后要关闭文件流


	//			2.2 自定义类型变量——write()方法写入，或使用重载的输出流运算符。

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

	// 3. 写文本文件——直接使用流输入运算符operator<<
	writeTextFile<< str1<<inum1<<fnum1; 

	// 4. 读文件：

	//		4.1 getline()方法——从流对象中读取数据存储到字符串。
	/*
		basic_istream& getline( 
							char_type* s, 
							std::streamsize count 
							);		
	*/
	std::cout << "循环调用getline()从文本文件中读取每一行：" << std::endl;
	while (readFile1.getline(str2, 512))		// 只要可以读到文件内容（包括空行），getline()返回值就一直是True(internal state flag)；
		std::cout << str2 << std::endl;				// 如果读取失败，那么会抛出相对应的异常。
	readFile1.close();
	std::cout << std::endl;

	//		4.2 read()方法————二进制文件中读取数据。
	/*
		basic_istream& read( 
							char_type* s,					接收读取数据的变量的头部指针，强转为char*	
						   std::streamsize count			读取输入的字节数。
							);
	*/
	myDate dt_input;
	readFile2.read(reinterpret_cast<char*>(&dt_input), sizeof(dt_input));
	std::cout << "日期是"<< dt_input.year << "-" << dt_input.month << "-"<< dt_input.day << std::endl;
	readFile2.close();


	debugDisp("test1() finished.");
}	



// test2: 使用cin对象来接收输入：
void stdlib_io_module::test2()
{
	std::cout << "\n\n\n\n" << std::endl;
	std::cout << "test2: 使用cin对象来接收输入" << std::endl;


	// 提取运算符">>"———提取cin对象中的数据
	int numi1;
	std::cout << "请输入一个整数" << std::endl;
	std::cin >> numi1;
	std::cout << "输入的整数是：" << numi1 << std::endl;
	std::cout << std::endl << std::endl;
	

	// cin.get()————类似于>>，但是>>拒绝接受空格，get()可以
	setbuf(stdin, NULL);					// 清空缓冲区
	std::cout << "请输入一段字符串，以q结束：" << std::endl;
	char ch;
	while ((ch = std::cin.get()) != 'q')
		std::cout.put(ch);

	setbuf(stdin, NULL);					// 清空缓冲区
	std::cin.clear();
	std::cout << std::endl << std::endl;


	// getline()———从cin中读取一系列字符，并且可以设置终止字符，并且可以存入string对象
	std::string str;
	std::cout << "请输入一段字符串，以p结束" << std::endl;
	std::getline(std::cin, str, 'p');					// 从cin中读取一系列字符，存入str对象，以p结束
	std::cin.clear();
	setbuf(stdin, NULL);					// 清空缓冲区
	std::cout << "输入的字符串为："<< str << std::endl;

}


// test3: string流
namespace TEST_STRINGSTREAM
{
	template<typename T>
	inline std::string toString(const T&);					// string流对象实现的将基本类型转换为string类型的函数

	template <typename T>
	inline std::string toString(const T& arg)
	{
		std::ostringstream os;
		os << arg;
		return os.str();							// string流类的str()方法——返回其封装的字符串对象。
	}
}

void stdlib_io_module::test3()
{
	using namespace TEST_STRINGSTREAM;
	std::cout << "\n\n\n\n" << std::endl;
	std::cout << "test3: string流" << std::endl;

	// 1. string流对象实现的toString函数：
	int numi1 = 999;
	std::string str = toString(numi1);
	std::cout << str << std::endl;

	std::stringstream ss;

	// 2. 字符串拷贝、拼接、格式化等工作都可以通过sstream来实现，比C语言中方便。

	//			格式化字符串
	for (int i = 1; i < 10; i++) 
	{
		ss << "这是第" << i << "次循环";
		std::cout << ss.str() << std::endl;
		ss.str("");					// 使用空字符串来替代oss流对象的底层字符串。
	}

	//			string对象拼接
	std::string str1, str2;
	str1 = "hahaha";
	str2 = "wawawa";
	ss << str1 << str2;
	str1 = ss.str();
	ss.str("");
	std::cout << str1 << std::endl << std::endl;;

	//			C风格的字符串拼接
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
	std::cout << cstr1 << std::endl;
	std::cout << cstr3 << std::endl;

	// 3. operator>>()返回布尔值，表示当前string流是否为空
	ss.clear();
	ss << "sadf";
	ss << "dfdf,12;";
	ss << "45oi^";
	unsigned elemCount = 0;
	std::list<char>chList;
	char tmpCh = 0;
	while (ss >> tmpCh)				// 逐个提取string流中的字符，直到取空为止；
	{
		chList.push_back(tmpCh);
		elemCount++;
	}
	
	str.clear();
	str.reserve(chList.size());
	for (const auto& ch : chList)
		str.push_back(ch);
	std::cout << "the input string is " << str << std::endl;
	std::cout << "elemCount of the string stream is  " << elemCount << std::endl;

}


// test4: 使用scanf()的返回值进行输入合法检验
void stdlib_io_module::test4()
{
	std::cout << "\n\n\n\n" << std::endl;
	std::cout << "test4: 使用scanf()的返回值进行输入合法检验" << std::endl;


	int inputValid = 0;
	int num;
	std::cout << "请输入一个整数" << std::endl;
	while(0 == inputValid)
	{
		setbuf(stdin, NULL);
		inputValid = scanf("%d", &num);

		if(0 == inputValid)
		{
			std::cout << "输入不合法，请重新输入。" << std::endl;
			setbuf(stdin, NULL);
		}
	}
	std::cout << "输入的整数是" << num << std::endl;
}


void stdlib_io_module::test5() 
{}


void stdlib_io_module::test6()
{}