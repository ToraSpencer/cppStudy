#include "head.h"

#include <sys/alg/isysmesh.h>									// VSSimpleMeshF
#include "obj/lsalgtools/ilsalgtoolsperfmesh.h"			// VSMesh 

#include "obj/alg/ialgobjectcontainerproxy.h"				// container
#include "obj/alg/ialgmeshrayintersection.h"				// 射线求交


//// third party静态库：
//#pragma comment(lib, "libamd.lib")
//#pragma comment(lib, "libblas.lib")
//#pragma comment(lib, "libbtf.lib")
//#pragma comment(lib, "libcamd.lib")
//#pragma comment(lib, "libccolamd.lib")
//#pragma comment(lib, "libcholmod.lib")
//#pragma comment(lib, "libcolamd.lib")
//#pragma comment(lib, "libcxsparse.lib")
//#pragma comment(lib, "libklu.lib")
//#pragma comment(lib, "liblapack.lib")
//#pragma comment(lib, "libldl.lib")
//#pragma comment(lib, "libspqr.lib")
//#pragma comment(lib, "libumfpack.lib")
//#pragma comment(lib, "metis.lib")
//#pragma comment(lib, "suitesparseconfig.lib")

//// 动态库的导入lib:
//#pragma comment(lib, "ldck4cce.lib")
//#pragma comment(lib, "ldwzkupdater.lib")

//// 其他：
//#pragma comment(lib, "vdmath.lib")
//#pragma comment(lib, "vmath.lib")
//#pragma comment(lib, "vstd.lib")
//#pragma comment(lib, "lsalgtools.lib")
//#pragma comment(lib, "lsalgmath.lib")
//#pragma comment(lib, "lsalgmatrix.lib")
//
//// container:
//#pragma comment(lib, "lsalgobjectcontainerproxy.lib")
//#pragma comment(lib, "ldobjectcontainer.lib")


/////////////////////////////////////////////////////////////////////////////////////////////////////////// DEBUG接口；
namespace MY_DEBUG
{
	static std::string g_debugPath = "E:/";

	static void debugDisp()			// 递归终止
	{						//		递归终止设为无参或者一个参数的情形都可以。
		std::cout << std::endl;
		return;
	}

	template <typename T, typename... Types>
	static void debugDisp(const T& firstArg, const Types&... args)
	{
		std::cout << firstArg << " ";
		debugDisp(args...);
	}

	static void debugWriteVers(const char* name, std::vector<VFVECTOR3>& vers)
	{
		char path[512] = { 0 };
		sprintf_s(path, "%s%s.obj", g_debugPath.c_str(), name);
		OBJWriteVertices(VD_V2CB(vers), path);
	}

#ifdef USE_MYEIGEN
	static void debugWriteVers(const char* name, std::vector<VDVECTOR3>& vers)
	{
		char path[512] = { 0 };
		sprintf_s(path, "%s%s.obj", g_debugPath.c_str(), name);
		Eigen::MatrixXd versMat = vers2matD(vers);
		objWriteVerticesMat(path, versMat);
	}
#endif

	static void debugWriteVers(const char* name, const VSConstBuffer<VFVECTOR3>& vers)
	{
		char path[512] = { 0 };
		sprintf_s(path, "%s%s.obj", g_debugPath.c_str(), name);
		OBJWriteVertices(vers, path);
	}

	static void debugWriteVers(const char* name, const VFVECTOR3& ver)
	{
		char path[512] = { 0 };
		sprintf_s(path, "%s%s.obj", g_debugPath.c_str(), name);
		OBJWriteVertices(VD_V2CB(std::vector<VFVECTOR3>{ver}), path);
	}

#ifdef USE_MYEIGEN
	template<typename DerivedV>
	static void debugWriteVers(const char* name, const Eigen::PlainObjectBase<DerivedV>& vers)
	{
		char path[512] = { 0 };
		sprintf_s(path, "%s%s.obj", g_debugPath.c_str(), name);
		objWriteVerticesMat(path, vers);
	}

	static void debugWriteVers(const char* name, const Eigen::RowVector3f& ver)
	{
		char path[512] = { 0 };
		sprintf_s(path, "%s%s.obj", g_debugPath.c_str(), name);
		OBJWriteVertices(VD_V2CB(std::vector<VFVECTOR3>{vec2ver(ver)}), path);
	}


	template <typename T>
	static void debugWriteVer(const char* name, const Eigen::Matrix<T, 1, 3>& ver)
	{
		Eigen::Matrix<T, Eigen::Dynamic, Eigen::Dynamic> verMat = ver;
		debugWriteVers(name, verMat);
	}
#endif

	static void debugWriteMesh(const char* name, const VSSimpleMeshF& mesh)
	{
		char path[512] = { 0 };
		sprintf_s(path, "%s%s.obj", g_debugPath.c_str(), name);
		OBJWriteSimpleMesh(path, mesh);
	}


