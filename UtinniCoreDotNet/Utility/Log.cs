using System.Diagnostics;
using UtinniCore.Utinni.Log;
using static UtinniCore.Utinni.utinni;

namespace UtinniCoreDotNet.Utility
{
    public static class Log
    {
        private static bool writeClassName;
        private static bool writeFunctionName;

        public static void LoadConfig()
        {
            writeClassName = GetConfig().GetBool("Log", "writeClassName");
            writeFunctionName = GetConfig().GetBool("Log", "writeFunctionName");
        }

        private static string FormatText(string text)
        {
            if (writeClassName)
            {
                var method = new StackTrace().GetFrame(2).GetMethod();

                if (writeFunctionName)
                {
                    return "[" + method.ReflectedType.Name + "][" + method.Name + "] " + text;
                }
                else
                {
                    return "[" + method.ReflectedType.Name + "] " + text;
                }
            }
            else
            {
                return text;
            }
        }

        public static void Critical(string text)
        {
            log.Critical(FormatText(text));
        }

        public static void Debug(string text)
        {
            log.Debug(FormatText(text));
        }

        public static void Error(string text)
        {
            log.Error(FormatText(text));
        }

        public static void Info(string text)
        {
            log.Info(FormatText(text));
        }

        public static void Warning(string text)
        {
            log.Warning(FormatText(text));
        }

        public static void CriticalSimple(string text)
        {
            log.Critical(text);
        }

        public static void DebugSimple(string text)
        {
            log.Debug(text);
        }

        public static void ErrorSimple(string text)
        {
            log.Error(text);
        }

        public static void InfoSimple(string text)
        {
            log.Info(text);
        }

        public static void WarningSimple(string text)
        {
            log.Warning(text);
        }
    }
}
