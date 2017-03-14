//------------------------------------------------------------
//! @file Block.h											
//! @brief ブロッククラスのヘッダファイル 
//! @author 喜田　啓太										
//------------------------------------------------------------
#ifndef __BLOCK_H__
#define __BLOCK_H__

#include "cocos2d.h"
#include "Box2D/Box2D.h"
#include "ui/CocosGUI.h"

class Block : public cocos2d::Node
{
private:
	// 物理空間のポインタ
	b2World* m_pWorld;
	// ボディのポインタ
	b2Body* m_pBody;
	// ボディの形を決める
	b2PolygonShape m_dynamicBox;
	// ボディの詳細を決める
	b2BodyDef m_bodydef;
	// ボディの備え付けを決める
	b2FixtureDef m_fixturedef;
	// ボディに張り付ける画像
	cocos2d::Sprite* m_sprite;
	// ポジション
	cocos2d::Vec2 m_position;
	// 画像の判定を取るための変数
	cocos2d::Rect m_char;
	// 動かないボディのポインタ
	b2Body* m_groundBody;
	// マウスジョイントのポインタ
	b2MouseJoint* m_mouseJoint;
public:
	// ブロック作成
	static Block* create(b2World* world, float x, float y);
	// 初期化
	virtual bool init(b2World* world,float x, float y);
	// 物理空間初期化
	void initBlockPhysics(float x,float y);
	// タッチ開始
	bool onTouchBegan(cocos2d::Touch * touch, cocos2d::Event * unusedevent);
	// 移動開始
	void onTouchMoved(cocos2d::Touch * touch, cocos2d::Event * unusedevent);
	// 終了
	void onTouchEnded(cocos2d::Touch * touch, cocos2d::Event * unusedevent);
};

#endif // __BLOCK_H__


