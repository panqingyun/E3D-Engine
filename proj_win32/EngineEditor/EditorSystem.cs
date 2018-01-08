using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Service;
using System.Xml;

namespace EngineEditor
{
    class EditorSystem
    {
        private int ID;
        public EditorSystem()
        {
            ID = 0;
        }

        // EditorPanel 和 Config 一一对应
        public Dictionary<int, Dictionary<int, Dictionary<string, string>>> ConfigList = new Dictionary<int, Dictionary<int, Dictionary<string, string>>>();
        public Dictionary<int, EditorPanel> PanelList = new Dictionary<int, EditorPanel>();
        XmlDocument xml_doc = new XmlDocument();
        public void AddConfig(string tbl)
        {
            xml_doc.LoadXml(tbl);
            analysisXml();
        }

        private void analysisXml()
        {
            if (xml_doc == null)
            {
                return;
            }
            XmlElement rootElem = xml_doc.DocumentElement;
            XmlNodeList ConfigItemList = rootElem.ChildNodes;
            
            foreach (XmlNode item_node in ConfigItemList)
            {
                procecssXmlNode((XmlElement)item_node);
                ID++;
            }
        }

        private void procecssXmlNode(XmlElement node)
        {
            XmlNodeList items = node.GetElementsByTagName("ConfigItem");
            Dictionary<string, string> dicItems = new Dictionary<string, string>();
            foreach (XmlNode item_node in items)
            {
                // 把值填入字典

            }
        }

        public void Clear()
        {
            ID = 0;
            ConfigList.Clear();
            PanelList.Clear();
        }
    }
}
