#include "pch.h"
#include "GameHost.h"
#include "GameData.h"
#include "SkillDataFactory.h"

void GameHost::Init()
{
	// 歹固 Enemy 积己
	//Enemy* e1 = new Enemy(GameData::GetInstance()->GetSpawnPosition());
	//e1->SetTarget(GameData::GetInstance()->GetDestPosition());
	//e1->SetHp(3000);
	//enemyList.push_back(e1);


	////Test..
	//SkillDataFactory::GetInstance();

	//// 歹固 Guardian 积己
	//Guardian* g1 = new Guardian(VectorPos(0,5));
	//g1->SetAttackRange(10);
	//g1->SetEnemyList(&enemyList);
	//guardianList.push_back(g1);


}

void GameHost::UpdateEntityList(float deltaTime)
{
	for (Enemy*& e : enemyList) {
		e->Update(deltaTime);
	}

	for (Guardian*& g : guardianList) {
		g->Update(deltaTime);
	}
}

void GameHost::UpdateDeadEntity(float deltaTime)
{
	for (Enemy*& e : enemyList) {
		if (e->GetHp() <= 0) {
			enemyList.remove(e);
		}
	}
}

void GameHost::Update(float deltaTime)
{
	//TODO : Spawn Entity


	//Entity Update
	UpdateEntityList(deltaTime);
}


