//------------------------------------------------------------
//! @file GamePlayLayer.h											
//! @briefゲームプレイレイヤークラスのヘッダファイル            
//! @author 喜田　啓太											
//------------------------------------------------------------
#ifndef __GAME_PLAY_LAYER_H__
#define __GAME_PLAY_LAYER_H__

#include "cocos2d.h"
#include "Box2D/Box2D.h"
#include "ui/CocosGUI.h"
#include "Object/Player/Player.h"
#include "Object/Enemy/Enemy.h"
#include "Object/Block/Block.h"
#include "Water/Water.h"
#include "Floor/Floor.h"
#include "Object/Goal/Goal.h"
#include "BackGroundLayer.h"

enum {
	Stage1 = 1,
	Stage2,
	Stage3,
	Stage4,
	Stage5,
	Stage6,
	Stage7,
	Stage8,
};

class GamePlayLayer : public cocos2d::Layer
{
private:
	// 物理空間のポインタ
	b2World* m_pWorld;
	// プレイヤーのポインタ
	Player* player;
	// エネミーのポインタ
	Enemy* enemy;
	// 水のポインタ
	Water* water;
	// 床のポインタ
	Floor* floor;
	// ゴールのポインタ
	Goal* goal;
	// ブロックのポインタ
	Block* block;
	// バックグラウンドレイヤー
	BackGroundLayer* m_backgroundlayer;

public:
	// コンストラクタ
	GamePlayLayer();
	// デフォルトコンストラクタ
	~GamePlayLayer();
	// ゲームレイヤー作成
	static GamePlayLayer* create();
	// 初期化
	virtual bool init();
	// 物理空間初期化
	void initPhysics();
	// 更新処理
	void update(float delta)override;
	// ポーズイベント
	void menuCloseCallback(cocos2d::Ref * sender);
	// リセットイベント
	void RisetCallback(cocos2d::Ref * sender);
};

#endif // __GAME_PLAY_LAYER__

