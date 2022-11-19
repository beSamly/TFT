#pragma once
#include "Session.h"

/*-----------------
	ClientSession
------------------*/
class Player;
using PlayerRef = std::shared_ptr<Player>;
using std::shared_ptr;
using std::function;

class ClientSession : public Session
{
public:
	ClientSession();
	virtual ~ClientSession();
	shared_ptr<ClientSession> GetClientSessionRef();
	function<void(shared_ptr<ClientSession>, BYTE*, int32)> OnRecvCallback;

public:
	PlayerRef _player = nullptr;
public:
	PlayerRef		GetPlayer();
	void			SetPlayer(PlayerRef player);

private:
	/* 인터페이스 구현 */
	virtual void	OnConnected() override;
	virtual void	OnDisconnected() override;
	virtual void	OnSend(int32 len) override;
	virtual int32	OnRecv(BYTE* buffer, int32 len) override;

private:
	void			OnRecvPacket(BYTE* buffer, int32 len);

public:
	/* 컨텐츠 로직 */
	//void SendLoginResponse(Protocol::LoginResponse pkt);

};
