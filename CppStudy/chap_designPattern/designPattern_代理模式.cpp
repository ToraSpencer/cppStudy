#include <string>
#include <vector>
#include <iostream>

#include <cstdio>

#include "designPattern_����ģʽ.h"


 
// ����ģʽ(proxy pattern)Ӧ�ó���1�������������ͬ��ҵ���ϷȨ�ޡ�
namespace PROXY_PATTERN_AS1
{
	// ��Ϸ��ͨ������ģʽʵ�ֲ�ͬvip������ҵ�Ȩ�ޡ�


	//	��Ϸģʽ�Ľӿڡ���������ͬ����Ϸģʽ�����в�ͬ��Ȩ�ޣ��е�ģʽֻ��봽��û�������
	class play
	{
	public:
		virtual void play1() = 0;
		virtual void play2() = 0;
		virtual void play3() = 0;
	};


	// �����
	class player final : public play  							// final�ؼ��ֽ�ֹ�౻�̳У��ں�������������Խ�ֹ�ú��������ء�
	{
	public:
		player() = default;

		virtual void play1() override
		{
			std::cout << "��ͨ��Ϸģʽ����ѵ�" << std::endl;
		}


		virtual void play2() override
		{
			std::cout << "����ģʽ��vip�ſ��Խ���" << std::endl;
		}

		virtual void play3() override
		{
			std::cout << "����ģʽ���׽�vip���Խ���" << std::endl;
		}

	};


	// ��ͨ��Ҵ�����
	class proxyOrdinaryPlayer :public play
	{
	private:
		player* p_player;							// ��������������������������ǹ�����ϵ��

	public:
		virtual void play1() override
		{
			p_player->play1();
		}

		virtual void play2() override
		{
			std::cout << "��ͨ�û����ܽ������Ϸģʽ��" << std::endl;
		}

		virtual void play3() override
		{
			std::cout << "��ͨ�û����ܽ������Ϸģʽ��" << std::endl;
		}
	};


	// vip��Ҵ�����
	class proxyVIPplayer : public play
	{
	private:
		player* p_player;

	public:
		virtual void play1() override
		{
			p_player->play1();
		}

		virtual void play2() override
		{
			p_player->play2();
		}

		virtual void play3() override
		{
			std::cout << "ֻ�а׽�VIP�û����ܽ������Ϸģʽ��" << std::endl;
		}
	};

	// �׽���Ҵ�����
	class proxyPlatinicVIPplayer : public play
	{
	private:
		player* p_player;
	public:
		virtual void play1() override
		{
			p_player->play1();
		}

		virtual void play2() override
		{
			p_player->play2();
		}

		virtual void play3() override
		{
			p_player->play3();
		}

	};

}


// ����ģʽ�͹���ģʽ�Ľ�ϡ���������Ŀ�е�Ӧ��
namespace PROXY_FACTORY 
{
	using FUNCPTRCreateOBJ = void*(*)(const unsigned);
	using FUNCPTRReleaseOBJ = void(*)(void*);
	FUNCPTRCreateOBJ g_FuncCreateObj= nullptr;		// ȫ�ֺ���ָ��
	FUNCPTRReleaseOBJ g_FuncReleaseObj = nullptr;


	// ������Ļ��࣬��һ��������
	struct IVObject		
	{
		IVObject() {}
		virtual ~IVObject() {}
	};


	// ������
	namespace NM_COMMON 
	{
		// ������
		struct IVObjRef
		{
			virtual unsigned GetGuid() = 0;
		};


		// ������
		class VObjRef : public IVObjRef
		{
		public:
			VObjRef(const unsigned nGuid) :m_nGuid(nGuid) {}
			virtual ~VObjRef() {}
			virtual unsigned GetGuid()
			{
				return m_nGuid;
			}

		private:
			unsigned m_nGuid;
		};
	}


	// ���񾫼�����
	namespace NMALG_MESHSIMPLIFY
	{
#define GUID_BASE 0x80000000

		// ���񾫼�����ĳ�����ࡪ�������һ���������������չ��
		struct IVMeshSimplify : public IVObject 
		{
			virtual void Gen() = 0;
		};


		// ���߼�⹦����
		class VCMeshSimplify : public IVMeshSimplify, public NM_COMMON::VObjRef 
		{
		public:
			VCMeshSimplify(const unsigned nGuid) : NM_COMMON::VObjRef(nGuid)
			{
				std::cout << "ʵ������һ�����񾫼��������" << std::endl;
			};

