using System;
using System.Collections.Generic;

namespace UtinniCoreDotNet.Callbacks
{
    public static class ObjectCallbacks
    {
        private static List<Action> onTargetCallbacks = new List<Action>();

        private static Queue<Action> onTargetCallQueue = new Queue<Action>();

        private static UtinniCore.Delegates.Action_IntPtr dequeueOnTargetCallsAction;
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

        private static void DequeueOnTargetCalls(IntPtr pTargetObject)
        {
            while (onTargetCallQueue.Count > 0)
            {
                var func = onTargetCallQueue.Dequeue();
                func(); // ToDo fix being able to set IntPtr to object, etc, to be able to pass it
            }

            foreach (Action callback in onTargetCallbacks)
            {
                callback();
            }
        }
    }
}
