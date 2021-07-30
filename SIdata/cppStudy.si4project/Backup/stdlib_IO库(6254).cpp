#include <iosfwd>
#include <ios>
#include <istream>
#include <ostream>
#include <iostream>
#include <fstream>
#include <sstream>				// �ַ�����ͷ�ļ�
//#include <syncstream>				// C++20��
#include <iomanip>
#include <streambuf>
#include <string>
#include <typeinfo>

#include "stdlib_IO��.h"


#include <cstdio>




#ifdef linux
#include <cstrubg>				// ��Ҫʹ��stderror()����
#endif



#define EPS 1e-10					//����ǳ�С��һ����EPSilon�������������������ֵʱ����Ϊ0
#define PI 3.14159



// ֪ʶ��
/*
	���õĸ�ʽ�����ݷ�
			setiosflags()			ʹ�ö���ö�ٳ������趨�����ʽ��
			setw()					���ÿ��
			setprecision()			���ø��������ȡ�
			hex						��ʮ��������ʽ�������
			fixed					����ͨС����ʽ���������
			scientific				�Կ�ѧ��������ʽ���������
			left					����룬���ڿ�Ȳ���ʱ������ַ���ӵ��ұߡ�Ĭ���������Ҷ��롣



	C++����Ҫ�ļ���������
			cin��������istream��
							�ӱ�׼�����ȡ���ݡ�
							
			std::cout��������ostream��
					�ӱ�׼���д�����ݡ�
					
			cerr��������ostream��
					����������������Ϣ��д�뵽��׼����
					
			clog��������ostream��
					������cerr�������л��壬��������ʱ�������


	C����Ҫ�ļ���������
			stdin
			stdout
			stderr


	C��IO��صĺ���
			scanf()					�ӱ�׼����stdin�����̣���ȡ��ʽ����������
			printf()				���ݸ�ʽ���������׼���stdout����Ļ���ϡ�
			fprintf()				���ݸ�ʽ�����뵽�������С�
			strerror()			���մ���Ų����ڲ�����������������һ��ָ�������Ϣ�ַ�����ָ�롣���ɵĴ����ַ���ȡ���ڿ���ƽ̨�ͱ�������


	C++IO���͵��ص�
			���󲻿��Ը�ֵ����ֵ

			�����ܴ���������

			�����βκͷ��ص�һ�㶼�������͵����ã������Ƕ��󡣶����Ƿ�const�����ã���Ϊ��дһ���������ı���״̬��
						���͵����Ӿ����ڶ�������/���������>>/<<������������ص�ʱ�򣬷������������á�
						������	istream& operator>>(istream& is, Complex& cc);	



	������
				ÿ�����������������һ����������
				�����������ã���������д�����ݡ�
				��������ᵼ�»�����ˢ�£�
						1. ��������������
						2. ����������
						3. ʹ��std::endl��flush�Ȳ��ݷ���ˢ�¡�
				������Ҫ�Ĳ��ݷ�
						std::endl
						ends
						flush
						unitbuf


	cin�������Ҫ������
				cin.get() 						//һ��ֻ�ܶ�ȡһ���ַ�
				cin.get(һ������) 				//��һ���ַ�
				cin.get(��������) 				//���Զ��ַ���
				cin.getline()					// ��cin�����ж�һ�У����뵽string�����С�
				cin.ignore()
				cin.putback()


	fstream��ļ�����Ҫ����
				���ֹ��캯��
								fstream(str);					// str���ļ�·��
								fstream(str, mode);		// mode�Ǵ�ģʽ
											in	�Զ��ķ�ʽ��
											out	��д�ķ�ʽ��
											app	ÿ��д����ǰ����λ���ļ�ĩβ
											ate	���ļ���������λ���ļ�ĩβ
											trunc	�ض��ļ�
											binary	�Զ����Ʒ�ʽ����IO������
				open()
				close()
				is_open()
								����һ��boolֵ��˵���ļ��Ƿ�ɹ��򿪲�����δ�رա�

	string���ࡪ��stringstream
				������string�����������ݣ����߽���string������������ݡ�
				��Ҫ����
							str()
										����1				str(void)��������stringstream�����ڷ�װ��string����
										����2				str(str1)�������ַ���str1���󿽱�����ǰstringstream�����С�
										Ӧ��				����Ӧ��stringstream����������������ת��Ϊstring.


*/


