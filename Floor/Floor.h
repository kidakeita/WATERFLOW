//------------------------------------------------------------
//! @file Floor.h											
//! @brief 水クラスのヘッダファイル 
//! @author 喜田　啓太										
//------------------------------------------------------------
#ifndef __FLOOR_H__
#define __FLOOR_H__

#include "cocos2d.h"
#include "Box2D/Box2D.h"
#include "ui/CocosGUI.h"
#include "GameManager.h"

// ステージフロアのタグ付け
enum {
	Stage_Floor1 = 1,
	Stage_Floor2 ,
	Stage_Floor3 ,
	Stage_Floor4 ,
	Stage_Floor5 ,
	Stage_Floor6 ,
	Stage_Floor7 ,
	Stage_Floor8 ,
};

class Floor : public cocos2d::Node
{
private:
	// ブロックの数
	static const int BLOCK = 3;
	// 大きいブロックの数（460x64）
	static const int LARGE_BLOCK = 3;
	// 普通のブロックの数（200x64）
	static const int MEDIUM_BLOCK = 3;
	// 小さいブロックの数（64x150）
	static const int SMALL_BLOCK = 2;
	// 物理空間のポインタ
	b2World* m_pWorld;
	// ボディのポインタ
	b2Body* m_pfloor[3];
	// ボディの形を決める
	b2PolygonShape m_dynamiclarge[3];
	b2PolygonShape m_dynamicmedium[3];
	b2PolygonShape m_dynamicsmall[3];
	// ボディの詳細を決める
	b2BodyDef m_bodydef[3];
	// ボディの備え付けを決める
	b2FixtureDef m_fix[3];
	// ボディに張り付ける画像
	cocos2d::Sprite* m_smallfloor[BLOCK];
	cocos2d::Sprite* m_mediumfloor[BLOCK];
	cocos2d::Sprite* m_largefloor[BLOCK];
	cocos2d::Sprite* m_floor;
	// ボディのポジション
	int m_bodypos;

public:
	// フロア作成
	static Floor* create(b2World* world);
	// 初期化
	virtual bool init(b2World* world);
	// 物理空間初期化
	void initFloorPhysics();
};

#endif // __FLOOR_H__

