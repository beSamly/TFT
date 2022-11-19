#include "pch.h"
#include "BattleEntity.h"

void BattleEntity::Update(float deltaTime)
{
	if (IsCoolTime()) {
		return;
	}

	for (auto& enemy : *enemyList) {
		bool canAttack = IsWithinAttackRange(enemy);
		if (canAttack) {
			if (IsCoolTime()) {
				//Log->Info("yes can attack");
			}
 			//Log->Info("yes can attack");
		}
	}
}

bool BattleEntity::IsCoolTime()
{
	return false;
}

bool BattleEntity::IsWithinAttackRange(Enemy* enemy) {
	float distance = MathUtil::GetDistanceBetweenTwoPoint(GetPosition(), enemy->GetPosition());
	return distance < attackRange ? true : false;
}

void BattleEntity::UpdateCoolTime()
{
}
