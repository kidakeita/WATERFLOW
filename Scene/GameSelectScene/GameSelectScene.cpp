//------------------------------------------------------------
//! @file GameSelectScene.cpp											
//! @brief ステージセレクトシーンクラスのソースファイル            
//! @author 喜田　啓太											
//------------------------------------------------------------
#include "GameSelectScene.h"
#include "SimpleAudioEngine.h"
#include "cocostudio/CocoStudio.h"
#include "Scene/GamePlayScene/GamePlayScene.h"

using namespace CocosDenshion;
USING_NS_CC;


//------------------------------------------------------
//! @brief ステージセレクトシーン作成
//! @param なし
//! @return ステージセレクトシーンクラスのインスタンスのポインタ
//------------------------------------------------------
Scene* GameSelectScene::createScene()
{
	// インスタンスの作成
	GameSelectScene *pRet = new(std::nothrow) GameSelectScene();
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
bool GameSelectScene::init()
{
	// シーンの初期化が成功していない場合
	if (!Scene::init())
	{
		// falseを返す
		return false;
	}

	// 画面サイズの取得
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	// ステージ管理フラグ初期化
	m_flag = 0;
	id = 0;

	// ゲームマネージャー作成
	m_gamemanager = GameManager::getInstance();

	// 背景を生成
	m_backgroundlayer = BackGroundLayer::create();
	this->addChild(m_backgroundlayer);

	// セレクトラベル作成
	select_label = Label::createWithTTF("STAGE SELECT", "fonts/uzura.ttf", 80);
	select_label->setColor(Color3B::YELLOW);
	select_label->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2 + 200));
	select_label->enableShadow(Color4B::BLACK, Size(-2, -4), 2);
	this->addChild(select_label);

	// ボタンの数だけループして配置を決める
	for (int i = 0; i < BUTTONNUM; i++)
	{
		id++;
		switch (id)
		{
		case Stage1:
			select[i] = ui::Button::create("SelectButton/babbul_Normal1.png", "SelectButton/babbul_Selected1.png");
			select[i]->setPosition(Vec2(visibleSize.width / 2 - 300, visibleSize.height / 2 + 90));
			select[i]->addTouchEventListener(CC_CALLBACK_2(GameSelectScene::StageTouchEvent1, this));
			break;
		case Stage2:
			select[i] = ui::Button::create("SelectButton/babbul_Normal2.png", "SelectButton/babbul_Selected2.png");
			select[i]->setPosition(Vec2(visibleSize.width / 2 - 100, visibleSize.height / 2 + 90));
			select[i]->addTouchEventListener(CC_CALLBACK_2(GameSelectScene::StageTouchEvent2, this));
			break;
		case Stage3:
			select[i] = ui::Button::create("SelectButton/babbul_Normal3.png", "SelectButton/babbul_Selected3.png");
			select[i]->setPosition(Vec2(visibleSize.width / 2 + 100, visibleSize.height / 2 + 90));
			select[i]->addTouchEventListener(CC_CALLBACK_2(GameSelectScene::StageTouchEvent3, this));
			break;
		case Stage4:
			select[i] = ui::Button::create("SelectButton/babbul_Normal4.png", "SelectButton/babbul_Selected4.png");
			select[i]->setPosition(Vec2(visibleSize.width / 2 + 300, visibleSize.height / 2 + 90));
			select[i]->addTouchEventListener(CC_CALLBACK_2(GameSelectScene::StageTouchEvent4, this));
			break;
		case Stage5:
			select[i] = ui::Button::create("SelectButton/babbul_Normal5.png", "SelectButton/babbul_Selected5.png");
			select[i]->setPosition(Vec2(visibleSize.width / 2 - 300, visibleSize.height / 2 - 70));
			select[i]->addTouchEventListener(CC_CALLBACK_2(GameSelectScene::StageTouchEvent5, this));
			break;
		case Stage6:
			select[i] = ui::Button::create("SelectButton/babbul_Normal6.png", "SelectButton/babbul_Selected6.png");
			select[i]->setPosition(Vec2(visibleSize.width / 2 - 100, visibleSize.height / 2 - 70));
			select[i]->addTouchEventListener(CC_CALLBACK_2(GameSelectScene::StageTouchEvent6, this));
			break;
		case Stage7:
			select[i] = ui::Button::create("SelectButton/babbul_Normal7.png", "SelectButton/babbul_Selected7.png");
			select[i]->setPosition(Vec2(visibleSize.width / 2 + 100, visibleSize.height / 2 - 70));
			select[i]->addTouchEventListener(CC_CALLBACK_2(GameSelectScene::StageTouchEvent7, this));
			break;
		case Stage8:
			select[i] = ui::Button::create("SelectButton/babbul_Normal8.png", "SelectButton/babbul_Selected8.png");
			select[i]->setPosition(Vec2(visibleSize.width / 2 + 300, visibleSize.height / 2 - 70));
			select[i]->addTouchEventListener(CC_CALLBACK_2(GameSelectScene::StageTouchEvent8, this));
			break;

		}

		this->addChild(select[i]);
	}


	// BGMをプレロードしておく
	SimpleAudioEngine::getInstance()->preloadBackgroundMusic("Sound/BGM.mp3");
	// 音量を設定
	SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(1.0f);
	// 再生する
	if (m_gamemanager->getSoundFlag() == 1)
	{
		SimpleAudioEngine::getInstance()->playBackgroundMusic("Sound/BGM.mp3", true);
	}

	// 効果音をプレロードしておく
	SimpleAudioEngine::sharedEngine()->preloadEffect("Sound/bubble-burst1.mp3");
	SimpleAudioEngine::sharedEngine()->preloadEffect("Sound/water-drop.mp3");
	// 音量を設定
	SimpleAudioEngine::sharedEngine()->setEffectsVolume(1.0f);

	// trueを返す
	return true;
}

