//------------------------------------------------------------
//! @file GameClearScene.cpp											
//! @brief クリアシーンクラスのソースファイル            
//! @author 喜田　啓太											
//------------------------------------------------------------
#include "GameClearScene.h"
#include "SimpleAudioEngine.h"
#include "Scene/GamePlayScene/GamePlayScene.h"
using namespace CocosDenshion;
USING_NS_CC;

//------------------------------------------------------
//! @brief クリアシーン作成
//! @param なし
//! @return クリアシーンクラスのインスタンスのポインタ
//------------------------------------------------------
Scene* GameClearScene::createScene()
{
	// インスタンスの作成
	GameClearScene *pRet = new(std::nothrow) GameClearScene();
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
bool GameClearScene::init()
{
	// シーンの初期化が成功していない場合
	if (!Scene::init())
	{
		// falseを返す
		return false;
	}
	// 画面サイズの取得
	Size visibleSize = Director::getInstance()->getVisibleSize();
	
	// ゲームマネージャー作成
	m_gamemanager = GameManager::getInstance();

	// 背景を生成
	m_backgroundlayer = BackGroundLayer::create();
	this->addChild(m_backgroundlayer);

	// タイトルに戻るボタン作成
	auto title = MenuItemImage::create("UI/TitleNormal.png", "UI/TitleSelected.png", CC_CALLBACK_1(GameClearScene::TitleCallback, this));
	title->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2 + 100));
	auto titlemenu = Menu::create(title, NULL);
	titlemenu->setPosition(Vec2::ZERO);
	this->addChild(titlemenu, 4);

	// ステージセレクトに戻るボタン作成
	auto stageback = MenuItemImage::create("UI/StageNormal.png", "UI/StageSelected.png", CC_CALLBACK_1(GameClearScene::StageSelectCallback, this));
	stageback->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	auto stagemenu = Menu::create(stageback, NULL);
	stagemenu->setPosition(Vec2::ZERO);
	this->addChild(stagemenu, 4);

	// 次のステージに行くボタン作成
	auto nextstage = MenuItemImage::create("UI/NextNormal.png", "UI/NextSelected.png", CC_CALLBACK_1(GameClearScene::NextStageCallback, this));
	nextstage->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2 - 100));
	auto nextmenu = Menu::create(nextstage, NULL);
	nextmenu->setPosition(Vec2::ZERO);
	this->addChild(nextmenu, 4);
	FadeIn* action1 = FadeIn::create(2.0f);
	nextstage->runAction(action1);

	// ゲームクリアラベル作成
	game_clear = Label::createWithTTF("GAME CLEAR", "fonts/uzura.ttf", 100);
	game_clear->setColor(Color3B::YELLOW);
	game_clear->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2 + 200));
	game_clear->enableShadow(Color4B::BLACK, Size(-2, -4), 2);
	this->addChild(game_clear);
	Blink* action = Blink::create(2.0f, 4);
	RepeatForever* rep = RepeatForever::create(action);
	game_clear->runAction(rep);

	// 拍手作成
	m_sprite = Sprite::create("UI/hakusyu.png");
	m_sprite->setPosition(Vec2(visibleSize.width / 2 - 260, visibleSize.height / 2 + 240));
	this->addChild(m_sprite, 4);
	Blink* action2 = Blink::create(2.0f, 4);
	RepeatForever* rep2 = RepeatForever::create(action2);
	m_sprite->runAction(rep2);

	// 効果音をプレロードしておく
	SimpleAudioEngine::sharedEngine()->preloadEffect("Sound/button.mp3");
	//SimpleAudioEngine::sharedEngine()->preloadEffect("clear.mp3");
	// 再生する
	//SimpleAudioEngine::sharedEngine()->playEffect("clear.mp3");
	// 音量を設定
	SimpleAudioEngine::sharedEngine()->setEffectsVolume(1.0f);

	// trueを返す
	return true;
}

//------------------------------------------------------
//! @brief 次のステージに行くイベント作成
//! @param レフのポインタ
//! @return なし
//------------------------------------------------------
void GameClearScene::NextStageCallback(cocos2d::Ref * pSender)
{
	m_gamemanager->setFlag(m_gamemanager->getFlag() + 1);
	if (m_gamemanager->getFlag() >= 9)
	{
		m_gamemanager->setFlag(1);
	}
	TransitionFade* fade = TransitionFade::create(0.5f, GamePlayScene::createScene(), Color3B::WHITE);
	Director::getInstance()->replaceScene(fade);
	SimpleAudioEngine::sharedEngine()->playEffect("Sound/button.mp3");
}

//------------------------------------------------------
//! @brief ステージ選択イベント作成
//! @param レフのポインタ
//! @return なし
//------------------------------------------------------
void GameClearScene::StageSelectCallback(cocos2d::Ref * sender)
{
	m_gamemanager->setSoundFlag(1);
	TransitionFade* fade = TransitionFade::create(1.0f, GameSelectScene::createScene(), Color3B::WHITE);
	Director::getInstance()->replaceScene(fade);
	SimpleAudioEngine::sharedEngine()->playEffect("Sound/button.mp3");
}

//------------------------------------------------------
//! @brief タイトルイベント作成
//! @param レフのポインタ
//! @return なし
//------------------------------------------------------
void GameClearScene::TitleCallback(cocos2d::Ref * sender)
{
	TransitionFade* fade = TransitionFade::create(2.0f, GameTitleScene::createScene(), Color3B::WHITE);
	Director::getInstance()->replaceScene(fade);
	SimpleAudioEngine::sharedEngine()->playEffect("Sound/button.mp3");
}
