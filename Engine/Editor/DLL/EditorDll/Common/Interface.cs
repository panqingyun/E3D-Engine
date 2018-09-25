using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace E3DEditor.Common
{
    public interface INode
    {
        object[] GetCustomAttributies(string name);
        void ChangeSelect();
    }

    public class SpecialGetAttributeClassMap
    {
        private static Dictionary<Type, bool> specialMap = new Dictionary<Type, bool>();

        public static void Register(Type type)
        {
            specialMap[type] = true;
        }

        public static bool GetIsSpecial(Type type)
        {
            return specialMap.ContainsKey(type);
        }
    }
}
