//------------------------------------------------------------
//! @file GameOverScene.h											
//! @brief タイトルシーンクラスのヘッダファイル 
//! @author 喜田　啓太										
//------------------------------------------------------------
#ifndef __GAME_OVER_SCENE_H__
#define __GAME_OVER_SCENE_H__

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "Layer/BackGroundLayer.h"
#include "Scene/GameTitleScene/GameTitleScene.h"
#include "Scene/GameSelectScene/GameSelectScene.h"

class GameOverScene : public cocos2d::Scene
{
private:
	// ゲームオーバーラベル
	cocos2d::Label* game_over;
	// バックグラウンドレイヤー
	BackGroundLayer* m_backgroundlayer;
	// 文字列
	char m_str[10];


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

#endif // __GAME_OVER_SCENE_H__