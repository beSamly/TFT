#pragma once
#include "GameHost.h"
#include "Command.h"

using namespace Command;

class GameSystem
{

public:
    GameSystem();

public:
    void Init();
    void Run();
    void PushCommand(sptr<ICommand> command);

private:
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

private:
    void HandleCreateDebugModeHost(sptr<ICommand> p_command);
};
