using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace E3DEditor.Common
{
    public delegate void ShowLogDelegate(string log);
    public class Debug
    {
        public static ShowLogDelegate ShowLogHandle;

        public static void Log(string log)
        {
            ShowLogHandle?.Invoke(log);
        }

        public static void Error(string err)
        {
            ShowLogHandle?.Invoke("[Error] " + err);
        }

        public static void Warning(string war)
        {
            ShowLogHandle?.Invoke("[Warning] " + war);
        }
    }
}
