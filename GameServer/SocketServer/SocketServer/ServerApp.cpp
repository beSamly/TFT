#include "pch.h"

#include "ServerApp.h"
#include "spdlog/spdlog.h"
#include <PacketHeader.h>
#include "MatchSystem.h"

int32 MAX_WORKER_THREAD = 10;
int32 NETWORK_TIME_OUT_MS = 1000;
int32 WORKER_TICK = 64;

ServerApp::ServerApp()
{
    threadSystem = make_shared<ThreadSystem>();
    dataSystem = make_shared<DataSystem>();
    inGameSystem = make_shared<GameSystem>(dataSystem);
    matchSystem = make_shared<MatchSystem>(inGameSystem);
    networkSystem = make_shared<NetworkSystem>(dataSystem, matchSystem);
}

void ServerApp::StartSocketServer()
{
    spdlog::set_level(spdlog::level::debug); // Set global log level to debug

    networkSystem->StartSocketServer();

    // IOCP WorkThread ���� : �� ������Ʈ������ IOCP WorkThread�� IOCP �̺�Ʈ
    // ó�� �� ��Ŷó������ ���
    for (int32 i = 0; i < MAX_WORKER_THREAD; i++)
    {
        threadSystem->Launch(
            [&]()
            {
                while (true)
                {
                    LEndTickCount = ::GetTickCount64() + WORKER_TICK;

                    // ��Ʈ��ũ ����� �� ��Ŷ �ڵ鷯 ����
                    socketServer->GetIocpCore()->HandleIocpEvent(NETWORK_TIME_OUT_MS);

                    // Global Queue �� �ϰ� ����
                    // threadSystem::DoGlobalQueueWork();

                    // JobTimer Queue �� �ϰ� ���� : �ð� ���� Ȥ�� ���͹� �ϰ�
                    // threadSystem::DistributeReservedJobs();
                }
            });
    }

    threadSystem->Join();
}

void ServerApp::StartGameSystem()
{
    inGameSystem->Init();

    //���ӽý��� ������
    threadSystem->Launch([&]() { inGameSystem->Run(); });
    threadSystem->Join();
}

void ServerApp::StartMatchSystem()
{
    threadSystem->Launch([&]() { matchSystem->Run(); });
    threadSystem->Join();
}
