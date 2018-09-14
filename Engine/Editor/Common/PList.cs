using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Xml;
using System.Xml.Linq;

namespace E3DEditor.Common
{
    public class PList : Dictionary<string, object>
    {
        public PList()
        {
        }

        public void Load(byte[] bytes)
        {
            using (var stream = new MemoryStream(bytes))
            {
                Load(stream);
            }
        }

        public void Load(string path)
        {
            using (var stream = new FileStream(path, FileMode.Open))
            {
                Load(stream);
            }
        }

        public void Load(Stream stream)
        {
            Clear();

            var reader = XmlReader.Create(stream, new XmlReaderSettings()
            {
                DtdProcessing = DtdProcessing.Parse
            });

            XDocument doc = XDocument.Load(reader);

            reader.Close();

            XElement plist = doc.Element("plist");
            XElement dict = plist.Element("dict");

            var dictElements = dict.Elements();
            Parse(this, dictElements);
        }

        public void Save(string path)
        {
            var contents = ToString();
            File.WriteAllText(path, contents);
        }

        public object GetValue(string key, object defaultValue = null)
        {
            return GetValue<object>(key, defaultValue);
        }

        public T GetValue<T>(string key, T defaultValue = default(T))
        {
            var splits = key.Split('/');

            Dictionary<string, object> dict = this;

            for (int i = 0; i < splits.Length - 1; i++)
            {
                dict = dict[splits[i]] as Dictionary<string, object>;
            }

            return (T)dict[splits[splits.Length - 1]];
        }

        private void Parse(PList dict, IEnumerable<XElement> elements)
        {
            for (int i = 0; i < elements.Count(); i += 2)
            {
                XElement key = elements.ElementAt(i);
                XElement val = elements.ElementAt(i + 1);

                dict[key.Value] = ParseValue(val);
            }
        }

        private List<object> ParseArray(IEnumerable<XElement> elements)
        {
            List<object> list = new List<object>();
            foreach (XElement e in elements)
            {
                object one = ParseValue(e);
                list.Add(one);
            }

            return list;
        }

        private object ParseValue(XElement val)
        {
            switch (val.Name.ToString())
            {
                case "string":
                    return val.Value;
                case "integer":
                    return int.Parse(val.Value);
                case "real":
                    return float.Parse(val.Value);
                case "true":
                    return true;
                case "false":
                    return false;
                case "dict":
                    PList plist = new PList();
                    Parse(plist, val.Elements());
                    return plist;
                case "array":
                    List<object> list = ParseArray(val.Elements());
                    return list;
                default:
                    throw new ArgumentException("Unsupported");
            }
        }

        public override string ToString()
        {
            var text = "<!DOCTYPE plist PUBLIC \" -//Apple//DTD PLIST 1.0//EN\" \"http://www.apple.com/DTDs/PropertyList-1.0.dtd\">\n";
            text += "<plist version=\"1.0\">\n";
            text += "<dict>\n";
            text += ToString(1) + "\n";
            text += "</dict>\n";
            text += "</plist>";

            return text;
        }

        private string ToString(int indent)
        {
            string prefix = "";
            for (int i = 0; i < indent; i++)
                prefix += "    ";

            string result = "";

            foreach (var item in this)
            {
                result += prefix + "<key>";
                result += item.Key;
                result += "</key>\n";

                var pList = item.Value as PList;
                if (pList != null)
                {
                    result += prefix + "<dict>\n";
                    result += pList.ToString(indent + 1);
                    result += prefix + "</dict>\n";
                }
                else
                {
                    if (item.Value is string)
                    {
                        result += prefix + "<string>";
                        result += item.Value;
                        result += "</string>\n";
                    }
                    else if (item.Value is int)
                    {
                        result += prefix + "<integer>";
                        result += item.Value;
                        result += "</integer>\n";
                    }
                    else if (item.Value is float)
                    {
                        result += prefix + "<real>";
                        result += item.Value;
                        result += "</real>\n";
                    }
                    else if (item.Value is bool)
                    {
                        var value = (bool)item.Value;
                        result += "<" + (value ? "true" : "false") + "/>";
                    }
                    else
                    {
                        result += prefix + "<value>";
                        result += item.Value;
                        result += "</value>\n";
                    }
                }
            }

            return result;
        }
    }
}
