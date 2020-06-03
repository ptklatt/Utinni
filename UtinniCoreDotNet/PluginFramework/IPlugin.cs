using System;
using System.ComponentModel.Composition;

namespace UtinniCoreDotNet.PluginFramework
{
    public class PluginInformation
    {
        public string Name { get; }
        public string Description { get; }
        public string Author { get; }
        public Version Version { get; }

        public PluginInformation(string name, string desc, string author, Version version)
        {
            Name = name;
            Description = desc;
            Author = author;
            Version = version;
        }
    }

    [InheritedExport(typeof(IPlugin))]
    public interface IPlugin
    {
        PluginInformation Information { get; }
    }
}
