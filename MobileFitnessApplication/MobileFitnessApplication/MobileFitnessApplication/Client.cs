using System;
using System.Collections.Generic;
using System.Net;
using System.Net.Sockets;
using System.Text;

namespace MobileFitnessApplication
{
    class Client
    {
        private Socket sender;
        private IPAddress ipAddress;
        private readonly IPEndPoint remoteEP;
        byte[] bytes = new byte[1024];


        /// <summary>
        /// Create client object
        /// </summary>
        /// <param name="ip">server ip adress</param>
        /// <param name="serverport">port number of server</param>
        public Client(string ip, int serverport)
        {
            ipAddress = IPAddress.Parse(ip);
            remoteEP = new IPEndPoint(ipAddress, serverport);
        }

        /// <summary>
        /// Opens connection to server
        /// </summary>
        public void OpenConnection()
        {
            sender = new Socket(ipAddress.AddressFamily, SocketType.Stream, ProtocolType.Tcp);
            sender.Connect(remoteEP);
        }

        /// <summary>
        /// Closes connection to server
        /// </summary>
        public void CloseConnection()
        {
            sender.Shutdown(SocketShutdown.Both);
            sender.Close();
        }

        /// <summary>
        /// Send command to server
        /// Use this when you don't expect a response
        /// </summary>
        /// <param name="command">Command to send to server (Only send one character!)</param>
        public void Send(string command)
        {
            byte[] cmd = Encoding.ASCII.GetBytes(command);
            sender.Send(cmd);
        }

        /// <summary>
        /// Send command to server
        /// Use this one when you expect e response from the server
        /// The response is a string
        /// </summary>
        /// <param name="command">Command to send to server (Only send one character!)</param>
        /// <returns>Response from server as a string</returns>
        public string Recieve(string command)
        {
            Send(command);
            try
            {
                int bytesRec = sender.Receive(bytes);
                return Encoding.ASCII.GetString(bytes, 0, bytesRec);
            }catch(Exception e)
            {
                return e.ToString();
            }
        }
    }
}