			virtual ~VCMeshSimplify() = default;

			virtual void Gen() 
			{
				std::cout << "���񾫼��������ִ�й��ܡ�" << std::endl;
			};

		};


		// ����һ�����߼�⹦�����ʵ�����������á�
		IVObject* GetGenerator(const unsigned nGuid)
		{
			return static_cast<IVMeshSimplify*>(new VCMeshSimplify(nGuid));
		}
	}


	// ���߼�⹦����
	namespace NMALG_MESHRAYINTERSECTION
	{
		struct IVMeshRayIntersection : public IVObject
		{
			virtual void Build() = 0;
		};


		class VSMeshRayIntersection :public NM_COMMON::VObjRef, public IVMeshRayIntersection
		{
		public:
			VSMeshRayIntersection(const unsigned nGuid) : NM_COMMON::VObjRef(nGuid)
			{
				std::cout << "ʵ������һ�����߼�⹦�������" << std::endl;
			}


			virtual ~VSMeshRayIntersection() = default;

			virtual void Build()
			{
				std::cout << "���߼�⹦�������ִ�й��ܡ�" << std::endl;
			}
		};

		IVObject* GetGenerator(const unsigned nGuid)
		{
			return static_cast<IVMeshRayIntersection*>(new VSMeshRayIntersection(nGuid));
		}

	}


	// ����S10����������и�·��������
	namespace NMALG_CUTPATHHPGEN
	{
		struct IVCutpathhpgen : public IVObject
		{
			virtual void Gen() = 0;
		};


		class VSCutpathhpgen :public NM_COMMON::VObjRef, public IVCutpathhpgen
		{
		public:
			VSCutpathhpgen(const unsigned nGuid) : NM_COMMON::VObjRef(nGuid)
			{
				std::cout << "ʵ������һ�����ɴ��������и�·�����������" << std::endl;

			}

			virtual ~VSCutpathhpgen() {}

			virtual void Gen()
			{
				std::cout << "���ɴ��������и�·�����������ִ�й��ܡ�" << std::endl;
			}
		};


		IVObject* GetGenerator(const unsigned nGuid)
		{
			return static_cast<IVCutpathhpgen*>(new VSCutpathhpgen(nGuid));
		}
	}


	// container������ֿռ�
	namespace NMALG_OBJECTCONTAINER
	{
		enum E_OBJ_TYPE
		{
			OBJ_MESHSIMPLIFY_GEN_E,
			OBJ_MESHRAYINTERSECTION_GEN_E,
			OBJ_CUTPATHHPGEN_GEN_E
		};

		// ��������������
		class VObjManager
		{
		public:
			VObjManager() = default;
			virtual ~VObjManager()
			{
				for (unsigned i = 0; i < m_vObj.size(); i++)
				{
					if (NULL != m_vObj[i])
						delete m_vObj[i];
				}
				m_vObj.clear();

			}

			void* CreateObj(const unsigned nObjEnum)		// �������������
			{
				switch (nObjEnum)
				{
				case OBJ_MESHSIMPLIFY_GEN_E:
					return OBJ_GetMeshSimplify();
				case OBJ_MESHRAYINTERSECTION_GEN_E:
					return OBJ_GetMeshrayintersection();
				case OBJ_CUTPATHHPGEN_GEN_E:
					return OBJ_GetCutpathhpgen();
				default:
					return NULL;
				}
			}


			void ReleaseObj(IVObject* pObj)		// ��Ҫ��һ�ͷ������еĶ���
			{
				if (pObj == nullptr)
					return;

				for (size_t i = 0; i < m_vObj.size(); i++)
				{
					if (pObj == m_vObj[i])
					{
						delete m_vObj[i];
						m_vObj[i] = NULL;
					}
				}
			}

		private:
			void* OBJ_GetMeshSimplify()
			{
				unsigned nIdx = m_vObj.size();
				m_vObj.push_back(NMALG_MESHSIMPLIFY::GetGenerator(nIdx + GUID_BASE));
				return m_vObj[nIdx];
			}


			void* OBJ_GetMeshrayintersection()
			{
				unsigned nIdx = m_vObj.size();
				m_vObj.push_back(NMALG_MESHRAYINTERSECTION::GetGenerator(nIdx + GUID_BASE));
				return m_vObj[nIdx];
			}


