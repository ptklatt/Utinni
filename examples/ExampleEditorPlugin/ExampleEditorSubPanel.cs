using System;
using UtinniCore.Utinni;
using UtinniCoreDotNet.Callbacks;
using UtinniCoreDotNet.Commands;
using UtinniCoreDotNet.PluginFramework;

namespace ExampleEditorPlugin
{
    // SubPanels should inherit EditorPanelBase as it sets up the the correct size automatically.
    public partial class ExampleEditorSubPanel : EditorPanelBase
    {
        private EventHandler<AddUndoCommandEventArgs> addUndoCommand;
        public ExampleEditorSubPanel(EventHandler<AddUndoCommandEventArgs> addUndoCommand)
        {
            InitializeComponent();
            this.addUndoCommand = addUndoCommand;

            ObjectCallbacks.AddOnTargetCallback(OnTarget);
            ImGuiCallbacks.AddOnPositionChangedCallback(OnPositionChanged);
            ImGuiCallbacks.AddOnRotationChangedCallback(OnRotationChanged);
        }

        private void btnAddWsNode_Click(object sender, EventArgs e)
        {
            GroundSceneCallbacks.AddUpdateLoopCall(() =>
            {
                WorldSnapshotReaderWriter.Node node = WorldSnapshot.CreateAddNode("object/tangible/furniture/elegant/shared_chair_s01.iff", Game.Player.ObjectToParent);

                if (node != null)
                {
                    addUndoCommand(this, new AddUndoCommandEventArgs(new AddWorldSnapshotNodeCommand(node)));
                }
            });
        }

        private void btnRemoveWsNode_Click(object sender, EventArgs e)
        {
            GroundSceneCallbacks.AddUpdateLoopCall(() =>
            {
                WorldSnapshotReaderWriter.Node node = WorldSnapshotReaderWriter.Get().GetNodeByNetworkId(Game.PlayerLookAtTargetObject.NetworkId);

                if (node != null)
                {
                    addUndoCommand(this, new AddUndoCommandEventArgs(new RemoveWorldSnapshotNodeCommand(node)));
                    WorldSnapshot.RemoveNode(node);
                }
            });
        }

        public void OnTarget()
        {
            var target = Game.PlayerLookAtTargetObject;
            if (target == null)
            {
                UtinniCore.ImguiGizmo.imgui_impl.Disable();
            }
            else
            {
                UtinniCore.ImguiGizmo.imgui_impl.Enable(target);
            }
        }

        public void OnPositionChanged() // ToDo Something is broken where it sometimes has 1-2 too many undo stages
        {
            bool allowMerge = UtinniCore.ImguiGizmo.imgui_impl.HasRecentPositionChange();
            GroundSceneCallbacks.AddUpdateLoopCall(() =>
            {
                var obj = Game.PlayerLookAtTargetObject;
                WorldSnapshotReaderWriter.Node node = WorldSnapshotReaderWriter.Get().GetNodeByNetworkId(obj.NetworkId);

                if (node != null)
                {
                    node.Transform.Position = obj.Transform.Position;
                    addUndoCommand(this, new AddUndoCommandEventArgs(new WorldSnapshotNodePositionChangedCommand(node, allowMerge)));
                }
            });
        }

        public void OnRotationChanged() // ToDo Something is broken where it sometimes has 1-2 too many undo stages
        {
            bool allowMerge = UtinniCore.ImguiGizmo.imgui_impl.HasRecentRotationChange();
            GroundSceneCallbacks.AddUpdateLoopCall(() =>
            {
                var obj = Game.PlayerLookAtTargetObject;
                WorldSnapshotReaderWriter.Node node = WorldSnapshotReaderWriter.Get().GetNodeByNetworkId(obj.NetworkId);

                if (node != null)
                {
                    node.Transform.CopyRotation(obj.Transform);
                    addUndoCommand(this, new AddUndoCommandEventArgs(new WorldSnapshotNodeRotationChangedCommand(node, allowMerge)));
                }
            });
        }

    }
}
