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
    list<uptr<GameHost>> gameHostList;
    queue<sptr<ICommand>> commandQueue;
    map<int, function<void(sptr<ICommand>)>> commandHandler;

private:
    void HandleCreateDebugModeHost(sptr<ICommand> p_command);
};
