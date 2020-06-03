using System.ComponentModel.Composition;
using System.Windows.Forms;

namespace UtinniCoreDotNet.PluginFramework
{
    [InheritedExport(typeof(IEditorPlugin))]
    public interface IEditorPlugin : IPlugin
    {
        UserControl GetControl();
    }
}
