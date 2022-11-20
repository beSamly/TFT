using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;

namespace Network
{
    public class Packet
    {
        private byte[] buffer;
        private int packetId;
        private int prefix;

        public Packet(int pfix, int id)
        {
            prefix = pfix;
            packetId = id;
        }

        public void WriteData(byte[] data)
        {
            PacketHeader header;
            header.size = (UInt16)0;
            header.id = (UInt16)0;
            header.prefix = (UInt16)0;

            UInt16 headerLength = (UInt16)Marshal.SizeOf(header);
            UInt16 dataLength = (UInt16)data.Length;
            header.id = (UInt16)packetId;
            header.prefix = (UInt16)prefix;
            header.size = (UInt16)(headerLength + dataLength);

            byte[] byteHeader = new byte[headerLength];
            IntPtr ptr = Marshal.AllocHGlobal(headerLength);
            Marshal.StructureToPtr(header, ptr, true);
            Marshal.Copy(ptr, byteHeader, 0, headerLength);
            Marshal.FreeHGlobal(ptr);

            byte[] returnByte = new byte[byteHeader.Length + data.Length];
            Buffer.BlockCopy(byteHeader, 0, returnByte, 0, byteHeader.Length);
            Buffer.BlockCopy(data, 0, returnByte, byteHeader.Length, data.Length);

            buffer = returnByte;
        }

        public byte[] ToBuffer()
        {
            return buffer;
        }
    }
}
