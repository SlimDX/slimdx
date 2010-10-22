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

namespace SlimDX2
{
    [StructLayout(LayoutKind.Sequential)]
    public struct Result
    {
        private int _code;

        public Result(int code)
        {
            _code = code;
        }

        public int Code
        {
            get { return _code; }
        }

        public bool Success
        {
            get { return Code >= 0; }
        }

        public bool Failure
        {
            get { return Code < 0; }
        }

        public static implicit operator Result(int result)
        {
            return new Result(result);
        }

        public override string ToString()
        {
            return string.Format("DirectX Exception (HRESULT = 0x{0:X})", _code);
        }

        public void CheckError()
        {
            if (_code < 0) throw new SlimDX2Exception(this);
        }
    }
}