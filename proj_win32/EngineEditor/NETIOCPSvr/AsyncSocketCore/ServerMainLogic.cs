using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Net;
using System.IO;
using System.Configuration;
using log4net.Repository.Hierarchy;
using log4net;

namespace AsyncSocketServer
{
    public class ServerMainLogic
    {
        private string requestUrl = "http://42.51.131.153:8082/plugin_watch.htm";
        public string RequestUrl { set { requestUrl = value; } get { return requestUrl; } }
        private Dictionary<string, string> gameLoginUrl = new Dictionary<string, string>();
        public Dictionary<string, string> GameLoginUrl { set { gameLoginUrl = value; } get { return gameLoginUrl; } }
        public List<int> platform = new List<int>();
        
        
        private static object m_threadObj = new object();
        private Dictionary<string, string> userExecInfo = new Dictionary<string, string>();
        private static ServerMainLogic server;
        private Tools tool;
        private int clearTime = 1000 * 60 * 60 * 2;
        private List<KeyValuePair<string, httpInfo>> keyUrlQueue1 = new List<KeyValuePair<string, httpInfo>>();
        private List<KeyValuePair<string, httpInfo>> keyUrlQueue2 = new List<KeyValuePair<string, httpInfo>>();
        private int CurrentWriteQueue = 1;
        public string PluginUpLoadServerID = "2";
        private WriteLog writeLog;
        private bool isInitilised = false;
        private System.Threading.Thread httpThread;
        private Busness.business bs;
        private System.Timers.Timer timer;
        public event EventHandler ServerClose;
        public event SocketConnectEventHandler ClientConnected;
        public event SocketConnectEventHandler ClientDisConnected;
        private bool canClearData = false;
        public int MaxStep = 16;

        public static ILog Logger;
        public static AsyncSocketServer AsyncSocketSvr;
        public static string FileDirectory;

        /// <summary>
        /// 获取实例
        /// </summary>
        /// <returns></returns>
        public static ServerMainLogic GetServer()
        {
            if (server == null)
            {
                server = new ServerMainLogic();
            }
            return server;
        }
        private ServerMainLogic() 
        {
        }

        /// <summary>
        /// 主逻辑循环
        /// </summary>
        public void ServerRun()
        {
            while (true)
            {
                try
                {
                    ReadKeyUrlQueue();
                    Busness.business.SaveUserPluginDataInDB();

                }
                catch (Exception ex)
                {
                    WriteLog(eLogLevel.ell_Error, ex.Message);
                }
                if (canClearData == true)
                {
                    clearData();
                }
            }
        }

        /// <summary>
        /// 初始化
        /// </summary>
        public void Initilised(int port)
        {
            if (isInitilised == true)
            {
                return;
            }
            Busness.business.GetPluginNumberEvent += new Busness.GetPluginNumEventHandler(business_GetPluginNumberEvent);
            //Dictionary<string, string> url = new Dictionary<string, string>();
            //ReadXML.ReadUrlFromXML("urlConfig.xml",ref url);
            //RequestUrl = url["RequestUrl"];

            writeLog = new WriteLog("E:\\webServerLog");   
            bs = new Busness.business();
            tool = new Tools();
            timer = new System.Timers.Timer(clearTime);
            timer.Elapsed += new System.Timers.ElapsedEventHandler(timer_Elapsed);
            timer.Enabled = true;
            timer.AutoReset = true;
            timer.Start();
            isInitilised = true;
        }

        private void business_GetPluginNumberEvent(object sender, Busness.GetPluginNumEventArgs e)
        {
            HttpClientProtocol client = (HttpClientProtocol)sender;
            client.CurrentStep += 1;
            if (client.CurrentStep == MaxStep * 4)
            {
                client.HtmlContent += "step=" + e.step + ";number=" + e.number + ";type=" + e.type;
                client.SendResponse(client.HtmlContent, "200 OK", HttpExtension.HTML);
            }
            else
            {                
                client.HtmlContent += "step=" + e.step + ";number=" + e.number + ";type=" + e.type + "&";
            }
        }

