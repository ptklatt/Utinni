using System.Collections.Generic;
using System.IO;
using System.Reflection;
using System.Windows.Forms;
using UtinniCore.Utinni;
using UtinniCoreDotNet.Callbacks;

namespace UtinniCoreDotNet.Hotkeys
{
    public class HotkeyManager
    {
        private readonly UtINI ini;

        public readonly Dictionary<string, Hotkey> Hotkeys = new Dictionary<string, Hotkey>();
        public bool OnGameFocusOnly;
        public bool Enabled = true;

        public HotkeyManager(bool onGameFocusOnly)
        {
            OnGameFocusOnly = onGameFocusOnly;
            ini = new UtINI(Path.GetDirectoryName(Assembly.GetCallingAssembly().Location) + "\\input.ini");
        }

        public void ProcessInput(Keys modifierKeys, Keys key)
        {
            if (!Enabled)
            {
                return;
            }

            foreach (var pair in Hotkeys)
            {
                Hotkey hotkey = pair.Value;
                if (hotkey.Enabled && hotkey.ModifierKeys == modifierKeys && hotkey.Key == key)
                {
                    if (hotkey.OverrideGameInput)
                    {
                        // Not happy about this solution, but works, ToDo find a better way
                        GameCallbacks.AddPreMainLoopCall(() =>
                        {
                            UtinniCore.Utinni.CuiIo.cui_io.EnableKeyboard(false);

                            hotkey.OnDownCallback();

                            // ToDo really far from perfect, occasionally doesn't proper block a call

                            GameCallbacks.AddMainLoopCall(() =>
                            {
                                GameCallbacks.AddPreMainLoopCall(() =>
                                {
                                    UtinniCore.Utinni.CuiIo.cui_io.EnableKeyboard(true);
                                });
                            });
                        });
                    }
                    else
                    {
                        hotkey.OnDownCallback();
                    }
                }
            }
        }

        public void Add(Hotkey hotkey)
        {
            Hotkeys[hotkey.Name] = hotkey;
        }

        public void CreateSettings()
        {
            foreach (var pair in Hotkeys)
            {
                ini.AddSetting("Hotkeys", pair.Key, pair.Value.GetKeyComboString(), UtINI.Value.Types.VtString);
            }
        }

        public void Load()
        {
            ini.Load();

            foreach (var pair in Hotkeys)
            {
                pair.Value.UpdateKeys(ini.GetString("Hotkeys", pair.Key));
            }
        }

        public void Save()
        {
            foreach (var pair in Hotkeys)
            {
                ini.SetString("Hotkeys", pair.Key, pair.Value.GetKeyComboString());
            }

            ini.Save();
        }
    }


}
