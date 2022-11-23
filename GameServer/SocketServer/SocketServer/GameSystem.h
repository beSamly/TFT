#pragma once
#include "GameHost.h"
#include "Command.h"
#include "DataSystem.h"

using namespace Command;

class GameSystem
{

public:
    GameSystem(sptr<DataSystem> p_dataSystem);

public:
    void Init();
    void Run();
    void PushCommand(sptr<ICommand> command);

private:
    sptr<DataSystem> dataSystem;

private:
    void Update(float deltaTime);
    queue<sptr<ICommand>> FlushQueue();
    void ProcessCommand();

private:
    USE_LOCK;
    map<int, sptr<GameHost>> gameHostMap;
    queue<sptr<ICommand>> commandQueue;
    map<int, function<void(sptr<ICommand>)>> commandHandler;
    int hostId = 1; // temp
    sptr<GameHost> CreateHost();

private:
    void HandleCreateDebugModeHost(sptr<ICommand> p_command);
};
