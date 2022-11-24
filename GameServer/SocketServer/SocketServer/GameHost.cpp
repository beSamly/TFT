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
                // stand_by 상태로 전환
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

    // 구매하려는 champData 기반으로 champion 데이터 만들어서 벤치에 넣어주기

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

    // 해당 유저의 상점에 해당 챔피언 존재하는지 체크
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

    // sptr<Champion> 데이터 생성
    sptr<Champion> champ = make_shared<Champion>();
    champ->SetBaseStat(statData);

    // bench 에 넣어주기
    inGamePlayer->bench.Locate(freeBenchIndex, champ);

    // TODO 골드 차감
}

void GameHost::HandleSellCommand(sptr<ICommand> command)
{

    // 판매하는 champ 의 star 계산해서 champPool로 반환시켜주기
}
