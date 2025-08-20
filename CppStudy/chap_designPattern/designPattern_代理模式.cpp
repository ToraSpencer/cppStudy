#include <string>
#include <vector>
#include <iostream>

#include <cstdio>

#include "designPattern_代理模式.h"


 
// 代理模式(proxy pattern)应用场景1——代理类管理不同玩家的游戏权限。
namespace PROXY_PATTERN_AS1
{
	// 游戏中通过代理模式实现不同vip级别玩家的权限。


	//	游戏模式的接口————不同的游戏模式可能有不同的权限，有的模式只有氪金用户才能玩
	class play
	{
	public:
		virtual void play1() = 0;
		virtual void play2() = 0;
		virtual void play3() = 0;
	};


	// 玩家类
	class player final : public play  							// final关键字禁止类被继承；在函数声明后面可以禁止该函数被重载。
	{
	public:
		player() = default;

		virtual void play1() override
		{
			std::cout << "普通游戏模式，免费的" << std::endl;
		}


		virtual void play2() override
		{
			std::cout << "副本模式，vip才可以进入" << std::endl;
		}

		virtual void play3() override
		{
			std::cout << "作弊模式，白金vip可以进入" << std::endl;
		}

	};


	// 普通玩家代理类
	class proxyOrdinaryPlayer :public play
	{
	private:
		player* p_player;							// 代理类对象包含被代理对象。两者是关联关系。

	public:
		virtual void play1() override
		{
			p_player->play1();
		}

		virtual void play2() override
		{
			std::cout << "普通用户不能进入此游戏模式。" << std::endl;
		}

		virtual void play3() override
		{
			std::cout << "普通用户不能进入此游戏模式。" << std::endl;
		}
	};


	// vip玩家代理类
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
			std::cout << "只有白金VIP用户才能进入此游戏模式。" << std::endl;
		}
	};

	// 白金玩家代理类
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


// 代理模式和工厂模式的结合——工作项目中的应用
namespace PROXY_FACTORY 
{
	using FUNCPTRCreateOBJ = void*(*)(const unsigned);
	using FUNCPTRReleaseOBJ = void(*)(void*);
	FUNCPTRCreateOBJ g_FuncCreateObj= nullptr;		// 全局函数指针
	FUNCPTRReleaseOBJ g_FuncReleaseObj = nullptr;


	// 最基础的基类，是一个抽象类
	struct IVObject		
	{
		IVObject() {}
		virtual ~IVObject() {}
	};


	// ？？？
	namespace NM_COMMON 
	{
		// ？？？
		struct IVObjRef
		{
			virtual unsigned GetGuid() = 0;
		};


		// ？？？
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


	// 网格精简功能类
	namespace NMALG_MESHSIMPLIFY
	{
#define GUID_BASE 0x80000000

		// 网格精简功能类的抽象基类——加这个一个抽象层提升可扩展性
		struct IVMeshSimplify : public IVObject 
		{
			virtual void Gen() = 0;
		};


		// 射线检测功能类
		class VCMeshSimplify : public IVMeshSimplify, public NM_COMMON::VObjRef 
		{
		public:
			VCMeshSimplify(const unsigned nGuid) : NM_COMMON::VObjRef(nGuid)
			{
				std::cout << "实例化了一个网格精简功能类对象" << std::endl;
			};

			virtual ~VCMeshSimplify() = default;

			virtual void Gen() 
			{
				std::cout << "网格精简功能类对象执行功能。" << std::endl;
			};

		};


		// 返回一个射线检测功能类的实力，工厂调用。
		IVObject* GetGenerator(const size_t nGuid)
		{
			return static_cast<IVMeshSimplify*>(new VCMeshSimplify(nGuid));
		}
	}


	// 射线检测功能类
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
				std::cout << "实例化了一个射线检测功能类对象" << std::endl;
			}


			virtual ~VSMeshRayIntersection() = default;

