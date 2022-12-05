#include "pch.h"
#include "SocketServer.h"
#include "ClientSession.h"
#include "spdlog/spdlog.h"

SocketServer::SocketServer(sptr<asio::io_context> context, int port) : ioContext(context), AsioBaseSocketServer(context, port)
{

}

void SocketServer::StartAccept()
{
	spdlog::log("Server starting..");
	AsioBaseSocketServer::StartAccept();
}

void SocketServer::OnAccept(sptr<AsioSession> session)
{
	sptr<ClientSession> clientSession = dynamic_pointer_cast<ClientSession>(session);
	OnClientConnect(clientSession);
}

sptr<AsioSession> SocketServer::CreateSession()
{
	sptr<ClientSession> clientSession = make_shared<ClientSession>(ioContext);
	clientSession->OnRecvCallback = OnClientRecv;
	clientSession->OnDisconnectCallback = OnClientDisconnect;
	return clientSession;
}

