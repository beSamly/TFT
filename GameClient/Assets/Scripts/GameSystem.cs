using Network;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using UnityEngine;

namespace Assets
{
    public class GameSystem : MonoBehaviour
    {

        public NetworkController networkController;
        private PacketController packetController;
        private ThreadManager threadManager;

        private void Awake()
        {
            DontDestroyOnLoad(this);

            networkController = new NetworkController();
            packetController = new PacketController();
            threadManager = new ThreadManager();
        }

        private void Start()
        {
            networkController.Init();
            networkController.SetRecvCallback(OnRecvPacket);
        }

        private void Update()
        {
            threadManager.Update();            
        }

        private void OnRecvPacket(byte[] data)
        {
            if (data.Length < 4)
            {
                //length should be bigger than header size
                return;
            }

            threadManager.ExecuteOnMainThread(() =>
            {
                packetController.HandlePacket(data);
            });
        }
    }
}
