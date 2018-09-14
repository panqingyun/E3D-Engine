using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace E3DEditor.Common
{
    /// <summary>
    /// 枚举
    /// </summary>
    public static class EnumTools
    {

        private static Dictionary<Type, Dictionary<string, int>> typeValueEnumMap = new Dictionary<Type, Dictionary<string, int>>();

        private static Dictionary<Type, List<string>> typeStringList = new Dictionary<Type, List<string>>();

        static EnumTools()
        {
        }
        
        private static void initListFromMap(Dictionary<string, int> map, List<string> list, List<string> ignoreList)
        {
            foreach (KeyValuePair<string, int> pair in map)
            {
                bool bAdd = true;
                for (int i = 0; i < ignoreList.Count; i++)
                {
                    if (ignoreList[i] == pair.Key)
                    {
                        bAdd = false;
                        break;
                    }
                }
                if (bAdd)
                {
                    list.Add(pair.Key);
                }
            }
        }

        public static int GetEnumValue(string text, Type enumType)
        {
            if (typeValueEnumMap.ContainsKey(enumType))
            {
                if (typeValueEnumMap[enumType].ContainsKey(text))
                {
                    return typeValueEnumMap[enumType][text];
                }
            }
            return -1;
        }

        public static string GetTextByValue(int value, Type enumType)
        {
            if (typeValueEnumMap.ContainsKey(enumType))
            {
                foreach (KeyValuePair<string, int> kv in typeValueEnumMap[enumType])
                {
                    if (value == kv.Value)
                    {
                        return kv.Key;
                    }
                }
            }

            return string.Empty;
        }

        public static List<string> GetEnumListByType(Type enumType)
        {
            return null;
        }

        public static object Int2Enum(int value, Type enumType)
        {            
            return null;
        }
    }

}
