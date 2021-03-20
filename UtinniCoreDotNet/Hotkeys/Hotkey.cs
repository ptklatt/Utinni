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

using System;
using System.Windows.Forms;
using UtinniCoreDotNet.Utility;

namespace UtinniCoreDotNet.Hotkeys
{
    public class Hotkey
    {
        public string Name;
        public string Text;
        public Keys ModifierKeys;
        public Keys Key;
        public Action OnDownCallback;
        public bool OverrideGameInput;
        public bool Enabled;
        public bool OnGameFocusOnly;

        public Hotkey(string name, string text, string keyComboStr, Action onDownCallback, bool overrideGameInput, bool enabled = true, bool onGameFocusOnly = false)
        {
            Name = name;
            Text = text;
            OnDownCallback = onDownCallback;
            OverrideGameInput = overrideGameInput;
            Enabled = enabled;
            OnGameFocusOnly = onGameFocusOnly;

            ProcessString(keyComboStr);
        }

        public Hotkey(string name, string text, Keys modifierKeys, Keys key, Action onDownCallback, bool overrideGameInput, bool enabled = true, bool onGameFocusOnly = false)
        {
            Name = name;
            Text = text;
            ModifierKeys = modifierKeys;
            Key = key;
            OnDownCallback = onDownCallback;
            OverrideGameInput = overrideGameInput;
            Enabled = enabled;
            OnGameFocusOnly = onGameFocusOnly;
        }

        private void ProcessString(string keyComboStr)
        {
            if (String.IsNullOrEmpty(keyComboStr))
            {
                Log.Warning("Hotkey " + Name + " failed to process empty key combo string.");
                return;
            }

            string key;

            int i = keyComboStr.IndexOf('+');
            if (i != -1)
            {
                key = keyComboStr.Substring(i + 1).Trim();

                string modifiers = keyComboStr.Substring(0, i).Trim();
                ModifierKeys = (Keys)Enum.Parse(typeof(Keys), modifiers, true);
            }
            else
            {
                key = keyComboStr.Trim();

                ModifierKeys = Keys.None;
            }

            Key = (Keys)Enum.Parse(typeof(Keys), key, true);
        }

        public void UpdateKeys(string keyComboStr)
        {
            ProcessString(keyComboStr);
        }

        public void UpdateKeys(Keys modifierKeys, Keys key)
        {
            ModifierKeys = modifierKeys;
            Key = key;
        }

        public string GetKeyComboString()
        {
            if (ModifierKeys == Keys.None)
            {
                return Key.ToString();
            }

            return ModifierKeys + " + " + Key;
        }

    }
}
