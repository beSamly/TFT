#include "pch.h"
#include "NetworkSystem.h"
#include "DataSystem.h"
#include "spdlog/spdlog.h"
#include "PacketController.h"

namespace
{
int32 PORT = 7777;
int32 MAX_SESSION_COUNT = 100;
} // namespace

NetworkSystem::NetworkSystem(sptr<DataSystem> dataSystem, sptr<MatchSystem> matchSystem)
{
    socketServer = make_shared<SocketServer>(NetAddress(L"127.0.0.1", PORT), MAX_SESSION_COUNT);
    packetController = make_unique<PacketController>(dataSystem, matchSystem);
}

void NetworkSystem::StartSocketServer()
{
    //패킷 컨트롤러 초기화
    packetController->Init();

    // 소켓 서버 실행
    socketServer->OnClientRecv = [&](sptr<ClientSession> client, BYTE* buffer, int len)
    { OnClientRecv(client, buffer, len); };
    socketServer->Start();
    spdlog::info("Server listening on {}", PORT);
}

void NetworkSystem::OnClientRecv(sptr<ClientSession> client, BYTE* buffer, int len)
{
    packetController->HandlePacket(client, buffer, len);
}
