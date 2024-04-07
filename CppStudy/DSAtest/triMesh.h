#pragma once
#include <iostream>
#include <cmath>
#include <cstdint>
#include <vector>
#include <stdexcept>


namespace TRIANGLE_MESH
{
	////////////////////////////////////////////////////////////////////////////////////////////// triplet<>��
	template <typename T>
	struct triplet
	{
		T x;
		T y;
		T z;

		triplet<T>() : x(0), y(0), z(0)
		{}

		triplet<T>(const T x0, const T y0, const T z0) : x(x0), y(y0), z(z0)
		{}

		template <typename Ti>
		triplet<T>(const triplet<Ti>& t) : x(static_cast<T>(t.x)), y(static_cast<T>(t.y)), z(static_cast<T>(t.z))
		{}

		T& at(const size_t idx)
		{
			switch (idx)
			{
			case 0:
				return x;
			case 1:
				return y;
			case 2:
				return z;
			default:
				throw(std::out_of_range("exception!!! idx should be 0, 1, or 2;"));
			}
		}

		T& operator[](const size_t idx)
		{
			return at(idx);
		}

		const T& at(const size_t idx) const
		{
			return at(idx);
		}

		const T& operator[](const size_t idx) const
		{
			switch (idx)
			{
			case 0:
				return x;
			case 1:
				return y;
			case 2:
				return z;
			default:
				throw(std::out_of_range("exception!!! idx should be 0, 1, or 2;"));
			}
		}

		const triplet<T>& operator=(const triplet<T>& t)
		{
			this->x = t.x;
			this->y = t.y;
			this->z = t.z;
			return *this;
		}

		template <typename Scalar>
		const triplet<T>& operator+=(const Scalar num)
		{
			this->x = static_cast<T>(x + num);
			this->y = static_cast<T>(y + num);
			this->z = static_cast<T>(z + num);
			return *this;
		}

		template <typename Ti>
		const triplet<T>& operator+=(const triplet<Ti>& t)
		{
			this->x = static_cast<T>(x + t.x);
			this->y = static_cast<T>(y + t.y);
			this->z = static_cast<T>(z + t.z);
			return *this;
		}

		template <typename Scalar>
		const triplet<T>& operator-=(const Scalar num)
		{
			this->x = static_cast<T>(x - num);
			this->y = static_cast<T>(y - num);
			this->z = static_cast<T>(z - num);
			return *this;
		}

		template <typename Ti>
		const triplet<T>& operator-=(const triplet<Ti>& t)
		{
			this->x = static_cast<T>(x - t.x);
			this->y = static_cast<T>(y - t.y);
			this->z = static_cast<T>(z - t.z);
			return *this;
		}

		template <typename Scalar>
		const triplet<T>& operator*=(const Scalar num)
		{
			this->x = static_cast<T>(x * num);
			this->y = static_cast<T>(y * num);
			this->z = static_cast<T>(z * num);
			return *this;
		}

		template <typename Scalar>
		const triplet<T>& operator/=(const Scalar num)
		{
			this->x = static_cast<T>(x / num);
			this->y = static_cast<T>(y / num);
			this->z = static_cast<T>(z / num);
			return *this;
		}

		double sqrLengh() const
		{
			return static_cast<double>(x * x + y * y + z * z);
		}

		double length() const
		{
			return std::sqrt(this->sqrLengh());
		}

		template <typename Ti>
		double distance(const triplet<Ti>& t) const
		{
			triplet<double> arrow{ static_cast<double>(x - t.x), \
				static_cast<double>(y - t.y), static_cast<double>(z - t.z), };

			return arrow.length();
		}

		void normalize()
		{
			double len = this->length();
			this->x = this->x / len;
			this->y = this->y / len;
			this->z = this->z / len;
		}

		template <typename Ti>
		double dot(const triplet<Ti>& t) const
		{
			return static_cast<double>(x * t.x + y * t.y + z * t.z);
		}

		template <typename Ti>
		triplet<T> cross(const triplet<Ti>& t) const
		{
			return triplet<T>{static_cast<T>(y* t.z - z * t.y), \
				static_cast<T>(z* t.x - x * t.z), \
				static_cast<T>(x* t.y - y * t.x)};
		}

		template <typename Ti>
		triplet<Ti> cast() const
		{
			return triplet<Ti>{static_cast<Ti>(x), static_cast<Ti>(y), static_cast<Ti>(z)};
		}
	};

	template <typename T>
	struct doublet
	{
		T x;
		T y; 

		doublet<T>() : x(0), y(0)
		{}

		doublet<T>(const T x0, const T y0) : x(x0), y(y0)
		{}

		template <typename Ti>
		doublet<T>(const doublet<Ti>& t) : x(static_cast<T>(t.x)), y(static_cast<T>(t.y))
		{}
	};


