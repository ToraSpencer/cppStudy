#ifndef SHAPES_H_
#define SHAPES_H_

#include <iostream>
#include <string>
#include <cmath>
#include <typeinfo>

#include <cstdio>

#define PI 3.14159




// .hpp文件
/*
    1、是Header Plus Plus 的简写。
    2、与*.h类似，hpp是C++程序头文件 。
    3、是VCL 专用的头文件,已预编译。
    4、是一般模板类的头文件。
    5、一般来说，*.h里面只有声明，没有实现，而*.hpp里声明实现都有，后者可以减 少.cpp的数量。
    6、*.h里面可以有using namespace std，而*.hpp里则无。

    a)不可包含全局对象和全局函数
    由于hpp本质上是作为.h被调用者include，所以当hpp文件中存在全局对象或者全局函数，而该hpp被多个调用者include时，将在链接时导致符号重定义错误。要避免这种情况，需要去除全局对象，将全局函数封装为类的静态方法。

    b)类之间不可循环调用
    在.h和.cpp的场景中，当两个类或者多个类之间有循环调用关系时，只要预先在头文件做被调用类的声明即可，

    c)不可使用静态成员
    静态成员的使用限制在于如果类含有静态成员，则在hpp中必需加入静态成员初始化代码，当该hpp被多个文档include时，将产生符号重定义错误。唯 一的例外是const static整型成员，因为在vs2003中，该类型允许在定义时初始化，如：
*/




// 本头文件用于OOP的学习——虚函数、抽象类（接口）、虚继承、多态。
//							关键字virtual, final, override,
/*
**	虚函数：
**			带有virtual关键字修饰的类成员函数。
**			基类中成员函数可以分为两类：
**					1. 希望直接被子类继承的成员函数
**					2. 希望子类覆盖的函数——这种函数一般都设置成虚函数。
**			只有类中的函数声明前可以加virtual，类外不可使用。
**			类的构造函数不可以加virtual，析构函数可以。
**			当使用基类指针来调用一个虚函数的时候，执行动态绑定——只有运行的时候才能知道执行的是哪个版本的虚函数，取决于指针指向了什么类型的对象。
**			当不希望动态绑定的时候，可以使用作用域运算符。
**
**
**
**
**	纯虚函数：
**			在类成员函数声明之后加" = 0;" 代表这是一个纯虚函数。
**			纯虚函数一般不写定义。
**			纯虚函数的意义是设定一个接口，起到一个规范的作用，规定子类中必须要是实现这个函数。
**
**	抽象类（接口）：
**			含有纯虚函数的类，不能被实例化。
**			作用是给其子类提供接口，继承之后子类可以覆盖这些接口。
**
**	多态：
**			体现出多态的根本原因，是引用或指针的静态类型与动态类型不同。
**
**	override关键字（c++11）
**			写在某个类成员函数声明之后，标志该函数覆盖了基类中的同名虚函数。
**			若未覆盖成功，编译会报错。
**
*/


/***************************************************************************
***************************************************************************/
// 前置声明(forward declaration)
 


/***************************************************************************
***************************************************************************/
// extern变量


/***************************************************************************
***************************************************************************/
// extern函数：
 

/***************************************************************************
***************************************************************************/
// 自定义类的声明：


// Shape类——所有图形的抽象基类
/*. BC------------------------------------------------------------------------
**	Shape类——所有图形的抽象基类
**	
**	描述：
**			给出了具体形状类的抽象基类，定义了基础的一些接口。
*. EC------------------------------------------------------------------------
*/
class Shape
{
public: 
    virtual ~Shape(void) = default;                           // 最好把基类的析构函数设为virtual
    virtual float area(void) const;                      // 求图形的表面积
    virtual float volume(void) const;                    // 求图形的体积
    virtual void shapeName(void) const = 0;             // 输出图形的名称。
};				 
 

// Point类
/*. BC------------------------------------------------------------------------
**	 
**	
**	描述：
**			给出了具体形状类的抽象基类，定义了基础的一些接口。
*. EC------------------------------------------------------------------------
*/
class Point:public Shape
{
public:
    // 友元
    friend std::ostream& operator<<(std::ostream&, const Point&);
    
