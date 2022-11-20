using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using Network;
using Protocol;
using Google.Protobuf;
using System.Runtime.InteropServices;

namespace Network
{
    public class NetworkController
    {
        private Client client = new Client();
        private PacketController controller = new PacketController();

        public void Init()
        {
            client.Init();
            client.ConnectToServer("127.0.0.1", 7777);
        }

        public void SetRecvCallback(Action<byte[]> callback)
        {
            client.OnRecv(callback);
        }

        public void SendLoginRequest(string email)
        {
            LoginRequest req = new LoginRequest();
            req.Email = email;
            req.Password = "password";

            Packet packet = new Packet((int)PacketId.Prefix.AUTH, (int)PacketId.Auth.LOGIN_REQ);
            packet.WriteData(req.ToByteArray());
            this.client.SendToServer(packet.ToBuffer());

            // deserialize
            //MessageParser<LoginRequest> parser = LoginRequest.Parser;
            //LoginRequest receivedRequest = parser.ParseFrom(byteData);
        }

        public void SendAiMatchRequest()
        {
            AiMatchRequest req = new AiMatchRequest();

            Packet packet = new Packet((int)PacketId.Prefix.MATCH, (int)PacketId.Match.AI_MATCH_REQ);
            packet.WriteData(req.ToByteArray());
            this.client.SendToServer(packet.ToBuffer());
        }
    }
}
