#include "pch.h"
#include "Packet.h"

sptr<SendBuffer> Packet::ToBuffer()
{
	return send_buffer;
}