    // 构造、析构函数：
    Point(float = 0, float = 0);                    // !!!
    ~Point(void);
    
    // get/set方法
    void set(float, float);
    float getX(void) const;
    float getY(void) const;

    // 其他方法： 
    virtual void shapeName(void) const;                   // 写virtual是为了提醒开发者：该函数被继承的时候，应该被重写覆盖。

protected:
    // protected成员数据
    float x,y;    

};



// Square类
/*. BC------------------------------------------------------------------------
**	 
**	
**	描述：
**			 
*. EC------------------------------------------------------------------------
*/
class Square:public Point
{
public:
    // 友元：
    friend std::ostream& operator<<(std::ostream&, const Square&);

    // 构造、析构函数：
    Square(float = 0, float = 0, float = 0);
    ~Square(void);

    // get/set方法：
    float getLength(void) const;
    void setLength(float);

    // 其他方法：
    virtual void shapeName(void) const;
    virtual float area(void) const;                       
 
protected:
    float length;

};



// Cube类
/*. BC------------------------------------------------------------------------
**	 
**	
**	描述：
**			 
*. EC------------------------------------------------------------------------
*/
class Cube: public Square
{
public:
    // 友元
    friend std::ostream& operator<<(std::ostream&, const Cube&);

    // 构造、析构函数
    Cube(float = 0, float = 0, float = 0);
    ~Cube(void);
    
    // get/set方法

    // 其他方法
    virtual void shapeName(void) const;
    virtual float area(void) const;                       
    virtual float volume(void) const; 

protected:

};



 

/***************************************************************************
***************************************************************************/
// 函数声明：
std::ostream& operator<<(std::ostream&, const Point&);
std::ostream& operator<<(std::ostream&, const Square&);
std::ostream& operator<<(std::ostream&, const Cube&);




/***************************************************************************
***************************************************************************/
// 自定义类的实现：
float Shape::area(void) const                      // 求图形的表面积
{
    return 0;
}



float Shape::volume(void) const                     // 求图形的体积
{
    return 0;
}  



Point::Point(float x0, float y0):x(x0),y(y0)            // 使用初始化列表来初始化
{

}


Point::~Point(void)
{
    std::cout << "A Point object has been eliminated." << std::endl;

}
 
void Point::set(float x0, float y0)
{
    this->x = x0;
    this->y = y0;      
}  



float Point::getX(void) const
{   
    return this->x;

}



float Point::getY(void) const
{
    return this->y;
}



void Point::shapeName(void) const
{
    std::cout << "this is a point." << std::endl;
}




Square::Square(float x0, float y0, float length0):Point(x0, y0),length(length0)
{}


Square::~Square(void)
{
    std::cout << "A Square object has been eliminated." << std::endl;
}


float Square::getLength(void) const
{
    return this->length;
}

void Square::setLength(float length0)
{
    length = length0;

}
 
void Square::shapeName(void) const
{
    std::cout << "This is a square." << std::endl;
}

float Square::area(void) const
{   
    return (this->length)*(this->length);
}


Cube::Cube(float x0, float y0, float length0):Square(x0,y0,length0)
{

}

Cube::~Cube(void)
{
    std::cout << "A Cube object has been eliminated." << std::endl;
}

void Cube::shapeName(void) const
{
    std::cout << "This is a cube." << std::endl;

}

float Cube::area(void) const
{
    return (this->length)*(this->length);
}

float Cube::volume(void) const
{
    return (this->area())*(this->length);
}




/***************************************************************************
***************************************************************************/
// 函数的实现：
std::ostream& operator<<(std::ostream& os, const Point& p)
{
    os << "(" << p.x <<", " << p.y <<")";
    return os;

}



std::ostream& operator<<(std::ostream& os, const Square& s)
{
    os << "(" << s.x <<", " << s.y <<")" << "; length == " << s.length;
    return os;
}



std::ostream& operator<<(std::ostream& os, const Cube& c)
{
    os << "(" << c.x <<", " << c.y <<")" << "; length == " << c.length;
    return os;
}



#endif		// VECTOR_HPP_