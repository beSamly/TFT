#pragma once
#include "SocketServer.h"
#include "SendBuffer.h"
#include "ThreadManager.h"
#include "GameSystem.h"
#include "PacketController.h"

class ServerSystem
{

public:
	sptr<SocketServer> socketServer;
	sptr<ThreadManager> threadManager;
	sptr<GameSystem> gameSystem;
	uptr<PacketController> packetController;

public:
	void Init();
	void StartSocketServer();

private:
	void OnClientRecv(sptr<ClientSession> client, BYTE* buffer, int len);
};

