//------------------------------------------------------------
//! @file Water.cpp											
//! @brief 水クラスのソースファイル            
//! @author 喜田　啓太											
//------------------------------------------------------------
#include "Water.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"

USING_NS_CC;
#define PTM_RATIO 32

//------------------------------------------------------
//! @brief 水作成
//! @param 物理空間のポインタ
//! @param 水の半径
//! @param 水のX座標
//! @param 水のY座標
//! @return 水クラスのインスタンスのポインタ
//------------------------------------------------------
Water* Water::create(b2World* world, float r, float x, float y)
{
	// インスタンスの作成
	Water *pRet = new(std::nothrow) Water();
	//	インスタンスが作成されていて、初期化も成功していたら
	if (pRet && pRet->init(world, r,x, y))
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
//! @param 物理空間のポインタ
//! @param 水の半径
//! @param 水のX座標
//! @param 水のY座標
//! @return 初期化処理の結果　成功(true)　失敗(false)
//------------------------------------------------------
bool Water::init(b2World* world,float r, float x, float y)
{
	// ノードの初期化が成功していない場合
	if (!Node::init())
	{
		// falseを返す
		return false;
	}

	// 表示対象の物理ワールド
	m_pWorld = world;

	// パーティクルを設定
	setParticle(r,x,y);

	// Update関数を呼び出す
	scheduleUpdate();

	// trueを返す
	return true;
}

//------------------------------------------------------
//! @brief 更新処理
//! @param デルタ（毎秒更新）
//! @return なし
//------------------------------------------------------
void Water::update(float delta)
{
	// box2d更新
	//m_World->Step(1.0 / 60.0f, 8, 3);

	// グループのパーティクルを更新
	userData = particleSystem->GetUserDataBuffer() + particleGroup->GetBufferIndex();

	// 座標
	b2Vec2* waterpos = particleSystem->GetPositionBuffer() + particleGroup->GetBufferIndex();

	// バッファループ
	for (int i = 0; i < particleGroup->GetParticleCount(); i++, waterpos++, userData++)
	{
		((Sprite*)(*userData))->setPosition((*waterpos).x * PTM_RATIO, (*waterpos).y * PTM_RATIO);
		((Sprite*)(*userData))->setColor(Color3B(0, 245, 255));
	}

}

//------------------------------------------------------
//! @brief パーティクルを設定する
//! @param 水の半径
//! @param 水のX座標
//! @param 水のY座標
//! @return なし
//------------------------------------------------------
void Water::setParticle(float r,float x,float y)
{
	// 画面のサイズ
	Size visibleSize = Director::getInstance()->getVisibleSize();

	// 円の形状データを作成
	b2CircleShape dynamicConvex;
	dynamicConvex.m_radius = r / PTM_RATIO;

	// パーティクルグループのデータ設定 
	b2ParticleGroupDef groupDef;
	// パーティクルのグループを設定 
	groupDef.shape = &dynamicConvex;
	groupDef.flags = b2_waterParticle;
	groupDef.position.Set(x / PTM_RATIO, y / PTM_RATIO);

	// パーティクルシステムの設定
	b2ParticleSystemDef particleSystemDef;
	particleSystemDef.density = 1.5;
	particleSystemDef.radius = 4.0f / PTM_RATIO;
	particleSystemDef.gravityScale = 5.5f;
	this->particleSystem = m_pWorld->CreateParticleSystem(&particleSystemDef);

	// グループを作成 
	particleGroup = this->particleSystem->CreateParticleGroup(groupDef);
	userData = particleSystem->GetUserDataBuffer() + particleGroup->GetBufferIndex();
	
	// ループで作られた分画像を描画
	for (int i = 0; i != particleGroup->GetParticleCount(); i++, userData++)
	{
		water = Sprite::create("Particle/water.png");
		(*userData) = water;
		water->setScale(0.3f);
		this->addChild(water);
	}
}
