#include "pch.h"
#include "PacketController.h"
#include "PacketHeader.h"
#include "PacketId.h"
#include "Login.h"
#include "spdlog/spdlog.h"

PacketController::PacketController()
{
	Init();
}

PacketController::~PacketController()
{
}

void PacketController::Init() {
	_handlers = Vector<IPacketHandler*>(UINT16_MAX, nullptr);
	_handlers[PacketId::LOGIN_REQ] = dynamic_cast<IPacketHandler*>(new PacketHandler::Login());

}

void PacketController::HandlePacket(sptr<ClientSession>& session, BYTE* buffer, int32 len) {

	PacketHeader* header = reinterpret_cast<PacketHeader*>(buffer);
	auto packetId = header->id;

	IPacketHandler* packetHandler = _handlers[packetId];

	if (packetHandler == nullptr) {
		spdlog::error("[PacketController] invalid packetId = {}", packetId);
		return;
	}

	bool requireLogin = packetHandler->RequireLogin();
	if (requireLogin && session->GetPlayer() == nullptr) {
		//Log->Debug(format("[PacketController] invalid packetId = {}", packetId));
		return;
	}

	// 패킷 유효성 검증은 일단 끄기
	/*if (!packetHandler->Validate(session, buffer, len)) {
		spdlog::debug("[PacketController] validation failed for packetId = {}", packetId);
		return;
	}*/

	_handlers[packetId]->HandlePacket(session, buffer, len);
}