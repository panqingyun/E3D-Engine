using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.CompilerServices;
using System.Text;
using System.Threading.Tasks;

namespace E3DEngine
{
    public class Debug
    {
        [MethodImpl(MethodImplOptions.InternalCall)]
        private static extern void log_error(string err);

        [MethodImpl(MethodImplOptions.InternalCall)]
        private static extern void log_warning(string warning);

        [MethodImpl(MethodImplOptions.InternalCall)]
        private static extern void log_info(string info);

        public static void Log(string log)
        {
            log_info(log);
        }

        public static void LogError(string error)
        {
            log_error(error);
        }

        public static void LogWarning(string warning)
        {
            log_warning(warning);
        }

    }
}
