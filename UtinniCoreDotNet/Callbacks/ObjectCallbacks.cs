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
