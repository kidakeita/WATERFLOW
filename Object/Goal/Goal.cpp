//------------------------------------------------------------
//! @file Goalcpp											
//! @brief ゴールクラスのソースファイル            
//! @author 喜田　啓太											
//------------------------------------------------------------
#include "Goal.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"

USING_NS_CC;
#define PTM_RATIO 32

using namespace cocostudio::timeline;

//------------------------------------------------------
//! @brief ゴール作成
//! @param ゴールのX座標
//! @param ゴールのY座標
//! @return ゴールクラスのインスタンスのポインタ
//------------------------------------------------------
Goal* Goal::create(int x,int y)
{
	// インスタンスの作成
	Goal *pRet = new(std::nothrow) Goal();
	//	インスタンスが作成されていて、初期化も成功していたら
	if (pRet && pRet->init(x, y))
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
//! @param ゴールのX座標
//! @param ゴールのY座標
//! @return 初期化処理の結果　成功(true)　失敗(false)
//------------------------------------------------------
bool Goal::init(int x,int y)
{
	// ノードの初期化が成功していない場合
	if (!Node::init())
	{
		// falseを返す
		return false;
	}
	// 画面サイズの取得
	Size visibleSize = Director::getInstance()->getVisibleSize();
	
	// ゴールの半径
	m_rad = 48.0f / 2.0f;
	
	// ゴール画像を作成
	m_spr = Sprite::create("Object/goal.png");
	m_spr->setPosition(Vec2(x, y));
	m_spr->setScale(0.5f);
	m_pos = Vec2(x, y);
	this->addChild(m_spr);
	// trueを返す
	return true;
}
