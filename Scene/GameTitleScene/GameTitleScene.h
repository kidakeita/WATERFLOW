//------------------------------------------------------------
//! @file GameTitleScene.h											
//! @brief タイトルシーンクラスのヘッダファイル 
//! @author 喜田　啓太										
//------------------------------------------------------------
#ifndef __GAME_TITLE_SCENE_H__
#define __GAME_TITLE_SCENE_H__

#include "cocos2d.h"
#include "Layer/BackGroundLayer.h"
#include "Scene/GameSelectScene/GameSelectScene.h"

class GameTitleScene : public cocos2d::Scene
{
private:
	// 画像表示
	cocos2d::Sprite* m_sprite;
	// スタートラベル
	cocos2d::Label* touch_label;
	// バックグラウンドレイヤー
	BackGroundLayer* m_backgroundlayer;
public:
	// タイトルシーン作成
	static cocos2d::Scene* createScene();
	// 初期化	
	virtual bool init();
	// タッチ開始
	bool onTouchBegan(cocos2d::Touch * touch, cocos2d::Event * unusedevent);
};

#endif // __TITLE_SCENE_H__