	static void debugWriteMesh(const char* name, const VSSimpleMeshD& mesh)
	{
		char path[512] = { 0 };
		sprintf_s(path, "%s%s.obj", g_debugPath.c_str(), name);
		OBJWriteSimpleMeshD(path, mesh);
	}


	static void debugWriteMesh(const char* name, const VSMeshD& mesh)
	{
		debugWriteMesh(name, mesh.GetSimpleMeshD());
	}


	static void debugWriteMesh(const char* name, const NM_PMMESH::VSMesh& mesh)
	{
		char path[512] = { 0 };
		sprintf_s(path, "%s%s.obj", g_debugPath.c_str(), name);
		mesh.WriteToFile(path);
	}

#ifdef USE_MYEIGEN
	static void debugWriteMesh(const char* name, const Eigen::MatrixXf& vers, const Eigen::MatrixXi& tris)
	{
		char path[512] = { 0 };
		sprintf_s(path, "%s%s.obj", g_debugPath.c_str(), name);
		objWriteMeshMat(path, vers, tris);
	}


	static void debugWriteMesh(const char* name, const Eigen::MatrixXd& vers, const Eigen::MatrixXi& tris)
	{
		char path[512] = { 0 };
		sprintf_s(path, "%s%s.obj", g_debugPath.c_str(), name);
		objWriteMeshMat(path, vers, tris);
	}


	template<typename DerivedV>
	static void debugWriteEdges(const char* name, const Eigen::MatrixXi& edges, const Eigen::PlainObjectBase<DerivedV>& vers)
	{
		char path[512] = { 0 };
		sprintf_s(path, "%s%s.obj", g_debugPath.c_str(), name);
		objWriteEdgesMat(path, edges, vers);
	}
#endif

}
using namespace MY_DEBUG;
 

struct meshRayOut
{
	std::vector<std::vector<float>> rayLen;
	std::vector<std::vector<float>> rayOppLen;
	std::vector<std::vector<unsigned>> isctTris;
	std::vector<std::vector<unsigned>> isctOppTris;
};


bool meshRayIntersect(meshRayOut& result, \
	NMALG_MESHRAYINTERSECTION::IVMeshRayIntersection* pMeshRay, \
	const std::vector<VFVECTOR3>& vers, const VSSimpleMeshF& smesh, \
	const VFVECTOR3& dir)
{
	/*
	VSConstBuffer<VSConstBuffer<float>>, cbRayLen				射线正方向与网格交点：ray.origin + ray.direction * len
	VSConstBuffer<VSConstBuffer<unsigned>>, cbSurfIdx			？？？射线正方向与网格相交的网格上的顶点索引，与cbRayLen一一对应
	VSConstBuffer<VSConstBuffer<float>>, cbOpRayLen				射线反方向与网格交点：ray.origin + ray.direction * len
	VSConstBuffer<VSConstBuffer<unsigned>>, cbOpSurfIdx			射线反方向与网格相交的三角片，与cbOpRayLen一一对应
	*/

	const unsigned long unitsLimit = 1e8;

	unsigned versCount = vers.size();

	if (versCount == 0 || smesh.nTriangleCount == 0 || smesh.nVertCount == 0)
		return false;

	if (smesh.nTriangleCount > unitsLimit)
		return false;

	result.rayLen.resize(versCount);
	result.rayOppLen.resize(versCount);
	result.isctTris.resize(versCount);
	result.isctOppTris.resize(versCount);

	auto copyRayResult = [&](meshRayOut& result, const unsigned start, const unsigned end, \
		const NMALG_MESHRAYINTERSECTION::VSMeshRayIntersectOutput& rayOut)
	{
		unsigned currentRaysCount = end - start;

		for (unsigned i = 0; i < currentRaysCount; ++i)
		{
			unsigned count = rayOut.cbRayLen.pData[i].len;
			if (count > 0)
			{
				result.rayLen[start + i].resize(count);
				std::memcpy(&result.rayLen[start + i][0], rayOut.cbRayLen.pData[i].pData, sizeof(float) * count);
			}
		}

		for (unsigned i = 0; i < currentRaysCount; ++i)
		{
			unsigned count = rayOut.cbOpRayLen.pData[i].len;
			if (count > 0)
			{
				result.rayOppLen[start + i].resize(count);
				std::memcpy(&result.rayOppLen[start + i][0], rayOut.cbOpRayLen.pData[i].pData, sizeof(float) * count);
			}
		}

		for (unsigned i = 0; i < currentRaysCount; ++i)
		{
			unsigned count = rayOut.cbSurfIdx.pData[i].len;
			if (count > 0)
			{
				result.isctTris[start + i].resize(count);
				std::memcpy(&result.isctTris[start + i][0], rayOut.cbSurfIdx.pData[i].pData, sizeof(unsigned) * count);
			}
		}

		for (unsigned i = 0; i < currentRaysCount; ++i)
		{
			unsigned count = rayOut.cbOpSurfIdx.pData[i].len;
			if (count > 0)
			{
				result.isctOppTris[start + i].resize(count);
				std::memcpy(&result.isctOppTris[start + i][0], rayOut.cbOpSurfIdx.pData[i].pData, sizeof(unsigned) * count);
			}
		}
	};

	// 若射线数 * 靶网格三角片数 > unitsLimit，则需要分多次做射线求交：
	unsigned long unitsCount = static_cast<unsigned long>(versCount) * static_cast<unsigned long>(smesh.nVertCount);
	if (static_cast<unsigned long>(unitsLimit) < unitsCount)
	{
		unsigned loopCount = std::floor(unitsCount / unitsLimit);
		unsigned raysCount = std::floor(versCount / loopCount);
		loopCount = std::ceil(versCount / raysCount);

		for (unsigned i = 0; i < loopCount; ++i)
		{
			unsigned start = raysCount * i;
			unsigned end = (loopCount - 1 == i) ? versCount : (raysCount * (i + 1));

			unsigned currentRaysCount = end - start;

			NMALG_MESHRAYINTERSECTION::VSMeshRayIntersectInput rayIn;
			NMALG_MESHRAYINTERSECTION::VSMeshRayIntersectOutput rayOut;
			std::vector<VFRay> vecRay;
			vecRay.reserve(currentRaysCount);
			for (unsigned k = start; k < end; ++k)
			{
				VFRay rayTemp(vers[k], dir);
				vecRay.push_back(rayTemp);
			}
			rayIn.simpMesh = smesh;
			rayIn.rays = VD_V2CB(vecRay);

			pMeshRay->Build(rayOut, rayIn);
			copyRayResult(result, start, end, rayOut);
		}
	}
	else
	{
		NMALG_MESHRAYINTERSECTION::VSMeshRayIntersectInput rayIn;
		NMALG_MESHRAYINTERSECTION::VSMeshRayIntersectOutput rayOut;
		std::vector<VFRay> vecRay;
		vecRay.reserve(versCount);
		for (const auto& ver : vers)
		{
			VFRay rayTemp(ver, dir);
			vecRay.push_back(rayTemp);
		}
		rayIn.simpMesh = smesh;
		rayIn.rays = VD_V2CB(vecRay);

		pMeshRay->Build(rayOut, rayIn);
		copyRayResult(result, 0, versCount, rayOut);
	}

	return true;
};


