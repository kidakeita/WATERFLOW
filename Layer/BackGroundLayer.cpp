//------------------------------------------------------------
//! @file BackGroundLayer.cpp											
//! @brief バックグラウンドレイヤークラスのソースファイル            
//! @author 喜田　啓太											
//------------------------------------------------------------
#include "BackGroundLayer.h"
USING_NS_CC;

//------------------------------------------------------
//! @brief バックグラウンドレイヤー作成
//! @param なし
//! @return バックグラウンドレイヤークラスのインスタンスのポインタ
//------------------------------------------------------
BackGroundLayer * BackGroundLayer::create()
{
	// インスタンスの作成
	BackGroundLayer *pRet = new(std::nothrow) BackGroundLayer();
	//	インスタンスが作成されていて、初期化も成功していたら
	if (pRet && pRet->init())
	{
		//	cocosのガーベジコレクタにインスタンスのポインタを登録
		pRet->autorelease();
		//	インスタンスのポインタを返す
		return pRet;
	}
	else
	{
		//	インスタンスを削除
		delete pRet;
		//	ポインタを空に
		pRet = nullptr;
		//	nullptrを返す
		return nullptr;
	}
}

//------------------------------------------------------
//! @brief 初期化
//! @param なし
//! @return 初期化処理の結果　成功(true)　失敗(false)
//------------------------------------------------------
bool BackGroundLayer::init()
{
	// レイヤーの初期化が成功していない場合
	if (!Layer::init())
	{
		// falseを返す
		return false;
	}
	// 画面サイズ取得
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	// 背景を生成（空）
	m_sprite_sky = Sprite::create("Background/background_sky.png");
	m_sprite_sky->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	this->addChild(m_sprite_sky, 0);

	// 背景を生成（海）
	m_sprite_sea = Sprite::create("Background/background_sea.png");
	m_sprite_sea->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	this->addChild(m_sprite_sea, 2);

	// パーティクル作成
	ParticleSystemQuad* particle = ParticleSystemQuad::create("Particle/particle_texture.plist");
	particle->resetSystem();
	particle->setPosition(Vec2(visibleSize.width / 2 - 50, visibleSize.height / 2));
	particle->setScale(0.9);
	this->addChild(particle, 5);

	// trueを返す
	return true;
}

//------------------------------------------------------
//! @brief 大きいカニのアクション作成
//! @param なし
//! @return なし
//------------------------------------------------------
void BackGroundLayer::Action()
{
	// 画面サイズ取得
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	// 後ろの大きいカニ作成
	m_sprite_bigcrab = Sprite::create("Object/bigenemy.png");
	m_sprite_bigcrab->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2 - 300));
	this->addChild(m_sprite_bigcrab, 1);
	// カニのアクション
	MoveBy* action1 = MoveBy::create(1.0f, Vec2(0, 300));
	DelayTime* action2 = DelayTime::create(3.0f);
	MoveBy* action3 = MoveBy::create(1.0f, Vec2(0, -300));
	Sequence* seq = Sequence::create(action1, action2, action3, action2, nullptr);
	RepeatForever* rep = RepeatForever::create(seq);
	m_sprite_bigcrab->runAction(rep);
}
