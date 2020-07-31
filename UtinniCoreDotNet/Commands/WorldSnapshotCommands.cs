using UtinniCore.Utinni;
using UtinniCoreDotNet.Callbacks;
using UtinniCoreDotNet.UndoRedo;

namespace UtinniCoreDotNet.Commands
{
    public class AddWorldSnapshotNodeCommand : IUndoCommand
    {
        private readonly WorldSnapshotReaderWriter.Node nodeCopy;
        private bool inititalExecute; // bool is used as a workaround for the limitations of using the original game code to handle adding nodes

        public AddWorldSnapshotNodeCommand(WorldSnapshotReaderWriter.Node node) // Node needs to already be created and added and passed to this ctor
        {
            nodeCopy = new WorldSnapshotReaderWriter.Node(node);
            inititalExecute = true;
        }

        public string GetText()
        {
            return "Added WorldSnapshot Node: (" + nodeCopy.Id + ") " + nodeCopy.ObjectTemplateName;
        }

        public void Execute()
        {
            if (inititalExecute) // As the node is already created and added before the first time this command is triggered, we skip
                return;

            GroundSceneCallbacks.AddUpdateLoopCall(() =>
            {
                WorldSnapshot.AddNode(nodeCopy);
            });
        }

        public void Undo()
        {
            GroundSceneCallbacks.AddUpdateLoopCall(() =>
            {
                // As we merely store a copy of the node, we need to fetch the actual node first before removing it
                WorldSnapshot.RemoveNode(WorldSnapshotReaderWriter.Get().GetNodeByNetworkId(nodeCopy.NodeNetworkId)); 
            });

            inititalExecute = false; // After the first undo, we enable the redo functionality
        }

        public bool Merge(IUndoCommand newCommand)
        {
            return false;
        }
    }

    public class RemoveWorldSnapshotNodeCommand : IUndoCommand
    {
        private readonly WorldSnapshotReaderWriter.Node nodeCopy;

        public RemoveWorldSnapshotNodeCommand(WorldSnapshotReaderWriter.Node node)
        {
            nodeCopy = new WorldSnapshotReaderWriter.Node(node);
        }

        public string GetText()
        {
            return "Removed WorldSnapshot Node: (" + nodeCopy.Id + ") " + nodeCopy.ObjectTemplateName;
        }

        public void Execute()
        {
            GroundSceneCallbacks.AddUpdateLoopCall(() =>
            {
                // As we merely store a copy of the node, we need to fetch the actual node first before removing it
                WorldSnapshot.RemoveNode(WorldSnapshotReaderWriter.Get().GetNodeByNetworkId(nodeCopy.Id));
            });
        }

        public void Undo()
        {
            GroundSceneCallbacks.AddUpdateLoopCall(() =>
            {
                WorldSnapshot.AddNode(nodeCopy);
            });
        }

        public bool Merge(IUndoCommand newCommand)
        {
            return false;
        }

        public void Unexecute()
        {
           
        }
    }
}
