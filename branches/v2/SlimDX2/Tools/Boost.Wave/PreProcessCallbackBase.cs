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
using System.Collections.Generic;

namespace Boost.Wave
{
    public abstract class PreProcessCallbackBase : IPreProcessCallback
    {
        public PreProcessCallbackBase()
        {
            Includes = new Stack<string>();
        }

        public Stack<string> Includes { get; private set; }

        public virtual void OnToken(Token token)
        {
        }

        public virtual void OnIncludBegin(string name)
        {
            Includes.Push(name);
        }

        public virtual string OnIncludeLoad(string name)
        {
            return "";
        }

        public virtual void OnIncludEnd()
        {
            Includes.Pop();
        }

        public virtual void OnMacroDefine(MacroDefinition macroDefinition)
        {
        }

        public virtual void OnMacroUndef(string name)
        {
        }

        public virtual void OnMacroFunctionExpand(MacroFunctionCall macroFunctionCall)
        {
        }

        public virtual void OnLogException(WaveExceptionSeverity severity, WaveExceptionErrorCode errorCode,
                                           string message)
        {
        }

        public PreProcessor Context { get; set; }
    }
}