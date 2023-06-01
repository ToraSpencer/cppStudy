#pragma once
#include <iostream>
#include <algorithm>
#include <cstring>					// 标准串操作
#include <iostream>					// 标准流操作
#include <limits>					// 极限
#include <cmath>					// 数据函数
#include <fstream>					// 文件输入输出
#include <cctype>					// 字符处理
#include <ctime>       				// 日期和时间函数
#include <cstdlib>					// 标准库
#include <cstdio>       			// 标准输入输出
#include <iomanip>					// 输入输出流格式设置	
#include <cstdarg> 					// 支持变长函数参数	
#include <cassert>					// 支持断言


#include <vector>
#include <map>
#include <unordered_map>
#include <windows.h>
#include <io.h>
 

// 表示状态的枚举量
enum Status {
	SUCCESS, FAIL, UNDER_FLOW, OVER_FLOW, RANGE_ERROR, DUPLICATE_ERROR,
	NOT_PRESENT, ENTRY_INSERTED, ENTRY_FOUND, VISITED, UNVISITED
};


// 宏定义、常量
#define DEFAULT_SIZE 1000			// 缺省元素个数
#define DEFAULT_INFINITY 1000000	// 缺省无穷大
#define MAX_ERROR_MESSAGE_LEN 100
#define MAX_PATH          260
constexpr float VF_EPS = 0.0001f;
constexpr float VF_EPS_2 = 0.000001f;
constexpr float VF_MAX = 10000.0f;
constexpr float VF_MIN = -10000.0f;


// 从输入流inStream中跳过空格及制表符获取一字符
char GetChar(std::istream &inStream = std::cin);


class Error
{
private:
	char message[MAX_ERROR_MESSAGE_LEN];		// 异常信息

public:
	Error(const char *mes = "一般性异常!");
	~Error(void) {};
	void Show() const;					// 显示异常信息
};


// 交换元素值
template <class ElemType >
void Swap(ElemType &e1, ElemType &e2)
{
	ElemType temp;		// 临时变量
						// 循环赋值实现交换e1, e2
	temp = e1;	e1 = e2;  e2 = temp;
}


// 打印数组
template<class ElemType>
void Display(ElemType elem[], int n)
{
	for (int i = 0; i < n; i++)
	{	// 显示数组elem
		std::cout << elem[i] << "  ";
	}
	std::cout << std::endl;
}


// 打印单个元素
template <class ElemType>
void Write(const ElemType &e)
{
	std::cout << e << "  ";
}


// 模块类的基类
struct virtualModule
{
protected:
	virtual void test0() {}
	virtual void test1() {}
	virtual void test2() {}
	virtual void test3() {}
	virtual void test4() {}
	virtual void test5() {}
	virtual void test6() {}
	virtual void test7() {}

public:
	static virtualModule* p_moduleIns;
	virtual ~virtualModule() = default;
	void run(unsigned testID);
};


// 章节类的抽象基类
struct virtualChap
{
public:
	virtualModule* pm;		// 当前查看的模块的指针，需要让caller可以访问，
							//	to be optimized: 其实更规范的作法是设计成友元，然后依然设置为protected成员
	static virtualChap* p_chapIns;
	virtual ~virtualChap();

	virtual void showModuleList() = 0;
	virtual bool selectModule(const int molEnum) = 0;
	virtual void runTest(const unsigned testID);
	bool isNullModule() const;
};



// 函数子baseTypePrinter——打印基本类型变量
class baseTypePrinter
{
public:
	baseTypePrinter() = default;

	template<typename T>
	void operator()(const T& arg)
	{
		std::cout << arg << "\t";
	}

};



// 函数子pairPrinter————功能是打印pair对象
class pairPrinter
{
private:
	unsigned int count = 0;

public:
	pairPrinter() = default;

	template<typename T1, typename T2>
	void operator()(const std::pair<T1, T2>& p)
	{
		std::cout << "\t(" << p.first << ", " << p.second << ")";
		this->count++;
	}

	unsigned int getCount(void)
	{
		return this->count;
	}

};


// 传入函数子或函数指针遍历stl容器
template<typename T, typename F>
void traverseSTL(T& con, F f)
{
	std::for_each(con.begin(), con.end(), f);
	std::cout << std::endl;
}


