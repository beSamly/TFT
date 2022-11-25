#pragma once;
#include "GameSystem.h"
#include "ClientSession.h"
#include "MatchWaitPlayer.h"
#include "PendingMatch.h"


class MatchSystem
{
private:
    sptr<GameSystem> gameSystem;
    queue<sptr<ICommand>> commandQueue;
    map<int, function<void(sptr<ICommand>)>> commandHandler;
    map<int, sptr<MatchWaitPlayer>> playerMap;
    map<int, int> playerToPendingMatchMap;
    map<int, sptr<PendingMatch>> pendingMatchPool;
    int playerPerMatch = 2;

public:
    MatchSystem(sptr<GameSystem> p_gameSystem);
    void Run();
    void PushCommand(sptr<ICommand> command);

private:
    USE_LOCK;
    void Update(float deltaTime);
    queue<sptr<ICommand>> FlushQueue();
    void ProcessCommand();
    void CreatePendingMatch();
    void UpdatePendingMatch(float deltaTime);
    void RemovePendingMatch(sptr<PendingMatch>& match);

private:
    void HandleMatchRequestCommand(sptr<ICommand> command);
    void HandleMatchCancelCommand(sptr<ICommand> command);
    void HandleMatchAcceptCommand(sptr<ICommand> command);
    void HandleMatchDeclineCommand(sptr<ICommand> command);
};
