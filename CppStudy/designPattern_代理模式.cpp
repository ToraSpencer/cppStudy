#include <string>
#include<iostream>

#include <cstdio>

using namespace std;


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
			cout << "普通游戏模式，免费的" << endl;
		}


		virtual void play2() override
		{
			cout << "副本模式，vip才可以进入" << endl;
		}

		virtual void play3() override
		{
			cout << "作弊模式，白金vip可以进入" << endl;
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
			cout << "普通用户不能进入此游戏模式。" << endl;
		}

		virtual void play3() override
		{
			cout << "普通用户不能进入此游戏模式。" << endl;
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
			cout << "只有白金VIP用户才能进入此游戏模式。" << endl;
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


// test0: 代理模式(proxy pattern)应用场景1——代理类管理不同玩家的游戏权限。
static void test0()
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

