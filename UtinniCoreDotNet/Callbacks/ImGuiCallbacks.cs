using System;
using System.Collections.Generic;

namespace UtinniCoreDotNet.Callbacks
{
    public static class ImGuiCallbacks
    {
        private static readonly List<Action> onPositionChangedCallbacks = new List<Action>();
        private static readonly List<Action> onRotationChangedCallbacks = new List<Action>();

        private static UtinniCore.Delegates.Action_ onPositionChangedCallbackAction;
        private static UtinniCore.Delegates.Action_ onRotationChangedCallbackAction;
        public static void Initialize()
        {
            onPositionChangedCallbackAction = OnPositionChangedCallback; // Storing this in a variable is somehow needed to prevent corruption on WinForms resize. Very odd bug that I still don't fully understand.
            onRotationChangedCallbackAction = OnRotationChangedCallback;

            UtinniCore.ImguiGizmo.imgui_impl.AddOnPositionChangedCallback(onPositionChangedCallbackAction);
            UtinniCore.ImguiGizmo.imgui_impl.AddOnRotationChangedCallback(onRotationChangedCallbackAction);
        }

        public static void AddOnPositionChangedCallback(Action call)
        {
            onPositionChangedCallbacks.Add(call);
        }

        public static void AddOnRotationChangedCallback(Action call)
        {
            onRotationChangedCallbacks.Add(call);
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
