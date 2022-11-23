#pragma once
#include "pch.h"
#include "Command.h"
#include "ChampDataFactory.h"
#include "InGamePlayer.h"
#include "IGameState.h"

using Command::ICommand;

class GameHost
{
private:
    USE_LOCK;
    sptr<IGameState> currentState;
    queue<sptr<ICommand>> commandQueue;
    map<int, function<void(sptr<ICommand>)>> commandHandler;

    /* Data */
    sptr<ChampDataFactory> champDataFactory;

public:
    map<int, vector<ChampData>> champPool;
    map<int, sptr<InGamePlayer>> inGamePlayerMap;

public:
    GameHost(sptr<ChampDataFactory> p_champDataFactory);
    void Start();

    void EnterClient(sptr<ClientSession> client);
    void PushCommand(sptr<ICommand> command);
    void Update(float deltaTime);
    void InitChampPool(vector<ChampData> champDataVec);

private:
    void SetCurrentState(sptr<IGameState> newState) { currentState = newState; }

private:
    /* Command Handler */
    void HandleBuyCommand(sptr<ICommand> command);
    void HandleSellCommand(sptr<ICommand> command);
};
