#pragma once
struct PacketHeader
{
	uint16 size;
	uint16 prefix;
	uint16 id; // 프로토콜ID (ex. 1=로그인, 2=이동요청)
};

