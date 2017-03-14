//------------------------------------------------------------
//! @file BackGroundLayer.h											
//! @brief バックグラウンドレイヤークラスのヘッダファイル            
//! @author 喜田　啓太											
//------------------------------------------------------------
#ifndef __BACK_GROUND_LAYER_H__
#define __BACK_GROUND_LAYER_H__

#include "cocos2d.h"
class BackGroundLayer : public cocos2d::Layer
{
private:
	// 海の背景画像
	cocos2d::Sprite* m_sprite_sea;
	// 空の背景画像
	cocos2d::Sprite* m_sprite_sky;
	// 大きいカニの画像
	cocos2d::Sprite* m_sprite_bigcrab;

public:
	// レイヤー作成
	static BackGroundLayer* create();
	// 初期化
	virtual bool init();
	// カニのアクション
	void Action();
};

#endif // __BACK_GROUND_LAYER_H__




