//------------------------------------------------------------
//! @file GameOverScene.cpp											
//! @brief タイトルシーンクラスのソースファイル            
//! @author 喜田　啓太											
//------------------------------------------------------------
#include "GameOverScene.h"
#include "SimpleAudioEngine.h"
#include "Scene/GamePlayScene/GamePlayScene.h"

using namespace CocosDenshion;
USING_NS_CC;

//------------------------------------------------------
//! @brief オーバーシーン作成
//! @param なし
//! @return オーバーシーンクラスのインスタンスのポインタ
//------------------------------------------------------
Scene* GameOverScene::createScene()
{
	// インスタンスの作成
	GameOverScene *pRet = new(std::nothrow) GameOverScene();
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
bool GameOverScene::init()
{
	// シーンの初期化が成功していない場合
	if (!Scene::init())
	{
		// falseを返す
		return false;
	}
	// 画面サイズの取得
	Size visibleSize = Director::getInstance()->getVisibleSize();
	
	// 背景を生成
	m_backgroundlayer = BackGroundLayer::create();
	this->addChild(m_backgroundlayer);

	// タイトルに戻るボタン作成
	auto title = MenuItemImage::create("UI/TitleNormal.png", "UI/TitleSelected.png", CC_CALLBACK_1(GameOverScene::TitleCallback, this));
	title->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2 + 100));
	auto titlemenu = Menu::create(title, NULL);
	titlemenu->setPosition(Vec2::ZERO);
	this->addChild(titlemenu, 4);

	// ステージセレクトに戻るボタン作成
	auto stageback = MenuItemImage::create("UI/StageNormal.png", "UI/StageSelected.png", CC_CALLBACK_1(GameOverScene::StageSelectCallback, this));
	stageback->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	auto stagemenu = Menu::create(stageback, NULL);
	stagemenu->setPosition(Vec2::ZERO);
	this->addChild(stagemenu, 4);

	// 再挑戦ボタン作成
	auto retry = MenuItemImage::create("UI/RetryNormal.png", "UI/RetrySelected.png", CC_CALLBACK_1(GameOverScene::menuCloseCallback, this));
	retry->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2 - 100));
	auto retrymenu = Menu::create(retry, NULL);
	retrymenu->setPosition(Vec2::ZERO);
	this->addChild(retrymenu, 4);

	// ゲームオーバーラベル作成
	game_over = Label::createWithTTF("GAME OVER", "fonts/uzura.ttf", 100);
	game_over->setColor(Color3B::RED);
	game_over->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2 + 200));
	game_over->enableShadow(Color4B::BLACK, Size(-2, -4), 2);
	this->addChild(game_over);
	ScaleBy* action1 = ScaleBy::create(1.0f, 0.5f);
	ScaleBy* action2 = ScaleBy::create(1.0f, 2.0f);
	ScaleBy* action3 = ScaleBy::create(0.5f, 1.0f);
	RotateBy* action4 = RotateBy::create(0.3f, 10.0f);
	Sequence* seq = Sequence::create(action1, action2, action3, action4, nullptr);
	game_over->runAction(seq);


	// 効果音をプレロードしておく
	//SimpleAudioEngine::sharedEngine()->preloadEffect("over.mp3");
	SimpleAudioEngine::sharedEngine()->preloadEffect("Sound/button.mp3");
	// 再生する
	//SimpleAudioEngine::sharedEngine()->playEffect("over.mp3");
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
void GameOverScene::menuCloseCallback(cocos2d::Ref * pSender)
{
	TransitionFade* fade = TransitionFade::create(0.5f, GamePlayScene::createScene(), Color3B::WHITE);
	Director::getInstance()->replaceScene(fade);
	SimpleAudioEngine::sharedEngine()->playEffect("Sound/button.mp3");

}

//------------------------------------------------------
//! @brief ステージ選択イベント作成
//! @param レフのポインタ
//! @return なし
//------------------------------------------------------
void GameOverScene::StageSelectCallback(cocos2d::Ref * sender)
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
void GameOverScene::TitleCallback(cocos2d::Ref * sender)
{
	TransitionFade* fade = TransitionFade::create(2.0f, GameTitleScene::createScene(), Color3B::WHITE);
	Director::getInstance()->replaceScene(fade);
	SimpleAudioEngine::sharedEngine()->playEffect("Sound/button.mp3");
}
