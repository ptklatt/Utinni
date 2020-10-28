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
using System.Collections.Concurrent;
using System.Collections.Generic;

namespace UtinniCoreDotNet.Callbacks
{
    public static class ObjectCallbacks
    {
        private static readonly SynchronizedCollection<Action> onTargetCallbacks = new SynchronizedCollection<Action>();
        private static readonly ConcurrentQueue<Action> onTargetCallQueue = new ConcurrentQueue<Action>();

        private static UtinniCore.Delegates.Action_IntPtr_C dequeueOnTargetCallsAction;
        public static void Initialize()
        {
            dequeueOnTargetCallsAction = DequeueOnTargetCalls; // Storing this in a variable is somehow needed to prevent corruption on WinForms resize. Very odd bug that I still don't fully understand.
            UtinniCore.Utinni.CreatureObject.creature_object.AddOnTargetCallback(dequeueOnTargetCallsAction);
        }

        public static void AddOnTargetCall(Action call)
        {
            onTargetCallQueue.Enqueue(call);
        }

        public static void AddOnTargetCallback(Action call)
        {
            onTargetCallbacks.Add(call);
        }

        public static void RemoveOnTargetCallback(Action call)
        {
            onTargetCallbacks.Remove(call);
        }

        private static void DequeueOnTargetCalls(IntPtr pTargetObject)
        {
            while (onTargetCallQueue.Count > 0)
            {
                if (onTargetCallQueue.TryDequeue(out var func))
                {
                    func(); // ToDo fix being able to set IntPtr to object, etc, to be able to pass it
                }
            }

            foreach (Action callback in onTargetCallbacks)
            {
                callback();
            }
        }
    }
}
