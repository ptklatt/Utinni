using System.Collections.Generic;
using System.IO;
using EnvDTE;
using Microsoft.VisualStudio.TemplateWizard;
using PluginTemplateWizard;

namespace UtinniPluginTemplateVsix.Wizards
{
    public class DotNetSolutionWizard : IWizard
    {
        private DTE dte;
        private bool slnExists;

        public void RunStarted(object automationObject, Dictionary<string, string> replacementsDictionary, WizardRunKind runKind, object[] customParams)
        {
            dte = (DTE) automationObject;

            string slnPath = replacementsDictionary["$solutiondirectory$"] + "/";
            string slnFilename = replacementsDictionary["$specifiedsolutionname$"] + ".sln";

            slnExists = File.Exists(slnPath + slnFilename);

            Props.CreateDotNetDirectoryProps(slnPath);
        }

        public void RunFinished()
        {
            if (!slnExists)
            {
                dte.Solution.SolutionBuild.SolutionConfigurations.Add("RelWithDbgInfo", "", false);
            }
        }

        public void BeforeOpeningFile(ProjectItem projectItem) { }

        public void ProjectFinishedGenerating(Project project) { }

        public void ProjectItemFinishedGenerating(ProjectItem projectItem) { }

        public bool ShouldAddProjectItem(string filePath) { return true; }

    }
}