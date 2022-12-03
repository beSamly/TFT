using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Assets.SceneManager;
using Google.Protobuf;
using Protocol;
using UnityEngine;
using UnityEngine.SceneManagement;

namespace Network
{
    public class MatchController : BaseController
    {
        private Dictionary<int, Action<byte[]>> packetHandler = new Dictionary<int, Action<byte[]>>();

        public MatchController()
        {
            packetHandler.Add((int)PacketId.Match.MATCH_REQ_RES, HandleMatchRequestRes);
            packetHandler.Add((int)PacketId.Match.PENDING_MATCH_CREATED_SEND, HandlePendingMatchCreatedSend);
            packetHandler.Add((int)PacketId.Match.MATCH_CREATED_SEND, HandleMatchCreatedSend);
        }

        public override void HandlePacket(byte[] data)
        {
            PacketHeader header = GetHeader(data);

            if (packetHandler.ContainsKey(header.id))
            {
                packetHandler[header.id].Invoke(data);
            }
            else
            {
                //log error
            }
        }

        private void HandleMatchRequestRes(byte[] data)
        {
            MessageParser<MatchRequestResponse> parser = MatchRequestResponse.Parser;
            MatchRequestResponse response = parser.ParseFrom(data, headerSize, data.Length - headerSize);
            if (response.Result == true)
            {
                // disable button
                LobbySceneManager[] list = GameObject.FindObjectsOfType<LobbySceneManager>();
                LobbySceneManager sceneManager = list[0];
                if (sceneManager)
                {
                    sceneManager.MatchRequested();
                };
            }
        }

        private void HandlePendingMatchCreatedSend(byte[] data)
        {
            // TODO : ACCEPT POP UP
            // disable button
            LobbySceneManager[] list = GameObject.FindObjectsOfType<LobbySceneManager>();
            LobbySceneManager sceneManager = list[0];
            if (sceneManager)
            {
                sceneManager.PendingMatchCreated();
            };
        }

        private void HandleMatchCreatedSend(byte[] data)
        {
            SceneManager.LoadScene("Game");
        }
    }
}
