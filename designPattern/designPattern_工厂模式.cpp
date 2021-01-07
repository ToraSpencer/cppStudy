#include <string>
#include<iostream>

#include <map>
#include <cstdio>

using namespace std;



// 简单工厂模式——产品被抽象为接口，产品的多态对应着不同的功能。
namespace SIMPLE_FACTORY
{

	// 鞋子抽象类
	class Shoes
	{
	public:
		virtual ~Shoes() {}
		virtual void Show() = 0;
	};



	// 耐克鞋子
	class NiKeShoes : public Shoes
	{
	public:
		void Show()
		{
			std::cout << "我是耐克球鞋，我的广告语：Just do it" << std::endl;
		}
	};



	// 阿迪达斯鞋子
	class AdidasShoes : public Shoes
	{
	public:
		void Show()
		{
			std::cout << "我是阿迪达斯球鞋，我的广告语:Impossible is nothing" << std::endl;
		}
	};



	// 李宁鞋子
	class LiNingShoes : public Shoes
	{
	public:
		void Show()
		{
			std::cout << "我是李宁球鞋，我的广告语：Everything is possible" << std::endl;
		}
	};



	enum SHOES_TYPE
	{
		NIKE,
		LINING,
		ADIDAS
	};



	// 总鞋厂
	class ShoesFactory
	{
	public:
		Shoes *CreateShoes(SHOES_TYPE type)
		{
			switch (type)
			{
			case NIKE:
				return new NiKeShoes();
				break;
			case LINING:
				return new LiNingShoes();
				break;
			case ADIDAS:
				return new AdidasShoes();
				break;
			default:
				return NULL;
				break;
			}
		}
	};

}


// 抽象工厂模式——工厂和产品都被抽象为接口。
namespace ABSTRACT_FACTORY
{
	// 衣服————接口类
	class Clothe
	{
	public:
		virtual void Show() = 0;
		virtual ~Clothe() {}
	};


	// 耐克衣服
	class NiKeClothe : public Clothe
	{
	public:
		void Show()
		{
			std::cout << "我是耐克衣服，时尚我最在行！" << std::endl;
		}
	};


	// 鞋子————接口类
	class Shoes
	{
	public:
		virtual void Show() = 0;
		virtual ~Shoes() {}
	};


	// 耐克鞋子
	class NiKeShoes : public Shoes
	{
	public:
		void Show()
		{
			std::cout << "我是耐克球鞋，让你酷起来！" << std::endl;
		}
	};


	// 工厂————接口类
	class Factory
	{
	public:
		virtual Shoes *CreateShoes() = 0;
		virtual Clothe *CreateClothe() = 0;
		virtual ~Factory() {}
	};



	// 耐克工厂
	class NiKeProducer : public Factory
	{
	public:
		Shoes *CreateShoes()
		{
			return new NiKeShoes();
		}

		Clothe *CreateClothe()
		{
			return new NiKeClothe();
		}
	};


}



// 模板工厂模式——产品的种类特别多，出现多维度分类的时候，工厂可以进一步抽象为模板。
namespace TEMPLATE_FACTORY
{

	class Shoes
	{
	public:
		virtual void Show() = 0;
		virtual ~Shoes() {}
	};


	class NiKeShoes : public Shoes
	{
	public:
		void Show()
		{
			std::cout << "我是耐克球鞋，我的广告语：Just do it" << std::endl;
		}
	};


	class Clothe
	{
	public:
		virtual void Show() = 0;
		virtual ~Clothe() {}
	};


	class UniqloClothe : public Clothe
	{
	public:
		void Show()
		{
			std::cout << "我是优衣库衣服，我的广告语：I am Uniqlo" << std::endl;
		}
	};


	// 抽象工厂模板——————接口
	// 模板参数：AbstractProduct_t 产品抽象类
	template <class AbstractProduct_t>
	class AbstractFactory
	{
	public:
		virtual AbstractProduct_t *CreateProduct() = 0;
		virtual ~AbstractFactory() {}
	};


	// 具体模板工厂类
	//		模板参数：AbstractProduct_t 产品抽象类，ConcreteProduct_t 产品具体类
	template <class AbstractProduct_t, class ConcreteProduct_t>
	class ConcreteFactory : public AbstractFactory<AbstractProduct_t>
	{
	public:
		AbstractProduct_t *CreateProduct()
		{
			return new ConcreteProduct_t();
		}
	};


}


// 工厂模式改进——结合了单例模式的工厂模式
namespace FACTORY_SINGLETON
{

	// 鞋接口
	class Shoes
	{
	public:
		virtual void Show() = 0;
		virtual ~Shoes() {}
	};


	class NiKeShoes : public Shoes
	{
	public:
		void Show()
		{
			std::cout << "我是耐克球鞋，我的广告语：Just do it" << std::endl;
		}
	};



	// 衣服接口
	class Clothe
	{
	public:
		virtual void Show() = 0;
		virtual ~Clothe() {}
	};


	class UniqloClothe : public Clothe
	{
	public:
		void Show()
		{
			std::cout << "我是优衣库衣服，我的广告语：I am Uniqlo" << std::endl;
		}
	};



