#include <string>
#include<iostream>

#include <map>
#include <cstdio>
#include "designPattern_����ģʽ.h"



// �򵥹���ģʽ������Ʒ������Ϊ�ӿڣ���Ʒ�Ķ�̬��Ӧ�Ų�ͬ�Ĺ��ܡ�
namespace SIMPLE_FACTORY
{

	// Ь�ӳ�����
	class Shoes
	{
	public:
		virtual ~Shoes() {}
		virtual void Show() = 0;
	};



	// �Ϳ�Ь��
	class NiKeShoes : public Shoes
	{
	public:
		void Show()
		{
			std::cout << "�����Ϳ���Ь���ҵĹ���Just do it" << std::endl;
		}
	};



	// ���ϴ�˹Ь��
	class AdidasShoes : public Shoes
	{
	public:
		void Show()
		{
			std::cout << "���ǰ��ϴ�˹��Ь���ҵĹ����:Impossible is nothing" << std::endl;
		}
	};



	// ����Ь��
	class LiNingShoes : public Shoes
	{
	public:
		void Show()
		{
			std::cout << "����������Ь���ҵĹ���Everything is possible" << std::endl;
		}
	};



	enum SHOES_TYPE
	{
		NIKE,
		LINING,
		ADIDAS
	};



	// ��Ь��
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


// ���󹤳�ģʽ���������Ͳ�Ʒ��������Ϊ�ӿڡ�
namespace ABSTRACT_FACTORY
{
	// �·����������ӿ���
	class Clothe
	{
	public:
		virtual void Show() = 0;
		virtual ~Clothe() {}
	};


	// �Ϳ��·�
	class NiKeClothe : public Clothe
	{
	public:
		void Show()
		{
			std::cout << "�����Ϳ��·���ʱ���������У�" << std::endl;
		}
	};


	// Ь�ӡ��������ӿ���
	class Shoes
	{
	public:
		virtual void Show() = 0;
		virtual ~Shoes() {}
	};


	// �Ϳ�Ь��
	class NiKeShoes : public Shoes
	{
	public:
		void Show()
		{
			std::cout << "�����Ϳ���Ь�������������" << std::endl;
		}
	};


	// �������������ӿ���
	class Factory
	{
	public:
		virtual Shoes *CreateShoes() = 0;
		virtual Clothe *CreateClothe() = 0;
		virtual ~Factory() {}
	};



	// �Ϳ˹���
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



// ģ�幤��ģʽ������Ʒ�������ر�࣬���ֶ�ά�ȷ����ʱ�򣬹������Խ�һ������Ϊģ�塣
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
			std::cout << "�����Ϳ���Ь���ҵĹ���Just do it" << std::endl;
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
			std::cout << "�������¿��·����ҵĹ���I am Uniqlo" << std::endl;
		}
	};


	// ���󹤳�ģ�塪�����������ӿ�
	// ģ�������AbstractProduct_t ��Ʒ������
	template <class AbstractProduct_t>
	class AbstractFactory
	{
	public:
		virtual AbstractProduct_t *CreateProduct() = 0;
		virtual ~AbstractFactory() {}
	};


	// ����ģ�幤����
	//		ģ�������AbstractProduct_t ��Ʒ�����࣬ConcreteProduct_t ��Ʒ������
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


// ����ģʽ�Ľ���������˵���ģʽ�Ĺ���ģʽ
namespace FACTORY_SINGLETON
{

	// Ь�ӿ�
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
			std::cout << "�����Ϳ���Ь���ҵĹ���Just do it" << std::endl;
		}
	};



	// �·��ӿ�
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
			std::cout << "�������¿��·����ҵĹ���I am Uniqlo" << std::endl;
		}
	};



	// ��Ʒע����ģ�塪�������ӿ�
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



	// ����ģ���࣬���ڻ�ȡ��ע���Ʒ����
	template <class ProductType_t>
	class ProductFactory
	{
	private:
		ProductFactory() {}			// ����ģʽ�����캯��˽��
		~ProductFactory() {}
		ProductFactory(const ProductFactory &);
		const ProductFactory &operator=(const ProductFactory &);
		std::map<std::string, IProductRegistrar<ProductType_t>*> m_ProductRegistry; // ����ע����Ĳ�Ʒ��key:��Ʒ���� , value:��Ʒ����


	public:
		static ProductFactory<ProductType_t> &Instance()	// ��ȡ������������meyers����ģʽ
		{
			static ProductFactory<ProductType_t> instance;
			return instance;
		}


		// ��Ʒע��
		void RegisterProduct(IProductRegistrar<ProductType_t> *registrar, std::string name)
		{
			m_ProductRegistry[name] = registrar;
		}


		// ��������name����ȡ��Ӧ����Ĳ�Ʒ����
		ProductType_t *GetProduct(std::string name)
		{
			// ��map�ҵ��Ѿ�ע����Ĳ�Ʒ�������ز�Ʒ����
			if (m_ProductRegistry.find(name) != m_ProductRegistry.end())
			{
				return m_ProductRegistry[name]->CreateProduct();
			}

			// δע��Ĳ�Ʒ���򱨴�δ�ҵ�
			std::cout << "No product found for " << name << std::endl;

			return NULL;
		}


	};



	// ��Ʒע����ģ�壬���ڴ��������Ʒ�ʹӹ�����ע���Ʒ
	// ģ����� ProductType_t ��ʾ�����ǲ�Ʒ�����ࣨ���ࣩ��ProductImpl_t ��ʾ�����Ǿ����Ʒ����Ʒ��������ࣩ
	template <class ProductType_t, class ProductImpl_t>
	class ProductRegistrar : public IProductRegistrar<ProductType_t>
	{
	public:
		// ���캯��������ע���Ʒ��������ֻ����ʾ����
		explicit ProductRegistrar(std::string name)
		{
			// ͨ�����������Ѳ�Ʒע�ᵽ����
			ProductFactory<ProductType_t>::Instance().RegisterProduct(this, name);
		}



		// ���������Ʒ����ָ��
		ProductType_t *CreateProduct()
		{
			return new ProductImpl_t();
		}
	};


}



virtualModule* designPattern_factory_module::getInstance()		// �̲߳���ȫ�ĵ���ģʽ
{
	if (nullptr != p_moduleIns)
	{
		delete p_moduleIns;
	}
	p_moduleIns = new designPattern_factory_module;
	return p_moduleIns;
}



// test0:�򵥹���ģʽ
void designPattern_factory_module::test0()
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



// test1�����󹤳�ģʽ��
void designPattern_factory_module::test1()
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



// test2�����󹤳��Ľ��ס���ģ�幤����
void designPattern_factory_module::test2()
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


// test3: ����ģʽ�Ľ���������˵���ģʽ�Ĺ���ģʽ
/*
	������ע���������Բ���ҪΪ�˲���ĳһ�ֲ�Ʒ�����������Ӧ�Ĺ��̶�����ʼ���ն�ֻ��һ������������Ҫ���ɲ�ͬ�Ĳ�Ʒֻ��Ҫ����ע�����Ϳ����ˡ�
	ע����������ʵ���˹����Ͳ�Ʒ���������ϡ�
	
*/
void designPattern_factory_module::test3()
{
	using namespace FACTORY_SINGLETON;


	// ע���Ʒ 
	ProductRegistrar<Shoes, NiKeShoes> Register1("nike");

	//  ��ȡ��Ʒ����
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


void designPattern_factory_module::test4() {}


void designPattern_factory_module::test5() {}


void designPattern_factory_module::test6() {}