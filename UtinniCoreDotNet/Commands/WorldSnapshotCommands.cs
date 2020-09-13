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

        public bool AllowMerge() { return false; }

        public bool Merge(IUndoCommand newCommand) { return false; }
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

        public bool AllowMerge() { return false; }

        public bool Merge(IUndoCommand newCommand) { return false; }
    }

    public class WorldSnapshotNodePositionChangedCommand : IUndoCommand
    {
        private WorldSnapshotReaderWriter.Node nodeCopy;
        private readonly bool allowMerge;

        public WorldSnapshotNodePositionChangedCommand(WorldSnapshotReaderWriter.Node node, bool allowMerge)
        {
            nodeCopy = new WorldSnapshotReaderWriter.Node(node);
            this.allowMerge = allowMerge;
        }

        public string GetText()
        {
            return "Changed position of WorldSnapshot Node: (" + nodeCopy.Id + ") " + nodeCopy.ObjectTemplateName;
        }

        private void RestorePreviousPosition()
        {
            GroundSceneCallbacks.AddUpdateLoopCall(() =>
            {
                var obj = Network.GetObjectById(nodeCopy.Id);
                obj.Transform.Position = nodeCopy.Transform.Position;

                WorldSnapshotReaderWriter.Node node;
                if (nodeCopy.ParentId > 0)
                {
                    node = nodeCopy.ParentNode.GetChildById(nodeCopy.Id);
                }
                else
                {
                    node = WorldSnapshotReaderWriter.Get().GetNodeById(nodeCopy.Id);
                }

                nodeCopy = new WorldSnapshotReaderWriter.Node(node); // Update the nodeCopy to the up to date previous state
                node.Transform.Position = obj.Transform.Position;

                WorldSnapshot.DetailLevelChanged();
            });
        }

        public void Execute()
        {
            RestorePreviousPosition();
        }

        public void Undo()
        {
            RestorePreviousPosition();
        }

        public bool AllowMerge()
        {
            return allowMerge;
        }

        public bool Merge(IUndoCommand newCommand)
        {
            if (newCommand.GetType() == typeof(WorldSnapshotNodePositionChangedCommand))
            {
                var cmd = (WorldSnapshotNodePositionChangedCommand)newCommand;

                if (nodeCopy.Id == cmd.nodeCopy.Id && newCommand.AllowMerge())
                {
                    return true;
                }
            }

            return false;
        }
    }

    public class WorldSnapshotNodeRotationChangedCommand : IUndoCommand
    {
        private WorldSnapshotReaderWriter.Node nodeCopy;
        private readonly bool allowMerge;
        public WorldSnapshotNodeRotationChangedCommand(WorldSnapshotReaderWriter.Node node, bool allowMerge)
        {
            nodeCopy = new WorldSnapshotReaderWriter.Node(node);
            this.allowMerge = allowMerge;
        }

        public string GetText()
        {
            return "Changed rotation of WorldSnapshot Node: (" + nodeCopy.Id + ") " + nodeCopy.ObjectTemplateName;
        }

        private void RestorePreviousPosition()
        {
            GroundSceneCallbacks.AddUpdateLoopCall(() =>
            {
                var obj = Network.GetObjectById(nodeCopy.Id);
                obj.Transform.CopyRotation(nodeCopy.Transform);

                WorldSnapshotReaderWriter.Node node;
                if (nodeCopy.ParentId > 0)
                {
                    node = nodeCopy.ParentNode.GetChildById(nodeCopy.Id);
                }
                else
                {
                    node = WorldSnapshotReaderWriter.Get().GetNodeById(nodeCopy.Id);
                }

                nodeCopy = new WorldSnapshotReaderWriter.Node(node); // Update the nodeCopy to the up to date previous state
                node.Transform.CopyRotation(obj.Transform);

                WorldSnapshot.DetailLevelChanged();
            });
        }

        public void Execute()
        {
            RestorePreviousPosition();
        }

        public void Undo()
        {
            RestorePreviousPosition();
        }

        public bool AllowMerge()
        {
            return allowMerge;
        }

        public bool Merge(IUndoCommand newCommand)
        {
            if (newCommand.GetType() == typeof(WorldSnapshotNodeRotationChangedCommand))
            {
                var cmd = (WorldSnapshotNodeRotationChangedCommand)newCommand;

                if (nodeCopy.Id == cmd.nodeCopy.Id && newCommand.AllowMerge())
                {
                    return true;
                }
            }

            return false;
        }
    }
}
