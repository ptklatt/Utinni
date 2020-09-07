using System;
using System.Collections.Generic;
using UtinniCoreDotNet.PluginFramework;

namespace UtinniCoreDotNet.UndoRedo
{
    public class UndoRedoManager
    {
        private readonly Action addUndoRedoCommandCallback;
        private readonly Action undoCallback;
        private readonly Action redoCallback;

        public readonly Stack<IUndoCommand> UndoCommands;
        public readonly Stack<IUndoCommand> RedoCommands;

        public UndoRedoManager(Action addUndoRedoCommandCallback, Action undoCallback, Action redoCallback)
        {
            UndoCommands = new Stack<IUndoCommand>();
            RedoCommands = new Stack<IUndoCommand>();

            this.addUndoRedoCommandCallback = addUndoRedoCommandCallback;
            this.undoCallback = undoCallback;
            this.redoCallback = redoCallback;
        }

        public void AddUndoCommand(IEditorPlugin editorPlugin)
        {
            editorPlugin.AddUndoCommand += (sender, args) =>
            {
                if (UndoCommands.Count > 0 && UndoCommands.Peek().Merge(args.UndoCommand))
                {
                    return;
                }

                UndoCommands.Push(args.UndoCommand);

                addUndoRedoCommandCallback();
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
