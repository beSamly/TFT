#pragma once
#include "pch.h"
#include "GameHost.h"

class GameSystem
{

public:
	GameSystem();

public:
	void Init();
	void Run();
	void Update(float deltaTime);
private:
	list<GameHost*> gameHostList;
};

