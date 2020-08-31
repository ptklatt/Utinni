namespace UtinniCoreDotNet.UndoRedo
{
   public interface IUndoCommand
    {
        // Gets the text displayed in the Undo/Redo lists
        string GetText();
        // Executes/redose the command
        void Execute();
        // Undos the command
        void Undo();
        // allows commands to situationally allow or disallow merging of commands 
        bool AllowMerge();
        // Returns true if the merge was successful
        bool Merge(IUndoCommand newCommand);
    }
}
