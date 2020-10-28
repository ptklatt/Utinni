/**
 * MIT License
 *
 * Copyright (c) 2020 Philip Klatt
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
**/

using System;
using System.Collections.Generic;
using System.Diagnostics;
using UtinniCore.Utinni.Log;
using static UtinniCore.Utinni.utinni;

namespace UtinniCoreDotNet.Utility
{
    public static class Log
    {
        private static bool writeClassName;
        private static bool writeFunctionName;

        private static readonly SynchronizedCollection<Action<string>> outputSinkCallbacks = new SynchronizedCollection<Action<string>>();

        private static UtinniCore.Delegates.Action_string outputSinkCallbacksAction;
        public static void Setup()
        {
            writeClassName = GetConfig().GetBool("Log", "writeClassName");
            writeFunctionName = GetConfig().GetBool("Log", "writeFunctionName");

            outputSinkCallbacksAction = CallOutputSinkCallbacks;
            log.AddOutputSinkCallback(outputSinkCallbacksAction);
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

        public static void AddOuputSinkCallback(Action<string> call)
        {
            outputSinkCallbacks.Add(call);
        }

        public static void RemoveOuputSinkCallback(Action<string> call)
        {
            outputSinkCallbacks.Remove(call);
        }

        private static void CallOutputSinkCallbacks(string msg)
        {
            foreach (Action<string> callback in outputSinkCallbacks)
            {
                callback(msg);
            }
        }
    }
}
