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

using System.Linq;
using Mono.Cecil;

namespace SlimDX.Combiner
{
    class Program
    {
        static void Main(string[] args)
        {
            var typeName = args[2];
            var sourceName = args[0];
            var sourceAssembly = AssemblyDefinition.ReadAssembly(sourceName);
            var sourceType = sourceAssembly.MainModule.GetType(typeName);

            var targetName = args[1];
            var targetAssembly = AssemblyDefinition.ReadAssembly(targetName);
            var targetType = targetAssembly.MainModule.GetType(typeName);

            foreach (var targetMethod in targetType.Methods)
            {
                var sourceMethod = sourceType.Methods.SingleOrDefault(x => x.FullName == targetMethod.FullName);
                if (sourceMethod == null)
                    continue;

                targetMethod.Body = sourceMethod.Body;
            }

            targetAssembly.Write(targetName);
        }
    }
}