	// 产品注册器模板————接口
	template <class ProductType_t>
	class IProductRegistrar
	{
	public:
		virtual ProductType_t *CreateProduct() = 0;

	protected:
		IProductRegistrar() {}
		virtual ~IProductRegistrar() {}

	private:
		IProductRegistrar(const IProductRegistrar &);
		const IProductRegistrar &operator=(const IProductRegistrar &);
	};



	// 工厂模板类，用于获取和注册产品对象
	template <class ProductType_t>
	class ProductFactory
	{
	private:
		ProductFactory() {}			// 单例模式，构造函数私有
		~ProductFactory() {}
		ProductFactory(const ProductFactory &);
		const ProductFactory &operator=(const ProductFactory &);
		std::map<std::string, IProductRegistrar<ProductType_t>*> m_ProductRegistry; // 保存注册过的产品，key:产品名字 , value:产品类型


	public:
		static ProductFactory<ProductType_t> &Instance()	// 获取工厂单例——meyers单例模式
		{
			static ProductFactory<ProductType_t> instance;
			return instance;
		}


		// 产品注册
		void RegisterProduct(IProductRegistrar<ProductType_t> *registrar, std::string name)
		{
			m_ProductRegistry[name] = registrar;
		}


		// 根据名字name，获取对应具体的产品对象
		ProductType_t *GetProduct(std::string name)
		{
			// 从map找到已经注册过的产品，并返回产品对象
			if (m_ProductRegistry.find(name) != m_ProductRegistry.end())
			{
				return m_ProductRegistry[name]->CreateProduct();
			}

			// 未注册的产品，则报错未找到
			std::cout << "No product found for " << name << std::endl;

			return NULL;
		}


	};



	// 产品注册器模板，用于创建具体产品和从工厂里注册产品
	// 模板参数 ProductType_t 表示的类是产品抽象类（基类），ProductImpl_t 表示的类是具体产品（产品种类的子类）
	template <class ProductType_t, class ProductImpl_t>
	class ProductRegistrar : public IProductRegistrar<ProductType_t>
	{
	public:
		// 构造函数，用于注册产品到工厂，只能显示调用
		explicit ProductRegistrar(std::string name)
		{
			// 通过工厂单例把产品注册到工厂
			ProductFactory<ProductType_t>::Instance().RegisterProduct(this, name);
		}



		// 创建具体产品对象指针
		ProductType_t *CreateProduct()
		{
			return new ProductImpl_t();
		}
	};


}





// test0:简单工厂模式
static void test0()
{

	SIMPLE_FACTORY::ShoesFactory shoesFactory;

	SIMPLE_FACTORY::Shoes* pShoes = shoesFactory.CreateShoes(SIMPLE_FACTORY::NIKE);
	pShoes->Show();
	delete pShoes;
	pShoes = shoesFactory.CreateShoes(SIMPLE_FACTORY::LINING);
	pShoes->Show();
	delete pShoes;
	pShoes = shoesFactory.CreateShoes(SIMPLE_FACTORY::ADIDAS);
	pShoes->Show();
	delete pShoes;



}



// test1：抽象工厂模式。
static void test1()
{


	ABSTRACT_FACTORY::Factory *niKeProducer = new ABSTRACT_FACTORY::NiKeProducer();

	ABSTRACT_FACTORY::Shoes *nikeShoes = niKeProducer->CreateShoes();
	ABSTRACT_FACTORY::Clothe *nikeClothe = niKeProducer->CreateClothe();


	nikeShoes->Show();
	nikeClothe->Show();


	delete nikeShoes;
	delete nikeClothe;
	delete niKeProducer;




}



// test2：抽象工厂的进阶——模板工厂。
static void test2()
{
	using namespace TEMPLATE_FACTORY;

	ConcreteFactory<Shoes, NiKeShoes> nikeFactory;
	Shoes *pNiKeShoes = nikeFactory.CreateProduct();
	pNiKeShoes->Show();
	ConcreteFactory<Clothe, UniqloClothe> uniqloFactory;
	Clothe *pUniqloClothe = uniqloFactory.CreateProduct();

	pUniqloClothe->Show();
	delete pNiKeShoes;
	pNiKeShoes = NULL;
	delete pUniqloClothe;
	pUniqloClothe = NULL;

}




// test3: 工厂模式改进——结合了单例模式的工厂模式
/*
	引入了注册器，可以不需要为了产生某一种产品对象而创建相应的工程对象，自始至终都只有一个工厂单例，要生成不同的产品只需要调整注册器就可以了。
	注册器的引入实现了工厂和产品种类的松耦合。
	
*/
void test3() 
{
	using namespace FACTORY_SINGLETON;


	// 注册产品 
	ProductRegistrar<Shoes, NiKeShoes> Register1("nike");

	//  获取产品对象
	Shoes *shoes = ProductFactory<Shoes>::Instance().GetProduct("nike");
	shoes->Show();
	if (shoes)
	{
		delete shoes;
	}


	ProductRegistrar<Clothe, UniqloClothe> Register2("uniqlo");
	Clothe *cloth = ProductFactory<Clothe>::Instance().GetProduct("uniqlo");
	cloth->Show();
	if (cloth)
	{
		delete cloth;
	}


}