// δ����ĺ���ԭ��
/*
		int scanf(const char *format, ...) 
		
		int printf(const char *format, ...)
		
		int fprintf(FILE *stream, const char *format, ...)
		
		char *strerror(int errnum)
					��ͷ�ļ�<string.h>�ж���
/*





// ������Բ���Ҫ��֪ʶ��
/*
		IO��ͷ�ļ���
					<iosfwd>			����IO�е����ǰ������
					<ios> 				std::std::ios_base �ࡢ	std::basic_ios ��ģ�塢 ���� typedef
					<istream> 		std::basic_istream ��ģ�塢 ���� typedef
					<ostream> 		std::basic_ostream�� std::basic_iostream ��ģ�塢	���� typedef
					<iostream>		������׼������
					<fstream> 		std::basic_fstream�� std::basic_ifstream��	std::basic_ofstream ��ģ�塢	����typedef
					<sstream> 		std::basic_stringstream��	std::basic_istringstream�� std::basic_ostringstream ��ģ�塢 ���� typedef
					<syncstream>	(C++20 ��) std::basic_osyncstream�� std::basic_syncbuf�� һЩtypedef
					<strstream> 	(C++98 ������)  
					<iomanip> 		����IO��ʽ�ĸ�������
					<streambuf> 		std::basic_streambuf ��ģ��
					<cstdio>			C ��������������


		IO���е��ࣺ
					ifstream
							��������<fstream>
							�����ļ�������

					ofstream
							��������<fstream>
							����ļ�������

					fstream
							��������<fstream>
							��������ļ�������
							���Զ�Ҳ����д
							
					��ļ̳й�ϵ��
							istream �� ifstream
									�� istringstream

					

*/



virtualModule* stdlib_io_module::getInstance()		// �̲߳���ȫ�ĵ���ģʽ
{
	if (nullptr != p_moduleIns)
	{
		delete p_moduleIns;
	}
	p_moduleIns = new stdlib_io_module;
	return p_moduleIns;
}

 
 


// test0: <iomanip>�еĲ��ݷ�(manipulator)�����������ʽ��
void stdlib_io_module::test0(void)
{
	double d1, d2, d3;
	d1 = 3.1415926;
	d2 = 232.2345;
	d3 = 90989.111;

	std::cout << "\n\n\n\n" << std::endl;
	std::cout << "test0: <iomanip>�еĲ��ݷ�(manipulator)�����������ʽ��" << std::endl;


	// setw()��std::cout.width()��������ָ������������Ŀ�ȣ����������Զ����ո�Ĭ���Ҷ��롣
	std::cout << std::setw(10) << d1 << std::endl;
	std::cout.width(10);								// ���һ�κ���趨��ʧЧ
	std::cout << d2 << std::endl;
	std::cout.width(10);
	std::cout << d3 << std::endl;
	std::cout << std::endl << std::endl;


	// setiosflags()��������ʹ�ö���ö�ٳ������趨�����ʽ��
	std::cout << "������ʽ����std::ios_base::left" << std::endl;
	std::cout << std::setiosflags(std::ios_base::left) << std::setw(20) << d1 << std::endl;			// ���������
	std::cout << std::setw(20)<< d2 << std::endl;
	std::cout << std::resetiosflags(std::ios_base::left) << std::setw(20) << d3 << std::endl;			// ����һ�κ�һֱ��Ч����Ҫ�ֶ�����
	std::cout << "����ǰ�����š���std::ios_base::showpos" << std::endl;
	std::cout << std::setiosflags(std::ios_base::showpos) << 1234 << std::endl;
	std::cout << resetiosflags(std::ios_base::showpos);							// �ֶ�������ʽ
	std::cout << std::endl << std::endl;


	// setprecision()�����������ø��������ȣ�
	std::cout << "setprecision()�����������ø��������ȣ�" << std::endl;
	std::cout << std::setprecision(1) << d2 << std::endl;					// ��ʱsetprecision()���õ�����Ч����λ����λ��������ʱĬ��ʹ�ÿ�ѧ������std::ios_base::scientific
	std::cout << setiosflags(std::ios_base::fixed) << std::setprecision(1) << d2 << std::endl;
																					// ָ�����������std::ios_base::fixed���ʱ��setprecision���õ���С�������λ����


}


