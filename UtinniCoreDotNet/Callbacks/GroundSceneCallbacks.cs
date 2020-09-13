using System;
using System.Collections.Generic;

namespace UtinniCoreDotNet.Callbacks
{
    public static class GroundSceneCallbacks
    {
        private static readonly Queue<Action> updateLoopCallQueue = new Queue<Action>();
        private static readonly Queue<Action> preDrawLoopCallQueue = new Queue<Action>();
        private static readonly Queue<Action> postDrawLoopCallQueue = new Queue<Action>();

        private static UtinniCore.Delegates.Action_IntPtr_float dequeueUpdateLoopCallsAction;
        private static UtinniCore.Delegates.Action_IntPtr dequeuePreDrawLoopCallsAction;
        private static UtinniCore.Delegates.Action_IntPtr dequeuePostDrawLoopCallsAction;
        public static void Initialize()
        {
            dequeueUpdateLoopCallsAction = DequeueUpdateLoopCalls;
            dequeuePreDrawLoopCallsAction = DequeuePreDrawLoopCalls;
            dequeuePostDrawLoopCallsAction = DequeuePostDrawLoopCalls;
            UtinniCore.Utinni.GroundScene.AddUpdateLoopCallback(dequeueUpdateLoopCallsAction);
            UtinniCore.Utinni.GroundScene.AddPreDrawLoopCallback(dequeuePreDrawLoopCallsAction);
            UtinniCore.Utinni.GroundScene.AddPostDrawLoopCallback(dequeuePostDrawLoopCallsAction);
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
                var func = updateLoopCallQueue.Dequeue();
                func();
            }
        }

        private static void DequeuePreDrawLoopCalls(IntPtr pGroundScene)
        {
            while (preDrawLoopCallQueue.Count > 0)
            {
                var func = preDrawLoopCallQueue.Dequeue();
                func();
            }
        }

        private static void DequeuePostDrawLoopCalls(IntPtr pGroundScene)
        {
            while (preDrawLoopCallQueue.Count > 0)
            {
                var func = preDrawLoopCallQueue.Dequeue();
                func();
            }
        }
    }
}