			virtual void Build()
			{
				std::cout << "射线检测功能类对象执行功能。" << std::endl;
			}
		};

		IVObject* GetGenerator(const unsigned nGuid)
		{
			return static_cast<IVMeshRayIntersection*>(new VSMeshRayIntersection(nGuid));
		}

	}


	// 生成S10带腭网格的切割路径功能类
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
				std::cout << "实例化了一个生成带腭网格切割路径功能类对象" << std::endl;

			}

			virtual ~VSCutpathhpgen() {}

			virtual void Gen()
			{
				std::cout << "生成带腭网格切割路径功能类对象执行功能。" << std::endl;
			}
		};


		IVObject* GetGenerator(const unsigned nGuid)
		{
			return static_cast<IVCutpathhpgen*>(new VSCutpathhpgen(nGuid));
		}
	}


	// container类的名字空间
	namespace NMALG_OBJECTCONTAINER
	{
		enum E_OBJ_TYPE
		{
			OBJ_MESHSIMPLIFY_GEN_E,
			OBJ_MESHRAYINTERSECTION_GEN_E,
			OBJ_CUTPATHHPGEN_GEN_E
		};

		// 功能类对象管理者
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

			void* CreateObj(const unsigned nObjEnum)		// 创建功能类对象
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


			void ReleaseObj(IVObject* pObj)		// 需要逐一释放容器中的对象。
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
				size_t nIdx = m_vObj.size();
				m_vObj.push_back(NMALG_MESHSIMPLIFY::GetGenerator(nIdx + GUID_BASE));
				return m_vObj[nIdx];
			}


			void* OBJ_GetMeshrayintersection()
			{
				size_t nIdx = m_vObj.size();
				m_vObj.push_back(NMALG_MESHRAYINTERSECTION::GetGenerator(nIdx + GUID_BASE));
				return m_vObj[nIdx];
			}


			void* OBJ_GetCutpathhpgen()
			{
				size_t nIdx = m_vObj.size();
				m_vObj.push_back(NMALG_CUTPATHHPGEN::GetGenerator(nIdx + GUID_BASE));
				return m_vObj[nIdx];
			}

		private:
			std::vector<IVObject*> m_vObj;			// 存储功能类对象的容器。	
		};

		static VObjManager g_objManager;			// 全局的功能类管理者对象


		void* CreateObject(const unsigned nObjEnum) 
		{
			return g_objManager.CreateObj(nObjEnum);
		}


		void ReleaseObject(IVObject* pObj) 
		{
			g_objManager.ReleaseObj(pObj);
		}

	}

	


	// 代理类——原项目中直接和该代理类对象通信，对象会调用各种库，程序不会直接访问各个功能类。
	namespace NMALG_OBJECTCONTAINERPROXY
	{
		class VCProxy
		{
		public:
			VCProxy() = default;
			~VCProxy() = default;

			void* CreateObj(const unsigned nObjEnum)		// 回调函数的一个caller
			{
				if (NULL != g_FuncCreateObj)		// 初始化后，回调函数被绑定为container库中的管理对象的createObj方法
				{
					return g_FuncCreateObj(nObjEnum);
				}
				return NULL;
			}


			void ReleaseObj(void* pObj)					// 同上。
			{
				if (NULL != g_FuncReleaseObj)
				{
					g_FuncReleaseObj(pObj);
				}
			}

			void Initialize()
			{
				// 简化了原有内容，实际上还包括加载动态库等步骤。
				g_FuncCreateObj = reinterpret_cast<FUNCPTRCreateOBJ>(NMALG_OBJECTCONTAINER::CreateObject);
				g_FuncReleaseObj = reinterpret_cast<FUNCPTRReleaseOBJ>(NMALG_OBJECTCONTAINER::ReleaseObject);
			}


		};
	}

 

}


virtualModule* designPattern_proxy_module::getInstance()		// 线程不安全的单例模式
{
	if (nullptr != p_moduleIns)
	{
		delete p_moduleIns;
	}
	p_moduleIns = new designPattern_proxy_module;
	return p_moduleIns;
}


// test0: 代理模式(proxy pattern)应用场景1——代理类管理不同玩家的游戏权限。
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


// test1:代理模式和工厂模式的结合——工作项目中的应用
void designPattern_proxy_module::test1()
{
	using namespace PROXY_FACTORY;

	NMALG_OBJECTCONTAINERPROXY::VCProxy proxyObj;
	proxyObj.Initialize();


	// 代理工厂实例化一个功能类对象：
	auto obj = reinterpret_cast<NMALG_MESHRAYINTERSECTION::IVMeshRayIntersection*>(proxyObj.CreateObj(NMALG_OBJECTCONTAINER::OBJ_MESHRAYINTERSECTION_GEN_E));

	obj->Build();


}


void designPattern_proxy_module::test2() {}


void designPattern_proxy_module::test3() {}


void designPattern_proxy_module::test4() {}


void designPattern_proxy_module::test5() {}


void designPattern_proxy_module::test6() {}


 
