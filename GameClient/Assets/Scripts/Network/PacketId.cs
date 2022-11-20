using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;


namespace Network
{
    namespace PacketId
    {
        enum Prefix
        {
            AUTH = 1,
            MATCH
        }

        enum Auth
        {
            LOGIN_REQ = 1,
            LOGIN_RES
        }

        enum Match
        {
            AI_MATCH_REQ = 1,
            AI_MATCH_RES
        }
    }
}
