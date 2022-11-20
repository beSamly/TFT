#pragma once
#include "IController.h"

class AuthController : public IController
{
private:
	map<int, std::function<void(sptr<ClientSession>&, BYTE*, int32)>> handlers;

public:
	AuthController();

	void HandlePacket(sptr<ClientSession>& session, BYTE* buffer, int32 len) override;

private:
	void HandleLoginRequest(sptr<ClientSession>& session, BYTE* buffer, int32 len);
};

