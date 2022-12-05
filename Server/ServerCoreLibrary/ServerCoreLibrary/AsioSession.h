#pragma once
#include "pch.h"
#include <asio/ip/tcp.hpp>
#include "SendBuffer.h"
#include "RecvBuffer.h"

using std::move;
using asio::ip::tcp;
using std::shared_ptr;

class AsioSession
	: public std::enable_shared_from_this<AsioSession>
{
public:
	AsioSession(shared_ptr<asio::io_context> context);

	virtual ~AsioSession();


	tcp::socket socket;


	void Start()
	{
		DoRead();
	}

private:
	void DoRead();
	void Send(shared_ptr<SendBuffer> sendBuffer);

private:
	/* Interface */
	int virtual OnRecv(BYTE* data, int length) abstract;
	void virtual OnDisconnect() abstract;
	void virtual OnConnect() abstract;


private:
	USE_LOCK;
	/* 수신 관련 */
	RecvBuffer				recvBuffer;
	int MAX_LENGTH = 0x10000;
	/* 송신 관련 */
	std::queue<shared_ptr<SendBuffer>>	sendQueue;
};