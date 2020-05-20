using System;
using System.Diagnostics;
using System.Windows.Forms;

namespace UtinniCoreDotNet
{
    internal static class Startup
    {
        private static bool m_initialized;
		
        [STAThread]
        private static int EntryPoint(string args)
        {
            if (!m_initialized)
            {
                m_initialized = true;
                Application.EnableVisualStyles();
				
				// Test Form
                Application.Run(new FormMain());
            }
            return 0;
        }


    }
}