			void* OBJ_GetCutpathhpgen()
			{
				unsigned nIdx = m_vObj.size();
				m_vObj.push_back(NMALG_CUTPATHHPGEN::GetGenerator(nIdx + GUID_BASE));
				return m_vObj[nIdx];
			}

		private:
			std::vector<IVObject*> m_vObj;			// �洢����������������	
		};

		static VObjManager g_objManager;			// ȫ�ֵĹ���������߶���


		void* CreateObject(const unsigned nObjEnum) 
		{
			return g_objManager.CreateObj(nObjEnum);
		}


		void ReleaseObject(IVObject* pObj) 
		{
			g_objManager.ReleaseObj(pObj);
		}

	}

	


	// �����ࡪ��ԭ��Ŀ��ֱ�Ӻ͸ô��������ͨ�ţ��������ø��ֿ⣬���򲻻�ֱ�ӷ��ʸ��������ࡣ
	namespace NMALG_OBJECTCONTAINERPROXY
	{
		class VCProxy
		{
		public:
			VCProxy() = default;
			~VCProxy() = default;

			void* CreateObj(const unsigned nObjEnum)		// �ص�������һ��caller
			{
				if (NULL != g_FuncCreateObj)		// ��ʼ���󣬻ص���������Ϊcontainer���еĹ�������createObj����
				{
					return g_FuncCreateObj(nObjEnum);
				}
				return NULL;
			}


			void ReleaseObj(void* pObj)					// ͬ�ϡ�
			{
				if (NULL != g_FuncReleaseObj)
				{
					g_FuncReleaseObj(pObj);
				}
			}

			void Initialize()
			{
				// ����ԭ�����ݣ�ʵ���ϻ��������ض�̬��Ȳ��衣
				g_FuncCreateObj = reinterpret_cast<FUNCPTRCreateOBJ>(NMALG_OBJECTCONTAINER::CreateObject);
				g_FuncReleaseObj = reinterpret_cast<FUNCPTRReleaseOBJ>(NMALG_OBJECTCONTAINER::ReleaseObject);
			}


		};
	}

 

}


virtualModule* designPattern_proxy_module::getInstance()		// �̲߳���ȫ�ĵ���ģʽ
{
	if (nullptr != p_moduleIns)
	{
		delete p_moduleIns;
	}
	p_moduleIns = new designPattern_proxy_module;
	return p_moduleIns;
}


// test0: ����ģʽ(proxy pattern)Ӧ�ó���1�������������ͬ��ҵ���ϷȨ�ޡ�
void designPattern_proxy_module::test0()
{
	PROXY_PATTERN_AS1::play* player123456 = nullptr;
	PROXY_PATTERN_AS1::play* player999988 = nullptr;
	PROXY_PATTERN_AS1::play* player112087 = nullptr;
	PROXY_PATTERN_AS1::play* player078990 = nullptr;
	PROXY_PATTERN_AS1::play* player098056 = nullptr;

	player123456 = new PROXY_PATTERN_AS1::proxyOrdinaryPlayer();
	player999988 = new PROXY_PATTERN_AS1::proxyOrdinaryPlayer();
	player112087 = new PROXY_PATTERN_AS1::proxyVIPplayer();
	player078990 = new PROXY_PATTERN_AS1::proxyVIPplayer();
	player098056 = new PROXY_PATTERN_AS1::proxyPlatinicVIPplayer();

	player123456->play1();
	player123456->play2();
	player123456->play3();
	player112087->play1();
	player112087->play2();
	player112087->play3();
	player098056->play3();


}


// test1:����ģʽ�͹���ģʽ�Ľ�ϡ���������Ŀ�е�Ӧ��
void designPattern_proxy_module::test1()
{
	using namespace PROXY_FACTORY;

	NMALG_OBJECTCONTAINERPROXY::VCProxy proxyObj;
	proxyObj.Initialize();


	// ������ʵ����һ�����������
	auto obj = reinterpret_cast<NMALG_MESHRAYINTERSECTION::IVMeshRayIntersection*>(proxyObj.CreateObj(NMALG_OBJECTCONTAINER::OBJ_MESHRAYINTERSECTION_GEN_E));

	obj->Build();


}


void designPattern_proxy_module::test2() {}


void designPattern_proxy_module::test3() {}


void designPattern_proxy_module::test4() {}


void designPattern_proxy_module::test5() {}


void designPattern_proxy_module::test6() {}


 
