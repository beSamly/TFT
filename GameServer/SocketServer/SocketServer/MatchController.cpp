#include "pch.h"
#include "MatchController.h"
#include "PacketId.h"

MatchController::MatchController()
{
	handlers[(int)PacketId::Match::AI_MATCH_REQ] = [&](sptr<ClientSession>& client, BYTE* buffer, int32 len) { this->HandleAiMatchRequest(client, buffer, len); };
}

void MatchController::HandlePacket(sptr<ClientSession>& session, BYTE* buffer, int32 len)
{
}

void MatchController::HandleAiMatchRequest(sptr<ClientSession>& session, BYTE* buffer, int32 len)
{
}
