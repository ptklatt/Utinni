using System;
using System.Windows.Forms;
using UtinniCoreDotNet.UI.Theme;

namespace UtinniCoreDotNet.UI.Controls
{
    public class UtinniTextbox : TextBox
    {
        public UtinniTextbox()
        {
            BorderStyle = BorderStyle.FixedSingle;

            UpdateColors();
        }

        private void UpdateColors()
        {
            BackColor = Colors.PrimaryHighlight();
            ForeColor = Colors.Font();
        }

        protected override void OnEnabledChanged(EventArgs e)
        {
            base.OnEnabledChanged(e);

            if (Enabled)
            {
                ForeColor = Colors.Font();
            }
            else
            {
                ForeColor = Colors.FontDisabled();
            }
        }
    }
}
