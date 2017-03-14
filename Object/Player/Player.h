//------------------------------------------------------------
//! @file Player.h											
//! @brief プレイヤークラスのヘッダファイル 
//! @author 喜田　啓太										
//------------------------------------------------------------
#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "cocos2d.h"
#include "Box2D/Box2D.h"

class Player : public cocos2d::Node
{
private:
	// 物理空間のポインタ
	b2World* m_pWorld;
	// ボディのポインタ
	b2Body* m_pBodyPlayer;
	// ボディの形を決める
	b2PolygonShape m_dynamicPlayerBox;
	// ボディの詳細を決める
	b2BodyDef m_bodydefPlayer;
	// ボディの備え付けを決める
	b2FixtureDef m_fixturedefPlayer;
	// ボディに張り付ける画像
	cocos2d::Sprite* m_spr;
	// プレイヤーの半径
	float m_rad;

public:
	// プレイヤー作成
	static Player* create(b2World* world, float x, float y);
	// 初期化
	virtual bool init(b2World* world, float x, float y);
	// 物理空間初期化
	void initPlayerPhysics(float x, float y);
	// プレイヤーの半径を取得
	float getRadians() { return m_rad; }
	// プレイヤーの画像を取得
	cocos2d::Sprite& getSprite() { return *m_spr; }
};

#endif // __PLAYER_H__
