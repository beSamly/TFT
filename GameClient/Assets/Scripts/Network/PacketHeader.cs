using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Network
{
    public struct PacketHeader
    {
        public UInt16 size;
        public UInt16 id;
    }
}
