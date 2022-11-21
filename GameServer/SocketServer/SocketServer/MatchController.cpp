#include "pch.h"
#include "MatchController.h"
#include "PacketId.h"
#include "MatchSystem.h"

MatchController::MatchController(sptr<MatchSystem> p_matchSystem)
{
    matchSystem = p_matchSystem;

    handlers[(int)PacketId::Match::AI_MATCH_REQ] = TO_LAMBDA(HandleAiMatchRequest);
}

void MatchController::HandlePacket(sptr<ClientSession>& session, BYTE* buffer, int32 len) {}

void MatchController::HandleMatchRequest(sptr<ClientSession>& session, BYTE* buffer, int32 len) {}

void MatchController::HandleAiMatchRequest(sptr<ClientSession>& session, BYTE* buffer, int32 len) {}
