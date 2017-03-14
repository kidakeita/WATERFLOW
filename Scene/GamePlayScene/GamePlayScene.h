//------------------------------------------------------------
//! @file GamePlayScene.h											
//! @brief プレイシーンクラスのヘッダファイル 
//! @author 喜田　啓太										
//------------------------------------------------------------
#ifndef __GAME_PLAY_SCENE_H__
#define __GAME_PLAY_SCENE_H__

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "Layer/GamePlayLayer.h"
#include "Layer/BackGroundLayer.h"

class GamePlayScene : public cocos2d::Scene
{
private:
	// バックグラウンドレイヤー
	BackGroundLayer* m_backgroundlayer;
	// ゲームレイヤー
	GamePlayLayer* m_gameplaylayer;
public:
	// プレイシーン作成
	static cocos2d::Scene* createScene();
	// 初期化
	virtual bool init();
};
#endif

