using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Net.Sockets;
using AsyncSocketServer;
using System.Diagnostics;

namespace AsyncSocketServer
{
  
    public class HttpClientProtocol : StateObject
    {
        public event SocketConnectEventHandler ClientConnected;
        public event SocketConnectEventHandler ClientDisconnected;
        public event SocketSendMsgEventHandler ClientSendMsg;
        private LogFixedBuffer m_logFixedBuffer;
        public LogFixedBuffer LogFixedBuffer { get { return m_logFixedBuffer; } }

        private AsyncSocketServer httpEntity;
        private Encoding charEncoder = Encoding.UTF8;
        private Tools tool;
        public Dictionary<string, httpEventHandler> KeyHtm;
        public string HtmlContent;
        public int CurrentStep;
        static object lock_object = new object();
        static object lock_return = new object();

        System.Timers.Timer timer = new System.Timers.Timer();

        public HttpClientProtocol(AsyncSocketServer http, AsyncSocketUserToken asyncSocketUserToken)
            : base(http, asyncSocketUserToken)
        {
            KeyHtm = new Dictionary<string, httpEventHandler>();
            m_socketFlag = "HttpClient";
            m_logFixedBuffer = new LogFixedBuffer();
            lock (http.LogOutputSocketProtocolMgr)
            {
                 http.HttpClientSocketProtocolMgr.Add(this);
            }
            httpEntity = http;
            
            Debug.WriteLog.Log(eLogLevel.ell_Info, "客户端连接 ：" + clientSocket.RemoteEndPoint.ToString());
           // bs = new Busness.business();
            timer.Interval = 10000;
            timer.Elapsed += timer_Elapsed;
            tool = new Tools();
        }

        string getTaskList(params string[] param)
        {
            string taskList = "";
            Process[] myProcesses = Process.GetProcesses();
            foreach (Process p in myProcesses)
            {
                taskList += p.ProcessName + "|";
            }
            SendResponse(taskList, "200 OK", HttpExtension.HTML);
            return null;
        }

        void timer_Elapsed(object sender, System.Timers.ElapsedEventArgs e)
        {
            
        }

