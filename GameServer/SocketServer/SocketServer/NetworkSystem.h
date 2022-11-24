#pragma once
#include "DataSystem.h"
#include "MatchSystem.h"
#include "PacketController.h"
#include "SocketServer.h"

class NetworkSystem
{
public:
    NetworkSystem(sptr<DataSystem> dataSystem, sptr<MatchSystem> matchSystem);
    void StartSocketServer();
    void HandleIocpEvent(int NETWORK_TIME_OUT_MS);

private:
    sptr<SocketServer> socketServer;
    uptr<PacketController> packetController;

private:
    void OnClientRecv(sptr<ClientSession> client, BYTE* buffer, int len);
};
