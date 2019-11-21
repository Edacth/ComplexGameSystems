using System;
using GameNetworking_1_Client.Client;

namespace GameNetworking_1_Client
{
    class Program
    {
        static int Main(string[] args)
        {
            Console.WriteLine("I am the Client.");
            SynchronousSocketClient.StartClient();
            return 0;
        }
    }
}