        // 定时清除数据
        private void timer_Elapsed(object sender, System.Timers.ElapsedEventArgs e)
        {
            lock (m_threadObj)
            {
                canClearData = true;
            }
        }

        private void clearData()
        {
            long time = tool.GetTimeStamp();
            try
            {
                Dictionary<string, DataAccess.ExectInfo> eDictionaryTemp = new Dictionary<string, DataAccess.ExectInfo>(DataAccess.memeryData.UserExecInfo);
                // : 清除clearTime之前的数据,记录的时间戳精确到十分之一毫秒
                foreach (KeyValuePair<string, DataAccess.ExectInfo> info in eDictionaryTemp)
                {
                    if (time - info.Value.TimeStamp > clearTime * 10)
                    {
                        bs.DeleteExectInfo(info.Key);
                        WriteLog(eLogLevel.ell_Info,"清除数据：Key = " + info.Key);
                    }
                }
                GC.Collect();
            }
            catch (Exception ex)
            {
                WriteLog(eLogLevel.ell_Error, ex.Message);
            }
            lock (m_threadObj)
            {
                canClearData = false;
            }
        }

        // 客户端断开连接
        private void http_ClientDisconnected(object sender, SocketConnectEventArgs e)
        {
            WriteLog(eLogLevel.ell_Info,"客户端：" + e.client.clientSocket.RemoteEndPoint.ToString() + e.Event + "：\n" + e.httpContent);
            if (ClientDisConnected != null)
            {
                ClientDisConnected(sender, e);
            }
        }

        // 有客户端连入
        private void http_ClientConnected(object sender, SocketConnectEventArgs e)
        {
            WriteLog(eLogLevel.ell_Info,"客户端：" + e.client.clientSocket.RemoteEndPoint.ToString() + e.Event + "：\n" + e.httpContent);
            if (ClientConnected != null)
            {
                ClientConnected(sender, e);
            }
        }

        /// <summary>
        /// 开启Htpp 监听
        /// </summary>
        private void StartHttp()
        {
            IPAddress address = IPAddress.Any;
            //iocp.Start(59129);
            DateTime currentTime = DateTime.Now;
            log4net.GlobalContext.Properties["LogDir"] = currentTime.ToString("yyyyMM");
            log4net.GlobalContext.Properties["LogFileName"] = "_SocketAsyncServer" + currentTime.ToString("yyyyMMdd");
            Logger = log4net.LogManager.GetLogger(System.Reflection.MethodBase.GetCurrentMethod().DeclaringType);

            Configuration config = ConfigurationManager.OpenExeConfiguration(ConfigurationUserLevel.None);
            FileDirectory = config.AppSettings.Settings["FileDirectory"].Value;
            if (FileDirectory == "")
                FileDirectory = Path.Combine(Directory.GetCurrentDirectory(), "Files");
            if (!Directory.Exists(FileDirectory))
                Directory.CreateDirectory(FileDirectory);
            int port = 59129;
            if (!(int.TryParse(config.AppSettings.Settings["Port"].Value, out port)))
                port = 59129;
            int parallelNum = 0;
            if (!(int.TryParse(config.AppSettings.Settings["ParallelNum"].Value, out parallelNum)))
                parallelNum = 8000;
            int socketTimeOutMS = 0;
            if (!(int.TryParse(config.AppSettings.Settings["SocketTimeOutMS"].Value, out socketTimeOutMS)))
                socketTimeOutMS = 5 * 60 * 1000;

            AsyncSocketSvr = new AsyncSocketServer(parallelNum);
            AsyncSocketSvr.SocketTimeOutMS = socketTimeOutMS;
            AsyncSocketSvr.Init();
            IPEndPoint listenPoint = new IPEndPoint(IPAddress.Any, port);
            AsyncSocketSvr.Start(listenPoint);

           // Console.WriteLine("Press any key to terminate the server process....");
           // Console.ReadKey();
           // http.Start(address, port, 10000); 
        }

        /// <summary>
        /// 获取http响应的类实例
        /// </summary>
        /// <returns></returns>
        //public HttpResponseCore GetHttpResponseEntity()
        //{
        //    return http;
        //}

