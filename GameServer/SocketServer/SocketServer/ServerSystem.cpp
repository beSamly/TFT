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

	//��Ŷ ��Ʈ�ѷ� �ʱ�ȭ
	packetController->Init();

	// ���� ���� ����
	socketServer->OnClientRecv = [&](sptr<ClientSession> client, BYTE* buffer, int len) {OnClientRecv(client, buffer, len); };
	socketServer->Start();
	spdlog::info("Server listening on {}", PORT);

	// IOCP WorkThread ���� : �� ������Ʈ������ IOCP WorkThread�� IOCP �̺�Ʈ ó�� �� ��Ŷó������ ���
	for (int32 i = 0; i < MAX_WORKER_THREAD; i++)
	{
		threadManager->Launch([&]()
		{
			while (true)
			{
				LEndTickCount = ::GetTickCount64() + WORKER_TICK;

				// ��Ʈ��ũ ����� �� ��Ŷ �ڵ鷯 ����
				socketServer->GetIocpCore()->HandleIocpEvent(NETWORK_TIME_OUT_MS);

				// Global Queue �� �ϰ� ����
				//ThreadManager::DoGlobalQueueWork();

				// JobTimer Queue �� �ϰ� ���� : �ð� ���� Ȥ�� ���͹� �ϰ�
				//ThreadManager::DistributeReservedJobs();
			}
		});
	}

	//gameSystem->Init();

	////���ӽý��� ������
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
