// Copyright (c) 2007-2011 SlimDX Group
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
using System.Diagnostics;
using System.IO;

namespace SlimDX.Combiner {
    class Program {
        static void Main(string[] args) {
            Replace(args[2], args[0], args[1]);
        }

        static void Replace(string typeName, string sourceAssembly, string targetAssembly) {
            var sourceDissassembly = Path.GetTempFileName();
            var targetDissassembly = Path.GetTempFileName();

            Execute("ildasm.exe", "/nobar", "/utf8", string.Format("/out={0}", Quote(sourceDissassembly)), Quote(sourceAssembly));
            Execute("ildasm.exe", "/nobar", "/utf8", string.Format("/out={0}", Quote(targetDissassembly)), Quote(targetAssembly));

            var sourceCode = File.ReadAllLines(sourceDissassembly);
            var targetCode = File.ReadAllLines(targetDissassembly);
            var sourceRange = FindClass(typeName, sourceCode);
            var targetRange = FindClass(typeName, targetCode);

            var sourceLines = sourceRange.Item2 - sourceRange.Item1 + 1;
            var targetLines = targetRange.Item2 - targetRange.Item1 + 1;
            var buffer = new string[targetCode.Length - targetLines + sourceLines];
            var line = 0;
            while (line < targetRange.Item1) {
                buffer[line] = targetCode[line];
                ++line;
            }

            for (int i = sourceRange.Item1; i <= sourceRange.Item2; ++i) {
                buffer[line] = sourceCode[i];
                ++line;
            }

            for (int i = targetRange.Item2 + 1; i < targetCode.Length; ++i) {
                buffer[line] = targetCode[i];
                ++line;
            }

            var combinedFile = Path.GetTempFileName();
            File.WriteAllLines(combinedFile, buffer);

            Execute("ilasm.exe", "/nolog", "/quiet", "/dll", string.Format("/out={0}", Quote(targetAssembly)), Quote(combinedFile));
        }

        static Tuple<int, int> FindClass(string typeName, string[] lines) {
            var startLine = -1;
            var endLine = -1;
            for (int line = 0; line < lines.Length; ++line) {
                var text = lines[line];

                if (startLine < 0 && text.StartsWith(".class") && text.Contains(typeName)) {
                    startLine = line;
                } if (endLine < 0 && text.Contains(string.Format("end of class {0}", typeName))) {
                    endLine = line;
                }
            }

            return new Tuple<int, int>(startLine, endLine);
        }

        static string Quote(string s) {
            return string.Format("\"{0}\"", s);
        }
        static void Execute(string tool, params string[] arguments) {
            var process = new Process {
                StartInfo = {
                    FileName = tool,
                    Arguments = string.Join(" ", arguments),
                    UseShellExecute = false,
                    CreateNoWindow = true,
                    RedirectStandardOutput = true
                }
            };

            process.Start();
            process.WaitForExit();
        }
    }
}
