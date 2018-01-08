using AsyncSocketServer;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Net;
using System.Net.Sockets;
using System.Reflection;
using System.Text;
using System.Threading;
using System.Threading.Tasks;

namespace EngineEditor
{
    struct NetCmd
    {
        public NetCommand cmd;
        public EditorClient client;
    }
    public class TCPServer : IServerLogic
    {
        public static AsyncSocketServer.AsyncSocketServer AsyncSocketSvr;
        private System.Threading.Thread tcpThread;
        private object lock_obj = new object();
        private WriteLog writeLog;
        public FPSChange FrameSpeedChange;
        public LogOutput LogOutputEvent;
        public List<EditorClient> Clients = new List<EditorClient>();
        private List<NetCmd> cmdList1 = new List<NetCmd>();
        private List<NetCmd> cmdList2 = new List<NetCmd>();
        int currentReadList = 1;
        public void BuildingSocketInvokeElement(ref AsyncSocketUserToken userToken)
        {       
            TCPProtocol tcpHandle = new TCPProtocol(AsyncSocketSvr, userToken);
            userToken.AsyncSocketInvokeElement = tcpHandle;
            tcpHandle.MessageReceiveEvent = new SocketTCPEventHandler(
                (object sender, byte[] bMessage) =>
            {
                // TODO 消息解析
                TCPProtocol proto = (TCPProtocol)sender;
                EditorClient client = null;
                if (proto.MessageHandle == null)
                {
                    client = new EditorClient();
                    proto.MessageHandle = client;
                    client.TCPHandle = proto;
                    client.FrameSpeedChange = new FPSChange((int fps) =>
                    {
                        if (FrameSpeedChange != null)
                        {
                            FrameSpeedChange(fps);
                        }
                    });
                    client.LogOutputEvent = new LogOutput((string log) =>
                    {
                        if (LogOutputEvent != null)
                        {
                            LogOutputEvent(log);
                        }
                        
                    });
                    Clients.Add(client);
                }
                else
                {
                    lock(lock_obj)
                    {
                        client = proto.MessageHandle as EditorClient;
                        descMsg(bMessage, client);
                    }
                }
            });
            
            if (userToken.AsyncSocketInvokeElement != null)
            {
                Debug.WriteLog.Log(eLogLevel.ell_Debug, "[ true ]" + "Building socket invoke element " +
                    userToken.AsyncSocketInvokeElement + ".Local Address: " + userToken.ConnectSocket.LocalEndPoint + ", Remote Address: " +
                    userToken.ConnectSocket.RemoteEndPoint);
            }
        }

        private void descMsg(byte[] bMsg, EditorClient client)
        {
            NetCommand cmd = NetService.DescCommand(ref bMsg);
            if (cmd == null)
            {
                return;
            }
            NetCmd nCmd = new NetCmd();
            nCmd.client = client;
            nCmd.cmd = cmd;
            if (currentReadList == 1)
            {
                cmdList2.Add(nCmd);
            }
            else
            {
                cmdList1.Add(nCmd);
            }
            //client.HandleMsg();
            if (bMsg != null && bMsg[0] != 0)
            {
                descMsg(bMsg, client);
            }
        }

        /// <summary>
        /// 开启 监听
        /// </summary>
        public void StartServer()
        {
            writeLog = new WriteLog("Log");
            Debug.WriteLog = writeLog;
            Console.WriteLine("...开始TCP监听");
            IPAddress address = IPAddress.Any;
            int port = 8800;
            int parallelNum = 1000;
            int socketTimeOutMS = 1000;

            AsyncSocketSvr = new AsyncSocketServer.AsyncSocketServer(parallelNum);
            AsyncSocketSvr.ServerLogic = this;
            AsyncSocketSvr.SocketTimeOutMS = socketTimeOutMS;
            AsyncSocketSvr.Init();
            IPEndPoint listenPoint = new IPEndPoint(IPAddress.Any, port);
            AsyncSocketSvr.Start(listenPoint);
        }
        public void CloseClientSocket(AsyncSocketUserToken userToken)
        {
            if (userToken.ConnectSocket == null)
                return;
            string socketInfo = string.Format("Local Address: {0} Remote Address: {1}", userToken.ConnectSocket.LocalEndPoint,
                 userToken.ConnectSocket.RemoteEndPoint);
            Debug.WriteLog.Log(eLogLevel.ell_Debug, "Client connection disconnected. " + socketInfo);
            if (Monitor.TryEnter(lock_obj, 100))
            {
                try
                {
                    TCPProtocol tcp = (TCPProtocol)userToken.AsyncSocketInvokeElement;
                    if (tcp != null && tcp.MessageHandle != null)
                    { 
                        userToken.ConnectSocket.Shutdown(SocketShutdown.Both);
                        userToken.ConnectSocket.Close();
                        userToken.ConnectSocket.Dispose();
                        userToken.ConnectSocket = null; //释放引用，并清理缓存，包括释放协议对象等资源
                    }
                }
                catch (Exception E)
                {
                    Debug.WriteLog.Log(eLogLevel.ell_Error, String.Format("CloseClientSocket Disconnect client {0} error, message: {1}", socketInfo, E.ToString()));
                }
                Monitor.Exit(lock_obj);
            }
        }

        public void ErrorResponseToClient(AsyncSocketUserToken userToken)
        {
           
        }
        
        public void Tick(float deltaTime)
        {
            if (currentReadList == 1)
            {
                for (int i = 0; i < cmdList1.Count; i++)
                {
                    cmdList1[i].client.HandleMsg(cmdList1[i].cmd);
                }
                cmdList1.Clear();
                currentReadList = 2;
            }
            else
            {
                for (int i = 0; i < cmdList2.Count; i++)
                {
                    cmdList2[i].client.HandleMsg(cmdList2[i].cmd);
                }
                cmdList2.Clear();
                currentReadList = 1;
            }
        }

        public void ShutDown()
        {
            AsyncSocketSvr.Stop();
            writeLog.Stop();
        }
    }
}
