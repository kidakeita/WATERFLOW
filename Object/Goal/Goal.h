//------------------------------------------------------------
//! @file Goal.h											
//! @brief ゴールクラスのヘッダファイル 
//! @author 喜田　啓太										
//------------------------------------------------------------
#ifndef __GOAL_H__
#define __GOAL_H__

#include "cocos2d.h"
#include "Box2D/Box2D.h"

class Goal : public cocos2d::Node
{
private:
	// ゴールの画像
	cocos2d::Sprite* m_spr;
	// ゴールのポジション
	cocos2d::Vec2 m_pos;
	// ゴールの半径
	float m_rad;

public:
	// ゴール作成
	static Goal* create(int x,int y);
	// 初期化
	virtual bool init(int x,int y);
	// ポジションを取得する
	cocos2d::Vec2 getPos() { return m_pos; }
	// ポジションをセットする
	void setPos(cocos2d::Vec2 pos) { m_pos = pos; }
	// ゴールの半径を取得する
	float getRadians() { return m_rad; }
};

#endif // __PLAYER_H__
