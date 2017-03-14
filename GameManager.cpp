#include "GameManager.h"
USING_NS_CC;

static GameManager* singleton = nullptr;
GameManager* GameManager::getInstance()
{
	if (!singleton)
	{
		singleton = new GameManager();
		if (singleton)
		{
			return singleton;
		}
	}
	return singleton;
}
