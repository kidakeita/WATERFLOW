//------------------------------------------------------------
//! @file Floor.cpp											
//! @brief フロアクラスのソースファイル            
//! @author 喜田　啓太											
//------------------------------------------------------------
#include "Floor.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
USING_NS_CC;
#define PTM_RATIO 32

using namespace cocostudio::timeline;

//------------------------------------------------------
//! @brief フロア作成
//! @param 物理空間のポインタ
//! @param なし
//! @return フロアクラスのインスタンスのポインタ
//------------------------------------------------------
Floor* Floor::create(b2World* world)
{
	// インスタンスの作成
	Floor *pRet = new(std::nothrow) Floor();
	//	インスタンスが作成されていて、初期化も成功していたら
	if (pRet && pRet->init(world))
	{
		//	cocosのガーベジコレクタにインスタンスのポインタを登録
		pRet->autorelease();
		//	インスタンスのポインタを返す
		return pRet;
	}
	else
	{
		//	インスタンスを削除
		delete pRet;
		//	ポインタを空に
		pRet = nullptr;
		//	nullptrを返す
		return nullptr;
	}
}

//------------------------------------------------------
//! @brief 初期化
//! @param 物理空間のポインタ
//! @param なし
//! @return 初期化処理の結果　成功(true)　失敗(false)
//------------------------------------------------------
bool Floor::init(b2World * world)
{
	// ノードの初期化が成功していない場合
	if (!Node::init())
	{
		// falseを返す
		return false;
	}
	// 表示対象の物理ワールド
	m_pWorld = world;

	m_bodypos = 0;

	for (int i = 0; i < BLOCK; i++)
	{
		// 64x150の画像
		//****************************************//
		m_smallfloor[i] = Sprite::create("Floor/floor2.png");
		m_smallfloor[i]->setPosition(-100, -100);
		this->addChild(m_smallfloor[i],1);

		// 200x64の画像
		//****************************************//
		m_mediumfloor[i] = Sprite::create("Floor/floor1.png");
		m_mediumfloor[i]->setPosition(-100, -100);
		this->addChild(m_mediumfloor[i],0);

		// 460x64の画像
		//****************************************//
		m_largefloor[i] = Sprite::create("Floor/floor3.png");
		m_largefloor[i]->setPosition(-100, -100);
		this->addChild(m_largefloor[i],2);
	}


	// 物理ワールド初期化
	initFloorPhysics();

	// trueを返す
	return true;
}

