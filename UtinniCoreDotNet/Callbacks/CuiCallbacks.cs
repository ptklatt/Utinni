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

namespace UtinniCoreDotNet.Callbacks
{
    public static class CuiCallbacks
    {
        private static readonly SynchronizedCollection<Action<string>> onReceiveSystemMessage = new SynchronizedCollection<Action<string>>();

        private static UtinniCore.Delegates.Action_string dequeueOnReceiveSystemMessageAction;
        public static void Initialize()
        {
            dequeueOnReceiveSystemMessageAction = DequeueOnReceiveSystemMessageCallbacks; // Storing this in a variable is somehow needed to prevent corruption on WinForms resize. Very odd bug that I still don't fully understand.
            UtinniCore.Utinni.SystemMessageManager.AddReceiveMessageCallback(dequeueOnReceiveSystemMessageAction);
        }

        public static void AddOnReceiveSystemMessageCallback(Action<string> call)
        {
            onReceiveSystemMessage.Add(call);
        }

        private static void DequeueOnReceiveSystemMessageCallbacks(string msg)
        {
            foreach (Action<string> callback in onReceiveSystemMessage)
            {
                callback(msg);
            }
        }
    }
}
