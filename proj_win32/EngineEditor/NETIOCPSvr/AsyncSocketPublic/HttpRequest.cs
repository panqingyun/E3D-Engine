using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Net;
using System.IO;

namespace AsyncSocketServer
{
    class HttpRequest
    {
        public string ProxyUser = "";
        public string ProxyPwd = "";
        private UTF8Encoding utf8 = new UTF8Encoding();
        Encoding gb2312 = Encoding.GetEncoding("GB2312");
        public HttpRequest()
        {
            System.Net.ServicePointManager.DefaultConnectionLimit = 10000;
        }
        public string Post(string url,string postData)
        {
            ASCIIEncoding encoding = new ASCIIEncoding();
            byte[] data = encoding.GetBytes(postData);                

            HttpWebRequest myRequest;
            try
            {
                myRequest = (HttpWebRequest)WebRequest.Create(url);
            }
            catch
            {
                return "";
            }
            Stream newStream = null;
            StreamReader reader = null;
            try
            {
                myRequest.Method = "POST";
                myRequest.ContentType = "application/x-www-form-urlencoded";
                myRequest.ContentLength = data.Length;
                newStream = myRequest.GetRequestStream();
                newStream.Write(data, 0, data.Length);
                newStream.Close();
                HttpWebResponse myResponse = (HttpWebResponse)myRequest.GetResponse();
                reader = new StreamReader(myResponse.GetResponseStream(), Encoding.Default);
                String result = reader.ReadToEnd();
                result = result.Replace("\r", "").Replace("\n", "").Replace("\t", "");
                result = "请求：" + url + "?" + postData + " 返回结果：" + utf8.GetString(gb2312.GetBytes(result));
               Debug.WriteLog.Log(eLogLevel.ell_Info, result );
                int status = (int)myResponse.StatusCode;
                reader.Close();
                return result;
            }
            catch (Exception ex)
            {
                if (newStream != null)
                {
                    newStream.Close();
                }
                if (reader != null)
                {
                    reader.Close();
                }
                 Debug.WriteLog.Log(eLogLevel.ell_Error, url + "?" + postData + "Http Post 请求出错！" + ex.ToString());
                return url + "?" + postData + "Http Post 请求出错！" + ex.Message;
            }
        }

        public bool Get(string url)
        {
            try
            {
                HttpWebRequest httpRequest = (HttpWebRequest)WebRequest.Create(url);
                httpRequest.Timeout = 10000;

                httpRequest.Method = "GET";
                HttpWebResponse httpResponse = (HttpWebResponse)httpRequest.GetResponse();
                StreamReader sr = new StreamReader(httpResponse.GetResponseStream(), System.Text.Encoding.GetEncoding("gb2312"));
                string result = sr.ReadToEnd();
                result = result.Replace("\r", "").Replace("\n", "").Replace("\t", "");
                int status = (int)httpResponse.StatusCode;
                sr.Close();
                return true;
            }
            catch (Exception ex)
            {
                 Debug.WriteLog.Log(eLogLevel.ell_Error, url + "Http GET 请求错误：" + ex.ToString());
                return false;
            }
        }
    }
}
