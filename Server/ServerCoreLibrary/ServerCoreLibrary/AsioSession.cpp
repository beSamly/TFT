#pragma once
#include "pch.h"
#include "AsioSession.h"

//#include <thread>
//#include <cstdlib>
//#include <iostream>
//#include <memory>
//#include <utility>
#include <asio/ts/buffer.hpp>
#include <asio/ts/internet.hpp>
#include <asio/io_context.hpp>


AsioSession::AsioSession(shared_ptr<asio::io_context> context) : socket(*context), recvBuffer(MAX_LENGTH) {	}

AsioSession::~AsioSession()
{

}

void AsioSession::DoRead()
{
	auto self(shared_from_this());
	socket.async_read_some(asio::buffer(recvBuffer.WritePos(), MAX_LENGTH),
		[this, self](std::error_code ec, std::size_t length)
		{
			if (!ec)
			{

				if (recvBuffer.OnWrite(length) == false)
				{
					//Disconnect(L"OnWrite Overflow");
					return;
				}

				int dataSize = recvBuffer.DataSize();
				int processLen = OnRecv(recvBuffer.ReadPos(), dataSize); // ������ �ڵ忡�� ������
				if (processLen < 0 || dataSize < processLen || recvBuffer.OnRead(processLen) == false)
				{
					//Disconnect(L"OnRead Overflow");
					return;
				}

				// Ŀ�� ����
				recvBuffer.Clean();

				DoRead();
			}
			else {
				//OnError();

				OnDisconnect();
			}
		});
}

void AsioSession::Send(shared_ptr<SendBuffer> sendBuffer)
{
	// TODO �ϴ� write_lock���� ������ ���߿��� queue�� ����?
	WRITE_LOCK;
	auto self(shared_from_this());
	asio::async_write(socket, asio::buffer(sendBuffer->GetBuffer(), sendBuffer->WriteSize()),
		[this, self](std::error_code ec, std::size_t /*length*/)
		{
			if (!ec)
			{
				DoRead();
			}
			else {
				OnDisconnect();
			}
		});
}
