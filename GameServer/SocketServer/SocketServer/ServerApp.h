#pragma once
#include "GameSystem.h"
#include "PacketController.h"
#include "SendBuffer.h"
#include "SocketServer.h"
#include "ThreadSystem.h"
#include "PlayerManager.h"
#include "DataSystem.h"
#include "NetworkSystem.h"
#include "MatchSystem.h"

class ServerApp
{
public:
    sptr<ThreadSystem> threadSystem;
    sptr<GameSystem> inGameSystem;
    sptr<MatchSystem> matchSystem;
    sptr<DataSystem> dataSystem;
    sptr<NetworkSystem> networkSystem;

public:
    ServerApp();

public:
    void StartSocketServer();
    void StartGameSystem();
    void StartMatchSystem();
    void JoinThread() { threadSystem->Join(); };

private:
};
