#include "basicTools.h"


// 从输入流inStream中跳过空格及制表符获取一字符
char GetChar(std::istream &inStream)
{
	char ch;
	while ((ch = (inStream).peek()) != EOF	// 文件结束符(peek()函数从输入流中接受1字符,流的当前位置不变)
		&& ((ch = (inStream).get()) == ' '	// 空格( get()函数从输入流中接受1字符,流的当前位置向后移1个位置)
			|| ch == '\t'));
	return ch;
}




// 由mes构构通用异常对象
Error::Error(const char *mes)
{
	strcpy_s(message, mes);				// 复制异常信息
}


//  显示异常信息
void Error::Show()const
{
	std::cout << message << std::endl;			// 显示异常信息	
}


virtualModule* virtualModule::p_moduleIns = nullptr;


void virtualModule::run(unsigned testID)
{
	switch (testID)
	{
	case 0:
		test0();
		break;
	case 1:
		test1();
		break;
	case 2:
		test2();
		break;
	case 3:
		test3();
		break;
	case 4:
		test4();
		break;
	case 5:
		test5();
		break;
	case 6:
		test6();
		break;
	case 7:
		test7();
		break;
	default:
		break;
	}
}


virtualChap* virtualChap::p_chapIns = nullptr;


virtualChap::~virtualChap()
{
	// std::cout << "调用了chap系列类的的析构函数" << std::endl;
	if (this->pm != nullptr)
	{
		delete this->pm;
		this->pm = nullptr;
	}
}


void virtualChap::runTest(const unsigned testID)
{
	if (nullptr == this->pm)
	{
		std::cout << "当前没有确定任何模块" << std::endl;
		return;
	}
	this->pm->run(testID);
}


bool virtualChap::isNullModule() const
{
	if (nullptr == this->pm) 
		return true;
	else 
		return false;
}


myString::myString(const myString& str)                                // ！！！类数据中有指针式，应该自己实现拷贝构造函数、重载赋值运算符，以实现深拷贝。否则系统分配浅拷贝的拷贝构造函数。
{
	const char* cStr = str.c_str();
	int size = strlen(cStr) + 1;

	char* tempStr = new char[size];
	strcpy_s(tempStr, size ,cStr);
	this->pc = tempStr;
}




unsigned ReadNextValidData(char*& pszBuf, unsigned& nCount, char* validData, const unsigned nMaxSize)
{
	unsigned nIndx = 0;

	while ((pszBuf[0] == ' ') ||
		(pszBuf[0] == '\n') ||
		(pszBuf[0] == '\t') ||
		(pszBuf[0] == '\r'))
	{
		pszBuf++;
		nCount++;
	}

	while ((pszBuf[0] != ' ') &&
		(pszBuf[0] != '\n') &&
		(pszBuf[0] != '\t') &&
		(pszBuf[0] != '\r') &&
		(pszBuf[0] != '\null') &&
		(pszBuf[0] != 0) &&
		(nIndx < nMaxSize))
	{
		validData[nIndx++] = pszBuf[0];
		pszBuf++;
		nCount++;
	}
	validData[nIndx] = 0;
	return nIndx;
}


