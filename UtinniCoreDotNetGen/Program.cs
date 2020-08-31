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

                // Needed for spdlog to work
                driver.ParserOptions.UnityBuild = true;
                driver.ParserOptions.EnableRTTI = true;
                driver.ParserOptions.AddDefines("SPDLOG_NO_EXCEPTIONS");
                driver.ParserOptions.AddDefines("FMT_EXCEPTIONS=0");

                var options = driver.Options;
                options.GeneratorKind = GeneratorKind.CSharp;
                options.OutputDir = slnDir + "UtinniCoreDotNet\\Generated\\";
                options.GenerateDebugOutput = false;

                options.SystemModule.SymbolsLibraryName = "UtinniCore-Symbols";

                string targetProjName = "UtinniCore";
                var module = options.AddModule(targetProjName);

                // Includes
                module.IncludeDirs.Add(slnDir);
                module.IncludeDirs.Add(slnDir + "external");
                module.IncludeDirs.Add(slnDir + targetProjName); // ToDo make this a loop to grab all the subfolders

                // Headers
                module.Headers.Add("utinni.h");
                module.Headers.Add("utility\\log.h");

                module.Headers.Add("swg\\client\\client.h");
                module.Headers.Add("swg\\game\\game.h");
                module.Headers.Add("swg\\graphics\\directx9.h");
                module.Headers.Add("swg\\graphics\\graphics.h");
                module.Headers.Add("swg\\misc\\network.h");
                module.Headers.Add("swg\\misc\\swg_math.h");
                module.Headers.Add("swg\\object\\creature_object.h");
                module.Headers.Add("swg\\scene\\ground_scene.h");
                module.Headers.Add("swg\\scene\\terrain.h");
                module.Headers.Add("swg\\scene\\world_snapshot.h");
                module.Headers.Add("swg\\ui\\cui_manager.h");
                module.Headers.Add("swg\\ui\\imgui_impl.h");

                // Library
                module.LibraryDirs.Add(slnDir + "bin\\" + buildMode + "\\");
                module.Libraries.Add(targetProjName + ".dll");
            }

            public void SetupPasses(Driver driver)
            {
            }

            public void Preprocess(Driver driver, ASTContext ctx)
            {
                ctx.IgnoreHeadersWithName("spdlog");
                ctx.IgnoreHeadersWithName("detourxs");
                ctx.IgnoreHeadersWithName("ADE32");
            }

            public void Postprocess(Driver driver, ASTContext ctx)
            {
            }

        }

        static void Main(string[] args)
        {
            ConsoleDriver.Run(new Gen());
            //Console.Read();
        }
    }
}
