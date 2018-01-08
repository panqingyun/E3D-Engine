using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Xml;

namespace AsyncSocketServer
{
    class WriteXML
    {
        static string FileContent = "";
        //public static string WritePlatformConfigWithText(string fileName, List<PlatformInfo> platform)
        //{
        //    if (File.Exists(fileName))
        //    {
        //        string sysLogFile = System.AppDomain.CurrentDomain.BaseDirectory + fileName;
        //        FileContent = "<?xml version=\"1.0\" encoding=\"utf-8\" ?>" + 
        //            "\r\n<PlatformList>";
        //        foreach (PlatformInfo p in platform)
        //        {
        //            FileContent += "\r\n" + "   <platform pid=\"" + p.pid + "\" idfString=\"" + p.idString + "\" IdUrl=\"" + p.IdUrl + "\" sid=\"" + p.sid + "\" uid=\"" + p.uid + "\" loginUrl = \"" + p.loginUrl + "\"/>";
        //        }
        //        FileContent += "\r\n</PlatformList>";
        //        WriteInFile(sysLogFile);
        //    }
        //    else
        //    {
        //        //文件不存在，这里可以采用第一种方法写入数据
        //    }

        //    return "成功";
        //}
        static private void WriteInFile(string SysFile)
        {
            StreamWriter sw = new StreamWriter(SysFile, false, Encoding.Default);

            sw.Write("");
            sw.Close();
            if (File.Exists(SysFile))
            {
                writeToFile(FileContent,SysFile);
            }
            else
            {

            }
        }

        static private void writeToFile(string fileContent, string SysFile)
        {
            try
            {
                using (StreamWriter wr = File.AppendText(SysFile))
                {
                    wr.Flush();
                    wr.Write(fileContent);
                    wr.Flush();
                    wr.Dispose();
                    wr.Close();
                }
            }
            catch (System.Exception)
            {
                throw new Exception("write file wrong!");
            }
        }

        //     static void Main(string[] args)
        //    {
        //        XmlDocument xmldoc;
        //        XmlNode xmlnode;
        //        XmlElement xmlelem;

        //        xmldoc = new XmlDocument();
        //        //加入XML的声明段落,<?xml version="1.0" encoding="gb2312"?>
        //        XmlDeclaration xmldecl;
        //        xmldecl = xmldoc.CreateXmlDeclaration("1.0", "gb2312", null);
        //        xmldoc.AppendChild(xmldecl);

        //        //加入一个根元素
        //        xmlelem = xmldoc.CreateElement("", "Employees", "");
        //        xmldoc.AppendChild(xmlelem);
        //        //加入另外一个元素
        //        for (int i = 1; i < 3; i++)
        //        {

        //            XmlNode root = xmldoc.SelectSingleNode("Employees");//查找<Employees> 
        //            XmlElement xe1 = xmldoc.CreateElement("Node");//创建一个<Node>节点 
        //            xe1.SetAttribute("genre", "李赞红");//设置该节点genre属性 
        //            xe1.SetAttribute("ISBN", "2-3631-4");//设置该节点ISBN属性 

        //            XmlElement xesub1 = xmldoc.CreateElement("title");
        //            xesub1.InnerText = "CS从入门到精通";//设置文本节点 
        //            xe1.AppendChild(xesub1);//添加到<Node>节点中 
        //            XmlElement xesub2 = xmldoc.CreateElement("author");
        //            xesub2.InnerText = "候捷";
        //            xe1.AppendChild(xesub2);
        //            XmlElement xesub3 = xmldoc.CreateElement("price");
        //            xesub3.InnerText = "58.3";
        //            xe1.AppendChild(xesub3);

        //            root.AppendChild(xe1);//添加到<Employees>节点中 
        //        }
        //        //保存创建好的XML文档
        //        xmldoc.Save("c:/data.xml"); 
        //    }
        //}


        //public static string WritePlatformConfigWithXml(string fileName, List<PlatformInfo> platformList)
        //{
        //    if (File.Exists(fileName))
        //    {
        //        StreamWriter sw = new StreamWriter(fileName, false, Encoding.Default);
        //        sw.Write("");
        //        sw.Close();
        //    }
        //    else
        //    {
        //        File.Create(fileName);
        //    }
        //    XmlDocument doc = new XmlDocument();
        //    XmlDeclaration dec = doc.CreateXmlDeclaration("1.0", "utf-8", null);
        //    doc.AppendChild(dec);
        //    创建一个根节点（一级）
        //    XmlElement root = doc.CreateElement("PlatformList");
        //    doc.AppendChild(root);
        //    try
        //    {
        //        foreach (PlatformInfo pi in platformList)
        //        {
        //            创建节点
        //            XmlElement element = doc.CreateElement("platform");
        //            element.SetAttribute("pid", pi.pid);
        //            element.SetAttribute("idfString", pi.idString);
        //            element.SetAttribute("IdUrl", pi.IdUrl);
        //            element.SetAttribute("sid", pi.sid);
        //            element.SetAttribute("uid", pi.uid);
        //            element.SetAttribute("loginUrl", pi.loginUrl);
        //            element1.InnerText = "Sam Comment";
        //            root.AppendChild(element);
        //        }
        //    }
        //    catch (Exception ex)
        //    {
        //        return ex.ToString();
        //    }
        //    doc.Save(fileName);
        //    ServerMainLogic.GetServer().WriteLog(eLogLevel.ell_Debug, doc.OuterXml);
        //    return "成功！";

        //}
    }
}