void OBJReadFile(std::vector<VFVECTOR3>& vVerts, std::vector<VNVECTOR3UI>& vSurfs, const char* pszFileName)
{
	char* pTmp = NULL;
	std::ifstream ifs(pszFileName);//cube bunny Eight
	if (false == ifs.is_open())
	{
		return;
	}
	std::streampos   pos = ifs.tellg();     //   save   current   position   
	ifs.seekg(0, std::ios::end);
	unsigned fileLen = (unsigned)ifs.tellg();
	if (0 == fileLen)
		return;

	ifs.seekg(pos);     //   restore   saved   position   
	char* pFileBuf = new char[fileLen + 1];
	std::memset(pFileBuf, 0, fileLen + 1);
	ifs.read(pFileBuf, fileLen);
	char tmpBuffer[1024];
	unsigned nMaxSize = 1024;
	pTmp = pFileBuf;
	unsigned nReadLen = 0;
	unsigned nRet = 0;

	while (nReadLen < fileLen)
	{
		nRet = ReadNextValidData(pTmp, nReadLen, tmpBuffer, nMaxSize);
		if (0 == nRet)
			break;
		// 顶点信息		
		if (std::strcmp(tmpBuffer, "v") == 0)
		{
			VFVECTOR3 vert;
			nRet = ReadNextValidData(pTmp, nReadLen, tmpBuffer, nMaxSize);
			if (0 == nRet)
				break;
			vert.x = (float)atof(tmpBuffer);
			nRet = ReadNextValidData(pTmp, nReadLen, tmpBuffer, nMaxSize);
			if (0 == nRet)
				break;
			vert.y = (float)atof(tmpBuffer);
			nRet = ReadNextValidData(pTmp, nReadLen, tmpBuffer, nMaxSize);
			if (0 == nRet)
				break;
			vert.z = (float)atof(tmpBuffer);
			vVerts.push_back(vert);
		}
		else if (std::strcmp(tmpBuffer, "f") == 0)
		{
			VNVECTOR3UI surf;
			nRet = ReadNextValidData(pTmp, nReadLen, tmpBuffer, nMaxSize);
			if (0 == nRet)
				break;
			surf.x = atoi(tmpBuffer) - 1;
			nRet = ReadNextValidData(pTmp, nReadLen, tmpBuffer, nMaxSize);
			if (0 == nRet)
				break;
			surf.y = atoi(tmpBuffer) - 1;

			nRet = ReadNextValidData(pTmp, nReadLen, tmpBuffer, nMaxSize);
			if (0 == nRet)
				break;
			surf.z = atoi(tmpBuffer) - 1;
			vSurfs.push_back(surf);
		}
	}
	delete[] pFileBuf;
}

 
inline
VFVector3::VFVector3()
{
}

inline
VFVector3::VFVector3(float _x, float _y, float _z)
	:x(_x), y(_y), z(_z)
{
}

inline
VFVector3::VFVector3(const float* f)
{
	x = f[0];
	y = f[1];
	z = f[2];
}

inline
VFVector3::VFVector3(const VFVector3& src)
{
	x = src.x;
	y = src.y;
	z = src.z;
}


inline const VFVector3& VFVector3::operator=(VFVector3 const& src)  // copy assignment operator  
{
	x = src.x;
	y = src.y;
	z = src.z;

	return *this;
}

inline
const float* VFVector3::Ptr() const
{
	return &x;
}

inline
float* VFVector3::Ptr()
{
	return &x;
}

inline
const float& VFVector3::operator[](unsigned i) const
{
	//   ASSERT( i >=0 && i < 3 ) ;
	return ((float*)(&x))[i];
}

inline
float& VFVector3::operator[](unsigned i)
{
	//   ASSERT( i >=0 && i < 3 ) ;
	return ((float*)(&x))[i];
}

inline
VFVector3& VFVector3::operator += (const VFVector3& v)
{
	x += v.x;
	y += v.y;
	z += v.z;
	return *this;
}

inline
VFVector3& VFVector3::operator -= (const VFVector3& v)
{
	x -= v.x;
	y -= v.y;
	z -= v.z;
	return *this;
}

inline
VFVector3& VFVector3::operator *= (const VFVector3& v)
{
	x *= v.x;
	y *= v.y;
	z *= v.z;
	return *this;
}

inline
VFVector3& VFVector3::operator /= (const VFVector3& v)
{
	x /= v.x;
	y /= v.y;
	z /= v.z;
	return *this;
};

inline
VFVector3& VFVector3::operator *= (float s)
{
	x *= s;
	y *= s;
	z *= s;
	return *this;
}

inline
VFVector3& VFVector3::operator /= (float s)
{
	x /= s;
	y /= s;
	z /= s;
	return *this;
}

inline VFVector3 operator + (const VFVector3& v)
{
	return v;
}
 
inline VFVector3 operator -(const VFVector3& v)
{
	return VFVector3(-v.x, -v.y, -v.z);
}
 
inline VFVector3 operator + (const VFVector3& x, const VFVector3& v)
{
	return VFVector3(x.x + v.x, x.y + v.y, x.z + v.z);
}
 

inline VFVector3 operator - (const VFVector3& x, const VFVector3& v)
{
	return VFVector3(x.x - v.x, x.y - v.y, x.z - v.z);
}
 

inline VFVector3 VFVector3::operator *  (float s) const
{
	return VFVector3(x * s, y * s, z * s);
}

// 注：非叉积 ,结果：( x1 * x2 , y1 * y2 , z1 * z2 ) ;
inline  VFVector3 VFVector3::operator * (const VFVector3& rhs) const
{
	return VFVector3(
		x * rhs.x,
		y * rhs.y,
		z * rhs.z);
}

