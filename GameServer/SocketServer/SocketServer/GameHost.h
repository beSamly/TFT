#pragma once
#include "pch.h"
#include "Command.h"

using Command::ICommand;

class GameHost
{
private:
    USE_LOCK;
    queue<sptr<ICommand>> commandQueue;
    map<int, function<void(sptr<ICommand>)>> commandHandler;
    vector<sptr<ClientSession>> clientVec;

    /* list<Enemy*> enemyList;
     list<Guardian*> guardianList;*/

public:
    GameHost();
    void AddClient(sptr<ClientSession> client) { clientVec.push_back(client); }
    /*list<Enemy*> GetEnemyList() { return enemyList; };
    list<Guardian*> GetGuardianList() { return guardianList; };*/

    void PushCommand(sptr<ICommand> command);

public:
    void Update(float deltaTime);
    void Init();

private:
    void UpdateEntityList(float deltaTime);
    void UpdateDeadEntity(float deltaTime);

private:
    /* Command Handler */
    void HandleBuyCommand(sptr<ICommand> command);
};
