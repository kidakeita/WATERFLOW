//------------------------------------------------------------
//! @file GameClearScene.h											
//! @brief クリアシーンクラスのヘッダファイル 
//! @author 喜田　啓太										
//------------------------------------------------------------
#ifndef __GAME_CLEAR_SCENE_H__
#define __GAME_CLEAR_SCENE_H__

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "Layer/BackGroundLayer.h"
#include "Scene/GameTitleScene/GameTitleScene.h"
#include "GameManager.h"
#include "Scene/GameSelectScene/GameSelectScene.h"

class GameClearScene : public cocos2d::Scene
{
private:
	// ゲームクリアラベル
	cocos2d::Label* game_clear;
	// 拍手画像
	cocos2d::Sprite* m_sprite;
	// バックグラウンドレイヤー
	BackGroundLayer* m_backgroundlayer;
	// 文字列
	char m_str[10];
	// ゲームマネージャー
	GameManager* m_gamemanager;

public:
	// タイトルシーン作成
	static cocos2d::Scene* createScene();
	// 初期化	
	virtual bool init();
	// 次のステージに行くイベント
	void NextStageCallback(cocos2d::Ref* pSender);
	// ステージ選択イベント
	void StageSelectCallback(cocos2d::Ref * sender);
	// タイトルイベント
	void TitleCallback(cocos2d::Ref * sender);
};

#endif // __GAME_CLEAR_SCENE_H__