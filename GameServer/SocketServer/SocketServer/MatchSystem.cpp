#include "pch.h"
#include "MatchSystem.h"
#include "Command.h"

namespace
{
#define TO_LAMBDA(FUNC) [&](sptr<ICommand> command) { FUNC(command); }
} // namespace

using namespace Command::N2M;

MatchSystem::MatchSystem(sptr<GameSystem> p_gameSystem)
{
    gameSystem = p_gameSystem;
    commandHandler.emplace((int)N2M::CommandId::MATCH_REQUEST, TO_LAMBDA(HandleMatchRequestCommand));
    commandHandler.emplace((int)N2M::CommandId::MATCH_CANCEL, TO_LAMBDA(HandleMatchCancelCommand));
    commandHandler.emplace((int)N2M::CommandId::MATCH_ACCEPT, TO_LAMBDA(HandleMatchAcceptCommand));
    commandHandler.emplace((int)N2M::CommandId::MATCH_DECLINE, TO_LAMBDA(HandleMatchDeclineCommand));
}

void MatchSystem::Run()
{
    DWORD intervalTick = 1000; // 1초에 한 번씩

    DWORD nextTickTime = GetTickCount() + intervalTick;
    DWORD prevTickTime = GetTickCount();

    while (true)
    {
        DWORD currentTime = GetTickCount();

        if (currentTime > nextTickTime)
        {
            float deltaTime = currentTime - prevTickTime;
            prevTickTime = currentTime;
            Update(deltaTime);
        }
    }
}

void MatchSystem::PushCommand(sptr<ICommand> command)
{
    WRITE_LOCK;
    commandQueue.push(command);
}

queue<sptr<ICommand>> MatchSystem::FlushQueue()
{
    WRITE_LOCK;
    queue<sptr<ICommand>> copied(commandQueue);
    return copied;
}

void MatchSystem::ProcessCommand()
{
    queue<sptr<ICommand>> copied = FlushQueue();

    while (!copied.empty())
    {
        sptr<ICommand> command = copied.front();
        int commandId = command->GetCommandId();
        if (commandHandler[commandId])
        {
            commandHandler[commandId](command);
        }
        copied.pop();
    }
}

void MatchSystem::CreatePendingMatch()
{
    if (playerMap.size() < playerPerMatch) {
        return;
    }

    for (const auto& [i_playerId, i_player] : playerMap) {
        sptr<PendingMatch> pendingMatch = make_shared<PendingMatch>(playerPerMatch);
        pendingMatch->AddPlayer(i_playerId, i_player);

        for (const auto& [j_playerId, j_player] : playerMap) {

            if (i_playerId == j_playerId) {
                continue;
            }

            if (pendingMatch->IsFull()) {
                break;
            }

            pendingMatch->AddPlayer(j_playerId, j_player);
        }

        // 매칭 성공!
        if (pendingMatch->IsFull()) {
            // playerMap에서 삭제
            vector<int> playerIds = pendingMatch->GetPlayerId();
            int matchId = pendingMatch->GetMatchId();

            for (int playerId : playerIds) {
                playerMap.erase(playerId);
                playerToPendingMatchMap.emplace(playerId, matchId);
            }

            pendingMatchPool.emplace(matchId, pendingMatch);
            continue;
        }
        else {
            //더 이상 매칭될 수 없다. 
            break;
        }
    }
}

void MatchSystem::UpdatePendingMatch(float deltaTime)
{
    for (auto& [matchId, pendingMatch] : pendingMatchPool) {

        pendingMatch->Update(deltaTime);

        if (pendingMatch->IsCanceled()) {
            RemovePendingMatch(pendingMatch);
            continue;
        }

        if (pendingMatch->IsExpired()) {
            RemovePendingMatch(pendingMatch);
            continue;
        }

        if (pendingMatch->IsReady()) {
            // todo GameSystem으로 날리기
            continue;
        }
    }
}

void MatchSystem::RemovePendingMatch(sptr<PendingMatch>& match)
{
    for (const auto& [playerId, player] : match->GetPlayerMap()) {
        playerMap.emplace(playerId, player);
        playerToPendingMatchMap.erase(playerId);
    };
    pendingMatchPool.erase(match->GetMatchId());
}

void MatchSystem::Update(float deltaTime) {
    ProcessCommand();
    UpdatePendingMatch(deltaTime);
    CreatePendingMatch();
}

void MatchSystem::HandleMatchRequestCommand(sptr<ICommand> p_command)
{
    sptr<MatchRequestCommand> command = dynamic_pointer_cast<MatchRequestCommand>(p_command);

    if (!command)
    {
        if (sptr<ClientSession> client = command->client.lock()) {
            int playerId = client->GetPlayer()->playerId;
            sptr<MatchWaitPlayer> player = make_shared<MatchWaitPlayer>();
            player->client = client;
            playerMap.emplace(playerId, player);
        }
    }
}

void MatchSystem::HandleMatchCancelCommand(sptr<ICommand> p_command)
{
    sptr<MatchCancelCommand> command = dynamic_pointer_cast<MatchCancelCommand>(p_command);

    if (!command)
    {
        if (sptr<ClientSession> client = command->client.lock()) {

        }
    }
}

void MatchSystem::HandleMatchAcceptCommand(sptr<ICommand> p_command)
{
    sptr<MatchAcceptCommand> command = dynamic_pointer_cast<MatchAcceptCommand>(p_command);

    if (!command)
    {
        if (sptr<ClientSession> client = command->client.lock()) {

        }
    }
}

void MatchSystem::HandleMatchDeclineCommand(sptr<ICommand> p_command)
{
    sptr<MatchDeclineCommand> command = dynamic_pointer_cast<MatchDeclineCommand>(p_command);

    if (!command)
    {
        if (sptr<ClientSession> client = command->client.lock()) {

        }
    }
}
;