/**
 * MIT License
 *
 * Copyright (c) 2020 Philip Klatt
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
**/

using System;
using System.Collections.Generic;

namespace UtinniCoreDotNet.Callbacks
{
    public static class ImGuiCallbacks
    {
        private static readonly SynchronizedCollection<Action> onEnabledCallbacks = new SynchronizedCollection<Action>();
        private static readonly SynchronizedCollection<Action> onDisabledCallbacks = new SynchronizedCollection<Action>();
        private static readonly SynchronizedCollection<Action> onPositionChangedCallbacks = new SynchronizedCollection<Action>();
        private static readonly SynchronizedCollection<Action> onRotationChangedCallbacks = new SynchronizedCollection<Action>();

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
