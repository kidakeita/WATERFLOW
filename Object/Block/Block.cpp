//------------------------------------------------------------
//! @file Block.cpp											
//! @brief ブロッククラスのソースファイル            
//! @author 喜田　啓太											
//------------------------------------------------------------
#include "Block.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"

USING_NS_CC;
#define PTM_RATIO 32

//------------------------------------------------------
//! @brief ブロック作成
//! @param 物理空間のポインタ
//! @param ブロックのX座標
//! @param ブロックのY座標
//! @return ブロッククラスのインスタンスのポインタ
//------------------------------------------------------
Block * Block::create(b2World * world, float x, float y)
{
	// インスタンスの作成
	Block *pRet = new(std::nothrow) Block();
	//	インスタンスが作成されていて、初期化も成功していたら
	if (pRet && pRet->init(world,x,y))
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
//! @param ブロックのX座標
//! @param ブロックのY座標
//! @return 初期化処理の結果　成功(true)　失敗(false)
//------------------------------------------------------
bool Block::init(b2World * world, float x, float y)
{
	// ノードの初期化が成功していない場合
	if (!Node::init())
	{
		// falseを返す
		return false;
	}
	// 表示対象の物理ワールド
	m_pWorld = world;

	// イベントリスナーを作成
	EventListenerTouchOneByOne* listener = EventListenerTouchOneByOne::create();
	// イベントリススナーに各コールバック関数をセットする
	listener->onTouchBegan = CC_CALLBACK_2(Block::onTouchBegan, this);
	listener->onTouchMoved = CC_CALLBACK_2(Block::onTouchMoved, this);
	listener->onTouchEnded = CC_CALLBACK_2(Block::onTouchEnded, this);
	// イベントリスナーを登録する
	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);

	// ブロック画像作成
	m_sprite = Sprite::create("Object/block.png");
	m_sprite->setTag(1);
	m_sprite->setName("block");
	this->addChild(m_sprite);

	// 物理空間初期化
	initBlockPhysics(x, y);

	// trueを返す
	return true;
}

//------------------------------------------------------
//! @brief 物理空間初期化
//! @param ブロックのX座標
//! @param ブロックのY座標
//! @return なし
//------------------------------------------------------
void Block::initBlockPhysics(float x, float y)
{
	// 動かないボディの設定を決める
	b2BodyDef groundBodyDef;
	groundBodyDef.position.Set(0, 0);
	m_groundBody = m_pWorld->CreateBody(&groundBodyDef);

	// 四角形の形状データを作る
	m_dynamicBox.SetAsBox(50.0f / 2 / PTM_RATIO, 100.0f / 2 / PTM_RATIO);

	//// ワールドに新たなギミックを追加
	m_bodydef.type = b2_dynamicBody;
	m_bodydef.position.Set(x / PTM_RATIO, y / PTM_RATIO);
	m_bodydef.fixedRotation = true;
	m_bodydef.gravityScale = 0.0f;
	m_bodydef.userData = m_sprite;
	m_pBody = m_pWorld->CreateBody(&m_bodydef);

	// ダイナミックボディを追加
	m_fixturedef.shape = &m_dynamicBox;
	m_fixturedef.density = 5000.0f;
	m_fixturedef.friction = 0.0f;
	m_fixturedef.restitution = 0.0f;
	m_pBody->CreateFixture(&m_fixturedef);
}

//------------------------------------------------------
//! @brief タッチ開始イベント作成
//! @param タッチのポインタ
//! @param イベントのポインタ
//! @return タッチ処理の結果　成功(true)→Move関数が呼ばれる　失敗(false)→Move関数が呼ばれない
//------------------------------------------------------
bool Block::onTouchBegan(cocos2d::Touch * touch, cocos2d::Event * unusedevent)
{
	// マウスジョイントがNULLじゃない場合
	if (m_mouseJoint != NULL)
	{
		// trueを返す
		return true;
	}
	// タッチ座標（ピクセル）
	m_position = touch->getLocation();

	// ブロックの矩形判定
	Sprite* charSprite = (Sprite*)this->getChildByTag(1);
	Point point = charSprite->getPosition();
	int width = charSprite->getContentSize().width;
	int height = charSprite->getContentSize().height;
	m_char = Rect(point.x - (width / 2), point.y - (height / 2), width, height);

	b2Vec2 location = b2Vec2(m_position.x / PTM_RATIO, m_position.y / PTM_RATIO);

	// 座標をコンバートする
	m_position = this->convertToNodeSpace(m_position);
	// タッチ座標とブロックが重なっていたら
	if (m_char.containsPoint(m_position) == true)
	{
		b2MouseJointDef md;
		// 画面の壁（動かないオブジェクトとして定義）
		md.bodyA = m_groundBody;
		// 移動したいボディオブジェクト
		md.bodyB = m_pBody;
		// タッチした場所
		md.target = location;
		// 衝突有効
		md.collideConnected = true;
		// 反応の速さ
		md.maxForce = 1000.0f * m_pBody->GetMass();
		// インスタンス変数として保持
		m_mouseJoint = (b2MouseJoint*)m_pWorld->CreateJoint(&md);
		// 反応する/しない
		m_pBody->SetAwake(true);
	}
	// trueを返す
	return true;
}

//------------------------------------------------------
//! @brief 移動開始イベント作成
//! @param タッチのポインタ
//! @param イベントのポインタ
//! @return なし
//------------------------------------------------------
void Block::onTouchMoved(cocos2d::Touch * touch, cocos2d::Event * unusedevent)
{
	// マウスジョイントがNULLじゃない場合
	if (m_mouseJoint == NULL)
	{
		// 返す
		return;
	}
	// タッチ座標（ピクセル）
	m_position = touch->getLocation();

	b2Vec2 location = b2Vec2(m_position.x / PTM_RATIO, m_position.y / PTM_RATIO);
	// 座標更新
	m_mouseJoint->SetTarget(location);
	// 座標をコンバートする
	m_position = this->convertToNodeSpace(m_position);
}

void Block::onTouchEnded(cocos2d::Touch * touch, cocos2d::Event * unusedevent)
{
	// マウスジョイントがNULLじゃない場合
	if (m_mouseJoint == NULL)
	{
		// 返す
		return;
	}
	// ジョイントを消す
	m_pWorld->DestroyJoint(m_mouseJoint);
	// ジョイントを空にする
	m_mouseJoint = nullptr;
}