//------------------------------------------------------
//! @brief 物理空間初期化
//! @param なし
//! @return なし
//------------------------------------------------------
void Floor::initFloorPhysics()
{
	// ステージの状態フラグ
	switch (GameManager::getInstance()->getFlag())
	{
		// ステージ１のマップ
	case Stage_Floor1:
		// 普通ブロックの数だけループする
		for (int i = 0; i < MEDIUM_BLOCK; i++)
		{
			m_dynamicmedium[i].SetAsBox(200 / 2 / PTM_RATIO, 64 / 2 / PTM_RATIO);
			m_bodydef[i].type = b2_staticBody;
			// ボディのポジションを決める
			switch (m_bodypos)
			{
			case 0:
				m_bodydef[i].position.Set(32 / PTM_RATIO, 32 * 16 / PTM_RATIO);
				m_bodydef[i].angle = MATH_DEG_TO_RAD(90.0f);
				m_bodypos = 1;
				break;
			case 1:
				m_bodydef[i].position.Set(32 * 13 / PTM_RATIO, 32 * 9 / PTM_RATIO);
				m_bodydef[i].angle = MATH_DEG_TO_RAD(0.0f);
				m_bodypos = 2;
				break;
			case 2:
				m_bodydef[i].position.Set(32 * 5 / PTM_RATIO, 32 * 14 / PTM_RATIO);
				m_bodydef[i].angle = MATH_DEG_TO_RAD(0.0f);
				m_bodypos = 0;
				break;
			}
			// 画像貼り付け
			m_bodydef[i].userData = m_mediumfloor[i];
			m_pfloor[1] = m_pWorld->CreateBody(&m_bodydef[i]);

			m_fix[i].shape = &m_dynamicmedium[i];
			m_pfloor[1]->CreateFixture(&m_fix[i]);
		}

		// 小さいブロックの数だけループする
		for (int i = 0; i < SMALL_BLOCK; i++)
		{
			m_dynamicsmall[i].SetAsBox(64 / 2 / PTM_RATIO, 150 / 2 / PTM_RATIO);
			m_bodydef[i].type = b2_staticBody;
			// ボディのポジションを決める
			switch (m_bodypos)
			{
			case 0:
				m_bodydef[i].position.Set(32 * 24 / PTM_RATIO, 32 * 2 / PTM_RATIO);
				m_bodydef[i].angle = MATH_DEG_TO_RAD(0.0f);
				m_bodypos = 1;
				break;
			case 1:
				m_bodydef[i].position.Set(32 * 21 / PTM_RATIO, 32 / PTM_RATIO);
				m_bodydef[i].angle = MATH_DEG_TO_RAD(90.0f);
				break;
			}
			// 画像貼り付け
			m_bodydef[i].userData = m_smallfloor[i];
			m_pfloor[0] = m_pWorld->CreateBody(&m_bodydef[i]);

			m_fix[i].shape = &m_dynamicsmall[i];
			m_pfloor[0]->CreateFixture(&m_fix[i]);
		}
		break;
		// ステージ２のマップ
	case Stage_Floor2:
		// 大きいブロック
		m_dynamiclarge[0].SetAsBox(460 / 2 / PTM_RATIO, 64 / 2 / PTM_RATIO);
		m_bodydef[0].type = b2_staticBody;
		// ボディのポジションを決める
		m_bodydef[0].position.Set(32 * 23 / PTM_RATIO, 32 * 14 / PTM_RATIO);
		m_bodypos = 0;
		m_bodydef[0].fixedRotation = true;
		// 画像貼り付け
		m_bodydef[0].userData = m_largefloor[0];
		m_pfloor[2] = m_pWorld->CreateBody(&m_bodydef[0]);

		m_fix[0].shape = &m_dynamiclarge[0];
		m_fix[0].friction = 0.0f;
		m_pfloor[2]->CreateFixture(&m_fix[0]);

		// 普通ブロックの数だけループする
		for (int i = 0; i < MEDIUM_BLOCK; i++)
		{
			m_dynamicmedium[i].SetAsBox(200 / 2 / PTM_RATIO, 64 / 2 / PTM_RATIO);
			// ボディのポジションを決める
			switch (m_bodypos)
			{
			case 0:
				m_bodydef[i].position.Set(32 / PTM_RATIO, 32 * 16 / PTM_RATIO);
				m_bodydef[i].angle = MATH_DEG_TO_RAD(90.0f);
				m_bodypos = 1;
				break;
			case 1:
				m_bodydef[i].position.Set(32 * 13 / PTM_RATIO, 32 * 7 / PTM_RATIO);
				m_bodydef[i].angle = MATH_DEG_TO_RAD(0.0f);
				m_bodypos = 2;
				break;
			case 2:
				m_bodydef[i].position.Set(32 * 5 / PTM_RATIO, 32 * 14 / PTM_RATIO);
				m_bodydef[i].angle = MATH_DEG_TO_RAD(0.0f);
				m_bodypos = 0;
				break;
			}
			// 画像貼り付け
			m_bodydef[i].userData = m_mediumfloor[i];
			m_pfloor[1] = m_pWorld->CreateBody(&m_bodydef[i]);

			m_fix[i].shape = &m_dynamicmedium[i];
			m_pfloor[1]->CreateFixture(&m_fix[i]);
		}

		// 小さいブロックの数だけループする
		for (int i = 0; i < SMALL_BLOCK; i++)
		{
			m_dynamicsmall[i].SetAsBox(64 / 2 / PTM_RATIO, 150 / 2 / PTM_RATIO);
			// ボディのポジションを決める
			switch (m_bodypos)
			{
			case 0:
				m_bodydef[i].position.Set(32 * 3 / PTM_RATIO, 32 * 2 / PTM_RATIO);
				m_bodydef[i].angle = MATH_DEG_TO_RAD(0.0f);
				m_bodypos = 1;
				break;
			case 1:
				m_bodydef[i].position.Set(32 * 6 / PTM_RATIO, 32 / PTM_RATIO);
				m_bodydef[i].angle = MATH_DEG_TO_RAD(90.0f);
				break;
			}
			// 画像貼り付け
			m_bodydef[i].userData = m_smallfloor[i];
			m_pfloor[0] = m_pWorld->CreateBody(&m_bodydef[i]);

			m_fix[i].shape = &m_dynamicsmall[i];
			m_pfloor[0]->CreateFixture(&m_fix[i]);
		}
		break;

		// ステージ３のマップ
	case Stage_Floor3:
		// 大きいブロックの数だけループする
		for (int i = 0; i < LARGE_BLOCK; i++)
		{
			m_dynamiclarge[i].SetAsBox(460 / 2 / PTM_RATIO, 64 / 2 / PTM_RATIO);
			m_bodydef[i].type = b2_staticBody;
			// ボディのポジションを決める
			switch (m_bodypos)
			{
			case 0:
				m_bodydef[i].position.Set(32 * 6 / PTM_RATIO, 32 * 13 / PTM_RATIO);
				m_bodydef[i].angle = MATH_DEG_TO_RAD(90.0f);
				m_bodypos = 1;
				break;
			case 1:
				m_bodydef[i].position.Set(32 * 12 / PTM_RATIO, 32 * 5 / PTM_RATIO);
				m_bodypos = 2;
				break;
			case 2:
				m_bodydef[i].position.Set(32 * 12 / PTM_RATIO, 32 * 15 / PTM_RATIO);
				m_bodydef[i].angle = MATH_DEG_TO_RAD(90.0f);
				m_bodypos = 0;
				break;

			}
			m_bodydef[i].fixedRotation = true;
			// 画像貼り付け
			m_bodydef[i].userData = m_largefloor[i];
			m_pfloor[2] = m_pWorld->CreateBody(&m_bodydef[i]);

			m_fix[i].shape = &m_dynamiclarge[i];
			m_fix[i].friction = 0.0f;
			m_pfloor[2]->CreateFixture(&m_fix[i]);

		}

		for (int i = 0; i < SMALL_BLOCK; i++)
		{
			m_dynamicsmall[i].SetAsBox(64 / 2 / PTM_RATIO, 150 / 2 / PTM_RATIO);
			switch (m_bodypos)
			{
			case 0:
				m_bodydef[i].position.Set(32 * 15 / PTM_RATIO, 32 * 9 / PTM_RATIO);
				m_bodydef[i].angle = MATH_DEG_TO_RAD(90.0f);
				m_bodypos = 1;
				break;
			case 1:
				m_bodydef[i].position.Set(32 * 20 / PTM_RATIO, 32 * 6 / PTM_RATIO);
				m_bodydef[i].angle = MATH_DEG_TO_RAD(-55.0f);
				break;
			}

			m_bodydef[i].userData = m_smallfloor[i];
			m_pfloor[0] = m_pWorld->CreateBody(&m_bodydef[i]);

			m_fix[i].shape = &m_dynamicsmall[i];
			m_pfloor[0]->CreateFixture(&m_fix[i]);
		}
		break;
		// ステージ４のマップ
	case Stage_Floor4:
		for (int i = 0; i < LARGE_BLOCK; i++)
		{
			m_dynamiclarge[i].SetAsBox(460 / 2 / PTM_RATIO, 64 / 2 / PTM_RATIO);

			m_bodydef[i].type = b2_staticBody;
			switch (m_bodypos)
			{
			case 0:
				m_bodydef[i].position.Set(32 * 7 / PTM_RATIO, 32 * 14 / PTM_RATIO);
				m_bodypos = 1;
				break;
			case 1:
				m_bodydef[i].position.Set(32 * 8 / PTM_RATIO, 32 * 3 / PTM_RATIO);
				m_bodypos = 2;
				break;
			case 2:
				m_bodydef[i].position.Set(32 * 13 / PTM_RATIO, 32 * 8 / PTM_RATIO);
				m_bodypos = 0;
				break;

			}
			m_bodydef[i].fixedRotation = true;
			m_bodydef[i].userData = m_largefloor[i];
			m_pfloor[2] = m_pWorld->CreateBody(&m_bodydef[i]);

			m_fix[i].shape = &m_dynamiclarge[i];
			m_fix[i].friction = 0.0f;
			m_pfloor[2]->CreateFixture(&m_fix[i]);
		}
		for (int i = 0; i < MEDIUM_BLOCK; i++)
		{
			m_dynamicmedium[i].SetAsBox(200 / 2 / PTM_RATIO, 64 / 2 / PTM_RATIO);

			switch (m_bodypos)
			{
			case 0:
				m_bodydef[i].position.Set(32 / PTM_RATIO, 32 * 16 / PTM_RATIO);
				m_bodypos = 1;
				break;
			case 1:
				m_bodydef[i].position.Set(32 * 2 / PTM_RATIO, 32 * 7 / PTM_RATIO);
				m_bodypos = 2;
				break;
			case 2:
				m_bodydef[i].position.Set(32 * 19 / PTM_RATIO, 32 * 12 / PTM_RATIO);
				m_bodypos = 0;
				break;
			}
			m_bodydef[i].angle = MATH_DEG_TO_RAD(90.0f);
			m_bodydef[i].userData = m_mediumfloor[i];
			m_pfloor[1] = m_pWorld->CreateBody(&m_bodydef[i]);

			m_fix[i].shape = &m_dynamicmedium[i];
			m_pfloor[1]->CreateFixture(&m_fix[i]);
		}

		for (int i = 0; i < SMALL_BLOCK; i++)
		{
			m_dynamicsmall[i].SetAsBox(64 / 2 / PTM_RATIO, 150 / 2 / PTM_RATIO);
			switch (m_bodypos)
			{
			case 0:
				m_bodydef[i].position.Set(32 * 16 / PTM_RATIO, 32 * 2 / PTM_RATIO);
				m_bodydef[i].angle = MATH_DEG_TO_RAD(0.0f);
				m_bodypos = 1;
				break;
			case 1:
				m_bodydef[i].position.Set(32 * 19 / PTM_RATIO, 32 / PTM_RATIO);
				m_bodydef[i].angle = MATH_DEG_TO_RAD(90.0f);
				break;
			}

			m_bodydef[i].userData = m_smallfloor[i];
			m_pfloor[0] = m_pWorld->CreateBody(&m_bodydef[i]);

			m_fix[i].shape = &m_dynamicsmall[i];
			m_pfloor[0]->CreateFixture(&m_fix[i]);
		}
		break;
		// ステージ５のマップ
	case Stage_Floor5:
		for (int i = 0; i < LARGE_BLOCK; i++)
		{
			m_dynamiclarge[i].SetAsBox(460 / 2 / PTM_RATIO, 64 / 2 / PTM_RATIO);

			m_bodydef[i].type = b2_staticBody;
			switch (m_bodypos)
			{
			case 0:
				m_bodydef[i].position.Set(32 * 23 / PTM_RATIO, 32 * 3 / PTM_RATIO);
				m_bodypos = 1;
				break;
			case 1:
				m_bodydef[i].position.Set(32 * 23 / PTM_RATIO, 32 * 7 / PTM_RATIO);
				m_bodypos = 2;
				break;
			case 2:
				m_bodydef[i].position.Set(32 * 9 / PTM_RATIO, 32 * 13 / PTM_RATIO);
				m_bodydef[i].angle = MATH_DEG_TO_RAD(90.0f);
				m_bodypos = 0;
				break;

			}
			m_bodydef[i].fixedRotation = true;
			m_bodydef[i].userData = m_largefloor[i];
			m_pfloor[2] = m_pWorld->CreateBody(&m_bodydef[i]);

			m_fix[i].shape = &m_dynamiclarge[i];
			m_fix[i].friction = 0.0f;
			m_pfloor[2]->CreateFixture(&m_fix[i]);
		}
		for (int i = 0; i < MEDIUM_BLOCK - 1; i++)
		{
			m_dynamicmedium[i].SetAsBox(200 / 2 / PTM_RATIO, 64 / 2 / PTM_RATIO);

			switch (m_bodypos)
			{
			case 0:
				m_bodydef[i].position.Set(32 * 13 / PTM_RATIO, 32 * 2 / PTM_RATIO);
				m_bodypos = 1;
				break;
			case 1:
				m_bodydef[i].position.Set(32 * 29 / PTM_RATIO, 32 * 11 / PTM_RATIO);
				m_bodydef[i].angle = MATH_DEG_TO_RAD(90.0f);
				m_bodypos = 0;
				break;
			}

			m_bodydef[i].userData = m_mediumfloor[i];
			m_pfloor[1] = m_pWorld->CreateBody(&m_bodydef[i]);

			m_fix[i].shape = &m_dynamicmedium[i];
			m_pfloor[1]->CreateFixture(&m_fix[i]);
		}
		break;
		// ステージ６のマップ
	case Stage_Floor6:
		for (int i = 0; i < MEDIUM_BLOCK; i++)
		{
			m_dynamicmedium[i].SetAsBox(200 / 2 / PTM_RATIO, 64 / 2 / PTM_RATIO);
			m_bodydef[i].type = b2_staticBody;
			switch (m_bodypos)
			{
			case 0:
				m_bodydef[i].position.Set(32 * 22 / PTM_RATIO, 32 * 12 / PTM_RATIO);
				m_bodydef[i].angle = MATH_DEG_TO_RAD(20.0f);
				m_bodypos = 1;
				break;
			case 1:
				m_bodydef[i].position.Set(32 * 12 / PTM_RATIO, 32 * 9 / PTM_RATIO);
				m_bodydef[i].angle = MATH_DEG_TO_RAD(20.0f);
				m_bodypos = 2;
				break;
			case 2:
				m_bodydef[i].position.Set(32 * 3 / PTM_RATIO, 32 / PTM_RATIO);
				m_bodypos = 0;
				break;
			}
			m_bodydef[i].userData = m_mediumfloor[i];
			m_pfloor[1] = m_pWorld->CreateBody(&m_bodydef[i]);

			m_fix[i].shape = &m_dynamicmedium[i];
			m_pfloor[1]->CreateFixture(&m_fix[i]);
		}

		for (int i = 0; i < SMALL_BLOCK + 1; i++)
		{
			m_dynamicsmall[i].SetAsBox(64 / 2 / PTM_RATIO, 150 / 2 / PTM_RATIO);
			switch (m_bodypos)
			{
			case 0:
				m_bodydef[i].position.Set(32 * 15 / PTM_RATIO, 32 * 9 / PTM_RATIO);
				m_bodydef[i].angle = MATH_DEG_TO_RAD(0.0f);
				m_bodypos = 1;
				break;
			case 1:
				m_bodydef[i].position.Set(32 * 26 / PTM_RATIO, 32 * 13 / PTM_RATIO);
				m_bodydef[i].angle = MATH_DEG_TO_RAD(90.0f);
				m_bodypos = 2;
				break;
			case 2:
				m_bodydef[i].position.Set(32 * 29 / PTM_RATIO, 32 * 14 / PTM_RATIO);
				m_bodydef[i].angle = MATH_DEG_TO_RAD(0.0f);
				break;
			}

			m_bodydef[i].userData = m_smallfloor[i];
			m_pfloor[0] = m_pWorld->CreateBody(&m_bodydef[i]);

			m_fix[i].shape = &m_dynamicsmall[i];
			m_pfloor[0]->CreateFixture(&m_fix[i]);
		}

		break;

		// ステージ７のマップ
	case Stage_Floor7:

		m_dynamiclarge[0].SetAsBox(460 / 2 / PTM_RATIO, 64 / 2 / PTM_RATIO);

		m_bodydef[0].type = b2_staticBody;
		m_bodydef[0].position.Set(32 * 8 / PTM_RATIO, 32 * 14 / PTM_RATIO);
		m_bodypos = 0;
		m_bodydef[0].fixedRotation = true;
		m_bodydef[0].userData = m_largefloor[0];
		m_pfloor[2] = m_pWorld->CreateBody(&m_bodydef[0]);

		m_fix[0].shape = &m_dynamiclarge[0];
		m_fix[0].friction = 0.0f;
		m_pfloor[2]->CreateFixture(&m_fix[0]);

		for (int i = 0; i < MEDIUM_BLOCK; i++)
		{
			m_dynamicmedium[i].SetAsBox(200 / 2 / PTM_RATIO, 64 / 2 / PTM_RATIO);
			switch (m_bodypos)
			{
			case 0:
				m_bodydef[i].position.Set(32 * 2 / PTM_RATIO, 32 * 16 / PTM_RATIO);
				m_bodydef[i].angle = MATH_DEG_TO_RAD(90.0f);
				m_bodypos = 1;
				break;
			case 1:
				m_bodydef[i].position.Set(32 * 14 / PTM_RATIO, 32 * 9 / PTM_RATIO);
				m_bodydef[i].angle = MATH_DEG_TO_RAD(0.0f);
				m_bodypos = 2;
				break;
			case 2:
				m_bodydef[i].position.Set(32 * 19 / PTM_RATIO, 32 * 13 / PTM_RATIO);
				m_bodydef[i].angle = MATH_DEG_TO_RAD(90.0f);
				m_bodypos = 0;
				break;
			}

			m_bodydef[i].userData = m_mediumfloor[i];
			m_pfloor[1] = m_pWorld->CreateBody(&m_bodydef[i]);

			m_fix[i].shape = &m_dynamicmedium[i];
			m_pfloor[1]->CreateFixture(&m_fix[i]);
		}

		for (int i = 0; i < SMALL_BLOCK; i++)
		{
			m_dynamicsmall[i].SetAsBox(64 / 2 / PTM_RATIO, 150 / 2 / PTM_RATIO);
			switch (m_bodypos)
			{
			case 0:
				m_bodydef[i].position.Set(32 * 7 / PTM_RATIO, 32 * 2 / PTM_RATIO);
				m_bodydef[i].angle = MATH_DEG_TO_RAD(0.0f);
				m_bodypos = 1;
				break;
			case 1:
				m_bodydef[i].position.Set(32 * 10 / PTM_RATIO, 32 / PTM_RATIO);
				m_bodydef[i].angle = MATH_DEG_TO_RAD(90.0f);
				break;
			}

			m_bodydef[i].userData = m_smallfloor[i];
			m_pfloor[0] = m_pWorld->CreateBody(&m_bodydef[i]);

			m_fix[i].shape = &m_dynamicsmall[i];
			m_pfloor[0]->CreateFixture(&m_fix[i]);
		}
		break;

		// ステージ８のマップ
	case Stage_Floor8:
		for (int i = 0; i < LARGE_BLOCK - 1; i++)
		{
			m_dynamiclarge[i].SetAsBox(460 / 2 / PTM_RATIO, 64 / 2 / PTM_RATIO);

			m_bodydef[i].type = b2_staticBody;
			switch (m_bodypos)
			{
			case 0:
				m_bodydef[i].position.Set(32 * 11 / PTM_RATIO, 32 * 14 / PTM_RATIO);
				m_bodypos = 1;
				break;
			case 1:
				m_bodydef[i].position.Set(32 * 14 / PTM_RATIO, 32 * 10 / PTM_RATIO);
				m_bodypos = 0;
				break;
			}
			m_bodydef[i].fixedRotation = true;
			m_bodydef[i].userData = m_largefloor[i];
			m_pfloor[2] = m_pWorld->CreateBody(&m_bodydef[i]);

			m_fix[i].shape = &m_dynamiclarge[i];
			m_fix[i].friction = 0.0f;
			m_pfloor[2]->CreateFixture(&m_fix[i]);
		}

		for (int i = 0; i < MEDIUM_BLOCK; i++)
		{
			m_dynamicmedium[i].SetAsBox(200 / 2 / PTM_RATIO, 64 / 2 / PTM_RATIO);
			switch (m_bodypos)
			{
			case 0:
				m_bodydef[i].position.Set(32 * 5 / PTM_RATIO, 32 * 16 / PTM_RATIO);
				m_bodydef[i].angle = MATH_DEG_TO_RAD(90.0f);
				m_bodypos = 1;
				break;
			case 1:
				m_bodydef[i].position.Set(32 * 8 / PTM_RATIO, 32 * 6 / PTM_RATIO);
				m_bodydef[i].angle = MATH_DEG_TO_RAD(90.0f);
				m_bodypos = 2;
				break;
			case 2:
				m_bodydef[i].position.Set(32 * 3 / PTM_RATIO, 32 * 8 / PTM_RATIO);
				m_bodydef[i].angle = MATH_DEG_TO_RAD(90.0f);
				m_bodypos = 0;
				break;
			}

			m_bodydef[i].userData = m_mediumfloor[i];
			m_pfloor[1] = m_pWorld->CreateBody(&m_bodydef[i]);

			m_fix[i].shape = &m_dynamicmedium[i];
			m_pfloor[1]->CreateFixture(&m_fix[i]);
		}
		m_dynamicsmall[0].SetAsBox(64 / 2 / PTM_RATIO, 150 / 2 / PTM_RATIO);
		m_bodydef[0].position.Set(32 * 8 / PTM_RATIO, 32 / PTM_RATIO);
		m_bodydef[0].angle = MATH_DEG_TO_RAD(90.0f);

		m_bodydef[0].userData = m_smallfloor[0];
		m_pfloor[0] = m_pWorld->CreateBody(&m_bodydef[0]);

		m_fix[0].shape = &m_dynamicsmall[0];
		m_pfloor[0]->CreateFixture(&m_fix[0]);

		break;
	}
}