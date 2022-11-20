#include "pch.h"
#include "PacketController.h"
#include "PacketHeader.h"
#include "PacketId.h"
#include "Login.h"
#include "spdlog/spdlog.h"
#include "MatchController.h"
#include "AuthController.h"

PacketController::PacketController()
{
	Init();
}

PacketController::~PacketController()
{
}

void PacketController::Init() {
	controllerMap.emplace((int)PacketId::Prefix::AUTH, make_shared<AuthController>());
	controllerMap.emplace((int)PacketId::Prefix::MATCH, make_shared<MatchController>());
}

void PacketController::HandlePacket(sptr<ClientSession>& session, BYTE* buffer, int32 len) {

	PacketHeader* header = reinterpret_cast<PacketHeader*>(buffer);
	auto prefix = header->prefix;

	sptr<IController> controller = controllerMap[prefix];

	if (controller) {
		controller->HandlePacket(session, buffer, len);
	}
	else {
		spdlog::error("[PacketController] invalid prefix = {}", prefix);
	}
}