#include "pch.h"
#include "GameData.h"

GameData::GameData()
{
	route.push_back(new VectorPos(1000, 0));
	spawnPosition.SetX(0);
	spawnPosition.SetZ(0);
}

GameData* GameData::GetInstance()
{
	static GameData* instance = new GameData();
	return instance;
}

VectorPos GameData::GetSpawnPosition()
{
	return spawnPosition;
}

VectorPos GameData::GetDestPosition()
{
	return VectorPos(1000, 0);
}
