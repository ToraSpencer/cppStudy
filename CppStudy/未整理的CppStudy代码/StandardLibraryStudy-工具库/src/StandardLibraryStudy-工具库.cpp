#include <typeinfo>
#include <ctime>
#include <chrono>

#include <string>
#include <iostream>

#include <thread>
#include <mutex>
#include <future>
#include <condition_variable>
using namespace std;


void testfuc2(int num){
    int a = 0;
    int num2 = num/2;
    future<void> ft1 = async(launch::async, [&]
    		{for (int i = 0; i != num2; i++) {
            int *b = new int[10]();
            delete [] b;
    		}
    });

    future<void> ft2 = async(launch::async, [&]
		{for (int i = num2; i != num; i++) {
            int *b = new int[10]();
            delete [] b;
        }
    });

    ft1.wait();
    ft2.wait();
}


//<typeinfo>
void test1()
{
	cout << "test1: <typeinfo> :" << endl << endl;

	cout << "typeid()返回type_info类，其中name()方法返回数据类型名：" << endl;
	cout << "type(5).name() = ：" << typeid(5).name() << endl;
	cout << "typeid(3.12).name() = " << typeid(3.12).name() << endl;
	cout << "typeid('c').name() = " << typeid('a').name() << endl;
	cout << "typeid(\"helloWorld\").name() = " << typeid("helloWorld").name() << "	//字符串的本质是字符数组。" << endl;

	int i = 1;
	int* p_i = &i;
	cout << "int i = 1; int* p_i = &i; typeid(p_i).name() = " << typeid(p_i).name() << endl;

	int a[] = {1,2,3};
	cout << "int a[] = {1,2,3}; typeid(a).name() = " << typeid(a).name() << endl;

	int b[2][3] = {{1,2,3},{4,5,6}};
	cout << "int b[2][3] = {{1,2,3},{4,5,6}}; typeid(b).name() = " << typeid(b).name() << endl;

	class testClass{};
	testClass t;
	cout << "class testClass{}; testClass t; typeid(t).name() = " << typeid(t).name() << endl;

	cout << endl;
}

//<ctime>:C风格的时间、日期工具。
void test2()
{
	cout << "<ctime>" << endl << endl;

}

//<chrono>:C++的时间工具。
void test3()
{
	using namespace chrono;

//循环1：
	auto start = system_clock::now();

	long int num = 10000000;
    for (int i = 0; i != num; i++)
    {
        int *b = new int[10]();
        delete [] b;
    }

	auto end   = system_clock::now();
	auto duration = duration_cast<microseconds>(end - start);
	cout <<  "程序1花费了"
	     << double(duration.count()) * microseconds::period::num / microseconds::period::den   << "秒" << endl;


//循环2
	start = system_clock::now();

    int num2 = num >> 1;
    for (int i = 0; i != num2; i++) {
        int *b = new int[10]();
        delete [] b;
    }
    for (int i = num2; i != num; i++) {
        int *b = new int[10]();
        delete [] b;
    }

	end   = system_clock::now();
	duration = duration_cast<microseconds>(end - start);
	cout <<  "程序2花费了"
	     << double(duration.count()) * microseconds::period::num / microseconds::period::den   << "秒" << endl;

//循环3
	start = system_clock::now();

	testfuc2(num);

	end   = system_clock::now();
	duration = duration_cast<microseconds>(end - start);
	cout <<  "程序3花费了"
	     << double(duration.count()) * microseconds::period::num / microseconds::period::den   << "秒" << endl;


}

int main()
{
	//test1();
	//test2();
	test3();






	return 0;
}


