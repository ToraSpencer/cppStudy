#pragma once
#include <iostream>
#include <algorithm>
#include <cstring>					// ��׼������
#include <iostream>					// ��׼������
#include <limits>					// ����
#include <cmath>					// ���ݺ���
#include <fstream>					// �ļ��������
#include <cctype>					// �ַ�����
#include <ctime>       				// ���ں�ʱ�亯��
#include <cstdlib>					// ��׼��
#include <cstdio>       			// ��׼�������
#include <iomanip>					// �����������ʽ����	
#include <cstdarg> 					// ֧�ֱ䳤��������	
#include <cassert>					// ֧�ֶ���


#include <vector>
#include <map>
#include <unordered_map>
#include <windows.h>
#include <io.h>
 

// ��ʾ״̬��ö����
enum Status {
	SUCCESS, FAIL, UNDER_FLOW, OVER_FLOW, RANGE_ERROR, DUPLICATE_ERROR,
	NOT_PRESENT, ENTRY_INSERTED, ENTRY_FOUND, VISITED, UNVISITED
};


// �궨�塢����
#define DEFAULT_SIZE 1000			// ȱʡԪ�ظ���
#define DEFAULT_INFINITY 1000000	// ȱʡ�����
#define MAX_ERROR_MESSAGE_LEN 100
#define MAX_PATH          260
constexpr float VF_EPS = 0.0001f;
constexpr float VF_EPS_2 = 0.000001f;
constexpr float VF_MAX = 10000.0f;
constexpr float VF_MIN = -10000.0f;


// ��������inStream�������ո��Ʊ����ȡһ�ַ�
char GetChar(std::istream &inStream = std::cin);


class Error
{
private:
	char message[MAX_ERROR_MESSAGE_LEN];		// �쳣��Ϣ

public:
	Error(const char *mes = "һ�����쳣!");
	~Error(void) {};
	void Show() const;					// ��ʾ�쳣��Ϣ
};


// ����Ԫ��ֵ
template <class ElemType >
void Swap(ElemType &e1, ElemType &e2)
{
	ElemType temp;		// ��ʱ����
						// ѭ����ֵʵ�ֽ���e1, e2
	temp = e1;	e1 = e2;  e2 = temp;
}


// ��ӡ����
template<class ElemType>
void Display(ElemType elem[], int n)
{
	for (int i = 0; i < n; i++)
	{	// ��ʾ����elem
		std::cout << elem[i] << "  ";
	}
	std::cout << std::endl;
}


// ��ӡ����Ԫ��
template <class ElemType>
void Write(const ElemType &e)
{
	std::cout << e << "  ";
}


// ģ����Ļ���
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


// �½���ĳ������
struct virtualChap
{
public:
	virtualModule* pm;		// ��ǰ�鿴��ģ���ָ�룬��Ҫ��caller���Է��ʣ�
							//	to be optimized: ��ʵ���淶����������Ƴ���Ԫ��Ȼ����Ȼ����Ϊprotected��Ա
	static virtualChap* p_chapIns;
	virtual ~virtualChap();

	virtual void showModuleList() = 0;
	virtual bool selectModule(const int molEnum) = 0;
	virtual void runTest(const unsigned testID);
	bool isNullModule() const;
};



// ������baseTypePrinter������ӡ�������ͱ���
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



// ������pairPrinter�������������Ǵ�ӡpair����
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


// ���뺯���ӻ���ָ�����stl����
template<typename T, typename F>
void traverseSTL(T& con, F f)
{
	std::for_each(con.begin(), con.end(), f);
	std::cout << std::endl;
}


// �������stl����
template<typename T, typename F>
void revTraverseSTL(T& con, F f)
{
	std::for_each(con.rbegin(), con.rend(), f);
	std::cout << std::endl;
}


// lambda������ӡstd::cout֧�ֵ����ͱ�����
template <typename T>
auto disp = [](const T& arg)
{
	std::cout << arg << ", ";
};


// �Զ���pointer-like�ַ�����
struct myString
{
private:
	const char*	pc;
public:
	myString() = delete;
	myString(const char* pc0) :pc(pc0) {}
	myString(const myString& str);	// Ӧ���Լ�ʵ�ֿ������캯�������ظ�ֵ���������ʵ�����������ϵͳ����ǳ�����Ŀ������캯����

	const char* c_str() const
	{
		return this->pc;
	}
};




//************������Ŀ�е�������ص����ݽṹʵ�֡��ͺ�����
 


//	�Ƿ�Լ������
inline constexpr bool vf_appro_zero(float r, float dThreshold = VF_EPS) { return r >= -dThreshold && r <= dThreshold; } 

// �Ƿ�Լ������
inline constexpr bool vf_appro_zero_2(float  r) { return vf_appro_zero(r, VF_EPS_2); } 


// ��Ԫ������ģ��
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


// ��ά������
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
    VFVector3 operator * (const VFVector3& rhs) const; // ע���ǲ�� ,�����( x1 * x2 , y1 * y2 , z1 * z2 ) ; 
    VFVector3 operator /  (float s) const;

    bool             operator <  (const VFVector3& v) const;
    bool             operator <= (const VFVector3& v) const;
    bool             operator >  (const VFVector3& v) const;
    bool             operator >= (const VFVector3& v) const;
    bool             operator == (const VFVector3& v) const;
    bool             operator != (const VFVector3& v) const;

    friend VFVector3    operator * (float s, const VFVector3& v);
    float      Dot(const VFVector3& v) const; // ���
    float      AbsDot(const VFVector3& v) const; // |x1*x2| + |y1*y2| + |z1*z2| 
    VFVector3  Cross(const VFVector3& v)     const; // ��� 
    VFVector3  operator / (const VFVector3& v)  const; // (x1/x2,y1/y2,z1/z2)

    float      Magnitude()                      const; // ģ��
    float      SqrMagnitude()                      const; // ģ��ƽ��
    VFVector3  Direction()                      const; // ����, ��λ������Լ�
    void        Normalize(); // ��λ��
    VFVector3  ToNormal()                      const; // ���ɵ�λ������
    VFVector3  GetOrthoVector()            const; // ����һ�����Լ���ֱ������
    VFVector3  GetOrthoNormal()            const; // ����һ�����Լ���ֱ�ĵ�λ����

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
    static const VFVector3 DIR_VTBL[6]; // ��EV_DIR_AXI_TYPE����
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






 





