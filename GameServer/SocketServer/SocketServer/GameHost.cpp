#include "pch.h"
#include "GameHost.h"
#include "SkillDataFactory.h"

using namespace Command;

GameHost::GameHost() {}

namespace
{
#define TO_LAMBDA(FUNC) [&](sptr<ICommand> command) { FUNC(command); }
} // namespace

void GameHost::Init()
{

    commandHandler.emplace((int)CommandId::BUY_COMMAND, TO_LAMBDA(HandleBuyCommand));

    // ���� Enemy ����
    // Enemy* e1 = new Enemy(GameData::GetInstance()->GetSpawnPosition());
    // e1->SetTarget(GameData::GetInstance()->GetDestPosition());
    // e1->SetHp(3000);
    // enemyList.push_back(e1);

    ////Test..
    // SkillDataFactory::GetInstance();

    //// ���� Guardian ����
    // Guardian* g1 = new Guardian(VectorPos(0,5));
    // g1->SetAttackRange(10);
    // g1->SetEnemyList(&enemyList);
    // guardianList.push_back(g1);
}

void GameHost::UpdateEntityList(float deltaTime)
{
    // for (Enemy*& e : enemyList)
    //{
    //     e->Update(deltaTime);
    // }

    // for (Guardian*& g : guardianList)
    //{
    //     g->Update(deltaTime);
    // }
}

void GameHost::UpdateDeadEntity(float deltaTime)
{
    /*for (Enemy*& e : enemyList)
    {
        if (e->GetHp() <= 0)
        {
            enemyList.remove(e);
        }
    }*/
}

void GameHost::PushCommand(sptr<ICommand> command)
{
    WRITE_LOCK;
    commandQueue.push(command);
}

void GameHost::Update(float deltaTime)
{
    // TODO : Spawn Entity

    // Entity Update
    UpdateEntityList(deltaTime);
}

void GameHost::HandleBuyCommand(sptr<ICommand> command) {}