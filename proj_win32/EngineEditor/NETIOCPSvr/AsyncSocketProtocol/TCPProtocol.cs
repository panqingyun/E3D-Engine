using System;
using System.Collections.Generic;
using System.Linq;
using System.Net;
using System.Net.Sockets;
using System.Text;

namespace AsyncSocketServer
{
    // State object for reading client data asynchronously
    public class StateObject : BaseSocketProtocol
    {
        public StateObject(AsyncSocketServer svr, AsyncSocketUserToken asyncSocketUserToken)
            : base(svr, asyncSocketUserToken) 
        {
            server = svr;

            this.asyncSocketTocken = asyncSocketUserToken;
            this.clientSocket = asyncSocketUserToken.ConnectSocket;

            IPEndPoint clientipe = (IPEndPoint)clientSocket.RemoteEndPoint;
            ClientIPAddress = clientipe.Address.ToString();
        }
        // Client  socket.
        public Socket clientSocket = null;
        // Size of receive buffer.
        public const int BufferSize = 1024 * 6;
        // Receive buffer.
        public byte[] bBuffer = new byte[BufferSize];
        // Received data string.
        public StringBuilder sbContent = new StringBuilder();
        // user tocken
        protected AsyncSocketUserToken asyncSocketTocken;

        protected AsyncSocketServer server;
        public string ClientIPAddress;
    }

    public class TCPProtocol : StateObject
    {
        public Object MessageHandle;
        public SocketTCPEventHandler MessageReceiveEvent;
        public EventHandler MessageSendComplete;
        public EventHandler MessageSendCallback;
        private List<byte[]> sendList = new List<byte[]>();
        public TCPProtocol(AsyncSocketServer svr, AsyncSocketUserToken asyncSocketUserToken)
            : base(svr, asyncSocketUserToken)
        {
           
        }

        public override bool ProcessReceive(byte[] buffer, int offset, int count) //接收异步事件返回的数据，用于对数据进行缓存和分包
        {
            if (clientSocket.Connected == false)
            {
                return false;
            }
            try
            {
                if (count > 0)
                {
                    ProcessCommand(buffer);
                }
            }
            catch (Exception ex)
            {
                Debug.Error(ex.ToString());
            }
            return true;
        }

        public bool ProcessCommand(byte[] content) //处理分完包的数据，子类从这个方法继承
        {
            if (MessageReceiveEvent != null)
            {
                MessageReceiveEvent(this, content);
                return true;
            }
            return false;
        }
        public override bool SendCallback()
        {
            if (MessageSendCallback != null)
            {
                MessageSendCallback(this, null);
            }
            return true;
        }
        public override void Close()
        {
            server.ServerLogic.CloseClientSocket(this.asyncSocketTocken);
            base.Close();
        }

        public override bool SendCompleted()
        {
            if (base.SendCompleted())
            {
                sendList.RemoveAt(0);
                if (MessageSendComplete != null)
                {
                    MessageSendComplete(this, null);
                }
                if (sendList.Count > 0)
                {
                    byte[] bContent = sendList[0];
                    server.SendAsyncEvent(clientSocket, m_asyncSocketUserToken.SendEventArgs, bContent,0, bContent.Length);
                }
                return true;
            }
            return false;
        }
        public void sendMessage(byte[] bContent)
        {
            try
            {
                sendList.Add(bContent);
                if (sendList.Count == 1)
                {
                    server.SendAsyncEvent(clientSocket, m_asyncSocketUserToken.SendEventArgs, bContent, 0, bContent.Length);
                }
            }
            catch (Exception ex)
            {
                Debug.Error(ex.ToString());
            }
        }
    }
}
