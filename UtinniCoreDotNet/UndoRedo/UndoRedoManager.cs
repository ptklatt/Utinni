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
using UtinniCoreDotNet.Callbacks;
using UtinniCoreDotNet.PluginFramework;

namespace UtinniCoreDotNet.UndoRedo
{
    public class UndoRedoManager
    {
        private readonly Action onUpdateCommandsCallback;
        private readonly Action undoCallback;
        private readonly Action redoCallback;

        public readonly Stack<IUndoCommand> UndoCommands;
        public readonly Stack<IUndoCommand> RedoCommands;

        public UndoRedoManager(Action onUpdateCommandsCallback, Action undoCallback, Action redoCallback)
        {
            UndoCommands = new Stack<IUndoCommand>();
            RedoCommands = new Stack<IUndoCommand>();

            this.onUpdateCommandsCallback = onUpdateCommandsCallback;
            this.undoCallback = undoCallback;
            this.redoCallback = redoCallback;

            GameCallbacks.AddCleanupSceneCall(OnCleanupCallback);
        }

        private void OnCleanupCallback()
        {
            UndoCommands.Clear();
            RedoCommands.Clear();
            onUpdateCommandsCallback();
        }

        public void AddUndoCommand(IEditorPlugin editorPlugin)
        {
            editorPlugin.AddUndoCommand += (sender, args) =>
            {
                RedoCommands.Clear();
                if (UndoCommands.Count > 0 && UndoCommands.Peek().Merge(args.UndoCommand))
                {
                    return;
                }

                UndoCommands.Push(args.UndoCommand);

                onUpdateCommandsCallback();
            };
        }

        public void Undo()
        {
            if (UndoCommands.Count == 0)
            {
                return;
            }

            IUndoCommand cmd = UndoCommands.Pop();
            cmd.Undo();
            RedoCommands.Push(cmd);
            undoCallback();
        }

        public void Undo(int count)
        {
            for (int i = 0; i < count; i++)
            {
                Undo();
            }
        }

        public void Redo()
        {
            if (RedoCommands.Count == 0)
            {
                return;
            }

            IUndoCommand cmd = RedoCommands.Pop();
            cmd.Execute();
            UndoCommands.Push(cmd);
            redoCallback();
        }

        public void Redo(int count)
        {
            for (int i = 0; i < count; i++)
            {
                Redo();
            }
        }

    }
}
