//------------------------------------------------------------
//! @file player.cpp											
//! @brief プレイヤークラスのソースファイル            
//! @author 喜田　啓太											
//------------------------------------------------------------
#include "Player.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"

USING_NS_CC;
#define PTM_RATIO 32

using namespace cocostudio::timeline;

//------------------------------------------------------
//! @brief プレイヤー作成
//! @param 物理空間のポインタ
//! @param プレイヤーのX座標
//! @param プレイヤーのY座標
//! @return プレイヤークラスのインスタンスのポインタ
//------------------------------------------------------
Player* Player::create(b2World* world,float x, float y)
{
	// インスタンスの作成
	Player *pRet = new(std::nothrow) Player();
	//	インスタンスが作成されていて、初期化も成功していたら
	if (pRet && pRet->init(world, x, y))
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
//! @param プレイヤーのX座標
//! @param プレイヤーのY座標
//! @return 初期化処理の結果　成功(true)　失敗(false)
//------------------------------------------------------
bool Player::init(b2World* world,float x,float y)
{
	// ノードの初期化が成功していない場合
	if (!Node::init())
	{
		// falseを返す
		return false;
	}
	// 表示対象の物理ワールド
	m_pWorld = world;
	// プレイヤー画像の半径を取得
	m_rad = 48.0f / 2.0f;
	// プレイヤーを作成する
	m_spr = Sprite::create("Object/player.png");
	m_spr->setTag(2);
	this->addChild(m_spr);
	// プレイヤーを設定（ポジション）
	initPlayerPhysics(x, y);

	// trueを返す
	return true;
}

//------------------------------------------------------
//! @brief 物理空間初期化
//! @param プレイヤーのX座標
//! @param プレイヤーのY座標
//! @return なし
//------------------------------------------------------
void Player::initPlayerPhysics(float x,float y)
{
	// 四角形の形状データを作る
	m_dynamicPlayerBox.SetAsBox(48.0f / 2 / PTM_RATIO, 48.0f / 2 / PTM_RATIO);

	// プレイヤーにギミックを追加
	m_bodydefPlayer.type = b2_dynamicBody;
	m_bodydefPlayer.position.Set(x / PTM_RATIO, y / PTM_RATIO);
	//bodydefPlayer.fixedRotation = false;
	m_bodydefPlayer.userData = m_spr;
	m_pBodyPlayer = m_pWorld->CreateBody(&m_bodydefPlayer);

	// ダイナミックボディをプレイヤーに追加
	m_fixturedefPlayer.shape = &m_dynamicPlayerBox;
	m_fixturedefPlayer.restitution = 0.5f;
	m_fixturedefPlayer.friction = 1.0f;
	m_fixturedefPlayer.density = 1.0f;
	m_pBodyPlayer->CreateFixture(&m_fixturedefPlayer);
}