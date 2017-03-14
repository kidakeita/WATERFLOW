//------------------------------------------------------------
//! @file Enemy.cpp											
//! @brief エネミークラスのソースファイル            
//! @author 喜田　啓太											
//------------------------------------------------------------
#include "Enemy.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"

USING_NS_CC;
#define PTM_RATIO 32

//------------------------------------------------------
//! @brief エネミー作成
//! @param 物理空間のポインタ
//! @param エネミーのX座標
//! @param エネミーのY座標
//! @return エネミークラスのインスタンスのポインタ
//------------------------------------------------------
Enemy * Enemy::create(b2World * world, float x, float y)
{
	// インスタンスの作成
	Enemy *pRet = new(std::nothrow) Enemy();
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
//! @param エネミーのX座標
//! @param エネミーのY座標
//! @return 初期化処理の結果　成功(true)　失敗(false)
//------------------------------------------------------
bool Enemy::init(b2World * world, float x, float y)
{
	// ノードの初期化が成功していない場合
	if (!Node::init())
	{
		// falseを返す
		return false;
	}
	// 表示対象の物理ワールド
	m_pWorld = world;

	// 敵を作成する
	m_enemy = Sprite::create("Object/enemy.png");
	this->addChild(m_enemy);

	// 敵の半径を設定
	m_enemy_rad = 32.0f ;

	// 敵を設定（ポジション）
	initEnemyPhysics(x, y);

	// アクションを呼ぶ
	Action();

	// trueを返す
	return true;
}

//------------------------------------------------------
//! @brief 物理空間初期化
//! @param エネミーのX座標
//! @param エネミーのY座標
//! @return なし
//------------------------------------------------------
void Enemy::initEnemyPhysics(float x, float y)
{
	// 四角形の形状データを作る
	dynamicEnemyBox.SetAsBox(32.0f / 2 / PTM_RATIO, 32.0f / 2 / PTM_RATIO);

	// 敵にギミックを追加
	bodydefEnemy.type = b2_dynamicBody;
	bodydefEnemy.position.Set(x / PTM_RATIO, y / PTM_RATIO);
	bodydefEnemy.fixedRotation = true;
	bodydefEnemy.linearVelocity.Set(-3.0f, 0.0f);
	bodydefEnemy.userData = m_enemy;
	m_pBodyEnemy = m_pWorld->CreateBody(&bodydefEnemy);

	// ダイナミックボディを敵に追加
	fixturedefEnemy.shape = &dynamicEnemyBox;
	fixturedefEnemy.restitution = 0.5f;
	fixturedefEnemy.friction = 1.0f;
	fixturedefEnemy.density = 1.0f;
	m_pBodyEnemy->CreateFixture(&fixturedefEnemy);
}

//------------------------------------------------------
//! @brief エネミーのアクション
//! @param なし
//! @return なし
//------------------------------------------------------
void Enemy::Action()
{
	JumpBy*action = JumpBy::create(1.0f, (Vec2(0, 0)), 80.0f, 2);
	this->runAction(action);
}
