namespace UtinniCoreDotNet.UndoRedo
{
   public interface ICommand
    {
        void Execute();
        void Unexecute();
    }
}
