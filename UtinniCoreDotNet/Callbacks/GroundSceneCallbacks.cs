using System;
using System.Collections.Generic;

namespace UtinniCoreDotNet.Callbacks
{
    public static class GroundSceneCallbacks
    {
        private static Queue<Action> updateLoopCallQueue = new Queue<Action>();
        private static Queue<Action> preDrawLoopCallQueue = new Queue<Action>();
        private static Queue<Action> postDrawLoopCallQueue = new Queue<Action>();

        public static void Initialize()
        {
            UtinniCore.Utinni.GroundScene.AddUpdateLoopCallback(DequeueUpdateLoopCalls);
            UtinniCore.Utinni.GroundScene.AddPreDrawLoopCallback(DequeuePreDrawLoopCalls);
            UtinniCore.Utinni.GroundScene.AddPostDrawLoopCallback(DequeuePostDrawLoopCalls);
        }

        public static void AddUpdateLoopCall(Action call)
        {
            updateLoopCallQueue.Enqueue(call);
        }

        public static void AddPreDrawLoopCall(Action call)
        {
            preDrawLoopCallQueue.Enqueue(call);
        }

        public static void AddPostDrawLoopCall(Action call)
        {
            postDrawLoopCallQueue.Enqueue(call);
        }

        private static void DequeueUpdateLoopCalls(IntPtr pGroundScene, float elapsedTime)
        {
            while (updateLoopCallQueue.Count > 0)
            {
                var call = updateLoopCallQueue.Dequeue();
                call();
            }
        }

        private static void DequeuePreDrawLoopCalls(IntPtr pGroundScene)
        {
            while (preDrawLoopCallQueue.Count > 0)
            {
                var call = preDrawLoopCallQueue.Dequeue();
                call();
            }
        }

        private static void DequeuePostDrawLoopCalls(IntPtr pGroundScene)
        {
            while (preDrawLoopCallQueue.Count > 0)
            {
                var call = preDrawLoopCallQueue.Dequeue();
                call();
            }
        }
    }
}