//------------------------------------------------------
//! @brief ステージ1のイベント作成
//! @param レフのポインタ
//! @param タッチイベントのポインタ
//! @return なし
//------------------------------------------------------
void GameSelectScene::StageTouchEvent1(Ref* sender, ui::Widget::TouchEventType type)
{
	Size visibleSize = Director::getInstance()->getVisibleSize();

	switch (type)
	{
	case cocos2d::ui::Widget::TouchEventType::BEGAN:
		SimpleAudioEngine::sharedEngine()->playEffect("Sound/water-drop.mp3");
		break;
	case cocos2d::ui::Widget::TouchEventType::ENDED:
		// BGMを停止させる
		SimpleAudioEngine::getInstance()->stopBackgroundMusic("Sound/BGM.mp3");
		//AudioEngine::play2d("pa-ne.mp3");
		SimpleAudioEngine::sharedEngine()->playEffect("Sound/bubble-burst1.mp3");
		// パーティクル作成
		SetParticle(visibleSize.width / 2 - 300, visibleSize.height / 2 + 90);
		// ステージ状態を保存する
		m_gamemanager->setFlag(1);
		m_flag = m_gamemanager->getFlag();
		this->removeChild(select[0]);
		TransitionFade* fade = TransitionFade::create(1.0f, GamePlayScene::createScene(), Color3B::WHITE);
		Director::getInstance()->replaceScene(fade);
		break;
	}

}

//------------------------------------------------------
//! @brief ステージ2のイベント作成
//! @param レフのポインタ
//! @param タッチイベントのポインタ
//! @return なし
//------------------------------------------------------
void GameSelectScene::StageTouchEvent2(cocos2d::Ref * sender, cocos2d::ui::Widget::TouchEventType type)
{
	switch (type)
	{
	case cocos2d::ui::Widget::TouchEventType::BEGAN:
		SimpleAudioEngine::sharedEngine()->playEffect("Sound/water-drop.mp3");
		break;
	case cocos2d::ui::Widget::TouchEventType::ENDED:
		// BGMを停止させる
		CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic("Sound/BGM.mp3");
		SimpleAudioEngine::sharedEngine()->playEffect("Sound/bubble-burst1.mp3");
		// パーティクル作成
		SetParticle(visibleSize.width / 2 - 100, visibleSize.height / 2 + 90);
		this->removeChild(select[1]);
		// ステージ状態を保存する
		m_gamemanager->setFlag(2);
		m_flag = m_gamemanager->getFlag();
		TransitionFade* fade = TransitionFade::create(0.5f, GamePlayScene::createScene(), Color3B::WHITE);
		Director::getInstance()->replaceScene(fade);
		break;
	}
}

