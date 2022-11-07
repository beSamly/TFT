#pragma once
#include "MoveEntity.h"
#include "StatEntity.h"

class Enemy : public MoveEntity, public StatEntity
{
public:
	void Update(float deltaTime);
};