void test0()
{
	using meshRayIsctPtr = NMALG_MESHRAYINTERSECTION::IVMeshRayIntersection*;

	VFVECTOR3 ver{ 1,2,3 };
	std::cout << ver.x << std::endl;
	std::vector<VFVECTOR3> versIn, versOut;
	VFPlane plane(VFVECTOR3(0, 0, 1), VFVECTOR3(0, 0, 0));
	OBJReadVertices(versIn, "E:/材料/circleVers.obj");
	PMBSpline(versOut, VD_V2CB(versIn), plane);
	debugWriteVers("versOut", versOut);
 
#if 0
	NMALG_OBJECTCONTAINERPROXY::VCProxy objProxy;
	objProxy.Initialize();
	NMALG_MESHRAYINTERSECTION::VSMeshRayIntersectInput rayIn;
	NMALG_MESHRAYINTERSECTION::VSMeshRayIntersectOutput	rayOut;
	meshRayIsctPtr pRay = (meshRayIsctPtr)objProxy.CreateObj(OBJ_MESHRAYINTERSECTION_GEN_E);;

	VSSimpleMeshF	srcMesh, mesh;
	OBJReadSimpMesh(srcMesh, "E:/材料/fatTeeth.obj");
	OBJReadSimpMesh(mesh, "E:/材料/jawMesh.obj");
	debugWriteMesh("srcMesh", srcMesh);
	debugWriteMesh("desMesh", mesh);

	VFVECTOR3 dir = -VFVECTOR3::AXIS_Z;				// 确定测量方向————应该是光源指向被测量物体
	dir.Normalize();

	meshRayOut result;
	std::cout << "start ray intersection: " << std::endl; 
	meshRayIntersect(result, pRay, NM_PMMESH::VSMesh{ srcMesh }.vVertice, mesh, dir); 

	std::vector<VFVECTOR3> positiveProVers;
	positiveProVers.reserve(srcMesh.nVertCount);
	for (unsigned i = 0; i < srcMesh.nVertCount; ++i)
	{
		if (result.rayLen[i].size() > 0)
		{
			float projDepth = result.rayLen[i][0];
			VFVECTOR3 projVer = srcMesh.pVertices[i] + projDepth * dir;
			positiveProVers.push_back(projVer);
		}
	}

	OBJWriteVertices(VD_V2CB(positiveProVers), "E:/投影点.obj");
#endif 

	debugDisp("test0() finished.");
}
