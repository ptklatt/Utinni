using System;
using System.Windows.Forms;
using UtinniCoreDotNet.Utility;

namespace UtinniCoreDotNet.Hotkeys
{
    public class Hotkey
    {
        public string Name;
        public Keys ModifierKeys;
        public Keys Key;
        public Action OnDownCallback;
        public bool OverrideGameInput;

        public Hotkey(string name, string keyComboStr, Action onDownCallback, bool overrideGameInput)
        {
            Name = name;
            OnDownCallback = onDownCallback;
            OverrideGameInput = overrideGameInput;

            ProcessString(keyComboStr);
        }

        public Hotkey(string name, Keys modifierKeys, Keys key, Action onDownCallback, bool overrideGameInput)
        {
            Name = name;
            ModifierKeys = modifierKeys;
            Key = key;
            OnDownCallback = onDownCallback;
            OverrideGameInput = overrideGameInput;
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
                string modifiers = keyComboStr.Substring(0, i).Trim();
                key = keyComboStr.Substring(i + 1).Trim();

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
            return ModifierKeys + " + " + Key;
        }

    }
}
