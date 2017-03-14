//------------------------------------------------------------
//! @file GameSelectScene.h											
//! @brief ステージセレクトシーンクラスのヘッダファイル 
//! @author 喜田　啓太										
//------------------------------------------------------------
#ifndef __GAME_SELECT_SCENE_H__
#define __GAME_SELECT_SCENE_H__

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "GameManager.h"
#include "Layer/BackGroundLayer.h"

class GameSelectScene : public cocos2d::Scene
{
private:
	// ボタンの数確保
	static const int BUTTONNUM = 8;
	// セレクトラベル
	cocos2d::Label* select_label;
	// ボタンを配列で管理
	cocos2d::ui::Button* select[BUTTONNUM];
	// ステージ管理フラグ
	int m_flag;
	// バックグラウンドレイヤー
	BackGroundLayer* m_backgroundlayer;
	// ボタンの配置
	int id;
	// パーティクルを描画するのためメンバ変数で管理
	cocos2d::Size visibleSize = cocos2d::Director::getInstance()->getVisibleSize();
	// ゲームマネージャー
	GameManager* m_gamemanager;
public:
	// タイトルシーン作成
	static cocos2d::Scene* createScene();
	// 初期化	
	virtual bool init();
	// ステージ1のイベント
	void StageTouchEvent1(cocos2d::Ref * sender, cocos2d::ui::Widget::TouchEventType type);
	// ステージ2のイベント
	void StageTouchEvent2(cocos2d::Ref * sender, cocos2d::ui::Widget::TouchEventType type);
	// ステージ3のイベント
	void StageTouchEvent3(cocos2d::Ref * sender, cocos2d::ui::Widget::TouchEventType type);
	// ステージ4のイベント
	void StageTouchEvent4(cocos2d::Ref * sender, cocos2d::ui::Widget::TouchEventType type);
	// ステージ5のイベント
	void StageTouchEvent5(cocos2d::Ref * sender, cocos2d::ui::Widget::TouchEventType type);
	// ステージ6のイベント
	void StageTouchEvent6(cocos2d::Ref * sender, cocos2d::ui::Widget::TouchEventType type);
	// ステージ7のイベント
	void StageTouchEvent7(cocos2d::Ref * sender, cocos2d::ui::Widget::TouchEventType type);
	// ステージ8のイベント
	void StageTouchEvent8(cocos2d::Ref * sender, cocos2d::ui::Widget::TouchEventType type);
	// パーティクルセット
	void SetParticle(float x, float y);

};

#endif // __GAME_SELECT_SCENE_H__