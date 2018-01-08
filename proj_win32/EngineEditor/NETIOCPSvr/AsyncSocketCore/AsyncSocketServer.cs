using System;
using System.Text;
using System.Net;
using System.Net.Sockets;
using System.Threading;

namespace AsyncSocketServer
{
    public class AsyncSocketServer
    {

        private Socket listenSocket;
        
        public int m_numConnections; //最大支持连接个数
        public int m_receiveBufferSize; //每个连接接收缓存大小
        public Semaphore m_maxNumberAcceptedClients; //限制访问接收连接的线程数，用来控制最大并发数

        private int m_socketTimeOutMS; //Socket最大超时时间，单位为MS
        public int SocketTimeOutMS { get { return m_socketTimeOutMS; } set { m_socketTimeOutMS = value; } }
               
        public AsyncSocketUserTokenPool m_asyncSocketUserTokenPool;
        public AsyncSocketUserTokenList m_asyncSocketUserTokenList;
        public AsyncSocketUserTokenList AsyncSocketUserTokenList { get { return m_asyncSocketUserTokenList; } }

        private LogOutputSocketProtocolMgr m_logOutputSocketProtocolMgr;
        public LogOutputSocketProtocolMgr LogOutputSocketProtocolMgr { get { return m_logOutputSocketProtocolMgr; } }

        private UploadSocketProtocolMgr m_uploadSocketProtocolMgr;
        public UploadSocketProtocolMgr UploadSocketProtocolMgr { get { return m_uploadSocketProtocolMgr; } }

        private DownloadSocketProtocolMgr m_downloadSocketProtocolMgr;
        public DownloadSocketProtocolMgr DownloadSocketProtocolMgr { get { return m_downloadSocketProtocolMgr; } }
        
        private HttpClientProtocolMgr m_httpClientSocketProtocolMgr;
        public HttpClientProtocolMgr HttpClientSocketProtocolMgr { get { return m_httpClientSocketProtocolMgr; } }
        
        private IServerLogic serverLogic;
        public IServerLogic ServerLogic
        {
            set { serverLogic = value; }
            get { return serverLogic; }
        }
        private DaemonThread m_daemonThread;

        public AsyncSocketServer(int numConnections)
        {
            m_numConnections = numConnections;
            m_receiveBufferSize = ProtocolConst.ReceiveBufferSize;

            m_asyncSocketUserTokenPool = new AsyncSocketUserTokenPool(numConnections);
            m_asyncSocketUserTokenList = new AsyncSocketUserTokenList();
            m_maxNumberAcceptedClients = new Semaphore(numConnections, numConnections);

            m_logOutputSocketProtocolMgr = new LogOutputSocketProtocolMgr();
            m_uploadSocketProtocolMgr = new UploadSocketProtocolMgr();
            m_downloadSocketProtocolMgr = new DownloadSocketProtocolMgr();
            m_httpClientSocketProtocolMgr = new HttpClientProtocolMgr();
        }

        public void Init()
        {
            AsyncSocketUserToken userToken;
            for (int i = 0; i < m_numConnections; i++) //按照连接数建立读写对象
            {
                userToken = new AsyncSocketUserToken(m_receiveBufferSize);
                userToken.TokenID = i;
                userToken.ReceiveEventArgs.Completed += new EventHandler<SocketAsyncEventArgs>(IO_Completed);
                userToken.SendEventArgs.Completed += new EventHandler<SocketAsyncEventArgs>(IO_Completed);
                m_asyncSocketUserTokenPool.Push(userToken);
            }
        }

        public void Start(IPEndPoint localEndPoint)
        {
            try
            {
                listenSocket = new Socket(localEndPoint.AddressFamily, SocketType.Stream, ProtocolType.Tcp);
                listenSocket.Bind(localEndPoint);
                listenSocket.Listen(m_numConnections);
                Debug.WriteLog.Log(eLogLevel.ell_Debug, "Start listen socket " + localEndPoint.ToString() + " success");
                //for (int i = 0; i < 64; i++) //不能循环投递多次AcceptAsync，会造成只接收8000连接后不接收连接了
                StartAccept(null);
                m_daemonThread = new DaemonThread(this);
            }
            catch (Exception ex)
            {
                Console.WriteLine(ex.Message);
            }
        }

