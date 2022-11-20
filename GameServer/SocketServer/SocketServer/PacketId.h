#pragma once

namespace PacketId {

	enum Prefix : uint16 {
		AUTH = 1,
		MATCH
	};

	enum Auth : uint16 {
		LOGIN_REQ = 1,
		LOGIN_RES,
	};

	enum Match : uint16 {
		AI_MATCH_REQ = 1,
		AI_MATCH_RES
	};
}



