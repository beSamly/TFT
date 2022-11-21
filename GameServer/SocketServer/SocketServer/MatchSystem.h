#pragma once;
#include "GameSystem.h"

class MatchSystem
{
private:
    sptr<GameSystem> gameSystem;
    queue<sptr<ICommand>> commandQueue;
    map<int, function<void(sptr<ICommand>)>> commandHandler;

public:
    MatchSystem(sptr<GameSystem> p_gameSystem);
    void Run();
    void PushCommand(sptr<ICommand> command);

private:
    USE_LOCK;
    void Update();
    queue<sptr<ICommand>> FlushQueue();
    void ProcessCommand();

private:
    void HandleMatchRequestCommand(sptr<ICommand> command);
};
