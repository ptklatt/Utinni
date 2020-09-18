using System.Windows.Forms;

namespace UtinniCoreDotNet.UI.Forms
{
    public interface IEditorForm
    {
        string GetName();
        Form Create();
    }
}
