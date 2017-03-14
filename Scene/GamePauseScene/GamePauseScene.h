//------------------------------------------------------------
//! @file GamePauseScene.h											
//! @brief ポーズシーンクラスのヘッダファイル 
//! @author 喜田　啓太										
//------------------------------------------------------------
#ifndef __GAME_PAUSE_SCENE_H__
#define __GAME_PAUSE_SCENE_H__
#include "cocos2d.h"
#include "Layer/BackGroundLayer.h"
#include "Scene/GameSelectScene/GameSelectScene.h"

class GamePauseScene : public cocos2d::Scene
{
private:
	// ポーズラベル
	cocos2d::Label* pause_label;
	// バックグラウンドレイヤー
	BackGroundLayer* m_backgroundlayer;
public:
	// タイトルシーン作成
	static cocos2d::Scene* createScene();
	// 初期化	
	virtual bool init();
	// リトライイベント
	void menuCloseCallback(cocos2d::Ref* pSender);
	// ステージ選択イベント
	void StageSelectCallback(cocos2d::Ref * sender);
	// タイトルイベント
	void TitleCallback(cocos2d::Ref * sender);
};

#endif // __GAME_PAUSE_SCENE_H__
