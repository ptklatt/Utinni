using System;
using System.Collections.Generic;

namespace UtinniCoreDotNet.Callbacks
{
    public static class ImGuiCallbacks
    {
        private static readonly List<Action> onEnabledCallbacks = new List<Action>();
        private static readonly List<Action> onDisabledCallbacks = new List<Action>();
        private static readonly List<Action> onPositionChangedCallbacks = new List<Action>();
        private static readonly List<Action> onRotationChangedCallbacks = new List<Action>();

        private static UtinniCore.Delegates.Action_ onEnabledCallbackAction;
        private static UtinniCore.Delegates.Action_ onDisabledCallbackAction;
        private static UtinniCore.Delegates.Action_ onPositionChangedCallbackAction;
        private static UtinniCore.Delegates.Action_ onRotationChangedCallbackAction;
        public static void Initialize()
        {
            onEnabledCallbackAction = OnEnabledCallback; // Storing this in a variable is somehow needed to prevent corruption on WinForms resize. Very odd bug that I still don't fully understand.
            onDisabledCallbackAction = OnDisabledCallback;
            onPositionChangedCallbackAction = OnPositionChangedCallback; 
            onRotationChangedCallbackAction = OnRotationChangedCallback;

            UtinniCore.ImguiGizmo.imgui_impl.AddOnEnabledCallback(onEnabledCallbackAction);
            UtinniCore.ImguiGizmo.imgui_impl.AddOnDisabledCallback(onDisabledCallbackAction);
            UtinniCore.ImguiGizmo.imgui_impl.AddOnPositionChangedCallback(onPositionChangedCallbackAction);
            UtinniCore.ImguiGizmo.imgui_impl.AddOnRotationChangedCallback(onRotationChangedCallbackAction);
        }

        public static void AddOnEnabledCallback(Action call)
        {
            onEnabledCallbacks.Add(call);
        }

        public static void AddOnDisabledCallback(Action call)
        {
            onDisabledCallbacks.Add(call);
        }

        public static void AddOnPositionChangedCallback(Action call)
        {
            onPositionChangedCallbacks.Add(call);
        }

        public static void AddOnRotationChangedCallback(Action call)
        {
            onRotationChangedCallbacks.Add(call);
        }

        public static void RemoveOnPositionChangedCallback(Action call)
        {
            onPositionChangedCallbacks.Remove(call);
        }

        public static void RemoveOnRotationChangedCallback(Action call)
        {
            onRotationChangedCallbacks.Remove(call);
        }

        private static void OnEnabledCallback()
        {
            foreach (Action callback in onEnabledCallbacks)
            {
                callback();
            }
        }

        private static void OnDisabledCallback()
        {
            foreach (Action callback in onDisabledCallbacks)
            {
                callback();
            }
        }

        private static void OnPositionChangedCallback()
        {
            foreach (Action callback in onPositionChangedCallbacks)
            {
                callback();
            }
        }

        private static void OnRotationChangedCallback()
        {
            foreach (Action callback in onRotationChangedCallbacks)
            {
                callback();
            }
        }
    }
}
