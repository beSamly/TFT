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

    // IOCP WorkThread 생성 : 이 프로젝트에서는 IOCP WorkThread가 IOCP 이벤트
    // 처리 후 패킷처리까지 담당
    for (int32 i = 0; i < MAX_WORKER_THREAD; i++)
    {
        threadSystem->Launch(
            [&]()
            {
                while (true)
                {
                    LEndTickCount = ::GetTickCount64() + WORKER_TICK;

                    // 네트워크 입출력 및 패킷 핸들러 실행
                    socketServer->GetIocpCore()->HandleIocpEvent(NETWORK_TIME_OUT_MS);

                    // Global Queue 의 일감 실행
                    // threadSystem::DoGlobalQueueWork();

                    // JobTimer Queue 의 일감 실행 : 시간 예약 혹은 인터벌 일감
                    // threadSystem::DistributeReservedJobs();
                }
            });
    }

    threadSystem->Join();
}

void ServerApp::StartGameSystem()
{
    inGameSystem->Init();

    //게임시스템 쓰레드
    threadSystem->Launch([&]() { inGameSystem->Run(); });
    threadSystem->Join();
}

void ServerApp::StartMatchSystem()
{
    threadSystem->Launch([&]() { matchSystem->Run(); });
    threadSystem->Join();
}
