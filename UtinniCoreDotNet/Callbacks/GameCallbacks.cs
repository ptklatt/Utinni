using System;
using System.Collections.Generic;

namespace UtinniCoreDotNet.Callbacks
{
    public static class GameCallbacks
    {
        private static Queue<Action> mainLoopCallQueue = new Queue<Action>();

        private static UtinniCore.Delegates.Action_ dequeueMainLoopCallsAction;
        public static void Initialize()
        { 
            dequeueMainLoopCallsAction = DequeueMainLoopCalls; // Storing this in a variable is somehow needed to prevent corruption on WinForms resize. Very odd bug that I still don't fully understand.
            UtinniCore.Utinni.Game.AddMainLoopCallback(dequeueMainLoopCallsAction);
        }

        public static void AddMainLoopCall(Action call)
        {
            mainLoopCallQueue.Enqueue(call);
        }

        private static void DequeueMainLoopCalls()
        {
            while (mainLoopCallQueue.Count > 0)
            {
                var func = mainLoopCallQueue.Dequeue();
                func();
            }
        }
    }
}