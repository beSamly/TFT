#include "pch.h"
#include "PlayerManager.h"
#include "Player.h"

void PlayerManager::AddPlayer(sptr<Player> player)
{
    WRITE_LOCK;
    player->playerId = tempPlayerId;
    playerMap->emplace(tempPlayerId, player);
    tempPlayerId++;
    return;
}
void PlayerManager::Update()
{
    /*Vector<PlayerRef> copiedPlayers;
    {
            WRITE_LOCK;
            for (auto const& [accountId, player] : *_players) {
                    copiedPlayers.push_back(player);
            }
    }

    for (auto& player : copiedPlayers) {
            player->Update();
    }*/
}

PlayerManager::PlayerManager()
{
    /*auto job = MakeShared<Job>([this]() {
            this->Update();
    });
    Scheduler::SetInterval(job);*/
}