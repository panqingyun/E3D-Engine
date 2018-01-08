using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Xml;

namespace AsyncSocketServer
{
    class ReadXML
    {
        private static XmlDocument doc = new XmlDocument();
        public static XMLFileState ReadUrlFromXML(string fileName,ref Dictionary<string,string> url)
        {
            try
            {
                doc.Load(fileName);
                XmlElement rootElem = doc.DocumentElement;
                if (rootElem == null)
                {
                    return XMLFileState.eFileOpenWrong;
                }
                XmlNodeList urlNodes = rootElem.GetElementsByTagName("Url");
                if (urlNodes == null)
                {
                    return XMLFileState.eElementWrong;
                }
                foreach (XmlNode node in urlNodes)
                {
                    string urlName = ((XmlElement)node).GetAttribute("urlName");
                    string urlContent = ((XmlElement)node).GetAttribute("urlContent");
                    url.Add(urlName, urlContent);
                }
            }
            catch(Exception ex)
            {
                return XMLFileState.eFileNotExit;
            }
            return XMLFileState.eFileReadSucceed;
        }

        
    }

}
