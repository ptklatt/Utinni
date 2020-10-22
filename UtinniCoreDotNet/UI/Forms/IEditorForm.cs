using System.Collections.Generic;
using System.Windows.Forms;
using UtinniCoreDotNet.PluginFramework;

namespace UtinniCoreDotNet.UI.Forms
{
    public interface IEditorForm
    {
        string GetName();
        void Create(IEditorPlugin editorPlugin, List<Form> parentChildren);
    }
}