//------------------------------------------------------
//! @brief ステージ3のイベント作成
//! @param レフのポインタ
//! @param タッチイベントのポインタ
//! @return なし
//------------------------------------------------------
void GameSelectScene::StageTouchEvent3(cocos2d::Ref * sender, cocos2d::ui::Widget::TouchEventType type)
{
	switch (type)
	{
	case cocos2d::ui::Widget::TouchEventType::BEGAN:
		SimpleAudioEngine::sharedEngine()->playEffect("Sound/water-drop.mp3");
		break;
	case cocos2d::ui::Widget::TouchEventType::ENDED:
		// BGMを停止させる
		SimpleAudioEngine::getInstance()->stopBackgroundMusic("Sound/BGM.mp3");
		SimpleAudioEngine::sharedEngine()->playEffect("Sound/bubble-burst1.mp3");
		// パーティクル作成
		SetParticle(visibleSize.width / 2 + 100, visibleSize.height / 2 + 90);
		this->removeChild(select[2]);
		// ステージ状態を保存する
		m_gamemanager->setFlag(3);
		m_flag = m_gamemanager->getFlag();

		TransitionFade* fade = TransitionFade::create(0.5f, GamePlayScene::createScene(), Color3B::WHITE);
		Director::getInstance()->replaceScene(fade);
		break;
	}
}

//------------------------------------------------------
//! @brief ステージ4のイベント作成
//! @param レフのポインタ
//! @param タッチイベントのポインタ
//! @return なし
//------------------------------------------------------
void GameSelectScene::StageTouchEvent4(cocos2d::Ref * sender, cocos2d::ui::Widget::TouchEventType type)
{
	switch (type)
	{
	case cocos2d::ui::Widget::TouchEventType::BEGAN:
		SimpleAudioEngine::sharedEngine()->playEffect("Sound/water-drop.mp3");
		break;
	case cocos2d::ui::Widget::TouchEventType::ENDED:
		// BGMを停止させる
		SimpleAudioEngine::getInstance()->stopBackgroundMusic("Sound/BGM.mp3");
		SimpleAudioEngine::sharedEngine()->playEffect("Sound/bubble-burst1.mp3");
		// パーティクル作成
		SetParticle(visibleSize.width / 2 + 300, visibleSize.height / 2 + 90);
		this->removeChild(select[3]);

		// ステージ状態を保存する
		m_gamemanager->setFlag(4);
		m_flag = m_gamemanager->getFlag();

		TransitionFade* fade = TransitionFade::create(0.5f, GamePlayScene::createScene(), Color3B::WHITE);
		Director::getInstance()->replaceScene(fade);
		break;
	}
}

//------------------------------------------------------
//! @brief ステージ5のイベント作成
//! @param レフのポインタ
//! @param タッチイベントのポインタ
//! @return なし
//------------------------------------------------------
void GameSelectScene::StageTouchEvent5(cocos2d::Ref * sender, cocos2d::ui::Widget::TouchEventType type)
{
	switch (type)
	{
	case cocos2d::ui::Widget::TouchEventType::BEGAN:
		SimpleAudioEngine::sharedEngine()->playEffect("Sound/water-drop.mp3");
		break;
	case cocos2d::ui::Widget::TouchEventType::ENDED:
		// BGMを停止させる
		SimpleAudioEngine::getInstance()->stopBackgroundMusic("Sound/BGM.mp3");
		SimpleAudioEngine::sharedEngine()->playEffect("Sound/bubble-burst1.mp3");
		// パーティクル作成
		SetParticle(visibleSize.width / 2 - 300, visibleSize.height / 2 - 70);
		this->removeChild(select[4]);
		// ステージ状態を保存する
		m_gamemanager->setFlag(5);
		m_flag = m_gamemanager->getFlag();
		TransitionFade* fade = TransitionFade::create(0.5f, GamePlayScene::createScene(), Color3B::WHITE);
		Director::getInstance()->replaceScene(fade);
		break;
	}
}

