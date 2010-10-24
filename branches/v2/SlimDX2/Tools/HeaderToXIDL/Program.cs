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

namespace SlimDX2.Tools.HeaderToXIDL
{
    /// <summary>
    /// Header To XIDL
    /// </summary>
    internal class Program
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

        /// <summary>
        /// Main
        /// </summary>
        /// <param name="args"></param>
        private static void Main(string[] args)
        {

            CommandArgs cmdArgs = ParseArgs(args);

            var cppHeaderParser = new CppHeaderParser {IncludePath = cmdArgs.IncludePath};

            cppHeaderParser.AddInclude("dxgi.h");
            cppHeaderParser.AddInclude("dxgiformat.h");
            cppHeaderParser.AddInclude("dxgitype.h");
            cppHeaderParser.AddInclude("d3dcommon.h");
            //cppHeaderParser.AddInclude("d3d10.h");
            //cppHeaderParser.AddInclude("d3d10_1.h");
            //cppHeaderParser.AddInclude("d3d10_1shader.h");
            //cppHeaderParser.AddInclude("d3d10effect.h");
            //cppHeaderParser.AddInclude("d3d10misc.h");
            //cppHeaderParser.AddInclude("d3d10sdklayers.h");
            //cppHeaderParser.AddInclude("d3d10shader.h");
            //cppHeaderParser.AddInclude("d3dx10.h");
            //cppHeaderParser.AddInclude("d3dx10core.h");
            //cppHeaderParser.AddInclude("d3dx10tex.h");
            //cppHeaderParser.AddInclude("d3dx10async.h");
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
        }
    }
}