inline VFVector3 VFVector3::operator /  (float s) const
{
	return VFVector3(x / s, y / s, z / s);
}

inline VFVector3 VFVector3::operator /  (const VFVector3& v) const
{
	return VFVector3(x / v.x, y / v.y, z / v.z);
}

inline void VFVector3::MakeFloor(const VFVector3& cmp)
{
	if (cmp.x < x) x = cmp.x;
	if (cmp.y < y) y = cmp.y;
	if (cmp.z < z) z = cmp.z;
}

 
inline void VFVector3::MakeCeil(const VFVector3& cmp)
{
	if (cmp.x > x) x = cmp.x;
	if (cmp.y > y) y = cmp.y;
	if (cmp.z > z) z = cmp.z;
}


inline float VFVector3::Dot(const VFVector3& v) const // 点积
{
	return x * v.x + y * v.y + z * v.z;
}


inline float VFVector3::AbsDot(const VFVector3& v) const // |x1*x2| + |y1*y2| + |z1*z2|
{
	return fabs(x * v.x) + fabs(y * v.y) + fabs(z * v.z);
}


inline bool VFVector3::operator < (const VFVector3&) const
{
	return true;
}


inline bool operator <= (const VFVector3&, const VFVector3&)
{
	return true;
}

inline float VFVector3::SqrMagnitude()                      const  // 模的平方
{
	return x * x + y * y + z * z;
}

inline float VFVector3::Magnitude()                      const // 模长
{
	return sqrt(SqrMagnitude());
}

inline VFVector3 VFVector3::Direction() const
{
	float len = 1.f / Magnitude();
	return VFVector3(x * len, y * len, z * len);
}

inline void        VFVector3::Normalize()                            // 单位化
{
	float flVal = Magnitude() + 1.0e-9f;
	float len = 1.f / flVal;

	x *= len;
	y *= len;
	z *= len;
}

inline VFVector3  VFVector3::ToNormal()                      const  // 生成单位化对象
{
	float len = 1.f / Magnitude() + 1.0e-9f;

	return VFVector3(x * len, y * len, z * len);
}

inline VFVector3  VFVector3::GetOrthoVector() const // 生成一个与自己垂直的向量( 任意 )
{
	if (fabs(x) > fabs(y))
	{
		if (fabs(x) < fabs(z))
			return Cross(VFVECTOR3::AXIS_Y);

		return Cross(VFVECTOR3::AXIS_Z);
	}
	else
	{
		if (fabs(y) < fabs(z))
			return Cross(VFVECTOR3::AXIS_X);

		return Cross(VFVECTOR3::AXIS_X);
	}
}

inline VFVector3  VFVector3::GetOrthoNormal() const // 生成一个与自己垂直的向量( 任意 )
{
	return GetOrthoVector().Direction();
}

inline bool VFVector3::operator == (const VFVector3& v) const
{
	return (x == v.x && y == v.y && z == v.z);
}

inline bool VFVector3::operator != (const VFVector3& v) const
{
	return (x != v.x || y != v.y || z != v.z);
}

inline VFVector3 VFVector3::Cross(const VFVector3& v) const
{
	return VFVector3(y * v.z - z * v.y,
		z * v.x - x * v.z,
		x * v.y - y * v.x);
}


inline VFVector3 operator * (float s, const VFVector3& v)
{
	return v * s;
}


inline  bool VFVector3::IsZero(float threshold) const
{
	return vf_appro_zero(SqrMagnitude(), threshold);
}


inline  bool VFVector3::IsNormalized(float threshold) const
{
	return vf_appro_zero(1.f - SqrMagnitude(), threshold);
}


