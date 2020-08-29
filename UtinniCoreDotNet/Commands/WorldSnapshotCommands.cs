using UtinniCore.Utinni;
using UtinniCoreDotNet.Callbacks;
using UtinniCoreDotNet.UndoRedo;

namespace UtinniCoreDotNet.Commands
{
    public class AddWorldSnapshotNodeCommand : IUndoCommand
    {
        private WorldSnapshotReaderWriter.Node nodeCopy;

        public AddWorldSnapshotNodeCommand(WorldSnapshotReaderWriter.Node node) // Node needs to already be created and added and passed to this ctor
        {
            nodeCopy = new WorldSnapshotReaderWriter.Node(node);
        }

        public string GetText()
        {
            return "Added WorldSnapshot Node: (" + nodeCopy.Id + ") " + nodeCopy.ObjectTemplateName;
        }

        public void Execute()
        {
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
                if (nodeCopy.ParentId == 0)
                {
                    WorldSnapshot.RemoveNode(WorldSnapshotReaderWriter.Get().LastNode);
                }
                else
                {
                    WorldSnapshot.RemoveNode(nodeCopy.ParentNode.LastChild);
                }
            });
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
                if (nodeCopy.ParentId == 0)
                {
                    WorldSnapshot.RemoveNode(WorldSnapshotReaderWriter.Get().LastNode);
                }
                else
                {
                    WorldSnapshot.RemoveNode(nodeCopy.ParentNode.LastChild);
                }
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
    }
}
