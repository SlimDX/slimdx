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
using System.Security;

namespace Boost.Wave.Native
{
    [InterfaceType(ComInterfaceType.InterfaceIsIUnknown), SuppressUnmanagedCodeSecurity]
    internal interface INativePreProcessCallback
    {
        void Token(TokenId tokenId, [MarshalAs(UnmanagedType.LPStr)] string value);

        void IncludeBegin([MarshalAs(UnmanagedType.LPStr)] string name);

//        [MarshalAs()]
        [PreserveSig]
        IntPtr IncludeLoadFile([MarshalAs(UnmanagedType.LPStr)] string name);

        void IncludeEnd();

        void MacroDefBegin([MarshalAs(UnmanagedType.LPStr)] string name, int nbArgs);
        void MacroDefBody();
        void MacroDefEnd();
        void MacroUnDef([MarshalAs(UnmanagedType.LPStr)] string name);

        void MacroArg();

        void MacroFunctionCall([MarshalAs(UnmanagedType.LPStr)] string name);
        void MacroFunctionEnd();


        void LogException(WaveExceptionSeverity severity, WaveExceptionErrorCode errorCode,
                          [MarshalAs(UnmanagedType.LPStr)] string message);
    }
}