        /// <summary>
        /// 开启服务
        /// </summary>
        /// <returns></returns>
        public bool StartServer()
        {
            httpThread = new System.Threading.Thread(StartHttp);
            httpThread.Start();
            Console.WriteLine("开启http响应线程，线程ID: " + httpThread.ManagedThreadId);
            return true;
        }
        /// <summary>
        /// 停止服务
        /// </summary>
        public void StopServer()
        {
          //  http.Stop();
        }

        public void SaveExecInfo(string execName,httpInfo info)
        {
            try
            {
                bs.InsertData(execName, info.url, info.referrer, tool.GetTimeStamp());
            }
            catch (Exception ex)
            { 
                WriteLog(eLogLevel.ell_Error, ex.ToString());
            }
        }

        public string getUserExecName(string key)
        {
            return bs.GetUrlByKey(key);
        }
        /// <summary>
        /// 写日志
        /// </summary>
        /// <param name="log"></param>
        public void WriteLog(eLogLevel logLevel, string log)
        {
            if (logLevel == eLogLevel.ell_Debug)
            {
                Console.ForegroundColor = ConsoleColor.Green;
                Console.WriteLine(log);
            }
            else if (logLevel == eLogLevel.ell_Error)
            {
                Logger.Error(log);
            }
            else if (logLevel == eLogLevel.ell_Fatal)
            {
                Logger.Fatal(log);
            }
            else if (logLevel == eLogLevel.ell_Info)
            {
                Console.ForegroundColor = ConsoleColor.White;
                writeLog.WriteInLog(log);
            }
            else if (logLevel == eLogLevel.ell_Warning)
            {
                Logger.Warn(log);
            }            
        }
        
        public void WriteKeyUrlQueue(string key, string url,string referrer)
        {
            lock (m_threadObj)
            {
                try
                {
                    if (CurrentWriteQueue == 1)
                    {
                        keyUrlQueue1.Add(new KeyValuePair<string, httpInfo>(key, new httpInfo(url, referrer)));
                    }
                    else
                    {
                        keyUrlQueue2.Add(new KeyValuePair<string, httpInfo>(key, new httpInfo(url, referrer)));
                    }
                }
                catch (Exception ex) 
                { 
                    WriteLog(eLogLevel.ell_Error, ex.ToString()); 
                }
            }
        }

        public bool GetQueueContainsKey(string key)
        {
            lock (m_threadObj)
            {
                try
                {
                    if ((keyUrlQueue1.Count > 0 && keyUrlQueue1[keyUrlQueue1.Count - 1].Key == key) ||
                        (keyUrlQueue2.Count > 0 && keyUrlQueue2[keyUrlQueue2.Count - 1].Key == key))
                    {
                        return true;
                    }
                }
                catch {
                    return true;
                }
                return false;
            }
        }

        private void ReadKeyUrlQueue()
        {
            lock (m_threadObj)
            {
                try
                {
                    if (CurrentWriteQueue == 1)
                    {
                        for (int i = 0; i != keyUrlQueue2.Count; ++i )
                        {
                            InsertExectNameUrl(keyUrlQueue2[i].Key, keyUrlQueue2[i].Value);
                        }
                        keyUrlQueue2.Clear();
                        CurrentWriteQueue = 2;
                    }
                    else
                    {
                        for (int i = 0; i != keyUrlQueue1.Count; ++i)
                        {
                            InsertExectNameUrl(keyUrlQueue1[i].Key, keyUrlQueue1[i].Value);
                        }
                        keyUrlQueue1.Clear();
                        CurrentWriteQueue = 1;
                    }
                }
                catch (Exception ex)
                { 
                    WriteLog(eLogLevel.ell_Error, ex.ToString()); 
                }
            }
        }

        private void InsertExectNameUrl(string key, httpInfo info)
        {
            bs.InsertData(key, info.url,info.referrer, tool.GetTimeStamp());
        }

        public void ShutdownServer()
        {
            if (ServerClose != null)
            {
                ServerClose(null, null);
            }
            keyUrlQueue1.Clear();
            keyUrlQueue2.Clear();
            StopServer();
            httpThread.Abort();
            GC.Collect();
        }
    }
}
