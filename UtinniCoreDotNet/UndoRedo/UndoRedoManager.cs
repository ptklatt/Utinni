using System;
using System.Collections.Generic;
using UtinniCoreDotNet.PluginFramework;

namespace UtinniCoreDotNet.UndoRedo
{
    public class UndoRedoManager
    {
        private readonly Stack<IUndoCommand> undoCommands;
        private readonly Stack<IUndoCommand> redoCommands;

        public UndoRedoManager()
        {
            undoCommands = new Stack<IUndoCommand>();
            redoCommands = new Stack<IUndoCommand>();
        }

        public void AddUndoCommand(IEditorPlugin editorPlugin)
        {
            editorPlugin.AddUndoCommand += (sender, args) =>
            {
                if (undoCommands.Count > 0 && undoCommands.Peek().Merge(args.UndoCommand))
                {
                    return;
                }

                undoCommands.Push(args.UndoCommand);
            };
        }

        public void Undo()
        {
            if (undoCommands.Count == 0)
            {
                return;
            }

            IUndoCommand cmd = undoCommands.Pop();
            cmd.Undo();
            redoCommands.Push(cmd);
        }

        public void Redo()
        {
            if (redoCommands.Count == 0)
            {
                return;
            }

            IUndoCommand cmd = redoCommands.Pop();
            cmd.Execute();
            undoCommands.Push(cmd);
        }

    }
}
