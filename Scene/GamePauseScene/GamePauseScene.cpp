//------------------------------------------------------------
//! @file GamePauseScene.cpp											
//! @brief ポーズシーンクラスのソースファイル            
//! @author 喜田　啓太											
//------------------------------------------------------------
#include "GamePauseScene.h"
#include "Scene/GameTitleScene/GameTitleScene.h"
#include "SimpleAudioEngine.h"
using namespace CocosDenshion;

USING_NS_CC;
//------------------------------------------------------
//! @brief ポーズシーン作成
//! @param なし
//! @return ポーズシーンクラスのインスタンスのポインタ
//------------------------------------------------------
Scene* GamePauseScene::createScene()
{
	// インスタンスの作成
	GamePauseScene *pRet = new(std::nothrow) GamePauseScene();
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
bool GamePauseScene::init()
{
	// シーンの初期化が成功していない場合
	if (!Scene::init())
	{
		// falseを返す
		return false;
	}
	// 画面サイズの取得
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	// 背景を生成
	m_backgroundlayer = BackGroundLayer::create();
	this->addChild(m_backgroundlayer);

	// タイトルに戻るボタン作成
	auto title = MenuItemImage::create("UI/TitleNormal.png", "UI/TitleSelected.png", CC_CALLBACK_1(GamePauseScene::TitleCallback, this));
	title->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2 + 100));
	auto titlemenu = Menu::create(title, NULL);
	titlemenu->setPosition(Vec2::ZERO);
	this->addChild(titlemenu, 4);

	// ステージセレクトに戻るボタン作成
	auto stageback = MenuItemImage::create("UI/StageNormal.png", "UI/StageSelected.png", CC_CALLBACK_1(GamePauseScene::StageSelectCallback, this));
	stageback->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	auto stagemenu = Menu::create(stageback, NULL);
	stagemenu->setPosition(Vec2::ZERO);
	this->addChild(stagemenu, 4);

	// 戻るボタン作成
	auto back = MenuItemImage::create("UI/BackNormal.png", "UI/BackSelected.png", CC_CALLBACK_1(GamePauseScene::menuCloseCallback, this));
	back->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2 - 100));
	auto backmenu = Menu::create(back, NULL);
	backmenu->setPosition(Vec2::ZERO);
	this->addChild(backmenu, 4);


	// ポーズラベル作成
	pause_label = Label::createWithTTF("PAUSE", "fonts/uzura.ttf", 80);
	pause_label->setColor(Color3B::YELLOW);
	pause_label->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2 + 200));
	pause_label->enableShadow(Color4B::BLACK, Size(-2, -4), 2);
	this->addChild(pause_label);

	// 効果音をプレロードしておく
	SimpleAudioEngine::sharedEngine()->preloadEffect("Sound/button.mp3");
	// 音量を設定
	SimpleAudioEngine::sharedEngine()->setEffectsVolume(1.0f);

	// trueを返す
	return true;
}

//------------------------------------------------------
//! @brief リトライイベント作成
//! @param レフのポインタ
//! @return なし
//------------------------------------------------------
void GamePauseScene::menuCloseCallback(Ref* sender)
{
	Director::getInstance()->popScene();
	SimpleAudioEngine::sharedEngine()->playEffect("Sound/button.mp3");
}

//------------------------------------------------------
//! @brief ステージ選択イベント作成
//! @param レフのポインタ
//! @return なし
//------------------------------------------------------
void GamePauseScene::StageSelectCallback(cocos2d::Ref * sender)
{
	GameManager::getInstance()->setSoundFlag(1);
	TransitionFade* fade = TransitionFade::create(1.0f, GameSelectScene::createScene(), Color3B::WHITE);
	Director::getInstance()->replaceScene(fade);
	SimpleAudioEngine::sharedEngine()->playEffect("Sound/button.mp3");

}

//------------------------------------------------------
//! @brief タイトルイベント作成
//! @param レフのポインタ
//! @return なし
//------------------------------------------------------
void GamePauseScene::TitleCallback(cocos2d::Ref * sender)
{
	TransitionFade* fade = TransitionFade::create(2.0f, GameTitleScene::createScene(), Color3B::WHITE);
	Director::getInstance()->replaceScene(fade);
	SimpleAudioEngine::sharedEngine()->playEffect("Sound/button.mp3");
}


