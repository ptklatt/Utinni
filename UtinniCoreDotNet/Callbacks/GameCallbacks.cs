using System;
using System.Collections.Generic;

namespace UtinniCoreDotNet.Callbacks
{
    public static class GameCallbacks
    {
        private static readonly List<Action> installCallback = new List<Action>();
        private static readonly List<Action> setupSceneCallback = new List<Action>();
        private static readonly List<Action> cleanupSceneCallback = new List<Action>();
        private static readonly Queue<Action> mainLoopCallQueue = new Queue<Action>();

        private static UtinniCore.Delegates.Action_ callInstallCallbacksAction;
        private static UtinniCore.Delegates.Action_ callSetupSceneCallbacksAction;
        private static UtinniCore.Delegates.Action_ callCleanupSceneCallbacksAction;
        private static UtinniCore.Delegates.Action_ dequeueMainLoopCallsAction;
        public static void Initialize()
        {
            // Storing this in a variable is somehow needed to prevent corruption on WinForms resize. Very odd bug that I still don't fully understand.
            callInstallCallbacksAction = CallInstallCallbacks;
            callSetupSceneCallbacksAction = CallSetupSceneCallbacks;
            callCleanupSceneCallbacksAction = CallCleanupSceneCallbacks;
            dequeueMainLoopCallsAction = DequeueMainLoopCalls;
            UtinniCore.Utinni.Game.AddInstallCallback(callInstallCallbacksAction);
            UtinniCore.Utinni.Game.AddSetSceneCallback(callSetupSceneCallbacksAction);
            UtinniCore.Utinni.Game.AddCleanupSceneCallback(callCleanupSceneCallbacksAction);
            UtinniCore.Utinni.Game.AddMainLoopCallback(dequeueMainLoopCallsAction);
        }

        public static void AddInstallCallback(Action call)
        {
            installCallback.Add(call);
        }

        public static void AddSetupSceneCall(Action call)
        {
            setupSceneCallback.Add(call);
        }

        public static void AddCleanupSceneCall(Action call)
        {
            cleanupSceneCallback.Add(call);
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

        private static void CallInstallCallbacks()
        {
            foreach (Action callback in installCallback)
            {
                callback();
            }
        }

        private static void CallSetupSceneCallbacks()
        {
            foreach (Action callback in setupSceneCallback)
            {
                callback();
            }
        }

        private static void CallCleanupSceneCallbacks()
        {
            foreach (Action callback in cleanupSceneCallback)
            {
                callback();
            }
        }
    }
}