using System.Collections.Generic;
using System.IO;
using System.Reflection;
using System.Windows.Forms;
using UtinniCore.Utinni;
using UtinniCoreDotNet.Utility;

namespace UtinniCoreDotNet.Hotkeys
{
    public class HotkeyManager
    {
        private readonly UtINI ini;

        public List<Hotkey> Hotkeys = new List<Hotkey>();
        public bool OnGameFocusOnly;

        public HotkeyManager(bool onGameFocusOnly)
        {
            OnGameFocusOnly = onGameFocusOnly;
            ini = new UtINI(Path.GetDirectoryName(Assembly.GetCallingAssembly().Location) + "\\input.ini");
        }

        public void ProcessInput(Keys modifierKeys, Keys key)
        {
            Log.InfoSimple(modifierKeys + " + " + key);
            foreach (Hotkey hotkey in Hotkeys)
            {
                Log.InfoSimple("Hotkey: " + hotkey.Name + " " + hotkey.GetKeyComboString());
                if (hotkey.ModifierKeys == modifierKeys && hotkey.Key == key)
                {
                    hotkey.OnDownCallback();

                    if (hotkey.OverrideGameInput)
                    {
                        // ToDo block game input
                    }
                }
            }
        }

        public void CreateSettings()
        {
            foreach (Hotkey hotkey in Hotkeys)
            {
                ini.AddSetting("Hotkeys", hotkey.Name, hotkey.GetKeyComboString(), UtINI.Value.Types.VtString); // new UtINI.Value("Hotkeys", hotkey.Name, hotkey.GetKeyComboString(), UtINI.Value.Types.VtString)
            }
        }

        public void Load()
        {
            ini.Load();

            foreach (Hotkey hotkey in Hotkeys)
            {
                hotkey.UpdateKeys(ini.GetString("Hotkeys", hotkey.Name));
            }
        }

        public void Save()
        {
            foreach (Hotkey hotkey in Hotkeys)
            {
                ini.SetString("Hotkeys", hotkey.Name, hotkey.GetKeyComboString());
            }

            ini.Save();
        }
    }


}