//------------------------------------------------------
//! @brief ステージ6のイベント作成
//! @param レフのポインタ
//! @param タッチイベントのポインタ
//! @return なし
//------------------------------------------------------
void GameSelectScene::StageTouchEvent6(cocos2d::Ref * sender, cocos2d::ui::Widget::TouchEventType type)
{
	switch (type)
	{
	case cocos2d::ui::Widget::TouchEventType::BEGAN:
		SimpleAudioEngine::sharedEngine()->playEffect("Sound/water-drop.mp3");
		break;
	case cocos2d::ui::Widget::TouchEventType::ENDED:
		// BGMを停止させる
		CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic("Sound/BGM.mp3");
		SimpleAudioEngine::sharedEngine()->playEffect("Sound/bubble-burst1.mp3");
		// パーティクル作成
		SetParticle(visibleSize.width / 2 - 100, visibleSize.height / 2 - 70);
		this->removeChild(select[5]);
		// ステージ状態を保存する
		m_gamemanager->setFlag(6);
		m_flag = m_gamemanager->getFlag();
		TransitionFade* fade = TransitionFade::create(0.5f, GamePlayScene::createScene(), Color3B::WHITE);
		Director::getInstance()->replaceScene(fade);
		break;
	}
}

//------------------------------------------------------
//! @brief ステージ7のイベント作成
//! @param レフのポインタ
//! @param タッチイベントのポインタ
//! @return なし
//------------------------------------------------------
void GameSelectScene::StageTouchEvent7(cocos2d::Ref * sender, cocos2d::ui::Widget::TouchEventType type)
{
	switch (type)
	{
	case cocos2d::ui::Widget::TouchEventType::BEGAN:
		SimpleAudioEngine::sharedEngine()->playEffect("Sound/water-drop.mp3");
		break;
	case cocos2d::ui::Widget::TouchEventType::ENDED:
		// BGMを停止させる
		SimpleAudioEngine::getInstance()->stopBackgroundMusic("Sound/BGM.mp3");
		SimpleAudioEngine::sharedEngine()->playEffect("Sound/bubble-burst1.mp3");
		// パーティクル作成
		SetParticle(visibleSize.width / 2 + 100, visibleSize.height / 2 - 70);
		this->removeChild(select[6]);

		// ステージ状態を保存する
		m_gamemanager->setFlag(7);
		m_flag = m_gamemanager->getFlag();
		TransitionFade* fade = TransitionFade::create(0.5f, GamePlayScene::createScene(), Color3B::WHITE);
		Director::getInstance()->replaceScene(fade);
		break;
	}
}

//------------------------------------------------------
//! @brief ステージ8のイベント作成
//! @param レフのポインタ
//! @param タッチイベントのポインタ
//! @return なし
//------------------------------------------------------
void GameSelectScene::StageTouchEvent8(cocos2d::Ref * sender, cocos2d::ui::Widget::TouchEventType type)
{
	switch (type)
	{
	case cocos2d::ui::Widget::TouchEventType::BEGAN:
		SimpleAudioEngine::sharedEngine()->playEffect("Sound/water-drop.mp3");
		break;
	case cocos2d::ui::Widget::TouchEventType::ENDED:
		// BGMを停止させる
		SimpleAudioEngine::getInstance()->stopBackgroundMusic("Sound/BGM.mp3");
		SimpleAudioEngine::sharedEngine()->playEffect("Sound/bubble-burst1.mp3");
		// パーティクル作成
		SetParticle(visibleSize.width / 2 + 300, visibleSize.height / 2 - 70);
		this->removeChild(select[7]);
		// ステージ状態を保存する
		m_gamemanager->setFlag(8);
		m_flag = m_gamemanager->getFlag();
		TransitionFade* fade = TransitionFade::create(0.5f, GamePlayScene::createScene(), Color3B::WHITE);
		Director::getInstance()->replaceScene(fade);
		break;
	}
}

//------------------------------------------------------
//! @brief パーティクルを設定する
//! @param X座標を決める
//! @param Y座標を決める
//! @return なし
//------------------------------------------------------
void GameSelectScene::SetParticle(float x, float y)
{
	ParticleSystemQuad* particle = ParticleSystemQuad::create("Particle/particle_babul.plist");
	particle->resetSystem();
	particle->setPosition(Vec2(x, y));
	particle->setScale(0.9);
	this->addChild(particle, 5);
}
