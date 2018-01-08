using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading;

namespace AsyncSocketServer
{
    class DaemonThread : Object
    {
        private Thread m_thread;
        private AsyncSocketServer m_asyncSocketServer;

        public DaemonThread(AsyncSocketServer asyncSocketServer)
        {
            m_asyncSocketServer = asyncSocketServer;
            m_thread = new Thread(DaemonThreadStart);
            m_thread.Start();
        }

        public void DaemonThreadStart()
        {
            while (true)
            {
                AsyncSocketUserToken[] userTokenArray = null;
                m_asyncSocketServer.AsyncSocketUserTokenList.CopyList(ref userTokenArray);
                for (int i = 0; i < userTokenArray.Length; i++)
                {
                    if (!m_thread.IsAlive)
                        break;
                    try
                    {
                        if ((DateTime.Now - userTokenArray[i].ActiveDateTime).TotalMilliseconds > m_asyncSocketServer.SocketTimeOutMS) //超时Socket断开
                        {
                            lock (userTokenArray[i])
                            {
                                m_asyncSocketServer.ServerLogic.CloseClientSocket(userTokenArray[i]);
                                m_asyncSocketServer.GCUserToken(userTokenArray[i]);
                            }
                        }
                    }                    
                    catch (Exception E)
                    {
                       Debug.WriteLog.Log(eLogLevel.ell_Error, E.StackTrace);
                    }
                }

                for (int i = 0; i < 60 * 100; i++) //每分钟检测一次
                {
                    //if (!m_thread.IsAlive)
                    //    break;
                    Thread.Sleep(10);
                }
            }
        }

        public void Close()
        {
            m_thread.Abort();
            m_thread.Join();
        }
    }
}
