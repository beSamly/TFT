#pragma once
#include "PacketHeader.h"
#include "SendBuffer.h"

class Packet
{
public:
	Packet(uint16 packetId) { packet_id = packetId; }

private:
	uint16 packet_id;
	sptr<SendBuffer> send_buffer;

public:
	template<typename T>
	void WriteData(T& pkt) ;

	sptr<SendBuffer> ToBuffer();
};

template<typename T>
inline void Packet::WriteData(T& pkt)
{
	const uint16 dataSize = static_cast<uint16>(pkt.ByteSizeLong());
	const uint16 packetSize = dataSize + sizeof(PacketHeader);

	send_buffer = MakeShared<SendBuffer>(packetSize);
	PacketHeader* header = reinterpret_cast<PacketHeader*>(send_buffer->Buffer());

	header->size = packetSize;
	header->id = packet_id;

	ASSERT_CRASH(pkt.SerializeToArray(&header[1], dataSize));
	send_buffer->Close(packetSize);
}
\