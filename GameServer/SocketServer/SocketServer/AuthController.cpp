#include "pch.h"
#include "AuthController.h"
#include "PacketId.h"
#include "PacketHeader.h"
#include "spdlog/spdlog.h"
#include "LoginRequest.pb.h"
#include "LoginResponse.pb.h"
#include "Packet.h"
#include "Player.h"
#include "PlayerManager.h"

AuthController::AuthController(sptr<PlayerManager> p_playerManager)
{
    playerManager = p_playerManager;

    handlers[(int)PacketId::Auth::LOGIN_REQ] = [&](sptr<ClientSession>& client, BYTE* buffer, int32 len)
    { this->HandleLoginRequest(client, buffer, len); };
}

void AuthController::HandlePacket(sptr<ClientSession>& session, BYTE* buffer, int32 len)
{
    PacketHeader* header = reinterpret_cast<PacketHeader*>(buffer);
    auto packetId = header->id;

    if (handlers[packetId])
    {
        handlers[packetId](session, buffer, len);
    }
    else
    {
        spdlog::error("[AuthController] invalid packetId = {}", packetId);
    }
}

void AuthController::HandleLoginRequest(sptr<ClientSession>& session, BYTE* buffer, int32 len)
{
    Protocol::LoginRequest pkt;
    if (pkt.ParseFromArray(buffer + sizeof(PacketHeader), len - sizeof(PacketHeader)) == false)
        return;

    auto email = pkt.email();
    auto password = pkt.password();
    auto w_email = wstring(email.begin(), email.end());

    // 해당 이메일에 계정이 없을 때
    // if (account == nullptr) {
    //	HandleFail(session, "AccountId does not exist");
    //	return;
    //}

    //// 비밀번호가 틀릴 때
    // if (wstring(password.begin(), password.end()) != account->GetPassword()) {
    //	HandleFail(session, "Invalid authentication info");
    // }

    // auto accountId = account->GetAccountId();
    // PlayerRef player = MakeShared<Player>(accountId);

    // Player 세팅

    sptr<Player> player = std::make_shared<Player>();

    playerManager->AddPlayer(player);

    // Response 보내기
    Protocol::LoginResponse response;
    response.set_result(true);

    Packet packet((uint16)PacketId::Auth::LOGIN_RES);
    packet.WriteData<Protocol::LoginResponse>(response);
    session->Send(packet.ToBuffer());
}
