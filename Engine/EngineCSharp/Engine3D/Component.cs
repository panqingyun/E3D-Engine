using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Runtime.CompilerServices;
using System.Reflection;

namespace E3DEngine
{
    public class EConvert
    {
        private static Dictionary<Type, bool> normalTypeMap = new Dictionary<Type, bool>();
        static EConvert()
        {
            normalTypeMap[typeof(int)] = true;
            normalTypeMap[typeof(float)] = true;
            normalTypeMap[typeof(double)] = true;
            normalTypeMap[typeof(short)] = true;
            normalTypeMap[typeof(string)] = true;
            normalTypeMap[typeof(char)] = true;
            normalTypeMap[typeof(byte)] = true;
            normalTypeMap[typeof(uint)] = true;
            normalTypeMap[typeof(ushort)] = true;
            normalTypeMap[typeof(ulong)] = true;
            normalTypeMap[typeof(sbyte)] = true;
        }

        public static object ChangeType(Type tp, string _value)
        {
            if (normalTypeMap.ContainsKey(tp))
            {
                 return Convert.ChangeType(_value, tp);
            }
            else if (tp == typeof(bool))
            {
                if (_value == "true")
                {
                    return true;
                }
                else
                {
                    return false;
                }
            }
            else
            {
                // TODO
                return null;
            }
        }
    }

    public class Component : Object
    {
        protected Component()
        {
           
        }

        public GameObject gameObject
        {
            get;set;
        }
        
    }
}
