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
    public class NetworkController : MonoBehaviour
    {
        private Client client = new Client();
        private PacketController controller = new PacketController();

        private void Awake()
        {
            DontDestroyOnLoad(this);
            client.OnRecv(OnRecvCallback);
            client.Init();
            client.ConnectToServer("127.0.0.1", 7777);
        }

        void Start()
        {

        }

        void Update()
        {

        }

        void OnRecvCallback(byte[] data, int length)
        {
            if(length < 4)
            {
                //length should be bigger than header size
                return;
            }

            controller.HandlePacket(data);
        }
        public void SendLoginRequest(string email)
        {
            LoginRequest req = new LoginRequest();
            req.Email = email;
            req.Password = "password";

            Packet packet = new Packet((int)PacketId.LOGIN_REQ);
            packet.WriteData(req.ToByteArray());
            this.client.SendToServer(packet.ToBuffer());

            // deserialize
            //MessageParser<LoginRequest> parser = LoginRequest.Parser;
            //LoginRequest receivedRequest = parser.ParseFrom(byteData);
        }
    }
}