	////////////////////////////////////////////////////////////////////////////////////////////// triMesh()���������ࣺ
	template <typename TV, typename TI>
	struct triMesh
	{
		std::vector<triplet<TV>> vertices;
		std::vector<triplet<TI>> triangles;

		triMesh() {}
		triMesh(const triMesh& mesh) = default;
		triMesh(const std::vector<triplet<TV>>& vers, \
			const std::vector<triplet<TI>>& tris) : vertices(vers), triangles(tris)
		{}

		triMesh(triMesh&& mesh)
		{
			this->vertices = std::move(mesh.vertices);
			this->triangles = std::move(mesh.triangles);
		}

		triMesh& operator=(const triMesh& mesh) = default;

		triMesh& operator=(triMesh&& mesh)
		{
			this->vertices = std::move(mesh.vertices);
			this->triangles = std::move(mesh.triangles);
			return *this;
		}

		void clear()
		{
			this->vertices.clear();
			this->triangles.clear();
		}

		// ������ 
		void concatenate(const triMesh& mesh)
		{
			size_t versCount0 = this->vertices.size();
			this->vertices.insert(this->vertices.end(), mesh.vertices.begin(), mesh.vertices.end());
			this->triangles.reserve(this->triangles.size() + mesh.triangles.size());
			for (const auto& tri : mesh.triangles)
				this->triangles.push_back(triplet<TI>{static_cast<TI>(tri.x + versCount0), \
					static_cast<TI>(tri.y + versCount0), static_cast<TI>(tri.z + versCount0)});
		}
	};


	////////////////////////////////////////////////////////////////////////////////////////////// ���������

	template <typename T>
	std::ostream& operator<<(std::ostream& os, const triplet<T>& t)
	{
		os << "(" << t.x << ", " << t.y << ", " << t.z << ")";
		return os;
	}


	template <typename T1, typename T2>
	triplet<T1> operator+(const triplet<T1>& t1, const triplet<T2>& t2)
	{
		return triplet<T1>{t1.x + t2.x, t1.y + t2.y, t1.z + t2.z};
	}


	template <typename T1, typename T2>
	triplet<T1> operator-(const triplet<T1>& t1, const triplet<T2>& t2)
	{
		return triplet<T1>{t1.x - t2.x, t1.y - t2.y, t1.z - t2.z};
	}

	// ���ţ�
	template <typename T>
	triplet<T> operator-(const triplet<T>& t)
	{
		return triplet<T>{-t.x, -t.y, -t.z};
	}

	template <typename T, typename Scalar>
	triplet<T> operator*(const triplet<T>& t, const Scalar num)
	{
		return triplet<T>{static_cast<T>(num* t.x), static_cast<T>(num* t.y), static_cast<T>(num* t.z)};
	}


	template <typename Scalar, typename T>
	triplet<T> operator*(const Scalar num, const triplet<T>& t)
	{
		return t * num;
	}

	template <typename T, typename Scalar>
	triplet<T> operator/(const triplet<T>& t, const Scalar num)
	{
		return triplet<T>{static_cast<T>(t.x / num), static_cast<T>(t.y / num), static_cast<T>(t.z / num)};
	}
}


// ������
using verF = TRIANGLE_MESH::triplet<float>;									// �����ȶ��㣻
using verD = TRIANGLE_MESH::triplet<double>;								// ˫���ȶ��㣻

// ��Ƭ����
using triangleI = TRIANGLE_MESH::triplet<int>;
using edgeI = TRIANGLE_MESH::doublet<int>;

// ����������
using triMeshF = TRIANGLE_MESH::triMesh<float, int>;					// �����ȶ�������
using triMeshD = TRIANGLE_MESH::triMesh<double, int>;				// ˫���ȶ�������

// IO methods:
bool readOBJ(std::vector<verF>& vers, const char* fileName);
bool readOBJ(std::vector<verD>& vers, const char* fileName);
bool readOBJ(triMeshF& mesh, const char* fileName);
bool readOBJ(triMeshD& mesh, const char* fileName);
bool readSTL(triMeshF& mesh, const char* fileName, const bool blIsAscii = false);
bool readSTL(triMeshD& mesh, const char* fileName, const bool blIsAscii = false);
bool writeOBJ(const char* fileName, const std::vector<verF>& vers);
bool writeOBJ(const char* fileName, const std::vector<verD>& vers);
bool writeOBJ(const char* fileName, const triMeshF& mesh);
bool writeOBJ(const char* fileName, const triMeshD& mesh);
bool writeOBJ(const char* fileName, const std::vector<verF>& vers, const std::vector<edgeI>& edges);
bool writeOBJ(const char* fileName, const std::vector<verD>& vers, const std::vector<edgeI>& edges);
bool writeSTL(const char* fileName, const triMeshF& mesh, const bool blCalcNorms = false);
bool writeSTL(const char* fileName, const triMeshD& mesh, const bool blCalcNorms = false);

// other methods:
void tris2edges(std::vector<edgeI>& edges, const std::vector<triangleI>& tris);
