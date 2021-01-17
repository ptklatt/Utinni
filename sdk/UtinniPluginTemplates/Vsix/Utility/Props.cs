using System.IO;
using System.Text;

namespace PluginTemplateWizard
{
    public static class Props
    {
        public static string DirectoryBuildPropsFilename = "Directory.Build.props";
        public static void CreateDotNetDirectoryProps(string slnPath)
        {
            if (File.Exists(slnPath + DirectoryBuildPropsFilename))
            {
                return;
            }

            StringBuilder sb = new StringBuilder();
            sb.AppendLine("<Project xmlns=\"http://schemas.microsoft.com/developer/msbuild/2003\">");
            sb.AppendLine("    <PropertyGroup>");
            sb.AppendLine("        <PluginOutputDir>$(SolutionDir)\\bin\\$(Configuration)\\</PluginOutputDir>");
            sb.AppendLine("    </PropertyGroup>");
            sb.AppendLine("");
            sb.AppendLine("    <PropertyGroup>");
            sb.AppendLine("        <UtinniCoreDotNetPath>..\\..\\..\\bin\\Release\\</UtinniCoreDotNetPath>");
            sb.AppendLine("    </PropertyGroup>");
            sb.AppendLine("");
            sb.AppendLine("    <PropertyGroup Condition=\"'$(Configuration)|$(Platform)' == 'RelWithDbgInfo|AnyCPU'\">");
            sb.AppendLine("        <OutputPath>$(PluginOutputDir)</OutputPath>");
            sb.AppendLine("        <DebugType>pdbonly</DebugType>");
            sb.AppendLine("        <Optimize>true</Optimize>");
            sb.AppendLine("        <DefineConstants>TRACE</DefineConstants>");
            sb.AppendLine("        <PlatformTarget>x86</PlatformTarget>");
            sb.AppendLine("        <ErrorReport>prompt</ErrorReport>");
            sb.AppendLine("        <LangVersion>7.3</LangVersion>");
            sb.AppendLine("        <CodeAnalysisRuleSet>MinimumRecommendedRules.ruleset</CodeAnalysisRuleSet>");
            sb.AppendLine("    </PropertyGroup>");
            sb.AppendLine("    <PropertyGroup Condition=\" '$(Configuration)|$(Platform)' == 'Release|AnyCPU' \">");
            sb.AppendLine("        <OutputPath>$(PluginOutputDir)</OutputPath>");
            sb.AppendLine("        <DebugType>pdbonly</DebugType>");
            sb.AppendLine("        <Optimize>true</Optimize>");
            sb.AppendLine("        <DefineConstants>TRACE</DefineConstants>");
            sb.AppendLine("        <PlatformTarget>x86</PlatformTarget>");
            sb.AppendLine("        <ErrorReport>prompt</ErrorReport>");
            sb.AppendLine("        <WarningLevel>4</WarningLevel>");
            sb.AppendLine("        <LangVersion>7.3</LangVersion>");
            sb.AppendLine("    </PropertyGroup>");
            sb.AppendLine("    <PropertyGroup Condition=\" '$(Configuration)|$(Platform)' == 'Debug|AnyCPU' \">");
            sb.AppendLine("        <OutputPath>$(PluginOutputDir)</OutputPath>");
            sb.AppendLine("        <DebugType>full</DebugType>");
            sb.AppendLine("        <DebugSymbols>true</DebugSymbols>");
            sb.AppendLine("        <Optimize>false</Optimize>");
            sb.AppendLine("        <DefineConstants>DEBUG;TRACE</DefineConstants>");
            sb.AppendLine("        <PlatformTarget>x86</PlatformTarget>");
            sb.AppendLine("        <ErrorReport>prompt</ErrorReport>");
            sb.AppendLine("        <WarningLevel>4</WarningLevel>");
            sb.AppendLine("        <LangVersion>7.3</LangVersion>");
            sb.AppendLine("    </PropertyGroup>");
            sb.AppendLine("</Project>");

            File.WriteAllText(slnPath + DirectoryBuildPropsFilename, sb.ToString());
        }
    }
}
