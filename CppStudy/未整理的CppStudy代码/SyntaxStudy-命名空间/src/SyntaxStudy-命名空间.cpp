#include <iostream>
#include <string>
#include <opencv2/opencv.hpp>
#include <cmath>
#include <complex>

namespace na
{
	void cout()
	{
		std::cout << "this is a function from na name space." << std:: endl;
	}

	void fun1();

	void fun2();
	//命名空间内写函数的实现：
	void fun2(){std::cout << "this is fun2() from na namespace;" << std::endl;}


}


//命名空间外写函数的实现。
void na::fun1(){std::cout << "this is fun1() from na namespace" << std::endl;}



namespace cv
{
	void cos()
	{
		std::cout << "this is cos function from cv namespace." << std::endl;
	}


	cv::Mat_<double> sin()
	{
		cv::Mat_<double> temp = cv::Mat_<double>::ones(3,3);
		return temp;
	}



}

int main()
{
	na::cout();

	std::cout << "cos(1) = " << std::cos(1) << std::endl;
	std::cout << "cv::cos()" << std::endl;
	cv::cos();
	std::cout  << std::endl;


	cv::Mat_<double> a = cv::sin();
	std::cout << "cv::sin() = \n" << a << std::endl;
	std::cout  << std::endl;


	std::complex<double> z(1,2);
	std::cout << "z(1,2) = " << z << std::endl;
	std::cout  << std::endl;




	return 0;
}
