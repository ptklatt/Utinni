using System;
using System.Windows.Forms;
using UtinniCoreDotNet.UI.Theme;

namespace UtinniCoreDotNet.UI.Controls
{
    public class UtinniLabel : Label
    {
        public UtinniLabel()
        {
            UpdateColors();
        }
        private void UpdateColors()
        {
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
