//------------------------------------------------------------
//! @file GameTitleScene.cpp											
//! @brief タイトルシーンクラスのソースファイル            
//! @author 喜田　啓太											
//------------------------------------------------------------
#include "GameTitleScene.h"
#include "SimpleAudioEngine.h"
#include "cocostudio/CocoStudio.h"
using namespace CocosDenshion;

USING_NS_CC;
//------------------------------------------------------
//! @brief タイトルシーン作成
//! @param なし
//! @return タイトルシーンクラスのインスタンスのポインタ
//------------------------------------------------------
Scene* GameTitleScene::createScene()
{
	// インスタンスの作成
	GameTitleScene *pRet = new(std::nothrow) GameTitleScene();
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
bool GameTitleScene::init()
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

	// イベントリスナーを作成
	EventListenerTouchOneByOne* listener = EventListenerTouchOneByOne::create();
	// イベントリススナーに各コールバック関数をセットする
	listener->onTouchBegan = CC_CALLBACK_2(GameTitleScene::onTouchBegan, this);
	// イベントリスナーを登録する
	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);

	// タイトルロゴ作成
	m_sprite = Sprite::create("Title/Title.png");
	m_sprite->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	this->addChild(m_sprite);

	// スタートラベル作成
	touch_label = Label::createWithTTF("TOUCH to START", "fonts/uzura.ttf", 80);
	touch_label->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2 - 230));
	touch_label->enableShadow(Color4B::BLACK, Size(-2, -4), 2);
	this->addChild(touch_label);

	// フェードアウト処理
	Sprite* spr = Sprite::create("Background/background.png");
	spr->setPosition(visibleSize.width / 2, visibleSize.height / 2);
	this->addChild(spr);
	FadeOut* act = FadeOut::create(2.0f);
	spr->runAction(act);

	// サウンドフラグを０にする
	GameManager::getInstance()->setSoundFlag(0);

	// ラベルフェードアウト処理
	FadeOut* action1 = FadeOut::create(1.0f);
	FadeIn* action2 = FadeIn::create(1.0f);
	Sequence* seq = Sequence::create(action1, action2, nullptr);
	RepeatForever* rep = RepeatForever::create(seq);
	touch_label->runAction(rep);


	// BGMをプリロードしておく
	SimpleAudioEngine::getInstance()->preloadBackgroundMusic("Sound/BGM.mp3");
	// 音量を設定
	SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(1.0f);
	// 再生する
	SimpleAudioEngine::getInstance()->playBackgroundMusic("Sound/BGM.mp3", true);

	// 効果音をプリロードしておく
	SimpleAudioEngine::sharedEngine()->preloadEffect("Sound/button.mp3");
	// 音量を設定
	SimpleAudioEngine::sharedEngine()->setEffectsVolume(1.0f);

	// trueを返す
	return true;
}

//------------------------------------------------------
//! @brief タッチ開始イベント作成
//! @param タッチのポインタ
//! @param イベントのポインタ
//! @return タッチ処理の結果　成功(true)→Move関数が呼ばれる　失敗(false)→Move関数が呼ばれない
//------------------------------------------------------
bool GameTitleScene::onTouchBegan(cocos2d::Touch * touch, cocos2d::Event * unusedevent)
{
	// シーン遷移
	auto fade = TransitionFade::create(0.5f, GameSelectScene::createScene(), Color3B::WHITE);
	Director::getInstance()->replaceScene(fade);
	
	// 再生する
	SimpleAudioEngine::sharedEngine()->playEffect("Sound/button.mp3");
	
	// trueを返す
	return true;
}