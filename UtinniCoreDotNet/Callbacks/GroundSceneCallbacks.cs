using System;
using System.Collections.Concurrent;
using System.Collections.Generic;

namespace UtinniCoreDotNet.Callbacks
{
    public static class GroundSceneCallbacks
    {
        private static readonly ConcurrentQueue<Action> updateLoopCallQueue = new ConcurrentQueue<Action>();
        private static readonly ConcurrentQueue<Action> preDrawLoopCallQueue = new ConcurrentQueue<Action>();
        private static readonly ConcurrentQueue<Action> postDrawLoopCallQueue = new ConcurrentQueue<Action>();
        private static readonly SynchronizedCollection<Action> cameraChangeCallbacks = new SynchronizedCollection<Action>();

        private static UtinniCore.Delegates.Action_IntPtr_float dequeueUpdateLoopCallsAction;
        private static UtinniCore.Delegates.Action_IntPtr_C dequeuePreDrawLoopCallsAction;
        private static UtinniCore.Delegates.Action_IntPtr_C dequeuePostDrawLoopCallsAction;
        private static UtinniCore.Delegates.Action_ callCameraChangeCallbacksAction;

        public static void Initialize()
        {
            dequeueUpdateLoopCallsAction = DequeueUpdateLoopCalls;
            dequeuePreDrawLoopCallsAction = DequeuePreDrawLoopCalls;
            dequeuePostDrawLoopCallsAction = DequeuePostDrawLoopCalls;
            callCameraChangeCallbacksAction = CallCameraChangeCallbacks;
            UtinniCore.Utinni.GroundScene.AddUpdateLoopCallback(dequeueUpdateLoopCallsAction);
            UtinniCore.Utinni.GroundScene.AddPreDrawLoopCallback(dequeuePreDrawLoopCallsAction);
            UtinniCore.Utinni.GroundScene.AddPostDrawLoopCallback(dequeuePostDrawLoopCallsAction);
            UtinniCore.Utinni.GroundScene.AddCameraChangeCallback(callCameraChangeCallbacksAction);
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

        public static void AddCameraChangeCallback(Action call)
        {
            cameraChangeCallbacks.Add(call);
        }

        private static void DequeueUpdateLoopCalls(IntPtr pGroundScene, float elapsedTime)
        {
            while (updateLoopCallQueue.Count > 0)
            {
                if (updateLoopCallQueue.TryDequeue(out var func))
                {
                    func();
                }
            }
        }

        private static void DequeuePreDrawLoopCalls(IntPtr pGroundScene)
        {
            while (preDrawLoopCallQueue.Count > 0)
            {
                if (preDrawLoopCallQueue.TryDequeue(out var func))
                {
                    func();
                }
            }
        }

        private static void DequeuePostDrawLoopCalls(IntPtr pGroundScene)
        {
            while (preDrawLoopCallQueue.Count > 0)
            {
                if (preDrawLoopCallQueue.TryDequeue(out var func))
                {
                    func();
                }
            }
        }

        private static void CallCameraChangeCallbacks()
        {
            foreach (Action callback in cameraChangeCallbacks)
            {
                callback();
            }
        }

    }
}
