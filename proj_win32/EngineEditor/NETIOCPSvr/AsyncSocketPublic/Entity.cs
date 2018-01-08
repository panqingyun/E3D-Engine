using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Net.Sockets;
using System.IO;

namespace AsyncSocketServer
{
    public delegate string httpEventHandler(params string[] param);
    public delegate void SendFileEventHandler(string fileFullName);
    public delegate void OutputLogEvent(string logContent);
    public class SocketEventArgs : EventArgs
    {
        public string Event;
        public string httpContent; 
    }

    public class SocketConnectEventArgs : SocketEventArgs
    {
        public HttpClientProtocol client;
    }
    public delegate void SocketConnectEventHandler(object sender, SocketConnectEventArgs e);
    public delegate void SocketSendMsgEventHandler(object sender, string htm, params string[] param);
    public delegate void SocketTCPEventHandler(object sender, byte[] data);

    public class httpInfo
    {
        public httpInfo(string url, string reffer)
        {
            this.url = url;
            this.referrer = reffer;
        }
        public string url;
        public string referrer;
    };
    // Content types that are supported by our server
    // To see other types: http://www.webmaster-toolkit.com/mime-types.shtml
    public struct HttpExtension
    {
        public static string HTM = "text/html";
        public static string HTML = "text/html;charset=UTF-8";
        public static string XML = "text/xml";
        public static string TXT = "text/plain";
        public static string CSS = "text/css";
        public static string PNG = "image/png";
        public static string GIF = "image/gif";
        public static string JPG = "image/jpg";
        public static string JPEG = "image/jpeg";
        public static string ZIP = "application/zip";
        public static string JSON = "application/json;charset=UTF-8";
        public static string EXE = "application/x-msdownload";
    }

    public enum Platform
    {
        PLATFORM_UNKNOWN = 0,
        PLATFORM_YOUXI = 1,
        PLATFORM_YY = 2,
        PLATFORM_WAN360 = 3,
        PLATFORM_52XIYOU = 4,
        PLATFORM_37WAN = 5,
        PLATFORM_XUNLEI = 6,
        PLATFORM_SHUNWANG = 7,
    }

    public enum XMLFileState
    {
        eFileReadSucceed = 0,
        eFileNotExit = 1,
        eFileOpenWrong = 2,
        eElementWrong = 3,
    }

    class BusnessEntity
    {
        
    }

    
}