        public override bool ProcessReceive(byte[] buffer, int offset, int count) //接收异步事件返回的数据，用于对数据进行缓存和分包
        {
            String content = String.Empty;
            this.bBuffer = buffer;
            if (clientSocket.Connected == false)
            {
                return false;
            }
            try
            {
                if (count > 0)
                {
                    this.sbContent.Append(Encoding.ASCII.GetString(
                        this.bBuffer, 0, count));
                    content = this.sbContent.ToString();
                    ProcessCommand(content);
                }
                else
                {
                    Close();
                }
            }
            catch (System.Net.Sockets.SocketException ex)
            {
                ErrorDisconnected(ex.ToString());
            }
            catch (System.InvalidOperationException ex)
            {
                ErrorDisconnected(ex.ToString());
            }
            catch (System.ArgumentNullException ex)
            {
                ErrorDisconnected(ex.ToString());
            }
            catch (System.ArgumentException ex)
            {
                ErrorDisconnected(ex.ToString());
            }
            catch (Exception ex)
            {
                ErrorDisconnected(ex.ToString());
            }
            return true;
        }
        public bool ProcessCommand(string content) //处理分完包的数据，子类从这个方法继承
        {
            string httpMethod = content.Substring(0, content.IndexOf(" "));
             Debug.WriteLog.Log(eLogLevel.ell_Info, content);
            int start = content.IndexOf(httpMethod) + httpMethod.Length + 1;
            int length = content.LastIndexOf("HTTP") - start - 1;
            string requestedUrl = content.Substring(start, length);
            string Referer = tool.GetRefererFromHttpHeader(content);
            string requestedHtm;
            string[] paramter = null;
            if (httpMethod.Equals("GET"))
            {
                requestedHtm = requestedUrl.Split('?')[0];
                requestedUrl = requestedUrl.Remove(0, requestedUrl.IndexOf('?') + 1);
               
                paramter = requestedUrl.Split('?');
                
            }
            else
            {
                Debug.WriteLog.Log(eLogLevel.ell_Info, "暂不支持POST请求");
                SendResponse("暂不支持POST请求", "501", HttpExtension.HTML);
                return false;
            }

            requestedHtm = requestedHtm.Replace("/", @"\").Replace("\\", "").Replace(".", "_");
            // TODO: 根据不同的htm 做不同的处理
            if (ClientSendMsg != null && requestedHtm.Contains("_htm"))
            {
                ClientSendMsg(this, requestedHtm, paramter);
            }
            return true;
        }
        public override bool SendCallback()
        {
            return true;
        }
        public override void Close()
        {
            httpEntity.ServerLogic.CloseClientSocket(this.asyncSocketTocken);
            base.Close();
        }

        protected string SetServerID(params string[] param)
        {
            return "";
        }

        private string GetFile(object data, string param)
        {
            //Socket clientSocket = (Socket)data;
            //string uid = tool.GetJsonCallBackFromUrl(param);
            //string fileName = ServerMainLogic.GetServer().getUserExecName(uid);
            //ServerMainLogic.GetServer().GetHttpResponseEntity().SendExeFileToClient(this, fileName);
            //return fileName;
            return "";
        }
        
        private void notImplemented()
        {
            SendResponse(
                "<html><head><meta http-equiv=\"Content-Type\" content=\"" + HttpExtension.HTML + "; charset=utf-8\"></head><body><h2>LongChengTieJi Web Server</h2><div>501 - Method Not Implemented</div></body></html>",
                "501 Not Implemented", "text/html");

        }

        private void notFound()
        {
            SendResponse(
                "<html><head><meta http-equiv=\"Content-Type\" content=\"" + HttpExtension.HTML + "; charset=utf-8\"></head><body><h2>LongChengTieJi Web Server</h2><div>404 - Not Found</div></body></html>",
                "404 Not Found", "text/html");
        }

        public void SendOkResponse( byte[] bContent, string contentType)
        {
            sendResponse(bContent, "200 OK", contentType);
        }

        // For strings
        public void SendResponse( string strContent, string responseCode,
                                  string contentType)
        {
            byte[] bContent = charEncoder.GetBytes(strContent);
            sendResponse( bContent, responseCode, contentType);
        }

        /// <summary>
        /// 响应请求
        /// </summary>
        /// <param name="client"></param>
        /// <param name="bContent">发送的内容</param>
        /// <param name="responseCode"></param>
        /// <param name="contentType"></param>
        public void sendResponse( byte[] bContent, string responseCode,
                                  string contentType)
        {
            try
            {
                byte[] bHeader = charEncoder.GetBytes(
                                    "HTTP/1.1 " + responseCode + "\r\n"
                                  + "Server: LongChengTieJi Web Server\r\n"
                                  + "Content-Length: " + bContent.Length.ToString() + "\r\n"
                                  + "Connection: close\r\n"
                                  + "Content-Type: " + contentType + "\r\n\r\n");
                if (clientSocket == null)
                    return;
                clientSocket.Send(bHeader);
                //clientSocket.Send(bContent);
                httpEntity.SendAsyncEvent(clientSocket, m_asyncSocketUserToken.SendEventArgs, bContent, 0, bContent.Length);
                //disconnected("成功关闭");
                //send(client, bContent);
            }
            catch (System.ArgumentNullException ex)
            {
                ErrorDisconnected(ex.ToString());
            }
            catch (System.Net.Sockets.SocketException ex)
            {
                ErrorDisconnected(ex.ToString());
            }
            catch (System.ObjectDisposedException ex)
            {
                ErrorDisconnected(ex.ToString());
            }
            catch (Exception ex)
            {
                ErrorDisconnected(ex.ToString());
            }
        }

        public override bool SendCompleted()
        {
            if (base.SendCompleted())
            {
                //ServerMainLogic.AsyncSocketSvr.CloseClientSocket(this.asyncSocketTocken);
                return true;
            }
            return false;
        }

        /// <summary>
        /// 网页重定向
        /// </summary>
        /// <param name="client"></param>
        /// <param name="url"></param>
        public void Redirect(string url)
        {
            if (clientSocket.Connected == true)
            {
                string htmlPage = "<HTML><head> <meta HTTP-EQUIV=\"REFRESH\" content=\"0; url=" + url + "\"></head></HTML>";
                sendResponse( charEncoder.GetBytes(htmlPage), "200 OK", HttpExtension.HTML);
            }
        }

        /// <summary>
        /// 关闭Socket
        /// </summary>
        /// <param name="client"></param>
        /// <param name="msg">output message</param>
        private void ErrorDisconnected(string msg)
        {
            if (ClientDisconnected != null)
            {
                SocketConnectEventArgs se = new SocketConnectEventArgs();
                se.httpContent = msg;
                se.client = this;
                se.Event = "断开连接 ： time:" + tool.GetTimeStamp();
                if (this.clientSocket.Connected == true)
                {
                    ClientDisconnected(this, se);
                }
            }
            if (clientSocket.Connected == true && clientSocket != null)
            {
                try
                {
                    string errString = "501 Not Implemented";
                    byte[] bHeader = charEncoder.GetBytes(
                                       "HTTP/1.1 501\r\n"
                                     + "Server: LongChengTieJi Web Server\r\n"
                                     + "Content-Length: " + errString.Length + "\r\n"
                                     + "Connection: close\r\n"
                                     + "Content-Type: " + HttpExtension.HTML + "\r\n\r\n");
                    clientSocket.Send(bHeader);
                    clientSocket.Send(charEncoder.GetBytes("501 Not Implemented"));
                }
                catch { }
            }
             Debug.WriteLog.Log(eLogLevel.ell_Error, msg);
            this.Close();
            GC.Collect();
        }
    }
}
public class HttpClientProtocolMgr : Object
{
    private List<HttpClientProtocol> m_list;

    public HttpClientProtocolMgr()
    {
        m_list = new List<HttpClientProtocol>();
    }

    public int Count()
    {
        return m_list.Count;
    }

    public HttpClientProtocol ElementAt(int index)
    {
        return m_list.ElementAt(index);
    }

    public void Add(HttpClientProtocol value)
    {
       // m_list.Add(value);
    }

    public void Remove(HttpClientProtocol value)
    {
        m_list.Remove(value);
    }
}