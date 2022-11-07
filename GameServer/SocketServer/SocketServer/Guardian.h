#pragma once
#include "BattleEntity.h"
#include "Enemy.h"
#include "MoveEntity.h"
#include "StatEntity.h"

class Guardian : public BattleEntity, public MoveEntity, public StatEntity
{
public:
	Guardian(VectorPos vec) { MoveEntity::SetPosition(vec.x, vec.z); }
	void Update(float deltaTime);

	virtual VectorPos GetPosition() { return MoveEntity::GetPosition(); }

};