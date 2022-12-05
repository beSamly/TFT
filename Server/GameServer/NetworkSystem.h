#pragma once
#include "DataSystem.h"
#include "PacketController.h"
#include "SocketServer.h"

class NetworkSystem
{
public:
	NetworkSystem(sptr<DataSystem> dataSystem);
	void StartSocketServer();
	void HandleIocpEvent(int NETWORK_TIME_OUT_MS);

private:
	sptr<SocketServer> socketServer;
	uptr<PacketController> packetController;
	sptr<DataSystem> dataSystem;

private:
	void OnClientRecv(sptr<ClientSession> client, BYTE* buffer, int len);
	void OnClientDisconnect(sptr<ClientSession> client);
	void OnClientConnect(sptr<ClientSession> client);
};
