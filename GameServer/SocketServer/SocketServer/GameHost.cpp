#include "pch.h"
#include "GameHost.h"
#include "SkillDataFactory.h"
#include "ChampDataFactory.h"
#include "GameStartedState.h"
#include "StandByState.h"
#include "RoundStartedState.h"

using namespace Command;

namespace
{
#define TO_LAMBDA(FUNC) [&](sptr<ICommand> command) { FUNC(command); }
#define SET_CURRENT_STATE_TO_LAMBDA(FUNC) [&](sptr<IGameState> newState) { FUNC(newState); }
} // namespace

GameHost::GameHost(sptr<ChampDataFactory> p_champDataFactory) : champDataFactory(p_champDataFactory)
{
    commandHandler.emplace((int)CommandId::BUY_COMMAND, TO_LAMBDA(HandleBuyCommand));
}

void GameHost::Start() { currentState = make_shared<GameStartedState>(); }

void GameHost::EnterClient(sptr<ClientSession> client)
{
    sptr<InGamePlayer> inGamePlayer = make_shared<InGamePlayer>();
    inGamePlayer->client = client;

    int playerId = client->GetPlayer()->playerId;
    inGamePlayerMap.emplace(playerId, inGamePlayer);
}

void GameHost::PushCommand(sptr<ICommand> command)
{
    WRITE_LOCK;
    commandQueue.push(command);
}

void GameHost::Update(float deltaTime)
{
    currentState->Update(*this, deltaTime);

    if (currentState->IsEnded())
    {
        switch (currentState->GetState())
        {
            case GameState::GAME_STARTED:
                currentState = make_shared<StandByState>();
                // stand_by ���·� ��ȯ
                break;
            case GameState::STAND_BY:
                currentState = make_shared<RoundStartedState>();
                break;

            case GameState::ROUND_STARTED:
                // currentState = make_shared<RoundEndedState>();

                break;
            default:
                break;
        }
    }

    // TODO : Spawn Entity

    // Entity Update
}

void GameHost::InitChampPool(vector<ChampData> champDataVec)
{
    for (ChampData& data : champDataVec)
    {
        int cost = data.cost;

        if (champPool.find(cost) == champPool.end())
        {
            champPool.emplace(cost, vector<ChampData>());
        }
        else
        {
            champPool[cost].push_back(data);
        }
    }
}

void GameHost::HandleBuyCommand(sptr<ICommand> command)
{
    sptr<BuyCommand> buyCommand = dynamic_pointer_cast<BuyCommand>(command);

    if (buyCommand == nullptr)
    {
        // error
        return;
    }

    // �����Ϸ��� champData ������� champion ������ ���� ��ġ�� �־��ֱ�

    sptr<ClientSession> client = command->client.lock();
    if (client == nullptr)
    {
        // client deleted
        return;
    }

    int playerId = client->GetPlayer()->playerId;

    if (!inGamePlayerMap.count(playerId))
    {
        // error
        return;
    }

    sptr<InGamePlayer> inGamePlayer = inGamePlayerMap[playerId];

    // �ش� ������ ������ �ش� è�Ǿ� �����ϴ��� üũ
    int uid = buyCommand->champUid;

    bool isExist = inGamePlayer->champShop.Exist(uid);
    if (!isExist)
    {
        // error
        return;
    }

    int freeBenchIndex = inGamePlayer->bench.GetEmptyBenchIndex();
    if (!freeBenchIndex)
    {
        // Bench is full!!
        return;
    }

    ChampStatData statData = champDataFactory->GetStatData(uid, 1);

    // sptr<Champion> ������ ����
    sptr<Champion> champ = make_shared<Champion>();
    champ->SetBaseStat(statData);

    // bench �� �־��ֱ�
    inGamePlayer->bench.Locate(freeBenchIndex, champ);

    // TODO ��� ����
}

void GameHost::HandleSellCommand(sptr<ICommand> command)
{

    // �Ǹ��ϴ� champ �� star ����ؼ� champPool�� ��ȯ�����ֱ�
}