// test1���ļ����ࡪ��ifstream, ofstream
namespace TEST_FILESTREAM 
{
	struct myDate
	{
		int year, month, day;
	};


}

void stdlib_io_module::test1(void)
{
	// �������롢����ļ������󡣳�����ļ��Ķ������룬д�����
	//		����������������������Գ�����ӽ������ģ���������׼�������д����std::cout <<..���ļ�������д������еı�����file>>arg
	//		���ϱ�̹淶��д����ֻд���·������д����·����
	//		std::ios_base::binary ָ����ģʽΪ�����ƣ���ָ���Ļ�Ĭ��Ϊ�ı�ģʽ
	//		std::ios_base::out�������ģʽ��û���ļ��򴴽��ļ������ļ�������ļ����ݡ�
	//		std::ios_base::app����׷��ģʽ����append��дʱ�����ԭ�����ݣ���ĩβ��ʼд��
	using namespace TEST_FILESTREAM;

	std::ofstream writeFile1("test1.xxx");
	std::ofstream writeFile2("test2.xxx", std::ios_base::out|std::ios_base::binary);
	std::ofstream writeTextFile("myText.txt", std::ios_base::out);
	std::ifstream readFile1("test1.xxx");
	std::ifstream readFile2("test2.xxx", std::ios_base::in|std::ios_base::binary);

	std::string str1 = "hello world";
	std::string str11;
	int inum1 = 2019;
	float fnum1 = 2019.4;
	char str2[100];

	std::cout << "\n\n\n\n" << std::endl;
	std::cout << "test1: ʹ��ifstream, ofstream��д�ļ�	" << std::endl;

	// 1. fstream������!�����������һ��bool�������ж��ļ�����Ƿ�򿪳ɹ���
	std::fstream testFile("E:/asdfasdfasdf.yuiu", std::ios_base::in);
	if (!testFile) 
	{
		std::cout << "�ļ����testFile��ʧ�ܡ�" << std::endl;
	}


	// 2. д�������ļ�

	//			2.1 �������ͱ�������������write()����д�룬��ʹ�����ص�������������
	writeFile1 << str1 << inum1 << fnum1 << std::endl;
	writeFile1.close();					// ����������֮��Ҫ�ر��ļ���


	//			2.2 �Զ������ͱ�������write()����д�룬��ʹ�����ص�������������

	// write()����
	/*
		basic_ostream& write( const char_type* s,		��д������ݵ�ͷ��ָ�룬ǿתΪchar*
						  std::streamsize count			��д�������ֽ�����
							)
							
		����������д�Զ���ṹ��ʵ����������д����󣻣�����Ϊʲô��
	*/
	myDate dt = {2020, 3, 15};
	writeFile2.write(reinterpret_cast<char*>(&dt), sizeof(dt));
	writeFile2.close();

	
	// 3. д�ı��ļ�
	writeTextFile<< str1<<inum1<<fnum1;
	


	// 4. ���ļ���

	//		4.1 getline()�����������������ж�ȡ���ݴ洢���ַ�����
	/*
		basic_istream& getline( char_type* s, 
							std::streamsize count 
							);
					
	*/
	readFile1.getline(str2,30);
	std::ifstream readTextFile("myText.txt", std::ios_base::in);
	readTextFile>>str11;		// ֱ���������������
	std::cout << str2 << std::endl;
	readFile1.close();


	//		4.2 read()�������������������ļ��ж�ȡ���ݡ�
	/*
		basic_istream& read( char_type* s,					���ն�ȡ���ݵı�����ͷ��ָ�룬ǿתΪchar*	
						   std::streamsize count			��ȡ������ֽ�����
							);
	*/
	myDate dt_input;
	readFile2.read(reinterpret_cast<char*>(&dt_input), sizeof(dt_input));
	std::cout << "������"<< dt_input.year << "-" << dt_input.month << "-"<< dt_input.day << std::endl;
	readFile2.close();

}	



