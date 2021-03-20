/**
 * MIT License
 *
 * Copyright (c) 2020 Philip Klatt
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
**/

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

        public void ProcessInput(Keys modifierKeys, Keys key, bool isGameFocused)
        {
            if (!Enabled)
            {
                return;
            }

            foreach (var pair in Hotkeys)
            {
                Hotkey hotkey = pair.Value;
                if (hotkey.Enabled && hotkey.ModifierKeys == modifierKeys && hotkey.Key == key) // ToDo figure out a way to have some hotkeys only work if the game has focus
                {
                    if (hotkey.OnGameFocusOnly && !isGameFocused)
                    {
                        continue;
                    }

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
