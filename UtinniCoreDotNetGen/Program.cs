using System;
using System.IO;
using CppSharp;
using CppSharp.AST;
using CppSharp.Generators;

namespace UtinniCoreDotNetGen
{
    class Program
    {
        class Gen : ILibrary
        {
            public void Setup(Driver driver)
            {
                string workingDir = AppDomain.CurrentDomain.BaseDirectory;
                string buildMode = new DirectoryInfo(workingDir).Name;
                string slnDir = Directory.GetParent(workingDir.Substring(0, workingDir.LastIndexOf("\\bin\\"))).FullName + "\\"; 

                driver.ParserOptions.TargetTriple = "i686-pc-win32-msvc"; // Generates x86 EntryPoints
                var options = driver.Options;
                options.GeneratorKind = GeneratorKind.CSharp;
                options.OutputDir = slnDir + "UtinniCoreDotNet\\Generated\\";

                string targetProjName = "UtinniCore";
                var module = options.AddModule(targetProjName);

                // Includes
                module.IncludeDirs.Add(slnDir + targetProjName); // ToDo make this a loop to grab all the subfolders

                // Headers
                //module.Headers.Add("world_snapshot.h");

                // Library
                module.LibraryDirs.Add(slnDir + "bin\\" + buildMode + "\\");
                module.Libraries.Add(targetProjName + ".dll");
            }

            public void SetupPasses(Driver driver)
            {
            }

            public void Preprocess(Driver driver, ASTContext ctx)
            {
                ctx.IgnoreHeadersWithName("utinni");

            }

            public void Postprocess(Driver driver, ASTContext ctx)
            {
            }

        }

        static void Main(string[] args)
        {
            ConsoleDriver.Run(new Gen());
        }
    }
}
