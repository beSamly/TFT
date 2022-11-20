#include "pch.h"
#include <iostream>

#include "ServerSystem.h"

// TODO ���� ���� �ϵ��ڵ� ���� Config ���Ͽ��� �о������ ����
int32 WORKER_TICK = 64;
int32 NETWORK_TIME_OUT_MS = 1000;
int32 MAX_WORKER_THREAD = 10;
int32 PORT = 7777;
int32 MAX_SESSION_COUNT = 100;

int main() {

	uptr<ServerSystem> server_system = std::make_unique<ServerSystem>();

	server_system->Init();
	server_system->StartSocketServer();

	return 0;
}