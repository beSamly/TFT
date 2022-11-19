#include "pch.h"
#include "ServerSystem.h"
#include <PacketHeader.h>
#include "spdlog/spdlog.h"

namespace {
	int32 WORKER_TICK = 64;
	int32 NETWORK_TIME_OUT_MS = 1000;
	int32 MAX_WORKER_THREAD = 10;
	int32 PORT = 7777;
	int32 MAX_SESSION_COUNT = 100;
}

void ServerSystem::Init()
{
	socketServer = make_shared<SocketServer>(NetAddress(L"127.0.0.1", PORT), MAX_SESSION_COUNT);
	threadManager = make_shared<ThreadManager>();
	gameSystem = make_shared<GameSystem>();
	packetController = make_unique<PacketController>();
}

void ServerSystem::StartSocketServer()
{
	spdlog::set_level(spdlog::level::debug); // Set global log level to debug

	//패킷 컨트롤러 초기화
	packetController->Init();

	// 소켓 서버 실행
	socketServer->OnClientRecv = [&](sptr<ClientSession> client, BYTE* buffer, int len) {OnClientRecv(client, buffer, len); };
	socketServer->Start();
	spdlog::info("Server listening on {}", PORT);

	// IOCP WorkThread 생성 : 이 프로젝트에서는 IOCP WorkThread가 IOCP 이벤트 처리 후 패킷처리까지 담당
	for (int32 i = 0; i < MAX_WORKER_THREAD; i++)
	{
		threadManager->Launch([&]()
		{
			while (true)
			{
				LEndTickCount = ::GetTickCount64() + WORKER_TICK;

				// 네트워크 입출력 및 패킷 핸들러 실행
				socketServer->GetIocpCore()->HandleIocpEvent(NETWORK_TIME_OUT_MS);

				// Global Queue 의 일감 실행
				//ThreadManager::DoGlobalQueueWork();

				// JobTimer Queue 의 일감 실행 : 시간 예약 혹은 인터벌 일감
				//ThreadManager::DistributeReservedJobs();
			}
		});
	}

	//gameSystem->Init();

	////게임시스템 쓰레드
	//threadManager->Launch([&]()
	//{
	//	gameSystem->Run();
	//});

	threadManager->Join();
}

void ServerSystem::OnClientRecv(sptr<ClientSession> client, BYTE* buffer, int len)
{
	packetController->HandlePacket(client, buffer, len);
}
