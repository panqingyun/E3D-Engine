using System;
using System.Collections.Generic;
using System.IO;
using System.Threading;

namespace AsyncSocketServer
{

    public class WriteLog : ILog
    {
        private string logFile = "";
        private string fileDirectory = "";
        private static object m_threadObj = new object();
        private System.Threading.Thread writeLogThread;
        System.Timers.Timer timer = new System.Timers.Timer();
        private List<string> log1 = new List<string>();
        private List<string> log2 = new List<string>();
        private int CurrentWriteLog = 1;
        StreamWriter m_streamWriter;
        public void Stop()
        {
            writeLogThread.Abort();
        }
        public WriteLog(string fileDir)
        {
            fileDirectory = fileDir;
            writeLogThread = new System.Threading.Thread(WriteThread);
            writeLogThread.Start();
            Console.WriteLine("开启写日志线程，线程ID: " + writeLogThread.ManagedThreadId);
            if (!Directory.Exists(fileDirectory))
            {
                Directory.CreateDirectory(fileDirectory);
            }
            CreateNewFile();
        }

        /// <summary>
        /// 写日志
        /// </summary>
        /// <param name="log"></param>
        public void Log(eLogLevel logLevel, string log)
        {
            if (logLevel == eLogLevel.ell_Debug)
            {
                Console.ForegroundColor = ConsoleColor.Green;
                Console.WriteLine("[" + DateTime.Now.ToString() + "]" + log);
            }
            else if (logLevel == eLogLevel.ell_Error)
            {
                WriteInLog(log);
            }
            else if (logLevel == eLogLevel.ell_Fatal)
            {
                WriteInLog(log);
            }
            else if (logLevel == eLogLevel.ell_Info)
            {
                Console.ForegroundColor = ConsoleColor.White;
                WriteInLog(log);
            }
            else if (logLevel == eLogLevel.ell_Warning)
            {
                WriteInLog(log);
            }
        }

        /// <summary>
        /// 每天0点0分1秒创建新的日志文件
        /// </summary>
        private void CreateNewFile()
        {
            if (m_streamWriter != null)
            {
                m_streamWriter.Dispose();
                m_streamWriter.Close();
            }
            DateTime n = DateTime.Now;
            int d = n.Day;
            DateTime dt = new DateTime(n.Year, n.Month, d, 23, 59, 59);
            if(dt > n)
            {
                timer.Interval = (dt - n).TotalSeconds * 1000 + 2;
                logFile = fileDirectory + "\\Engine3D_" + DateTime.Now.Year + DateTime.Now.Month + DateTime.Now.Day + "_log.log";
            }
            else
            {
                timer.Interval = 60000;
                logFile = fileDirectory + "\\Engine3D_" + DateTime.UtcNow.Ticks + "__log.log";
            }
            timer.Elapsed += new System.Timers.ElapsedEventHandler(timer_Elapsed);
            timer.Start();
            if (File.Exists(logFile) == false)
            {
                createAndWriteLogFile("创建文件：[" + DateTime.Now.ToString() + "]");
            }
            m_streamWriter = File.AppendText(logFile);
        }

        void timer_Elapsed(object sender, System.Timers.ElapsedEventArgs e)
        {
            timer.Stop();
            CreateNewFile();
        }

        void WriteLog_ServerClose(object sender, EventArgs e)
        {
            writeLogThread.Abort();
        }

        public void WriteInLog(string log)
        {
            lock (m_threadObj)
            {
                try
                {
                    if (CurrentWriteLog == 1)
                    {
                        log1.Add(log);
                    }
                    else
                    {
                        log2.Add(log);
                    }
                }
                catch (Exception ex)
                {
                    Console.WriteLine(ex.Message);
                }
            }
        }
        private string ReadLog()
        {
            string log = "";
            lock (m_threadObj)
            {
                try
                {
                    if (CurrentWriteLog == 1)
                    {
                        if (log2.Count > 0)
                        {
                            log = log2[0];
                            log2.RemoveAt(0);
                        }
                        if (log2.Count == 0)
                        {
                            CurrentWriteLog = 2;
                        }
                    }
                    else if (CurrentWriteLog == 2)
                    {
                        if (log1.Count > 0)
                        {
                            log = log1[0];
                            log1.RemoveAt(0);
                        }
                        if (log1.Count == 0)
                        {
                            CurrentWriteLog = 1;
                        }
                    }
                }
                catch (Exception ex)
                {
                    Console.WriteLine(ex.Message);
                }
            }
            return log;
        }

        private void WriteThread()
        {
            while (true)
            {
                writeLog();
                Thread.Sleep(1);
            }
        }

        /// <summary>
        /// 写日志信息
        /// </summary>
        /// <param name="logInfo">写入文件的内容</param>
        private void writeLog()
        {
            string log = ReadLog();
            if (log != "")
            {
                log = "[" + DateTime.Now.ToString() + "]:\t" + log;
                writeLogToFile(log);
                Console.WriteLine(log);
            }

        }

        /// <summary>
        /// 往日志文件中追加信息
        /// </summary>
        /// <param name="logInfo">写入文件的内容</param>
        private void writeLogToFile(string logInfo)
        {
            try
            { 
                m_streamWriter.Flush();
                m_streamWriter.WriteLine(logInfo);
                m_streamWriter.Flush();
                
            }
            catch (System.Exception ex)
            {
                throw ex;
            }
        }

        /// <summary>
        /// 创建文件并写日志信息
        /// </summary>
        /// <param name="logInfo">写入文件的内容</param>
        private void createAndWriteLogFile(string logInfo)
        {
            FileStream fs = new FileStream(logFile, FileMode.CreateNew, FileAccess.Write);
            try
            {
                using (StreamWriter m_streamWriter = new StreamWriter(fs))
                {
                    m_streamWriter.Flush();
                    m_streamWriter.WriteLine(logInfo);
                    m_streamWriter.Flush();
                    m_streamWriter.Dispose();
                    m_streamWriter.Close();
                }
            }
            catch (Exception ex)
            {
                Console.WriteLine(ex.Message);
            }
            finally
            {
                fs.Dispose();
                fs.Close();
            }
        }

    }
}
