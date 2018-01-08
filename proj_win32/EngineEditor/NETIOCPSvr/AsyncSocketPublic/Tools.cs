using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.IO;
using System.Text.RegularExpressions;

namespace AsyncSocketServer
{
    public class Tools
    {
        //business bs = new business();
        /// <summary>
        /// 从Url获取 json 的回调函数名字
        /// </summary>
        /// <param name="url"></param>
        /// <returns></returns>
        public string GetJsonCallBackFromUrl(string url)
        {
            string[] info = url.Split('&');
            string uid = "";
            for (int i = 0; i < info.Length; i++)
            {
                if (info[i].Contains("successCallback"))
                {
                    uid = info[i].Split('=')[1];
                    break;
                }
            }
            return uid;
        }

        public string GetQueryString(string url,string arg)
        {
            if (!url.Contains(arg)) return "";
            string[] parm = url.Split('&');
            int index = url.IndexOf(arg);
            string pParam = url.Substring(index);
            string pString = pParam.Split('&')[0].Replace(arg+"=","");
            return pString;
        }

        public string GetQueryString(string url, string arg,char splitChar,string equalChar)
        {
            if (!url.Contains(arg)) return "";
            string[] parm = url.Split(splitChar);
            int index = url.IndexOf(arg);
            string pParam = url.Substring(index);
            string pString = pParam.Split(splitChar)[0].Replace(arg + equalChar, "");
            return pString;
        }

        private string resNumber = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
        /// <summary>
        ///  时间戳精确到十分之一毫秒 
        /// </summary>
        /// <returns></returns>
        public long GetTimeStamp()
        {
            DateTime timeStamp = new DateTime(1970, 1, 1); // 距离1970-1-1 0点的时间长度
            long timeStampNow = (DateTime.Now.ToUniversalTime().Ticks - timeStamp.Ticks) / 1000;
            return timeStampNow + 8 * 60 * 60 * 10000;
        }
        /// <summary>
        /// 获取距离今天0时0分0秒的时间长度，精确到十分之一毫秒
        /// </summary>
        /// <returns></returns>
        public long GetTimeLongToday()
        {
            DateTime timeStamp = new DateTime(DateTime.Now.Year, DateTime.Now.Month, DateTime.Now.Day); // 距离今天0点的时间长度
            long timeStampNow = (DateTime.Now.ToUniversalTime().Ticks - timeStamp.Ticks) / 1000;
            return timeStampNow + 8 * 60 * 60 * 10000;
        }
        /// <summary>
        /// 获取 6 位长度字符串
        /// </summary>
        /// <returns></returns>
        public string Get6RandomChar()
        {
            long number = GetTimeLongToday();
            string result = "";
            int numLength = 0;
            while (number >= 36)
            {
                result = resNumber[(int)(number % 36)] + result;
                number /= 36;
                numLength += 1;
            }
            if (number >= 0)
            {
                result = resNumber[(int)number] + result;
                numLength += 1;
            }
            for (int i = 0; i != 6 - numLength; ++i)
            {
                result = "0" + result;
            }
            return result;
        }
        /// <summary>
        /// 获得Http 消息头的 Referer 内容
        /// </summary>
        /// <param name="headerContent"></param>
        /// <returns></returns>
        public string GetRefererFromHttpHeader(string headerContent)
        {
            string Referer = "";
            string[] content = headerContent.Split('\n');
            for (int i = 0; i < content.Length; i++)
            {
                if (content[i].Contains("Referer"))
                {
                    Referer = content[i].Split(' ')[1];
                    break;
                }
            }
            return Referer;
        }

        public static System.Text.Encoding GetType(string FILE_NAME)
        {
            FileStream fs = new FileStream(FILE_NAME, FileMode.Open, FileAccess.Read);
            Encoding r = GetType(fs);
            fs.Close();
            return r;
        }

        /// <summary>
        /// 通过给定的文件流，判断文件的编码类型
        /// </summary>
        /// <param name="fs">文件流</param>
        /// <returns>文件的编码类型</returns>
        public static System.Text.Encoding GetType(FileStream fs)
        {
            byte[] Unicode = new byte[] { 0xFF, 0xFE, 0x41 };
            byte[] UnicodeBIG = new byte[] { 0xFE, 0xFF, 0x00 };
            byte[] UTF8 = new byte[] { 0xEF, 0xBB, 0xBF }; //带BOM
            Encoding reVal = Encoding.Default;

            BinaryReader r = new BinaryReader(fs, System.Text.Encoding.Default);
            int i;
            int.TryParse(fs.Length.ToString(), out i);
            byte[] ss = r.ReadBytes(i);
            if (IsUTF8Bytes(ss) || (ss[0] == 0xEF && ss[1] == 0xBB && ss[2] == 0xBF))
            {
                reVal = Encoding.UTF8;
            }
            else if (ss[0] == 0xFE && ss[1] == 0xFF && ss[2] == 0x00)
            {
                reVal = Encoding.BigEndianUnicode;
            }
            else if (ss[0] == 0xFF && ss[1] == 0xFE && ss[2] == 0x41)
            {
                reVal = Encoding.Unicode;
            }
            r.Close();
            return reVal;

        }

        /// <summary>
        /// 判断是否是不带 BOM 的 UTF8 格式
        /// </summary>
        /// <param name="data"></param>
        /// <returns></returns>
        private static bool IsUTF8Bytes(byte[] data)
        {
            int charByteCounter = 1; //计算当前正分析的字符应还有的字节数
            byte curByte; //当前分析的字节.
            for (int i = 0; i < data.Length; i++)
            {
                curByte = data[i];
                if (charByteCounter == 1)
                {
                    if (curByte >= 0x80)
                    {
                        //判断当前
                        while (((curByte <<= 1) & 0x80) != 0)
                        {
                            charByteCounter++;
                        }
                        //标记位首位若为非0 则至少以2个1开始 如:110XXXXX...........1111110X 
                        if (charByteCounter == 1 || charByteCounter > 6)
                        {
                            return false;
                        }
                    }
                }
                else
                {
                    //若是UTF-8 此时第一位必须为1
                    if ((curByte & 0xC0) != 0x80)
                    {
                        return false;
                    }
                    charByteCounter--;
                }
            }
            if (charByteCounter > 1)
            {
                throw new Exception("非预期的byte格式");
            }
            return true;
        }
    }
}
