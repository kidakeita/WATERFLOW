//------------------------------------------------------------
//! @file GamePlayLayer.cpp											
//! @brief ゲームプレイレイヤークラスのソースファイル            
//! @author 喜田　啓太											
//------------------------------------------------------------
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "SimpleAudioEngine.h"
#include "GameManager.h"
#include "Layer/GamePlayLayer.h"
#include "Scene/GamePlayScene/GamePlayScene.h"
#include "Scene/GameClearScene/GameClearScene.h"
#include "Scene/GameOverScene/GameOverScene.h"
#include "Scene/GameSelectScene/GameSelectScene.h"
#include "Scene/GamePauseScene/GamePauseScene.h"
using namespace CocosDenshion;
using namespace cocostudio::timeline;

USING_NS_CC;
#define PTM_RATIO 32

//------------------------------------------------------
//! @brief コンストラクタ
//! @param なし
//! @return なし
//------------------------------------------------------
GamePlayLayer::GamePlayLayer()
{
}

//------------------------------------------------------
//! @brief デフォルトコンストラクタ
//! @param なし
//! @return なし
//------------------------------------------------------
GamePlayLayer::~GamePlayLayer()
{
	// 物理空間削除
	delete m_pWorld;
}
//------------------------------------------------------
//! @brief ゲームプレイレイヤー作成
//! @param なし
//! @return ゲームプレイレイヤークラスのインスタンスのポインタ
//------------------------------------------------------
GamePlayLayer * GamePlayLayer::create()
{
	// インスタンスの作成
	GamePlayLayer *pRet = new(std::nothrow) GamePlayLayer();
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
bool GamePlayLayer::init()
{
	// レイヤーの初期化が成功していない場合
	if (!Layer::init())
	{
		// falseを返す
		return false;
	}
	// 画面サイズを取得
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	// 背景を生成
	m_backgroundlayer = BackGroundLayer::create();
	m_backgroundlayer->Action();
	this->addChild(m_backgroundlayer);

	// 物理ワールド初期化
	initPhysics();

	// ステージ選択でフラグを管理
	switch (GameManager::getInstance()->getFlag())
	{
		// ステージ１
	case Stage1:
		// プレイヤーを生成(重力を与える、X座標、Y座標)
		player = Player::create(m_pWorld, 170.0f, 600.0f);
		this->addChild(player);
		// 水を生成(重力を与える、水の大きさ、X座標、Y座標)
		water = Water::create(m_pWorld, 55.0f, 190.0f, 580.0f);
		this->addChild(water);
		// ゴールを生成(X座標、Y座標)
		goal = Goal::create(640, 80);
		this->addChild(goal);
		// 床を生成(重力を与える)
		floor = Floor::create(m_pWorld);
		this->addChild(floor);
		// ブロックを生成(重力を与える、X座標、Y座標)
		block = Block::create(m_pWorld, 280.0f, 510.0f);
		this->addChild(block);
		break;
		// ステージ２
	case Stage2:
		// プレイヤーを生成
		player = Player::create(m_pWorld, 170.0f, 600.0f);
		this->addChild(player);
		// 水を生成
		water = Water::create(m_pWorld, 55.0f, 190.0f, 580.0f);
		this->addChild(water);
		// ゴールを生成
		goal = Goal::create(150, 80);
		this->addChild(goal);
		// 床を生成
		floor = Floor::create(m_pWorld);
		this->addChild(floor);
		// ブロックを生成
		block = Block::create(m_pWorld, 280.0f, 510.0f);
		this->addChild(block);
		// 敵を生成
		enemy = Enemy::create(m_pWorld, 620.0f, 510.0f);
		this->addChild(enemy);
		break;
		// ステージ３
	case Stage3:
		// プレイヤーを生成
		player = Player::create(m_pWorld, 402.0f, 260.0f);
		this->addChild(player);
		// 水を生成
		water = Water::create(m_pWorld, 62.0f, 284.0f, 520.0f);
		this->addChild(water);
		// ゴールを生成
		goal = Goal::create(448, 335);
		this->addChild(goal);
		// 床を生成
		floor = Floor::create(m_pWorld);
		this->addChild(floor);
		// ブロックを生成
		block = Block::create(m_pWorld, 545.0f, 350.0f);
		this->addChild(block);
		break;
		// ステージ4
	case Stage4:
		// プレイヤーを生成
		player = Player::create(m_pWorld, 390.0f, 630.0f);
		this->addChild(player);
		// 水を生成
		water = Water::create(m_pWorld, 60.0f, 210.0f, 580.0f);
		this->addChild(water);
		// ゴールを生成
		goal = Goal::create(560, 80);
		this->addChild(goal);
		// 床を生成
		floor = Floor::create(m_pWorld);
		this->addChild(floor);
		// ブロックを生成
		block = Block::create(m_pWorld, 340.0f, 450.0f);
		this->addChild(block);
		// 敵を生成
		enemy = Enemy::create(m_pWorld, 620.0f, 510.0f);
		this->addChild(enemy);
		break;
		// ステージ5
	case Stage5:
		// プレイヤーを生成
		player = Player::create(m_pWorld, 402.0f, 100.0f);
		this->addChild(player);
		// 水を生成
		water = Water::create(m_pWorld, 60.0f, 700.0f, 480.0f);
		this->addChild(water);
		// ゴールを生成
		goal = Goal::create(800, 140);
		this->addChild(goal);
		// 床を生成
		floor = Floor::create(m_pWorld);
		this->addChild(floor);
		// ブロックを生成
		block = Block::create(m_pWorld, 545.0f, 300.0f);
		this->addChild(block);
		break;
		// ステージ6
	case Stage6:
		// プレイヤーを生成
		player = Player::create(m_pWorld, 480.0f, 400.0f);
		this->addChild(player);
		// 水を生成
		water = Water::create(m_pWorld, 60.0f, 860.0f, 520.0f);
		this->addChild(water);
		// ゴールを生成
		goal = Goal::create(100, 80);
		this->addChild(goal);
		// 床を生成
		floor = Floor::create(m_pWorld);
		this->addChild(floor);
		// ブロックを生成
		block = Block::create(m_pWorld, 545.0f, 315.0f);
		this->addChild(block);
		break;
		// ステージ7
	case Stage7:
		// プレイヤーを生成
		player = Player::create(m_pWorld, 390.0f, 630.0f);
		this->addChild(player);
		// 水を生成
		water = Water::create(m_pWorld, 60.0f, 210.0f, 580.0f);
		this->addChild(water);
		// ゴールを生成
		goal = Goal::create(380, 80);
		this->addChild(goal);
		// 床を生成
		floor = Floor::create(m_pWorld);
		this->addChild(floor);
		// ブロックを生成
		block = Block::create(m_pWorld, 340.0f, 450.0f);
		this->addChild(block);
		block = Block::create(m_pWorld, 740.0f, 450.0f);
		this->addChild(block);
		// 敵を生成
		enemy = Enemy::create(m_pWorld, 380.0f, 80.0f);
		this->addChild(enemy);
		break;
		// ステージ8
	case Stage8:
		// プレイヤーを生成
		player = Player::create(m_pWorld, 390.0f, 630.0f);
		this->addChild(player);
		// 水を生成
		water = Water::create(m_pWorld, 60.0f, 240.0f, 580.0f);
		this->addChild(water);
		// ゴールを生成
		goal = Goal::create(220, 80);
		this->addChild(goal);
		// 床を生成
		floor = Floor::create(m_pWorld);
		this->addChild(floor);
		// ブロックを生成
		block = Block::create(m_pWorld, 340.0f, 450.0f);
		this->addChild(block);
		break;

	}
	// Update関数を呼び出す
	scheduleUpdate();

	// ポーズボタン作成
	auto pause = MenuItemImage::create("UI/OptionNormal.png", "UI/OptionSelected.png", CC_CALLBACK_1(GamePlayLayer::menuCloseCallback, this));
	pause->setPosition(Vec2(960 - 50, 640 - 50));
	auto menu = Menu::create(pause, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 4);

	// 再挑戦ボタン作成
	auto riset = MenuItemImage::create("UI/Riset.png", "UI/RisetSelect.png", CC_CALLBACK_1(GamePlayLayer::RisetCallback, this));
	riset->setPosition(Vec2(960 - 100, 640 - 50));
	auto risetmenu = Menu::create(riset, NULL);
	risetmenu->setPosition(Vec2::ZERO);
	this->addChild(risetmenu, 4);

	// BGMをプレロードしておく
	SimpleAudioEngine::getInstance()->preloadBackgroundMusic("Sound/BGM2.mp3");
	// 音量を設定
	SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(1.0f);
	// 再生する
	SimpleAudioEngine::getInstance()->playBackgroundMusic("Sound/BGM2.mp3", true);

	// 効果音をプレロードしておく
	SimpleAudioEngine::sharedEngine()->preloadEffect("Sound/button.mp3");
	SimpleAudioEngine::sharedEngine()->preloadEffect("Sound/Attack.mp3");
	SimpleAudioEngine::sharedEngine()->preloadEffect("Sound/pan.mp3");
	SimpleAudioEngine::sharedEngine()->preloadEffect("Sound/flag.mp3");
	// 音量を設定
	SimpleAudioEngine::sharedEngine()->setEffectsVolume(1.0f);
	// trueを返す
	return true;
}

//------------------------------------------------------
//! @brief 物理空間初期化
//! @param なし
//! @return なし
//------------------------------------------------------
void GamePlayLayer::initPhysics()
{
	// 物理ワールドの重力設定
	b2Vec2 gravity;
	// 下方向に毎フレーム10m加速
	gravity.Set(0.0f, -10.0f);
	// 物理空間を作成
	m_pWorld = new b2World(gravity);

	m_pWorld->SetAllowSleeping(true);
}

//------------------------------------------------------
//! @brief 更新処理
//! @param デルタ（毎秒更新）
//! @return なし
//------------------------------------------------------
void GamePlayLayer::update(float delta)
{
	// box2d更新
	m_pWorld->Step(1.0 / 60.0f, 1, 1, 1);

	for (b2Body* body = m_pWorld->GetBodyList();
	body != nullptr;
		body = body->GetNext())
	{
		Sprite* spr = (Sprite*)body->GetUserData();
		if (spr != nullptr)
		{
			b2Vec2 pos = body->GetPosition();
			spr->setPosition(pos.x*PTM_RATIO, pos.y*PTM_RATIO);
			float rot = body->GetAngle();
			spr->setRotation(-CC_RADIANS_TO_DEGREES(rot));
		}
	}

	// 画面サイズを取得
	Size visibleSize = Director::getInstance()->getVisibleSize();

	// プレイヤーのポジション取得
	float x = player->getSprite().getPositionX();
	float y = player->getSprite().getPositionY();
	// ゴールのポジション取得
	float x2 = goal->getPos().x;
	float y2 = goal->getPos().y;
	// プレイヤーとゴールの二つの距離を測る
	float distance = (float)(sqrt((x2 - x)*(x2 - x) + (y2 - y)*(y2 - y)));
	// その距離がプレイヤーの半径とゴールの半径を足して大きかったら当たる
	if (distance <= player->getRadians() + goal->getRadians())
	{
		// ゴールを消す
		this->removeChild(goal);
		TransitionFade* fade = TransitionFade::create(1.0f, GameClearScene::createScene());
		Director::getInstance()->replaceScene(fade);
		SimpleAudioEngine::sharedEngine()->playEffect("Sound/flag.mp3");
		// Updateを呼ばない
		unscheduleUpdate();

	}

	// プレイヤーと敵の当たり判定
	switch (GameManager::getInstance()->getFlag())
	{
	case Stage2:
	case Stage4:
	case Stage7:
		// エネミーのポジション取得
		float x3 = enemy->getSprite().getPositionX();
		float y3 = enemy->getSprite().getPositionY();
		// プレイヤーとエネミーの二つの距離を測る
		float distance2 = (float)(sqrt((x3 - x)*(x3 - x) + (y3 - y)*(y3 - y)));
		// その距離がプレイヤーの半径とエネミーの半径を足して大きかったら当たる
		if (distance2 <= player->getRadians() + enemy->getRadians())
		{
			// プレイヤーを消す
			player->setVisible(false);
			TransitionFadeTR* fade = TransitionFadeTR::create(2.0f, GameOverScene::createScene());
			Director::getInstance()->replaceScene(fade);
			SimpleAudioEngine::sharedEngine()->playEffect("Sound/Attack.mp3");
			unscheduleUpdate();
		}
		break;
	}
	// プレイヤーと壁の当たり判定
	if (x < 0 || x > 960 || y < 0 || y > 640)
	{
		TransitionFadeTR* fade = TransitionFadeTR::create(1.0f, GameOverScene::createScene());
		Director::getInstance()->replaceScene(fade);
		SimpleAudioEngine::sharedEngine()->playEffect("Sound/Attack.mp3");
		unscheduleUpdate();
	}
}

//------------------------------------------------------
//! @brief ポーズイベント作成
//! @param レフのポインタ
//! @return なし
//------------------------------------------------------
void GamePlayLayer::menuCloseCallback(cocos2d::Ref * sender)
{
	TransitionFade* fade = TransitionFade::create(0.3f, GamePauseScene::createScene());
	Director::getInstance()->pushScene(fade);
	SimpleAudioEngine::sharedEngine()->playEffect("Sound/button.mp3");
}

//------------------------------------------------------
//! @brief リセットイベント作成
//! @param レフのポインタ
//! @return なし
//------------------------------------------------------
void GamePlayLayer::RisetCallback(cocos2d::Ref * sender)
{
	TransitionFade* fade = TransitionFade::create(0.5f, GamePlayScene::createScene(), Color3B::WHITE);
	Director::getInstance()->replaceScene(fade);
	SimpleAudioEngine::sharedEngine()->playEffect("Sound/button.mp3");
}

