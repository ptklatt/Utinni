using System;
using UtinniCoreDotNet.UndoRedo;
using UtinniCore.Utinni;
using UtinniCoreDotNet.Callbacks;

namespace ExampleEditorPlugin.Commands
{
    public class AddWorldSnapshotNodeCommand : ICommand
    {
        private WorldSnapshotReaderWriter.Node node;

        public AddWorldSnapshotNodeCommand()
        {

        }


        public void Execute()
        {
            GroundSceneCallbacks.AddUpdateLoopCall(() =>
            {
                var createdNode = WorldSnapshot.CreateNewNode("object/tangible/furniture/technical/shared_chair_s01.iff", Game.Player.ObjectToParent);

                node = new WorldSnapshotReaderWriter.Node(createdNode);

            });
        }

        public void Unexecute()
        {
            GroundSceneCallbacks.AddUpdateLoopCall(() =>
            {

                WorldSnapshot.RemoveNode(WorldSnapshotReaderWriter.Get().GetNodeByNetworkId(node.NodeNetworkId));

            });
        }
    }

    public class RemoveWorldSnapshotNodeCommand : ICommand
    {
        private WorldSnapshotReaderWriter.Node nodeCopy;

        public RemoveWorldSnapshotNodeCommand(WorldSnapshotReaderWriter.Node node)
        {
            nodeCopy = new WorldSnapshotReaderWriter.Node(node);
        }


        public void Execute()
        {
            GroundSceneCallbacks.AddUpdateLoopCall(() =>
            {
                WorldSnapshot.RemoveNode(WorldSnapshotReaderWriter.Get().GetNodeByNetworkId(nodeCopy.Id));
            });
        }

        public void Unexecute()
        {
            GroundSceneCallbacks.AddUpdateLoopCall(() =>
            {
                WorldSnapshot.CreateNewNode(nodeCopy.ObjectTemplateName, nodeCopy.Transform);

            });
        }
    }
}
