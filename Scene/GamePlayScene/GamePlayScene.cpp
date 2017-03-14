//------------------------------------------------------------
//! @file GamePlayScene.cpp											
//! @brief プレイシーンクラスのソースファイル            
//! @author 喜田　啓太											
//------------------------------------------------------------
#include "GamePlayScene.h"

//------------------------------------------------------
//! @brief プレイシーン作成
//! @param なし
//! @return プレイシーンクラスのインスタンスのポインタ
//------------------------------------------------------
cocos2d::Scene * GamePlayScene::createScene()
{
	// インスタンスの作成
	GamePlayScene *pRet = new(std::nothrow) GamePlayScene();
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
bool GamePlayScene::init()
{
	// シーンの初期化が成功していない場合
	if (!Scene::init())
	{
		// falseを返す
		return false;
	}
	// バックグラウンドレイヤーを作成
	m_backgroundlayer = BackGroundLayer::create();
	this->addChild(m_backgroundlayer);
	// ゲームレイヤーを作成
	m_gameplaylayer = GamePlayLayer::create();
	this->addChild(m_gameplaylayer);
	// trueを返す
	return true;
}