const VFVECTOR3 VFVECTOR3::ORIGIN(0, 0, 0);
const VFVECTOR3 VFVECTOR3::ZERO(0, 0, 0);
const VFVECTOR3 VFVECTOR3::AXIS_X(1, 0, 0);
const VFVECTOR3 VFVECTOR3::AXIS_Y(0, 1, 0);
const VFVECTOR3 VFVECTOR3::AXIS_Z(0, 0, 1);
const VFVECTOR3 VFVECTOR3::AXIS_NEG_X(-1, 0, 0);
const VFVECTOR3 VFVECTOR3::AXIS_NEG_Y(0, -1, 0);
const VFVECTOR3 VFVECTOR3::AXIS_NEG_Z(0, 0, -1);
const VFVECTOR3 VFVECTOR3::UNIT_SCALE(1, 1, 1);
const VFVECTOR3 VFVECTOR3::VTBL[] = { VFVECTOR3::AXIS_X , VFVECTOR3::AXIS_Y , VFVECTOR3::AXIS_Z };
const VFVECTOR3 VFVECTOR3::NEG_VTBL[] = { VFVECTOR3::AXIS_NEG_X , VFVECTOR3::AXIS_NEG_Y , VFVECTOR3::AXIS_NEG_Z };
const VFVECTOR3 VFVECTOR3::DIR_VTBL[] = { VFVECTOR3::AXIS_X , VFVECTOR3::AXIS_Y , VFVECTOR3::AXIS_Z
										, VFVECTOR3::AXIS_NEG_X , VFVECTOR3::AXIS_NEG_Y , VFVECTOR3::AXIS_NEG_Z };



 
VSMesh::VSMesh()
{
}


VSMesh::VSMesh(const VSMesh& in)
	: vVertice(in.vVertice)
	, vSurface(in.vSurface)
{
}

 
VSMesh::VSMesh(VSMesh&& in)
	: vVertice(std::move(in.vVertice))
	, vSurface(std::move(in.vSurface))
{
}


VSMesh::VSMesh(const char* szPath)
{
	this->LoadFromFile(szPath);
}

VSMesh::~VSMesh()
{
}


VSMesh& VSMesh::operator=(const VSMesh& in)
{
	this->vVertice = in.vVertice;
	this->vSurface = in.vSurface;
	return *this;
}

 
VSMesh& VSMesh::operator=(VSMesh&& in)
{
	this->vVertice = std::move(in.vVertice);
	this->vSurface = std::move(in.vSurface);
	return *this;
}

VSMesh& VSMesh::AddTriangle(const VFVECTOR3& p0, const VFVECTOR3& p1, const VFVECTOR3& p2)
{
	//if (!(p0 - p1).IsZero() && !(p1 - p2).IsZero() && !(p2 - p0).IsZero())
	{
		unsigned cnt = this->vVertice.size();
		this->vVertice.push_back(p0);
		this->vVertice.push_back(p1);
		this->vVertice.push_back(p2);
		this->vSurface.push_back({ cnt, cnt + 1, cnt + 2 });
	}
	return *this;
}

VSMesh& VSMesh::MergeMesh(const VSMesh& in)
{
	if (in.vVertice.empty() && in.vSurface.empty())
		return *this;
	const auto vcnt = this->vVertice.size();
	const auto scnt = this->vSurface.size();
	this->vVertice.insert(this->vVertice.end(), in.vVertice.begin(), in.vVertice.end());
	this->vSurface.resize(scnt + in.vSurface.size());
	for (size_t i = 0; i < in.vSurface.size(); i++) {
		this->vSurface[scnt + i].x = vcnt + in.vSurface[i].x;
		this->vSurface[scnt + i].y = vcnt + in.vSurface[i].y;
		this->vSurface[scnt + i].z = vcnt + in.vSurface[i].z;
	}
	return *this;
}

 

void VSMesh::RemoveRepeatPoint()
{
	const auto oriVertCnt = this->vVertice.size();
	const auto oriSurfCnt = this->vSurface.size();

	VSMesh dst;
	dst.vVertice.reserve(oriVertCnt);
	dst.vSurface.reserve(oriSurfCnt);

	std::unordered_map<size_t, size_t> vertIdxMap;
	std::unordered_map<VFVECTOR3, size_t> dstVertMap;

	for (size_t oriIdx = 0, dstIdx = 0; oriIdx < oriVertCnt; oriIdx++)
	{
		const auto& v = this->vVertice[oriIdx];
		if (dstVertMap.count(v) == 0)
		{
			dstVertMap.insert(std::make_pair(v, dstIdx));
			dst.vVertice.push_back(v);
			vertIdxMap[oriIdx] = dstIdx++;
		}
		vertIdxMap[oriIdx] = dstVertMap[v];
	}
	dst.vVertice.shrink_to_fit();

	for (const auto& f : this->vSurface)
	{
		const auto surf = VNVECTOR3UI(vertIdxMap[f.x], vertIdxMap[f.y], vertIdxMap[f.z]);
		if (surf.x == surf.y || surf.y == surf.z || surf.z == surf.x)
			continue;
		dst.vSurface.push_back(surf);
	}
	dst.vSurface.shrink_to_fit();

	this->Swap(dst);
}
 
