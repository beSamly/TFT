#pragma once
#include "IController.h"
#include "PlayerManager.h"
#include "ClientSession.h"
#include "MatchSystem.h"

class AuthController : public IController
{
private:
    map<int, std::function<void(sptr<ClientSession>&, BYTE*, int32)>> handlers;
    sptr<PlayerManager> playerManager;
    sptr<MatchSystem> matchSystem;

public:
    AuthController(sptr<PlayerManager> p_playerManager, sptr<MatchSystem> p_matchsystem);

    void HandlePacket(sptr<ClientSession>& session, BYTE* buffer, int32 len) override;

private:
    void HandleLoginRequest(sptr<ClientSession>& session, BYTE* buffer, int32 len);
    void HandleLogoutRequest(sptr<ClientSession>& session, BYTE* buffer, int32 len);
};
