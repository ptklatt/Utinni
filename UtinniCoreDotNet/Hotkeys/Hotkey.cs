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

        public Hotkey(string name, string text, string keyComboStr, Action onDownCallback, bool overrideGameInput, bool enabled = true)
        {
            Name = name;
            Text = text;
            OnDownCallback = onDownCallback;
            OverrideGameInput = overrideGameInput;
            Enabled = enabled;

            ProcessString(keyComboStr);
        }

        public Hotkey(string name, string text, Keys modifierKeys, Keys key, Action onDownCallback, bool overrideGameInput, bool enabled = true)
        {
            Name = name;
            Text = text;
            ModifierKeys = modifierKeys;
            Key = key;
            OnDownCallback = onDownCallback;
            OverrideGameInput = overrideGameInput;
            Enabled = enabled;
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
