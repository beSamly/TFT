#pragma once
#include "DataSystem.h"
#include "MatchSystem.h"
#include "PacketController.h"

class NetworkSystem
{
public:
    NetworkSystem(sptr<DataSystem> dataSystem, sptr<MatchSystem> matchSystem);
    void StartSocketServer();

private:
    sptr<SocketServer> socketServer;
    uptr<PacketController> packetController;

private:
    void OnClientRecv(sptr<ClientSession> client, BYTE* buffer, int len);
};