void VSMesh::PanMove(const VFVECTOR3& offset)
{
	if (offset == VFVECTOR3::ZERO)
		return;
	for (auto& v : this->vVertice)
		v += offset;
}

void VSMesh::Scale(const VFVECTOR3& scaleVal, const VFVECTOR3& scaleCenter)
{
	if (this->IsEmpty() || scaleVal == VFVECTOR3(1.0f, 1.0f, 1.0f))
		return;
	this->PanMove(-scaleCenter);
	for (auto& v : this->vVertice)
		v *= scaleVal;
	this->PanMove(scaleCenter);
}

void VSMesh::Scale(const float scaleVal, const VFVECTOR3& scaleCenter)
{
	this->Scale({ scaleVal , scaleVal , scaleVal }, scaleCenter);
}
 

void VSMesh::Clear()
{
	this->vVertice.clear();
	this->vSurface.clear();
}


void VSMesh::Swap(VSMesh& in)
{
	this->vVertice.swap(in.vVertice);
	this->vSurface.swap(in.vSurface);
}


void VSMesh::LoadFromFile(const char* szPath, ...)
{
	this->Clear();
	char _Buffer[MAX_PATH]{};
	va_list _ArgList;
	va_start(_ArgList, szPath);
	int _Result = _vsprintf_s_l(_Buffer, MAX_PATH, szPath, NULL, _ArgList);
	va_end(_ArgList);
	if (_Result < 4 || _access(_Buffer, 0) == -1)
		return;

	if (_stricmp(_Buffer + _Result - 4, ".stl") == 0)
	{
		// OBJReadStlFile(this->vVertice, this->vSurface, _Buffer);
	}
	else if (_stricmp(_Buffer + _Result - 4, ".obj") == 0)
	{
		OBJReadFile(this->vVertice, this->vSurface, _Buffer);
	}
}


void VSMesh::WriteToFile(const char* szPath, ...) const
{
	if (this->IsEmpty())
		return;

	std::ofstream dstFile(szPath);

	unsigned nSize = this->vVertice.size();

	for (unsigned j = 0; j < nSize; j++)
	{
		char szBuf[256] = { 0 };
		VFVECTOR3 vert = this->vVertice[j];
		sprintf_s(szBuf, 256, "v %f %f %f", vert.x, vert.y, vert.z);
		dstFile << szBuf << "\n";
	}

	nSize = this->vSurface.size();
	for (unsigned j = 0; j < nSize; ++j)
	{
		char szBuf[256] = { 0 };
		const VNVECTOR3UI& tri = this->vSurface[j];
		sprintf_s(szBuf, 256, "f %d %d %d", tri.x + 1, tri.y + 1, tri.z + 1);
		dstFile << szBuf << "\n";
	}
}


bool VSMesh::IsEmpty() const
{
	return this->vVertice.empty();
}

 
VFVECTOR3 VSMesh::GetVertexCenter() const
{
	VFVECTOR3 ret = VFVECTOR3::ZERO;
	if (!this->IsEmpty())
	{
		for (const auto& v : this->vVertice)
			ret += v;
		ret /= (float)this->vVertice.size();
	}
	return ret;
}


VFVECTOR3 VSMesh::GetAxisMaxPoint() const
{
	if (this->IsEmpty())
		return VFVECTOR3::ZERO;

	VFVECTOR3 ret = { VF_MIN, VF_MIN, VF_MIN };
	for (const auto& v : this->vVertice)
	{
		if (ret.x < v.x)
			ret.x = v.x;
		if (ret.y < v.y)
			ret.y = v.y;
		if (ret.z < v.z)
			ret.z = v.z;
	}
	return ret;
}


VFVECTOR3 VSMesh::GetAxisMinPoint() const
{
	if (this->IsEmpty())
		return VFVECTOR3::ZERO;

	VFVECTOR3 ret = { VF_MAX, VF_MAX, VF_MAX };
	for (const auto& v : this->vVertice)
	{
		if (ret.x > v.x)
			ret.x = v.x;
		if (ret.y > v.y)
			ret.y = v.y;
		if (ret.z > v.z)
			ret.z = v.z;
	}
	return ret;
} 