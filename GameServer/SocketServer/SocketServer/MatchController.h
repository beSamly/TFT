#pragma once
#include "IController.h"

class MatchController : public IController
{
private:
	map<int, std::function<void(sptr<ClientSession>&, BYTE*, int32)>> handlers;

public:
	MatchController();

	void HandlePacket(sptr<ClientSession>& session, BYTE* buffer, int32 len) override;

private:
	void HandleAiMatchRequest(sptr<ClientSession>& session, BYTE* buffer, int32 len);
};

