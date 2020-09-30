using UtinniCoreDotNet.PluginFramework;

namespace UtinniCoreDotNet.UI.Forms
{
    public interface IEditorForm
    {
        string GetName();
        void Create(IEditorPlugin editorPlugin);
    }
}
