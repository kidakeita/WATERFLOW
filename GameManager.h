#pragma once
#ifndef __GAME_MANAGER_H__
#define __GAME_MANAGER_H__

#include "cocos2d.h"

class GameManager
{
private:
	int m_flag;
	int m_soundflag;
public :
	static GameManager* getInstance();
	//static void replaceScene(SceneType type);
	// ステージ状態のフラグ
	inline void setFlag(int tempflag) { m_flag = tempflag; }
	inline int getFlag() { return m_flag; }
	// サウンドを止めるためのフラグ
	inline void setSoundFlag(int tempsoundflag) { m_soundflag = tempsoundflag; }
	inline int getSoundFlag() { return m_soundflag; }
};

#endif // __GAME_MANAGER_H__

