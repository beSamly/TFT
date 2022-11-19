using Google.Protobuf;
using Protocol;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;

namespace Network
{
    public class PacketController
    {
        public PacketController()
        {
            packetHandler.Add((int)PacketId.LOGIN_RES, HandleLoginRes);
        }

        private Dictionary<int, Action<byte[]>> packetHandler = new Dictionary<int, Action<byte[]>>();
        private int headerSize = Marshal.SizeOf(typeof(PacketHeader));

        private PacketHeader GetHeader(byte[] data)
        {
            if (headerSize > data.Length)
            {
                throw new Exception();
            }

            IntPtr ptr = Marshal.AllocHGlobal(headerSize);

            Marshal.Copy(data, 0, ptr, headerSize);

            PacketHeader header = (PacketHeader)Marshal.PtrToStructure(ptr, typeof(PacketHeader));

            Marshal.FreeHGlobal(ptr);

            return header;
        }
        public void HandlePacket(byte[] data)
        {
            PacketHeader header = GetHeader(data);

            if (packetHandler.ContainsKey(header.id))
            {
                packetHandler[header.id].Invoke(data);
            } else
            {
                //log error
            }
        }

        private void HandleLoginRes(byte[] data)
        {
            MessageParser<LoginResponse> parser = LoginResponse.Parser;
            LoginResponse response = parser.ParseFrom(data, headerSize, data.Length - headerSize );
            if(response.Result == true)
            {
                //move to next scene
            } else
            {
                //error
            }
        }
    }
}
