#include "pch.h"
#include "GameSystem.h"

DWORD intervalTick = 1000; // 3초에 한 번씩

void GameSystem::Init()
{
	GameHost* host1 = new GameHost();
	host1->Init();
	gameHostList.push_back(host1);
}

void GameSystem::Run()
{
	DWORD startTime = 0;
	DWORD nextTickTime = GetTickCount() + intervalTick;
	DWORD deltaTime = 0;
	DWORD prevTime = 0;

	while (true) {
		DWORD currentTime = GetTickCount();
		if (startTime == 0) {
			startTime = currentTime;
		}

		DWORD elapsedMils = currentTime - startTime;
		DWORD elapsedSec = elapsedMils / 1000;
		if (currentTime > nextTickTime) {

			deltaTime = currentTime - prevTime;
			prevTime = currentTime;
			nextTickTime += intervalTick;
			cout << "elapsed time is " << elapsedMils / 1000 << " delta time is " << deltaTime << endl;
			Update(elapsedMils / 1000);
		}
	}
}

void GameSystem::Update(float deltaTime)
{
	for (GameHost* gameHost : gameHostList) {
		gameHost->Update(deltaTime);
	}
}

GameSystem::GameSystem()
{
}