        public void Stop()
        {
            listenSocket.Close();
        }

        public void StartAccept(SocketAsyncEventArgs acceptEventArgs)
        {
            if (acceptEventArgs == null)
            {
                acceptEventArgs = new SocketAsyncEventArgs();
                acceptEventArgs.Completed += new EventHandler<SocketAsyncEventArgs>(AcceptEventArg_Completed);
            }
            else
            {
                acceptEventArgs.AcceptSocket = null; //释放上次绑定的Socket，等待下一个Socket连接
            }

            m_maxNumberAcceptedClients.WaitOne(); //获取信号量
            bool willRaiseEvent = listenSocket.AcceptAsync(acceptEventArgs);
            if (!willRaiseEvent)
            {
                ProcessAccept(acceptEventArgs);
            }
        }

        void AcceptEventArg_Completed(object sender, SocketAsyncEventArgs acceptEventArgs)
        {
            try
            {
                ProcessAccept(acceptEventArgs);
            }
            catch (Exception E)
            {
                string error = String.Format("Accept client {0} error, message: {1}\n", acceptEventArgs.AcceptSocket, E.Message);
                Debug.WriteLog.Log(eLogLevel.ell_Error, error + E.StackTrace);  
            }            
        }

        private void ProcessAccept(SocketAsyncEventArgs acceptEventArgs)
        {
             Debug.WriteLog.Log(eLogLevel.ell_Debug,
                "Client connection accepted. Local Address: " + acceptEventArgs.AcceptSocket.LocalEndPoint + ", Remote Address: " + acceptEventArgs.AcceptSocket.RemoteEndPoint);
            AsyncSocketUserToken userToken = m_asyncSocketUserTokenPool.Pop();
            m_asyncSocketUserTokenList.Add(userToken); //添加到正在连接列表
            userToken.ConnectSocket = acceptEventArgs.AcceptSocket;
            userToken.ConnectDateTime = DateTime.Now;

            try
            {
                bool willRaiseEvent = userToken.ConnectSocket.ReceiveAsync(userToken.ReceiveEventArgs); //投递接收请求
                if (!willRaiseEvent)
                {
                    lock (userToken)
                    {
                        ProcessReceive(userToken.ReceiveEventArgs);
                    }
                }                    
            }
            catch (Exception E)
            {
                Debug.WriteLog.Log(eLogLevel.ell_Error, E.StackTrace);    
            
            }            

            StartAccept(acceptEventArgs); //把当前异步事件释放，等待下次连接
        }

