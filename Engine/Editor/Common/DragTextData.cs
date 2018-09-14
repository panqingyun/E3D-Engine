using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace E3DEditor.Common
{
    public class DragTextData
    {
        public const string TablePropertyText = "table";
        public const string FilePropertyText = "file";
        public const string DragContentText = "text";
        public const string DragIDText = "ID";
        public static Dictionary<string, string> DescDragString(string dragText)
        {
            Dictionary<string, string> keyValueMap = new Dictionary<string, string>();
            if (dragText == null || dragText == "")
            {
                return keyValueMap;
            }
            string[] sData = dragText.Split(';');
            for(int i = 0; i < sData.Length; i ++)
            {
                string[] kv = sData[i].Split('=');
                keyValueMap[kv[0]] = kv[1];
            }
            return keyValueMap;
        }

        public static string MakeDragData(string[] keyValue)
        {
            string ret = "";
            for (int i = 0; i < keyValue.Length; i+=2 )
            {
                string _key = keyValue[i];
                string _value = keyValue[i + 1];
                ret += _key + "=" + _value;
                if (i != keyValue.Length-2)
                {
                    ret += ";"; 
                }
            }

            return ret;
        }
    }
}
