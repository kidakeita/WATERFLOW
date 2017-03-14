//------------------------------------------------------------
//! @file Enemy.h											
//! @brief エネミークラスのヘッダファイル 
//! @author 喜田　啓太										
//------------------------------------------------------------
#ifndef __ENEMY_H__
#define __ENEMY_H__

#include "cocos2d.h"
#include "Box2D/Box2D.h"

class Enemy : public cocos2d::Node
{
private:
	// 物理空間のポインタ
	b2World* m_pWorld;
	// ボディのポインタ
	b2Body* m_pBodyEnemy;
	// ボディの形を決める
	b2PolygonShape dynamicEnemyBox;
	// ボディの詳細を決める
	b2BodyDef bodydefEnemy;
	// ボディの備え付けを決める
	b2FixtureDef fixturedefEnemy;
	// ボディに張り付ける画像
	cocos2d::Sprite* m_enemy;
	// 敵の半径
	float m_enemy_rad;
public:
	// エネミー作成
	static Enemy* create(b2World* world, float x, float y);
	// 初期化
	virtual bool init(b2World* world, float x, float y);
	// 物理空間初期化
	void initEnemyPhysics(float x, float y);
	// エネミーの半径を取得
	float getRadians() { return m_enemy_rad; }
	// エネミーの画像を取得
	cocos2d::Sprite& getSprite() { return *m_enemy; }
	// エネミーのアクション
	void Action();
};

#endif // __ENEMY_H__
