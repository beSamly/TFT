#pragma once
#include "pch.h"
#include "Enemy.h"
#include "Guardian.h"
#include "GameData.h"

class GameHost
{
private:
	list<Enemy*> enemyList;
	list<Guardian*> guardianList;
public:
	list<Enemy*> GetEnemyList() { return enemyList; };
	list<Guardian*> GetGuardianList() { return guardianList; };

public:
	void Update(float deltaTime);
	void Init();

private:
	void UpdateEntityList(float deltaTime);
	void UpdateDeadEntity(float deltaTime);
};

