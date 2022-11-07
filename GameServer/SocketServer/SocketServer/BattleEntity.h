#pragma once
#include "Enemy.h"

class BattleEntity
{
public:
	BattleEntity() {};

private:
	list<Enemy*>* enemyList;
	int attackRange;
	float coolTime;

private:
	void UpdateCoolTime();
	int GetAttackRange() { return attackRange; }
	bool IsCoolTime();
	bool IsWithinAttackRange(Enemy* enemy);

public:
	void Update(float deltaTime);
	void SetAttackRange(int newAttackRange) { attackRange = newAttackRange; }
	void SetEnemyList(list<Enemy*>* list) { enemyList = list; }

	/* Virtual Method */
public:
	virtual VectorPos GetPosition() abstract;

};