        void IO_Completed(object sender, SocketAsyncEventArgs asyncEventArgs)
        {
            AsyncSocketUserToken userToken = asyncEventArgs.UserToken as AsyncSocketUserToken;
            userToken.ActiveDateTime = DateTime.Now;
            try
            {                
                lock (userToken)
                {
                    if (asyncEventArgs.LastOperation == SocketAsyncOperation.Receive)
                        ProcessReceive(asyncEventArgs);
                    else if (asyncEventArgs.LastOperation == SocketAsyncOperation.Send)
                        ProcessSend(asyncEventArgs);
                    else
                        throw new ArgumentException("The last operation completed on the socket was not a receive or send");
                }   
            }
            catch (Exception E)
            {
                Debug.WriteLog.Log(eLogLevel.ell_Error, E.StackTrace);
            }                     
        }

      
        private void ProcessReceive(SocketAsyncEventArgs receiveEventArgs)
        {
            AsyncSocketUserToken userToken = receiveEventArgs.UserToken as AsyncSocketUserToken;
            if (userToken.ConnectSocket == null)
                return;
            userToken.ActiveDateTime = DateTime.Now;
            if (userToken.ReceiveEventArgs.BytesTransferred > 0 && userToken.ReceiveEventArgs.SocketError == SocketError.Success)
            {
                int offset = userToken.ReceiveEventArgs.Offset;
                int count = userToken.ReceiveEventArgs.BytesTransferred;

                if ((userToken.AsyncSocketInvokeElement == null) && (userToken.ConnectSocket != null)) //存在Socket对象，并且没有绑定协议对象，则进行协议对象绑定
                {
                    serverLogic.BuildingSocketInvokeElement(ref userToken);
                    offset = offset + 1;
                    count = count - 1;
                }
                if (userToken.AsyncSocketInvokeElement == null) //如果没有解析对象，提示非法连接并关闭连接
                {
                    //serverLogic.ErrorResponseToClient(userToken);
                    //serverLogic.CloseClientSocket(userToken);
                    GCUserToken(userToken);
                }
                else
                {
                    if (count > 0) //处理接收数据
                    {
                        if (!userToken.AsyncSocketInvokeElement.ProcessReceive(userToken.ReceiveEventArgs.Buffer, offset, count))
                        { //如果处理数据返回失败，则断开连接
                            serverLogic.ErrorResponseToClient(userToken);
                            serverLogic.CloseClientSocket(userToken);
                            GCUserToken(userToken);
                        }
                        else //否则投递下次数据请求
                        {
                            if (userToken.ConnectSocket == null)
                                return;
                            bool willRaiseEvent = userToken.ConnectSocket.ReceiveAsync(userToken.ReceiveEventArgs); //投递接收请求
                            if (!willRaiseEvent)
                                ProcessReceive(userToken.ReceiveEventArgs);
                        }
                    }
                    else
                    {
                        bool willRaiseEvent = userToken.ConnectSocket.ReceiveAsync(userToken.ReceiveEventArgs); //投递接收请求
                        if (!willRaiseEvent)
                            ProcessReceive(userToken.ReceiveEventArgs);
                    }
                }
            }
            else
            {
                //serverLogic.ErrorResponseToClient(userToken);
                serverLogic.CloseClientSocket(userToken);
                GCUserToken(userToken);
            }
        }

        public void GCUserToken(AsyncSocketUserToken userToken)
        {
            for (int i = 0; i < m_asyncSocketUserTokenList.Count; i++)
            {
                if (m_asyncSocketUserTokenList[i] != null && m_asyncSocketUserTokenList[i].TokenID == userToken.TokenID)
                {
                    m_asyncSocketUserTokenList.Remove(userToken);
                    m_asyncSocketUserTokenPool.Push(userToken);
                    break;
                }
            }
        }

        private bool ProcessSend(SocketAsyncEventArgs sendEventArgs)
        {
            AsyncSocketUserToken userToken = sendEventArgs.UserToken as AsyncSocketUserToken;
            if (userToken.AsyncSocketInvokeElement == null)
                return false;
            userToken.ActiveDateTime = DateTime.Now;
            if (sendEventArgs.SocketError == SocketError.Success)
                return userToken.AsyncSocketInvokeElement.SendCompleted(); //调用子类回调函数
            else
            {
                serverLogic.CloseClientSocket(userToken);
                GCUserToken(userToken);
                GCUserToken(userToken);
                return false;
            }
        }

        public bool SendAsyncEvent(Socket connectSocket, SocketAsyncEventArgs sendEventArgs, byte[] buffer, int offset, int count)
        {
            if (connectSocket == null)
                return false;
            if (!connectSocket.Connected)
                return false;
            sendEventArgs.SetBuffer(buffer, offset, count);
            bool willRaiseEvent = connectSocket.SendAsync(sendEventArgs);
            if (!willRaiseEvent)
            {
                return ProcessSend(sendEventArgs);
            }
            else
                return true;
        }

        private object m_lockObj = new object();
      
    }
}
