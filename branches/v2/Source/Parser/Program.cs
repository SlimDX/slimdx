// Copyright (c) 2007-2010 SlimDX Group
// 
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
// 
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
// 
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.
using System;
using System.IO;
using System.Reflection;
using SlimDX.XIDL;

namespace SlimDX.Parser
{
    /// <summary>
    /// Header To XIDL
    /// </summary>
    public class Program
    {
        /// <summary>
        /// Arguments
        /// </summary>
        private class CommandArgs
        {
            public string IncludePath = null;
            public string Output = "directx.xidl";            
        }

        /// <summary>
        /// Print usage and exit
        /// </summary>
        /// <param name="exitCode">exit code to return</param>
        /// <param name="message">error message to print</param>
        /// <param name="messageArgs">error message arguments</param>
        private static void Usage(int exitCode, string message = null, params string[] messageArgs)
        {
            Console.WriteLine(
                "Usage: {0} [/i:path_to_directx default = ENV($DXSDK_DIR\\Include)] [/o:output_xidl_file default = directx.xidl]",
                Assembly.GetEntryAssembly().FullName);
            if (message != null )
                Console.WriteLine(message, messageArgs);

            Environment.Exit(exitCode);
        }

        /// <summary>
        /// Parse arguments
        /// </summary>
        /// <param name="args"></param>
        /// <returns></returns>
        private static CommandArgs ParseArgs(string[] args)
        {
            var cmdArgs = new CommandArgs();

            foreach (var arg in args)
            {
                if (arg.StartsWith("/i:"))
                    cmdArgs.IncludePath = arg.Substring("/i:".Length);
                else if (arg.StartsWith("/o:"))
                    cmdArgs.Output = arg.Substring("/o:".Length);
                else
                    Usage(1, "Unexpected argument: {0}", arg);
            }

            if (cmdArgs.IncludePath == null)
            {
                cmdArgs.IncludePath = Environment.GetEnvironmentVariable("DXSDK_DIR");
                if (cmdArgs.IncludePath == null)
                    Usage(1, "Environment Variable [DXSDK_DIR] for DirectX SDK Directory is not defined");
                cmdArgs.IncludePath += Path.DirectorySeparatorChar + "Include";
            }

            return cmdArgs;
        }

        private string checkOkFile = ".slimdx_parser_ok";
        private DateTime creationTimeForGeneratorAssembly = File.GetLastWriteTime(Assembly.GetExecutingAssembly().Location);
        
        public bool IsParserAlreadyUpToDate(params string[] args)
        {
            CommandArgs cmdArgs = ParseArgs(args);
            return !(File.Exists(cmdArgs.Output) && File.Exists(checkOkFile) && File.GetLastWriteTime(checkOkFile) == creationTimeForGeneratorAssembly);
        }

        public CppIncludeGroup Run(params string[] args)
        {
            CommandArgs cmdArgs = ParseArgs(args);

            if (IsParserAlreadyUpToDate())
            {
                Console.WriteLine("The parser don't need to generate files again. Last run was successfull");
                return CppIncludeGroup.Read(cmdArgs.Output);
            }
            
            var cppHeaderParser = new CppHeaderParser();

            cppHeaderParser.IncludePath.Add(cmdArgs.IncludePath);

            // DXGI
            cppHeaderParser.AddInclude("dxgi.h");
            cppHeaderParser.AddInclude("dxgiformat.h");
            cppHeaderParser.AddInclude("dxgitype.h");

            // Direct3D9
            cppHeaderParser.AddInclude("d3d9.h");
            cppHeaderParser.AddInclude("d3d9caps.h");
            cppHeaderParser.AddInclude("d3d9types.h");
            cppHeaderParser.AddInclude("d3dx9.h");
            cppHeaderParser.AddInclude("d3dx9anim.h");
            cppHeaderParser.AddInclude("d3dx9core.h");
            cppHeaderParser.AddInclude("d3dx9effect.h");
            cppHeaderParser.AddInclude("d3dx9mesh.h");
            cppHeaderParser.AddInclude("d3dx9shader.h");
            cppHeaderParser.AddInclude("d3dx9shape.h");
            cppHeaderParser.AddInclude("d3dx9tex.h");
            cppHeaderParser.AddInclude("d3dx9xof.h");

            // Direct3D Common
            cppHeaderParser.AddInclude("d3dcommon.h");

            // Direct3D10 and Direct3D10.1
            cppHeaderParser.AddInclude("d3d10.h");
            cppHeaderParser.AddInclude("d3d10_1.h");
            cppHeaderParser.AddInclude("d3d10shader.h");
            cppHeaderParser.AddInclude("d3d10_1shader.h");
            cppHeaderParser.AddInclude("d3d10effect.h");
            cppHeaderParser.AddInclude("d3d10misc.h");
            cppHeaderParser.AddInclude("d3d10sdklayers.h");
            cppHeaderParser.AddInclude("d3dx10.h");
            cppHeaderParser.AddInclude("d3dx10core.h");
            cppHeaderParser.AddInclude("d3dx10tex.h");
            cppHeaderParser.AddInclude("d3dx10async.h");

            // Direct3D 11
            cppHeaderParser.AddInclude("d3d11.h");
            cppHeaderParser.AddInclude("d3d11shader.h");
            cppHeaderParser.AddInclude("d3dx11.h");
            cppHeaderParser.AddInclude("d3dx11core.h");
            cppHeaderParser.AddInclude("d3dx11tex.h");
            cppHeaderParser.AddInclude("d3dx11async.h");
            cppHeaderParser.AddInclude("d3dcompiler.h");

            cppHeaderParser.Run();

            // Write XIDL model to the disk
            cppHeaderParser.IncludeGroup.Write(cmdArgs.Output);

            // Write check ok file
            File.WriteAllText(checkOkFile, "");
            File.SetLastWriteTime(checkOkFile, creationTimeForGeneratorAssembly);

            return cppHeaderParser.IncludeGroup;
        }

        /// <summary>
        /// Main
        /// </summary>
        /// <param name="args"></param>
        private static void Main(string[] args)
        {
            Program program = new Program();
            program.Run(args);
        }
    }
}