// 反向遍历stl容器
template<typename T, typename F>
void revTraverseSTL(T& con, F f)
{
	std::for_each(con.rbegin(), con.rend(), f);
	std::cout << std::endl;
}


// lambda——打印std::cout支持的类型变量。
template <typename T>
auto disp = [](const T& arg)
{
	std::cout << arg << ", ";
};


// 自定义pointer-like字符串类
struct myString
{
private:
	const char*	pc;
public:
	myString() = delete;
	myString(const char* pc0) :pc(pc0) {}
	myString(const myString& str);	// 应该自己实现拷贝构造函数、重载赋值运算符，以实现深拷贝。否则系统分配浅拷贝的拷贝构造函数。

	const char* c_str() const
	{
		return this->pc;
	}
};




//************工作项目中的网格相关的数据结构实现、和函数：
 


//	是否约等于零
inline constexpr bool vf_appro_zero(float r, float dThreshold = VF_EPS) { return r >= -dThreshold && r <= dThreshold; } 

// 是否约等于零
inline constexpr bool vf_appro_zero_2(float  r) { return vf_appro_zero(r, VF_EPS_2); } 


// 三元数组类模板
template< class T >
struct VNVector3
{
	T  x;
	T  y;
	T  z;
	VNVector3() {}
	VNVector3(T ix, T iy, T iz) : x(ix), y(iy), z(iz) {}
	const T& operator[](unsigned i) const { return  ((T*)(&x))[i]; }
	T& operator[](unsigned i) { return  ((T*)(&x))[i]; }
	const T* Ptr() const { return &x; }
	T* Ptr() { return &x; }

	VNVector3< T > operator +(const VNVector3< T >& v) const { return VNVector3< T >(x + v.x, y + v.y, z + v.z); }
	VNVector3< T > operator -(const VNVector3< T >& v) const { return VNVector3< T >(x - v.x, y - v.y, z - v.z); }
	VNVector3< T > operator +() const { return *this; };
	VNVector3< T > operator -() const { return VNVector3< T >(-x, -y, -z); }
	VNVector3< T > operator *(T v) const { return VNVector3< T >(x * v, y * v, z * v); }
	VNVector3< T > operator /(T v) const { return VNVector3< T >(x / v, y / v, z / v); }

	bool operator==(const VNVector3<T>& src) const { return x == src.x && y == src.y && z == src.z; }
	bool operator!=(const VNVector3<T>& src) const { return x != src.x || y != src.y || z != src.z; }
};
using VNVECTOR3UI = VNVector3<unsigned int> ;


