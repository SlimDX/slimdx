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
using SlimDX.Tools.XIDL;

namespace SlimDX.Tools.XIDLToCSharp
{
    internal partial class Program
    {
        /// <summary>
        /// Map DirectInput API
        /// </summary>
        public void MapDirectInput()
        {
            // Global namespace for DirectInput
            string assemblyName = Global.Name + ".DirectInput";
            string namespaceName = assemblyName;

            // Map dinput headers to corresponding assembly
            gen.MapIncludeToNamespace("dinput", assemblyName, namespaceName);

            // Limit Find to "dinput" in this method (in order to be sure that we don't touch other includes)
            group.FindContext.Add("dinput");

            // --------------------------------------------------------------------------------------------------------
            // DirectInput Enumerations
            // --------------------------------------------------------------------------------------------------------
            group.TagName<CppEnum>(@"^DI(.*)", "$1", false);

            // --------------------------------------------------------------------------------------------------------
            // DirectInput Structures
            // --------------------------------------------------------------------------------------------------------
            group.TagName<CppStruct>(@"^DI(.*)", "$1", false);


            // --------------------------------------------------------------------------------------------------------
            // DirectInput Interfaces
            // --------------------------------------------------------------------------------------------------------
            group.TagName<CppInterface>(@"^IDirectInput(.*)", "$1", false);
            
            // --------------------------------------------------------------------------------------------------------
            // DirectInput Functions
            // --------------------------------------------------------------------------------------------------------
            CSharpFunctionGroup dinputFunctionGroup = gen.CreateFunctionGroup(assemblyName, namespaceName, "DInput");
            group.TagFunction("^DirectInput.*$", "dinput.dll", dinputFunctionGroup);

            // Clear FindContext
            group.FindContext.Clear();
        }
    }
}