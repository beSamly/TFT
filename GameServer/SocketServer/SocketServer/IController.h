#pragma once
class IController
{
public:
	virtual void HandlePacket(sptr<ClientSession>& session, BYTE* buffer, int32 len) abstract;
};

