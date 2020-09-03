using System;
using System.Collections.Generic;

namespace UtinniCoreDotNet.Callbacks
{
    public static class GameCallbacks
    {
        private static Queue<Action> mainLoopCallQueue = new Queue<Action>();
        private static Queue<Action> cleanupSceneCallQueue = new Queue<Action>();

        private static UtinniCore.Delegates.Action_ dequeueMainLoopCallsAction;
        private static UtinniCore.Delegates.Action_ dequeueCleanupSceneCallsAction;
        public static void Initialize()
        { 
            dequeueMainLoopCallsAction = DequeueMainLoopCalls; // Storing this in a variable is somehow needed to prevent corruption on WinForms resize. Very odd bug that I still don't fully understand.
            dequeueCleanupSceneCallsAction = DequeueCleanupSceneCalls;
            UtinniCore.Utinni.Game.AddMainLoopCallback(dequeueMainLoopCallsAction);
            UtinniCore.Utinni.Game.AddCleanupSceneCallback(dequeueCleanupSceneCallsAction);
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

        public static void AddCleanupSceneCall(Action call)
        {
            cleanupSceneCallQueue.Enqueue(call);
        }

        private static void DequeueCleanupSceneCalls()
        {
            while (cleanupSceneCallQueue.Count > 0)
            {
                var func = cleanupSceneCallQueue.Dequeue();
                func();
            }
        }
    }
}