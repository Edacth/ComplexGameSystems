using System;
using GameNetworking_1_Server.Server;

namespace GameNetworking_1_Server
{
    class Program
    {
        static int Main(string[] args)
        {
            Console.WriteLine("I am the Server.");
            SynchronousSocketListener.StartListening();
            return 0;
        }
    }
}
