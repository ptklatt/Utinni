using System;
using System.Collections.Generic;

namespace UtinniCoreDotNet.Callbacks
{
    public static class GameCallbacks
    {
        private static Queue<Action> mainLoopCallQueue = new Queue<Action>();

        public static void Initialize()
        {
            UtinniCore.Utinni.Game.AddMainLoopCallback(DequeueMainLoopCalls);
        }

        public static void AddMainLoopCall(Action call)
        {
            mainLoopCallQueue.Enqueue(call);
        }

        private static void DequeueMainLoopCalls()
        {
            while (mainLoopCallQueue.Count > 0)
            {
                var call = mainLoopCallQueue.Dequeue();
                call();
            }
        }
    }
}