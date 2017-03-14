//------------------------------------------------------------
//! @file Water.h											
//! @brief 水クラスのヘッダファイル 
//! @author 喜田　啓太										
//------------------------------------------------------------
#ifndef __WATER_H__
#define __WATER_H__

#include "cocos2d.h"
#include "Box2D/Box2D.h"
#include "GLES-Render.h"
#include "ui/CocosGUI.h"

class Water : public cocos2d::Node
{
private:
	// パーティクルグループ
	b2ParticleGroup* particleGroup;
	// パーティクルシステム
	b2ParticleSystem* particleSystem;
	// 物理空間のポインタ
	b2World* m_pWorld;
	// ユーザーデーター
	void** userData;
	// 水の画像
	cocos2d::Sprite* water;
public:
	// ブロック作成
	static Water* create(b2World* world,float r, float x, float y);
	// 初期化
	virtual bool init(b2World* world, float r, float x, float y);
	// 更新処理
	void update(float delta)override;
	// パーティクルを設定
	void setParticle(float r,float x,float y);
};

#endif // __WATER_H__

