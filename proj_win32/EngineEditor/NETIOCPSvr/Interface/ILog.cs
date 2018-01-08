using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace AsyncSocketServer
{
    public enum eLogLevel
    {
        ell_Debug,
        ell_Error,
        ell_Fatal,
        ell_Warning,
        ell_Info,
    }

    public class Debug
    {
        public static ILog WriteLog;
        public static void Log(string log)
        {
            WriteLog.Log(eLogLevel.ell_Info, log);
        }

        public static void Error(string error)
        {
            WriteLog.Log(eLogLevel.ell_Error, error);
        }

        public static void Warning(string warning)
        {
            WriteLog.Log(eLogLevel.ell_Warning, warning);
        }

        public static void LogDebug(string debug)
        {
            WriteLog.Log(eLogLevel.ell_Debug, debug);
        }
    }

    public interface ILog
    {
        void Log(eLogLevel logLevel, string log);
    }
}