// test2: ʹ��cin�������������룺
void stdlib_io_module::test2(void)
{
	std::cout << "\n\n\n\n" << std::endl;
	std::cout << "test2: ʹ��cin��������������" << std::endl;


	// ��ȡ�����">>"��������ȡcin�����е�����
	int numi1;
	std::cout << "������һ������" << std::endl;
	std::cin >> numi1;
	std::cout << "����������ǣ�" << numi1 << std::endl;
	std::cout << std::endl << std::endl;
	
	

	// cin.get()��������������>>������>>�ܾ����ܿո�get()����
	setbuf(stdin, NULL);					// ��ջ�����
	std::cout << "������һ���ַ�������q������" << std::endl;
	char ch;
	while ((ch = std::cin.get()) != 'q')
	{
		std::cout.put(ch);
	}
	setbuf(stdin, NULL);					// ��ջ�����
	std::cin.clear();
	std::cout << std::endl << std::endl;


	// getline()��������cin�ж�ȡһϵ���ַ������ҿ���������ֹ�ַ������ҿ��Դ���string����
	std::string str;
	std::cout << "������һ���ַ�������p����" << std::endl;
	std::getline(std::cin, str, 'p');					// ��cin�ж�ȡһϵ���ַ�������str������p����
	std::cin.clear();
	setbuf(stdin, NULL);					// ��ջ�����
	std::cout << "������ַ���Ϊ��"<< str << std::endl;



}



// test3: string��
namespace TEST_STRINGSTREAM
{
	template<typename T>
	inline std::string toString(const T&);					// string������ʵ�ֵĽ���������ת��Ϊstring���͵ĺ���

	template <typename T>
	inline std::string toString(const T& arg)
	{
		std::ostringstream os;
		os << arg;
		return os.str();							// string�����str()���������������װ���ַ�������
	}
}

void stdlib_io_module::test3(void)
{
	using namespace TEST_STRINGSTREAM;
	std::cout << "\n\n\n\n" << std::endl;
	std::cout << "test3: string��" << std::endl;


	// string������ʵ�ֵ�toString������
	int numi1 = 999;
	std::string str = toString(numi1);
	std::cout << str << std::endl;


	std::stringstream ss;
	// �ַ���������ƴ�ӡ���ʽ���ȹ���������ͨ��sstream��ʵ�֣���C�����з��㡣
	//		��ʽ���ַ���
	for (int i = 1; i < 10; i++) 
	{
		ss << "���ǵ�" << i << "��ѭ��";
		std::cout << ss.str() << std::endl;
		ss.str("");					// ʹ�ÿ��ַ��������oss������ĵײ��ַ�����
	}

	// string����ƴ��
	std::string str1, str2;
	str1 = "hahaha";
	str2 = "wawawa";
	ss << str1 << str2;
	str1 = ss.str();
	ss.str("");
	std::cout << str1 << std::endl << std::endl;;

	// C�����ַ���ƴ��
	char cstr1[50] = "hahaha";
	char cstr2[50] = "wawawa";
	char cstr3[50] = "1";
	ss << cstr1 << cstr2;
	ss >> cstr1;				// c�����ַ���������ʹ��"="��ֵ��c������ʹ��strcpy();
	// ��������������������������ss����ʧЧ״̬���������clear()���������ٴ�ʹ�á�
	ss.clear();				// clear()��������ʹ���������´�����Ч״̬��
	ss << cstr1;
	ss >> cstr3;
	ss.str("");
	std::cout << cstr1 << std::endl;
	std::cout << cstr3 << std::endl;
}


// test4: ʹ��scanf()�ķ���ֵ��������Ϸ�����
void stdlib_io_module::test4(void)
{
	std::cout << "\n\n\n\n" << std::endl;
	std::cout << "test4: ʹ��scanf()�ķ���ֵ��������Ϸ�����" << std::endl;


	int inputValid = 0;
	int num;
	std::cout << "������һ������" << std::endl;
	while(0 == inputValid)
	{
		setbuf(stdin, NULL);
		inputValid = scanf("%d", &num);

		if(0 == inputValid)
		{
			std::cout << "���벻�Ϸ������������롣" << std::endl;
			setbuf(stdin, NULL);
		}
	}
	std::cout << "�����������" << num << std::endl;
}


void stdlib_io_module::test5(void) 
{}


void stdlib_io_module::test6(void)
{}