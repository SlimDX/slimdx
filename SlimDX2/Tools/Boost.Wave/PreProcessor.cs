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
using System.Runtime.InteropServices;
using Boost.Wave.Native;

namespace Boost.Wave
{
    public class PreProcessor
    {
        private string _headerStr;
        private string _fileName;
        private IPreProcessCallback _callback;
        private INativePreProcessor _nativeWave;

        public PreProcessor(string headerStr, string fileName, IPreProcessCallback callback)
        {
            callback.Context = this;

            _callback = callback;

            _headerStr = headerStr;
            _fileName = fileName;


            NativePreProcessCallbackImpl nativeCallback = new NativePreProcessCallbackImpl();
            nativeCallback.Callback = _callback;

            _nativeWave = WavePreprocess(_headerStr, _fileName, nativeCallback);
        }

        ~PreProcessor()
        {
            _nativeWave = null;
            _callback = null;
        }

        public void Run()
        {
            _nativeWave.Run();
        }

        public void DefineMacro(string macroDef, bool isPredefined)
        {
            _nativeWave.DefineMacro(macroDef, isPredefined);
        }

        public void AddIncludePath(string includePath)
        {
            _nativeWave.AddIncludePath(includePath);
        }

        //public void Run(string headerStr, string fileName, IPreProcessCallback callback)
        //{
        //    callback.Context = this;
        //    NativePreProcessCallbackImpl nativeCallback = new NativePreProcessCallbackImpl();
        //    nativeCallback.Callback = callback;

        //    WavePreprocess(headerStr, fileName, nativeCallback);
        //}

        // exported method of the C/C++ DLL.
        [DllImport("BoostWaveNative", CallingConvention = CallingConvention.Cdecl, ExactSpelling = true)]
        private static extern INativePreProcessor WavePreprocess(string headerStr, string fileName,
                                                                 INativePreProcessCallback callback);
    }
}