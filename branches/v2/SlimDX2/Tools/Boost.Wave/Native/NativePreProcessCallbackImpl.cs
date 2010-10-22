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
using System.Runtime.InteropServices;

namespace Boost.Wave.Native
{
    internal class NativePreProcessCallbackImpl : INativePreProcessCallback
    {
        internal IPreProcessCallback Callback;
        private MacroDefinition _currentMacroDefinition;
        private MacroFunctionCall _currentMacroFunctionCall;
        private bool _isMacroDefinitionBody;

        #region INativePreProcessCallback Members

        public void Token(TokenId tokenId, string value)
        {
            Token token = new Token {Id = tokenId, Value = value};
            if (_currentMacroDefinition != null)
            {
                if (_isMacroDefinitionBody)
                {
                    _currentMacroDefinition.Body.Add(token);
                }
                else
                {
                    _currentMacroDefinition.ParameterNames.Add(token);
                }
            }
            else if (_currentMacroFunctionCall != null)
            {
                _currentMacroFunctionCall.Arguments[_currentMacroFunctionCall.Arguments.Count - 1].Add(token);
            }
            else
            {
                try
                {
                    Callback.OnToken(token);
                }
                catch (Exception ex)
                {
                    LogError(ex);
                }
            }
        }

        public void IncludeBegin(string name)
        {
            try
            {
                Callback.OnIncludBegin(name);
            }
            catch (Exception ex)
            {
                LogError(ex);
            }
        }

        private void LogError(Exception ex)
        {
            Console.WriteLine(ex);
            Console.WriteLine(ex.StackTrace);
        }

        public IntPtr IncludeLoadFile(string name)
        {
            try
            {
                return Marshal.StringToHGlobalAnsi(Callback.OnIncludeLoad(name));
            }
            catch (Exception ex)
            {
                LogError(ex);
            }
            return Marshal.StringToHGlobalAnsi("");
        }

        public void IncludeEnd()
        {
            try
            {
                Callback.OnIncludEnd();
            }
            catch (Exception ex)
            {
                LogError(ex);
            }
        }

        public void MacroDefBegin(string name, int nbArgs)
        {
            _currentMacroDefinition = new MacroDefinition {Name = name};
        }

        public void MacroDefBody()
        {
            _isMacroDefinitionBody = true;
        }

        public void MacroDefEnd()
        {
            try
            {
                Callback.OnMacroDefine(_currentMacroDefinition);
            }
            catch (Exception ex)
            {
                LogError(ex);
            }
            _currentMacroDefinition = null;
            _isMacroDefinitionBody = false;
        }

        public void MacroUnDef(string name)
        {
            try
            {
                Callback.OnMacroUndef(name);
            }
            catch (Exception ex)
            {
                LogError(ex);
            }
        }

        public void MacroArg()
        {
            _currentMacroFunctionCall.Arguments.Add(new MacroFunctionCall.MacroArgument());
        }

        public void MacroFunctionCall(string name)
        {
            _currentMacroFunctionCall = new MacroFunctionCall {Name = name};
        }

        public void MacroFunctionEnd()
        {
            try
            {
                Callback.OnMacroFunctionExpand(_currentMacroFunctionCall);
            }
            catch (Exception ex)
            {
                LogError(ex);
            }

            _currentMacroFunctionCall = null;
        }

        public void LogException(WaveExceptionSeverity severity, WaveExceptionErrorCode errorCode, string message)
        {
            try
            {
                Callback.OnLogException(severity, errorCode, message);
            }
            catch (Exception ex)
            {
                LogError(ex);
            }
        }

        #endregion
    }
}