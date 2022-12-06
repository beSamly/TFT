#pragma once
#include "PacketController.h"
#include "SocketServer.h"

class NetworkSystem
{
public:
    NetworkSystem();
    void StartSocketServer();
    void HandleIocpEvent(int NETWORK_TIME_OUT_MS);

private:
    sptr<SocketServer> socketServer;
    uptr<PacketController> packetController;

private:
    void OnClientRecv(sptr<ClientSession> client, BYTE* buffer, int len);
    void OnClientDisconnect(sptr<ClientSession> client);
    void OnClientConnect(sptr<ClientSession> client);
};