// 三维顶点类
typedef struct VFVector3
{
    float x;
    float y;
    float z;
 
    VFVector3();
    VFVector3(float _x, float _y, float _z);
    VFVector3(const float* f);
    VFVector3(const VFVector3& src);
 
    const float* Ptr() const;
    float* Ptr();

    const VFVector3& operator=(VFVector3 const& src); // copy assignment operator  


    const float& operator[](unsigned i) const;
    float& operator[](unsigned i);
    VFVector3& operator += (const VFVector3& v);
    VFVector3& operator -= (const VFVector3& v);
    VFVector3& operator *= (const VFVector3& v);
    VFVector3& operator /= (const VFVector3& v);
    VFVector3& operator *= (float s);
    VFVector3& operator /= (float s);
    friend VFVector3    operator + (const VFVector3& v);
    friend VFVector3    operator - (const VFVector3& v);
    friend VFVector3    operator +  (const VFVector3& x, const VFVector3& v);
    friend VFVector3    operator -  (const VFVector3& x, const VFVector3& v);
 
    void MakeFloor(const VFVector3& cmp);
    void MakeCeil(const VFVector3& cmp);

    VFVector3 operator *  (float s) const;
    VFVector3 operator * (const VFVector3& rhs) const; // 注：非叉积 ,结果：( x1 * x2 , y1 * y2 , z1 * z2 ) ; 
    VFVector3 operator /  (float s) const;

    bool             operator <  (const VFVector3& v) const;
    bool             operator <= (const VFVector3& v) const;
    bool             operator >  (const VFVector3& v) const;
    bool             operator >= (const VFVector3& v) const;
    bool             operator == (const VFVector3& v) const;
    bool             operator != (const VFVector3& v) const;

    friend VFVector3    operator * (float s, const VFVector3& v);
    float      Dot(const VFVector3& v) const; // 点积
    float      AbsDot(const VFVector3& v) const; // |x1*x2| + |y1*y2| + |z1*z2| 
    VFVector3  Cross(const VFVector3& v)     const; // 叉积 
    VFVector3  operator / (const VFVector3& v)  const; // (x1/x2,y1/y2,z1/z2)

    float      Magnitude()                      const; // 模长
    float      SqrMagnitude()                      const; // 模的平方
    VFVector3  Direction()                      const; // 方向, 单位化后的自己
    void        Normalize(); // 单位化
    VFVector3  ToNormal()                      const; // 生成单位化对象
    VFVector3  GetOrthoVector()            const; // 生成一个与自己垂直的向量
    VFVector3  GetOrthoNormal()            const; // 生成一个与自己垂直的单位向量

    bool IsZero(float threshold = VF_EPS_2) const;
    bool IsNormalized(float threshold = VF_EPS_2) const;

    static const VFVector3 ORIGIN;
    static const VFVector3 ZERO;
    static const VFVector3 AXIS_X;
    static const VFVector3 AXIS_Y;
    static const VFVector3 AXIS_Z;
    static const VFVector3 AXIS_NEG_X;
    static const VFVector3 AXIS_NEG_Y;
    static const VFVector3 AXIS_NEG_Z;
    static const VFVector3 UNIT_SCALE;
    static const VFVector3 VTBL[3];
    static const VFVector3 NEG_VTBL[3];
    static const VFVector3 DIR_VTBL[6]; // 用EV_DIR_AXI_TYPE索引
} VFVECTOR3, * LPVFVECTOR3;



template<>
struct std::hash<VFVECTOR3>
{
	size_t operator() (const VFVECTOR3& v) const
	{
		const auto _eps = VF_EPS;
		const auto vx = std::hash<float>()(std::floor(v.x) + std::floor((v.x - std::floor(v.x)) / _eps) * _eps);
		const auto vy = std::hash<float>()(std::floor(v.y) + std::floor((v.y - std::floor(v.y)) / _eps) * _eps);
		const auto vz = std::hash<float>()(std::floor(v.z) + std::floor((v.z - std::floor(v.z)) / _eps) * _eps);
		return (((vx << 1) ^ vy) << 1) + vz;
	}
};


template<>
struct std::equal_to<VFVECTOR3>
{
	bool operator() (const VFVECTOR3& v0, const VFVECTOR3& v1) const
	{
		return (v0 - v1).IsZero(VF_EPS);
	}
};

typedef const VFVECTOR3* LPCVFVECTOR3;



struct VSMesh
{
	std::vector<VFVECTOR3> vVertice;
	std::vector<VNVECTOR3UI> vSurface;

	VSMesh();
	VSMesh(const VSMesh& in);
	VSMesh(VSMesh&& in);
	VSMesh(const char* szPath);
	~VSMesh();

	VSMesh& operator=(const VSMesh& in);
	VSMesh& operator=(VSMesh&& in);

	VSMesh& AddTriangle(const VFVECTOR3& p0, const VFVECTOR3& p1, const VFVECTOR3& p2);
	VSMesh& MergeMesh(const VSMesh& in);
	void RemoveRepeatPoint();

	void PanMove(const VFVECTOR3& offset);
	void Scale(const VFVECTOR3& scaleVal, const VFVECTOR3& scaleCenter = VFVECTOR3::ZERO);
	void Scale(const float scaleVal, const VFVECTOR3& scaleCenter = VFVECTOR3::ZERO);
	void Swap(VSMesh& in);
	void Clear();
	void WriteToFile(const char* szPath, ...) const;
	void LoadFromFile(const char* szPath, ...);

	bool IsEmpty() const;
	VFVECTOR3 GetVertexCenter() const;
	VFVECTOR3 GetAxisMaxPoint() const;
	VFVECTOR3 GetAxisMinPoint() const;

};






 





